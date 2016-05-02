/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: Music response data object sample appilcation
 *  Description:
 *  This application uses MusicID to look up Album response data object content,	including
 *  Album	artist,	credits, title,	year, and genre.
 *  It demonstrates how to navigate the album response that returns basic track information,
 *  including artist, credits, title, track	number,	and	genre.
 *  Notes:
 *  For clarity and simplicity error handling in not shown here.
 *  Refer "logging"	sample to learn	about GNSDK	error handling.
 *
 *  Command-line Syntax:
 *  sample client_id client_id_tag license [local|online]
 */

/* Online vs Local queries
 * For local queries, a Gracenote local database must be present.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "gnsdk.hpp"
#include "gnsdk_musicid.hpp"
#include "gnsdk_storage_sqlite.hpp"
#include "gnsdk_lookup_local.hpp"

using namespace gracenote;
using namespace gracenote::musicid;
using namespace gracenote::metadata;
using namespace gracenote::lookup_local;
using namespace gracenote::storage_sqlite;


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


/*
 * Local function declarations
 */

static void
create_tab_string(
	gnsdk_uint32_t tab_index,
	gnsdk_char_t*  tab_string
	)
{
	gnsdk_uint32_t i;

	for (i = 0; i < tab_index; i++)
	{
		tab_string[i] =  '\t';
	}

	tab_string[i] = 0;
}


/*-----------------------------------------------------------------------------
 *  display_value
 */
static void
display_value(gnsdk_cstr_t str_value_tag, gnsdk_cstr_t str_value, gnsdk_uint32_t tab_index)
{
	gnsdk_char_t tab_string[256];

	create_tab_string(tab_index, tab_string);

	if (str_value && *str_value)
	{
		printf("%s%s: %s\n", tab_string, str_value_tag, str_value);
	}

}


/*-----------------------------------------------------------------------------
 *  navigate_name_official
 */
static void
navigate_name_official(GnName nameOfficial, gnsdk_uint32_t tab_index)
{
	gnsdk_char_t tab_string[1024];

	create_tab_string(tab_index, tab_string);
	tab_index += 1;

	printf("%sName Official:\n", tab_string);
	display_value("Display", nameOfficial.Display(), tab_index);

}


/*-----------------------------------------------------------------------------
 *  navigate_title_official
 */
static void
navigate_title_official(GnTitle titleOfficial, gnsdk_uint32_t tab_index)
{
	gnsdk_char_t tab_string[1024];

	create_tab_string(tab_index, tab_string);
	tab_index += 1;

	printf("%sTitle Official:\n", tab_string);
	display_value("Display", titleOfficial.Display(), tab_index);

}


/*-----------------------------------------------------------------------------
 *  navigate_contributor
 */
static void
navigate_contributor( GnContributor contributor, gnsdk_uint32_t tab_index )
{
	gnsdk_char_t tab_string[1024];

	create_tab_string( tab_index, tab_string );
	tab_index += 1;

	/* Navigate	Contributor	Object	*/
	printf("%sContributor:\n", tab_string);

	metadata::name_iterator it_name = contributor.NamesOfficial().begin();
	for (; it_name != contributor.NamesOfficial().end(); ++it_name)
	{
		navigate_name_official(*it_name, tab_index);
	}

	/* Display origin levels from the contributor */
	display_value("Origin Level 1", contributor.Origin(kDataLevel_1), tab_index );
	display_value("Origin Level 2", contributor.Origin(kDataLevel_2), tab_index );
	display_value("Origin Level 3", contributor.Origin(kDataLevel_3), tab_index );
	display_value("Origin Level 4", contributor.Origin(kDataLevel_4), tab_index );

	/* Display Era levels from the contributor */
	display_value("Era Level 1", contributor.Era(kDataLevel_1), tab_index );
	display_value("Era Level 2", contributor.Era(kDataLevel_2), tab_index );
	display_value("Era Level 3", contributor.Era(kDataLevel_3), tab_index );

	/* Display Artist type levels from the contributor */
	display_value("Artist Type	Level 1", contributor.ArtistType(kDataLevel_1), tab_index );
	display_value("Artist Type	Level 2", contributor.ArtistType(kDataLevel_2), tab_index );


}


/*-----------------------------------------------------------------------------
 *  navigate_credit
 */
static void
navigate_credit( GnArtist gnArtist, gnsdk_uint32_t tab_index )
{
	gnsdk_char_t tab_string[1024];

	create_tab_string(tab_index, tab_string);
	tab_index += 1;

	printf("%sCredit:\n", tab_string);

	navigate_contributor(gnArtist.Contributor(), tab_index);
}


/*-----------------------------------------------------------------------------
 *  navigate_track
 */
static void
navigate_track( GnTrack track, gnsdk_uint32_t tab_index )
{
	gnsdk_char_t tab_string[1024];

	create_tab_string(tab_index, tab_string);
	tab_index += 1;

	printf("%sTrack:\n", tab_string);

	display_value("Track Tui", track.Tui(), tab_index );

	display_value("Track Number", track.TrackNumber(), tab_index );

	/* Navigate	credit from track artist  */

	GnArtist artist = track.Artist();
	if (artist.native())
	{
		navigate_credit(track.Artist(), tab_index);
	}

	/* Navigate	Title Official from track  */
	navigate_title_official(track.Title(), tab_index);


	display_value("Year", track.Year(), tab_index );

	/*Gnere levels from track*/
	display_value("Genre Level 1", track.Genre(kDataLevel_1), tab_index );
	display_value("Genre Level 2", track.Genre(kDataLevel_2), tab_index );
	display_value("Genre Level 3", track.Genre(kDataLevel_3), tab_index );
}


/*-----------------------------------------------------------------------------
 *  navigate_album_response
 */
static void
navigate_album_response( GnResponseAlbums& response )
{
	gnsdk_uint32_t tab_index = 1;
	char           strBuffer [33];

	printf("\n***Navigating	Result GDO***\n");

	printf("Album:\n");

	/* Get the album from the match	response */
	int albCount =  response.Albums().count();
	if (albCount == 0) return;

	GnAlbum album = *(response.Albums().at(0));

	display_value("Package Language", album.Language(), tab_index );

	/* Navigate	the	credit artist from the album */
	navigate_credit( album.Artist(), tab_index );

	/* Navigate	Title Official from album  */
	navigate_title_official(album.Title(), tab_index);

	/* Display album attributes  */
	display_value("Year", album.Year(), tab_index );

	/*Display genre levels form album*/
	display_value("Genre Level 1", album.Genre(kDataLevel_1), tab_index );
	display_value("Genre Level 2", album.Genre(kDataLevel_2), tab_index );
	display_value("Genre Level 3", album.Genre(kDataLevel_3), tab_index );

	display_value("Album Label", album.Label(), tab_index );

	gnstd::gn_itoa(strBuffer, 33, album.TotalInSet());
	display_value("Total in Set", strBuffer, tab_index );

	gnstd::gn_itoa(strBuffer, 33, album.DiscInSet());
	display_value("Disc in Set", strBuffer, tab_index );

	printf("\tTrack Count: %d\n", album.Tracks().count());

	metadata::track_iterator it_track = album.Tracks().begin();
	for (; it_track != album.Tracks().end(); ++it_track)
	{
		navigate_track( *it_track, tab_index );
	}

}


/*-----------------------------------------------------------------------------
 *  do_album_tui_lookup
 */
static void
do_album_tui_lookup( gnsdk_cstr_t inputTuiId, gnsdk_cstr_t inputTuiTag, GnUser& user )
{
	printf("\n*****Sample MusicID Query*****\n");

	LookupStatusEvents statusEvents;
	GnMusicId musicid(user, &statusEvents);

	GnAlbum albObj(inputTuiId, inputTuiTag);

	GnResponseAlbums albResponse = musicid.FindAlbums(albObj);
	int              albCount    =  albResponse.Albums().count();
	if (albCount > 0)
	{
		/* Match */
		printf("Match.\n");

		/* Get first album GDO and check if	it's a partial album */
		GnAlbum album = *(albResponse.Albums().at(0));

		/* Is this a partial album? */
		bool fullResult = album.IsFullResult();
		if (!fullResult)
		{
			printf("retrieving FULL	RESULT\n");
			/* Query for this match	in full	*/
			GnResponseAlbums full_alb_response = musicid.FindAlbums(album);

			/* Full	album match	retrieved. Now we navigate the full	album GDO */
			navigate_album_response(full_alb_response);

		}
		else
		{
			navigate_album_response(albResponse);
		}

	}
	else
	{
		/* No Matches */
		printf("No matches.\n");
	}

}


/*-----------------------------------------------------------------------------
 *  do_tui_lookups
 */
static void
do_sample_tui_lookups( GnUser& user )
{
	/* Lookup album: Nelly -	Nellyville to demonstrate collaborative artist navigation in track level (track#12)*/
	gnsdk_cstr_t inputTuiId  = "30716057";
	gnsdk_cstr_t inputTuiTag = "BB402408B507485074CC8B3C6D313616";


	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup album: Dido -	Life for Rent */
	inputTuiId  = "3020551";
	inputTuiTag = "CAA37D27FD12337073B54F8E597A11D3";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup album: Jean-Pierre Rampal	- Portrait Of Rampal */
	inputTuiId  = "2971440";
	inputTuiTag = "7F6C280498E077330B1732086C3AAD8F";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup album: Various Artists - Grieg: Piano	Concerto, Peer Gynth Suites	#1 */
	inputTuiId  = "2971440";
	inputTuiTag = "7F6C280498E077330B1732086C3AAD8F";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup album: Stephen Kovacevich	- Brahms: Rhapsodies, Waltzes &	Piano Pieces*/
	inputTuiId  = "2972852";
	inputTuiTag = "EC246BB5B359D88BEBDC1EF55873311E";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup album: Nirvana - Nevermind */
	inputTuiId  = "2897699";
	inputTuiTag = "2FAE8F59CCECBA288810EC27DCD56A0A";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup album: Eminem	- Encore */
	inputTuiId  = "68056434";
	inputTuiTag = "C6E3634DF05EF343E3D22CE3A28A901A";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup Japanese album:
	 * NOTE: In order to correctly see the Japanese metadata results for
	 * this lookup, this program will need to write out to UTF-8
	 */
	inputTuiId  = "16391605";
	inputTuiTag = "F272BD764FDEB344A54F53D0756DC3FD";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);

	/* Lookup Chinese album:
	 * NOTE: In order to correctly see the Chinese metadata results for this
	 * lookup, this program will need to write out to UTF-8
	 */
	inputTuiId  = "3798282";
	inputTuiTag = "6BF6849840A77C987E8D3AF675129F33";
	do_album_tui_lookup(inputTuiId, inputTuiTag, user);
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
main( int argc, char* argv[] )
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
		sampleLog.Enable(kLogPackageAllGNSDK);		/* Enable for all GNSDK packages */

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

		do_sample_tui_lookups( user );
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}
}

