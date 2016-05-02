/*
* Copyright (c) 2000-2013 Gracenote.
*
* This software may not be used in any way or distributed without
* permission. All rights reserved.
*
* Some code herein may be covered by US and international patents.
*/

/*
*	Name: playlist
*	Description:
*	Playlist is the GNSDK library that generates playlists when integrated with the GNSDK MusicID or MusicID-File
*	library (or both). Playlist APIs enable an application to:
*	01. Create, administer, populate, and synchronize a collection summary.
*	02. Store a collection summary within a local storage solution.
*	03. Validate PDL statements.
*	04. Generate Playlists using either the More Like This function or the general playlist generation function.
*	05. Manage results.
*	Streamline your Playlist implementation by using the provided More Like This function
*	(gnsdk_playlist_generate_morelikethis), which contains the More Like This algorithm to generate
*	optimal playlist results and eliminates the need to create and validate Playlist Definition
*	Language statements.
*	Steps:
*	See inline comments below.
*
*	Command-line Syntax:
 *	sample clientId clientTag license libraryPath
*/

using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.IO;
using GracenoteSDK;
namespace Sample
{
    class Playlist
    {
        static int SUCCESS = 0;
        static int ERROR = 1;
        private static string dbPath = @"../../../../sample_data/sample_db";
        // Callback delegate called when loading locale
        public class LookupStatusEvents : GnStatusEventsDelegate
        {
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
                    GnLocaleGroup.kLocaleGroupPlaylist,  // Locale group
                    GnLanguage.kLanguageEnglish,         // Language 
                    GnRegion.kRegionDefault,             // Region 
                    GnDescriptor.kDescriptorSimplified,  // Descriptor 
                    user,                                // User 
                    null                                 // locale Events object 
                    );

                locale.SetGroupDefault();
            }
        }


        /***************************************************************************
         *
         *    PrintPlaylistMorelikethisOptions
         *
         *    The following illustrates how to get the various morelikethis options.
         *
         ***************************************************************************/
        private static void
        PrintPlaylistMorelikethisOptions(GnPlaylistCollection playlistCollection)
        {
            uint value;

            value = playlistCollection.MoreLikeThisOptions().MaxTracks();              
            Console.WriteLine(" Max tracks :" + value);

            value = playlistCollection.MoreLikeThisOptions().MaxPerAlbum();              
            Console.WriteLine(" Max results per album, :" + value);

            value = playlistCollection.MoreLikeThisOptions().MaxPerArtist();          
            Console.WriteLine(" Max results per artist:" + value);
        }

        /***************************************************************************
         *
         *    PlaylistCollectionPopulate
         *
         *    Here we are doing basic MusicID queries on CDTOCs to populate a
         *    Playlist Collection Summary.
         *    Any GNSDK result GDO can be used for Collection Summary
         *    population.
         *
         ***************************************************************************/
        private static void
        PlaylistCollectionPopulate(GnUser user, GnPlaylistCollection playlistCollection)
        {
            uint countOrdinal = 0;
            string[] inputQueryTocs =  {
		        "150 13224 54343 71791 91348 103567 116709 132142 141174 157219 175674 197098 238987 257905",
		        "182 23637 47507 63692 79615 98742 117937 133712 151660 170112 189281",
		        "182 14035 25710 40955 55975 71650 85445 99680 115902 129747 144332 156122 170507",
		        "150 10705 19417 30005 40877 50745 62252 72627 84955 99245 109657 119062 131692 141827 152207 164085 173597 187090 204152 219687 229957 261790 276195 289657 303247 322635 339947 356272",
		        "150 14112 25007 41402 54705 69572 87335 98945 112902 131902 144055 157985 176900 189260 203342",
		        "150 1307 15551 31744 45022 57486 72947 85253 100214 115073 128384 141948 152951 167014",
		        "183 69633 96258 149208 174783 213408 317508",
		        "150 19831 36808 56383 70533 87138 105157 121415 135112 151619 169903 189073",
		        "182 10970 29265 38470 59517 74487 83422 100987 113777 137640 150052 162445 173390 196295 221582",
		        "150 52977 87922 128260 167245 187902 215777 248265",
		        "183 40758 66708 69893 75408 78598 82983 87633 91608 98690 103233 108950 111640 117633 124343 126883 132298 138783 144708 152358 175233 189408 201408 214758 239808",
		        "150 92100 135622 183410 251160 293700 334140",
		        "150 17710 33797 65680 86977 116362 150932 166355 183640 193035",
		        "150 26235 51960 73111 93906 115911 142086 161361 185586 205986 227820 249300 277275 333000",
		        "150 1032 27551 53742 75281 96399 118691 145295 165029 189661 210477 232501 254342 282525",
		        "150 26650 52737 74200 95325 117675 144287 163975 188650 209350 231300 253137 281525 337875",
		        "150 19335 35855 59943 78183 96553 111115 125647 145635 163062 188810 214233 223010 241800 271197",
		        "150 17942 32115 47037 63500 79055 96837 117772 131940 148382 163417 181167 201745",
		        "150 17820 29895 41775 52915 69407 93767 105292 137857 161617 171547 182482 204637 239630 250692 282942 299695 311092 319080",
		        "182 21995 45882 53607 71945 80495 94445 119270 141845 166445 174432 187295 210395 230270 240057 255770 277745 305382 318020 335795 356120",
		        "187 34360 64007 81050 122800 157925 195707 230030 255537 279212 291562 301852 310601",
		        "150 72403 124298 165585 226668 260273 291185"
	        };

            int count = inputQueryTocs.Count();

            Console.Write("Populating Collection Summary from sample TOCs");

            /* Create the MusicId object to TOC lookups */
            GnMusicId musicid = new GnMusicId(user);

            /* Set the option for retrieving DSP attributes.
            Note: Please note that these attributes are entitlements to your user id. You must have them enabled in your licence.
            */
            musicid.Options().LookupData(GnLookupData.kLookupDataSonicData, true);
            /*
            Set the option for retrieving Playlist attributes.
            Note: Please note that these attributes are entitlements to your user id. You must have them enabled in your licence.
            */
            musicid.Options().LookupData(GnLookupData.kLookupDataPlaylist, true);

            if (user.Options().LookupMode() == GnLookupMode.kLookupModeLocal)
            {
                Console.Write(" LOCAL lookup...");
            }
            else
            {
                Console.Write(" ONLINE lookup...");
            }

            foreach (string toc in inputQueryTocs)
            {
                // Find album
                GnResponseAlbums responseAlbums = musicid.FindAlbums(toc);

                GnAlbum album = responseAlbums.Albums.at(0).Current;

                /*  Add MusicID result to Playlist   */
                uint trackCount = album.Tracks.count();

                /*  To make playlist of tracks we add each and every track in the album to the collection summary */
                for (uint trackOrdinal = 1; trackOrdinal <= trackCount; ++trackOrdinal)
                {
                    GnTrack track = album.Tracks.at(trackOrdinal - 1).Current;

                    /* create a unique ident for every track that is added to the playlist.
                       Ideally the ident allows for the identification of which track it is.
                       e.g. path/filename.ext , or an id that can be externally looked up.
                    */
                    string uniqueIdent = countOrdinal + "_" + trackOrdinal;

                    /*
                        Add the the Album and Track GDO for the same ident so that we can
                        query the Playlist Collection with both track and album level attributes.
                    */
                    playlistCollection.Add(uniqueIdent, album);
                    playlistCollection.Add(uniqueIdent, track);

                    Console.Write("..");
                }
                countOrdinal++;
            }


            /* count the albums recognized */
            uint identCount = playlistCollection.MediaIdentifiers.count();
            Console.WriteLine("\n Recognized " + identCount + " tracks out of " + count + " Album TOCS");

            Console.WriteLine(" Finished Recognition ");
        }

        /***************************************************************************
         *
         *    PlaylistCollectionCreate
         *
         *    Here we attempt to load an existing Playlist Collection Summary from the GNSDK
         *    storage if one was previously stored. If not, we create a new Collection Summary
         *    (which initially is empty) and populate it with media. We then store this
         *    Collection Summary in the GNSDK storage.
         *
         ***************************************************************************/
        private static GnPlaylistCollection
        PlaylistCollectionCreate(GnUser user)
        {
            /* Initialize the Playlist Library */
            GnPlaylistStorage plStorage = new GnPlaylistStorage();

            /* Specify the location for our collection store. */
            plStorage.Location(".");

            uint count = plStorage.Names.count();
            Console.WriteLine("\nCurrently stored collections :" + count);

            GnPlaylistCollection playlistCollection;
            if (count == 0)
            {
                Console.WriteLine("Creating a new collection");
                playlistCollection = new GnPlaylistCollection("sample_collection");

                PlaylistCollectionPopulate(user, playlistCollection);

                Console.WriteLine("\nStoring collection... ");
                plStorage.Store(playlistCollection);
            }

            /* get the count again */
            count = plStorage.Names.count();
            Console.WriteLine("Currently stored collections :" + count);

            /* get the first collection */
            string collectionName = plStorage.Names.GetEnumerator().Current;
            playlistCollection = plStorage.Load(collectionName);
            Console.Write(" Loading Collection '" + collectionName + "' from store");

            return playlistCollection;
        }
                
        /***************************************************************************
         *
         *    PlaylistGetAttributeValue
         *
         ***************************************************************************/

        private static void
        PlaylistGetAttributeValue(GnPlaylistAttributes gdoAttr)
        {
            /* Album name */
            if (gdoAttr.AlbumName != "")
                Console.WriteLine("\n\t\tGN_AlbumName:" + gdoAttr.AlbumName);

            /* Artist name */
            if (gdoAttr.ArtistName != "")
                Console.WriteLine("\t\tGN_ArtistName:" + gdoAttr.ArtistName);

            /* Artist Type */
            if (gdoAttr.ArtistType != "")
                Console.WriteLine("\t\tGN_ArtistType:" + gdoAttr.ArtistType);

            /*Artist Era */
            if (gdoAttr.Era != "")
                Console.WriteLine("\t\tGN_Era:" + gdoAttr.Era);

            /*Artist Origin */
            if (gdoAttr.Origin != "")
                Console.WriteLine("\t\tGN_Origin:" + gdoAttr.Origin);

            /* Mood */
            if (gdoAttr.Mood != "")
                Console.WriteLine("\t\tGN_Mood:" + gdoAttr.Mood);

            /*Tempo*/
            if (gdoAttr.Tempo != "")
                Console.WriteLine("\t\tGN_Tempo:" + gdoAttr.Tempo);
        }

        /***************************************************************************
        *
        *    DoPlaylistMorelikethis
        *
        *    The following illustrates how to get the various morelikethis options.
        *
        ***************************************************************************/
        private static void
        DoPlaylistMorelikethis(GnUser user, GnPlaylistCollection playlistCollection)
        {
            /*
             A seed gdo can be any recognized media gdo.
             In this example we are using the a gdo from a random track in the playlist collection summary
             */
            GnPlaylistIdentifier identifier = playlistCollection.MediaIdentifiers.at(3).Current;

            GnPlaylistAttributes data = playlistCollection.Attributes(user, identifier);

            Console.Write("\n MoreLikeThis tests\n MoreLikeThis Seed details:");

            PlaylistGetAttributeValue( data);

            /* Generate a more Like this with the default settings */
            Console.WriteLine("\n MoreLikeThis with Default Options \n");

            /* Print the default More Like This options */
            PrintPlaylistMorelikethisOptions(playlistCollection);

            GnPlaylistResult playlistResult = playlistCollection.GenerateMoreLikeThis(user, data);

            EnumeratePlaylistResults(user, playlistCollection, playlistResult);

            /* Generate a more Like this with the custom settings */
            Console.WriteLine("\n MoreLikeThis with Custom Options \n");

            /* Change the possible result set to be a maximum of 30 tracks.*/
            playlistCollection.MoreLikeThisOptions().MaxTracks(30);

            /* Change the max per artist to be 20 */
            playlistCollection.MoreLikeThisOptions().MaxPerArtist(20);

            /* Change the max per album to be 5 */
            playlistCollection.MoreLikeThisOptions().MaxPerAlbum(5);

            /* Print the customized More Like This options */
            PrintPlaylistMorelikethisOptions(playlistCollection);

            playlistResult = playlistCollection.GenerateMoreLikeThis(user, data);

            EnumeratePlaylistResults(user, playlistCollection, playlistResult);
        }

        /***************************************************************************
         *
         *    EnumeratePlaylistResults
         *
         *    The following illustrates how to get each  ident and its associated
         *    GDO from a results handle.
         *
         ***************************************************************************/
        private static void
        EnumeratePlaylistResults(GnUser user, GnPlaylistCollection playlistCollection, GnPlaylistResult playlistResult)
        {
            GnPlaylistAttributes gdoAttr = null;
            string ident = null;
            string collectionName = null;
            uint countOrdinal = 0;
            uint resultsCount = 0;
            GnPlaylistCollection tempCollection = null;

            resultsCount = playlistResult.Identifiers.count();

            Console.WriteLine("Generated Playlist: " + resultsCount);

            GnPlaylistResultIdentEnumerable playlistResultIdentEnumerable = playlistResult.Identifiers;
            foreach (GnPlaylistIdentifier playlistIdentifier in playlistResultIdentEnumerable)
            {
                collectionName = playlistIdentifier.CollectionName;
                ident = playlistIdentifier.MediaIdentifier;

                Console.Write("    " + ++countOrdinal + ": " + ident + " Collection Name:" + collectionName);

                /*	The following illustrates how to get a collection handle
                    from the collection name string in the results enum function call.
                    It ensures that Joined collections as well as non joined collections will work with minimal overhead.
                    */
                tempCollection = playlistCollection.JoinFindByName(collectionName);

                gdoAttr = tempCollection.Attributes(user, playlistIdentifier);

                PlaylistGetAttributeValue(gdoAttr);

            }

        }

        /***************************************************************************
         *
         *    DoPlaylistPdl
         *
         *    Here we perform playlist generation from our created Collection Summary via
         *    custom PDL (Playlist Definition Language) statements.
         *
         ***************************************************************************/
        private static void
        DoPlaylistPdl(GnUser user, GnPlaylistCollection playlistCollection)
        {
            uint stmtIdx = 0;
            uint pdlstmtCount = 0;

            string[] pdlStatements =
	            {
		            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 0",     /* like pop with a low score threshold (0)*/
		            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 300",   /* like pop with a reasonable score threshold (300)*/
		            "GENERATE PLAYLIST WHERE GN_Genre = 2929",              /* exactly pop */
		            "GENERATE PLAYLIST WHERE GN_Genre = 2821",              /* exactly rock */
		            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 0",     /* like rock with a low score threshold (0)*/
		            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 300",   /* like rock with a reasonable score threshold (300)*/
		            "GENERATE PLAYLIST WHERE (GN_Genre LIKE SEED) > 300 LIMIT 20 RESULTS",
		            "GENERATE PLAYLIST WHERE (GN_ArtistName LIKE 'Green Day') > 300 LIMIT 20 RESULTS, 2 PER GN_ArtistName;",
	            };
            GnPlaylistAttributes gdoSeed = null;

            pdlstmtCount = (uint)pdlStatements.Count();
            gdoSeed = playlistCollection.Attributes(user, playlistCollection.MediaIdentifiers.at(4).Current);
            for (stmtIdx = 0; stmtIdx < pdlstmtCount; stmtIdx++)
            {
                Console.WriteLine("\n PDL " + stmtIdx + ": " + pdlStatements[stmtIdx] + " ");
                GnError error = playlistCollection.StatementValidate(pdlStatements[stmtIdx]);
                if (error.ErrorCode() == 0)
                {
                    /*
                        A seed gdo can be any recognized media gdo.
                        In this example we are using the a gdo from a track in the playlist collection summary
                    */
                    GnPlaylistResult playlistResult = playlistCollection.GeneratePlaylist(user, pdlStatements[stmtIdx], gdoSeed);

                    EnumeratePlaylistResults(user, playlistCollection, playlistResult);
                }

            }
        }

        /***************************************************************************
         *
         *    PerformSamplePlaylist
         *
         *    Our top level function that calls the required Playlist routines
         *
         ***************************************************************************/
        private static void
        PerformSamplePlaylist(GnUser user)
        {
            GnPlaylistCollection playlistCollection = PlaylistCollectionCreate(user);

            /* demonstrate PDL usage */
            DoPlaylistPdl(user, playlistCollection);

            /* demonstrate MoreLike usage*/
            DoPlaylistMorelikethis(user, playlistCollection);
        }

        /******************************************************************
        *
        *    MAIN
        *
        ******************************************************************/
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
			        return result;
		        }
	        }
	        else
	        {
		        Console.Write("\nUsage:  clientId clientIdTag license gnsdkLibraryPath lookupMode\n");
		        return result;
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

                LoadLocale(user);

                // Perform a sample album TOC query
                PerformSamplePlaylist(user);

                // Success 
                result = SUCCESS; 
            }
            // All gracenote sdk objects throws GnException
            catch (GnException e)
            {
                Console.WriteLine("Error Code           :: " + e.ErrorCode);
                Console.WriteLine("Error Description    :: " + e.ErrorDescription);
                Console.WriteLine("Error API            :: " + e.ErrorAPI);
                Console.WriteLine("Source Error Code    :: " + e.SourceErrorCode);
                Console.WriteLine("Source Error Module  :: " + e.SourceErrorModule);
            }

            return result;
        }
    }
}
