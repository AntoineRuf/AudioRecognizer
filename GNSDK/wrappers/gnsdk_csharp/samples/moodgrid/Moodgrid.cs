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
using System.Collections;
using System.Linq;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;
using GracenoteSDK;

namespace Sample
{
    /// <summary>
    ///  Name: Moodgrid
    ///  Description:
    ///  Moodgrid is the GNSDK library that generates playlists based on Mood by simply accessing parts of the Grid.
    ///  moodgrid APIs enable an application to: 
    ///  01. Discover and enumerate all datasources available for Moodgrid (from both offline and online sources )
    ///  02. Create and administer data representation of Moodgrid for different types of datasources and grid types.
    ///  03. Query a grid cell for a playlist based on the Mood it represents.
    ///  04. Set Pre Filters on the Moodgrid for Music Genre, Artist Origin and Artist Era.
    ///  05. Manage results.
    ///  Datasources : Offline datasources for Moodgrid can be created by using Gnsdk Playlist. This sample demonstrates this.
    ///  Steps:
    ///  See inline comments below.
    ///  Notes:
    ///  For clarity and simplicity error handling in not shown here.
    ///  Refer "logging" sample to learn about GNSDK error handling.
    ///  Command-line Syntax:
    ///  sample client_id client_id_tag license
    /// </summary>
    /// 
    class Moodgrid
    {
        static int SUCCESS = 0;
        static int ERROR = 1;
        private static string folderPath = @"../../../../sample_data/";
        private static string dbPath = @"../../../../sample_data/sample_db";
		
        public class LookupStatusEvents : GnStatusEventsDelegate
        {
           
           /// <summary>
           /// Overrride implemented for status events . 
           /// </summary>
           /// <param name="status"></param>
           /// <param name="percentComplete"></param>
           /// <param name="bytesTotalSent"></param>
           /// <param name="bytesTotalReceived"></param>
           /// <param name="canceller"></param>
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
	        uint    ordinal     = gnLookupLocal.StorageInfoCount(GnLocalStorageName.kLocalStorageMetadata, GnLocalStorageInfo.kLocalStorageInfoVersion);
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
        /// 
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
        /// DoMoodgridPresentation
        /// </summary>
        /// <param name="user"></param>
        /// <param name="provider"></param>
        /// <param name="gnMoodgridPresentationType"></param>
        private static void DoMoodgridPresentation(GnUser user, GnMoodgridProvider provider, GnMoodgridPresentationType gnMoodgridPresentationType)
        {

            GnMoodgridPresentation presentation = null;
            uint count = 0;
            string value = null;

            /* get the details for the provider */
            value = provider.Name;
            Console.WriteLine("GNSDK_MOODGRID_PROVIDER_NAME : " + value + " ");

            value = provider.Type;
            Console.WriteLine("\nGNSDK_MOODGRID_PROVIDER_TYPE : " + value + " ");

            value = provider.RequiresNetwork.ToString();
            Console.WriteLine("\nGNSDK_MOODGRID_PROVIDER_NETWORK_USE : " + value.ToUpper() + " ");

            GnMoodgrid moodGrid = new GnMoodgrid();

            // create a moodgrid presentation for the specified type 
            presentation = moodGrid.CreatePresentation(user, gnMoodgridPresentationType, GnMoodgridCoordinateType.kMoodgridCoordinateTopLeft);            
            
            // query the presentation type for its dimensions 
            GnMoodgridDataPoint dataPoint = moodGrid.Dimensions(gnMoodgridPresentationType);
            Console.WriteLine("\n PRINTING MOODGRID " + dataPoint.X + " x " + dataPoint.Y + " GRID ");

            // enumerate through the moodgrid getting individual data and results 
            GnMoodgridPresentationDataEnumerable moodgridPresentationDataEnumerable = presentation.Moods;           
           
            foreach (GnMoodgridDataPoint position in moodgridPresentationDataEnumerable)
            {
                uint x = position.X;
                uint y = position.Y;

                // get the name for the grid coordinates in the language defined by Locale
                string name = presentation.MoodName(position);

                // get the mood id 
                string id = presentation.MoodId(position);

                // find the recommendation for the mood 
                GnMoodgridResult moodgridResult = presentation.FindRecommendations(provider, position);

                // count the number of results 
                count = moodgridResult.Count();
                Console.WriteLine("\n\n\tX:" + x + "  Y:" + y + " name: " + name + " count: " + count + " ");

                // iterate the results for the idents 
                GnMoodgridResultEnumerable identifiers = moodgridResult.Identifiers;
                foreach (GnMoodgridIdentifier identifier in identifiers)
                {
                    string ident = identifier.MediaIdentifier;
                    string group = identifier.Group;
                    Console.WriteLine("\n\tX:" + x + " Y:" + y + " \nident:\t" + ident + "  \ngroup:\t" + group );
                }
            }
        }

        /// <summary>
        /// PerformSampleMoodgrid
        /// </summary>
        /// <param name="user"></param>
        private static void PerformSampleMoodgrid(GnUser user)
        {
            GnPlaylistStorage plStorage = new GnPlaylistStorage();
            plStorage.Location(folderPath);

            // load the offline collection  
            Console.WriteLine("\nLoading sample collection");
            GnPlaylistCollection collection = plStorage.Load("sample_collection");

            Console.WriteLine("Enumerating for the first Moodgrid Provider available");
            GnMoodgrid moodgrid = new GnMoodgrid();
            GnMoodgridProvider provider = moodgrid.Providers.at(0).next();

            // create, query and print a  5 x  5  moodgrid  
            DoMoodgridPresentation(user, provider, GnMoodgridPresentationType.kMoodgridPresentationType5x5);

            Console.WriteLine("");

            // create, query and print a 10 x 10 moodgrid
            DoMoodgridPresentation(user, provider, GnMoodgridPresentationType.kMoodgridPresentationType10x10);
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
	        string  applicationVersion = "1.0.0.0";  // Increment with each version of your app */
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
			        return result;
		        }
	        }
	        else
	        {
		        Console.Write("\nUsage:  clientId clientIdTag license gnsdkLibraryPath lookupMode\n");
		        return result;
	        }

		    // GNSDK initialization 
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
                sampleLog.Enable(GnLogPackageType.kLogPackageAllGNSDK);     // Include entries for all packages and subsystems 

                // Enable storage module 
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

                // Perform a sample album TOC query 
                PerformSampleMoodgrid(user);

                // success 
                result = SUCCESS;
            }

            // All gracenote sdk objects throws GnException
            catch (GnException e)
            {
                Console.WriteLine("Error Code           :: " + e.ErrorCode);
                Console.WriteLine("Error Description    :: " + e.ErrorDescription);
                Console.WriteLine("Error API            :: " + e.ErrorAPI);
                Console.WriteLine("Source Error Code    :: {0:X}", e.SourceErrorCode);
                Console.WriteLine("Source Error Module :: " + e.SourceErrorModule);
            }
            return result;
        }
    }
}
