/*
 * Copyright (c) 2000-2013 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: VideoProductsMetadata.cs
 *  Description:
 *  This sample shows accessing product metadata: Disc > Side >  Layer >  Feature > Chapters.
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
	public class VideoProductMetadata
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
				Console.Write("\nPerforming Video Product Metadata ...\t");
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
		/// <param name="videoResponse"></param>
		/// <param name="user"></param>
		private static void
		DisplayMultipleProduct(GnResponseVideoProduct videoResponse, GnUser user)
		{
			int count = 0;

			/*
			 * LOOP THROUGH MATCHES
			 *
			 * Note that the GDO accessors below are "ordinal" based, not index based.  so the 'first' of
			 * anything has a one-based ordinal of '1' - "not" an index of '0'
			 */

			GnVideoProductEnumerable videoProductEnumerable = videoResponse.Products;

			foreach (GnVideoProduct videoProduct in videoProductEnumerable)
			{
				Console.WriteLine("\nMatch : " + ++count);
				DispalyBasicData(videoProduct);
			}
		}

		/*-----------------------------------------------------------------------------
		 *  DisplayChapters
		 */
		private static void
		DisplayChapters(GnVideoFeature gnVideoFeature)
		{
			string value = null;
			/* Get chapter count */
			uint chapterCount = gnVideoFeature.Chapters.count();

			Console.WriteLine("\t\t\tchapters: " + chapterCount);

			GnVideoChapterEnumerable chapterEnumerable = gnVideoFeature.Chapters;

			foreach (GnVideoChapter gnVideoChapter in chapterEnumerable)
			{
				/* Get chapter number */
				uint chapternumStr = gnVideoChapter.Ordinal;

				/* Get the chapter title name GDO */
				GnTitle gnChpaterTitle = gnVideoChapter.OfficialTitle;

				value = gnChpaterTitle.Display;
				if (value != null && value != "")
					Console.Write("\t\t\t\t" + chapternumStr + ": " + value);

				uint duration = gnVideoChapter.Duration;

				if (duration > 0)
				{
					uint seconds = duration;
					uint minutes = seconds / 60;
					uint hours   = minutes / 60;
					seconds = seconds - (60 * minutes);
					minutes = minutes - (60 * hours);
					Console.WriteLine(" [" + hours.ToString("0") + ":" + minutes.ToString("00") + ":" + seconds.ToString("00") + "]");
				}

			} /* For each chapter */
		}

		/*-----------------------------------------------------------------------------
		 *  DisplayLayers
		 */
		private static void
		DisplayLayers(GnVideoSide side)
		{
			string value      = null;
			uint   layerCount = side.Layers.count();
			if (layerCount > 0)
				Console.WriteLine("\tNumber layers: " + layerCount);
			else
			{
				Console.WriteLine("\tNo layer data");
				return;
			}

			GnVideoLayerEnumerable layerEnumerable = side.Layers;

			foreach (GnVideoLayer gnVideoLayer in layerEnumerable)
			{
				/* Get the layer number */
				uint layerNumber = Convert.ToUInt32(gnVideoLayer.Ordinal);

				/* matched - was this the layer that matched the initial query input */
				string matched = null;

				if (!gnVideoLayer.Matched)
					matched = "";
				else
					matched = "MATCHED";

				Console.WriteLine("\t\tLayer " + layerNumber + " -------- " + matched);

				/* Get media type */
				value = gnVideoLayer.MediaType;
				if (value != null && value != "")
					Console.WriteLine("\t\tMedia type: " + value);

				/* Get TV system */
				value = gnVideoLayer.TvSystem;
				if (value != null && value != "")
					Console.WriteLine("\t\tTV system: " + value);

				/* Get region */
				value = gnVideoLayer.RegionCode;
				if (value != null && value != "")
					Console.WriteLine("\t\tRegion Code: " + value);
				value = gnVideoLayer.VideoRegion;
				if (value != null && value != "")
					Console.WriteLine("\t\tVideo Region: " + value);

				/* Get aspect ratio */
				value = gnVideoLayer.AspectRatio;
				if (value != null && value != "")
				{
					Console.Write("\t\tAspect ratio: " + value);

					/* Get aspect ration type */
					value = gnVideoLayer.AspectRatioType;
					if (value != null && value != "")
						Console.Write(" [" + value + "]");
					Console.WriteLine();
				}

				/* Get number of layer features */
				uint featureCount = gnVideoLayer.Features.count();
				if (featureCount > 0)
					Console.WriteLine("\t\tFeatures: " + featureCount);

				/* Loop thru features */
				GnVideoFeatureEnumerable videoFeatureEnumerable = gnVideoLayer.Features;
				foreach (GnVideoFeature gnVideoFeature in videoFeatureEnumerable)
				{
					/* Get feature number */
					uint featureNumber = gnVideoFeature.Ordinal;

					/* Get matched */
					if (!gnVideoFeature.Matched)
						matched = "";
					else
						matched = "MATCHED";

					Console.WriteLine("\n\t\t\tFeature " + featureNumber + " -------- " + matched);

					/* Get the feature title name GDO */
					GnTitle gnTitle = gnVideoFeature.OfficialTitle;

					/* Get title */
					value = gnTitle.Display;
					if (value != null && value != "")
						Console.WriteLine("\t\t\tFeature title: " + value);

					uint duration = gnVideoFeature.Duration;

					if (duration > 0)
					{
						uint seconds = duration;
						uint minutes = seconds / 60;
						uint hours   = minutes / 60;
						seconds = seconds - (60 * minutes);
						minutes = minutes - (60 * hours);
						Console.WriteLine("\t\t\tLength: " + hours.ToString("0") + ":" + minutes.ToString("00") + ":" + seconds.ToString("00"));
					}

					/* Aspect ratio */
					value = gnVideoFeature.AspectRatio;
					if (value != null && value != "")
					{
						Console.Write("\t\t\tAspect ratio: " + value);

						/* Aspect ratio type */
						value = gnVideoFeature.AspectRatioType;
						if (value != null && value != "")
							Console.Write(" [" + value + "]");
						Console.WriteLine();
					}
					/*
					 * Note: Genre display strings come from a genre hierarchy, so you can choose what level
					 * of granularity to display.  GNSDK_GDO_VALUE_GENRE_LEVEL1 are the top level genres and
					 * the most general, GNSDK_GDO_VALUE_GENRE_LEVEL2 is the mid-level genre and the most
					 * granular genre is GNSDK_GDO_VALUE_GENRE_LEVEL#.
					 */

					/* Feature genre(s)  */
					value = gnVideoFeature.Genre(GnDataLevel.kDataLevel_1);
					if (value != null && value != "")
						Console.WriteLine("\t\t\tPrimary genre: " + value);

					/* Feature rating */
					GnRating gnFeatureRating = gnVideoFeature.Rating;
					value = gnFeatureRating.Rating;
					if (value != null && value != "")
					{
						Console.Write("\t\t\tRating: " + value);
						value = gnFeatureRating.RatingType;
						if (value != null && value != "")
							Console.Write(" [" + value + "]");
						value = gnFeatureRating.RatingDesc();
						if (value != null && value != "")
							Console.Write(" - " + value);
						Console.WriteLine();
					}

					/* Feature type */
					value = gnVideoFeature.VideoFeatureType;
					if (value != null && value != "")
						Console.WriteLine("\t\t\tFeature type: " + value);

					/* Video type */
					value = gnVideoFeature.VideoProductionType;
					if (value != null && value != "")
						Console.WriteLine("\t\t\tProduction type: " + value);

					/* feature plot */
					value = gnVideoFeature.PlotSummary;
					if (value != null && value != "")
						Console.WriteLine("\t\t\tPlot summary: " + value);
					value = gnVideoFeature.PlotSynopsis;
					if (value != null && value != "")
						Console.WriteLine("\t\t\tPlot synopsis: " + value);
					value = gnVideoFeature.PlotTagline;
					if (value != null && value != "")
						Console.WriteLine("\t\t\tTagline: " + value);

					DisplayChapters(gnVideoFeature);

				}

			}
		}

		/*-----------------------------------------------------------------------------
		 *  DisplayDiscInformation
		 */
		private static void
		DisplayDiscInformation(GnVideoProduct product)
		{
			/* Get disc count */
			uint discCount = product.Discs.count();
			Console.WriteLine("\nDiscs:" + discCount);

			/* Discs in set */
			GnVideoDiscEnumerable discEnumerable = product.Discs;
			/* metadata::disc_iterator discItr = product.Discs().begin(); */

			foreach (GnVideoDisc disc in discEnumerable) /*Discs in set loop*/
			{
				/* Disc number */
				uint discNumber = disc.Ordinal;
				/* Matched --  */
				string discMatch = null;

				if (!disc.Matched)
					discMatch = "";
				else
					discMatch = "MATCHED";

				Console.WriteLine("disc " + discNumber + " -------- " + discMatch);

				GnTitle discTitle = disc.OfficialTitle;
				Console.WriteLine("\tTitle: " + discTitle.Display);

				/* Count the number of sides */
				uint sideCount = disc.Sides.count();

				Console.WriteLine("\tNumber sides: " + sideCount);

				/* Sides in set - sides details */
				GnVideoSideEnumerable sideEnumerable = disc.Sides;

				foreach (GnVideoSide side in sideEnumerable) /*side loop*/
				{
					/* Side number */
					uint sideNumber = side.Ordinal;
					/* Matched -- */
					string sideMatch = null;
					if (!side.Matched)
						sideMatch = "";
					else
						sideMatch = "MATCHED";

					Console.WriteLine("\tSide " + sideNumber + " -------- " + sideMatch);

					DisplayLayers(side);

				} /*side loop*/

			} /*Discs in set loop*/
		}

		/*-----------------------------------------------------------------------------
		 *  DispalyBasicData
		 */
		private static void
		DispalyBasicData(GnVideoProduct videoProduct)
		{
			string value = null;
			/* Get the video title GDO */
			GnTitle productTitle = videoProduct.OfficialTitle;

			/* Display video title */
			Console.WriteLine("Title: " + productTitle.Display);

			/* Video edition */
			value = productTitle.StringValue("gnsdk_val_edition" /*gnsdk_marshal.GNSDK_GDO_VALUE_EDITION*/);
			if (value != null && value != "")
				Console.WriteLine("Edition: " + value);

			/* Video type */
			value = videoProduct.VideoProductionType;
			if (value != null && value != "")
				Console.WriteLine("Production type: " + value);

			/* Video original release */
			value = videoProduct.DateOriginalRelease;
			if (value != null && value != "")
				Console.WriteLine("Orig release: " + value);

			/* Rating */
			GnRating rating = videoProduct.Rating;
			value = rating.Rating;
			if (value != null && value != "")
			{
				Console.Write("Rating: " + value);

				value = rating.RatingType;
				if (value != null && value != "")
					Console.Write(" [" + value + "]");

				value = rating.RatingDesc();
				if (value != null && value != "")
					Console.WriteLine(" - " + value);

				Console.WriteLine();
			}
			/* Video release year */
			value = videoProduct.DateRelease;
			if (value != null && value != "")
				Console.WriteLine("Release: " + value);

			/* Discs in set */
			Console.WriteLine("Discs: " + videoProduct.Discs.count());
		}

		/*-----------------------------------------------------------------------------
		 *  DisplaySingleProduct
		 */
		private static void
		DisplaySingleProduct(GnResponseVideoProduct videoResponse, GnUser user)
		{
			/* Get the current product from the response */
			GnVideoProductEnumerable productEnumerable = videoResponse.Products;
			GnVideoProductEnumerator productEnumerator = productEnumerable.GetEnumerator();
			GnVideoProduct           product           = productEnumerator.Current;
			/* foreach (GnVideoProduct product in productEnumerable) */
			{
				DispalyBasicData(product);

				GnVideoProduct fullVideoProduct = product;
				if (!product.IsFullResult)
				{
					/* Get a GDO with full metadata */
					GnVideo                gnVideo  = new GnVideo(user);
					GnResponseVideoProduct response = gnVideo.FindProducts(product);
					fullVideoProduct = response.Products.at(0).next();
				}

				DisplayDiscInformation(fullVideoProduct);
			}

		}

		/*-----------------------------------------------------------------------------
		 *  DoProductSearch
		 */
		private static void
		DoProductSearch(GnUser user)
		{
			string searchTitle = "Star";

			Console.WriteLine("\n*****Sample Title Search: '" + searchTitle + "'*****");

			using (LookupStatusEvents videoEvents = new LookupStatusEvents())
			{
				GnVideo video = new GnVideo(user, videoEvents);

				/* Setting range values */
				video.Options().ResultRangeStart(1);
				video.Options().ResultCount(20);

				GnResponseVideoProduct videoResponse = video.FindProducts(searchTitle, GnVideoSearchField.kSearchFieldProductTitle, GnVideoSearchType.kSearchTypeDefault);

				if (1 == videoResponse.Products.count())
				{
					DisplaySingleProduct(videoResponse, user);
				}
				else
				{
					/* We now have 1-n matches needing resolution
					   DisplayMultipleProduct(videoResponse, user);*/

					/* Typically the user would choose one (or none) of the presented choices.
					 * For this simplified sample, just pick the first choice  */

					DisplaySingleProduct(videoResponse, user);

				}
			}
		}

		/*-----------------------------------------------------------------------------
		 *  Main
		 */
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

				/* Lookup products and display */
				DoProductSearch(user);
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

