/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: video_contributors_lookup/main.c
 *  Description:
 *  This sample shows basic use of the gnsdk_video_query_find_contributors() API
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
_do_contributors_lookup(
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
			/* Lookup AV Work and display contributors */
			rc = _do_contributors_lookup(user_handle);

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


/******************************************************************
*
*   _DISPLAY_CONTRIBUTORS
*
******************************************************************/
int
_display_contributors(gnsdk_gdo_handle_t response_gdo)
{
	gnsdk_error_t      error                = GNSDK_SUCCESS;
	gnsdk_gdo_handle_t contributor_gdo      = GNSDK_NULL;
	gnsdk_gdo_handle_t contributor_name_gdo = GNSDK_NULL;
	gnsdk_cstr_t       value                = GNSDK_NULL;
	int                rc                   = 0;
	int                count                = 1;  /* Child GDOs always start at 1 */


	printf("\nContributors:\n");
	while (0 == rc)
	{
		error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_CONTRIBUTOR, count, &contributor_gdo);
		if (GNSDK_SUCCESS != error)
		{
			rc = -1;
		}

		if (0 == rc)
		{
			error = gnsdk_manager_gdo_child_get(contributor_gdo, GNSDK_GDO_CHILD_NAME_OFFICIAL, 1, &contributor_name_gdo);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
		}

		if (0 == rc)
		{
			error = gnsdk_manager_gdo_value_get(contributor_name_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
			else printf("\t%d : %s\n", count, value);
		}

		if (0 == rc)
		{
			gnsdk_manager_gdo_release(contributor_gdo);
			gnsdk_manager_gdo_release(contributor_name_gdo);
		}

		count++;

	} /* while */

	return rc;

}  /* _display_contributors() */


/******************************************************************
*
*   _DO_CONTRIBUTORS_LOOKUP
*
******************************************************************/
int
_do_contributors_lookup(gnsdk_user_handle_t user_handle)
{
	gnsdk_error_t              error                 = GNSDK_SUCCESS;
	gnsdk_video_query_handle_t query_handle          = GNSDK_NULL;
	gnsdk_gdo_handle_t         response_gdo          = GNSDK_NULL;
	gnsdk_gdo_handle_t         query_gdo             = GNSDK_NULL;
	gnsdk_gdo_handle_t         work_gdo              = GNSDK_NULL;
	gnsdk_gdo_handle_t         work_title_gdo        = GNSDK_NULL;
	gnsdk_cstr_t               work_title            = GNSDK_NULL;
	gnsdk_cstr_t               needs_decision        = GNSDK_NULL;
	gnsdk_gdo_handle_t         followup_response_gdo = GNSDK_NULL;
	gnsdk_uint32_t             count                 = 0;
	gnsdk_cstr_t               is_full               = GNSDK_NULL;


	/******************************
	* Get Work GDO
	******************************/

	error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);


	if (GNSDK_SUCCESS == error)
	{
		/* Deserialize GDO */
		error = gnsdk_manager_gdo_deserialize( "WEcxAxpHl1mb/3LWaUoNklp7jGNb+JJ6JjfVejkh2RyiKi05lSEtfOeCNB5yvBRo4liQy9nzqL5HawtU90Sz7GcuetF6p+V0JpiB+lLSKydG5bhN2YYNqLzQdaJOUbIBnhTUdiXmAWuDh9FhGx9fgGKHH1Zjn+V7ff+DwxqK7lpY+EI243+xFw4kuePtsf+SkOKExQ==", &query_gdo);
		if (GNSDK_SUCCESS == error)
		{
			error = gnsdk_video_query_set_gdo(query_handle, query_gdo);
			if (GNSDK_SUCCESS == error)
			{
				/* Perform the search */
				error = gnsdk_video_query_find_works(query_handle, &response_gdo);
				if (GNSDK_SUCCESS == error)
				{
					error = gnsdk_manager_gdo_child_count(response_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, &count);
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

					} /* end else got count ok */
				}
				else _display_last_error(__LINE__);
			}
			else _display_last_error(__LINE__);
		}
		else _display_last_error(__LINE__);
	}
	else _display_last_error(__LINE__);


	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, 1, &work_gdo );
		if (GNSDK_SUCCESS != error)
			_display_last_error(__LINE__);
	}

	if (GNSDK_SUCCESS == error)
	{
		/***********************************************************************************
		 *
		 *  FULL or PARTIAL DATA CHECK
		 *
		 *  See if the video has full or partial data.
		 *  Note that this step is only necessary if you need more than partial data
		 *  Consult the GNSDK data model to see if this is true. We only need partial data
		 *  for this sample, but we are checking/getting the full result for demo purposes.
		 *
		 ************************************************************************************/

		error = gnsdk_manager_gdo_value_get(work_gdo, GNSDK_GDO_VALUE_FULL_RESULT, 1, &is_full);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			/* If we only have a partial result, we do a follow-up query to retrieve the full video */
			if (0 == strcmp(is_full, GNSDK_VALUE_FALSE))
			{
				/* Do followup query to get full object. Setting the partial video as the query input. */
				error = gnsdk_video_query_set_gdo(query_handle, work_gdo);
				if (GNSDK_SUCCESS != error)
				{
					_display_last_error(__LINE__);
				}
				else
				{
					/* We can now release the partial video */
					gnsdk_manager_gdo_release(work_gdo);
					work_gdo = GNSDK_NULL;

					error = gnsdk_video_query_find_works(query_handle, &followup_response_gdo);
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
					}
					else
					{
						/* Now our first video is the desired result with full data */
						error = gnsdk_manager_gdo_child_get(followup_response_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, 1, &work_gdo);

						/* Release the followup query's response object */
						gnsdk_manager_gdo_release(followup_response_gdo);

					} /* else find_works ok*/
				}  /* else set_gdo ok */
			}  /* if not full */
		} /* end else */

		/********************************
		* Get and display video title
		********************************/
		if (GNSDK_SUCCESS == error)
		{
			error = gnsdk_manager_gdo_child_get(work_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &work_title_gdo );
			if (GNSDK_SUCCESS == error)
			{
				error = gnsdk_manager_gdo_value_get(work_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &work_title );
				if (GNSDK_SUCCESS == error)
					printf("\n\nTitle: %s\n", work_title);
			}
			else _display_last_error(__LINE__);

		}  /* end if */

	} /* end if */

	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_video_query_release(query_handle);

	/******************************
	* Get contributors
	******************************/
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_video_query_create(user_handle, GNSDK_NULL,  GNSDK_NULL, &query_handle);
		if (GNSDK_SUCCESS == error)
		{
			error = gnsdk_video_query_set_gdo(query_handle, work_gdo);
			if (GNSDK_SUCCESS == error)
			{
				error = gnsdk_video_query_find_contributors(query_handle, &response_gdo);
				if (GNSDK_SUCCESS == error)
				{
					_display_contributors(response_gdo);
				}
				else _display_last_error(__LINE__);
			}
			else _display_last_error(__LINE__);
		}
		else _display_last_error(__LINE__);
	}

	/*********************************
	* Clean up and shutdown
	*********************************/

	/* Release GDOs and Query Handle */
	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_manager_gdo_release(query_gdo);
	gnsdk_manager_gdo_release(work_gdo);
	gnsdk_manager_gdo_release(work_title_gdo);
	gnsdk_video_query_release(query_handle);

	return 0;

}  /* _do_contributors_lookup */

