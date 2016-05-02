/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: VideoSearchSuggestion.cs
 *  Description:
 *  This sample shows basic use of FindSuggestions() call
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
using System.Diagnostics;
namespace Sample
{
	public class VideoSearchSuggestion
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
		private static 
        void DoSampleSuggestionSearch(GnUser user)
		{
			uint match = 0;
			uint moreResults = 1;
			uint pageStart = 1;
			uint pageCount = 20;
			string suggestionTitle = null;
			string searchText = "spider";

			Console.WriteLine("\n*****Sample VideoID Suggestion Lookup*****\n");
			try
			{
				while (1 == moreResults)
				{

					moreResults = 0;

					GnVideo video = new GnVideo(user);

					/* Set the search options */
					video.Options().ResultRangeStart(pageStart);
					video.Options().ResultCount(pageCount);

					/* Set the input text and perform the search with no optional data passed to callback function */
					GnResponseVideoSuggestions responseVideoSuggestions = video.FindSuggestions(searchText, GnVideoSearchField.kSearchFieldProductTitle, GnVideoSearchType.kSearchTypeAnchored);

					/* Handle the results. Retrieve number of search terms in result */
					uint count = responseVideoSuggestions.ChildCount("gnsdk_val_suggestion_title" /*gnsdk_marshal.GNSDK_GDO_VALUE_SUGGESTION_TITLE*/);

					uint rangeStart = Convert.ToUInt32(responseVideoSuggestions.RangeStart);
					uint rangeEnd = Convert.ToUInt32(responseVideoSuggestions.RangeEnd);
					uint rangeCount = Convert.ToUInt32(responseVideoSuggestions.RangeTotal);

					if (count > 0)
						Console.WriteLine("\t" + rangeStart + " - " + rangeEnd + " of " + rangeCount + " suggestions for \'" + searchText + "\'");

					string type = responseVideoSuggestions.GetType();

					for (uint i = 1; i <= count; i++)
					{
						suggestionTitle = responseVideoSuggestions.SuggestionTitle(i);
						Console.WriteLine("\t" + ++match + ": " + suggestionTitle);
					}

					if (rangeCount > rangeEnd)
					{
						moreResults = 1;
						pageStart += pageCount;
					}
				}
			}
			catch (Exception e)
			{
				Debug.WriteLine("Exception Message: " + e.Message);
			}

		}

		static void
		Main(string[] args)
		{
			string licenseFile;
			string gnsdkLibraryPath;
			string clientId;
			string clientIdTag;
			string applicationVersion = "1.0.0.0";  /* Increment with each version of your app */
			GnLookupMode lookupMode;


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

				/* Do suggestion search */
				DoSampleSuggestionSearch(user);
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
