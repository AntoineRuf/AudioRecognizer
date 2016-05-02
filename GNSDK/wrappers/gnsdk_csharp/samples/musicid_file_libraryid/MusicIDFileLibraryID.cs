/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: MusicIDFileLibraryID.cs (MusicID-File LibraryID sample appilcation)
 *  Description:
 *  LibraryID processing adds another level of processing above AlbumID for very large collections of media files.
 *  LibraryID extends AlbumID functionality by  performing additional scanning and processing of all the files in
 *  an entire collection. This enables LibraryID to find groupings that are not captured by AlbumID processing.
 *  This method is highly recommended for use when there are a large number (hundreds to thousands) of files to
 *  identify, though it is also equally effective when processing only a few files. This method takes most of
 *  the guesswork out of MusicID-File and lets the library do all the work for the application.
 *  The GnMusicIdFile::DoAlbumID method provides LibraryID processing.
 *
 *  Command-line Syntax:
 *  sample clientId clientIdTag license gnsdkLibraryPath
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using GracenoteSDK;
using System.Diagnostics;

namespace Sample
{
	public class MusicIDFileLibraryID
	{
        static int SUCCESS = 0;
        static int ERROR = 1;
        private static string folderPath = @"../../../../sample_data/";
        private static string dbPath = @"../../../../sample_data/sample_db";
		/* Callback delegate called when performing MusicID-File operation */
        /// <summary>
        /// Callback delegate called when performing MusicID-File operation
        /// IMPORTANT NOTE: All the interface elements of GnMusicIdFileEventsDelegate must be overriden.
        /// </summary>
		public class MusicIDFileEvents : GnMusicIdFileEventsDelegate
		{
			
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


            /// <summary>
            /// This method is called when a MusicIdFile Status Event is triggered.
            /// </summary>
            /// <param name="fileInfo"></param>
            /// <param name="status"></param>
            /// <param name="currentFile"></param>
            /// <param name="totalFiles"></param>
            /// <param name="canceller"></param>
            public override void
			MusicIdFileStatusEvent(GnMusicIdFileInfo fileInfo, GnMusicIdFileCallbackStatus status, uint currentFile, uint totalFiles, IGnCancellable canceller)
			{
				switch (status)
				{
					case GnMusicIdFileCallbackStatus.kMusicIdFileCallbackStatusProcessingBegin:
					Console.WriteLine("\nMID-File Status: " + currentFile + " of " + totalFiles + " - fileInfo_processing_begin - " + fileInfo.Identifier);
					break;

					case GnMusicIdFileCallbackStatus.kMusicIdFileCallbackStatusFileInfoQuery:
					Console.WriteLine("\nMID-File Status: " + currentFile + " of " + totalFiles + " - fileInfo_query - " + fileInfo.Identifier);
					break;

					case GnMusicIdFileCallbackStatus.kMusicIdFileCallbackStatusProcessingComplete:
					Console.WriteLine("\nMID-File Status: " + currentFile + " of " + totalFiles + " - fileInfo_processing_complete - " + fileInfo.Identifier);
					break;
				}
			}

            /// <summary>
            /// This will be called when a fingerprint needs to gathered from file.
            /// </summary>
            /// <param name="fileInfo"></param>
            /// <param name="currentFile"></param>
            /// <param name="totalFiles"></param>
            /// <param name="canceller"></param>
			public override void
			GatherFingerprint(GnMusicIdFileInfo fileInfo, uint currentFile, uint totalFiles, IGnCancellable canceller)
			{
				FileStream fileStream = null;
				try
				{
					bool   complete  = false;
					byte[] audioData = new byte[2048];
					int    numRead   = 0;

					string filename = fileInfo.FileName.ToString();

					fileStream = new FileStream(folderPath + filename, FileMode.Open, FileAccess.Read);

					/* check file for existence */
					if (fileStream == null || !fileStream.CanRead)
					{
						Console.WriteLine("\n\nError: Failed to open input file: " + filename);
					}
					else
					{
						/* skip the wave header (first 44 bytes). we know the format of our sample files, but please
						   be aware that many wav file headers are larger then 44 bytes! */
						if (44 != fileStream.Seek(44, SeekOrigin.Begin))
						{
							Console.WriteLine("\n\nError: Failed to seek past header: %s\n", filename);
						}
						else
						{
							/* initialize the fingerprinter
							   Note: Our sample files are non-standard 11025 Hz 16-bit mono to save on file size */
							fileInfo.FingerprintBegin(11025, 16, 1);

							numRead = fileStream.Read(audioData, 0, 2048);
							while ((numRead) > 0)
							{
								/* write audio to the fingerprinter */
								complete = fileInfo.FingerprintWrite(audioData, Convert.ToUInt32(numRead));

								/* does the fingerprinter have enough audio? */
								if (complete)
								{
									break;
								}

								numRead = fileStream.Read(audioData, 0, 2048);
							}
							fileStream.Close();

							/* signal that we are done */
							fileInfo.FingerprintEnd();
							Debug.WriteLine("Fingerprint: " + fileInfo.Fingerprint + " File: " + fileInfo.FileName);
						}
					}
					if (!complete)
					{
						/* Fingerprinter doesn't have enough data to generate a fingerprint.
						   Note that the sample data does include one track that is too short to fingerprint. */
						Console.WriteLine("Warning: input file does not contain enough data to generate a fingerprint:\n" + filename);
					}
				}
				catch (FileNotFoundException e)
				{
					Console.WriteLine("FileNotFoundException " + e.Message);
				}
				catch (IOException e)
				{
					Console.WriteLine("IOException " + e.Message);
				}
				finally
				{
					try
					{
						fileStream.Close();
					}
					catch (IOException e)
					{
						Console.WriteLine("IOException " + e.Message);
					}
				}
			}

            /// <summary>
            /// This method will be called when metadata is needed  for a file. 
            /// A typical use for this callback is to read file tags (ID3, etc) for the basic 
            /// metadata of the track.  To keep the sample code simple, we went with .wav files
            /// To keep the sample code simple, we went with .wav files
            /// and hardcoded in metadata for just one of the sample tracks.  (MYAPP_SAMPLE_FILE_5)
            /// </summary>
            /// <param name="fileInfo"></param>
            /// <param name="currentFile"></param>
            /// <param name="totalFiles"></param>
            /// <param name="canceller"></param>
			public override void
			GatherMetadata(GnMusicIdFileInfo fileInfo, uint currentFile, uint totalFiles, IGnCancellable canceller)
			{
				try
				{
					String identifier = fileInfo.Identifier;

					/*
					 * A typical use for this callback is to read file tags (ID3, etc) for the basic
					 * metadata of the track.  To keep the sample code simple, we went with .wav files
					 * and hardcoded in metadata for just one of the sample tracks.  (MYAPP_SAMPLE_FILE_5)
					 */

					/* So, if this isn't the correct sample track, return.*/
					if (!identifier.Contains(@"kardinal_offishall_01_3s.wav"))
					{
						return;
					}
					fileInfo.AlbumArtist = @"kardinal offishall";
					fileInfo.AlbumTitle  = @"quest for fire";
					fileInfo.TrackTitle  = @"intro";
				}
				catch (GnException ex)
				{
					Console.WriteLine("Error while setting metadata setMetadata()" + ex.Message);
				}
			}

            /// <summary>
            /// This method will be called when there is an album available 
            /// </summary>
            /// <param name="albumResult"></param>
            /// <param name="currentAlbum"></param>
            /// <param name="totalAlbums"></param>
            /// <param name="canceller"></param>
			public override void
			MusicIdFileAlbumResult(GnResponseAlbums album_result, uint current_album, uint total_albums, IGnCancellable canceller)
			{
				Console.WriteLine("\nMID-File Result: ");
				Console.WriteLine("\tAlbum count: " + album_result.Albums.count());
				DisplayAlbums(album_result);
			}

            /// <summary>
            /// This method will be called when a FindMatches call is made and a result is available. 
            /// </summary>
            /// <param name="matchesResult"></param>
            /// <param name="currentAlbum"></param>
            /// <param name="totalAlbums"></param>
            /// <param name="canceller"></param>
            public override void MusicIdFileMatchResult(GnResponseDataMatches matchesResult, uint currentAlbum, uint totalAlbums, IGnCancellable canceller)
            {
                Console.Write("\n MusicIdFileMatchResult  *Match Result " + currentAlbum + " of " + totalAlbums + "*\n");
            }

            /// <summary>
            /// This method will be called when there is no result available for a given MusicIdFileInfo 
            /// </summary>
            /// <param name="fileInfo"></param>
            /// <param name="currentFile"></param>
            /// <param name="totalFiles"></param>
            /// <param name="canceller"></param>
            public override void MusicIdFileResultNotFound(GnMusicIdFileInfo fileInfo, uint currentFile, uint totalFiles, IGnCancellable canceller)
            {
                Console.Write("\n MusicIdFileResultNotFound  *File " + currentFile + " of " + totalFiles + "*\n");
            }

            /// <summary>
            /// This will be called when the MusicIdFile find operation is completed.
            /// </summary>
            /// <param name="completeError">Any error that occurred will be returned. </param>
            public override void MusicIdFileComplete(GnError completeError)
            {
                Console.Write("\n MusicIdFileComplete " + completeError.ErrorDescription());
            }

		}

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



		/*-----------------------------------------------------------------------------
		 *  DisplayAlbums
		 */
		public static void
		DisplayAlbums(GnResponseAlbums response)
		{
			int               match           = 0;
			GnAlbumEnumerable albumEnumerable = response.Albums;
			GnAlbumEnumerator albumEnumerator = albumEnumerable.GetEnumerator();
			while (albumEnumerator.hasNext())
			{
				GnAlbum album      = albumEnumerator.Current;
				GnTitle albumTitle = album.Title;
				Console.WriteLine("\tMatch " + ++match + " - Album title:\t\t" + albumTitle.Display);

			}
		}

		/*-----------------------------------------------------------------------------
		 *  AddFile
		 */
		static void
		AddFile(GnMusicIdFile midf, string filePath)
		{
			/* identifier string - we'll use the file path, which is unique */
			GnMusicIdFileInfo fileInfo = midf.FileInfos.Add(filePath);

			/* Set the file path in the fileInfo */
			fileInfo.FileName = filePath;
		}

		/*-----------------------------------------------------------------------------
		 *  SetQueryData
		 */
		static void
		SetQueryData(GnMusicIdFile midf)
		{
			List<string> filenames = new List<string>();

			filenames.Add(@"01_stone_roses.wav");
			filenames.Add(@"04_stone_roses.wav");
			filenames.Add(@"stone roses live.wav");
			filenames.Add(@"Dock Boggs - Sugar Baby - 01.wav");
			filenames.Add(@"kardinal_offishall_01_3s.wav");
			filenames.Add(@"Kardinal Offishall - Quest For Fire - 15 - Go Ahead Den.wav");

			/* add our 6 sample files to the query */
			foreach (string file in filenames)
			{
				AddFile(midf, file);
			}
		}

	    /// <summary>
	    /// 
	    /// </summary>
	    /// <param name="user"></param>
	    /// <param name="responseType"></param>
	
		static void
		DoMusicIDFile(GnUser user, GnMusicIdFileResponseType responseType)
		{
			/* Perform the Query */
			using (GnMusicIdFileEventsDelegate myMidEvents = new MusicIDFileEvents())
			{
				GnMusicIdFile midf = new GnMusicIdFile(user, myMidEvents);

				/* Add our sample files to the query. Metadata and fingerprints will be set in the callbacks. */
				SetQueryData(midf);

				midf.DoLibraryId(responseType);
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="args"></param>
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

                // Enable Database Storage 
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

				// Perform MusicID-File LibraryID lookups 

				DoMusicIDFile(user, GnMusicIdFileResponseType.kResponseAlbums);

                // success
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

