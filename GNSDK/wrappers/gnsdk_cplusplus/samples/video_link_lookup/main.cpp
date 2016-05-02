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
 *  This sample shows basic extended metadata retrieval using the Link module.
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
#include "gnsdk_link.hpp"

using namespace gracenote;
using namespace gracenote::link;
using namespace gracenote::video;
using namespace gracenote::metadata;


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
 *  do_link_lookup
 */
static void
do_link_lookup(GnUser& user)
{
	/* Set a video TOC for this query handle - A Bug's Life */
	gnsdk_cstr_t toc = "1:15;2:198 15;3:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 \
					   6914 1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 \
					   7630 2564 8910 15;4:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 6914 \
					   1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 7630 2564 \
					   8910 15;5:8962 15;6:11474 15;7:11538 15;";		

	GnVideo video(user);
	video.Options().LookupData(kLookupDataContent, true);

	GnResponseVideoProduct responseVideoProduct = video.FindProducts(toc, kTOCFlagDefault);
	int count =  responseVideoProduct.Products().count();
	if(count == 0)
	{ 
		printf("\nNo albums found for the input.\n");
	}else
	{
		bool	needs_decision = false;
		needs_decision =responseVideoProduct.NeedsDecision();

		/* See if selection of one of the albums needs to happen */
		if(needs_decision)
		{
			/*-------------------
			* Resolve match here
			*/
		}

		GnVideoProduct product = *(responseVideoProduct.Products().begin());		

		bool fullResult = product.IsFullResult();

		/* if we only have a partial result, we do a follow-up query to retrieve the full album */
		if(!fullResult)
		{
			/* do followup query to get full object. Setting the partial album as the query input. */
			GnResponseVideoProduct followup_response = video.FindProducts(product);

			/* now our first album is the desired result with full data */ 
			product = *(followup_response.Products().begin());
		}
		printf("\n\nTitle: %s\n", product.OfficialTitle().Display());

		/*------------------------
		* Get Link cover art
		*/
		GnLink link(product, user, GNSDK_NULL);

		/* Fetch the image */
		GnLinkContent linkContent = link.CoverArt( kImageSize75, smallest );

		printf("\nThumbnail cover art: %lu byte JPEG\n", linkContent.DataSize());
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

		/* Lookup AV Work and display */
		do_link_lookup(user);
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

