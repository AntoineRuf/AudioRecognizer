/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 * Name: musicid_lookup_album_FPX.MusicIDLookupAlbumFPX
 * Description:
 *  This example generates an FPX fingerprint and then queries it using MusicID.
 *  This is only supported by online queries.
 *
 * Command line arguments:
 * clientId clientIdTag license gnsdkLibraryPath
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

package musicid_lookup_album_fpx;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class MusicIDLookupAlbumFPX {

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
		
		if ((args.length != 4) && (args.length != 5)) {
			System.out.println("Usage : clientId clientIdTag license gnsdkLibraryPath");
			return;
		}

		new MusicIDLookupAlbumFPX().doSample(
				args[0].trim(), 	// Client ID
				args[1].trim(), 	// Client ID Tag
				args[2].trim(), 	// License
                args[3].trim(), 	// GNSDK Library Path
				GnLookupMode.kLookupModeOnline );
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

			// Perform a sample album FPX query
			performAlbumFPXLookup( gnUser );

		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	
	//=============================================================================================
	// performAlbumFPXLookup
	//
	void
	performAlbumFPXLookup( GnUser gnUser ) throws GnException
	{
        boolean complete = false;
        GnMusicId mid = new GnMusicId( gnUser );

        try {

            System.out.println("\n*****MusicID FPX Query*****\n");
        
            //LookupStatusEvents statusEvents;
            //GnMusicId musicid(user, &statusEvents);
            //GnMusicId mid = new GnMusicId( gnUser );

            FileInputStream audioFileInputStream = null;
            DataInputStream audioDataInputStream = null;

            audioFileInputStream = new FileInputStream("../../../../sample_data/teen_spirit_14s.wav");
        
            // skip the wave header (first 44 bytes). the format of the sample files is known,
            // but please be aware that many wav file headers are larger then 44 bytes!
            audioFileInputStream.skip(44);
        
            // initialize the fingerprinter
            mid.fingerprintBegin(GnFingerprintType.kFingerprintTypeGNFPX, 44100, 16, 2);

            audioDataInputStream = new DataInputStream(audioFileInputStream);
        
            byte[] audioBuffer = new byte[2048];
            int readSize = 0;
            do {
            
                // read data, check for -1 to see if we are at end of file
                readSize = audioDataInputStream.read( audioBuffer );
                if ( readSize == -1) {
                    break;
                }
            
                complete = mid.fingerprintWrite( audioBuffer, readSize );
            
                // does the fingerprinter have enough audio?
                if (complete) {
                    break;
                }
            
            }
            while ( (readSize > 0) && (complete == false) );
        
            audioDataInputStream.close();
        
            mid.fingerprintEnd();
        
            if (!complete){
                // Fingerprinter doesn't have enough data to generate a fingerprint.
                // Note that the sample data does include one track that is too short to fingerprint.
                System.out.println("Warning: input file does not contain enough data to generate a fingerprint:\n");
            }

        } catch ( GnException gnException ) {
            System.out.println("GnException \t" + gnException.getMessage());
        } catch ( IOException e ){
            System.out.println( "Execption reading audio file" + e.getMessage() );
        }			

		// Perform the query with FPX as input
		GnResponseAlbums albumResponse = mid.findAlbums( mid.fingerprintDataGet(), GnFingerprintType.kFingerprintTypeGNFPX );
		
		// See if we need any follow-up queries or disambiguation
		if ( albumResponse.albums().count() == 0 ){
			
			System.out.println("\nNo albums found for the input.\n");
			
		} else {
			
			int choiceIndex;
			
			// we have at least one album, see if disambiguation (match resolution) is necessary.
			if ( albumResponse.needsDecision() ){
				
				choiceIndex = doMatchSelection( albumResponse );
				
			} else {
				
				// no need for disambiguation, we'll take the first album
				choiceIndex = 0;
			}
			
			GnAlbum album = albumResponse.albums().at(choiceIndex).next();
			
			// See if the album has full data or only partial data.
			// If we only have a partial result, we do a follow-up query to retrieve the full album
			if ( !album.isFullResult() ){
			
				// do followup query to get full object. Setting the partial album as the query input.
				albumResponse = mid.findAlbums( album );
				album = albumResponse.albums().at(0).next();
			}
			
			// We should now have our final, full album result.
			System.out.printf( "%16s\n", "Final album:");
			displayAlbum( album );
		}
	}	

	//=============================================================================================
	// initializeLocalDatabase
	//
	void
	initializeLocalDatabase() throws GnException
	{
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
	// doMatchSelection
	//
	int
	doMatchSelection( GnResponseAlbums albumResponse ) throws GnException
	{
		// This is where any matches that need resolution/disambiguation are iterated
		// and a single selection of the best match is made.
		//
		// For this simplified sample, we'll just echo the matches and select the first match.
		System.out.printf( "%16s %d\n", "Match count:", albumResponse.albums().count() );
		
		GnAlbumIterator iter = albumResponse.albums().getIterator();
		while ( iter.hasNext() ){
			displayAlbum( iter.next() );
		}

		return 0;
	}
	
	
	//=============================================================================================
	// displayAlbum
	//
	void
	displayAlbum( GnAlbum album ) throws GnException{
		System.out.printf( "%16s %s\n", "Title:", album.title().display() );
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

}
