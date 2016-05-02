/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * Name: musicid_lookup_matches_text.MusicIDLookupMatchesText 
 * Description:
 * This example finds matches based on input text.
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

package musicid_lookup_matches_text;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class MusicIDLookupMatchesText {

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

		new MusicIDLookupMatchesText().doSample( 
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

			// Perform a sample text query with Album, Track and Artist inputs
			doSampleTextQuery( "Supernatural", "Africa Bamba", "Santana", gnUser );

			// Perform a query with just the album name.
			doSampleTextQuery( "看我72变", null, null, gnUser );

			// Perform a sample text query with only the Artist name as an input.
			doSampleTextQuery( null, null, "Philip Glass", gnUser );
			doSampleTextQuery( null, null, "Bob Marley", gnUser );

			// Perform a sample text query with Track Title and Artist name.
			doSampleTextQuery(null, "Purple Stain", "Red Hot Chili Peppers", gnUser );
			doSampleTextQuery(null, "Eyeless", "Slipknot", gnUser );

		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	
	//=============================================================================================
	// doSampleTextQuery
	//
	void
	doSampleTextQuery( String albumTitle, String trackTitle, String artistName, GnUser gnUser) throws GnException
	{
		System.out.printf("\n*****MusicID Text Match Query*****\n");

		if (albumTitle != null) {	System.out.printf( "%-15s: %s\n", "album title", albumTitle );	}
		if (trackTitle != null) {	System.out.printf( "%-15s: %s\n", "track title", trackTitle );	}
		if (artistName != null) {	System.out.printf( "%-15s: %s\n", "artist name", artistName );	}

		GnMusicId mid = new GnMusicId( gnUser );

		// Perform the query with input text as album title, artist name, track title
		GnResponseDataMatches matchResponse = mid.findMatches( albumTitle, trackTitle, artistName, null, null );

		// See if we need any follow-up queries or disambiguation
		if ( matchResponse.dataMatches().count() == 0 ){
			
			System.out.println("\nNo albums found for the input.\n");
			
		} else {
			
			int choiceIndex;
			
			// we have at least one album, see if disambiguation (match resolution) is necessary.
			if ( matchResponse.needsDecision() ){
				
				choiceIndex = doMatchSelection( matchResponse );
				
			} else {
				
				// no need for disambiguation, we'll take the first album
				choiceIndex = 0;
			}
			
			GnDataMatch match = matchResponse.dataMatches().at(choiceIndex).next();
			
			GnAlbum album = null;

			if ( match.isAlbum() )
			{
				album = match.getAsAlbum();
				
				// See if the match has full data or only partial data.
				if ( !album.isFullResult() )
				{
					// do followup query to get full object. Setting the partial album as the query input.
					GnResponseAlbums albumResponse = mid.findAlbums( album );

					// now our first album is the desired result with full data
					album = albumResponse.albums().at(0).next();
				}		
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
	doMatchSelection( GnResponseDataMatches matchResponse ) throws GnException
	{
		// This is where any matches that need resolution/disambiguation are iterated
		// and a single selection of the best match is made.
		//
		// For this simplified sample, we'll just echo the matches and select the first match.

		System.out.printf( "%16s %d\n", "Match count:", matchResponse.dataMatches().count() );

		GnDataMatchIterator iter = matchResponse.dataMatches().getIterator();
		while ( iter.hasNext() ){
			displayMatch( iter.next() );
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
	// displayMatch
	//
	void
	displayMatch( GnDataMatch dataMatch ) throws GnException{
		if ( dataMatch.isAlbum() )
		{
			// Display Album match
			GnAlbum album = dataMatch.getAsAlbum();
			System.out.printf( "%16s %s\n", "Title:", album.title().display() );		

		}
		else if ( dataMatch.isContributor() )
		{
			// Display Contributor match
			GnContributor contrib = dataMatch.getAsContributor();
			GnName name = contrib.namesOfficial().at(0).next();
			System.out.printf( "%16s %s\n", "Name:", name.display() );
		}
		else
		{
			System.out.printf("\nUnsupported match data type: %s\n", dataMatch.getType());
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
		
}

