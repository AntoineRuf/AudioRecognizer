/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: video_explore/main.c
 *  Description:
 *  This sample shows basic video explore functionality.
 *
 *  Command-line Syntax:
 *  sample client_id client_id_tag license
 */

/* GNSDK headers
 *
 * Define the modules your application needs.
 * These constants enable inclusion of headers and symbols in gnsdk.h.
 */
#define GNSDK_VIDEO                1
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
_do_video_work_lookup(
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
			/* Lookup AV Work and display */
			rc = _do_video_work_lookup(user_handle);

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
*    _DISPLAY_VIDEO_WORK
*
*    Do a video work lookup
*
******************************************************************/
static int
_display_video_work(gnsdk_user_handle_t user_handle, gnsdk_gdo_handle_t work_gdo)
{
	gnsdk_gdo_handle_t credit_gdo      = GNSDK_NULL;
	gnsdk_gdo_handle_t credit_name_gdo = GNSDK_NULL;
	gnsdk_gdo_handle_t video_title_gdo = GNSDK_NULL;
	gnsdk_gdo_handle_t contributor_gdo = GNSDK_NULL;
	gnsdk_gdo_handle_t ref_credit_gdo  = GNSDK_NULL;
	gnsdk_cstr_t       ref_credit_name = GNSDK_NULL;
	gnsdk_uint32_t     credit_count    = 0;
	int                rc              = 0;
	gnsdk_error_t      error           = GNSDK_SUCCESS;


	/* Explore contributors : Who are the cast and crew? */
	printf("\nVideo Work - Crouching Tiger, Hidden Dragon: \n\nActor Credits:\n");

	/* How many credits for this work */
	error = gnsdk_manager_gdo_child_count(work_gdo, GNSDK_GDO_CHILD_CREDIT_ACTOR, &credit_count);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
	}
	else
	{
		/* Iterate all actor credits */
		gnsdk_uint32_t credit_index = 0;

		for (credit_index = 1; credit_index <= credit_count; credit_index++)
		{
			error = gnsdk_manager_gdo_child_get(work_gdo, GNSDK_GDO_CHILD_CREDIT_ACTOR, credit_index, &credit_gdo);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}
			else
			{
				error = gnsdk_manager_gdo_child_get(credit_gdo, GNSDK_GDO_CHILD_CONTRIBUTOR, 1, &contributor_gdo);
				if (GNSDK_SUCCESS != error)
				{
					_display_last_error(__LINE__);
				}
				else
				{
					gnsdk_cstr_t value = GNSDK_NULL;

					error = gnsdk_manager_gdo_child_get(contributor_gdo, GNSDK_GDO_CHILD_NAME_OFFICIAL, 1, &credit_name_gdo);
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
					}
					else
					{
						error = gnsdk_manager_gdo_value_get(credit_name_gdo, GNSDK_GDO_VALUE_DISPLAY, 1,    &value);
						if (GNSDK_SUCCESS != error)
						{
							_display_last_error(__LINE__);
							rc = -1;
						}
						else printf("\t%d : %s\n", credit_index, value);

						/* Keep first actor credit around to get its filmography */
						if (1 == credit_index)
						{
							ref_credit_gdo  = credit_gdo;
							ref_credit_name = value;
						}
						else gnsdk_manager_gdo_release(credit_gdo);
					}
				}

				gnsdk_manager_gdo_release(credit_name_gdo);
				gnsdk_manager_gdo_release(contributor_gdo);
			}    /* else */
		}    /* for (all credits) */
	}    /* else */


	/*************************************************************************
	 * Explore filmography : What other films did this actor play in ?
	 ************************************************************************/
	printf( "\nActor Credit: %s Filmography\n", ref_credit_name);

	/* Get Contirbutor GDO from credit GDO */
	if (GNSDK_SUCCESS == error)
	{
		gnsdk_video_query_handle_t video_query_handle = GNSDK_NULL;
		gnsdk_gdo_handle_t         response_gdo       = GNSDK_NULL;
		gnsdk_uint32_t             work_count         = 0;
		gnsdk_cstr_t               video_value_str    = GNSDK_NULL;

		error = gnsdk_manager_gdo_child_get(ref_credit_gdo, GNSDK_GDO_CHILD_CONTRIBUTOR, 1, &contributor_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			/* Get related video works */
			error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &video_query_handle);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}
			else
			{
				error = gnsdk_video_query_set_gdo(video_query_handle, contributor_gdo);
				if (GNSDK_SUCCESS != error)
				{
					_display_last_error(__LINE__);
				}
				else
				{
					error = gnsdk_video_query_find_works(video_query_handle, &response_gdo);
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
					}
					else
					{
						/* How many works in this response? */
						error = gnsdk_manager_gdo_child_count(response_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, &work_count);
						if (GNSDK_SUCCESS != error)
						{
							_display_last_error(__LINE__);
						}
						else
						{
							gnsdk_uint32_t     work_index     = 0;
							gnsdk_gdo_handle_t video_work_gdo = GNSDK_NULL;

							printf("\nNumber works: %d\n", work_count);

							for (work_index = 1; work_index <= work_count; work_index++)
							{
								error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, work_index, &video_work_gdo);
								if (GNSDK_SUCCESS != error)
								{
									_display_last_error(__LINE__);
								}
								else
								{
									error = gnsdk_manager_gdo_child_get(video_work_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &video_title_gdo);
									if (GNSDK_SUCCESS != error)
									{
										_display_last_error(__LINE__);
									}
									else
									{
										error = gnsdk_manager_gdo_value_get(video_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &video_value_str);
										if (GNSDK_SUCCESS != error)
										{
											_display_last_error(__LINE__);
										}
										else printf("\t%d : %s\n", work_index, video_value_str);
									}
								}
								gnsdk_manager_gdo_release(video_work_gdo);
								gnsdk_manager_gdo_release(video_title_gdo);

							} /* for */
						} /* else */
					}  /* else */
				}  /* else */
			}  /* else */
		} /* else */

		/* Release GDO and Query */
		gnsdk_manager_gdo_release(response_gdo);
		gnsdk_video_query_release(video_query_handle);

	} /* if */

	/* Clean up */
	gnsdk_manager_gdo_release(contributor_gdo);
	gnsdk_manager_gdo_release(ref_credit_gdo);

	return (GNSDK_SUCCESS == error) ? 0 : -1;

}    /* _display_video_work() */


/******************************************************************
*
*    _DO_VIDEO_WORK_LOOKUP
*
*    Do a video work lookup
*
******************************************************************/
static int
_do_video_work_lookup(gnsdk_user_handle_t user_handle)
{
	gnsdk_error_t              error          = GNSDK_SUCCESS;
	gnsdk_video_query_handle_t query_handle   = GNSDK_NULL;
	gnsdk_gdo_handle_t         work_gdo       = GNSDK_NULL;
	gnsdk_gdo_handle_t         input_gdo      = GNSDK_NULL;
	gnsdk_gdo_handle_t         response_gdo   = GNSDK_NULL;
	gnsdk_cstr_t               needs_decision = GNSDK_NULL;
	int                        rc             = -1;
	gnsdk_uint32_t             count          = 0;


	error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
	}
	else
	{
		error = gnsdk_manager_gdo_deserialize("WEcxA6R75JwbiGUIxLFZHBr4tv+bxvwlIMr0XK62z68zC+/kDDdELzwiHmBPkmOvbB4rYEY/UOOvFwnk6qHiLdb1iFLtVy44LfXNsTH3uNgYfSymsp9uL+hyHfrzUSwoREk1oX/rN44qn/3NFkEYa2FoB73sRxyRkfdnTGZT7MceHHA/28aWZlr3q48NbtCGWPQmTSrK", &input_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			error = gnsdk_video_query_set_gdo(query_handle, input_gdo);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}
			else
			{
				error = gnsdk_video_query_find_works(query_handle, &response_gdo);
				if (GNSDK_SUCCESS != error)
				{
					_display_last_error(__LINE__);
				}
			}
		}
	}

	if (GNSDK_SUCCESS == error)
	{
		gnsdk_manager_gdo_child_count(response_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, &count);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			/**********************************************
			*  Needs decision (match resolution) check
			**********************************************/
			if (count > 0)
			{
				/* We have at least one match - see if resolution is necessary. */
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
			}
		}
	}

	if (GNSDK_SUCCESS == error)
	{
		/* Get first work */
		error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_VIDEO_WORK, 1, &work_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			if (GNSDK_SUCCESS == error)
			{
				/* Display metadata to console */
				rc = _display_video_work(user_handle, work_gdo);
			}
		}
	}

	/* Clean up */
	gnsdk_manager_gdo_release(work_gdo);
	gnsdk_manager_gdo_release(input_gdo);
	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_video_query_release(query_handle);

	return rc;

}    /* _do_video_work_lookup() */


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
		GNSDK_FALSE                                               /* GNSDK_TRUE = old logs will be renamed and saved */
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

