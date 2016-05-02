/*
 *  Copyright (c) 2014 Gracenote.
 *
 *  This software may not be used in any way or distributed without
 *  permission. All rights reserved.
 *
 *  Some code herein may be covered by US and international patents.
 */

/*
 *   Name: musicid_stream app
 *   Description:
 *   This is a placeholder. Auto C build supports a musicid_stream sample. That requires the C++ build to have one as well.
 *
 *   Command-line Syntax:
 *   sample client_id client_id_tag license [local|online]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "gnsdk.hpp"

using namespace gracenote;
using namespace gracenote::metadata;
using namespace gracenote::musicid_stream;
using namespace gracenote::lookup_localstream;
using namespace gracenote::lookup_local;
using namespace gracenote::storage_sqlite;

/*
 * Locale function prototypes
 */
void display_album( GnResponseAlbums response );
void display_track( GnTrack track );

/*
 * Callback delegate classes
 */

/* Callback delegate called when performing MusicID-Stream operation */
class MusicIDStreamEvents : public IGnMusicIdStreamEvents
{
public:
	virtual void
    StatusEvent(GnStatus status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, IGnCancellable& canceller)
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

	void
    MusicIdStreamProcessingStatusEvent(GnMusicIdStreamProcessingStatus status, IGnCancellable& canceller)
    {
		GNSDK_UNUSED(status);
		GNSDK_UNUSED(canceller);
    }

    void
    MusicIdStreamIdentifyingStatusEvent(GnMusicIdStreamIdentifyingStatus status, IGnCancellable& canceller)
    {
        if (status == kStatusIdentifyingEnded)
        {
            std::cout << std::endl << " identify ended ... aborting" << std::endl;
            canceller.SetCancel(true);
        }
    }
    
    void
    MusicIdStreamAlbumResult(GnResponseAlbums& album_result, IGnCancellable& canceller)
    {
		display_album(album_result);

		GNSDK_UNUSED(canceller);
    }
    
    void
    MusicIdStreamIdentifyCompletedWithError(GnError& e)
    {
		std::cout << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
    }

};

/* Provide an audio source implementation. In this sample we read directly from a wav file.
 * More typical streaming examples would get data from a microphone or a tuner.
 */
class AudioSource : public IGnAudioSource
{
public:

    gnsdk_uint32_t
    SourceInit()
    {
        wav_file.open("../../../../sample_data/teen_spirit_14s.wav", std::ios_base::in | std::ios_base::binary);
        if (wav_file.fail())
        {
            return -1;
        }
        else
        {
            /* Skip the header. We know the format of our wav file. */
            wav_file.seekg(44);
            return 0;
        }
    }
    
    void
    SourceClose()
    {
        wav_file.close();
    }

    gnsdk_uint32_t
    SamplesPerSecond()
    {
        return 44100;
    }
    
    gnsdk_uint32_t
    SampleSizeInBits()
    {
        return 16;
    }
    
    gnsdk_uint32_t
    NumberOfChannels()
    {
        return 2;
    }

    gnsdk_size_t
    GetData(gnsdk_byte_t* dataBuffer, gnsdk_size_t dataSize)
    {
        wav_file.read((gnsdk_char_t*)dataBuffer, dataSize);
        return wav_file.gcount();
    }

private:
    std::ifstream  wav_file;
};

/*-----------------------------------------------------------------------------
 *  do_musicid_stream
 */
void
do_musicid_stream(GnUser& user)
{
	MusicIDStreamEvents midStreamEvents;
    AudioSource         audioSource;
	GnMusicIdStream     mids(user, kPresetRadio, &midStreamEvents);

    mids.Options().ResultSingle(true);
    mids.AudioProcessStart(audioSource);
    mids.IdentifyAlbum();

}

/*-----------------------------------------------------------------------------
 *  display_track
 */
void
display_track( GnTrack track )
{
    std::cout << "\t\tMatched track:" << std::endl;
    std::cout << "\t\t\tnumber: " << track.TrackNumber() << std::endl;
    std::cout << "\t\t\ttitle: " << track.Title().Display() << std::endl;
    std::cout << "\t\t\ttrack length (ms): " << track.Duration() << std::endl;
    std::cout << "\t\t\tmatch position (ms): " << track.MatchPosition() << std::endl;
    std::cout << "\t\t\tmatch duration (ms): " << track.MatchDuration() << std::endl;
}

/*-----------------------------------------------------------------------------
 *  display_album
 */
void
display_album( GnResponseAlbums response )
{
	std::cout<<"\tAlbum count: " << response.Albums().count() << std::endl;
    
	int                      matchCounter = 0;
	metadata::album_iterator it_album     = response.Albums().begin();
    
	for (; it_album != response.Albums().end(); ++it_album)
	{
		std::cout << "\tMatch " << ++matchCounter << " - Album Title:\t" << it_album->Title().Display() << std::endl;
        display_track(it_album->TrackMatched());
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
    GnLookupLocalStream& gnLookupLocalStream = GnLookupLocalStream::Enable();

	/* By default this module will used the location set to the storage module.
     ** If an alternate path is desired, use the following API to set alternate
     ** database locations:
     */
	gnLookupLocal.StorageLocation(kLocalStorageAll, "../../../../sample_data/sample_db");
	gnLookupLocalStream.StorageLocation("../../../../sample_data/sample_db");
    
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

		fileName = clientId;
		fileName += "_user.txt";

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

		fileName = clientId;
		fileName += "_user.txt";

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
	GnLocale locale( kLocaleGroupMusic, kLanguageEnglish, kRegionDefault, kDescriptorSimplified, user);

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
        
		std::cout << "\n-------Starting MusicID Stream -------"<< std::endl;
		do_musicid_stream(user);
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}
