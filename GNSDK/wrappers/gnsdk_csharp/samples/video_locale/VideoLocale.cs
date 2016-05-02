/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: VideoLocale
 *  Description:
 *  This sample shows basic access of locale-dependent fields
 *
 *  Command-line Syntax:
 *  sample clientId clientIdTag license libPath
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
    public class VideoLocale
    {
        /// <summary>
        /// GnStatusEventsDelegate : override methods of this class to get delegate callbacks
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
                    GnLocaleGroup.kLocaleGroupVideo,     /* Locale group */
                    GnLanguage.kLanguageEnglish,         /* Language */
                    GnRegion.kRegionDefault,             /* Region */
                    GnDescriptor.kDescriptorSimplified,  /* Descriptor */
                    user,                                /* User */
                    null                                 /* locale Events object */
                    );

                locale.SetGroupDefault();
            }
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="user"></param>
        private static void
        DoWorkSearch(GnUser user)
        {
            string value         = null;
            /*string searchText    = "Harrison Ford";*/
            string serializedGDO = "WEcxA6R75JwbiGUIxLFZHBr4tv+bxvwlIMr0XK62z68zC+/kDDdELzwiHmBPkmOvbB4rYEY/UOOvFwnk6qHiLdb1iFLtVy44LfXNsTH3uNgYfSymsp9uL+hyHfrzUSwoREk1oX/rN44qn/3NFkEYa2FoB73sRxyRkfdnTGZT7MceHHA/28aWZlr3q48NbtCGWPQmTSrK";

            Console.WriteLine("\n*****Sample Video Work Search*****");

            using (LookupStatusEvents videoEvents = new LookupStatusEvents())
            {
                GnVideo      video           = new GnVideo(user, videoEvents);
                GnDataObject inpupdataobject = GnDataObject.Deserialize(serializedGDO);

                /* GnResponseVideoWork videoWorksResponse = video.FindWorks(searchText, GnVideoSearchField.kSearchFieldContributorName, GnVideoSearchType.kSearchTypeDefault); */
                GnResponseVideoWork videoWorksResponse = video.FindWorks(inpupdataobject);

                Console.WriteLine("\n\nNumber matches: " + videoWorksResponse.Works.count());

                /**********************************************
                *  Needs decision (match resolution) check
                **********************************************/
                if (videoWorksResponse.NeedsDecision)
                {
                    /**********************************************
                    * Resolve match here
                    **********************************************/
                }

                if (videoWorksResponse.Works.count() > 0)
                {
                    GnVideoWorkEnumerable videoWorkEnumerable = videoWorksResponse.Works;

                    foreach (GnVideoWork work in videoWorkEnumerable)
                    {
                        /*Work title*/
                        GnTitle workTitle = work.OfficialTitle;
                        value = workTitle.Display;
                        if (value != null && value != "")
                            Console.WriteLine("\nTitle: " + value);

                        /*Origin info*/
                        value = work.Origin(GnDataLevel.kDataLevel_1);
                        if (value != null && value != "")
                            Console.WriteLine("\nOrigin1: " + value);
                        value = work.Origin(GnDataLevel.kDataLevel_2);
                        if (value != null && value != "")
                            Console.WriteLine("\nOrigin2: " + value);
                        value = work.Origin(GnDataLevel.kDataLevel_3);
                        if (value != null && value != "")
                            Console.WriteLine("\nOrigin3: " + value);
                        value = work.Origin(GnDataLevel.kDataLevel_4);
                        if (value != null && value != "")
                            Console.WriteLine("\nOrigin4: " + value);

                        /*Genre info*/
                        value = work.Genre(GnDataLevel.kDataLevel_1);
                        if (value != null && value != "")
                            Console.WriteLine("\nGenre1: " + value);
                        value = work.Genre(GnDataLevel.kDataLevel_2);
                        if (value != null && value != "")
                            Console.WriteLine("\nGenre2: " + value);
                        value = work.Genre(GnDataLevel.kDataLevel_3);
                        if (value != null && value != "")
                            Console.WriteLine("\nGenre3: " + value);

                        /*Video mood
                           value = work.VideoMood;
                           if (value != null && value != "")
                            Console.WriteLine("\nMood: " + value);*/

                        /* Primary rating */
                        GnRating rating = work.Rating();
                        value = rating.Rating;
                        if (value != null && value != "")
                        {
                            Console.Write("\nRating: " + value);

                            value = rating.RatingType;
                            if (value != null && value != "")
                                Console.Write(" [" + value + "]");

                            value = rating.RatingDesc();
                            if (value != null && value != "")
                                Console.WriteLine(" - " + value);

                            value = rating.RatingReason;
                            if (value != null && value != "")
                                Console.WriteLine(" Reason: " + value);

                            Console.WriteLine();
                        }

                        value = work.PlotSynopsis;
                        if (value != null && value != "")
                            Console.WriteLine("Plot synopsis: " + work.PlotSynopsis);

                        GnVideoCreditEnumerable videoCreditEnumerable = work.VideoCredits;

                        foreach (GnVideoCredit credit in videoCreditEnumerable)
                        {
                            /* Display name
                               GnName name = credit.OfficialName;
                               value = name.Display;
                               if (value != null && value != "")
                                Console.WriteLine("\nName: " + value);*/

                            /* Genres */
                            value = credit.Genre(GnDataLevel.kDataLevel_1);
                            if (value != null && value != "")
                                Console.WriteLine("\n\tGenre1: " + value);
                            value = credit.Genre(GnDataLevel.kDataLevel_2);
                            if (value != null && value != "")
                                Console.WriteLine("\n\tGenre2: " + value);
                            value = credit.Genre(GnDataLevel.kDataLevel_3);
                            if (value != null && value != "")
                                Console.WriteLine("\n\tGenre3: " + value);

                        }
                    }
                }
            }
        }


    
        /// <summary>
        /// 
        /// </summary>
        /// <param name="args"></param>
        static void
        Main(string[] args)
        {
            string  licenseFile;
            string  gnsdkLibraryPath;
            string  clientId;
            string  clientIdTag;
            string  applicationVersion = "1.0.0.0";  /* Increment with each version of your app */
            GnLookupMode  lookupMode;


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
                    return;
                }
            }
            else
            {
                Console.Write("\nUsage:  clientId clientIdTag license gnsdkLibraryPath lookupMode\n");
                return;
            }

            /* GNSDK initialization */
            try
            {
                /* Initialize SDK */
                GnManager manager = new GnManager(gnsdkLibraryPath, licenseFile, GnLicenseInputMode.kLicenseInputModeFilename);


                /* Display SDK version */
                Console.WriteLine("\nGNSDK Product Version : " + manager.ProductVersion + " \t(built " + manager.BuildDate + ")");

                /* Enable GNSDK logging */
                GnLog sampleLog = new GnLog("sample.log", null);
                GnLogFilters filters = new GnLogFilters();
                sampleLog.Filters(filters.Error().Warning());               // Include only error and warning entries 
                GnLogColumns columns = new GnLogColumns();
                sampleLog.Columns(columns.All());			                // Add all columns to log: timestamps, thread IDs, etc 
                GnLogOptions options = new GnLogOptions();
                sampleLog.Options(options.MaxSize(0).Archive(false));       // Max size of log: 0 means a new log file will be created each run. Archive option will save old log else it will regenerate the log each time 
                sampleLog.Enable(GnLogPackageType.kLogPackageAllGNSDK);     // Include entries for all packages and subsystems 


                /*
                 *    Load existing user handle, or register new one.
                 */
                GnUser user = GetUser(manager, clientId, clientIdTag, applicationVersion, lookupMode);

                /* Set locale with desired Group, Language, Region and Descriptor
                 * Set the 'locale' to return locale-specific results values. This examples loads an English locale.
                 */
                LoadLocale(user);

                /* Lookup AV Works and display */
                DoWorkSearch(user);
            }
            catch (GnException e)
            {
                Console.WriteLine("Error API            :: " + e.ErrorAPI);
                Console.WriteLine("Error Description    :: " + e.ErrorDescription);
                Console.WriteLine("Error Code           :: " + e.ErrorCode);
            }
        }
    }
}

