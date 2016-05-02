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
 *  This sample shows basic access of locale-dependent fields
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
 *  display_credit_character
 */
static void
display_credit(GnVideoWork& work)
{
	
	GnVideoCredit credit = *(work.VideoCredits().begin());
	/* Display name */	
	printf("\n\tChatacter Name: %s\n",credit.CharacterName());

	/* Genres */	
	if (credit.Genre(kDataLevel_1)) /* if a genre exists for one level, it exists for all */
	{
		printf("\n\tGenre1: %s\n", credit.Genre(kDataLevel_1));
		printf("\n\tGenre2: %s\n", credit.Genre(kDataLevel_2));
		printf("\n\tGenre3: %s\n", credit.Genre(kDataLevel_3));
	}
}


/*-----------------------------------------------------------------------------
 *  display_work_metadata
 */
static void
display_work_metadata(GnVideoWork& work)
{
	printf("\nTitle: %s\n", work.OfficialTitle().Display());	

	/* Origin info (origins support 4 levels) */
	if (work.Origin(kDataLevel_1)) /* if an origin exists for one level, it exists for all */
	{
		printf("\nOrigin1: %s\n", work.Origin(kDataLevel_1));
		printf("\nOrigin2: %s\n", work.Origin(kDataLevel_2));
		printf("\nOrigin3: %s\n", work.Origin(kDataLevel_3));
		printf("\nOrigin4: %s\n", work.Origin(kDataLevel_4));
	}

	/* Genre info (genre supports 3 levels) */
	if (work.Genre(kDataLevel_1)) /* if a genre exists for one level, it exists for all */
	{
		printf("\nGenre1: %s\n", work.Genre(kDataLevel_1));
		printf("\nGenre2: %s\n", work.Genre(kDataLevel_2));
		printf("\nGenre3: %s\n", work.Genre(kDataLevel_3));
	}

	/*Video mood*/
	if (work.VideoMood())
		printf("\nMood: %s\n", work.VideoMood());


	/*Primary rating*/
	GnRating rating = work.Rating();
	if (rating.Rating())
		printf("\nRating: %s", rating.Rating());
	if (rating.RatingType())
		printf(" [%s]", rating.RatingType());	
	if (rating.RatingDesc())
		printf(" [%s]", rating.RatingDesc());

	if (rating.RatingReason())
		printf(" Reason: %s", rating.RatingReason());
	printf("\n");

	/* Plot synopsis */
	if (work.PlotSynopsis())
		printf("\nPlot synopsis: %s\n", work.PlotSynopsis());
}
/*-----------------------------------------------------------------------------
 *  do_work_search
 */
static void
do_work_search(GnUser& user)
{

	printf("\n*****Sample Video Work Search*****\n");

	gnsdk_cstr_t serialized_gdo = "WEcxA6R75JwbiGUIxLFZHBr4tv+bxvwlIMr0XK62z68zC+/kDDdELzwiHmBPkmOvbB4rYEY/UOOvFwnk6qHiLdb1iFLtVy44LfXNsTH3uNgYfSymsp9uL+hyHfrzUSwoREk1oX/rN44qn/3NFkEYa2FoB73sRxyRkfdnTGZT7MceHHA/28aWZlr3q48NbtCGWPQmTSrK";

	/* Get Work */		
	GnVideo myVideoID(user);
	GnDataObject gnDataObject = GnDataObject::Deserialize(serialized_gdo);

	GnResponseVideoWork videoWorksResponse = myVideoID.FindWorks(gnDataObject);

	GnVideoWork work = *(videoWorksResponse.Works().begin());

	int count =  videoWorksResponse.Works().count();	
	if (count == 0)
	{
		printf("\nNo matches. \n");		
	}
	else 
	{
		printf("\n\nNumber matches: %d\n", count);
		bool fullResult = work.IsFullResult();

		/* if we only have a partial result, we do a follow-up query to retrieve the full work */
		if (!fullResult)
		{
			/* do followup query to get full object. Setting the partial video work as the query input. */
			GnResponseVideoWork followup_response = myVideoID.FindWorks(work);

			/* Now our first video is the desired result with full data */
			work =*(followup_response.Works().begin());

		}
		/* Display Title and other Metadata */		
		display_work_metadata(work);

		/* Display credits */	
		display_credit(work);		
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

		/* Lookup AV Works and display */
		do_work_search(user);
	}
	catch (GnError e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

