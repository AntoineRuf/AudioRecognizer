/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Description:
 *  This sample shows basic use of the FindWorks() call
 *
 *  Command-line Syntax:
 *  sample clientId clientIdTag licenseFile [local|online]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "gnsdk.hpp"
#include "gnsdk_video.hpp"

using namespace gracenote;
using namespace gracenote::video;
using namespace gracenote::metadata;


/* Callback delegate called when performing queries */
class LookupStatusEvents : public IGnStatusEvents
{
	/*-----------------------------------------------------------------------------
	 *  StatusEvent
	 */
	void
	StatusEvent(gracenote::GnStatus status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, IGnCancellable& canceller)
	{
		std::cout << "status (";

		switch (status)
		{
		case gnsdk_status_unknown:
			std::cout <<"Unknown ";
			break;

		case gnsdk_status_begin:
			std::cout <<"Begin ";
			break;

		case gnsdk_status_connecting:
			std::cout <<"Connecting ";
			break;

		case gnsdk_status_sending:
			std::cout <<"Sending ";
			break;

		case gnsdk_status_receiving:
			std::cout <<"Receiving ";
			break;

		case gnsdk_status_disconnected:
			std::cout <<"Disconnected ";
			break;

		case gnsdk_status_complete:
			std::cout <<"Complete ";
			break;

		default:
			break;
		}

		std::cout << "), % complete (" << percent_complete << "), sent (" << bytes_total_sent << "), received (" << bytes_total_received << ")" << std::endl;

		GNSDK_UNUSED(canceller);
	}

};

/*-----------------------------------------------------------------------------
 *  find_video_work_by_video_work
 */
static void
find_video_work_by_video_work(GnUser& user)
{
	GnVideo videoid(user);

	GnVideoWork queryVideoWork("193405107", "35CEB8C30984910098F37FF7AF68CCA8");
	GnResponseVideoWork videoWorkResponse = videoid.FindWorks(queryVideoWork);

	metadata::works_iterator workIterator = videoWorkResponse.Works().begin();			

	for (int i = 1; workIterator != videoWorkResponse.Works().end(); ++workIterator, ++i)
	{
		GnVideoWork work = *workIterator;
		printf("\t%d: %s\n", i, work.OfficialTitle().Display());

	}
}

/*-----------------------------------------------------------------------------
 *  find_video_work_by_text_search
 */
static void
find_video_work_by_text_search(GnUser& user)
{
	gnsdk_cstr_t search_text = "Harrison Ford";		

	GnVideo videoid(user);

	GnResponseVideoWork videoWorkResponse = videoid.FindWorks(search_text,
		kSearchFieldContributorName,
		kSearchTypeDefault);

	int count =  videoWorkResponse.Works().count();
	if (count == 0)
	{
		printf("\nNo matches. \n");		
	}
	else
	{
		printf("\nAV Works for Harrison Ford:\n");

		metadata::works_iterator workIterator = videoWorkResponse.Works().begin();			

		for (int i = 1; workIterator != videoWorkResponse.Works().end(); ++workIterator, ++i)
		{
			GnVideoWork work = *workIterator;
			/* Work title */
			printf("\t%d: %s\n", i, work.OfficialTitle().Display());

		}
	}
}

/*-----------------------------------------------------------------------------
 *  perform_find_work_query
 */
static void
perform_find_work_query(GnUser& user)
{
	find_video_work_by_video_work(user);
	find_video_work_by_text_search(user);
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
	GnLocale locale( kLocaleGroupVideo, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, user, GNSDK_NULL ); /*use &statusEvents instead of GNSDK_NULL to view progress*/

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

		/* Get GnUser instance to allow us to perform queries */
		UserStore userStore;
		GnUser user = GnUser(userStore, clientId, clientIdTag, applicationVersion);

		/* set user to match our desired lookup mode (all queries done with this user will inherit the lookup mode) */
		user.Options().LookupMode(lookupMode);

		LoadLocale(user);

		/* Lookup AV Works and display */
		perform_find_work_query(user);
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

