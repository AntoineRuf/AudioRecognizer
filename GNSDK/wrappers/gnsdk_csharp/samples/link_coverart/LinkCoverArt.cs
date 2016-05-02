/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using GracenoteSDK;
namespace Sample
{
    /// <summary>
    /// Name: LinkCoverArt
    /// Description:
    /// Retrieves a coverart image using Link starting with a serialized GDO as source.
    /// Command-line Syntax:
    /// sample clientId clientTag license libPath
    /// </summary>
	public class LinkCoverArt
	{
        static int SUCCESS = 0;
        static int ERROR = 1;
        private static string folderPath = @"../../../../sample_data/";
        private static string dbPath = @"../../../../sample_data/sample_db";
		/// <summary>
        /// Callback delegate called when loading locale
		/// </summary>
 		public class LookupStatusEvents : GnStatusEventsDelegate
		{
		    /// <summary>
            /// Overrriden for  StatusEvent.
            /// </summary>
            /// <param name="status"></param>
            /// <param name="percentComplete"></param>
            /// <param name="bytesTotalSent"></param>
            /// <param name="bytesTotalReceived"></param>
            /// <param name="canceller"></param>
			public override void
			StatusEvent(GnStatus status, uint percentComplete, uint bytesTotalSent, uint bytesTotalReceived, IGnCancellable canceller)
			{
				switch (status)
				{
				case GnStatus.kStatusUnknown:
					Console.Write("Status unknown ");
					break;

				case GnStatus.kStatusBegin:
					Console.Write("Status query begin ");
					break;

				case GnStatus.kStatusConnecting:
					Console.Write("Status  connecting ");
					break;

				case GnStatus.kStatusSending:
					Console.Write("Status sending ");
					break;

				case GnStatus.kStatusReceiving:
					Console.Write("Status receiving ");
					break;

				case GnStatus.kStatusComplete:
					Console.Write("Status complete ");
					break;

				default:
					break;
				}

				Console.WriteLine("\n\t% Complete (" + percentComplete + "),\tTotal Bytes Sent (" + bytesTotalSent + "),\tTotal Bytes Received (" + bytesTotalReceived + ")");
			}

		};



        /// <summary>
        /// EnableStorage:
        /// Enabling a storage module for GNSDK enables the SDK to use it 
        /// for caching of online queries, storing Playlist Collections, and
        /// to access to Local Databases for offline queries.
        /// Using a storage module is optional and the SDK is capable of operating
        /// without those features if you so chose.
        /// </summary>
        private static void EnableStorage()
        {
            // Instantiate SQLite module to use as our database 
            GnStorageSqlite storageSqlite = GnStorageSqlite.Enable();

            // Set folder location for sqlite storage 
            storageSqlite.StorageLocation = ".";
        }

        /// <summary>
        /// EnableLocalLookups:
        /// Enabling a Local Lookup module gives the SDK the ability to perform
        /// certain queries without going online. This can enable an completely
        /// off-line mode for your application, or can act as a performance boost
        /// over going online for some queries.
        /// </summary>
        private static void EnableLocalLookups()
        {
            // Instantiate Local Lookup module to enable local queries
            GnLookupLocal gnLookupLocal = GnLookupLocal.Enable();
            gnLookupLocal.StorageLocation(GnLocalStorageName.kLocalStorageAll, dbPath);
            // Display Local Database version 
            uint ordinal = gnLookupLocal.StorageInfoCount(GnLocalStorageName.kLocalStorageMetadata, GnLocalStorageInfo.kLocalStorageInfoVersion);
            string gdb_version = gnLookupLocal.StorageInfo(GnLocalStorageName.kLocalStorageMetadata, GnLocalStorageInfo.kLocalStorageInfoVersion, ordinal);
            Console.Write("Gracenote Local Database Version : %s\n", gdb_version);
        }



      
        /// <summary>
        ///  GetUser:
        /// Creating a GnUser is required before performing any queries to Gracenote services,
        /// and such APIs in the SDK require a GnUser to be provided. GnUsers can be created 
        /// 'Online' which means they are created by the Gracenote backend and fully vetted. 
        /// Or they can be create 'Local Only' which means they are created locally by the 
        /// SDK but then can only be used locally by the SDK.
        /// If the application cannot go online at time of user-regstration it should
        /// create a 'local only' user. If connectivity is available, an Online user should
        /// be created. An Online user can do both Local and Online queries.
        /// </summary>
        /// <param name="manager"></param>
        /// <param name="clientId"></param>
        /// <param name="clientIdTag"></param>
        /// <param name="applicationVersion"></param>
        /// <param name="lookupMode"></param>
        /// <returns>Returns a stored user if exists, or create new user and store it for use next time.
        /// </returns>
        private static GnUser
        GetUser(GnManager manager, string clientId, string clientIdTag, string applicationVersion, GnLookupMode lookupMode)
        {
            string serializedUser = String.Empty;

           
            GnUserRegisterMode userRegMode = GnUserRegisterMode.kUserRegisterModeOnline;
            if (lookupMode == GnLookupMode.kLookupModeLocal)
                userRegMode = GnUserRegisterMode.kUserRegisterModeLocalOnly;

            // read stored user data from file 
            if (File.Exists("user.txt"))
            {
                using (StreamReader sr = new StreamReader("user.txt"))
                {
                    serializedUser = sr.ReadToEnd();
                }
            }

            if (serializedUser.Length > 0)
            {
                // pass in clientID (optional) to ensure this serialized user is for this clientID 
                GnUser user = new GnUser(serializedUser, clientId);

                if ((userRegMode == GnUserRegisterMode.kUserRegisterModeLocalOnly) || !user.IsLocalOnly())
                    return user;
                // else desired regmode is online, but user is localonly - discard and register new online user */
            }

            
             // Register new user
            serializedUser = manager.UserRegister(userRegMode, clientId, clientIdTag, applicationVersion).c_str();

            // store user data to file 
            using (StreamWriter outfile = new StreamWriter("user.txt"))
            {
                outfile.Write(serializedUser);
                outfile.Close();
            }

            return new GnUser(serializedUser);
        }

        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="user"></param>
        static void
        LoadLocale( GnUser user)
        {
            using (LookupStatusEvents localeEvents = new LookupStatusEvents())
            {
                GnLocale locale = new GnLocale(
                    GnLocaleGroup.kLocaleGroupMusic,     // Locale group 
                    GnLanguage.kLanguageEnglish,         // Language 
                    GnRegion.kRegionDefault,             // Region 
                    GnDescriptor.kDescriptorSimplified,  // Descriptor 
                    user,                                // User 
                    null                                 // locale Events object 
                    );

                locale.SetGroupDefault();
            }
        }

        /// <summary>
        /// Fetching Image
        /// </summary>
        /// <param name="coverArt">size in bytes</param>
        /// <param name="imageTypeStr">name</param>
		private static void
		fetchImage(string coverArt, String imageTypeStr)
		{
			if (coverArt != null)
			{
				Console.WriteLine("\nRETRIEVED: " + imageTypeStr
				                  + " image: "
				                  + coverArt
				                  + " byte JPEG");
			}
			else
			{
				/* Do not return error code for not found. */
				/* For image to be fetched, it must exist in the size specified and you must be entitled to fetch images. */
				Console.WriteLine("\nNOT FOUND: " + imageTypeStr + " image ");
			}
		}

		/*-----------------------------------------------------------------------------
		 *  FetchCoverArt
		 */
		private static void
		FetchCoverArt(GnUser user)
		{
			Console.WriteLine("\n*****Sample Link Album Query*****");

            using (LookupStatusEvents linkStatusEvents = new LookupStatusEvents())
			{
                // The below serialized GDO was an 1-track album result from another GNSDK query. 
				string serializedGdo = "WEcxAbwX1+DYDXSI3nZZ/L9ntBr8EhRjYAYzNEwlFNYCWkbGGLvyitwgmBccgJtgIM/dkcbDgrOqBMIQJZMmvysjCkx10ppXc68ZcgU0SgLelyjfo1Tt7Ix/cn32BvcbeuPkAk0WwwReVdcSLuO8cYxAGcGQrEE+4s2H75HwxFG28r/yb2QX71pR";

				// Typically, the GDO passed in to a Link query will come from the output of a GNSDK query. 
				// For an example of how to perform a query and get a GDO please refer to the documentation 
				// or other sample applications. 
				

				GnMusicId gnMusicID = new GnMusicId(user);
				gnMusicID.Options().LookupData(GnLookupData.kLookupDataContent, true);

				GnResponseAlbums responseAlbums = gnMusicID.FindAlbums(GnDataObject.Deserialize(serializedGdo));
				GnAlbum          gnAlbum        = responseAlbums.Albums.First<GnAlbum>();

				GnLink link = new GnLink(gnAlbum, user, null);
				if (link != null)
				{
					// Cover Art 
    				GnLinkContent coverArt  = link.CoverArt(GnImageSize.kImageSize170, GnImagePreference.smallest);
					byte[]        coverData = coverArt.DataBuffer;

                    // save coverart to a file.
					fetchImage(coverData.Length.ToString(), "cover art");
					if (coverData != null)
						File.WriteAllBytes("cover.jpeg", coverData);
            
                    // Artist Image 
					GnLinkContent imageArtist = link.ArtistImage(GnImageSize.kImageSize170, GnImagePreference.smallest);
                    byte[]        artistData = imageArtist.DataBuffer;
					
                    // save artist image to a file.
					fetchImage(artistData.Length.ToString(), "artist");
					if (artistData != null)
						File.WriteAllBytes("artist.jpeg", artistData);
				}
			}

		}

		
        /// <summary>
        /// MAIN
        /// </summary>
        /// <param name="args"></param>
		static int Main(string[] args)
		{
	        string  licenseFile;
	        string  gnsdkLibraryPath;
	        string  clientId;
	        string  clientIdTag;
	        string  applicationVersion = "1.0.0.0";  // Increment with each version of your app 
	        GnLookupMode  lookupMode;
            int result = ERROR;

            Console.OutputEncoding = Encoding.UTF8;
	        if (args.Length == 5)
	        {
		        clientId         = args[0];
		        clientIdTag      = args[1];
		        licenseFile      = args[2];
		        gnsdkLibraryPath = args[3];

		        if (args[4] == "online")
		        {
			        lookupMode = GnLookupMode.kLookupModeOnline;
		        }
		        else if (args[4] == "local")
		        {
			        lookupMode = GnLookupMode.kLookupModeLocal;
		        }
		        else
		        {
			        Console.Write("Incorrect lookupMode specified.\n");
			        Console.Write("Please choose either \"local\" or \"online\"\n");
			        return ERROR;
		        }
	        }
	        else
	        {
		        Console.Write("\nUsage:  clientId clientIdTag license gnsdkLibraryPath lookupMode\n");
		        return ERROR;
	        }

			try
			{
                // Initialize SDK 
                GnManager manager = new GnManager(gnsdkLibraryPath, licenseFile, GnLicenseInputMode.kLicenseInputModeFilename);

                // Display SDK version 
                Console.WriteLine("\nGNSDK Product Version : " + manager.ProductVersion + " \t(built " + manager.BuildDate + ")");

                // Enable GNSDK logging 
                GnLog sampleLog = new GnLog("sample.log", null);
                GnLogFilters filters = new GnLogFilters();
                sampleLog.Filters(filters.Error().Warning());               // Include only error and warning entries 
                GnLogColumns columns = new GnLogColumns();
                sampleLog.Columns(columns.All());			                // Add all columns to log: timestamps, thread IDs, etc 
                GnLogOptions options = new GnLogOptions();
                sampleLog.Options(options.MaxSize(0).Archive(false));       // Max size of log: 0 means a new log file will be created each run. Archive option will save old log else it will regenerate the log each time 
                sampleLog.Enable(GnLogPackageType.kLogPackageAllGNSDK);


                // Enable Storage module
                EnableStorage();

                if (lookupMode == GnLookupMode.kLookupModeLocal)
                {
                    //Enable local database lookups 
                    EnableLocalLookups();
                }

                // Get GnUser instance to allow us to perform queries 
                GnUser user = GetUser(manager, clientId, clientIdTag, applicationVersion, lookupMode);

                // set user to match our desired lookup mode (all queries done with this user will inherit the lookup mode) 
                user.Options().LookupMode(lookupMode);

				//  Load locale to retrive Gracenote Descriptor/List basesd values e.g, genre, era, origin, mood, tempo 
				LoadLocale(user);

				// Perform a sample query 
				FetchCoverArt(user);

                // Success
                result = SUCCESS;
			}
			// All gracenote sdk objects throws GnException 
			catch (GnException e)
			{
				Console.WriteLine("Error Description    :: " + e.ErrorDescription);
				Console.WriteLine("Error API            :: " + e.ErrorAPI);
				Console.WriteLine("Source Error Code    :: {0:X}", e.SourceErrorCode);
				Console.WriteLine("Source Error Modulee :: " + e.SourceErrorModule);
			}
            return result;
		  }
	}
}

