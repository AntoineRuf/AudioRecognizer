/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */
/*
 * Name: video_product_metadata.VideoProductMetadata
 * Description:
 * This sample shows accessing product metadata: Disc > Side >  Layer >  Feature > Chapters.
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

package video_product_metadata;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

import com.gracenote.gnsdk.*;

public class VideoProductMetadata {
	
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

		new VideoProductMetadata().doSample( 
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

			// Lookup products and display
			doProductSearch( gnUser );

		}catch (GnException gnException) {
			System.out.println("GnException \t" + gnException.getMessage());
		} finally {
			System.runFinalization();
			System.gc();
		}
	}
	
	
	//=============================================================================================
	// doProductSearch
	//
	void
	doProductSearch( GnUser user ) {
		
		String searchTitle = "Star";

		try {
			
			System.out.println( "\n*****Sample Title Search:" + searchTitle + "*****" );

			GnVideo myVideoId = new GnVideo( user );

			// Set result range to return up to the first 20 results
			myVideoId.options().resultRangeStart(1);
			myVideoId.options().resultCount(20);

			GnResponseVideoProduct videoResponse = myVideoId.findProducts( searchTitle, GnVideoSearchField.kSearchFieldProductTitle, GnVideoSearchType.kSearchTypeDefault );

			System.out.println( "\nPossible Matches\t:" + videoResponse.products().count() );

			if ( 1 == videoResponse.products().count() ){
				
				displaySingleProduct(videoResponse);
				
			} else {
				
				// We now have 1-n matches needing resolution
				displayMultipleProduct(videoResponse);

				// Typically the user would choose one (or none) of the presented choices.
				// For this simplified sample, just pick the first choice

				displaySingleProduct(videoResponse);

			}

		}
		catch (GnException error)
		{
			System.out.println( error.errorAPI() );
			System.out.println( error.errorDescription() );
			System.out.println( error.errorCode() );
		}
	}	
	
	//=============================================================================================
	// displayChapters
	//
	void
	displayChapters(GnVideoFeature gnVideoFeature) throws GnException {
		
		System.out.println( "\t\t\tchapters: " + gnVideoFeature.chapters().count());

		GnVideoChapterIterator chapterIterator = gnVideoFeature.chapters().getIterator();

		while ( chapterIterator.hasNext() ){
			
			GnVideoChapter gnVideoChapter = chapterIterator.next();

			GnTitle gnChpaterTitle = gnVideoChapter.officialTitle();

			System.out.println( "\t\t\t\t" + gnVideoChapter.ordinal() + ": " + gnChpaterTitle.display());

			long seconds = gnVideoChapter.duration();
			long minutes = seconds/60;
			long hours   = minutes/60;
			seconds = seconds - (60*minutes);
			minutes = minutes - (60*hours);
			System.out.println(  " [" + hours + ":" + minutes + ":" + seconds + "]" );
		}
	}


	//=============================================================================================
	// displayLayers
	//
	void
	displayLayers(GnVideoSide side) throws GnException {
		
		long layerCount = side.layers().count();


		if ( layerCount > 0 ) {
			
			System.out.println( "\tNumber of layers: " + layerCount );
		
		} else {
			
			System.out.println( "\tNo layer data" );
			return;
		}

		GnVideoLayerIterator layerIterator = side.layers().getIterator();

		while ( layerIterator.hasNext() ){
			
			GnVideoLayer gnVideoLayer = layerIterator.next();

			long layerNumber = gnVideoLayer.ordinal();

			boolean matched = gnVideoLayer.matched();
			String matchedStr = "";
			if (matched) {
				matchedStr = "MATCHED";
			}

			System.out.println( "\t\tLayer " + layerNumber + " -------- " + matchedStr );

			System.out.println( "\t\tMedia type: " + gnVideoLayer.mediaType());

			System.out.println( "\t\tTV system: " + gnVideoLayer.tvSystem() );

			System.out.println( "\t\tRegion code: " + gnVideoLayer.regionCode() );
			
			System.out.println( "\t\tVideo region: " + gnVideoLayer.videoRegion() );

			System.out.println( "\t\tAspect ratio: " + gnVideoLayer.aspectRatio() );
			
			System.out.println( " [" + gnVideoLayer.aspectRatioType() + "]" );


			System.out.println( "\t\tFeatures: " + gnVideoLayer.features().count() );

			GnVideoFeatureIterator featureIterator = gnVideoLayer.features().getIterator();
			while ( featureIterator.hasNext() ){
				
				GnVideoFeature gnVideoFeature = featureIterator.next();

				long featureNumber = gnVideoFeature.ordinal();

				matched = gnVideoFeature.matched();
				matchedStr = "";
				if (matched) {
					matchedStr = "MATCHED";
				}

				System.out.println( "\n\t\t\tFeature " + featureNumber + " -------- " + matchedStr );

				GnTitle gnTitle = gnVideoFeature.officialTitle();

				System.out.println( "\t\t\tFeature title: " + gnTitle.display() );

				long seconds = gnVideoFeature.duration();
				long minutes = seconds/60;
				long hours   = minutes/60;
				seconds = seconds - (60*minutes);
				minutes = minutes - (60*hours);
				System.out.println( "\t\t\tLength: " + hours + ":" + minutes + ":" + seconds );

				System.out.println( "\t\t\tAspect ratio: " + gnVideoFeature.aspectRatio() );

				System.out.println( " [" + gnVideoFeature.aspectRatioType() + "]" );

				System.out.println( "\t\t\tPrimary genre: " + gnVideoFeature.genre( GnDataLevel.kDataLevel_1) );

				GnRating gnFeatureRating = gnVideoFeature.rating();
				System.out.print("\t\t\tRating:" + gnFeatureRating.rating());
				System.out.print(" [%s]" + gnFeatureRating.ratingType());
				System.out.println(" - " + gnFeatureRating.ratingDesc());

				System.out.println( "\t\t\tFeature type: " + gnVideoFeature.videoFeatureType() );

				System.out.println( "\t\t\tProduction type: " + gnVideoFeature.videoProductionType() );

				System.out.println( "\t\t\tPlot summary: " + gnVideoFeature.plotSummary() );

				System.out.println( "\t\t\tPlot synopsis: " + gnVideoFeature.plotSynopsis() );

				System.out.println( "\t\t\tTagline: " + gnVideoFeature.plotTagline() );

				displayChapters(gnVideoFeature);
			}
		}
	}


	//=============================================================================================
	// displayBasicData
	//
	void
	displayBasicData( GnVideoProduct videoProduct ) {
		
		GnTitle productTitle = videoProduct.officialTitle();

		System.out.println( "\nTitle: " + productTitle.display() );

		System.out.println( "Production Type: " + videoProduct.videoProductionType() );

		System.out.println( "Orig release: " + videoProduct.dateOriginalRelease() );

		GnRating rating = videoProduct.rating();

		System.out.println( "Rating: " + rating.rating());

		System.out.println( "[" + rating.ratingType() +"]" );

		System.out.println( "- " + rating.ratingDesc());

		System.out.println( "Release: " + videoProduct.dateRelease() );
	}


	//=============================================================================================
	// displayDiscInformation
	//
	void
	displayDiscInformation( GnVideoProduct product ) throws GnException {
		System.out.println( "Discs: " + product.discs().count() );

		GnVideoDiscIterator discItr = product.discs().getIterator();

		while ( discItr.hasNext() ) {
			
			GnVideoDisc disc = discItr.next();

			long discNumber = disc.ordinal();
			boolean discMatch = disc.matched();
			String discMatchStr = "";

			if (discMatch) {
				discMatchStr = "MATCHED";
			} else {
				discMatchStr = "";
			}

			System.out.println( "disc  " + discNumber + " -------- " + discMatchStr );

			GnTitle discTitle = disc.officialTitle();

			System.out.println( "\tTitle:\t" + discTitle.display() );

			System.out.println( "\tNumber sides:\t" + disc.sides().count() );

			GnVideoSideIterator sideItr = disc.sides().getIterator();

			while ( sideItr.hasNext() ) {
				
				GnVideoSide side = sideItr.next();

				long sideNumber = side.ordinal();

				boolean sideMatch = side.matched();
				String sideMatchStr = "";
				if (sideMatch) {
					sideMatchStr = "MATCHED";
				}

				System.out.println( "\tSide  " + sideNumber + " -------- " + sideMatchStr );

				displayLayers(side);
			}
		}
	}


	//=============================================================================================
	// displayMultipleProduct
	//
	void
	displayMultipleProduct( GnResponseVideoProduct  videoResponse ) throws GnException {
		
		GnVideoProductIterator productIterator = videoResponse.products().getIterator();

		int count = 0;
		while ( productIterator.hasNext() ) {
			System.out.println( "Match : " + ++count );
			GnVideoProduct product = productIterator.next();
			displayBasicData(product);
		}
	}


	//=============================================================================================
	// displaySingleProduct
	//
	void
	displaySingleProduct( GnResponseVideoProduct videoResponse ) throws GnException {
		
		GnVideoProductIterator productIterator = videoResponse.products().getIterator();

		GnVideoProduct product = productIterator.next();

		displayBasicData(product);
		displayDiscInformation(product);
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
