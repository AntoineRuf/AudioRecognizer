/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: musicid_image_fetch/main.cpp
 *  Description:
 *  This example does a text search and finds images based on album or contributor.
 *  It also finds an image based on genre.
 *
 *  Command-line Syntax:
 *  sample clientId clientIdTag licenseFile [local|online]
 */

/* Online vs Local queries
 * For local queries, a Gracenote local database must be present.
 */

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <string.h>

#include "gnsdk.hpp"
#include "gnsdk_musicid.hpp"
#include "gnsdk_link.hpp"
#include "gnsdk_storage_sqlite.hpp"

using namespace gracenote;
using namespace gracenote::link;
using namespace gracenote::musicid;
using namespace gracenote::metadata;
using namespace gracenote::lookup_local;
using namespace gracenote::storage_sqlite;


/* Simulate MP3 tag data. */
typedef struct mp3_s
{
	const char* album_title_tag;
	const char* artist_name_tag;
	const char* genre_tag;

} mp3_file_t;


/* Simulate a folder of MP3s.
 *
 * file 1: Online - At the time of writing, yields an album match but no cover art or artist images are available.
 *                  Fetches the genre image for the returned album's genre.
 *         Local - Yields no match for the query of "Low Commotion Blues Band" against the sample database.
 *                 Uses the genre tag from the file, "Rock", to perform a genre search and fetches the genre image from that.
 * file 2: Online - Yields an album match for album tag "Supernatural". Fetches the cover art for that album.
 *         Local - Same result.
 * file 3: Online - Yields an album matches for Phillip Glass. Fetches the cover art for the first album returned.
 *         Local - Yields an artist match for the artist tag "Phillip Glass". Fetches the artist image for Phillip Glass.
 */
static mp3_file_t
	_mp3_folder[] =
{
	{"Ask Me No Questions",  "Low Commotion Blues Band",    "Rock"},
	{"Supernatural",         "Santana",                     GNSDK_NULL},
	{GNSDK_NULL,             "Phillip Glass",               GNSDK_NULL}
};

/* Callback delegate called when performing queries */
class LookupStatusEvents : public IGnStatusEvents
{
	/*-----------------------------------------------------------------------------
	 *  StatusEvent
	 */
	void
	StatusEvent(GnStatus status, gnsdk_uint32_t percentComplete, gnsdk_size_t bytesTotalSent, gnsdk_size_t bytesTotalReceived, IGnCancellable& canceller)
	{
		std::cout << "status (";

		switch (status)
		{
		case gnsdk_status_unknown:
			std::cout << "Unknown ";
			break;

		case gnsdk_status_begin:
			std::cout << "Begin ";
			break;

		case gnsdk_status_connecting:
			std::cout << "Connecting ";
			break;

		case gnsdk_status_sending:
			std::cout << "Sending ";
			break;

		case gnsdk_status_receiving:
			std::cout << "Receiving ";
			break;

		case gnsdk_status_disconnected:
			std::cout << "Disconnected ";
			break;

		case gnsdk_status_complete:
			std::cout << "Complete ";
			break;

		default:
			break;
		}

		std::cout << "), % complete (" << percentComplete << "), sent (" << bytesTotalSent << "), received (" << bytesTotalReceived << ")" << std::endl;

		GNSDK_UNUSED(canceller);
	}

};


/*-----------------------------------------------------------------------------
 *  fetchImage
 *  Display file size
 */
static bool
fetch_image(GnLink& link, gnsdk_link_content_type_t contentType, const char* imageTypeStr)
{
	gnsdk_uint32_t    fileSize      = 0;
	GnImagePreference imgPreference = exact;
	bool              notFound      = false;
	GnImageSize       imageSize     = kImageSize170;
	GnLinkContent     linkContent;

	/* Perform the image fetch */
	try
	{
		switch (contentType)
		{
		case gnsdk_link_content_cover_art:
			linkContent = link.CoverArt(imageSize, imgPreference);
			break;

		case gnsdk_link_content_image_artist:
			linkContent = link.ArtistImage(imageSize, imgPreference);
			break;

		case gnsdk_link_content_genre_art:
			linkContent = link.GenreArt(imageSize, imgPreference);
			break;

		default:
			return notFound;
		}

		fileSize = linkContent.DataSize();

		/* Do something with the image, e.g. display, save, etc. Here we just print the size. */
		printf("\nRetrieved: '%s': %d byte JPEG\n", imageTypeStr, fileSize);

		notFound = false;
	}
	catch (GnError& e)
	{
		std::cout << "Retrieving '" << imageTypeStr << "':\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
		notFound = true;
	}

	return notFound;
}


/*-----------------------------------------------------------------------------
 *  perform_image_fetch
 */
static void
perform_image_fetch(GnDataMatch& dataMatch, GnUser& user)
{
	GnLink link(dataMatch, user);

	/* Perform the image fetch */
	if (dataMatch.IsAlbum())
	{
		/* If album type get cover art */
		if (fetch_image(link, gnsdk_link_content_cover_art, "cover art"))
		{
			/* if no cover art, try to get the album's artist image */
			if (fetch_image(link, gnsdk_link_content_image_artist, "artist image"))
			{
				/* if no artist image, try to get the album's genre image so we have something to display */
				fetch_image(link, gnsdk_link_content_genre_art, "genre image");
			}
		}
	}
	else if (dataMatch.IsContributor())
	{
		/* If contributor type get artist image */
		if (fetch_image(link, gnsdk_link_content_image_artist, "artist image"))
		{
			/* if no artist image, try to get the album's genre image so we have something to display */
			fetch_image(link, gnsdk_link_content_genre_art, "genre image");
		}
	}
	else
	{
		printf("Unknown gdo Type, must be ALBUM or CONTRIBUTOR\n");
	}

}


/*-----------------------------------------------------------------------------
 *  perform_image_fetch
 *  Query sample text
 */
static int
do_sample_text_query(
	gnsdk_cstr_t album_title,
	gnsdk_cstr_t artist_name,
	GnUser&      user
	)
{
	gnsdk_cstr_t   gdo_type  = GNSDK_NULL;
	int            got_match = 0;

	printf("MusicID Text Match Query\n");

	if ((album_title == NULL) && (artist_name == NULL)) {    printf("Must pass album title or artist name\n");  return -1;  }
	if (album_title != GNSDK_NULL)  {   printf( "%-15s: %s\n", "album title", album_title );    }
	if (artist_name != GNSDK_NULL)  {   printf( "%-15s: %s\n", "artist name", artist_name );    }

	GnMusicId musicid(user);
	
	musicid.Options().LookupData(kLookupDataContent, true);
	/* Perform the query */
	GnResponseDataMatches response = musicid.FindMatches(album_title, GNSDK_NULL, artist_name, GNSDK_NULL, GNSDK_NULL);
	int                   count    = response.DataMatches().count();
	printf( "Number matches = %d\n\n", count);

	/* Get the first match type */
	if (count > 0 )  {   got_match = 1; }  /* OK, we got at least one match. */

	/* Just use the first match for demonstration. */
	GnDataMatch dataMatch = *(response.DataMatches().begin());
	gdo_type = dataMatch.GetType();
	printf( "First Match GDO type: %s\n", gdo_type);

	perform_image_fetch(dataMatch, user);

	return got_match;
}


/*-----------------------------------------------------------------------------
 *  find_genre_image
 */
static int
find_genre_image(GnUser& user, gnsdk_cstr_t genre, GnList& list)
{
	int gotMatch =   0;
	printf("Genre String Search\n");

	if (genre == NULL)  {       printf("Must pass a genre\n");      return -1;  }

	printf( "%-15s: %s\n", "genre", genre );
	/* Find the list element for our input string */
	GnListElement listElement(list.ElementByString(genre));

	printf("List element result: %s (level %d)\n", listElement.DisplayString(), listElement.Level());

	GnLink link(listElement, user);
	gotMatch = 1;
	fetch_image(link, gnsdk_link_content_genre_art, "genre image");

	return gotMatch;
}


/*-----------------------------------------------------------------------------
 *  process_sample_mp3
 */
static void
process_sample_mp3(mp3_file_t* mp3_file,   GnUser&    user, GnList& list)
{
	int got_match = 0;
	/* Do a music text query and fetch image from result. */
	got_match = do_sample_text_query(mp3_file->album_title_tag, mp3_file->artist_name_tag, user);

	/* If there were no results from the musicid query for this file, try looking up the genre tag to get the genre image. */
	if (0 == got_match)
	{
		if (GNSDK_NULL != mp3_file->genre_tag)
		{
			got_match = find_genre_image(user, mp3_file->genre_tag, list);
		}
	}

	/* did we succesfully find a relevant image? */
	if (0 == got_match)
	{
		printf("Because there was no match result for any of the input tags, you may want to associated the generic music image with this track, music_75x75.jpg, music_170x170.jpg or music_300x300.jpg\n");
	}
}


/*-----------------------------------------------------------------------------
 *  EnableStorage
 *		Enabling a storage module for GNSDK enables the SDK to use it 
 *		for caching of online queries, storing Playlist Collections, and
 *		to access to Local Databases for offline queries.
 *		Using a storage module is optional and the SDK is capable of operating
 *		without those features if you so chose.
 */
static void
EnableStorage(GnLookupMode lookupMode)
{
	/* Enable StorageSQLite module to use as our database engine */
	GnStorageSqlite& storageSqlite = GnStorageSqlite::Enable();

	/* The storage module defaults to use the current folder when initialized, 
	** but we set it manually here if we have a directory we'd like to use
	** instead for our local stores.
	*/
	if (lookupMode == kLookupModeLocal)
	{
		storageSqlite.StorageLocation("../../../../sample_data/sample_db");
	}
}

/*-----------------------------------------------------------------------------
 *  EnableLocalLookups
 *		Enabling a Local Lookup module gives the SDK the ability to perform
 *		certain queries without going online. This can enable an completely
 *		off-line mode for your application, or can act as a performance boost
 *		over going online for some queries.
 */
static void
EnableLocalLookups()
{
	/* Enable Local Lookup module to use for local queries */
	GnLookupLocal& gnLookupLocal = GnLookupLocal::Enable();

	/* By default this module will used the location set to the storage module. 
	** If an alternate path is desired, use the following API to set alternate 
	** database locations:
	*/
	gnLookupLocal.StorageLocation(kLocalStorageAll, "../../../../sample_data/sample_db");

	/* Display Local Database version */
	gnsdk_cstr_t gdb_version = gnLookupLocal.StorageInfo(kLocalStorageMetadata, kLocalStorageInfoVersion, 1);
	std::cout << "Gracenote Local Database Version : " << gdb_version << std::endl;
}


/*-----------------------------------------------------------------------------
 *  class UserStore
 *    Example implementation of interface: IGnUserStore
 *		Loads and stores User data for the GnUser object. This sample stores the
 *		user data to a local file named 'user.txt'.
 *		Your application should store the user data to an appropriate location.
 */
class UserStore : public IGnUserStore
{
public:
	GnString
	LoadSerializedUser(gnsdk_cstr_t clientId)
	{
		std::fstream	userRegFile;
		std::string		fileName;
		std::string		serialized;
		GnString		userData;

		fileName  = "user_";
		fileName += clientId;
		fileName += ".txt";

		userRegFile.open(fileName.c_str(), std::ios_base::in);
		if (!userRegFile.fail())
		{
			userRegFile >> serialized;
			userData = serialized.c_str();
		}
		return userData;
	}

	bool
	StoreSerializedUser(gnsdk_cstr_t clientId, gnsdk_cstr_t userData)
	{
		std::fstream userRegFile;
		std::string  fileName;

		fileName  = "user_";
		fileName += clientId;
		fileName += ".txt";

		/* store user data to file */
		userRegFile.open(fileName.c_str(), std::ios_base::out);
		if (!userRegFile.fail())
		{
			userRegFile << userData;
			return true;
		}
		return false;
	}
};


/*-----------------------------------------------------------------------------
 *  LoadLocale
 *    Load a 'locale' to return locale-specific values in the Metadata.
 *    This examples loads an English locale.
 */
void
LoadLocale(GnUser& user)
{
	LookupStatusEvents localeEvents;

	/* Set locale with desired Group, Language, Region and Descriptor */
	GnLocale locale( kLocaleGroupMusic, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, user, &localeEvents );

	/* set this locale as default for the duration of gnsdk */
	locale.SetGroupDefault();
}


/******************************************************************
*
*    MAIN
*
******************************************************************/
int
main(int argc, char* argv[])
{
	gnsdk_cstr_t  licenseFile        = GNSDK_NULL;
	gnsdk_cstr_t  clientId           = GNSDK_NULL;
	gnsdk_cstr_t  clientIdTag        = GNSDK_NULL;
	GnLookupMode  lookupMode         = kLookupModeInvalid;
	gnsdk_cstr_t  applicationVersion = "1.0.0.0";  /* Increment with each version of your app */


	if (argc == 5)
	{
		clientId         = argv[1];
		clientIdTag      = argv[2];
		licenseFile      = argv[3];

		if (strcmp(argv[4], "online") == 0)
		{
			lookupMode = kLookupModeOnline;
		}
		else if (strcmp(argv[4], "local") == 0)
		{
			lookupMode = kLookupModeLocal;
		}
		else
		{
			printf("Incorrect lookupMode specified.\n");
			printf("Please choose either \"local\" or \"online\"\n");
			return 0;
		}
	}
	else
	{
		std::cout << "\nUsage:  clientId clientIdTag license lookupMode\n"<< std::endl;
		return 0;
	}

	/* GNSDK initialization */
	try
	{
		GnManager gnMgr(licenseFile, kLicenseInputModeFilename);

		/* Display GNSDK Version infomation */
		std::cout << std::endl << "GNSDK Product Version : " << gnMgr.ProductVersion() << " \t(built " << gnMgr.BuildDate() << ")" << std::endl;

		/* Enable GNSDK logging */
		GnLog sampleLog(
			"sample.log",								/* File to write log to (optional if using delegate) */
			GnLogFilters().Error().Warning(),			/* Include only error and warning entries */
			GnLogColumns().All(),						/* Add all columns to log: timestamps, thread IDs, etc */
			GnLogOptions().MaxSize(0).Archive(false),	/* Max size of log: 0 means a new log file will be created each run. Archiving of logs disabled. */
			GNSDK_NULL									/* Optional callback delegate for logging messages */
			);
		sampleLog.Enable(kLogPackageAllGNSDK);			/* Enable for all GNSDK packages */

		/* Enable storage module */
		EnableStorage(lookupMode);

		if (lookupMode == kLookupModeLocal)
		{
			/* Enable local database lookups */
			EnableLocalLookups();
		}

		/* Get GnUser instance to allow us to perform queries */
		UserStore userStore;
		GnUser user = GnUser(userStore, clientId, clientIdTag, applicationVersion);

		/* set user to match our desired lookup mode (all queries done with this user will inherit the lookup mode) */
		user.Options().LookupMode(lookupMode);

		LoadLocale(user);

		/* Get the genre list handle.
		 * Be sure these params match the ones used in LoadLocale to avoid loading a different list into memory.
		 */
		GnList list(kListTypeGenres, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, user);

		/* Simulate iterating a sample of mp3s. */
		for (gnsdk_size_t file_index = 0; file_index < sizeof(_mp3_folder)/sizeof(mp3_file_t); file_index++)
		{
			printf("\n\n***** Processing File %lu *****\n", file_index);
			process_sample_mp3(&_mp3_folder[file_index], user, list);
		}

	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

