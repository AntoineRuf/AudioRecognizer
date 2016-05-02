/*
 *
 *  GRACENOTE, INC. PROPRIETARY INFORMATION
 *  This software is supplied under the terms of a license agreement or
 *  nondisclosure agreement with Gracenote, Inc. and may not be copied
 *  or disclosed except in accordance with the terms of that agreement.
 *  Copyright(c) 2000-2013. Gracenote, Inc. All Rights Reserved.
 *
 */

/*
 * MusicIDImageFetch.cs
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
	/**********************************************
	*    Test Data
	**********************************************/

	/* Simulate MP3 tag data. */
	public class MP3
	{
		public string albumTitleTag;
		public string artistNameTag;
		public string genreTag;
		public
		MP3(string albumTitle, string artistname, string genre)
		{
			albumTitleTag = albumTitle;
			artistNameTag = artistname;
			genreTag      = genre;
		}

	}


	public class MusicIDImageFetch
	{
        static int SUCCESS = 0;
        static int ERROR = 1;
		private static List<MP3> mp3Folder = new List<MP3>();
        private static string dbPath = @"../../../../sample_data/sample_db";
		/* GnStatusEventsDelegate : overrider methods of this class to get delegate callbacks */
        public class LookupStatusEvents : GnStatusEventsDelegate
		{
			/*-----------------------------------------------------------------------------
			 *  StatusEvent
			 */
			public override void
			StatusEvent(GnStatus status, uint percentComplete, uint bytesTotalSent, uint bytesTotalReceived, IGnCancellable canceller)
			{
				Console.Write("\nPerforming MusicID Query ...\t");
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

		}



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
        /// 
        /// </summary>
        /// <param name="input"></param>
        /// <param name="list"></param>
        /// <returns></returns>
		static GnListElement DoListSearch(string input, GnList list)
		{
			GnListElement listElement = list.ElementByString(input);

			uint   level = listElement.Level;
			string value = listElement.DisplayString;

			Console.WriteLine("List element result: " + value + " (level " + level + ")");
			return listElement;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="album"></param>
		/// <param name="gdoType"></param>
		/// <param name="user"></param>
		private static void PerformImageFetch(GnAlbum album, string gdoType, GnUser user)
		{
			GnImageSize imageSize          = GnImageSize.kImageSize170;
			string      availableImageSize = null;
			bool        notFound           = false;

			if ((album == null) || (gdoType == null))
			{
				Console.WriteLine("Must pass a GDO and type");
				return;
			}

			/* Create the query handle without a callback or callback data (GNSDK_NULL) */
			GnLink link = new GnLink(album, user);

			/* Set preferred image size */
			GnImageSize preferredImageSize = GnImageSize.kImageSize170;

			/* Obtain image size available */
            if (user.Options().LookupMode() == GnLookupMode.kLookupModeLocal)
            {
                GnLookupLocal gnLookupLocal = GnLookupLocal.Enable();

                uint count = gnLookupLocal.StorageInfoCount(GnLocalStorageName.kLocalStorageContent, GnLocalStorageInfo.kLocalStorageInfoImageSize);
                for (uint ordinal = 0; ordinal < count; ordinal++)
                {
                    availableImageSize = gnLookupLocal.StorageInfo(GnLocalStorageName.kLocalStorageContent, GnLocalStorageInfo.kLocalStorageInfoImageSize, ordinal);
                    /* TODO */
                }
            }
            else
            {
                imageSize = preferredImageSize;
            }

			/* If album type get cover art */
			notFound = FetchImage(link, imageSize, "cover art");

			/* if no cover art, try to get the album's artist image */
			if (notFound == true)
			{
				notFound = FetchImage(link, imageSize, "artist image");

				/* if no artist image, try to get the album's genre image so we have something to display */
				if (notFound == true)
					notFound = FetchImage(link, imageSize, "genre image");
			}

		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="link"></param>
		/// <param name="imageSize"></param>
		/// <param name="imageType"></param>
		/// <returns></returns>
		private static bool
		FetchImage(GnLink link, GnImageSize imageSize, string imageType)
		{
			GnLinkContent linkContent = null;
			bool          notFound    = false;

			try
			{
				/* Perform the image fetch */
				switch (imageType)
				{
				case "cover art":
					linkContent = link.CoverArt(imageSize, GnImagePreference.exact);
					break;

				case "artist image":
					linkContent = link.ArtistImage(imageSize, GnImagePreference.exact);
					break;

				case "genre image":
					linkContent = link.GenreArt(imageSize, GnImagePreference.exact);
					break;
				}


				Console.WriteLine("\nRETRIEVED: " + imageType
				                  + ": "
				                  + linkContent.DataBuffer.Length
				                  + " byte JPEG");

				notFound = false;
			}
			catch (GnException)
			{
				/* Do not return error code for not found. */
				/* For image to be fetched, it must exist in the size specified and you must be entitled to fetch images. */
				Console.WriteLine("NOT FOUND: " + imageType);
				notFound = true;
			}

			return notFound;
		}

		/***************************************************************************
		*
		*    FindGenreImage
		*
		* This function performs a text lookup of a genre string.
		* If there is a match, the genre image is fetched.
		*
		***************************************************************************/
		private static int
		FindGenreImage(GnUser user, string genre, GnList list)
		{
			int         gotMatch = 0;
			string      availableImageSize;
			GnImageSize imageSize = GnImageSize.kImageSize170;
			GnLink      link      = null;

			Console.WriteLine("Genre String Search");

			if (genre == null)
			{
				Console.WriteLine("Must pass a genre");
				return -1;
			}

			/* Find the list element for our input string */
			GnListElement listElement = DoListSearch(genre, list);

			if (listElement != null)
			{
				/* we were able to idenfity the input genre string */
				gotMatch = 1;

				/* Create the query handle without a callback or callback data (GNSDK_NULL) */
				link = new GnLink(listElement, user);
			}

			/* Set preferred image size */
			GnImageSize preferredImageSize = GnImageSize.kImageSize170;

			/* Obtain image size available */
            if (user.Options().LookupMode() == GnLookupMode.kLookupModeLocal)
            {
                GnLookupLocal gnLookupLocal = GnLookupLocal.Enable();

                uint count = gnLookupLocal.StorageInfoCount(GnLocalStorageName.kLocalStorageContent, GnLocalStorageInfo.kLocalStorageInfoImageSize);
                for (uint ordinal = 0; ordinal < count; ordinal++)
                {
                    availableImageSize = gnLookupLocal.StorageInfo(GnLocalStorageName.kLocalStorageContent, GnLocalStorageInfo.kLocalStorageInfoImageSize, ordinal);
                    /* TODO */
                }
            }
            else
            {
                imageSize = preferredImageSize;
            }

			bool notFound = FetchImage(link, imageSize, "genre image");

			return gotMatch;
		}

		/***************************************************************************
		*
		*    DoSampleTextQuery
		*
		* This function performs a text lookup using musicid. If there is a match,
		* the associated image is fetched.
		*
		***************************************************************************/
		private static int
		DoSampleTextQuery(string albumTitleTag, string artistNameTag, GnUser user)
		{
			int    gotMatch = 0;
			string gdoType  = null;

			Console.WriteLine("MusicID Text Match Query");

			if ((albumTitleTag == null) && (artistNameTag == null))
			{
				Console.WriteLine("Must pass album title or artist name");
				return -1;
			}

			if (albumTitleTag == null)
				albumTitleTag = String.Empty;
			else
				Console.WriteLine("album title    : " + albumTitleTag);        /*    show the fields that we have set    */

			if (artistNameTag == null)
				artistNameTag = String.Empty;
			else
				Console.WriteLine("artist name    : " + artistNameTag);

			GnMusicId musicID = new GnMusicId(user);
			GnResponseDataMatches responseDataMatches = musicID.FindMatches(albumTitleTag, String.Empty, artistNameTag, string.Empty, string.Empty);

			uint count = responseDataMatches.DataMatches.count();

			Console.WriteLine("Number matches = " + count);

			/* Get the first match type */
			if (count > 0)
			{
				/* OK, we got at least one match. */
				gotMatch = 1;

				/* Just use the first match for demonstration. */
				GnDataMatch dataMatch = responseDataMatches.DataMatches.at(0).next();


				gdoType = dataMatch.GetType();

				Console.WriteLine("\nFirst Match GDO type: " + gdoType);

				/* Get the best image for the match */
				PerformImageFetch(dataMatch.GetAsAlbum(), gdoType, user);
			}

			return gotMatch;
		}

		/***************************************************************************
		*
		*    ProcessSampleMp3
		*
		***************************************************************************/
		private static void
		ProcessSampleMp3(MP3 mp3, GnUser user, GnList list)
		{
			int got_match = 0;

			/* Do a music text query and fetch image from result. */
			got_match = DoSampleTextQuery(mp3.albumTitleTag, mp3.artistNameTag, user);

			/* If there were no results from the musicid query for this file, try looking up the genre tag to get the genre image. */
			if (0 == got_match)
			{
				if (null != mp3.genreTag)
				{
					got_match = FindGenreImage(user, mp3.genreTag, list);
				}
			}

			/* did we succesfully find a relevant image? */
			if (0 == got_match)
			{
				Console.Write("Because there was no match result for any of the input tags, you may want to associated the generic music image with this track, music_75x75.jpg, music_170x170.jpg or music_300x300.jpg\n");
			}
		}

		/*-----------------------------------------------------------------------------
		 *  PopulateData
		 */
		private static void
		PopulateData()
		{
			/* Simulate a folder of MP3s.
			 *
			 * file 1: Online - At the time of writing, yields an album match but no cover art or artist images are available.
			 *                  Fetches the genre image for the returned album's genre.
			 *         Local - Yields no match for the query of "Low Commotion Blues Band" against the sample database.
			 *                 Uses the genre tag from the file, "Rock", to perform a genre search and fetches the genre image from that.
			 * file 2: Online - Yields an album match for album tag "Supernatural". Fetches the cover art for that album.
			 *         Local - Same result.
			 * file 3: Online - Yields an album matches for Phillip Glass. Fetches the cover art for the first album returned.
			 *         Local - Yields an artist match for the artist tag "Phillip Glass". Fetches the artist image for Phillip Glass.
			 */
			mp3Folder.Add(new MP3("Ask Me No Questions", "Low Commotion Blues Band", "Rock"));
			mp3Folder.Add(new MP3("Supernatural", "Santana", null));
			mp3Folder.Add(new MP3(null, "Phillip Glass", null));

		}

		/*
		 * Sample app start (main)
		 */
		static int Main(string[] args)
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

            /* GNSDK initialization */
            try
			{
				// Initialize SDK 
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

                LoadLocale(user);

				PopulateData();
				// Get the genre list handle. This will come from our pre-loaded locale.
				//   Be sure these params match the ones used in get_locale to avoid loading a different list into memory.

				//   NB: If you plan to do many genre searches, it is most efficient to get this handle once during
				//   initialization (after setting your locale) and then only release it before shutdown.
				 

				GnList list = new GnList(
                    GnListType.kListTypeGenres, 
                    GnLanguage.kLanguageEnglish, 
                    GnRegion.kRegionDefault, 
                    GnDescriptor.kDescriptorSimplified, 
                    user
                    );

				/* Simulate iterating a sample of mp3s. */
				for (int fileIndex = 0; fileIndex < mp3Folder.Count; fileIndex++)
				{
					Console.Write("\n\n***** Processing File " + (fileIndex) + " *****\n");
					ProcessSampleMp3(mp3Folder[fileIndex], user, list);
				}

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

