/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: video_link_lookup/main.c
 *  Description:
 *  This sample shows basic extended metadata retrieval using the Link module.
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
#define GNSDK_LINK              1
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
_do_link_lookup(
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
	const char*         client_app_version = "1";         /* Increment with each version of your app */
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
			rc = _do_link_lookup(user_handle);

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

	/* Initialize the Link SDK */
	if (0 == rc)
	{
		error = gnsdk_link_initialize(sdkmgr_handle);
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
*    _DO_LINK_LOOKUP
*
******************************************************************/
static int
_do_link_lookup(gnsdk_user_handle_t user_handle)
{
	gnsdk_error_t              error             = GNSDK_SUCCESS;
	gnsdk_video_query_handle_t query_handle      = GNSDK_NULL;
	gnsdk_link_query_handle_t  link_query_handle = GNSDK_NULL;
	gnsdk_gdo_handle_t         response_gdo      = GNSDK_NULL;
	gnsdk_gdo_handle_t         full_response_gdo = GNSDK_NULL;
	gnsdk_gdo_handle_t         product_gdo       = GNSDK_NULL;
	gnsdk_gdo_handle_t         product_title_gdo = GNSDK_NULL;
	gnsdk_cstr_t               product_title     = GNSDK_NULL;
	gnsdk_byte_t*              buffer            = GNSDK_NULL;
	gnsdk_size_t               buffer_size       = 0;
	gnsdk_link_data_type_t     data_type         = gnsdk_link_data_unknown;
	gnsdk_cstr_t               needs_decision    = GNSDK_NULL;
	gnsdk_cstr_t               is_full           = GNSDK_NULL;
	gnsdk_uint32_t             count             = 0;
	int                        rc                = -1;

	/* Create a new query handle */
	error = gnsdk_video_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);
	
	/****************************************************************************
	* Enable the 'Content Data' query option for efficient cover art retrieval.
	******************************************************************************/
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_video_query_option_set( query_handle, GNSDK_VIDEO_OPTION_ENABLE_CONTENT_DATA, GNSDK_VALUE_TRUE);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
	}

	/*******************************************
	* Get Product based on TOC
	*******************************************/
	if (GNSDK_SUCCESS == error)
	{
		/* Set a video TOC for this query handle - A Bug's Life */
		error = gnsdk_video_query_set_toc_string( query_handle,
												  "1:15;2:198 15;3:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 6914 1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 7630 2564 8910 15;4:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 6914 1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 7630 2564 8910 15;5:8962 15;6:11474 15;7:11538 15;", 0 );

		if (GNSDK_SUCCESS == error)
		{
			/* Attempt to look up this TOC */
			error = gnsdk_video_query_find_products(query_handle, &response_gdo);

			if (GNSDK_SUCCESS == error)
			{
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
			}
			else _display_last_error(__LINE__);
		}
		else _display_last_error(__LINE__);
	}
	else _display_last_error(__LINE__);

	if (GNSDK_SUCCESS == error)
	{
		/* Get child video product */
		error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_VIDEO_PRODUCT, 1, &product_gdo );
		if (GNSDK_SUCCESS == error)
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
			error = gnsdk_manager_gdo_value_get(product_gdo, GNSDK_GDO_VALUE_FULL_RESULT, 1, &is_full);
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

						/* remember to enable 'Content' for efficient cover art retrieval */
						error = gnsdk_video_query_option_set( query_handle, GNSDK_VIDEO_OPTION_ENABLE_CONTENT_DATA, GNSDK_VALUE_TRUE);
						if (GNSDK_SUCCESS != error)
						{
							_display_last_error(__LINE__);
						}
						else
						{
							/* set the desired product as the query input */
							error = gnsdk_video_query_set_gdo(query_handle, product_gdo);
							if (GNSDK_SUCCESS != error)
							{
								_display_last_error(__LINE__);
							}
							else
							{
								/* We can now release the partial video */
								gnsdk_manager_gdo_release(product_gdo);
								product_gdo = GNSDK_NULL;

								error = gnsdk_video_query_find_products(query_handle, &full_response_gdo);
								if (GNSDK_SUCCESS != error)
								{
									_display_last_error(__LINE__);
								}
								else
								{
									/* Now our first video is the desired result with full data */
									error = gnsdk_manager_gdo_child_get(full_response_gdo, GNSDK_GDO_CHILD_VIDEO_PRODUCT, 1, &product_gdo);

									/* Release the followup query's response object */
									gnsdk_manager_gdo_release(full_response_gdo);

								} /* else find_products ok*/
							} /* else set_gdo ok */
						} /* else option_set ok */
					}  /* if query_create ok */
				}  /* if !full */
			} /* end else */
		} /* if not full */
		else _display_last_error(__LINE__);
	}

	if (GNSDK_SUCCESS == error)
	{
		/* Get title GDO */
		error = gnsdk_manager_gdo_child_get(product_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &product_title_gdo );
		if (GNSDK_SUCCESS == error)
		{
			/* Get title and display */
			error = gnsdk_manager_gdo_value_get(product_title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &product_title );
			if (GNSDK_SUCCESS == error)
				printf("\n\nTitle: %s\n", product_title);
			else
				_display_last_error(__LINE__);
		}
		else _display_last_error(__LINE__);
	}

	/********************************************
	* Get Link cover art
	********************************************/
	if (GNSDK_SUCCESS == error)
	{
		/* Create the link query handle */
		error = gnsdk_link_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &link_query_handle);

		if (GNSDK_SUCCESS == error)
		{
			/* Set the input GDO */
			error = gnsdk_link_query_set_gdo(link_query_handle, product_gdo);
			if (GNSDK_SUCCESS == error)
			{
				/* Set the thumbnail size option */
				error = gnsdk_link_query_option_set(
					link_query_handle,
					GNSDK_LINK_OPTION_KEY_IMAGE_SIZE,
					GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_75
					);

				if (GNSDK_SUCCESS == error)
				{
					/* Fetch the image */
					error = gnsdk_link_query_content_retrieve(
						link_query_handle,                     /* Link query handle to retrieve content for  */
						gnsdk_link_content_cover_art,          /* Type of content to request */
						1,                                     /* Nth item of content_type to retrieve */
						&data_type,                            /* Pointer to receive the content data type */
						&buffer,                               /* Pointer to receive the buffer that contains the requested content */
						&buffer_size                           /* Pointer to receive the memory size pointed to by p_buffer */
						);
					if (GNSDK_SUCCESS == error)
					{
						printf("\nThumbnail cover art: %d byte JPEG\n", (gnsdk_uint32_t)buffer_size);

						/* Free the data when you are done with it */
						error = gnsdk_link_query_content_free(buffer);

						/* mark this function as successful! */
						rc = 0;
					}
					else _display_last_error(__LINE__);
				}
				else _display_last_error(__LINE__);
			}
			else _display_last_error(__LINE__);
		}
		else _display_last_error(__LINE__);

	}  /* if (got product GDO without error) */

	/********************************
	* Clean up and shutdown
	********************************/

	/* Release GDOs and Query Handles */
	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_manager_gdo_release(product_gdo);
	gnsdk_manager_gdo_release(product_title_gdo);
	gnsdk_video_query_release(query_handle);
	gnsdk_link_query_release(link_query_handle);

	return rc;

}  /* _do_link_lookup() */

