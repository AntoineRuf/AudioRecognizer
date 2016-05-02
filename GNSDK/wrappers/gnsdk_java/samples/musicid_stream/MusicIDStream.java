/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 * Name: musicid_stream.MusicIDStream
 * Description:
 *
 * Command line arguments:
 * clientId clientIdTag license gnsdkLibraryPath lookupMode 
 *
 * To build and run using GNSDK makefiles:
 * 1. Customize .../wrappers/gnsdk_java/samples/sample_vars.mk and set:
 *   a. CID=<your Client ID>
 *   b. CTAG=<your Client Tag>
 *   c. LIC=<path to your GNSDK license file>
 *   d. LOCAL=<online or local>
 * 2. Navigate to the sample directory
 * 3. Build "make"
 * 4. Run "make run"
 */

package musicid_stream;

import java.io.File;
import java.io.FileInputStream;
import java.nio.channels.FileChannel;
import java.io.RandomAccessFile;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class MusicIDStream {

	final String CLIENT_APP_VERSION = "1.0.0.0";	// Version of your application

	// Load GNSDK native libraries
	static {
		try {
			System.loadLibrary("gnsdk_java_marshal");
		} catch (UnsatisfiedLinkError unsatisfiedLinkError) {
			System.err.println("Native code library failed to load\n" + unsatisfiedLinkError.getMessage());
			System.exit(1);
		}
	}
	
	
	//=============================================================================================
	//
	// main
	//
	//=============================================================================================
	public static void main(String[] args) {
		
		if (args.length != 5) {
			System.out.println("Usage : clientId clientIdTag license gnsdkLibraryPath lookupMode");
			return;
		}
		
		GnLookupMode lookupMode;
		
		if ( args[4].trim().equals( "online" ) ){
			lookupMode = GnLookupMode.kLookupModeOnline;
		}else if ( args[4].trim().equals( "local" ) ){
			lookupMode = GnLookupMode.kLookupModeLocal;
		}else{
			System.out.println("Incorrect lookup mode specified.\n");
			System.out.println("Please choose either \"local\" or \"online\"\n");
			return;
		}

		new MusicIDStream().doSample(
				args[0].trim(), 	// Client ID
				args[1].trim(), 	// Client ID Tag
				args[2].trim(), 	// License
				args[3].trim(), 	// GNSDK Library Path
				lookupMode );
	}

	//=============================================================================================
	// doSample
	//
	void doSample( String clientId, String clientIdTag, String licensePath, String libPath, GnLookupMode lookupMode ){
		
		try{
			
			// Initialize GNSDK
			// Note: For Android GnManager constructors are different. Consult documentation for more information.
			GnManager gnManager = new GnManager(libPath, licensePath, GnLicenseInputMode.kLicenseInputModeFilename);
			
			// Display GNSDK Version infomation
			System.out.println("\nGNSDK Product Version : " + GnManager.productVersion() + "\t(built " + GnManager.buildDate() + ")");

			// Enable GNSDK logging
			GnLog sampleLog = new GnLog("sample.log", null );
			sampleLog.filters(new GnLogFilters().error().warning());				// Include only error and warning entries
			sampleLog.columns(new GnLogColumns().all());							// Add all columns to log: timestamps, thread IDs, etc
			sampleLog.options(new GnLogOptions().maxSize (new BigInteger("0") ));	// Max size of log: 0 means a new log file will be created each run
			sampleLog.options(new GnLogOptions().archive( false ));					// True = old logs will be renamed and saved. False = new log each time
			// To enable logging package call enable with the package. Enable can be called multiple times to turn on multiple packages
			sampleLog.enable(GnLogPackageType.kLogPackageAll);

			if ( lookupMode == GnLookupMode.kLookupModeLocal )
			{
				// Enable local database lookups
				initializeLocalDatabase();
			}

			// Get User handle to allow us to perform queries
			GnUser gnUser = new GnUser( new UserStore(), clientId, clientIdTag, CLIENT_APP_VERSION );
			
			// set user to match our desired lookup mode (all queries done with this user will inherit the lookup mode)
			gnUser.options().lookupMode( lookupMode );
			
			// Load a 'locale' to return locale-specifc results values. This examples loads an English locale.
			loadLocale( gnUser );

            System.out.println("\n-------Starting MusicID Stream -------");
            doMusicidStream(gnUser);

		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	//=============================================================================================
	// doMusicidStream
	//
	void
	doMusicidStream( GnUser gnUser ) throws GnException {
        AudioSource audioSource = new AudioSource( );
		GnMusicIdStream mids = new GnMusicIdStream( gnUser, GnMusicIdStreamPreset.kPresetRadio, new MusicIDStreamEvents() );

        mids.options().resultSingle(true);
        mids.audioProcessStart(audioSource);
        mids.identifyAlbum();
	}

    //=============================================================================================
	// initializeLocalDatabase
	//
	void
	initializeLocalDatabase() throws GnException {
		
		long 	infoCount;
		String  gdbVersion;

		// Initialize SQLite module to use as our database
		GnStorageSqlite gnStorage = GnStorageSqlite.enable();
		
		// Set folder location of local database
		gnStorage.storageLocation( "../../../../sample_data/sample_db" );

		// Initialize Local Lookup module to enable local queries
		GnLookupLocal gnLookupLocal = GnLookupLocal.enable();
        GnLookupLocalStream gnLookupLocalStream = GnLookupLocalStream.enable();

		// Display local database version
		infoCount = gnLookupLocal.storageInfoCount( GnLocalStorageName.kLocalStorageMetadata, GnLocalStorageInfo.kLocalStorageInfoVersion );
		gdbVersion = gnLookupLocal.storageInfo( GnLocalStorageName.kLocalStorageMetadata, GnLocalStorageInfo.kLocalStorageInfoVersion, infoCount );
		
		System.out.println("Gracenote Local Database Version : " + gdbVersion);
	}

	//=============================================================================================
	// loadLocale
	//	Load a 'locale' to return locale-specific values in the Metadata.
	//	This examples loads an English locale.
	//
	void
	loadLocale( GnUser gnUser ) throws GnException
	{
		GnLocale locale = new GnLocale(
							GnLocaleGroup.kLocaleGroupMusic, 
							GnLanguage.kLanguageEnglish, 
							GnRegion.kRegionDefault, 
							GnDescriptor.kDescriptorDefault, 
							gnUser);
		
		// Setting the 'locale' as default
		// If default not set, no locale-specific results would be available
		locale.setGroupDefault();
		
		// GnSDK will hold onto the locale when set as default
		// so it's ok to allow our reference to go out of scope
	}

	//=============================================================================================
	// displayTrack
	//
	void
	displayTrack( GnTrack track ) throws GnException
    {
        System.out.println( "\t\tMatched track:" );
        System.out.println( "\t\t\tnumber: " + track.trackNumber() );
        System.out.println( "\t\t\ttitle: " + track.title().display() );
        System.out.println( "\t\t\ttrack length (ms): " + track.duration() );
        System.out.println( "\t\t\tmatch position (ms): " + track.matchPosition() );
        System.out.println( "\t\t\tmatch duration (ms): " + track.matchDuration() );
    }

	//=============================================================================================
	// displayResult
	//
	void
	displayResult( GnResponseAlbums response ) throws GnException
	{
		System.out.println( "\tAlbum count: " + response.albums().count() );

		int matchCounter = 0;
		GnAlbumIterator itr = response.albums().getIterator();
        
		while ( itr.hasNext() ) {
			GnAlbum album = itr.next();
			System.out.println( "\tMatch " + ++matchCounter + " - Album Title:\t" + album.title().display() );
            displayTrack( album.trackMatched() );
		}
	}

	//=============================================================================================
	// UserStore
	// Persistent store and recall of serialized user
	//
	class UserStore implements IGnUserStore {
		
		@Override
		public GnString loadSerializedUser( String clientId ) {
			
			try {
				InputStream userFileInputStream = new FileInputStream( "user.txt" );
				
				Scanner scanner = new java.util.Scanner( userFileInputStream ).useDelimiter("\\A");
				GnString serializeUser = new GnString( scanner.hasNext() ? scanner.next() : "" );
				
				userFileInputStream.close();
				
				return serializeUser;
				
			} catch (IOException e) {
				// ignore
			}
			
			return null;
		}
		
		@Override
		public boolean storeSerializedUser( String clientId, String serializedUser ) {
			
			try{
				File userFile = new File( "user.txt" );
				if ( !userFile.exists() )
					userFile.createNewFile();
				PrintWriter out = new PrintWriter( userFile );
				out.print( serializedUser );
				out.close();
			} catch (IOException e) {
				return false;
			}
			
			return true;
		}
	}

    // Callback delegate called when performing MusicID-Stream operation
    class MusicIDStreamEvents implements IGnMusicIdStreamEvents, IGnStatusEvents {
    
        @Override
        public void
        statusEvent( GnStatus status, long percent_complete, long bytes_total_sent, long bytes_total_received, IGnCancellable canceller ) {
        
            System.out.print( "status (" );
        
            switch ( status )
            {
                case kStatusUnknown:
                    System.out.print( "Unknown " );
                    break;
                
                case kStatusBegin:
                    System.out.print( "Begin " );
                    break;
                
                case kStatusConnecting:
                    System.out.print( "Connecting " );
                    break;
                
                case kStatusSending:
                    System.out.print( "Sending " );
                    break;
                
                case kStatusReceiving:
                    System.out.print( "Receiving " );
                    break;
                
                case kStatusDisconnected:
                    System.out.print( "Disconnected " );
                    break;
                
                case kStatusComplete:
                    System.out.print( "Complete " );
                    break;
                
                default:
                    break;
            }
        
            System.out.println( "), % complete (" + percent_complete + "), sent (" + bytes_total_sent + "), received (" + bytes_total_received + ")" );
        }
    
        @Override
        public void
        musicIdStreamProcessingStatusEvent( GnMusicIdStreamProcessingStatus status, IGnCancellable canceller ) {
        
        }
    
        @Override
        public void
        musicIdStreamIdentifyingStatusEvent( GnMusicIdStreamIdentifyingStatus status, IGnCancellable canceller ) {
            
            if (status == GnMusicIdStreamIdentifyingStatus.kStatusIdentifyingEnded)
            {
                System.out.println( "\n identify ended ... aborting");
                canceller.setCancel( true );
            }
        }
    
        @Override
        public void
        musicIdStreamAlbumResult( GnResponseAlbums result, IGnCancellable canceller ) {
            try {
                displayResult(result);
            } catch ( GnException gnException ) {
                System.out.println("GnException \t" + gnException.getMessage());
            }
        }
    
        @Override
        public void
        musicIdStreamIdentifyCompletedWithError( GnError e ) {
            System.out.println( e.errorAPI() + "\t" + e.errorCode() + "\t" + e.errorDescription());
        }
    }
    
    // Provide an audio source implementation. In this sample we read directly from a wav file.
    // More typical streaming examples would get data from a microphone or a tuner.
    class AudioSource implements IGnAudioSource {

        RandomAccessFile wavFile;
        FileChannel wavFileChannel;

        @Override
        public long sourceInit() {
            try {
                wavFile = new RandomAccessFile("../../../../sample_data/teen_spirit_14s.wav", "r");
                wavFile.seek(44);
                wavFileChannel = wavFile.getChannel();
                return 0;
            } catch (IOException e) {
                return -1;
            }
        }
        
        @Override
        public void sourceClose() {
            try {
                wavFileChannel.close();
                wavFile.close();
            } catch (IOException e) {
                // ignore
            }
        }

        @Override
        public long samplesPerSecond() {
            return 44100;
        }

        @Override
        public long sampleSizeInBits() {
            return 16;
        }

        @Override
        public long numberOfChannels() {
            return 2;
        }

        @Override
        public long getData(java.nio.ByteBuffer dataBuffer, long dataSize) {
            int bytesRead = 0;
            try {
                bytesRead = wavFileChannel.read(dataBuffer);
                if (bytesRead == -1) {
                    return 0;
                } else {
                    return bytesRead;
                }
            } catch (IOException e) {
                return 0;
            }
        }
    }
}
