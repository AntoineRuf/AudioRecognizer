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
 *  This sample shows basic video explore functionality.
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
 *  find_work_for_contributor
 */
static void
find_work_for_contributor(GnDataObject& pContribHandle, GnUser& user)
{
	GnVideo mVideoID(user);
 
	GnResponseVideoWork relatedWorksResponse = mVideoID.FindWorks(pContribHandle);

	int workCount = relatedWorksResponse.Works().count();
	printf("\nNumber works: %d\n", workCount);	

	metadata::works_iterator relatedworkIter = relatedWorksResponse.Works().begin();
	for (int work_index = 1; relatedworkIter != relatedWorksResponse.Works().end(); ++relatedworkIter, ++work_index)
	{
		GnVideoWork work = *relatedworkIter;
		printf("\t%d : %s\n", work_index,work .OfficialTitle().Display());
		
	}
}

/*-----------------------------------------------------------------------------
 *  display_video_work
 */
static void 
display_video_work(GnUser& user, GnVideoWork& work)
{
	/* Explore contributors : Who are the cast and crew? */
	printf("\nVideo Work - Crouching Tiger, Hidden Dragon: \n\nActor Credits:\n");

	/* How many credits for this work */
	int credit_count = work.VideoCredits().count();
	GNSDK_UNUSED(credit_count);

	metadata::video_credit_iterator credIter = work.VideoCredits().begin();

	GnContributor tempContribObj;

	/* Iterate all actor credits */
	for (; credIter != work.VideoCredits().end(); ++credIter)
	{
		GnVideoCredit cred = *credIter;				

		/* compare the Roleid if it is equal to Actor's Role ID */
		static int credit_index = 0;
		if (cred.RoleId() == 15942)
		{
			++credit_index;

			GnContributor contrib =  cred.Contributor();

			/* Keep first actor credit around to get its filmography */
			if (1 == credit_index)
			{
				tempContribObj = contrib;

			}
			metadata::name_iterator nameItr = contrib.NamesOfficial().begin();
			for (; nameItr != contrib.NamesOfficial().end(); ++nameItr)
			{
				GnName _nameItr = *nameItr;						
				printf("\t%d : %s\n", credit_index, _nameItr.Display());
			}
		}
	}

	/*---------------------------------------------------------------
	* Explore filmography : What other films did this actor play in ?
	*/
	metadata::name_iterator nameItr = tempContribObj.NamesOfficial().begin();
	for (; nameItr != tempContribObj.NamesOfficial().end(); ++nameItr)
	{
		GnName _nameItr = *nameItr;				
		printf( "\nActor Credit: %s Filmography\n", _nameItr.Display());
	}

	GnDataObject firstContribGDO(tempContribObj.native());

	/* find work for contributor */
	find_work_for_contributor(firstContribGDO, user);
}

/*-----------------------------------------------------------------------------
 *  do_video_work_lookup
 */
static void
do_video_work_lookup(GnUser& user)
{
	gnsdk_cstr_t serialized_gdo = "WEcxA6R75JwbiGUIxLFZHBr4tv+bxvwlIMr0XK62z68zC+/kDDdELzwiHmBPkmOvbB4rYEY/UOOvFwnk6qHiLdb1iFLtVy44LfXNsTH3uNgYfSymsp9uL+hyHfrzUSwoREk1oX/rN44qn/3NFkEYa2FoB73sRxyRkfdnTGZT7MceHHA/28aWZlr3q48NbtCGWPQmTSrK";
	GnDataObject gnDataObject = GnDataObject::Deserialize(serialized_gdo);

	GnVideo myVideoID(user);

	GnResponseVideoWork videoWorksResponse = myVideoID.FindWorks(gnDataObject);

	int wCount = videoWorksResponse.Works().count();

	if (wCount == 0)
	{
		printf("\nNo Matches.\n");
	}
	else
	{
		bool needs_decision = videoWorksResponse.NeedsDecision();

		/* See if selection of one of the albums needs to happen */
		if (needs_decision)
		{
			/*---------------------
			* Resolve match here
			*/
		}
	}		
	/* Get first work */
	GnVideoWork work = *(videoWorksResponse.Works().begin());

	/* Display metadata to console */
	display_video_work(user,work);		
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

		/* Lookup AV Works and display */
		do_video_work_lookup(user);
	}
	catch (GnError e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

