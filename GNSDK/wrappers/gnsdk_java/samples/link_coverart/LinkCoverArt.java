/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 * Name: link_coverart.LinkCoverArt
 * Description:
 * Retrieves a coverart image using Link starting with a serialized GnDataObject as source.
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
package link_coverart;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class LinkCoverArt {

	final String CLIENT_APP_VERSION = "1.0.0.0";	// Version of your application
	
	
	List<IGnCancellable> currentQueries = new ArrayList<IGnCancellable>();
	
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

		new LinkCoverArt().doSample( 
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

			queryForAlbumImages( gnUser );
			
		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	//=============================================================================================
	// queryForAlbumImages
	//
	void
	queryForAlbumImages( GnUser user ) throws GnException{
		
		System.out.println( "\n*****Sample Link Album Query*****" );

		// Typically, the GDO passed in to a Link query will come from the output of a GNSDK query.
		// For an example of how to perform a query and get a GDO please refer to the documentation
		// or other sample applications.
		// The below serialized GDO was an 1-track album result from another GNSDK query.

		String serialized_gdo = "WEcxAbwX1+DYDXSI3nZZ/L9ntBr8EhRjYAYzNEwlFNYCWkbGGLvyitwgmBccgJtgIM/dkcbDgrOqBMIQJZMmvysjCkx10ppXc68ZcgU0SgLelyjfo1Tt7Ix/cn32BvcbeuPkAk0WwwReVdcSLuO8cYxAGcGQrEE+4s2H75HwxFG28r/yb2QX71pR";
		GnDataObject gnDataObject = GnDataObject.deserialize(serialized_gdo);
		
		GnLink link = new GnLink( gnDataObject, user ); /* use linkevents object to view progress status*/

		// Perform the image fetches
		fetchImage(link, GnLinkContentType.kLinkContentCoverArt, "cover art");
		fetchImage(link, GnLinkContentType.kLinkContentImageArtist, "artist");
	}

	
	//=============================================================================================
	// fetchImage
	//	Display file size
	//	
	void
	fetchImage( GnLink link, GnLinkContentType contentType, String imageTypeStr )
	{
		GnImagePreference 	imgPreference = GnImagePreference.smallest;
		GnImageSize       	imageSize     = GnImageSize.kImageSize170;
		String      		fileName      = null;
		GnLinkContent     	linkContent	  = null;

		// Perform the image fetch
		try
		{
			// For image to be fetched, it must exist in the size specified and you must be entitled to fetch images.
			switch ( contentType )
			{
			case kLinkContentCoverArt:
				linkContent = link.coverArt( imageSize, imgPreference );
				fileName    = "cover.jpg";
				break;

			case kLinkContentImageArtist:
				linkContent = link.artistImage( imageSize, imgPreference );
				fileName    = "artist.jpg";
				break;
			}

			// Do something with the image, e.g. display, save, etc. Here we just print the size.
			long dataSize = linkContent.dataSize();
			System.out.printf( "\nRETRIEVED: %s: %d byte JPEG\n", imageTypeStr, dataSize );

			// get image data
			byte[] imageData = new byte[(int) dataSize];
			linkContent.dataBuffer(imageData);

			// Save image to file.
			DataOutputStream os = new DataOutputStream( new FileOutputStream(fileName) );
			os.write( imageData );
			os.close();
		}
		catch ( GnException e ) 
		{
			System.out.println( e.errorAPI() + "\t" + e.errorCode() + "\t" +  e.errorDescription() );
		} catch (IOException e) {
			System.out.println( e.getMessage() );
		}
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
		gnStorage.storageLocation( "../../../sample_db" );
		
		
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
