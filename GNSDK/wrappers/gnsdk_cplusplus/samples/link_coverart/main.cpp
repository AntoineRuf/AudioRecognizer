/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: link_coverart
 *  Description:
 *  Retrieves a coverart image using Link starting with a serialized GDO as source.
 *
 *  Command-line Syntax:
 *  sample clientId clientIdTag licenseFile [local|online]
 */

/* Online vs Local queries
 *	Set to 0 to have the sample perform online queries.
 *  Set to 1 to have the sample perform local queries.
 *  For local queries, a Gracenote local database must be present.
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
#include "gnsdk_lookup_local.hpp"

using namespace gracenote;
using namespace gracenote::link;
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
 *  fetchImage
 *  Display file size
 */
static void
fetchImage(GnLink& link, gnsdk_link_content_type_t contentType, const char*  imageTypeStr)
{
	GnImagePreference imgPreference = smallest;
	gnsdk_cstr_t      fileName      = GNSDK_NULL;
	GnImageSize       imageSize     = kImageSize170;
	GnLinkContent     linkContent;

	/* Perform the image fetch */
	try
	{
		/* For image to be fetched, it must exist in the size specified and you must be entitled to fetch images. */
		switch (contentType)
		{
		case gnsdk_link_content_cover_art:
			linkContent = link.CoverArt(imageSize, imgPreference);
			fileName    = "cover.jpg";
			break;

		case gnsdk_link_content_image_artist:
			linkContent = link.ArtistImage(imageSize, imgPreference);
			fileName    = "artist.jpg";
			break;

		default:
			/* unhandled type */
			return;
		}

		/* Do something with the image, e.g. display, save, etc. Here we just print the size. */
		gnsdk_size_t dataSize = linkContent.DataSize();
		printf("\nRETRIEVED: %s: %lu byte JPEG\n", imageTypeStr, dataSize);

		/* get image data */
		const void* imageData = linkContent.ContentData();

		/* Save image to file. */
		{
			std::fstream saveFile(fileName, std::ios_base::out);
			saveFile.write((const char*)imageData, dataSize);
		}
	}
	catch (GnError& e)
	{
		std::cout << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
	}
}


/*-----------------------------------------------------------------------------
 *  queryForAlbumImages
 */
static void
queryForAlbumImages(GnUser& user)
{
	printf("\n*****Sample Link Album Query*****\n");

	/* Typically, the GDO passed in to a Link query will come from the output of a GNSDK query.
	 * For an example of how to perform a query and get a GDO please refer to the documentation
	 * or other sample applications.
	 * The below serialized GDO was an 1-track album result from another GNSDK query.
	 */

	gnsdk_cstr_t serialized_gdo = "WEcxAbwX1+DYDXSI3nZZ/L9ntBr8EhRjYAYzNEwlFNYCWkbGGLvyitwgmBccgJtgIM/dkcbDgrOqBMIQJZMmvysjCkx10ppXc68ZcgU0SgLelyjfo1Tt7Ix/cn32BvcbeuPkAk0WwwReVdcSLuO8cYxAGcGQrEE+4s2H75HwxFG28r/yb2QX71pR";
	GnDataObject gnDataObject = GnDataObject::Deserialize(serialized_gdo);

	/*LinkEvents linkevents;*/

	GnLink link(gnDataObject, user /*, linkevents*/); /* use linkevents object to view progress status*/

	/* Perform the image fetches */
	fetchImage(link, gnsdk_link_content_cover_art, "cover art");
	fetchImage(link, gnsdk_link_content_image_artist, "artist");

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

		//LoadLocale(user);

		/* Perform a sample cover art query */
		queryForAlbumImages(user);
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

