/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: video_product_metadata/main.c
 *  Description:
 *  This sample shows accessing product metadata: Disc > Side >  Layer >  Feature > Chapters.
 *
 *  Command-line Syntax:
 *  sample client_id client_id_tag license
 */

/* GNSDK headers
 *
 * Define the modules your application needs.
 * These constants enable inclusion of headers and symbols in gnsdk.h.
 */
#define GNSDK_VIDEO             1
#define GNSDK_STORAGE_SQLITE    1
#include "gnsdk.h"

/* Standard C headers - used by the sample app, but not required for GNSDK */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**********************************************
*    Local Function Declarations
**********************************************/
static int
_do_sample_title_search(
	gnsdk_user_handle_t user_handle, gnsdk_cstr_t title
	);

static int
_init_gnsdk(
	const char*          client_id,
	const char*          client_id_tag,
	const char*          client_app_version,
	const char*          license_path,
	gnsdk_user_handle_t* p_user_handle
	);

static void
_shutdown_gnsdk(
	gnsdk_user_handle_t user_handle
	);

/******************************************************************
*
*    MAIN
*
******************************************************************/
int
main(int argc, char* argv[])
{
	gnsdk_user_handle_t user_handle        = GNSDK_NULL;
	const char*         client_id          = NULL;
	const char*         client_id_tag      = NULL;
	const char*         client_app_version = "1";  /* Increment with each version of your app */
	const char*         license_path       = NULL;
	int                 rc                 = 0;


	/* Client ID, Client ID Tag and License file must be provided.
	 * The last member of argv is used by many samples to determine whether to
	 * use local or online lookups. This sample only supports online queries
     * so this argument is not required and is ignored if it is present.
	 */
	if ((argc == 4) || (argc == 5))
	{
		client_id     = argv[1];
		client_id_tag = argv[2];
		license_path  = argv[3];

		/* Initialize GNSDK     */
		rc = _init_gnsdk(
			client_id,
			client_id_tag,
			client_app_version,
			license_path,
			&user_handle
			);
		if (0 == rc)
		{
			/* Perform a sample title search */
			rc = _do_sample_title_search(user_handle, "Star");

			/* Clean up and shutdown */
			_shutdown_gnsdk(user_handle);
		}
	}
	else
	{
		printf("\nUsage:\n%s clientid clientidtag license\n", argv[0]);
		rc = -1;
	}

	return rc;

}    /* main() */


/******************************************************************
 *
 *    _DISPLAY_LAST_ERROR
 *
 *    Echo the error and information.
 *
 *****************************************************************/
static void
_display_last_error(
	int line_num
	)
{
	/* Get the last error information from the SDK */
	const gnsdk_error_info_t* error_info = gnsdk_manager_error_info();


	/* Error_info will never be GNSDK_NULL.
	 * The SDK will always return a pointer to a populated error info structure.
	 */
	printf(
		"\nerror from: %s()  [on line %d]\n\t0x%08x %s",
		error_info->error_api,
		line_num,
		error_info->error_code,
		error_info->error_description
		);

} /* display_last_error() */


/*********************************************************************************
 *
 *    _SET_LOCALE
 *
 *  Set application locale. Note that this is only necessary if you are accessing
 *  locale-dependant fields such as genre, mood, origin, era, etc. Your app
 *  may or may not be accessing ocale_dependent fields, but it does not hurt
 *  to do this initialization as a matter of course .
 *
 **********************************************************************************/
static int
_set_locale(
	gnsdk_user_handle_t user_handle
	)
{
	gnsdk_locale_handle_t locale_handle = GNSDK_NULL;
	gnsdk_error_t         error         = GNSDK_SUCCESS;
	int                   rc            = 0;


	error = gnsdk_manager_locale_load(
		GNSDK_LOCALE_GROUP_VIDEO,            /* Locale group */
		GNSDK_LANG_ENGLISH,                  /* Languae */
		GNSDK_REGION_DEFAULT,                /* Region */
		GNSDK_DESCRIPTOR_SIMPLIFIED,         /* Descriptor */
		user_handle,                         /* User handle */
		GNSDK_NULL,                          /* User callback function */
		0,                                   /* Optional data for user callback function */
		&locale_handle                       /* Return handle */
		);
	if (GNSDK_SUCCESS == error)
	{
		/* Setting the 'locale' as default
		 * If default not set, no locale-specific results would be available
		 */
		error = gnsdk_manager_locale_set_group_default(locale_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}

		/* The manager will hold onto the locale when set as default
		 * so it's ok to release our reference to it here
		 */
		gnsdk_manager_locale_release(locale_handle);
	}
	else
	{
		_display_last_error(__LINE__);
		rc = -1;
	}

	return rc;

} /* _set_locale() */


/******************************************************************
*
*    _DISPLAY_GNSDK_PRODUCT_INFO
*
*    Display product version information
*
******************************************************************/
static void
_display_gnsdk_product_info(void)
{
	/* Display GNSDK Version infomation */
	printf("\nGNSDK Product Version    : %s \t(built %s)\n", gnsdk_manager_get_product_version(), gnsdk_manager_get_build_date());

}    /* _display_gnsdk_product_info() */


/******************************************************************
*
*    _ENABLE_LOGGING
*
*  Enable logging for the SDK. Not used by Sample App. This helps
*  Gracenote debug your app, if necessary.
*
******************************************************************/
static int
_enable_logging(void)
{
	gnsdk_error_t error = GNSDK_SUCCESS;
	int           rc    = 0;


	error = gnsdk_manager_logging_enable(
		"sample.log",                                            /* Log file path */
		GNSDK_LOG_PKG_ALL,                                       /* Include entries for all packages and subsystems */
		GNSDK_LOG_LEVEL_ERROR|GNSDK_LOG_LEVEL_WARNING,           /* Include only error and warning entries */
		GNSDK_LOG_OPTION_ALL,                                    /* All logging options: timestamps, thread IDs, etc */
		0,                                                       /* Max size of log: 0 means a new log file will be created each run */
		GNSDK_FALSE                                              /* GNSDK_TRUE = old logs will be renamed and saved */
		);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		rc = -1;
	}

	return rc;

} /* _enable_logging() */


/*****************************************************************************************
 *
 *    _GET_USER_HANDLE
 *
 *    Load existing user handle, or register new one.
 *
 *    GNSDK requires a user handle instance to perform queries.
 *    User handles encapsulate your Gracenote provided Client ID which is unique for your
 *    application. User handles are registered once with Gracenote then must be saved by
 *    your application and reused on future invocations.
 *
 *******************************************************************************************/
static int
_get_user_handle(
	const char*          client_id,
	const char*          client_id_tag,
	const char*          client_app_version,
	gnsdk_user_handle_t* p_user_handle
	)
{
	gnsdk_user_handle_t user_handle       = GNSDK_NULL;
	gnsdk_str_t         serialized_user   = GNSDK_NULL;
	gnsdk_error_t       error             = GNSDK_SUCCESS;
	char                user_filename[32] = {0};
	int                 rc                = 0;
	FILE*               file              = NULL;


	strcpy(user_filename, client_id);
	strcat(user_filename, "_user.txt");

	/* Do we have a user saved locally? */
	file = fopen(user_filename, "r");
	if (file)
	{
		gnsdk_char_t serialized_user_string[1024] = {0};

		fgets(serialized_user_string, 1024, file);

		/* Create the user handle from the saved user */
		error = gnsdk_manager_user_create(serialized_user_string, client_id, &user_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}

		fclose(file);
	}
	else
	{
		printf("\nInfo: No stored user - this must be the app's first run.\n");
	}

	/* If not, create new one*/
	if (GNSDK_NULL == user_handle)
	{
#if USE_LOCAL
		error = gnsdk_manager_user_register(GNSDK_USER_REGISTER_MODE_LOCALONLY, client_id, client_id_tag, client_app_version, &serialized_user);
#else
		error = gnsdk_manager_user_register(GNSDK_USER_REGISTER_MODE_ONLINE, client_id, client_id_tag, client_app_version, &serialized_user);
#endif
		if (GNSDK_SUCCESS == error)
		{
			/* save newly registered user for use next time */
			file = fopen(user_filename, "w");
			if (file)
			{
				fputs(serialized_user, file);
				fclose(file);
			}

			/* Create the user handle from the registered user */
			error = gnsdk_manager_user_create(serialized_user, client_id, &user_handle);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}

			gnsdk_manager_string_free(serialized_user);
		}
		else
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
	}

	if (rc == 0)
	{
		*p_user_handle = user_handle;
	}

	return rc;
} /* _get_user_handle() */


/****************************************************************************************
*
*    _INIT_GNSDK
*
*     Initializing the GNSDK is required before any other APIs can be called.
*     First step is to always initialize the Manager module, then use the returned
*     handle to initialize any modules to be used by the application.
*
*     For this sample, we also load a locale which is used by GNSDK to provide
*     appropriate locale-sensitive metadata for certain metadata values. Loading of the
*     locale is done here for sample convenience but can be done at anytime in your
*     application.
*
****************************************************************************************/
static int
_init_gnsdk(
	const char*          client_id,
	const char*          client_id_tag,
	const char*          client_app_version,
	const char*          license_path,
	gnsdk_user_handle_t* p_user_handle
	)
{
	gnsdk_manager_handle_t sdkmgr_handle = GNSDK_NULL;
	gnsdk_error_t          error         = GNSDK_SUCCESS;
	gnsdk_user_handle_t    user_handle   = GNSDK_NULL;
	int                    rc            = 0;


	/* Display GNSDK Product Version Info */
	_display_gnsdk_product_info();

	/* Initialize the GNSDK Manager */
	error = gnsdk_manager_initialize(
		&sdkmgr_handle,
		license_path,
		GNSDK_MANAGER_LICENSEDATA_FILENAME
		);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		return -1;
	}

	/* Enable SDK logging */
	if (0 == rc)
	{
		rc = _enable_logging();
	}

	/* Initialize the Storage SQLite Library */
	if (0 == rc)
	{
		error = gnsdk_storage_sqlite_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
	}

	/* Initialize the VideoID SDK */
	error = gnsdk_video_initialize(sdkmgr_handle);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		rc = -1;
	}

	/* Get a user handle for our client ID.  This will be passed in for all queries */
	if (0 == rc)
	{
		rc = _get_user_handle(
			client_id,
			client_id_tag,
			client_app_version,
			&user_handle
			);
	}

	/* Set locale */
	if (0 == rc)
	{
		rc = _set_locale(user_handle);
	}

	if (0 != rc)
	{
		/* Clean up on failure. */
		_shutdown_gnsdk(user_handle);
	}
	else
	{
		/* Return the User handle for use at query time */
		*p_user_handle = user_handle;
	}

	return rc;

}    /* _init_gnsdk() */


/***************************************************************************
*
*    _SHUTDOWN_GNSDK
*
*     Call shutdown on all initialized GNSDK modules.
*     Release all existing handles before shutting down any of the modules.
*     Shutting down the Manager module should occur last, but the shutdown
*     ordering of all other modules does not matter.
*
***************************************************************************/
static void
_shutdown_gnsdk(
	gnsdk_user_handle_t user_handle
	)
{
	gnsdk_error_t error = GNSDK_SUCCESS;


	error = gnsdk_manager_user_release(user_handle);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
	}

	/* Shutdown the libraries */
	gnsdk_manager_shutdown();

}    /* _shutdown_gnsdk() */


/*****************************************************************
*
*   _DISPLAY_BASIC_DATA
*
*****************************************************************/
static int
_display_basic_data(gnsdk_gdo_handle_t video_gdo)
{
	gnsdk_error_t      error           = GNSDK_SUCCESS;
	gnsdk_cstr_t       value           = GNSDK_NULL;
	gnsdk_uint32_t     disc_count      = 0;
	gnsdk_gdo_handle_t video_title_gdo = GNSDK_NULL;
	int                rc              = 0;


	/* Get the video title GDO */
	error = gnsdk_manager_gdo_child_get(video_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &video_title_gdo);

	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		return -1;
	}

	/* Display video title */
	error = gnsdk_manager_gdo_value_get(video_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value);
	if (GNSDK_SUCCESS == error)
	{
		printf("Title: %s\n", value);
	}
	else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
	{
		_display_last_error(__LINE__);
	}

	/* Video edition */
	error = gnsdk_manager_gdo_value_get(video_title_gdo, GNSDK_GDO_VALUE_EDITION, 1, &value);
	if (GNSDK_SUCCESS == error)
	{
		printf("Edition: %s\n", value);
	}
	else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
	{
		_display_last_error(__LINE__);
	}

	/* Video type */
	if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(video_gdo, GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE, 1, &value))
	{
		printf("Production type: %s\n", value);
	}
	else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
	{
		_display_last_error(__LINE__);
	}

	/* Video original release */
	if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(video_gdo, GNSDK_GDO_VALUE_DATE_ORIGINAL_RELEASE, 1, &value))
	{
		printf("Orig release: %s\n", value);
	}
	else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
	{
		_display_last_error(__LINE__);
	}

	/* Video rating */
	if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(video_gdo, GNSDK_GDO_VALUE_RATING, 1, &value))
	{
		printf("Rating: %s", value);
		if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(video_gdo, GNSDK_GDO_VALUE_RATING_TYPE, 1, &value))
		{
			printf(" [%s]", value);
		}
		if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(video_gdo, GNSDK_GDO_VALUE_RATING_DESC, 1, &value))
		{
			printf(" - %s", value);
		}
		printf("\n");
	}

	/* Video release year  */
	error = gnsdk_manager_gdo_value_get(video_gdo, GNSDK_GDO_VALUE_DATE_RELEASE, 1, &value);
	if (GNSDK_SUCCESS == error)
	{
		printf("Release: %s\n", value);
	}
	else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
	{
		_display_last_error(__LINE__);
	}

	/* Discs in set */
	error = gnsdk_manager_gdo_child_count(video_gdo, GNSDK_GDO_CHILD_VIDEO_DISC, &disc_count);
	if (GNSDK_SUCCESS == error)
	{
		printf("Discs: %d\n\n", disc_count);
	}
	else
	{
		_display_last_error(__LINE__);
	}

	gnsdk_manager_gdo_release(video_title_gdo);
	return rc;

}  /* _display_basic_data() */


/*****************************************************************
*
*   _DISPLAY_CHAPTERS
*
*****************************************************************/
static int
_display_chapters(gnsdk_gdo_handle_t feature_gdo)
{
	int           rc    = 0;
	gnsdk_error_t error = GNSDK_SUCCESS;
	gnsdk_cstr_t  value = GNSDK_NULL;

	gnsdk_gdo_handle_t chapter_gdo       = GNSDK_NULL;
	gnsdk_gdo_handle_t chapter_title_gdo = GNSDK_NULL;

	gnsdk_uint32_t chapter_count  = 0;
	gnsdk_uint32_t chptr          = 0;
	gnsdk_cstr_t   chapternum_str = GNSDK_NULL;


	/* Chapters */
	error = gnsdk_manager_gdo_child_count(feature_gdo, GNSDK_GDO_CHILD_VIDEO_CHAPTER, &chapter_count);
	if (GNSDK_SUCCESS == error)
	{
		printf("\t\t\tchapters: %d\n", chapter_count);
	}
	else
	{
		_display_last_error(__LINE__);
		return -1;
	}

	for (chptr = 1; chptr <= chapter_count; chptr++)
	{
		/* Get the chapter GDO */
		error = gnsdk_manager_gdo_child_get(feature_gdo, GNSDK_GDO_CHILD_VIDEO_CHAPTER, chptr, &chapter_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
			break;
		}

		/* Get chapter number */
		error = gnsdk_manager_gdo_value_get(chapter_gdo, GNSDK_GDO_VALUE_ORDINAL, 1, &chapternum_str);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			gnsdk_manager_gdo_release(chapter_gdo);
			rc = -1;
			break;
		}

		/* Get the chapter title name GDO */
		error = gnsdk_manager_gdo_child_get(chapter_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &chapter_title_gdo);

		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			gnsdk_manager_gdo_release(chapter_gdo);
			rc = -1;
			break;
		}

		error = gnsdk_manager_gdo_value_get(chapter_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value);
		if (GNSDK_SUCCESS == error)
		{
			printf("\t\t\t\t%s: %s", chapternum_str, value);
		}
		else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			printf("\t\t\t\t%s: (no title data)", chapternum_str);
		}

		error = gnsdk_manager_gdo_value_get(chapter_gdo, GNSDK_GDO_VALUE_DURATION, 1, &value);
		if (GNSDK_SUCCESS == error)
		{
			int seconds = atoi(value);
			int minutes = seconds/60;
			int hours   = minutes/60;
			seconds = seconds - (60*minutes);
			minutes = minutes - (60*hours);
			printf(" [%d:%02d:%02d]", hours, minutes, seconds);
		}
		else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
		{
			_display_last_error(__LINE__);
		}

		printf("\n");

		gnsdk_manager_gdo_release(chapter_gdo);
		gnsdk_manager_gdo_release(chapter_title_gdo);

	} /* For each chapter */

	return rc;

} /* _display_chapters() */


/*****************************************************************
*
*   _DISPLAY_LAYERS
*
*****************************************************************/
static int
_display_layers(gnsdk_gdo_handle_t side_gdo)
{
	gnsdk_error_t      error             = GNSDK_SUCCESS;
	gnsdk_cstr_t       value             = GNSDK_NULL;
	gnsdk_cstr_t       layernum_str      = GNSDK_NULL;
	gnsdk_cstr_t       featurenum_str    = GNSDK_NULL;
	gnsdk_cstr_t       matched_str       = GNSDK_NULL;
	gnsdk_gdo_handle_t layer_gdo         = GNSDK_NULL;
	gnsdk_gdo_handle_t feature_gdo       = GNSDK_NULL;
	gnsdk_gdo_handle_t feature_title_gdo = GNSDK_NULL;
	int                rc                = 0;
	gnsdk_uint32_t     layer_count       = 0;
	gnsdk_uint32_t     lyr               = 0;
	gnsdk_uint32_t     feature_count     = 0;
	gnsdk_uint32_t     ftr               = 0;


	/* Get number of layers */
	error = gnsdk_manager_gdo_child_count(side_gdo, GNSDK_GDO_CHILD_VIDEO_LAYER, &layer_count);
	if (GNSDK_SUCCESS == error)
	{
		printf("\tNumber layers: %d\n", layer_count);
	}
	else if (GNSDKERR_ERROR_CODE(error) == GNSDKERR_NotFound)
	{
		printf("\tno layer data\n");
	}
	else
	{
		_display_last_error(__LINE__);
		rc = -1;
	}

	for (lyr = 1; lyr <= layer_count; lyr++)
	{
		/* Get the layer GDO */
		error = gnsdk_manager_gdo_child_get(side_gdo, GNSDK_GDO_CHILD_VIDEO_LAYER, lyr, &layer_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
			break;
		}

		/* Get the layer number */
		error = gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_ORDINAL, 1, &layernum_str);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			gnsdk_manager_gdo_release(layer_gdo);
			rc = -1;
			break;
		}

		/* matched - was this the layer that matched the initial query input */
		error = gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_MATCHED, 1, &value);
		if (GNSDK_SUCCESS != error)
			matched_str = "";
		else
			matched_str = "MATCHED";

		printf("\t\tLayer %s -------- %s\n", layernum_str, matched_str);

		/* Get media type */
		if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_MEDIA_TYPE, 1, &value))
		{
			printf("\t\tMedia type: %s\n", value);
		}

		/* Get TV system */
		if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_TV_SYSTEM, 1, &value))
		{
			printf("\t\tTV system: %s\n", value);
		}

		/* Get region */
		if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_REGION_CODE, 1, &value))
		{
			printf("\t\tRegion Code: %s\n", value);
		}

		if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_VIDEO_REGION, 1, &value))
		{
			printf("\t\tVideo Region: %s\n", value);
		}

		/* Get aspect ratio */
		if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_ASPECT_RATIO, 1, &value))
		{
			printf("\t\tAspect ratio: %s", value);

			/* Get aspect ratio type */
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(layer_gdo, GNSDK_GDO_VALUE_ASPECT_RATIO_TYPE, 1, &value))
			{
				printf(" [%s]", value);
			}
			printf("\n");
		}

		/* Get number of  layer features */
		error = gnsdk_manager_gdo_child_count(layer_gdo, GNSDK_GDO_CHILD_VIDEO_FEATURE,    &feature_count);
		if (GNSDK_SUCCESS == error)
		{
			printf("\t\tFeatures: %d\n", feature_count);
		}
		else
		{
			_display_last_error(__LINE__);
		}

		/* Loop thru features */
		for (ftr = 1; ftr <= feature_count; ftr++)
		{
			/* Get the feature GDO */
			error = gnsdk_manager_gdo_child_get(layer_gdo, GNSDK_GDO_CHILD_VIDEO_FEATURE, ftr, &feature_gdo);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
				break;
			}

			/* Get feature number */
			error = gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_ORDINAL, 1, &featurenum_str);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				gnsdk_manager_gdo_release(feature_gdo);
				rc = -1;
				break;
			}

			/* Get matched */
			error = gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_MATCHED, 1, &value);
			if (GNSDK_SUCCESS != error)
				matched_str = "";
			else
				matched_str = "MATCHED";

			printf("\n\t\t\tFeature %s -------- %s\n", featurenum_str, matched_str);


			/* Get the feature title name GDO */
			error = gnsdk_manager_gdo_child_get(feature_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &feature_title_gdo    );

			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				gnsdk_manager_gdo_release(feature_gdo);
				rc = -1;
				break;
			}

			/* Get title */
			error = gnsdk_manager_gdo_value_get(feature_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value);
			if (GNSDK_SUCCESS == error)
			{
				printf("\t\t\tFeature title: %s\n", value);
			}
			else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
			{
				_display_last_error(__LINE__);
				gnsdk_manager_gdo_release(feature_gdo);
				gnsdk_manager_gdo_release(feature_title_gdo);
				rc = -1;
				break;
			}

			error = gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_DURATION, 1, &value);
			if (GNSDK_SUCCESS == error)
			{
				int seconds = atoi(value);
				int minutes = seconds/60;
				int hours   = minutes/60;
				seconds = seconds - (60*minutes);
				minutes = minutes - (60*hours);
				printf("\t\t\tLength: %d:%02d:%02d\n", hours, minutes, seconds);
			}
			else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
			{
				_display_last_error(__LINE__);
			}

			/*  Aspect ratio */
			error = gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_ASPECT_RATIO, 1, &value);
			if (GNSDK_SUCCESS == error)
			{
				printf("\t\t\tAspect ratio: %s", value);

				/* Aspect ratio type */
				if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_ASPECT_RATIO_TYPE, 1, &value))
				{
					printf(" [%s]", value);
				}
				printf("\n");
			}
			else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
			{
				_display_last_error(__LINE__);
			}

			/*
			 * Note: Genre display strings come from a genre hierarchy, so you can choose what level
			 * of granularity to display.  GNSDK_GDO_VALUE_GENRE_LEVEL1 are the top level genres and
			 * the most general, GNSDK_GDO_VALUE_GENRE_LEVEL2 is the mid-level genre and the most
			 * granular genre is GNSDK_GDO_VALUE_GENRE_LEVEL#.
			 */

			/* Feature genre(s) */
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_GENRE_LEVEL1, 1, &value))
			{
				printf("\t\t\tPrimary genre: %s\n", value);
			}


			/* Feature rating */
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_RATING, 1, &value))
			{
				printf("\t\t\tRating: %s", value);
				if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_RATING_TYPE, 1, &value))
				{
					printf(" [%s]", value);
				}
				if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_RATING_DESC, 1, &value))
				{
					printf(" - %s", value);
				}
				printf("\n");
			}

			/* Feature type */
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_VIDEO_FEATURE_TYPE, 1, &value))
			{
				printf("\t\t\tFeature type: %s\n", value);
			}

			/* Video type */
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE, 1, &value))
			{
				printf("\t\t\tProduction type: %s\n", value);
			}

			/* Feature plot */
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_PLOT_SUMMARY, 1, &value))
			{
				printf("\t\t\tPlot summary: %s\n", value);
			}
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_PLOT_SYNOPSIS, 1, &value))
			{
				printf("\t\t\tPlot synopsis: %s\n", value);
			}
			if (GNSDK_SUCCESS == gnsdk_manager_gdo_value_get(feature_gdo, GNSDK_GDO_VALUE_PLOT_TAGLINE, 1, &value))
			{
				printf("\t\t\tTagline: %s\n", value);
			}


			/* Display chapters */
			rc = _display_chapters(feature_gdo);
			gnsdk_manager_gdo_release(feature_gdo);
			gnsdk_manager_gdo_release(feature_title_gdo);

			if (0 != rc)
			{
				break;
			}

		}    /* For each feature */

		gnsdk_manager_gdo_release(layer_gdo);

	} /* For each layer */


	return rc;

} /* _display_layers() */


/*****************************************************************
*
*   _DISPLAY_DISCS
*
*****************************************************************/
static int
_display_discs(gnsdk_gdo_handle_t video_gdo)
{
	int           rc    = 0;
	gnsdk_error_t error = GNSDK_SUCCESS;
	gnsdk_cstr_t  value = GNSDK_NULL;

	gnsdk_gdo_handle_t disc_gdo      = GNSDK_NULL;
	gnsdk_gdo_handle_t disc_name_gdo = GNSDK_NULL;
	gnsdk_gdo_handle_t side_gdo      = GNSDK_NULL;

	gnsdk_uint32_t disc_count = 0;
	gnsdk_uint32_t dsc        = 0;
	gnsdk_uint32_t side_count = 0;
	gnsdk_uint32_t sde        = 0;

	gnsdk_cstr_t discnum_str = GNSDK_NULL;
	gnsdk_cstr_t sidenum_str = GNSDK_NULL;
	gnsdk_cstr_t matched_str = GNSDK_NULL;


	/* Get disc count */
	error = gnsdk_manager_gdo_child_count(video_gdo, GNSDK_GDO_CHILD_VIDEO_DISC, &disc_count);


	if (GNSDK_SUCCESS == error)
	{
		printf("Discs:%d\n", disc_count);
	}
	else
	{
		_display_last_error(__LINE__);
		return -1;
	}

	for (dsc = 1; dsc <= disc_count; dsc++)
	{
		/* Get the disc GDO */
		error = gnsdk_manager_gdo_child_get(video_gdo, GNSDK_GDO_CHILD_VIDEO_DISC, dsc, &disc_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
			break;
		}

		/* Disc number */
		error = gnsdk_manager_gdo_value_get(disc_gdo, GNSDK_GDO_VALUE_ORDINAL, 1, &discnum_str);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			gnsdk_manager_gdo_release(disc_gdo);
			rc = -1;
			break;
		}

		/* Matched */
		error = gnsdk_manager_gdo_value_get(disc_gdo, GNSDK_GDO_VALUE_MATCHED, 1, &value);
		if (GNSDK_SUCCESS != error)
			matched_str =  "";
		else
			matched_str = "MATCHED";


		printf("disc %s -------- %s\n", discnum_str, matched_str);

		/* Get the disc title GDO */
		error = gnsdk_manager_gdo_child_get(disc_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &disc_name_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			gnsdk_manager_gdo_release(disc_gdo);
			rc = -1;
			break;
		}

		/* Get and display title */
		error = gnsdk_manager_gdo_value_get(disc_name_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value);
		if (GNSDK_SUCCESS == error)
		{
			printf("\tTitle: %s\n", value);
		}
		else if (GNSDKERR_ERROR_CODE(error) != GNSDKERR_NotFound)
		{
			_display_last_error(__LINE__);
		}

		/* Get disc side count */
		error = gnsdk_manager_gdo_child_count(disc_gdo,    GNSDK_GDO_CHILD_VIDEO_SIDE,    &side_count    );
		if (GNSDK_SUCCESS == error)
		{
			printf("\tNumber sides: %d\n", side_count);
		}
		else
		{
			_display_last_error(__LINE__);
			rc = -1;
		}

		/**************************************************
		 *
		 *    LOOP THRU SIDES
		 *
		 *************************************************/
		for (sde = 1; sde <= side_count; sde++)
		{
			/* Get the side GDO */
			error = gnsdk_manager_gdo_child_get(disc_gdo, GNSDK_GDO_CHILD_VIDEO_SIDE, sde, &side_gdo);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
				break;
			}

			/* Get side number */
			error = gnsdk_manager_gdo_value_get(side_gdo, GNSDK_GDO_VALUE_ORDINAL, 1, &sidenum_str);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				gnsdk_manager_gdo_release(side_gdo);
				rc = -1;
				break;
			}

			/* Get matched */
			error = gnsdk_manager_gdo_value_get(side_gdo, GNSDK_GDO_VALUE_MATCHED, 1, &value);
			if (GNSDK_SUCCESS != error)
				matched_str = "";
			else
				matched_str = "MATCHED";

			printf("\tSide %s -------- %s\n", sidenum_str, matched_str);

			rc = _display_layers(side_gdo);

			gnsdk_manager_gdo_release(side_gdo);

		} /* For each side */

		gnsdk_manager_gdo_release(disc_gdo);
		gnsdk_manager_gdo_release(disc_name_gdo);

	} /* For each disc */

	return rc;

}  /* _display_discs() */


/*****************************************************************
*
*   _DISPLAY_SINGLE_PRODUCT
*
*****************************************************************/
static int
_display_single_product(gnsdk_gdo_handle_t response_gdo, gnsdk_user_handle_t user_handle)
{
	gnsdk_error_t              error             = GNSDK_SUCCESS;
	gnsdk_gdo_handle_t         full_response_gdo = GNSDK_NULL;
	gnsdk_gdo_handle_t         video_gdo         = GNSDK_NULL;
	gnsdk_video_query_handle_t query_handle      = GNSDK_NULL;
	int                        rc                = 0;
	gnsdk_cstr_t               is_full           = GNSDK_NULL;


	/*
	 * Note that the GDO accessors below are *ordinal* based, not index based.  so the 'first' of
	 * anything has a one-based ordinal of '1' - *not* an index of '0'
	 */


	/* Get the child video GDO */
	error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_VIDEO_PRODUCT, 1, &video_gdo);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
	}
	else
	{
		/***********************************************************************************
		 *
		 *  FULL or PARTIAL DATA CHECK
		 *
		 *  See if the video has full or partial data.
		 *  Note that this step is only necessary if you need more than partial data
		 *  Consult the GNSDK data model to see if this is true.
		 *
		 ************************************************************************************/

		error = gnsdk_manager_gdo_value_get(video_gdo, GNSDK_GDO_VALUE_FULL_RESULT, 1, &is_full);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			/* If we only have a partial result, we do a follow-up query to retrieve the full video */
			if (0 == strcmp(is_full, GNSDK_VALUE_FALSE))
			{
				/* Get a GDO with full metadata */
				error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);
				if (GNSDK_SUCCESS != error)
				{
					_display_last_error(__LINE__);
				}
				else
				{
					/* Do followup query to get full object. Setting the partial video as the query input. */
					error = gnsdk_video_query_set_gdo(query_handle, video_gdo);
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
					}
					else
					{
						/* We can now release the partial video */
						gnsdk_manager_gdo_release(video_gdo);
						video_gdo = GNSDK_NULL;

						error = gnsdk_video_query_find_products(query_handle, &full_response_gdo);
						if (GNSDK_SUCCESS != error)
						{
							_display_last_error(__LINE__);
						}
						else
						{
							/* Now our first video is the desired result with full data */
							error = gnsdk_manager_gdo_child_get(full_response_gdo, GNSDK_GDO_CHILD_VIDEO_PRODUCT, 1, &video_gdo);

							/* Release the followup query's response object */
							gnsdk_manager_gdo_release(full_response_gdo);

						} /* else find_products ok*/
					} /* else set_gdo ok */
				}  /* if query_create ok */
			} /* end else */
		} /* if not full */
	} /* else get child ok */


	if (GNSDK_SUCCESS == error)
	{
		rc =  _display_basic_data(video_gdo);
		if (rc == 0)
		{
			rc = _display_discs(video_gdo);
		}
	}

	gnsdk_manager_gdo_release(video_gdo);
	gnsdk_video_query_release(query_handle);

	if ((rc == 0) && (error != GNSDK_SUCCESS))
	{
		rc = -1;
	}

	return rc;

}  /* _display_single_product()  */


/*****************************************************************
*
*   _HANDLE_PRODUCT_RESULTS
*
*****************************************************************/
static int
_handle_product_results(gnsdk_gdo_handle_t response_gdo, gnsdk_user_handle_t user_handle)
{
	gnsdk_error_t  error          = GNSDK_SUCCESS;
	gnsdk_uint32_t count          = 0;
	int            rc             = 0;
	gnsdk_cstr_t   needs_decision = GNSDK_NULL;


	error = gnsdk_manager_gdo_child_count(response_gdo, GNSDK_GDO_CHILD_VIDEO_PRODUCT, &count);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
	}
	else
	{
		if (count > 0)
		{
			/****************************************************************
			*  Needs decision (match resolution) check
			*  We have at least one match - see if resolution is necessary.
			****************************************************************/
			error = gnsdk_manager_gdo_value_get(response_gdo, GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION, 1, &needs_decision);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}
			else
			{
				/* See if selection of one of the videos needs to happen */
				if (0 == strcmp(needs_decision, GNSDK_VALUE_TRUE))
				{
					/**********************************************
					* Resolve match here
					**********************************************/
				}
			}
		} /* end if (count > 0) */
	}

	if (GNSDK_SUCCESS == error)
	{
		/*
		 * Typically the user would choose one (or none) of the presented choices.
		 * For this simplified sample, just pick the first choice
		 */
		if (count > 0)
		{
			rc = _display_single_product(response_gdo, user_handle);
		}
	}
	else
	{
		rc = -1;
	}

	return rc;

}  /* _handle_product_results() */


/*****************************************************************
*
*   _DO_SAMPLE_TITLE_SEARCH
*
*****************************************************************/
static int
_do_sample_title_search(gnsdk_user_handle_t user_handle, gnsdk_cstr_t title)
{
	gnsdk_video_query_handle_t query_handle = GNSDK_NULL;
	gnsdk_gdo_handle_t         response_gdo = GNSDK_NULL;
	gnsdk_error_t              error        = GNSDK_SUCCESS;
	int                        rc           = 0;


	printf("\n*****Sample Title Search: '%s'*****\n", title);

	error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		return -1;
	}

	/* Set the Input Text */
	if (0 == rc)
	{
		error = gnsdk_video_query_set_text(query_handle, GNSDK_VIDEO_SEARCH_FIELD_PRODUCT_TITLE, "Star", gnsdk_video_search_type_default);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
	}

	/* Set the search options */
	if (0 == rc)
	{
		/* For this example, get results 1 to 20 */
		error = gnsdk_video_query_option_set(query_handle, GNSDK_VIDEO_OPTION_RESULT_RANGE_START, "1");
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}

		error = gnsdk_video_query_option_set(query_handle, GNSDK_VIDEO_OPTION_RESULT_RANGE_SIZE, "20");
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
	}

	/* Perform the video find products search */
	if (0 == rc)
	{
		error = gnsdk_video_query_find_products(query_handle, &response_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
		else
		{
			rc = _handle_product_results( response_gdo, user_handle);
			gnsdk_manager_gdo_release(response_gdo);
		}
	}

	/* Release handle */
	gnsdk_video_query_release(query_handle);

	return rc;

}  /* _do_sample_title_search() */

