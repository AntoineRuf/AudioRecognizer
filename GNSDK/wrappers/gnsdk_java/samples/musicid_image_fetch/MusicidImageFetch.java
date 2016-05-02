/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 * Name: musicid_image_fetch.MusicidImageFetch
 * Description:
 * This example does a text search and finds images based on album or contributor.
 * It also finds an image based on genre.
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
package musicid_image_fetch;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class MusicidImageFetch {
	
	// Simulate a folder of MP3s.
	//
	// file 1: Online - At the time of writing, yields an album match but no cover art or artist images are available.
	//                  Fetches the genre image for the returned album's genre.
	//         Local - Yields no match for the query of "Low Commotion Blues Band" against the sample database.
	//                 Uses the genre tag from the file, "Rock", to perform a genre search and fetches the genre image from that.
	// file 2: Online - Yields an album match for album tag "Supernatural". Fetches the cover art for that album.
	//         Local - Same result.
	// file 3: Online - Yields an album matches for Phillip Glass. Fetches the cover art for the first album returned.
	//         Local - Yields an artist match for the artist tag "Phillip Glass". Fetches the artist image for Phillip Glass.
	static class Mp3
	{
		String albumTitleTag;
		String artistNameTag;
		String genreTag;
		
		Mp3 ( String newAlbumTitleTag, String newArtistNameTag, String newGenreTag ){
			albumTitleTag = newAlbumTitleTag;
			artistNameTag = newArtistNameTag;
			genreTag      = newGenreTag;
		}
	};
	
	static Mp3 mp3Folder[] ={
		new Mp3("Ask Me No Questions", "Low Commotion Blues Band",	"Rock"),
		new Mp3("Supernatural",       	"Santana",                   null),
		new Mp3(null,             		"Phillip Glass",             null)
	};
	
	
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

		new MusicidImageFetch().doSample( 
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
			
			// Get the genre list handle. This will come from our pre-loaded locale.
			// Be sure these params match the ones used in get_locale to avoid loading a different list into memory.
			//
			// NB: If you plan to do many genre searches, it is most efficient to get this handle once during
			// initialization (after setting your locale) and then only release it before shutdown.
			GnList list = new GnList( 
							GnListType.kListTypeGenres, 
							GnLanguage.kLanguageEnglish, 
							GnRegion.kRegionDefault, 
							GnDescriptor.kDescriptorSimplified, 
							gnUser );

			// Simulate iterating a sample of mp3s
			int cnt = 0;
			for ( Mp3 mp3 : mp3Folder ){
				System.out.printf( "\n\n***** Processing File %d *****\n", ++cnt );
				processSampleMp3( mp3, gnUser, list );
			}

		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	
	//=============================================================================================
	// findGenreImage
	//
	boolean
	findGenreImage( GnUser gnUser, String genre, GnList list ) throws GnException
	{
		System.out.println( "Genre String Search" );

		if ( genre == null ){       
			System.out.println( "Must pass a genre" );      
			return false;  
		}

		System.out.printf( "%-15s: %s\n", "genre", genre );
		
		// Find the list element for our input string
		GnListElement listElement = list.elementByString( genre );

		System.out.printf( "List element result: %s (level %d)\n", listElement.displayString(), listElement.level() );

		GnLink link = new GnLink( listElement, gnUser );
		
		return fetchImage(link, GnLinkContentType.kLinkContentGenreArt, "genre image");
	}
	
	
	//=============================================================================================
	// fetchImage
	//
	boolean
	fetchImage( GnLink link, GnLinkContentType contentType, String  imageTypeStr)
	{
		long    			fileSize      = 0;
		GnImagePreference 	imgPreference = GnImagePreference.exact;
		boolean           	notFound      = false;
		GnImageSize       	imageSize     = GnImageSize.kImageSize170;
		GnLinkContent     	linkContent;

		/* Perform the image fetch */
		try
		{
			switch (contentType)
			{
			case kLinkContentCoverArt:
				linkContent = link.coverArt(imageSize, imgPreference);
				break;

			case kLinkContentImageArtist:
				linkContent = link.artistImage(imageSize, imgPreference);
				break;

			case kLinkContentGenreArt:
				linkContent = link.genreArt(imageSize, imgPreference);
				break;

			default:
				return notFound;
			}

			fileSize = linkContent.dataSize();

			/* Do something with the image, e.g. display, save, etc. Here we just print the size. */
			System.out.printf( "\nRETRIEVED: %s: %d byte JPEG\n", imageTypeStr, fileSize );

			notFound = false;
		}
		catch ( GnException e )
		{
			System.out.println ( e.errorAPI() + "\t" + e.errorCode() + "\t" + e.errorDescription() );
			notFound = true;
		}

		return notFound;
	}	


	//=============================================================================================
	// processSampleMp3
	//
	void
	processSampleMp3( Mp3 mp3, GnUser gnUser, GnList list) throws GnException
	{
		boolean gotMatch = false;
		
		// Do a music text query and fetch image from result.
		gotMatch = doSampleTextQuery( gnUser, mp3.albumTitleTag, mp3.artistNameTag );

		// If there were no results from the musicid query for this file, try looking up the genre tag to get the genre image.
		if ( gotMatch == false )
		{
			if ( null != mp3.genreTag )
			{
				gotMatch = findGenreImage( gnUser, mp3.genreTag, list );
			}
		}
		
		// did we succesfully find a relevant image?
		if ( gotMatch == false )
		{
			System.out.printf("Because there was no match result for any of the input tags, you may want to associated the generic music image with this track, music_75x75.jpg, music_170x170.jpg or music_300x300.jpg\n");
		}

	}
	
	
	//=============================================================================================
	// doSampleTextQuery
	//
	boolean
	doSampleTextQuery( GnUser gnUser, String albumTitle, String artistName ) throws GnException{

		System.out.println( "MusicID Text Match Query" );

		if ( (albumTitle == null) && (artistName == null) ) {    
			System.out.println( "Must pass album title or artist name\n" );  
			return false;  
		}
		if ( albumTitle != null ) {   
			System.out.printf( "%-15s: %s\n", "album title", albumTitle );    
		}
		if ( artistName != null )  {   
			System.out.printf( "%-15s: %s\n", "artist name", artistName );    
		}

		GnMusicId mid = new GnMusicId( gnUser );
		
		mid.options().lookupData( GnLookupData.kLookupDataContent, true );
		
		// Perform the query
		GnResponseDataMatches dataResponse = mid.findMatches( albumTitle, null, artistName, null, null );
		
		long count = dataResponse.dataMatches().count();
		System.out.printf( "Number matches = %d\n\n", count );

		if ( count != 0 ){
			
			// Get the first match type, just use the first match for demonstration.
			GnDataMatch dataMatch = dataResponse.dataMatches().at(0).next();
			System.out.printf( "First Match GDO type: %s\n", dataMatch.getType() );
	
			performImageFetch( dataMatch, gnUser );
		}

		return (count != 0);
	}	
	
	
	//=============================================================================================
	// performImageFetch
	//	
	void
	performImageFetch( GnDataMatch dataMatch, GnUser user ) throws GnException
	{
		GnLink link = new GnLink( dataMatch, user );

		// Perform the image fetch
		if (dataMatch.isAlbum())
		{
			// If album type get cover art
			if (fetchImage(link, GnLinkContentType.kLinkContentCoverArt, "cover art") )
			{
				/* if no cover art, try to get the album's artist image */
				if (fetchImage(link, GnLinkContentType.kLinkContentImageArtist, "artist image") )
				{
					/* if no artist image, try to get the album's genre image so we have something to display */
					fetchImage(link, GnLinkContentType.kLinkContentGenreArt, "genre image");
				}
			}
		}
		else if (dataMatch.isContributor())
		{
			// If contributor type get artist image
			if (fetchImage(link, GnLinkContentType.kLinkContentImageArtist, "artist image"))
			{
				// if no artist image, try to get the album's genre image so we have something to display
				fetchImage(link, GnLinkContentType.kLinkContentGenreArt, "genre image");
			}
		}
		else
		{
			System.out.printf("Unknown gdo Type, must be ALBUM or CONTRIBUTOR\n");
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
