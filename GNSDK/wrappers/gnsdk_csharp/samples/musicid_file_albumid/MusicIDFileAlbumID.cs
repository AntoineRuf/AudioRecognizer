/*
 *  Copyright (c) 2000-2014 Gracenote.
 *
 *  This software may not be used in any way or distributed without
 *  permission. All rights reserved.
 *
 *  Some code herein may be covered by US and international patents.
 */


using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using GracenoteSDK;

namespace Sample
{
    /// <summary>
    /// Name: MusicIDFileAlbumID.cs (MusicID-File AlbumID sample appilcation)
    /// Description:
    /// AlbumID processing provides an advanced method of media file recognition. The context of the media files
    /// (their folder location and similarity with other media files) are used to achieve more accurate media recognition.
    /// This method is best used for groups of media files where the grouping of the results matters as much as obtaining
    /// accurate, individual results. The GnMusicIdFile::DoAlbumID method provides AlbumID processing.
    /// Command-line Syntax:
    /// sample clientId clientIdTag license gnsdkLibraryPath
    /// </summary>
	public class MusicIDFileAlbumID
	{
        static int SUCCESS = 0;
        static int ERROR = 1;
        private static string folderPath = @"../../../../sample_data/";
        private static string dbPath = @"../../../../sample_data/sample_db";


        /// <summary>
        /// Callback delegate called when performing MusicID-File operation
        /// IMPORTANT NOTE: All the interface elements of GnMusicIdFileEventsDelegate must be overriden.
        /// </summary>
		public class MusicIDFileEvents : GnMusicIdFileEventsDelegate
		{
          
            /// <summary>
            /// Overriden StatusEvent
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

            
            /// <summary>
            /// 
            /// </summary>
            /// <param name="fileinfo"></param>
            /// <param name="status"></param>
            /// <param name="currentFile"></param>
            /// <param name="totalFiles"></param>
            /// <param name="canceller"></param>
            public override void
			MusicIdFileStatusEvent(GnMusicIdFileInfo fileinfo, GnMusicIdFileCallbackStatus status, uint currentFile, uint totalFiles, IGnCancellable canceller)
			{
				GnMusicIdFileInfoStatus midfStatus;

				switch (status)
				{
				case GnMusicIdFileCallbackStatus.kMusicIdFileCallbackStatusProcessingComplete:
					/* Debug.WriteLine(" : Status - Processing completed", fileinfo.Identifier); */
					midfStatus = fileinfo.Status();
					if ((int)midfStatus == 4 || (int)midfStatus == 5)
					{
						Console.Write("\n*File " + currentFile + " of " + totalFiles + "*\n");
						DisplayAlbums(fileinfo.AlbumResponse, midfStatus);
					}
					break;

				default:
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
				byte[]     audioData  = new byte[2048];
				bool       complete   = false;
				int        numRead    = 0;
				FileStream fileStream = null;
				try
				{
					string filename = fileInfo.FileName;
					if (filename.Contains('\\'))
						fileStream = new FileStream(filename, FileMode.Open, FileAccess.Read);
					else
						fileStream = new FileStream(folderPath + filename, FileMode.Open, FileAccess.Read);
					/* check file for existence */
					if (fileStream == null || !fileStream.CanRead)
					{
						Console.WriteLine("\n\nError: Failed to open input file: " + filename);
					}
					else
					{
						// skip the wave header (first 44 bytes). we know the format of our sample files, but please
						//	be aware that many wav file headers are larger then 44 bytes! 
						if (44 != fileStream.Seek(44, SeekOrigin.Begin))
						{
							Console.WriteLine("\n\nError: Failed to seek past header: %s\n", filename);
						}
						else
						{
							// initialize the fingerprinter
						    //Note: Our sample files are non-standard 11025 Hz 16-bit mono to save on file size 
							fileInfo.FingerprintBegin(11025, 16, 1);

							numRead = fileStream.Read(audioData, 0, 2048);
							while ((numRead) > 0)
							{
								// write audio to the fingerprinter 
								complete = fileInfo.FingerprintWrite(audioData, Convert.ToUInt32(numRead));

								// does the fingerprinter have enough audio? 
								if (complete)
								{
									break;
								}

								numRead = fileStream.Read(audioData, 0, 2048);
							}
							fileStream.Close();

							// signal that we are done 
							fileInfo.FingerprintEnd();
							Debug.WriteLine("Fingerprint: " + fileInfo.Fingerprint + " File: " + fileInfo.FileName);
						}
					}
					if (!complete)
					{
						// Fingerprinter doesn't have enough data to generate a fingerprint.
						// Note: that the sample data does include one track that is too short to fingerprint. 
						Console.WriteLine("Warning: input file does contain enough data to generate a fingerprint:\n" + filename);
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
				if (0 != fileInfo.Identifier.CompareTo("kardinal_offishall_01_3s.wav"))
				{
					return;
				}

				fileInfo.AlbumArtist = "kardinal offishall";
				fileInfo.AlbumTitle  = "quest for fire";
				fileInfo.TrackTitle  = "intro";
			}

            /// <summary>
            /// This method will be called when there is an album available 
            /// </summary>
            /// <param name="albumResult"></param>
            /// <param name="currentAlbum"></param>
            /// <param name="totalAlbums"></param>
            /// <param name="canceller"></param>
            public override void MusicIdFileAlbumResult(GnResponseAlbums albumResult, uint currentAlbum, uint totalAlbums, IGnCancellable canceller)
            {
                Console.Write("\n MusicIdFileAlbumResult  *Album " + currentAlbum + " of " + totalAlbums + "*\n");
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
        /// <param name="response"></param>
        /// <param name="status"></param>
		public static void DisplayAlbums(GnResponseAlbums response, GnMusicIdFileInfoStatus status)
		{
			int matchCounter = 0;
			if ((int)status == 4)
				Console.WriteLine("\n\tSingle result.");
			else if ((int)status == 5)
				Console.WriteLine("\n\tMultiple results.");

			Console.WriteLine("\tAlbum count: " + response.Albums.count());

			GnAlbumEnumerable albumEnumerable = response.Albums;
			GnAlbumEnumerator albumEnumerator = albumEnumerable.GetEnumerator();
			foreach ( GnAlbum album in albumEnumerable)
			/* while (albumEnumerator.hasNext()) */
			{
				/* GnAlbum album = albumEnumerator.next(); */

				GnTitle albTitle = album.Title;
				Console.WriteLine("\tMatch " + ++matchCounter + " - Album title:\t\t" + albTitle.Display);
			}

		}
        
        /// <summary>
        /// 
        /// </summary>
        /// <param name="fileinfo"></param>
		private static void SetMetadata(GnMusicIdFileInfo fileinfo)
		{
			try
			{
				String identifier = fileinfo.Identifier;

				/*
				 * A typical use for this callback is to read file tags (ID3, etc) for the basic
				 * metadata of the track.  To keep the sample code simple, we went with .wav files
				 * and hardcoded in metadata for just one of the sample tracks.  (MYAPP_SAMPLE_FILE_5)
				 */

				/* So, if this isn't the correct sample track, return.*/
				if (!identifier.Contains("kardinal_offishall_01_3s.wav"))
				{
					return;
				}
				fileinfo.AlbumArtist = "kardinal offishall";
				fileinfo.AlbumTitle  = "quest for fire";
				fileinfo.TrackTitle  = "intro";
			}
			catch (GnException ex)
			{
				Console.WriteLine("Error while setting metadata setMetadata()" + ex.Message);
			}
		}

	    /// <summary>
	    /// 
	    /// </summary>
	    /// <param name="fileInfo"></param>
		private static void SetFingerprint(GnMusicIdFileInfo fileInfo)
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
					Console.WriteLine("Warning: input file does contain enough data to generate a fingerprint:\n" + filename);
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
        /// 
        /// </summary>
        /// <param name="midf"></param>
        /// <param name="filePath"></param>
		static void
		AddFile(GnMusicIdFile midf, string filePath)
		{
			/* identifier string - we'll use the file path, which is unique */
			GnMusicIdFileInfo fileinfo = midf.FileInfos.Add(filePath);

			/* Set the file path in the fileinfo */
			fileinfo.FileName = filePath;

			/*Set fingerprint and metadata*/
			SetFingerprint(fileinfo);
			SetMetadata(fileinfo);
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

		/*-----------------------------------------------------------------------------
		 *  DoMusicIDFile
		 */
		static void
		DoMusicIDFile(GnUser user, GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType)
		{
			/* Perform the Query */
			using (GnMusicIdFileEventsDelegate myMidEvents = new MusicIDFileEvents())
			{
				GnMusicIdFile midf = new GnMusicIdFile(user, myMidEvents);

				/* Add our sample files to the query. Metadata and fingerprints will be set in the callbacks. */
				SetQueryData(midf);

				Console.WriteLine("\nPrinting results for " + midf.FileInfos.count() + " files:");
				midf.DoAlbumId(processType, responseType);
			}
			Console.WriteLine("\n");
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
				// Set the 'locale' to return locale-specific results values. This examples loads an English locale.
			    LoadLocale(user);

				// Perform two MusicID-File AlubmID lookups,
				// first with RETURN_SINGLE,
				// second with RETURN_ALL.
				Console.WriteLine("-------AlbumID with 'RETURN_SINGLE' option:-------");
				DoMusicIDFile(user, GnMusicIdFileProcessType.kQueryReturnSingle, GnMusicIdFileResponseType.kResponseAlbums);

				Console.WriteLine("-------AlbumID with 'RETURN_ALL' option:-------");
				DoMusicIDFile(user, GnMusicIdFileProcessType.kQueryReturnAll, GnMusicIdFileResponseType.kResponseAlbums);

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

