/*
 *  Copyright (c) 2000-2013 Gracenote.
 *
 *  This software may not be used in any way or distributed without
 *  permission. All rights reserved.
 *
 *  Some code herein may be covered by US and international patents.
 */

/*
 *  Name: Music response data object sample appilcation
 *  Description:
 *  This application uses MusicID to look up Album GDO content,	including Album	artist,	credits, title,	year, and genre.
 *  It demonstrates	how	to navigate	the	album GDO that returns basic track information,	including artist, credits, title, track	number,	and	genre.
 *  Notes:
 *  For	clarity	and	simplicity error handling in not shown here.
 *  Refer "logging"	sample to learn	about GNSDK	error handling.
 *
 *  Command-line Syntax:
 *  sample clientId clientIdTag license gnsdkLibraryPath
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
	public class MusicIDGdoNavigation
	{
        static int SUCCESS = 0;
        static int ERROR = 1;
        private static string dbPath = @"../../../../sample_data/sample_db";


        /// <summary>
        /// Callback delegate called when loading locale
        /// </summary>
		public class LookupStatusEvents : GnStatusEventsDelegate
		{
			public static List<string> statusString = new List<string> { "Unknown", "Begin", "Progress", "Complete", "ErrorInfo", "Connecting", "Sending", "Recieving", "Disconnected", "Reading", "Writing" };

			/*-----------------------------------------------------------------------------
			 *  StatusEvent
			 */
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
				Console.WriteLine("\t% Complete (" + percentComplete + "),\tTotal Bytes Sent (" + bytesTotalSent + "),\tTotal Bytes Received (" + bytesTotalReceived + ")");
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
        /// Prints out the relevant information for the Track.
        /// </summary>
        /// <param name="gnTrack"></param>
		private static void
		DisplayTrack(GnTrack gnTrack)
		{
			Console.WriteLine("\tTrack:");
			Console.WriteLine("\t\tTrack TUI: " + gnTrack.Tui);
			Console.WriteLine("\t\tTrack Number: " + gnTrack.TrackNumber);

			GnArtist      artist      = gnTrack.Artist;
			GnContributor contributor = artist.Contributor;

			if (contributor != null)
			{
				DisplayContributors(contributor, "\t\t");
			}
			if (gnTrack.Title != null)
			{
				DisplayTitle(gnTrack.Title, "\t");
			}
			if (!String.IsNullOrEmpty(gnTrack.Genre(GnDataLevel.kDataLevel_1)))
			{
				Console.WriteLine("\t\tGenre Level 1: " + gnTrack.Genre(GnDataLevel.kDataLevel_1));
			}
			if (!String.IsNullOrEmpty(gnTrack.Genre(GnDataLevel.kDataLevel_2)))
			{
				Console.WriteLine("\t\tGenre Level 2: " + gnTrack.Genre(GnDataLevel.kDataLevel_2));
			}
			if (!String.IsNullOrEmpty(gnTrack.Genre(GnDataLevel.kDataLevel_3)))
			{
				Console.WriteLine("\t\tGenre Level 3: " + gnTrack.Genre(GnDataLevel.kDataLevel_3));
			}
			if (!String.IsNullOrEmpty(gnTrack.Year))
			{
				Console.WriteLine("\t\tYear: " + gnTrack.Year);
			}
		}

		/*-----------------------------------------------------------------------------
		 *  displayGnTitle
		 */
		private static void
		DisplayTitle(GnTitle gnTitle, string tab)
		{
			/* GnTitle gnTitle = gnAlbum.Title; */
			Console.WriteLine(tab + "\tTitle\tOfficial:");
			Console.WriteLine(tab + "\t\tDisplay: " + gnTitle.Display);
			if (gnTitle.Sortable != null && gnTitle.Sortable != "")
			{
				Console.WriteLine(tab + "\t\tSortable: " + gnTitle.Sortable);
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="gnContributor"></param>
		/// <param name="tab"></param>
		private static void
		DisplayContributors(GnContributor gnContributor, string tab)
		{
			GnNameEnumerable nameEnumerable = gnContributor.NamesOfficial;
			GnNameEnumerator nameEnumerator = nameEnumerable.GetEnumerator();

			if (nameEnumerator.hasNext())
			{
				Console.WriteLine(tab + "Credit:");
				Console.WriteLine(tab + "\tContributor:");
				Console.WriteLine(tab + "\t\tName Official:");

				while (nameEnumerator.hasNext())
				{
					GnName gnName = nameEnumerator.next();
					Console.WriteLine(tab + "\t\t\tDisplay: " + gnName.Display);
				}

				if (gnContributor.Origin(GnDataLevel.kDataLevel_1) != null && gnContributor.Origin(GnDataLevel.kDataLevel_1) != "")
				{
					Console.WriteLine(tab + "\t\tOrigin Level 1: " + gnContributor.Origin(GnDataLevel.kDataLevel_1));
				}
				if (gnContributor.Origin(GnDataLevel.kDataLevel_2) != null && gnContributor.Origin(GnDataLevel.kDataLevel_2) != "")
				{
					Console.WriteLine(tab + "\t\tOrigin Level 2: " + gnContributor.Origin(GnDataLevel.kDataLevel_2));
				}
				if (gnContributor.Origin(GnDataLevel.kDataLevel_3) != null && gnContributor.Origin(GnDataLevel.kDataLevel_3) != "")
				{
					Console.WriteLine(tab + "\t\tOrigin Level 3: " + gnContributor.Origin(GnDataLevel.kDataLevel_3));
				}
				if (gnContributor.Origin(GnDataLevel.kDataLevel_4) != null && gnContributor.Origin(GnDataLevel.kDataLevel_4) != "")
				{
					Console.WriteLine(tab + "\t\tOrigin Level 4: " + gnContributor.Origin(GnDataLevel.kDataLevel_4));
				}
				if (gnContributor.Era(GnDataLevel.kDataLevel_1) != null && gnContributor.Era(GnDataLevel.kDataLevel_1) != "")
				{
					Console.WriteLine(tab + "\t\tEra Level 1: " + gnContributor.Era(GnDataLevel.kDataLevel_1));
				}
				if (gnContributor.Era(GnDataLevel.kDataLevel_2) != null && gnContributor.Era(GnDataLevel.kDataLevel_2) != "")
				{
					Console.WriteLine(tab + "\t\tEra Level 2: " + gnContributor.Era(GnDataLevel.kDataLevel_2));
				}
				if (gnContributor.Era(GnDataLevel.kDataLevel_3) != null && gnContributor.Era(GnDataLevel.kDataLevel_3) != "")
				{
					Console.WriteLine(tab + "\t\tEra Level 3: " + gnContributor.Era(GnDataLevel.kDataLevel_3));
				}
				if (gnContributor.ArtistType(GnDataLevel.kDataLevel_1) != null && gnContributor.ArtistType(GnDataLevel.kDataLevel_1) != "")
				{
					Console.WriteLine(tab + "\t\tArtist Type\tLevel 1: " + gnContributor.ArtistType(GnDataLevel.kDataLevel_1));
				}
				if (gnContributor.ArtistType(GnDataLevel.kDataLevel_2) != null && gnContributor.ArtistType(GnDataLevel.kDataLevel_2) != "")
				{
					Console.WriteLine(tab + "\t\tArtist Type\tLevel 2: " + gnContributor.ArtistType(GnDataLevel.kDataLevel_2));
				}
			}
		}

	    /// <summary>
	    /// 
	    /// </summary>
	    /// <param name="gnAlbum"></param>
		private static void
		DisplayAlbum(GnAlbum gnAlbum)
		{
			Console.WriteLine("Album:");

			/*Display the package language	for	this album GDO */
			Console.WriteLine("\tPackage Language: " + gnAlbum.Language);

			GnArtist      artist      = gnAlbum.Artist;
			GnContributor contributor = artist.Contributor;

			if (contributor != null)
			{
				DisplayContributors(contributor, "\t");
			}
			if (gnAlbum.Title != null)
			{
				DisplayTitle(gnAlbum.Title, "");
			}
			if (!String.IsNullOrEmpty(gnAlbum.Year))
			{
				Console.WriteLine("\tYear: " + gnAlbum.Year);
			}
			if (!String.IsNullOrEmpty(gnAlbum.Genre(GnDataLevel.kDataLevel_1)))
			{
				Console.WriteLine("\tGenre Level 1: " + gnAlbum.Genre(GnDataLevel.kDataLevel_1));
			}
			if (!String.IsNullOrEmpty(gnAlbum.Genre(GnDataLevel.kDataLevel_2)))
			{
				Console.WriteLine("\tGenre Level 2: " + gnAlbum.Genre(GnDataLevel.kDataLevel_2));
			}
			if (!String.IsNullOrEmpty(gnAlbum.Genre(GnDataLevel.kDataLevel_3)))
			{
				Console.WriteLine("\tGenre Level 3: " + gnAlbum.Genre(GnDataLevel.kDataLevel_3));
			}
			if (!String.IsNullOrEmpty(gnAlbum.Label))
			{
				Console.WriteLine("\tAlbum Label: " + gnAlbum.Label);
			}
			if (gnAlbum.TotalInSet > 0)
			{
				Console.WriteLine("\tTotal In	Set: "+ gnAlbum.TotalInSet);
			}
			if (gnAlbum.DiscInSet > 0)
			{
				Console.WriteLine("\tDisc In Set: " + gnAlbum.DiscInSet);
			}

			/*Navigate	a track	GDO retrieved from an album	GDO */
			Console.WriteLine("\tTrack	Count: "+ gnAlbum.TrackCount);

            foreach (GnTrack track in gnAlbum.Tracks)
			{
                DisplayTrack(track);
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="gnResponse"></param>
		private static void
		DisplayFindAlbumResults(GnResponseAlbums gnResponse)
		{
			Console.WriteLine("\n***Navigating	Result GDO***");

			if (gnResponse.Albums.count() > 0)
			{
				GnAlbum album = gnResponse.Albums.First<GnAlbum>();
				DisplayAlbum(album);
			}
		}

		/*
		 *  This function looks up an album by its TUI. Upon successful single matches, it
		 *  will call the displayFindAlbumResults to navigate and display the album GDO.
		 */
		private static void
		musicidLookupAlbum(string inputTuiId, string inputTuiTag, GnUser user)
		{
			Console.WriteLine("\n*****Sample MusicID Query*****");

			GnMusicId musicid = new GnMusicId(user);
			GnAlbum          gnDataObj  = new GnAlbum(inputTuiId, inputTuiTag);
			GnResponseAlbums gnResponse = musicid.FindAlbums(gnDataObj);
			if (gnResponse.Albums.count() == 0)
			{
				/* No Matches */
				Console.WriteLine("No matches.");
			}
			else
			{
				Console.WriteLine("Match.");
				GnAlbum album = gnResponse.Albums.at(0).next();

				/* Is this a partial album? */
				bool fullResult = album.IsFullResult;
				if (!fullResult)
				{
					Console.WriteLine("retrieving FULL	RESULT");

					/* do followup query to get full object. Setting the partial album as the query input. */
					gnResponse = musicid.FindAlbums(album);
				}
				DisplayFindAlbumResults(gnResponse);
			}
		}

	
        /// <summary>
        /// This function performs TUI lookups for several different albums.
        /// </summary>
        /// <param name="user"></param>
		private static void
		DoSampleTuiLookups(GnUser user)
		{
			// Lookup album: Nelly -	Nellyville to demonstrate collaborative artist navigation in track level (track#12)
			string inputTuiId  = "30716057";
			string inputTuiTag = "BB402408B507485074CC8B3C6D313616";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);

			// Lookup album: Dido - Life for Rent  
			inputTuiId  = "46508189";
			inputTuiTag = "951407B37F9D8EAE68F74B0B5C5E1224";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);


			// Lookup album: Jean-Pierre Rampal - Portrait Of Rampal   
			inputTuiId  = "3020551";
			inputTuiTag = "CAA37D27FD12337073B54F8E597A11D3";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);

			/*
			 * Lookup album: Various Artists - Grieg: Piano Concerto, Peer Gynth
			 * Suites #1
			 */
			inputTuiId  = "2971440";
			inputTuiTag = "7F6C280498E077330B1732086C3AAD8F";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);

			/*
			 * Lookup album: Stephen Kovacevich - Brahms: Rhapsodies, Waltzes &
			 * Piano Pieces
			 */
			inputTuiId  = "2972852";
			inputTuiTag = "EC246BB5B359D88BEBDC1EF55873311E";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);

			/* Lookup album: Nirvana - Nevermind    */
			inputTuiId  = "2897699";
			inputTuiTag = "2FAE8F59CCECBA288810EC27DCD56A0A";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);


			//  Lookup album: Eminem - Encore  
			inputTuiId  = "68056434";
			inputTuiTag = "C6E3634DF05EF343E3D22CE3A28A901A";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);

			/*
			 * Lookup Japanese album: 川澄綾子 - 藍より青し -音絵巻-
			 * NOTE: In order to correctly see the Japanese metadata results for
			 * this lookup, this program will need to write out to UTF-8
			 */
			inputTuiId  = "16391605";
			inputTuiTag = "F272BD764FDEB344A54F53D0756DC3FD";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);

			/*
			 * Lookup Chinese album: 蘇芮	- 蘇芮經典
			 * NOTE: In order to correctly see the Chinese metadata results for this
			 * lookup, this program will need to write out to UTF-8
			 */
			inputTuiId  = "3798282";
			inputTuiTag = "6BF6849840A77C987E8D3AF675129F33";
			musicidLookupAlbum(inputTuiId, inputTuiTag, user);
		}

		/// <summary>
        /// Sample app start (main)
		/// </summary>
		/// <param name="args"></param>
		static int
		Main(string[] args)
		{
            string licenseFile;
            string gnsdkLibraryPath;
            string clientId;
            string clientIdTag;
            string applicationVersion = "1.0.0.0";  /* Increment with each version of your app */
            GnLookupMode lookupMode;
            int result = ERROR;

            Console.OutputEncoding = Encoding.UTF8;
            if (args.Length == 5)
            {
                clientId = args[0];
                clientIdTag = args[1];
                licenseFile = args[2];
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

            // GNSDK initialization 
            try
			{
				// Initialize SDK 
				GnManager manager = new GnManager(gnsdkLibraryPath, licenseFile, GnLicenseInputMode.kLicenseInputModeFilename);

               //Display SDK version 
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

                EnableStorage();

                if (lookupMode == GnLookupMode.kLookupModeLocal)
                {
                    EnableLocalLookups();
                }

                // Get GnUser instance to allow us to perform queries 
                GnUser user = GetUser(manager, clientId, clientIdTag, applicationVersion, lookupMode);

                // set user to match our desired lookup mode (all queries done with this user will inherit the lookup mode) 
                user.Options().LookupMode(lookupMode);

				// Set locale with desired Group, Language, Region and Descriptor
				// Set the 'locale' to return locale-specifc results values. This examples loads an English locale.

				LoadLocale( user);

				// Perform a sample	album lookup from an input GDO 
				DoSampleTuiLookups(user);

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

