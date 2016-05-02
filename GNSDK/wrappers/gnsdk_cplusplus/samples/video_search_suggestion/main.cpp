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
 *  This sample performs a VideoID query for search suggestion text.
 *
 *  Command-line Syntax:
 *  sample client_id client_id_tag license [local|online]
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
 *  do_suggestion_search
 */
static void
do_suggestion_search(GnUser& user)
{
	gnsdk_cstr_t   suggestionTitle = GNSDK_NULL;
	gnsdk_cstr_t   searchText      = "spider";


	try
	{
		GnVideo myVideoID(user);

		GnResponseVideoSuggestions responseVideoSuggestions = myVideoID.FindSuggestions( searchText, kSearchFieldProductTitle, kSearchTypeAnchored );

		gnsdk_uint32_t   rangeStart  = responseVideoSuggestions.RangeStart();
		gnsdk_uint32_t   rangeEnd    = responseVideoSuggestions.RangeEnd();
		gnsdk_uint32_t   rangeCount  = responseVideoSuggestions.RangeTotal();
		gnsdk_uint32_t   resultCount = responseVideoSuggestions.RangeEnd();

		if (resultCount > 0)
		{
			std::cout << std::endl << rangeStart << " - " << rangeEnd << " of " << rangeCount << " suggestions for \'" << searchText << "\' " << std::endl;
		}

		for (gnsdk_uint32_t i = 1; i <= resultCount; i++)
		{
			suggestionTitle = responseVideoSuggestions.SuggestionTitle(i);
			std::cout << "\t" << i << " : " << suggestionTitle << std::endl;
		}
	}
	catch (GnError& e)
	{
		std::cout << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
	}
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
	GnLocale locale( kLocaleGroupVideo, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, user, &localeEvents );

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

		/* Do suggestion search */
		do_suggestion_search(user);
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

