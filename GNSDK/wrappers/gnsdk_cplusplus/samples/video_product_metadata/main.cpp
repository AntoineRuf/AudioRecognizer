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
 *  This sample shows accessing product metadata: Disc > Side >  Layer >  Feature > Chapters.
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
 *  displayChapters
 */
static void
displayChapters(GnVideoFeature gnVideoFeature)
{
	std::cout << "\t\t\tchapters: " << gnVideoFeature.Chapters().count() << std::endl;

	metadata::chapter_iterator chapterIterator = gnVideoFeature.Chapters().begin();


	for (; chapterIterator != gnVideoFeature.Chapters().end(); ++chapterIterator)
	{
		GnVideoChapter gnVideoChapter = *chapterIterator;

		GnTitle gnChpaterTitle = gnVideoChapter.OfficialTitle();

		std::cout << "\t\t\t\t" << gnVideoChapter.Ordinal() << ": " << gnChpaterTitle.Display();

		int seconds = gnVideoChapter.Duration();
		int minutes = seconds/60;
		int hours   = minutes/60;
		seconds = seconds - (60*minutes);
		minutes = minutes - (60*hours);
		std::cout << " [" << hours << ":" << minutes << ":" << seconds << "]" << std::endl;
	}
}


/*-----------------------------------------------------------------------------
 *  displayLayers
 */
static void
displayLayers(GnVideoSide side)
{
	gnsdk_uint32_t layerCount = side.Layers().count();


	if ( layerCount > 0 )
		std::cout << "\tNumber of layers: " << layerCount << std::endl;
	else
	{
		std::cout << "\tNo layer data\n";
		return;
	}

	metadata::layer_iterator layerIterator = side.Layers().begin();

	for (; layerIterator != side.Layers().end(); ++layerIterator)
	{
		GnVideoLayer gnVideoLayer = *layerIterator;

		gnsdk_int32_t layerNumber = gnVideoLayer.Ordinal();

		bool matched = gnVideoLayer.Matched();
		if (matched)
			matched = "MATCHED";
		else
			matched = "";

		std::cout << "\t\tLayer " << layerNumber << " -------- " << matched << std::endl;

		printf( "\t\tMedia type: %s\n", gnVideoLayer.MediaType());

		std::cout << "\t\tTV system: " << gnVideoLayer.TvSystem() << std::endl;

		std::cout << "\t\tRegion code: " << gnVideoLayer.RegionCode() << std::endl;
		std::cout << "\t\tVideo region: " << gnVideoLayer.VideoRegion() << std::endl;

		if (gnVideoLayer.AspectRatio())
			std::cout << "\t\tAspect ratio: " << gnVideoLayer.AspectRatio();

		if (gnVideoLayer.AspectRatioType())
			std::cout << " [" << gnVideoLayer.AspectRatioType() << "]" << std::endl;


		std::cout << "\t\tFeatures: " << gnVideoLayer.Features().count() << std::endl;

		metadata::feature_iterator featureIterator = gnVideoLayer.Features().begin();
		for (; featureIterator != gnVideoLayer.Features().end(); ++featureIterator)
		{
			GnVideoFeature gnVideoFeature = *featureIterator;

			gnsdk_int32_t featureNumber = gnVideoFeature.Ordinal();

			matched = gnVideoFeature.Matched();
			if (matched)
				matched = "MATCHED";
			else
				matched = "";

			std::cout << "\n\t\t\tFeature " << featureNumber << " -------- " << matched << std::endl;

			GnTitle gnTitle = gnVideoFeature.OfficialTitle();

			std::cout << "\t\t\tFeature title: " << gnTitle.Display() << std::endl;

			int seconds = gnVideoFeature.Duration();
			int minutes = seconds/60;
			int hours   = minutes/60;
			seconds = seconds - (60*minutes);
			minutes = minutes - (60*hours);
			printf("\t\t\tLength: %d:%02d:%02d\n", hours, minutes, seconds);

			std::cout << "\t\t\tAspect ratio: " << gnVideoFeature.AspectRatio();

			std::cout << " [" << gnVideoFeature.AspectRatioType() << "]" << std::endl;

			std::cout << "\t\t\tPrimary genre: " << gnVideoFeature.Genre(kDataLevel_1) << std::endl;

			GnRating gnFeatureRating = gnVideoFeature.Rating();
			printf("\t\t\tRating:%s ", gnFeatureRating.Rating());
			printf("[%s]", gnFeatureRating.RatingType());
			printf(" - %s\n", gnFeatureRating.RatingDesc());

			std::cout << "\t\t\tFeature type: " << gnVideoFeature.VideoFeatureType() << std::endl;

			std::cout << "\t\t\tProduction type: " << gnVideoFeature.VideoProductionType() << std::endl;

			std::cout << "\t\t\tPlot summary: " << gnVideoFeature.PlotSummary() << std::endl;

			std::cout << "\t\t\tPlot synopsis: " << gnVideoFeature.PlotSynopsis() << std::endl;

			std::cout << "\t\t\tTagline: " << gnVideoFeature.PlotTagline() << std::endl;

			displayChapters(gnVideoFeature);
		}
	}
}


/*-----------------------------------------------------------------------------
 *  displayBasicData
 */
static void
displayBasicData(GnVideoProduct& videoProduct)
{
	GnTitle productTitle = videoProduct.OfficialTitle();

	std::cout << "\nTitle: " << productTitle.Display() << std::endl;


	if (videoProduct.VideoProductionType())
		std::cout << "Production Type: " << videoProduct.VideoProductionType() << std::endl;

	if (videoProduct.DateOriginalRelease())
		std::cout << "Orig release: " << videoProduct.DateOriginalRelease() << std::endl;

	GnRating rating = videoProduct.Rating();

	printf( "Rating: %s", rating.Rating());

	printf( "[%s]", rating.RatingType());

	if (rating.RatingDesc())
		printf( "- %s", rating.RatingDesc());

	std::cout << "Release: " << videoProduct.DateRelease() << std::endl;
}


/*-----------------------------------------------------------------------------
 *  displayDiscInformation
 */
static void
displayDiscInformation(GnVideoProduct& product)
{
	std::cout << "Discs: " << product.Discs().count() << std::endl;

	metadata::disc_iterator discItr = product.Discs().begin();


	for (; discItr !=  product.Discs().end(); ++discItr)
	{
		GnVideoDisc disc = *discItr;

		gnsdk_int32_t discNumber = disc.Ordinal();
		bool discMatch = disc.Matched();

		if (discMatch)
			discMatch = "MATCHED";
		else
			discMatch = "";

		std::cout << "disc  " << discNumber << " -------- " << discMatch << std::endl;

		GnTitle discTitle = disc.OfficialTitle();

		std::cout << "\tTitle:\t" << discTitle.Display() << std::endl;

		std::cout << "\tNumber sides:\t" << disc.Sides().count()<< std::endl;

		metadata::side_iterator sideItr = disc.Sides().begin();

		for (; sideItr != disc.Sides().end(); ++sideItr) /*side loop*/
		{
			GnVideoSide side = *sideItr;

			gnsdk_int32_t sideNumber = side.Ordinal();

			bool sideMatch = side.Matched();
			if (sideMatch)
				sideMatch = "MATCHED";
			else
				sideMatch = "";

			std::cout << "\tSide  " << sideNumber<< " -------- " << sideMatch << std::endl;

			displayLayers(side);
		}
	}
}


/*-----------------------------------------------------------------------------
 *  displayMultipleProduct
 */
static void
displayMultipleProduct(GnResponseVideoProduct& videoResponse)
{
	gnsdk_uint32_t count = 0;

	metadata::product_iterator productIterator = videoResponse.Products().begin();


	for (; productIterator != videoResponse.Products().end(); ++productIterator)
	{
		std::cout << "Match : " << ++count;
		GnVideoProduct product = *productIterator;
		displayBasicData(product);
	}
}


/*-----------------------------------------------------------------------------
 *  displaySingleProduct
 */
static void
displaySingleProduct(GnResponseVideoProduct& videoResponse)
{
	metadata::product_iterator productIterator = videoResponse.Products().begin();

	GnVideoProduct product = *productIterator;

	displayBasicData(product);
	displayDiscInformation(product);
}


/*-----------------------------------------------------------------------------
 *  do_Product_Search
 */
static void
do_Product_Search(GnUser& user)
{
	gnsdk_cstr_t searchTitle = "Star";


	try
	{
		std::cout << "\n*****Sample Title Search:"<< searchTitle << "*****\n";

		LookupStatusEvents videoEvents;

		GnVideo myVideoId(user, &videoEvents);

		/* Set result range to return up to the first 20 results */
		myVideoId.Options().ResultRangeStart(1);
		myVideoId.Options().ResultCount(20);

		GnResponseVideoProduct videoResponse = myVideoId.FindProducts( searchTitle, kSearchFieldProductTitle, kSearchTypeDefault );

		std::cout << "\nPossible Matches\t:" << videoResponse.Products().count() << std::endl;

		if ( 1 == videoResponse.Products().count() )
		{
			displaySingleProduct(videoResponse);
		}
		else
		{
			/* We now have 1-n matches needing resolution  */
			displayMultipleProduct(videoResponse);

			/* Typically the user would choose one (or none) of the presented choices.
			 * For this simplified sample, just pick the first choice  */

			displaySingleProduct(videoResponse);

		}

	}
	catch (GnError error)
	{
		std::cout << error.ErrorAPI() << std::endl;
		std::cout << error.ErrorDescription() << std::endl;
		std::cout << error.ErrorCode() << std::endl;
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

		/* Lookup products and display */
		do_Product_Search(user);
	}
	catch (GnError e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

