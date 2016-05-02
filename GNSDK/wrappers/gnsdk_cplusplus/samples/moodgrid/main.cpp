/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *
 *	Description:
 *	Moodgrid enables querying offline and online providers for mood based playlists.
 *  Moodgrid is a curated flow of adjacent moods that is available in ( multiple) 2 Dimension data grids.
 *  The sample shows using a playlist collection as an offline provider of music for a 5x5 Moodgrid and 10x10 Moodgrid.
 *	Command-line Syntax:
 *	sample clientId clientIdTag licenseFile [local|online]
 */

/* Online vs Local queries
 * Set to 0 to have the sample perform online queries.
 * Set to 1 to have the sample perform local queries.
 * For local queries, a Gracenote local database must be present.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

#include "gnsdk.hpp"
#include "gnsdk_musicid.hpp"
#include "gnsdk_storage_sqlite.hpp"
#include "gnsdk_playlist.hpp"
#include "gnsdk_moodgrid.hpp"
#include "gnsdk_lookup_local.hpp"

using namespace gracenote;
using namespace gracenote::musicid;
using namespace gracenote::metadata;
using namespace gracenote::lookup_local;
using namespace gracenote::storage_sqlite;


/*-----------------------------------------------------------------------------
 *  do_music_recognition
 */
void
do_music_recognition (GnUser& user,   playlist::GnPlaylistCollection& collection )
{
	gnsdk_cstr_t input_query_tocs[] =  {
		"150 13224 54343 71791 91348 103567 116709 132142 141174 157219 175674 197098 238987 257905",
		"182 23637 47507 63692 79615 98742 117937 133712 151660 170112 189281",
		"182 14035 25710 40955 55975 71650 85445 99680 115902 129747 144332 156122 170507",
		"150 10705 19417 30005 40877 50745 62252 72627 84955 99245 109657 119062 131692 141827 152207 164085 173597 187090 204152 219687 229957 261790 276195 289657 303247 322635 339947 356272",
		"150 14112 25007 41402 54705 69572 87335 98945 112902 131902 144055 157985 176900 189260 203342",
		"150 1307 15551 31744 45022 57486 72947 85253 100214 115073 128384 141948 152951 167014",
		"183 69633 96258 149208 174783 213408 317508",
		"150 19831 36808 56383 70533 87138 105157 121415 135112 151619 169903 189073",
		"182 10970 29265 38470 59517 74487 83422 100987 113777 137640 150052 162445 173390 196295 221582",
		"150 52977 87922 128260 167245 187902 215777 248265",
		"183 40758 66708 69893 75408 78598 82983 87633 91608 98690 103233 108950 111640 117633 124343 126883 132298 138783 144708 152358 175233 189408 201408 214758 239808",
		"150 92100 135622 183410 251160 293700 334140",
		"150 17710 33797 65680 86977 116362 150932 166355 183640 193035",
		"150 26235 51960 73111 93906 115911 142086 161361 185586 205986 227820 249300 277275 333000",
		"150 1032 27551 53742 75281 96399 118691 145295 165029 189661 210477 232501 254342 282525",
		"150 26650 52737 74200 95325 117675 144287 163975 188650 209350 231300 253137 281525 337875",
		"150 19335 35855 59943 78183 96553 111115 125647 145635 163062 188810 214233 223010 241800 271197",
		"150 17942 32115 47037 63500 79055 96837 117772 131940 148382 163417 181167 201745",
		"150 17820 29895 41775 52915 69407 93767 105292 137857 161617 171547 182482 204637 239630 250692 282942 299695 311092 319080",
		"182 21995 45882 53607 71945 80495 94445 119270 141845 166445 174432 187295 210395 230270 240057 255770 277745 305382 318020 335795 356120",
		"187 34360 64007 81050 122800 157925 195707 230030 255537 279212 291562 301852 310601",
		"150 72403 124298 165585 226668 260273 291185"
	};


	printf("\nPopulating Collection Summary from sample TOCs \n");
	gnsdk_uint32_t count             = sizeof(input_query_tocs) / sizeof(input_query_tocs[0]);
	
	GnMusicId musicId(user);

	musicId.Options().LookupData(kLookupDataPlaylist, true);

	std::ostringstream outStream;
	for (gnsdk_uint32_t index = 0; index < count; ++index) {
		GnResponseAlbums response = musicId.FindAlbums(input_query_tocs[index]);

		GnAlbum        album  = *(response.Albums().begin());
		gnsdk_uint32_t ntrack = 1;
		for (metadata::track_iterator itr = album.Tracks().begin(); itr != album.Tracks().end(); ++itr, ++ntrack)
		{
			/* create a unique ident for every track that is added to the playlist.
			   Ideally the ident allows for the identification of which track it is.
			   e.g. path/filename.ext , or an id that can be externally looked up.
			 */
			outStream.str("");
			outStream << index << '_' << ntrack ;
				/*
				   Add the the Album and Track GDO for the same ident so that we can
				   query the Playlist Collection with both track and album level attributes.
				 */
			std::string unique_ident = outStream.str();
			collection.Add(unique_ident.c_str(), album);     /* Add the album*/
			collection.Add(unique_ident.c_str(), *itr);      /* Add the track*/
			outStream.clear();
			
		}
	}

	printf("\n Finished Recognition \n");
}


/*-----------------------------------------------------------------------------
 *  do_moodgrid_recommendations
 */
void
do_moodgrid_recommendations(GnUser& user, moodgrid::GnMoodgridProvider& provider,  playlist::GnPlaylistCollection& collection, moodgrid::GnMoodgridPresentationType type)
{

	
	moodgrid::GnMoodgrid myMoodgrid;
	/* get the details for the provider */
	gnsdk_cstr_t mProviderName = provider.Name();
	printf("\n GNSDK_MOODGRID_PROVIDER_NAME :%s \n", mProviderName);

	gnsdk_cstr_t mProviderType = provider.Type();
	printf("\n GNSDK_MOODGRID_PROVIDER_TYPE :%s \n", mProviderType);

	/* create a moodgrid presentation for the specified type */
	moodgrid::GnMoodgridPresentation myPresentation = myMoodgrid.CreatePresentation(user, type, moodgrid::kMoodgridCoordinateTopLeft);

	moodgrid::mooddatapoint_iterator itr = myPresentation.Moods().begin();

	for (; itr != myPresentation.Moods().end(); ++itr) {
		/* find the recommendation for the mood */
		moodgrid::GnMoodgridResult result = myPresentation.FindRecommendations(provider, *itr);
		
		printf("\n\n\tX:%d  Y:%d\tMood Name: %s\tMood ID: %s\tCount: %d\n", itr->X, itr->Y, myPresentation.MoodName(*itr), myPresentation.MoodId(*itr), result.Count());

		moodgrid::moodidentifier_iterator result_itr = result.Identifiers().begin();
		/* iterate the results for the idents */
		for (; result_itr != result.Identifiers().end(); ++result_itr) {
			printf("\n\n\tX:%d  Y:%d", itr->X, itr->Y);

			printf("\nident:\t%s\n", result_itr->MediaIdentifier());
			printf("group:\t%s\n", result_itr->Group());

			playlist::GnPlaylistAttributes data = collection.Attributes(user, result_itr->MediaIdentifier(), result_itr->Group());

			printf("Album:\t%s\n", data.AlbumName());
			printf("Mood :\t%s\n", data.Mood());

		}
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

	/* Set locale with desired Group, Language, Region and Descriptor */
	GnLocale locale( kLocaleGroupPlaylist, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, user);
	
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

		/* initialize Storage for storing Playlist Collections */
		GnStorageSqlite::Enable();
		playlist::GnPlaylistStorage plStorage;

		/* How many collections are stored? */
		int storedCollCount = plStorage.Names().count();
		printf("\nStored Collections Count: %d\n", storedCollCount);

		playlist::GnPlaylistCollection myCollection;
		if (storedCollCount == 0)
		{
			/* Create new collection onlne if not stored any*/
			myCollection = playlist::GnPlaylistCollection("sample_collection");
			do_music_recognition(user, myCollection);
			plStorage.Store(myCollection);
		}
		else
		{
			/* Load existing collection from local store*/
			playlist::storage_iterator storageItr = plStorage.Names().begin();
			myCollection = plStorage.Load(storageItr);
					
		}
		
		moodgrid::GnMoodgrid myMoodgrid;
		moodgrid::moodprovider_iterable providers(myMoodgrid.Providers());
		for (moodgrid::moodprovider_iterator itr = providers.begin(); itr != providers.end() ; ++itr)
		{
			
			/* create, query and print a  5 x  5  moodgrid  */
			do_moodgrid_recommendations(user,*itr,  myCollection, moodgrid::kMoodgridPresentationType5x5);

			/* create, query and print a 10 x 10 moodgrid*/
			do_moodgrid_recommendations(user,*itr, myCollection, moodgrid::kMoodgridPresentationType10x10);
		}
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

