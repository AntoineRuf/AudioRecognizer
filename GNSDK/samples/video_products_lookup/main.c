/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: video_products_lookup/main.c
 *  Description:
 *  This sample shows use of the gnsdk_video_query_find_products() API
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

static int
_do_products_lookup(
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
	const char*         client_app_version = "1";   /* Increment with each version of your app */
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
			/* Lookup products and display */
			rc = _do_products_lookup(user_handle);

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


/******************************************************************
*
*   _DISPLAY_PRODUCT_METADATA
*
******************************************************************/
void
_display_product_metadata(gnsdk_gdo_handle_t product_gdo)
{
	gnsdk_error_t error = GNSDK_SUCCESS;
	gnsdk_cstr_t  value = GNSDK_NULL;
	int           rc    = 0;


	error = gnsdk_manager_gdo_value_get(product_gdo,     GNSDK_GDO_VALUE_ASPECT_RATIO, 1, &value);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
	}
	else
	{
		printf("Aspect ratio: %s\n", value);
	}

	error = gnsdk_manager_gdo_value_get(product_gdo, GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE, 1, &value);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		rc = -1;
	}
	else
	{
		printf("Production Type: %s\n", value);
	}

	error = gnsdk_manager_gdo_value_get(product_gdo, GNSDK_GDO_VALUE_PACKAGE_LANGUAGE_DISPLAY, 1, &value);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		rc = -1;
	}
	else
	{
		printf("Package language: %s\n", value);
	}

	error = gnsdk_manager_gdo_value_get(product_gdo, GNSDK_GDO_VALUE_RATING, 1, &value);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		rc = -1;
	}
	else
	{
		printf("Rating: %s\n", value);
	}

}  /* _display_product_metadata() */


/******************************************************************
*
*  _DO_PRODUCTS_LOOKUP
*
******************************************************************/
int
_do_products_lookup(gnsdk_user_handle_t user_handle)
{
	gnsdk_error_t              error             = GNSDK_SUCCESS;
	gnsdk_video_query_handle_t query_handle      = GNSDK_NULL;
	gnsdk_gdo_handle_t         response_gdo      = GNSDK_NULL;
	gnsdk_gdo_handle_t         product_gdo       = GNSDK_NULL;
	gnsdk_gdo_handle_t         product_title_gdo = GNSDK_NULL;
	gnsdk_cstr_t               product_title     = GNSDK_NULL;


	/********************************************
	* Get Product based on TOC
	********************************************/

	/* Create a new query handle */
	error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);


	if (GNSDK_SUCCESS == error)
	{
		/* Set the input ID */
		gnsdk_video_query_set_toc_string( query_handle,
										  "1:15;2:198 15;3:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 6914 1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 7630 2564 8910 15;4:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 6914 1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 7630 2564 8910 15;5:8962 15;6:11474 15;7:11538 15;", 0 );


		if (GNSDK_SUCCESS == error)
		{
			/* Attempt to look up this UPC */
			error = gnsdk_video_query_find_products(query_handle, &response_gdo);

			if (GNSDK_SUCCESS == error)
			{
				error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_VIDEO_PRODUCT, 1, &product_gdo );
				if (GNSDK_SUCCESS == error)
				{
					error = gnsdk_manager_gdo_child_get(product_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &product_title_gdo );
					if (GNSDK_SUCCESS == error)
					{
						error = gnsdk_manager_gdo_value_get(product_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &product_title );
						if (GNSDK_SUCCESS == error)
						{
							printf("\nTitle: %s\n", product_title);
							_display_product_metadata(product_gdo);
						}
						else
							printf("\nGet Title error: 0x%x\n", error);
					}
					else _display_last_error(__LINE__);
				}
				else _display_last_error(__LINE__);
			}
			else _display_last_error(__LINE__);
		}
		else _display_last_error(__LINE__);
	}
	else _display_last_error(__LINE__);

	/*********************************
	* Clean up and shutdown
	*********************************/

	/* Release GDOs and Query Handle */
	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_manager_gdo_release(product_gdo);
	gnsdk_manager_gdo_release(product_title_gdo);
	gnsdk_video_query_release(query_handle);

	return 0;
}  /* _do_products_lookup() */


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


/******************************************************************
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
 *****************************************************************/
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

	/* Enable logging */
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
	if (0 == rc)
	{
		error = gnsdk_video_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
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
		/* Clean up on failure */
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

