/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 *  Name: musicid_lookup_album_fpx
 *  Description:
 *  This example generates an FPX fingerprint and then queries it using MusicID.
 *  This is only supported by online queries.
 *
 *  Command-line Syntax:
 *  sample client_id client_id_tag license
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


/*-----------------------------------------------------------------------------
 *  doMatchSelection
 */
static int
doMatchSelection(GnResponseAlbums& response)
{
	/*
	   This is where any matches that need resolution/disambiguation are iterated
	   and a single selection of the best match is made.

	   For this simplified sample, we'll just echo the matches and select the first match.
	 */
	printf( "%16s %d\n", "Match count:", response.Albums().count());

	metadata::album_iterator it_album = response.Albums().begin();
	for (; it_album != response.Albums().end(); ++it_album )
	{
		printf( "%16s %s\n", "Title:", it_album->Title().Display() );

	}

	return 0;
}

/*-----------------------------------------------------------------------------
 *  performAlbumFPXLookup
 */
void
performAlbumFPXLookup(GnUser& user)
{
	gnsdk_byte_t   pcmAudio[2048];
	gnsdk_bool_t   b_complete = GNSDK_FALSE;
	bool           needs_decision = false;
	gnsdk_uint32_t choice_ordinal = 0;

	printf("\n*****MusicID FPX Query*****\n");

	/* get the file */
	std::fstream sampleAudio("../../../../sample_data/teen_spirit_14s.wav", std::ios_base::in);
	std::streamsize readSize = sampleAudio.readsome((char*)pcmAudio, 44);
	if (readSize == 0)
	{
		printf("\n\nFailed to open input file\n\n");
		return;
	}
    
	// Skip the wave header (first 44 bytes). we know the format of our sample files, but
    // be aware that many wav file headers are larger then 44 bytes!
	if (readSize < 44)
	{
		printf("\n\nInput file incorrect for fingerprint\n\n");
		return;
	}

	LookupStatusEvents statusEvents;
	GnMusicId musicid(user, &statusEvents);

	// initialize the fingerprinter
	musicid.FingerprintBegin(kFingerprintTypeStream3, 44100, 16, 2);
    
	readSize = sampleAudio.readsome((char*)pcmAudio, sizeof(pcmAudio));
	while (readSize > 0)
	{
		/* write audio to the fingerprinter */
		b_complete = musicid.FingerprintWrite(pcmAudio, (gnsdk_size_t)readSize);
		if (b_complete)
		{
			/* The fingerprinter has enough audio */
			break;
		}
        
		readSize = sampleAudio.readsome((char*)pcmAudio, sizeof(pcmAudio));
	}
    
	if (!b_complete)
	{
		/* Our audio ended before fingerprint was complete. */
		/* Call FingerprintEnd to tell the fingerprinter to complete. */
		musicid.FingerprintEnd();
	}
    
	/* query generated fingerprint */
	GnResponseAlbums response =  musicid.FindAlbums(musicid.FingerprintDataGet(), kFingerprintTypeStream3);

	int count =  response.Albums().count();
	if (count == 0)
	{
		printf("\nNo albums found for the input.\n");
	}
	else
	{
		needs_decision = response.NeedsDecision();

		/* See if selection of one of the albums needs to happen */
		if (needs_decision)
		{
			choice_ordinal = doMatchSelection(response);
		}
		else
		{
			/* no need for disambiguation, we'll take the first album */
			choice_ordinal = 0; /* Since iterator starts reading from 0th position in the list*/
		}

		GnAlbum album = *(response.Albums().at(choice_ordinal));

		bool fullResult = album.IsFullResult();

		/* if we only have a partial result, we do a follow-up query to retrieve the full album */
		if (!fullResult)
		{
			/* do followup query to get full object. Setting the partial album as the query input. */
			GnResponseAlbums followup_response = musicid.FindAlbums(album);

			/* now our first album is the desired result with full data */
			album = *(followup_response.Albums().begin());
		}
		printf( "%16s\n", "Final album:");
		printf( "%16s %s\n", "Title:", album.Title().Display() );
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


	if ((argc == 4) || (argc == 5))
	{
		clientId         = argv[1];
		clientIdTag      = argv[2];
		licenseFile      = argv[3];
        lookupMode       = kLookupModeOnline;
	}
	else
	{
		std::cout << "\nUsage:  clientId clientIdTag license\n"<< std::endl;
		return -1;
	}

	/* GNSDK initialization */
	try
	{
		GnManager gnsdk(licenseFile, kLicenseInputModeFilename);

		/* Display GNSDK Version infomation */
		std::cout << std::endl << "GNSDK Product Version : " << gnsdk.ProductVersion() << " \t(built " << gnsdk.BuildDate() << ")" << std::endl;

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

		/* Perform album lookup with new user */
		performAlbumFPXLookup(user);
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

