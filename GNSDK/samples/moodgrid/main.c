/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 * Name: moodgrid
 * Description:
 * Moodgrid is the GNSDK library that generates playlists based on Mood by simply accessing parts of the Grid.
 * moodgrid APIs enable an application to:
 * 01. Discover and enumerate all datasources available for Moodgrid (from both offline and online sources )
 * 02. Create and administer data representation of Moodgrid for different types of datasources and grid types.
 * 03. Query a grid cell for a playlist based on the Mood it represents.
 * 04. Set Pre Filters on the Moodgrid for Music Genre, Artist Origin and Artist Era.
 * 05. Manage results.
 * Datasources : Offline datasources for Moodgrid can be created by using Gnsdk Playlist. This sample demonstrates this.
 * Steps:
 *  See inline comments below.
 * Notes:
 * For clarity and simplicity error handling in not shown here.
 * Refer "logging" sample to learn about GNSDK error handling.

 *  Command-line Syntax:
 *  sample <client_id> <client_id_tag> <license> [local|online]
 */

/* GNSDK headers
 *
 * Define the modules your application needs.
 * These constants enable inclusion of headers and symbols in gnsdk.h.
 * Define GNSDK_LOOKUP_LOCAL because this program has the potential to do local queries.
 * For local queries, a Gracenote local database must be present.
 */
#define GNSDK_PLAYLIST              1
#define GNSDK_MOODGRID              1
#define GNSDK_STORAGE_SQLITE        1
#define GNSDK_LOOKUP_LOCAL          1
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
	int                  use_local,
	gnsdk_user_handle_t* p_user_handle
	);

static void
_shutdown_gnsdk(
	gnsdk_user_handle_t user_handle
	);

static void
_perform_sample_moodgrid(
	gnsdk_user_handle_t user_handle
	);

/******************************************************************
 *
 *    MAIN
 *
 ******************************************************************/
int
main( int argc, char* argv[] )
{
	gnsdk_user_handle_t user_handle        = GNSDK_NULL;
	const char*         client_id          = NULL;
	const char*         client_id_tag      = NULL;
	const char*         client_app_version = "1.0.0.0"; /* Version of your application */
	const char*         license_path       = NULL;
	int                 use_local          = -1;
	int                 rc                 = 0;
	
	if (argc == 5)
	{
		client_id     = argv[1];
		client_id_tag = argv[2];
		license_path  = argv[3];
		if (!strcmp(argv[4], "online"))
		{
			use_local = 0;
		}
		else if (!strcmp(argv[4], "local"))
		{
			use_local = 1;
		}
		
		/* GNSDK initialization */
		if (use_local != -1)
		{
			rc = _init_gnsdk(
				client_id,
				client_id_tag,
				client_app_version,
				license_path,
				use_local,
				&user_handle
			);
			if (0 == rc)
			{
				/* Generate mood grid for simulated music collection and generate some playlists */
				_perform_sample_moodgrid(user_handle);
			   
				/* Clean up and shutdown */
				_shutdown_gnsdk( user_handle );
			}
		}
	}
	if (argc != 5 || use_local == -1)
	{
		printf( "\nUsage:\n%s clientid clientidtag license [local|online]\n", argv[0] );
		rc = -1;
	}
	
	return rc;
	
}  /* main() */


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
		"\nerror from: %s()  [on line %d]\n\t0x%08x %s\n",
		error_info->error_api,
		line_num,
		error_info->error_code,
		error_info->error_description
	);
	
} /* _display_last_error() */


/******************************************************************
 *
 *    _GET_USER_HANDLE
 *
 *    Load existing user handle, or register new one.
 *
 *    GNSDK requires a user handle instance to perform queries.
 *    User handles encapsulate your Gracenote provided Client ID
 *    which is unique for your application. User handles are
 *    registered once with Gracenote then must be saved by
 *    your application and reused on future invocations.
 *
 *****************************************************************/
static int
_get_user_handle(
	const char*          client_id,
	const char*          client_id_tag,
	const char*          client_app_version,
	int                  use_local,
	gnsdk_user_handle_t* p_user_handle
	)
{
	gnsdk_user_handle_t user_handle               = GNSDK_NULL;
	gnsdk_cstr_t		user_reg_mode             = GNSDK_NULL;
	gnsdk_str_t         serialized_user           = GNSDK_NULL;
	gnsdk_char_t		serialized_user_buf[1024] = {0};
	gnsdk_bool_t        b_localonly               = GNSDK_FALSE;
	gnsdk_error_t       error                     = GNSDK_SUCCESS;
	FILE*               file                      = NULL;
	int                 rc                        = 0;
	
	/* Creating a GnUser is required before performing any queries to Gracenote services,
	 * and such APIs in the SDK require a GnUser to be provided. GnUsers can be created
	 * 'Online' which means they are created by the Gracenote backend and fully vetted.
	 * Or they can be create 'Local Only' which means they are created locally by the
	 * SDK but then can only be used locally by the SDK.
	 */
	
	/* If the application cannot go online at time of user-regstration it should
	 * create a 'local only' user. If connectivity is available, an Online user should
	 * be created. An Online user can do both Local and Online queries.
	 */
	if (use_local)
	{
		user_reg_mode = GNSDK_USER_REGISTER_MODE_LOCALONLY;
	}
	else
	{
		user_reg_mode = GNSDK_USER_REGISTER_MODE_ONLINE;
	}
	
	/* Do we have a user saved locally? */
	file = fopen("user.txt", "r");
	if (file)
	{
		fgets(serialized_user_buf, sizeof(serialized_user_buf), file);
		fclose(file);
		
		/* Create the user handle from the saved user */
		error = gnsdk_manager_user_create(serialized_user_buf, client_id, &user_handle);
		if (GNSDK_SUCCESS == error)
		{
			error = gnsdk_manager_user_is_localonly(user_handle, &b_localonly);
			if (!b_localonly || (strcmp(user_reg_mode, GNSDK_USER_REGISTER_MODE_LOCALONLY) == 0))
			{
				*p_user_handle = user_handle;
				return 0;
			}
			
			/* else desired regmode is online, but user is localonly - discard and register new online user */
			gnsdk_manager_user_release(user_handle);
		}
		
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
	}
	else
	{
		printf("\nInfo: No stored user - this must be the app's first run.\n");
	}
	
	/*
	 * Register new user
	 */
	error = gnsdk_manager_user_register(
		user_reg_mode,
		client_id,
		client_id_tag,
		client_app_version,
		&serialized_user
	);
	if (GNSDK_SUCCESS == error)
	{
		/* Create the user handle from the newly registered user */
		error = gnsdk_manager_user_create(serialized_user, client_id, &user_handle);
		if (GNSDK_SUCCESS == error)
		{
			/* save newly registered user for use next time */
			file = fopen("user.txt", "w");
			if (file)
			{
				fputs(serialized_user, file);
				fclose(file);
			}
		}
		
		gnsdk_manager_string_free(serialized_user);
	}
	
	if (GNSDK_SUCCESS == error)
	{
		*p_user_handle = user_handle;
		rc = 0;
	}
	else
	{
		_display_last_error(__LINE__);
		rc = -1;
	}
	
	return rc;
	
} /* _get_user_handle() */

/******************************************************************
 *
 *    _DISPLAY_EMBEDDED_DB_INFO
 *
 *    Display local Gracenote DB information.
 *
 ******************************************************************/
static void
_display_embedded_db_info(void)
{
	gnsdk_cstr_t   gdb_version = GNSDK_NULL;
	gnsdk_error_t  error;
	
	error = gnsdk_lookup_local_storage_info_get(
		GNSDK_LOOKUP_LOCAL_STORAGE_METADATA,
		GNSDK_LOOKUP_LOCAL_STORAGE_GDB_VERSION,
		1,
		&gdb_version
	);
	if (!error)
	{
		printf("Gracenote DB Version : %s\n", gdb_version);
	}
	else
	{
		_display_last_error(__LINE__);
	}
	
}  /* _display_embedded_db_info() */

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
	printf(
		"\nGNSDK Product Version    : %s \t(built %s)\n",
		gnsdk_manager_get_product_version(),
		gnsdk_manager_get_build_date()
	);
	
}  /* _display_gnsdk_product_info() */


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
	
}  /* _enable_logging() */


/******************************************************************
 *
 *    _SET_LOCALE
 *
 *    Set the application Locale.
 *
 ******************************************************************/
static int
_set_locale(
	gnsdk_user_handle_t user_handle
	)
{
	gnsdk_locale_handle_t locale_handle = GNSDK_NULL;
	gnsdk_error_t         error         = GNSDK_SUCCESS;
	int                   rc            = 0;
	
	error = gnsdk_manager_locale_load(
		GNSDK_LOCALE_GROUP_PLAYLIST,            /* Locale group */
		GNSDK_LANG_ENGLISH,                     /* Language */
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
	
}  /* _set_locale() */


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
	int                  use_local,
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
	
	if (use_local)
	{
		/* Set folder location of local database */
		if (0 == rc)
		{
			error = gnsdk_storage_sqlite_option_set(
				GNSDK_STORAGE_SQLITE_OPTION_STORAGE_FOLDER,
				"../../sample_data/sample_db"
			);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
		}
		
		/* Initialize the Lookup Local Library */
		if (0 == rc)
		{
			error = gnsdk_lookup_local_initialize(sdkmgr_handle);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
			else
			{
				/* Display information about our local EDB */
				_display_embedded_db_info();
			}
		}
	}
	
	/* Initialize the Playlist Library */
	if (0 == rc)
	{
		error = gnsdk_playlist_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
		else
		{
			/* Specify the location for our collection store. */
			error = gnsdk_playlist_storage_location_set("../../sample_data");
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
		}
	}
	
	/* Initialize the Moodgrid Library */
	if (0 == rc)
	{
		error = gnsdk_moodgrid_initialize(sdkmgr_handle);
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
			use_local,
			&user_handle
		);
	}
	
	/* Set the user option to use our local Gracenote DB unless overridden. */
	if (use_local)
	{
		if (0 == rc)
		{
			error = gnsdk_manager_user_option_set(
				user_handle,
				GNSDK_USER_OPTION_LOOKUP_MODE,
				GNSDK_LOOKUP_MODE_LOCAL
			);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
		}
	}
	
	/* Set the 'locale' to return locale-specifc results values. This examples loads an English locale. */
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
		/* return the User handle for use at query time */
		*p_user_handle = user_handle;
	}
	
	return rc;
	
}  /* _init_gnsdk() */


/***************************************************************************
 *
 *    _SHUTDOWN_GNSDK
 *
 *     When your program is terminating, or you no longer need GNSDK, you should
 *     call gnsdk_manager_shutdown(). No other shutdown operations are required.
 *     gnsdk_manager_shutdown() also shuts down all other modules, regardless
 *     of the number of times they have been initialized.
 *     You can shut down individual modules while your program is running with
 *     their dedicated shutdown functions in order to free up resources.
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
	
	/* Shutdown the Manager to shutdown all libraries */
	gnsdk_manager_shutdown();
	
}  /* _shutdown_gnsdk() */


/***************************************************************************
 *
 *   _DO_MOODGRID_PRESENTATION
 *
 *   Do Moodgrid Presentation
 *
 ***************************************************************************/
static gnsdk_error_t
_do_moodgrid_presentation(
	gnsdk_user_handle_t                user_handle,
	gnsdk_moodgrid_presentation_type_t type,
	gnsdk_moodgrid_provider_handle_t   provider
	)
{
	gnsdk_error_t                        error        = GNSDK_SUCCESS;
	gnsdk_moodgrid_presentation_handle_t presentation = GNSDK_NULL;
	gnsdk_uint32_t                       max_x        = 0;
	gnsdk_uint32_t                       max_y        = 0;
	gnsdk_cstr_t                         value        = GNSDK_NULL;


	/* get the details for the provider */
	error = gnsdk_moodgrid_provider_get_data(provider, GNSDK_MOODGRID_PROVIDER_NAME, &value);
	printf("\n%s : %s \n", "GNSDK_MOODGRID_PROVIDER_NAME", value);

	if (!error)
	{
		error = gnsdk_moodgrid_provider_get_data(provider, GNSDK_MOODGRID_PROVIDER_TYPE, &value);
		printf("\n%s : %s \n", "GNSDK_MOODGRID_PROVIDER_TYPE", value);
	}

	if (!error)
	{
		error = gnsdk_moodgrid_provider_get_data(provider, GNSDK_MOODGRID_PROVIDER_NETWORK_USE, &value);
		printf("\n%s : %s \n", "GNSDK_MOODGRID_PROVIDER_NETWORK_USE", value);
	}

	/* query the presentation type for its dimensions */
	if (!error)
	{
		error = gnsdk_moodgrid_presentation_type_dimension(type, &max_x, &max_y);
	}

	/* create a moodgrid presentation for the specified type */
	if (!error)
	{
		error = gnsdk_moodgrid_presentation_create(
			user_handle,         /* user handle                  */
			type,                /* Moodgrid Presentation Type   */
			GNSDK_NULL,          /* Callback function            */
			GNSDK_NULL,          /* Callback data                */
			&presentation        /* out - Moodgrid Presentation  */
			);
		if (error)
		{
			_display_last_error(__LINE__);
		}
	}

	/* set a filter  or filters
	   comment this out to use filters.

	   if (!error)
	   {
		error = gnsdk_moodgrid_presentation_filter_set(presentation,"FILTER",
							   GNSDK_MOODGRID_FILTER_LIST_TYPE_GENRE,
							   GNSDK_LIST_MUSIC_GENRE_ROCK,
							   GNSDK_MOODGRID_FILTER_CONDITION_INCLUDE);
	   }
	 */

	/* enumerate through the moodgrid getting individual data and results */
	if (!error)
	{
		gnsdk_uint32_t x = 1;
		gnsdk_uint32_t y = 1;

		gnsdk_uint32_t count = 0;
		gnsdk_cstr_t   name  = GNSDK_NULL;

		gnsdk_moodgrid_result_handle_t results = GNSDK_NULL;

		printf("\n PRINTING MOODGRID %d x %d GRID \n", max_x, max_y);
		for (x = 1; x <= max_x; ++x)
		{
			for (y = 1; y <= max_y; ++y)
			{
				/* get the name for the grid coordinates in the language defined by Locale*/
				error = gnsdk_moodgrid_presentation_get_mood_name(
					presentation,                 /* Presentation handle  */
					x,                            /* mood x coordinate    */
					y,                            /* mood y coordinate    */
					&name                         /* out mood name    */
					);

				/* find the recommendation for the mood */
				if (!error)
				{
					error = gnsdk_moodgrid_presentation_find_recommendations(
						presentation,             /* Moodgrid Presentation */
						provider,                 /* Moodgrid Provider     */
						x,                        /* mood x coordinate     */
						y,                        /* mood y coordinate     */
						&results                  /* out results           */
						);
				}

				/* count the number of results */
				if (!error)
				{
					error = gnsdk_moodgrid_results_count(results, &count);
				}

				/* iterate the results for the idents */
				if (!error)
				{
					gnsdk_uint32_t j     = 0;
					gnsdk_cstr_t   ident = GNSDK_NULL;
					gnsdk_cstr_t   group = GNSDK_NULL;

					printf("\n\n\tX:%d  Y:%d name: %s count: %d \n", x, y, name, count);

					for (j = 0; j < count && !error; ++j)
					{
						error = gnsdk_moodgrid_results_enum(results, j, &ident, &group);
						if (!error)
						{
							printf("\n\tX:%d Y:%d \nident:\t%s  \ngroup:\t%s\n", x, y, ident, group);
						}
					}
				}

				/* error case printing */
				if (error)
				{
					printf("\n\n\tX:%d  Y:%d ERROR!!  \n\n", x, y);
					_display_last_error(__LINE__);
				}

				/* release the results */
				gnsdk_moodgrid_results_release(results);
				results = GNSDK_NULL;
			}
		}
	}
	/* cleanup */
	gnsdk_moodgrid_presentation_release(presentation);

	return error;

}   /*  _do_moodgrid_presentation() */


/***************************************************************************
 *
 *    _PERFORM_SAMPLE_MOODGRID
 *
 ***************************************************************************/
static void
_perform_sample_moodgrid(
	gnsdk_user_handle_t user_handle
	)
{
	gnsdk_playlist_collection_handle_t h_collection = GNSDK_NULL;
	gnsdk_moodgrid_provider_handle_t   h_provider   = GNSDK_NULL;
	gnsdk_error_t                      error        = GNSDK_SUCCESS;


	/* load the offline collection  */
	printf("\nLoading sample collection");
	error = gnsdk_playlist_storage_load_collection(
		"sample_collection",
		&h_collection
		);
	if (error)
	{
		_display_last_error(__LINE__);
	}
	/* enumerate for a moodgrid provider - in this case the first one available*/
	if (!error)
	{
		printf("\nEnumerating for the first Moodgrid Provider available");
		error = gnsdk_moodgrid_provider_enum(0, &h_provider);
		if (error)
		{
			_display_last_error(__LINE__);
		}
	}


	/* create, query and print a  5 x  5  moodgrid  */
	if (!error)
	{
		error = _do_moodgrid_presentation(
			user_handle,
			gnsdk_moodgrid_presentation_type_5x5,
			h_provider
			);
	}

	/* create, query and print a 10 x 10 moodgrid*/
	if (!error)
	{
		error = _do_moodgrid_presentation(
			user_handle,
			gnsdk_moodgrid_presentation_type_10x10,
			h_provider
			);
	}

	/* cleanup */
	gnsdk_playlist_collection_release(h_collection);
	gnsdk_moodgrid_provider_release(h_provider);

}  /* _perform_sample_moodgrid() */

