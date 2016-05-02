/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * Name: MusicID-File LibraryID sample appilcation
 * Description:
 * LibraryID processing adds another level of processing above AlbumID for very large collections of media files.
 * LibraryID extends AlbumID functionality by performing additional scanning and processing of all the files in
 * an entire collection. This enables LibraryID to find groupings that are not captured by AlbumID processing.
 * This method is highly recommended for use when there are a large number (hundreds to thousands) of files to
 * identify, though it is also equally effective when processing only a few files. This method takes most of
 * the guesswork out of MusicID-File and lets the library do all the work for the application.
 * The GnMusicIdFile::DoLibraryID method provides LibraryID processing.
 *
 * Command-line Syntax:
 * sample clientId clientIdTag license [local|online]
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

#include "gnsdk.hpp"
#include "gnsdk_musicidfile.hpp"
#include "gnsdk_storage_sqlite.hpp"
#include "gnsdk_lookup_local.hpp"

using namespace gracenote;
using namespace gracenote::metadata;
using namespace gracenote::musicid_file;
using namespace gracenote::lookup_local;
using namespace gracenote::storage_sqlite;


/* Files used by this application */
static gnsdk_cstr_t s_sample_audio_files[6] =
{
	"../../../../sample_data/01_stone_roses.wav",
	"../../../../sample_data/04_stone_roses.wav",
	"../../../../sample_data/stone roses live.wav",
	"../../../../sample_data/Dock Boggs - Sugar Baby - 01.wav",
	"../../../../sample_data/kardinal_offishall_01_3s.wav",
	"../../../../sample_data/Kardinal Offishall - Quest For Fire - 15 - Go Ahead Den.wav"
};

/*
 * Locale function prototypes
 */
void display_result( GnResponseAlbums response );


/*
 * Callback delegate classes
 */

/* Callback delegate called when performing MusicID-File operation */
class MusicIDFileEvents : public IGnMusicIdFileEvents
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
	MusicIdFileStatusEvent(GnMusicIdFileInfo& fileinfo, GnMusicIdFileCallbackStatus status, gnsdk_uint32_t currentFile, gnsdk_uint32_t totalFiles, IGnCancellable& canceller)
	{
		GNSDK_UNUSED(fileinfo);
		GNSDK_UNUSED(status);
		GNSDK_UNUSED(currentFile);
		GNSDK_UNUSED(totalFiles);
		GNSDK_UNUSED(canceller);
	}

	/*-----------------------------------------------------------------------------
	 *  MusicIdFileAlbumResult
	 */
	void
	MusicIdFileAlbumResult(GnResponseAlbums& album_result, gnsdk_uint32_t current_album, gnsdk_uint32_t total_albums, IGnCancellable& canceller)
	{
		std::cout<<"\n*Album " << current_album << " of " << total_albums << "*\n"<< std::endl;

		display_result(album_result);

		GNSDK_UNUSED(canceller);
	}

	void
	MusicIdFileMatchResult(GnResponseDataMatches& matches_result, gnsdk_uint32_t current_match, gnsdk_uint32_t total_matches, IGnCancellable& canceller)
	{
		std::cout<<"\n*Match " << current_match << " of " << total_matches << "*\n"<< std::endl;

		GNSDK_UNUSED(matches_result);
		GNSDK_UNUSED(canceller);
	}

	void
	MusicIdFileResultNotFound(GnMusicIdFileInfo& fileinfo, gnsdk_uint32_t currentFile, gnsdk_uint32_t totalFiles, IGnCancellable& canceller)
	{
		GNSDK_UNUSED(fileinfo);
		GNSDK_UNUSED(currentFile);
		GNSDK_UNUSED(totalFiles);
		GNSDK_UNUSED(canceller);
	}

	void
	MusicIdFileComplete(GnError& completeError)
	{
		GNSDK_UNUSED(completeError);
	}

	/*-----------------------------------------------------------------------------
	 *  GatherFingerprint
	 */
	virtual void
	GatherFingerprint(GnMusicIdFileInfo& fileInfo, gnsdk_uint32_t currentFile, gnsdk_uint32_t totalFiles, IGnCancellable& canceller)
	{
		char         pcmAudio[2048] = {0};
		gnsdk_bool_t complete       = GNSDK_FALSE;
		gnsdk_cstr_t file;

		GNSDK_UNUSED(currentFile);
		GNSDK_UNUSED(totalFiles);
		GNSDK_UNUSED(canceller);

		try
		{
			file = fileInfo.FileName();

			std::ifstream audioFile (file, std::ios::in | std::ios::binary);
			if ( audioFile.is_open() )
			{
				/* skip the wave header (first 44 bytes). the format of the sample files is known,
				 * but please be aware that many wav file headers are larger then 44 bytes!
				 */
				audioFile.seekg(44);
				if ( audioFile.good() )
				{
					/* initialize the fingerprinter
					 * Note: The sample files are non-standard 11025 Hz 16-bit mono to save on file size
					 */
					fileInfo.FingerprintBegin(11025, 16, 1);

					do
					{
						audioFile.read(pcmAudio, 2048);
						complete = fileInfo.FingerprintWrite(
							(gnsdk_byte_t*)pcmAudio,
							(gnsdk_size_t)audioFile.gcount()
							);

						/* does the fingerprinter have enough audio? */
						if (GNSDK_TRUE == complete)
						{
							break;
						}
					}
					while ( audioFile.good() );

					if (GNSDK_TRUE != complete)
					{
						/* Fingerprinter doesn't have enough data to generate a fingerprint.
							Note that the sample data does include one track that is too short to fingerprint. */
						std::cout << "Warning: input file does contain enough data to generate a fingerprint:\n" << file <<"\n";
						fileInfo.FingerprintEnd();
					}
				}
				else
				{
					std::cout << "\n\nError: Failed to skip wav file header: " << file <<"\n\n";
				}
			}
			else
			{
				std::cout << "\n\nError: Failed to open input file: " << file << "\n\n";
			}
		}
		catch (GnError& e)
		{
			std::cout << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
		}
	}

	/*-----------------------------------------------------------------------------
	 *  GatherMetadata
	 */
	virtual void
	GatherMetadata(GnMusicIdFileInfo& fileInfo, gnsdk_uint32_t currentFile, gnsdk_uint32_t totalFiles, IGnCancellable& canceller)
	{
		GNSDK_UNUSED(currentFile);
		GNSDK_UNUSED(totalFiles);

		/*
		 * A typical use for this callback is to read file tags (ID3, etc) for the basic
		 * metadata of the track.  To keep the sample code simple, we went with .wav files
		 * and hardcoded in metadata for just one of the sample tracks.  (MYAPP_SAMPLE_FILE_5)
		 */

		/* So, if this isn't the correct sample track, return.*/
		gnsdk_cstr_t fileIdent = fileInfo.Identifier();

		if (fileIdent[0] == '5')
		{
			/* we pretend that file 5 has no metadata */
			return;
		}

		fileInfo.AlbumArtist( "kardinal offishall" );
		fileInfo.AlbumTitle ( "quest for fire" );
		fileInfo.TrackTitle ( "intro" );

		GNSDK_UNUSED(canceller);
	}

};


/*
 * Local function declarations
 */

void
set_query_data( GnMusicIdFile& midf, gnsdk_cstr_t fileIdent, gnsdk_cstr_t filePath )
{
	GnMusicIdFileInfo fileinfo;

	fileinfo = midf.FileInfos().Add(fileIdent);

	/* Set data for this file information instance.
	 * This only sets file path but all available data
	 * should be set, such as artist name, track title
	 * and album tile if available, such as via audio
	 * file tags.
	 */
	fileinfo.FileName(filePath);
}


/*-----------------------------------------------------------------------------
 *  do_musicid_file
 */
void
do_musicid_file( GnUser& user )
{
	MusicIDFileEvents midFileEvents;
	GnMusicIdFile     midf(user, &midFileEvents);

	int count = sizeof(s_sample_audio_files) / sizeof(s_sample_audio_files[0]);
	for (int i = 0; i < count; i += 1)
	{
		/* our file identifier is the index of the file in s_sample_audio_files */
		gnsdk_char_t fileIdent[4];
		fileIdent[0] = (gnsdk_char_t)('0' + i);
		fileIdent[1] = 0;

		set_query_data(midf, fileIdent, s_sample_audio_files[i]);
	}

	/* LibraryID always returns single (kQueryReturnSingle) */
	midf.DoLibraryId(kResponseAlbums);

	/* Using local MusicIDFileEvents above ok because we wait in scope to complete */
	midf.WaitForComplete();
}


/*-----------------------------------------------------------------------------
 *  display_result
 */
void
display_result( GnResponseAlbums response )
{
	std::cout<<"\tAlbum count: " << response.Albums().count() << std::endl;

	int                      matchCounter = 0;
	metadata::album_iterator it_album     = response.Albums().begin();

	for (; it_album != response.Albums().end(); ++it_album)
	{
		std::cout << "\tMatch " << ++matchCounter << " - Album Title:\t" << it_album->Title().Display() << std::endl;
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
	MusicIDFileEvents localeEvents;

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
main( int argc, char* argv[] )
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

		do_musicid_file( user );
	}
	catch (GnError& e)
	{
		std::cout << "ERROR: " << e.ErrorAPI() << "\t" << std::hex << e.ErrorCode() << "\t" <<  e.ErrorDescription() << std::endl;
        return 1;
	}

	return 0;
}

