/*
 *  Copyright (c) 2000-2013 Gracenote.
 *
 *  This software may not be used in any way or distributed without
 *  permission. All rights reserved.
 *
 *  Some code herein may be covered by US and international patents.
 */

/*
 *  Name: MusicIDLookupAlbumTOC
 *  Description:
 *  This example looks up an Album based on its TOC.
 *
 *  Command-line Syntax:
 *  sample clientId clientTag license gnsdkLibraryPath
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.IO;
using System.Runtime.InteropServices;
using GracenoteSDK;
namespace Sample
{
	public class MusicIDLookupAlbumTOC
	{

        static int SUCCESS = 0;
        static int ERROR = 1;
        private static string dbPath = @"../../../../sample_data/sample_db";
        /// <summary>
        /// Callback delegate called when loading locale
        /// </summary>
		public class LookupStatusEvents : GnStatusEventsDelegate
		{
			/*-----------------------------------------------------------------------------
			 *  StatusEvent
			 */
			public override void
			StatusEvent(GnStatus status, uint percentComplete, uint bytesTotalSent, uint bytesTotalReceived, IGnCancellable canceller)
			{
		        Console.Write("status (");

		        switch (status)
		        {
		        case GnStatus.kStatusUnknown:
			        Console.Write("Unknown");
			        break;

		        case GnStatus.kStatusBegin:
			        Console.Write("Begin");
			        break;

		        case GnStatus.kStatusConnecting:
			        Console.Write("Connecting");
			        break;

		        case GnStatus.kStatusSending:
			        Console.Write("Sending");
			        break;

		        case GnStatus.kStatusReceiving:
			        Console.Write("Receiving");
			        break;

		        case GnStatus.kStatusDisconnected:
			        Console.Write("Disconnected");
			        break;

		        case GnStatus.kStatusComplete:
			        Console.Write("Complete");
			        break;

		        default:
			        break;
		        }

                Console.Write("), complete ({0:D}%), sent ({1:D}), received ({2:D})\n", percentComplete, bytesTotalSent, bytesTotalReceived);
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
        /// GetUser:
        /// Return a stored user if exists, or create new user and store it for use next time.
        /// </summary>
        /// <param name="manager"></param>
        /// <param name="clientId"></param>
        /// <param name="clientIdTag"></param>
        /// <param name="applicationVersion"></param>
        /// <param name="lookupMode"></param>
        /// <returns></returns>
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
                // else desired regmode is online, but user is localonly - discard and register new online user
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
        ///  LoadLocale:
        /// </summary>
        /// <param name="user"></param>
        static void
        LoadLocale(GnUser user)
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
        /// DisplayForResolve
        /// </summary>
        /// <param name="response"></param>
        /// <returns></returns>
		private static uint
		DisplayForResolve(GnResponseAlbums response)
		{
			uint albumCount = 0;

			albumCount = response.Albums.count();

			Console.WriteLine("    Match count: " + albumCount);

			GnAlbumEnumerable albumEnumerable = response.Albums;
			GnAlbumEnumerator albumEnumerator = albumEnumerable.GetEnumerator();

			while (albumEnumerator.hasNext())
			{
				GnAlbum album = albumEnumerator.Current;
				/* Album Title */
				Console.WriteLine("          Title: " + album.Title.Display);
			}
			return 0;
		}

		
        /// <summary>
        ///   MusicIDAlbumLookup
        /// </summary>
        /// <param name="user"></param>
		private static void	MusicIDAlbumLookup(GnUser user)
		{
			string toc = "150 14112 25007 41402 54705 69572 87335 98945 112902 131902 144055 157985 176900 189260 203342";
			try
			{
                using (GnStatusEventsDelegate midEvents = new LookupStatusEvents())
				{
					uint      choiceOrdinal = 0;
					GnMusicId gnMusicID = new GnMusicId(user, midEvents);
					Console.WriteLine("\n*****MusicID TOC Query*****");
					GnResponseAlbums gnResponse = gnMusicID.FindAlbums(toc);

					/* using response.StringValue instead of response.NeedsDecision as it throws ArgumentException */
					/* See if selection of one of the albums needs to happen */
					if (gnResponse.NeedsDecision)
					{
						choiceOrdinal = DisplayForResolve(gnResponse);
					}
					else
					{
						/* no need for disambiguation, we'll take the first album */
						choiceOrdinal = 0;
					}

					GnAlbum album = gnResponse.Albums.at(choiceOrdinal).next();

					/* Is this a partial album? */
					bool fullResult = album.IsFullResult;
					if (!fullResult)
					{
						/* do followup query to get full object. Setting the partial album as the query input. */
						/* GnDataObject dataobj = new GnDataObject(album); */
						gnResponse = gnMusicID.FindAlbums(album);

						/* now our first album is the desired result with full data */
						album = gnResponse.Albums.at(0).next();
					}

					if (album != null)
					{
						GnTitle iGnTitle = album.Title;
						Console.WriteLine("    Final album:");
						Console.WriteLine("          Title: " + iGnTitle.Display);
					}
				}

			}
			catch (GnException e)
			{
				Console.WriteLine("Error Code           :: " + e.ErrorCode);
				Console.WriteLine("Error Description    :: " + e.ErrorDescription);
				Console.WriteLine("Error API            :: " + e.ErrorAPI);
				Console.WriteLine("Source Error Code    :: " + e.SourceErrorCode);
				Console.WriteLine("SourceE rror Module  :: " + e.SourceErrorModule);
			}
		}

        /// <summary>
        /// Sample app start (main)
        /// </summary>
        /// <param name="args"></param>
        /// <returns></returns>
		static int Main(string[] args)
		{
	        string  licenseFile;
	        string  gnsdkLibraryPath;
	        string  clientId;
	        string  clientIdTag;
	        string  applicationVersion = "1.0.0.0";  /* Increment with each version of your app */
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

			/* GNSDK initialization */
			try
			{
				/* Initialize SDK */
                GnManager manager = new GnManager(gnsdkLibraryPath, licenseFile, GnLicenseInputMode.kLicenseInputModeFilename);

                /* Display SDK version */
                Console.WriteLine("\nGNSDK Product Version : " + manager.ProductVersion + " \t(built " + manager.BuildDate + ")");

                // Enable GNSDK logging 
                GnLog sampleLog = new GnLog("sample.log", null);
                GnLogFilters filters = new GnLogFilters();
                sampleLog.Filters(filters.Error().Warning());               // Include only error and warning entries 
                GnLogColumns columns = new GnLogColumns();
                sampleLog.Columns(columns.All());			                // Add all columns to log: timestamps, thread IDs, etc 
                GnLogOptions options = new GnLogOptions();
                sampleLog.Options(options.MaxSize(0).Archive(false));       // Max size of log: 0 means a new log file will be created each run. Archive option will save old log else it will regenerate the log each time 
                sampleLog.Enable(GnLogPackageType.kLogPackageAllGNSDK);     // Include entries for all packages and subsystems 

                // Enable Database Support
                EnableStorage();

                if (lookupMode == GnLookupMode.kLookupModeLocal)
                {
                    // Enable local database lookups 
                    EnableLocalLookups();
                }

                // Get GnUser instance to allow us to perform queries 
                GnUser user = GetUser(manager, clientId, clientIdTag, applicationVersion, lookupMode);

                // set user to match our desired lookup mode (all queries done with this user will inherit the lookup mode) 
                user.Options().LookupMode(lookupMode);

				// Set locale with desired Group, Language, Region and Descriptor
				// Set the 'locale' to return locale-specifc results values. This examples loads an English locale.
				LoadLocale(user);

				// perform a sample album TOC lookup
				MusicIDAlbumLookup(user);

                // Success
                result = SUCCESS;

			}
			catch (GnException e)
			{
				Console.WriteLine("GnException : (" + e.Message.ToString() + ")" + e.Message);
			}
            return result;
		}
	}
}

