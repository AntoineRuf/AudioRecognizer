/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 * Name: video_contributors_lookup.VideoContributorsLookup
 * Description:
 * This sample shows basic use of the findContributor() API
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

package video_contributors_lookup;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class VideoContributorsLookup {
	
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

		new VideoContributorsLookup().doSample( 
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
				initializeLocalDatabase( gnManager );
			}

			// Get User handle to allow us to perform queries
			GnUser gnUser = new GnUser( new UserStore(), clientId, clientIdTag, CLIENT_APP_VERSION );
			
			// set user to match our desired lookup mode (all queries done with this user will inherit the lookup mode)
			gnUser.options().lookupMode( lookupMode );
			
			// Load a 'locale' to return locale-specifc results values. This examples loads an English locale.
			loadLocale( gnUser );

			// Lookup AV Work and display contributors
			doVideoContributorsLookup( gnUser );

		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	//=============================================================================================
	// doVideoContributorsLookup
	//
	void
	doVideoContributorsLookup( GnUser user ) throws GnException
	{
		String serializedGDO = "WEcxAxpHl1mb/3LWaUoNklp7jGNb+JJ6JjfVejkh2RyiKi05lSEtfOeCNB5yvBRo4liQy9nzqL5HawtU90Sz7GcuetF6p+V0JpiB+lLSKydG5bhN2YYNqLzQdaJOUbIBnhTUdiXmAWuDh9FhGx9fgGKHH1Zjn+V7ff+DwxqK7lpY+EI243+xFw4kuePtsf+SkOKExQ==";

		// Get Work

		GnVideo      myVideoID	= new GnVideo( user );
		GnDataObject dataObj 	= GnDataObject.deserialize( serializedGDO );

		GnResponseVideoWork videoWorksResponse = myVideoID.findWorks(dataObj);

		GnVideoWork work = videoWorksResponse.works().getIterator().next();

		long count =  videoWorksResponse.works().count();
		if (count == 0)
		{
			System.out.println( "\nNo matches." );
		}
		else
		{
			boolean fullResult = work.isFullResult();

			// if we only have a partial result, we do a follow-up query to retrieve the full work
			if (!fullResult)
			{
				// do followup query to get full object. Setting the partial video work as the query input. 
				GnResponseVideoWork followupResponse = myVideoID.findWorks(work);

				// Now our first video is the desired result with full data
				work = followupResponse.works().getIterator().next();

			}
			// Display Title and other Metadata 
			System.out.println("\n\nTitle: " + work.officialTitle().display());

			// Find contributors from this work
			findContributor(work, user);
		}

	}
	
	//=============================================================================================
	// findContributor
	//
	void
	findContributor( GnDataObject pWorkHandle, GnUser user ) throws GnException {
		GnVideo                mVideoID			= new GnVideo( user );
		GnResponseContributors contribResponse 	= mVideoID.findContributors(pWorkHandle);

		// Find all contributors
		System.out.println("\nContributors:");

		GnContributorIterator contribItr = contribResponse.contributors().getIterator();
		int i = 1;
		while ( contribItr.hasNext() ) {
			
			// print the first name.
			System.out.println("\t" + i++ + " : " + contribItr.next().namesOfficial().getIterator().next().display());

		}
	}
	
	
	//=============================================================================================
	// initializeLocalDatabase
	//
	void
	initializeLocalDatabase( GnManager gnManager) throws GnException {
		
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
	loadLocale( GnUser gnUser ) throws GnException {
		
		GnLocale locale = new GnLocale(
							GnLocaleGroup.kLocaleGroupVideo, 
							GnLanguage.kLanguageEnglish, 
							GnRegion.kRegionDefault, 
							GnDescriptor.kDescriptorDefault, 
							gnUser);
		
		// Setting the 'locale' as default
		// If default not set, no locale-specific results would be available
		locale.setGroupDefault();
		
		// GNSDK will hold onto the locale when set as default
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
