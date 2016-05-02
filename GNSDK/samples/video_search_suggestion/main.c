/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: video_search_suggestion/main.c
 *  Description:
 *  This sample shows basic use of the gnsdk_video_query_find_suggestions() call
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
*	Local Function Declarations
**********************************************/
static
int _init_gnsdk(
	gnsdk_cstr_t         client_id,
	gnsdk_cstr_t         client_id_tag,
	gnsdk_cstr_t         client_id_app_version,
	gnsdk_cstr_t         license_path,
	gnsdk_user_handle_t* p_user_handle);

static
int _do_sample_suggestion_search(
	gnsdk_user_handle_t user_handle,
	gnsdk_cstr_t        text
	);

static
void _shutdown_gnsdk(
	gnsdk_user_handle_t user_handle
	);


/******************************************************************
*
*	MAIN
*
******************************************************************/
int
main(int argc, char* argv[])
{
	gnsdk_user_handle_t user_handle        = GNSDK_NULL;
	const char*         client_id          = NULL;
	const char*         client_id_tag      = NULL;
	const char*         client_app_version = "1";      /* Increment with each version of your app */
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

		/* Initialize GNSDK	 */
		rc = _init_gnsdk(
			client_id,
			client_id_tag,
			client_app_version,
			license_path,
			&user_handle
			);

		if (0 == rc)
		{
			/* Do suggestion search */
			rc = _do_sample_suggestion_search(user_handle, "spider");

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

}   /* main() */


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


/*****************************************************************
 *
 *   _DO_SAMPLE_SUGGESTION_SEARCH
 *
 ******************************************************************/
static int
_do_sample_suggestion_search(
	gnsdk_user_handle_t user_handle,
	gnsdk_cstr_t        text
	)
{
	gnsdk_error_t              error             = GNSDK_SUCCESS;
	gnsdk_video_query_handle_t query_handle      = GNSDK_NULL;
	gnsdk_gdo_handle_t         response_gdo      = GNSDK_NULL;
	int                        rc                = 0;
	gnsdk_uint32_t             count             = 0;
	gnsdk_uint32_t             i                 = 0;
	gnsdk_cstr_t               search_term       = GNSDK_NULL;
	gnsdk_cstr_t               range_start       = GNSDK_NULL;
	gnsdk_cstr_t               range_end         = GNSDK_NULL;
	gnsdk_cstr_t               range_count       = GNSDK_NULL;
	int                        more_results      = 1;
	int                        page_start        = 1;
	int                        page_count        = 20;
	char                       int_as_string[10] = {0};


	printf("\n*****Sample VideoID Suggestion Lookup*****\n\n");

	while (1 == more_results)
	{
		query_handle = GNSDK_NULL;
		response_gdo = GNSDK_NULL;
		more_results = 0;

		/* Create query handle with no optional data passed to callback function */
		error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}

		/* Set the input text  */
		if (0 == rc)
		{
			error = gnsdk_video_query_set_text(
				query_handle,
				GNSDK_VIDEO_SEARCH_FIELD_PRODUCT_TITLE,
				text,
				gnsdk_video_search_type_anchored
				);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
		}

		/* Set the search options  */
		if (0 == rc)
		{
			sprintf(int_as_string, "%d", page_start);

			error = gnsdk_video_query_option_set(query_handle, GNSDK_VIDEO_OPTION_RESULT_RANGE_START, (gnsdk_cstr_t)int_as_string);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}

			sprintf(int_as_string, "%d", page_count);

			error = gnsdk_video_query_option_set(query_handle, GNSDK_VIDEO_OPTION_RESULT_RANGE_SIZE, (gnsdk_cstr_t)int_as_string);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}
		}

		/* Perform the search  */
		if (0 == rc)
		{
			error = gnsdk_video_query_find_suggestions(query_handle, &response_gdo);

			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
			else
			{
				/* Handle the results
				 * Retrieve number of search terms in result  */

				error = gnsdk_manager_gdo_value_count(response_gdo, GNSDK_GDO_VALUE_SUGGESTION_TITLE, &count);
				if (GNSDK_SUCCESS != error)
				{
					_display_last_error(__LINE__);
					rc = -1;
				}
				else
				{
					error = gnsdk_manager_gdo_value_get(response_gdo, GNSDK_GDO_VALUE_RESPONSE_RANGE_START, 1, &range_start);
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
						rc = -1;
					}

					error = gnsdk_manager_gdo_value_get(response_gdo, GNSDK_GDO_VALUE_RESPONSE_RANGE_END, 1, &range_end);
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
						rc = -1;
					}


					error = gnsdk_manager_gdo_value_get(response_gdo, GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL, 1, &range_count);
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
						rc = -1;
					}


					if (count > 0)
						printf("\t%s - %s of %s suggestions for '%s'\n", range_start, range_end, range_count, text);

					/* Get search term */
					for (i = 1; i <= count; i++)
					{
						error = gnsdk_manager_gdo_value_get(response_gdo, GNSDK_GDO_VALUE_SUGGESTION_TITLE, i, &search_term);
						if (GNSDK_SUCCESS != error)
						{
							_display_last_error(__LINE__);
							rc = -1;
						}
						else printf("\t%d: %s\n", i+page_start-1, search_term);
					}

					if (0 == rc)
					{
						if (atoi(range_count) > atoi(range_end))
						{
							more_results = 1;
							page_start  += page_count;
						}
					}

				} /* else get count ok */

			} /* else search ok */

		} /* if (0 == rc) */

		/* Clean up  */
		gnsdk_manager_gdo_release(response_gdo);
		gnsdk_video_query_release(query_handle);
	}

	return rc;

}  /* _do_sample_suggestion_search  */


/******************************************************************
*
*	_DISPLAY_GNSDK_PRODUCT_INFO
*
*	Display product version information
*
******************************************************************/
static void
_display_gnsdk_product_info(void)
{
	/* Display GNSDK Version infomation */
	printf("\nGNSDK Product Version	: %s \t(built %s)\n", gnsdk_manager_get_product_version(), gnsdk_manager_get_build_date());

}   /* _display_gnsdk_product_info() */


/******************************************************************
*
*	_ENABLE_LOGGING
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
		"sample.log",                                           /* Log file path */
		GNSDK_LOG_PKG_ALL,                                      /* Include entries for all packages and subsystems */
		GNSDK_LOG_LEVEL_ERROR|GNSDK_LOG_LEVEL_WARNING,          /* Include only error and warning entries */
		GNSDK_LOG_OPTION_ALL,                                   /* All logging options: timestamps, thread IDs, etc */
		0,                                                      /* Max size of log: 0 means a new log file will be created each run */
		GNSDK_FALSE                                             /* GNSDK_TRUE = old logs will be renamed and saved */
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
 *	_GET_USER_HANDLE
 *
 *	Load existing user handle, or register new one.
 *
 *	GNSDK requires a user handle instance to perform queries.
 *	User handles encapsulate your Gracenote provided Client ID which is unique for your
 *	application. User handles are registered once with Gracenote then must be saved by
 *	your application and reused on future invocations.
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


/*********************************************************************************
 *
 *	_SET_LOCALE
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
		GNSDK_LOCALE_GROUP_VIDEO,               /* Locale group */
		GNSDK_LANG_ENGLISH,                     /* Languae */
		GNSDK_REGION_DEFAULT,                   /* Region */
		GNSDK_DESCRIPTOR_SIMPLIFIED,            /* Descriptor */
		user_handle,                            /* User handle */
		GNSDK_NULL,                             /* User callback function */
		0,                                      /* Optional data for user callback function */
		&locale_handle                          /* Return handle */
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
*	_INIT_GNSDK
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

}   /* _init_gnsdk() */


/***************************************************************************
*
*	_SHUTDOWN_GNSDK
*
*		Call shutdown on all initialized GNSDK modules.
*		Release all existing handles before shutting down any of the modules.
*		Shutting down the Manager module should occur last, but the shutdown
*		ordering of all other modules does not matter.
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

}   /* _shutdown_gnsdk() */

