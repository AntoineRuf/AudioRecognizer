/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/* 
 * Name: musicid_file_albumid.MusicIDFileAlbumID
 * Description:
 * AlbumID processing provides an advanced method of media file recognition. The context of the media files
 * (their folder location and similarity with other media files) are used to achieve more accurate media recognition.
 * This method is best used for groups of media files where the grouping of the results matters as much as obtaining
 * accurate, individual results. The GnMusicIdFile::doAlbumId method provides AlbumID processing.
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
package musicid_file_albumid;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class MusicIDFileAlbumID
{
	final String CLIENT_APP_VERSION = "1.0.0.0";	// Version of your application
	
	final static String DATA_DIRECTORY = "../../../../sample_data/";
	final static int BUFFER_READ_SIZE = 1024; 
	
	String sampleAudioFiles[] = {
		"01_stone_roses.wav",
		"04_stone_roses.wav",
		"stone roses live.wav",
		"Dock Boggs - Sugar Baby - 01.wav",
		"kardinal_offishall_01_3s.wav",
		"Kardinal Offishall - Quest For Fire - 15 - Go Ahead Den.wav"
	};
	
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
	public static void main(String[] args) throws IOException {
		
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
		
		if ( new File(DATA_DIRECTORY).exists() == false ) {
			System.out.println("Data directory does not exist. " + DATA_DIRECTORY);
			return;
		}

		new MusicIDFileAlbumID().doSample( 
				args[0].trim(), 	// Client ID
				args[1].trim(), 	// Client ID Tag
				args[2].trim(), 	// License
				args[3].trim(), 	// GNSDK Library Path
				lookupMode );  
	}
	
	
	//=============================================================================================
	// doSample
	//
	void doSample( String clientId, String clientIdTag, String licensePath, String libPath, GnLookupMode lookupMode ) {
		
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

			System.out.println( "\n-------AlbumID with 'RETURN_SINGLE' option:-------" );
			doMusicidFile( gnUser, GnMusicIdFileProcessType.kQueryReturnSingle, GnMusicIdFileResponseType.kResponseAlbums);

			System.out.println( "\n-------AlbumID with 'RETURN_ALL' option:-------" );
			doMusicidFile( gnUser, GnMusicIdFileProcessType.kQueryReturnAll, GnMusicIdFileResponseType.kResponseAlbums);

		}catch ( GnException gnException ) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	//=============================================================================================
	// doMusicidFile
	//
	void
	doMusicidFile( GnUser gnUser, GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throws GnException {
		
		GnMusicIdFile midf = new GnMusicIdFile( gnUser, new MusicIDFileEvents() );

		for ( int i = 0 ; i < sampleAudioFiles.length ; i++ )
		{
			// our file identifier is the index of the file in sampleAudioFiles
			String fileIdent = String.format("%d", i);

			setQueryData( midf, fileIdent, DATA_DIRECTORY + sampleAudioFiles[i] );
		}

		// Launch AlbumID
		midf.doAlbumId( processType, responseType );

		// Using local MusicIDFileEvents above ok because we wait in scope to complete
		midf.waitForComplete();
	}
	
	
	//=============================================================================================
	// setQueryData
	//	
	void
	setQueryData( GnMusicIdFile midf, String fileIdent, String filePath ) throws GnException {
		
		GnMusicIdFileInfo fileInfo;

		fileInfo = midf.fileInfos().add( fileIdent );

		// Set data for this file information instance.
		// This only sets file path but all available data
		// should be set, such as artist name, track title
		// and album tile if available, such as via audio
		// file tags.
		fileInfo.fileName( filePath );
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
	loadLocale( GnUser gnUser ) throws GnException {
		
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
	
	
	//=============================================================================================
	// Callback delegate classes
	//
	
	// Callback delegate called when performing MusicID-File operation
	class MusicIDFileEvents implements IGnMusicIdFileEvents {
		
		@Override
		public void
		musicIdFileStatusEvent( GnMusicIdFileInfo fileinfo, GnMusicIdFileCallbackStatus status, long currentFile, long totalFiles, IGnCancellable canceller ) {
			
		}

		@Override
		public void
		musicIdFileAlbumResult( GnResponseAlbums album_result, long current_album, long total_albums, IGnCancellable canceller ) {
			System.out.println( "\n*Album " + current_album + " of " + total_albums + "*\n" );

			try {
				displayResult(album_result);
			} catch ( GnException gnException ) {
				System.out.println("GnException \t" + gnException.getMessage());
			}
		}

		@Override
		public void
		musicIdFileMatchResult( GnResponseDataMatches matches_result, long current_match, long total_matches, IGnCancellable canceller ) {
			System.out.println( "\n*Match " + current_match + " of " + total_matches + "*\n" );
		}

		@Override
		public void
		musicIdFileResultNotFound( GnMusicIdFileInfo fileinfo, long currentFile, long totalFiles, IGnCancellable canceller ) {
			
		}

		@Override
		public void
		musicIdFileComplete( GnError completeError ) {
			
		}

		@Override 
		public void
		gatherFingerprint( GnMusicIdFileInfo fileInfo, long currentFile, long totalFiles, IGnCancellable canceller) {
			
			boolean complete = false;
		
			try {
				
				File audioFile = new File( fileInfo.fileName() );
				
				if (audioFile.exists()) {
					
					FileInputStream audioFileInputStream = null;
					DataInputStream audioDataInputStream = null;
	
					audioFileInputStream = new FileInputStream(audioFile);
					
					// skip the wave header (first 44 bytes). the format of the sample files is known,
					// but please be aware that many wav file headers are larger then 44 bytes!
					audioFileInputStream.skip(44);

					// initialize the fingerprinter
					// Note: The sample files are non-standard 11025 Hz 16-bit mono to save on file size
					fileInfo.fingerprintBegin(11025, 16, 1);
					
					audioDataInputStream = new DataInputStream(audioFileInputStream);

					byte[] audioBuffer = new byte[BUFFER_READ_SIZE];
					int readSize = 0;
					do {

						// read data, check for -1 to see if we are at end of file
						readSize = audioDataInputStream.read( audioBuffer );
						if ( readSize == -1) {
							break;
						}
						
						complete = fileInfo.fingerprintWrite( audioBuffer, readSize );
						
						// does the fingerprinter have enough audio?
						if (complete) {
							break;
						}
						
					}
					while ( (readSize > 0) && (complete == false) );
					
					audioDataInputStream.close();
					
					fileInfo.fingerprintEnd();
					
					if (!complete){
						// Fingerprinter doesn't have enough data to generate a fingerprint.
						// Note that the sample data does include one track that is too short to fingerprint.
						System.out.println("Warning: input file does not contain enough data to generate a fingerprint:\n" + audioFile.getPath());
					}
					
				}
				
			} catch ( GnException gnException ) {
				System.out.println("GnException \t" + gnException.getMessage());
			} catch ( IOException e ){
				System.out.println( "Execption reading audio file" + e.getMessage() );
			}			
		}

		@Override
		public void
		gatherMetadata( GnMusicIdFileInfo fileInfo, long currentFile, long totalFiles, IGnCancellable canceller ) {

			try {
				
				// A typical use for this callback is to read file tags (ID3, etc) for the basic
				// metadata of the track.  To keep the sample code simple, we went with .wav files
				// and hardcoded in metadata for just one of the sample tracks, index 5 from
				// sampleAudioFile. So, if this isn't the correct sample track, return.
				if ( fileInfo.identifier().equals( '5' ) == false ) {
					return;
				}
	
				fileInfo.albumArtist( "kardinal offishall" );
				fileInfo.albumTitle ( "quest for fire" );
				fileInfo.trackTitle ( "intro" );
			
			} catch ( GnException gnException ) {
				System.out.println("GnException \t" + gnException.getMessage());
			}
		}

		@Override
		public void statusEvent(GnStatus status, long percentComplete, long bytesTotalSent, long bytesTotalReceived, IGnCancellable canceller) {
			// override to receive status events for queries to Gracenote service
		}

	};	
}
