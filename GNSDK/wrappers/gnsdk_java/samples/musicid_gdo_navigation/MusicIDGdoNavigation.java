/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 * Name: musicid_gdo_navigation.MusicIDGdoNavigation
 * Description:
 * This application uses MusicID to look up Album response data object content,	including
 * Album	artist,	credits, title,	year, and genre.
 * It demonstrates how to navigate the album response that returns basic track information,
 * including artist, credits, title, track	number,	and	genre.
 * Notes:
 * For clarity and simplicity error handling in not shown here.
 * Refer "logging"	sample to learn	about GNSDK	error handling.
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
package musicid_gdo_navigation;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class MusicIDGdoNavigation {

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

		new MusicIDGdoNavigation().doSample( 
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

			doSampleTuiLookups( gnUser);

		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	
	//=============================================================================================
	// doSampleTuiLookups
	//
	void
	doSampleTuiLookups( GnUser gnUser ) throws GnException{
		
		// Lookup album: Nelly -	Nellyville to demonstrate collaborative artist navigation in track level (track#12)
		String inputTuiId  = "30716057";
		String inputTuiTag = "BB402408B507485074CC8B3C6D313616";
		doAlbumTuiLookup( inputTuiId, inputTuiTag, gnUser );

		// Lookup album: Dido -	Life for Rent
		inputTuiId  = "3020551";
		inputTuiTag = "CAA37D27FD12337073B54F8E597A11D3";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );

		// Lookup album: Jean-Pierre Rampal	- Portrait Of Rampal
		inputTuiId  = "2971440";
		inputTuiTag = "7F6C280498E077330B1732086C3AAD8F";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );

		// Lookup album: Various Artists - Grieg: Piano	Concerto, Peer Gynth Suites	#1
		inputTuiId  = "2971440";
		inputTuiTag = "7F6C280498E077330B1732086C3AAD8F";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );

		// Lookup album: Stephen Kovacevich	- Brahms: Rhapsodies, Waltzes &	Piano Pieces
		inputTuiId  = "2972852";
		inputTuiTag = "EC246BB5B359D88BEBDC1EF55873311E";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );

		// Lookup album: Nirvana - Nevermind
		inputTuiId  = "2897699";
		inputTuiTag = "2FAE8F59CCECBA288810EC27DCD56A0A";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );

		// Lookup album: Eminem	- Encore
		inputTuiId  = "68056434";
		inputTuiTag = "C6E3634DF05EF343E3D22CE3A28A901A";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );

		// Lookup Japanese album:
		// NOTE: In order to correctly see the Japanese metadata results for
		// this lookup, this program will need to write out to UTF-8
		inputTuiId  = "16391605";
		inputTuiTag = "F272BD764FDEB344A54F53D0756DC3FD";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );

		// Lookup Chinese album:
		// NOTE: In order to correctly see the Chinese metadata results for this
		// lookup, this program will need to write out to UTF-8
		inputTuiId  = "3798282";
		inputTuiTag = "6BF6849840A77C987E8D3AF675129F33";
		doAlbumTuiLookup(inputTuiId, inputTuiTag, gnUser );
	}
	
	
	//=============================================================================================
	// doAlbumTuiLookup
	//	
	void
	doAlbumTuiLookup( String inputTuiId, String inputTuiTag, GnUser gnUser ) throws GnException
	{
		System.out.printf("\n*****Sample MusicID Query*****\n");

		GnAlbum album = new GnAlbum( inputTuiId, inputTuiTag );

		GnMusicId mid = new GnMusicId( gnUser );
		GnResponseAlbums albumResponse = mid.findAlbums( album );
		
		
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
			
			album = albumResponse.albums().at(choiceIndex).next();
			
			// See if the album has full data or only partial data.
			// If we only have a partial result, we do a follow-up query to retrieve the full album
			if ( !album.isFullResult() ){
			
				// do followup query to get full object. Setting the partial album as the query input.
				albumResponse = mid.findAlbums( album );
			}
			
			// We should now have our final, full album result.
			System.out.printf( "%16s\n", "Final album:");
			navigateAlbumResponse( albumResponse );
		}	
		
	}
	
	
	//=============================================================================================
	// navigateAlbumResponse
	//	
	void
	navigateAlbumResponse( GnResponseAlbums albumResponse ) throws GnException
	{
		int 	tabIndex = 1;

		System.out.println( "\n***Navigating	Result GDO***" );

		System.out.println( "Album:" );

		// Get the album from the match	response
		long albCount =  albumResponse.albums().count();
		if (albCount == 0){
			return;
		}

		GnAlbum album = albumResponse.albums().at(0).next();

		displayValue("Package Language", album.language(), tabIndex );

		// Navigate	the	credit artist from the album
		navigateCredit( album.artist(), tabIndex );

		// Navigate	Title Official from album
		navigateTitleOfficial(album.title(), tabIndex);

		// Display album attributes
		displayValue("Year", album.year(), tabIndex );

		// Display genre levels form album
		displayValue("Genre Level 1", album.genre(GnDataLevel.kDataLevel_1), tabIndex );
		displayValue("Genre Level 2", album.genre(GnDataLevel.kDataLevel_2), tabIndex );
		displayValue("Genre Level 3", album.genre(GnDataLevel.kDataLevel_3), tabIndex );

		displayValue("Album Label", album.label(), tabIndex );

		displayValue("Album Label", album.label(), tabIndex );

		displayValue("Total in Set", String.format("%d", album.totalInSet()), tabIndex );

		displayValue("Disc in Set", String.format("%d", album.discInSet()), tabIndex );

		System.out.printf( "\tTrack Count: %d\n", album.tracks().count() );

		GnTrackIterator iter = album.tracks().getIterator();
		while ( iter.hasNext() ){
			navigateTrack( iter.next(), tabIndex );
		}

	}	
	
	
	//=============================================================================================
	// displayValue
	//
	void
	displayValue( String tag, String value, int tabIndex)
	{
		String tabString = createTabString( tabIndex );

		if ( value != null )
		{
			System.out.printf( "%s%s: %s\n", tabString, tag, value );
		}

	}


	//=============================================================================================
	// navigateNameOfficial
	//
	void
	navigateNameOfficial(GnName nameOfficial, int tabIndex) throws GnException
	{
		String tabString = createTabString( tabIndex );
		tabIndex++;

		System.out.printf( "%sName Official:\n", tabString );
		displayValue("Display", nameOfficial.display(), tabIndex);

	}


	//=============================================================================================
	// navigateTitleOfficial
	//
	void
	navigateTitleOfficial(GnTitle titleOfficial, int tabIndex) throws GnException
	{
		String tabString = createTabString( tabIndex );
		tabIndex++;

		System.out.printf( "%sTitle Official:\n", tabString );
		displayValue("Display", titleOfficial.display(), tabIndex);

	}


	//=============================================================================================
	// navigateContributor
	//
	void
	navigateContributor( GnContributor contributor, int tabIndex ) throws GnException
	{
		String tabString = createTabString( tabIndex );
		tabIndex++;

		// Navigate	Contributor	Object
		System.out.printf("%sContributor:\n", tabString);

		GnNameIterator iter = contributor.namesOfficial().getIterator();
		while( iter.hasNext() ){
			navigateNameOfficial( iter.next(), tabIndex );
		}

		// Display origin levels from the contributor
		displayValue("Origin Level 1", contributor.origin(GnDataLevel.kDataLevel_1), tabIndex );
		displayValue("Origin Level 2", contributor.origin(GnDataLevel.kDataLevel_2), tabIndex );
		displayValue("Origin Level 3", contributor.origin(GnDataLevel.kDataLevel_3), tabIndex );
		displayValue("Origin Level 4", contributor.origin(GnDataLevel.kDataLevel_4), tabIndex );

		// Display Era levels from the contributor
		displayValue("Era Level 1", contributor.era(GnDataLevel.kDataLevel_1), tabIndex );
		displayValue("Era Level 2", contributor.era(GnDataLevel.kDataLevel_2), tabIndex );
		displayValue("Era Level 3", contributor.era(GnDataLevel.kDataLevel_3), tabIndex );

		// Display Artist type levels from the contributor
		displayValue("Artist Type	Level 1", contributor.artistType(GnDataLevel.kDataLevel_1), tabIndex );
		displayValue("Artist Type	Level 2", contributor.artistType(GnDataLevel.kDataLevel_2), tabIndex );
	}


	//=============================================================================================
	// navigateCredit
	//
	void
	navigateCredit( GnArtist gnArtist, int tabIndex ) throws GnException
	{
		String tabString = createTabString( tabIndex );
		tabIndex += 1;

		System.out.printf( "%sCredit:\n", tabString );

		navigateContributor( gnArtist.contributor(), tabIndex );
	}


	//=============================================================================================
	// navigateTrack
	//
	void
	navigateTrack( GnTrack track, int tabIndex ) throws GnException
	{
		String tabString = createTabString( tabIndex );

		tabIndex++;

		System.out.printf( "%sTrack:\n", tabString );

		displayValue("Track TUI", track.tui(), tabIndex );

		displayValue("Track Number", track.trackNumber(), tabIndex );

		// Navigate	credit from track artist
		navigateCredit(track.artist(), tabIndex);

		// Navigate	Title Official from track
		navigateTitleOfficial(track.title(), tabIndex);


		displayValue("Year", track.year(), tabIndex );

		// Gnere levels from track
		displayValue("Genre Level 1", track.genre(GnDataLevel.kDataLevel_1), tabIndex );
		displayValue("Genre Level 2", track.genre(GnDataLevel.kDataLevel_2), tabIndex );
		displayValue("Genre Level 3", track.genre(GnDataLevel.kDataLevel_3), tabIndex );
	}	
	
	
	//=============================================================================================
	// createTabString
	//	
	String
	createTabString( int tabIndex )
	{
		StringBuilder strBuilder = new StringBuilder();

		for ( ; tabIndex>0; tabIndex--)
		{
			strBuilder.append( '\t' );
		}

		return strBuilder.toString();
	}	
	
	
	//=============================================================================================
	// initializeLocalDatabase
	//
	void
	initializeLocalDatabase() throws GnException{
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
	loadLocale( GnUser gnUser ) throws GnException{
		
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
	doMatchSelection( GnResponseAlbums albumResponse ) throws GnException{
		
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
