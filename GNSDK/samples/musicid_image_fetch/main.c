/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *  Name: musicid_image_fetch
 *  Description:
 *  This example does a text search and finds images based on gdo type (album or contributor).
 *  It also finds an image based on genre.
 *
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
#define GNSDK_LINK                  1
#define GNSDK_MUSICID               1
#define GNSDK_STORAGE_SQLITE        1
#define GNSDK_LOOKUP_LOCAL          1
#include "gnsdk.h"

/* Standard C headers - used by the sample app, but not required for GNSDK */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**********************************************
*    Test Data
**********************************************/

/* Simulate MP3 tag data. */
typedef struct mp3_s
{
	const char* album_title_tag;
	const char* artist_name_tag;
	const char* genre_tag;

} mp3_file_t;

/* Simulate a folder of MP3s.
 *
 * file 1: Online - At the time of writing, yields an album match but no cover art or artist images are available.
 *                  Fetches the genre image for the returned album's genre.
 *         Local - Same result.
 * file 2: Online - Yields an album match for album tag "Supernatural". Fetches the cover art for that album.
 *         Local - Same result.
 * file 3: Online - Yields an album matches for Phillip Glass. Fetches the cover art for the first album returned.
 *         Local - Yields an artist match for the artist tag "Phillip Glass". Fetches the artist image for Phillip Glass.
 */
static mp3_file_t
_mp3_folder[] =
{
	{"Ask Me No Questions",  "Low Commotion Blues Band",    "Rock"},
	{"Supernatural",         "Santana",                     GNSDK_NULL},
	{GNSDK_NULL,             "Phillip Glass",               GNSDK_NULL}
};

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
_process_sample_mp3s(
	gnsdk_user_handle_t user_handle,
	int                 use_local
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
				/* Process the mp3s. */
				_process_sample_mp3s(user_handle, use_local);

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


/*****************************************************************************
 *
 *    _SET_LOCALE
 *
 *  Set application locale. Note that this is only necessary if you are using
 *  locale-dependant fields such as genre, mood, origin, era, etc. Your app
 *  may or may not be accessing locale_dependent fields, but it does not hurt
 *  to do this initialization as a matter of course .
 *
 ****************************************************************************/
static int
_set_locale(
			gnsdk_user_handle_t user_handle
			)
{
	gnsdk_locale_handle_t locale_handle = GNSDK_NULL;
	gnsdk_error_t         error         = GNSDK_SUCCESS;
	int                   rc            = 0;
	
	
	error = gnsdk_manager_locale_load(
		GNSDK_LOCALE_GROUP_MUSIC,               /* Locale group */
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
	
	/* Initialize the MusicID Library */
	if (0 == rc)
	{
		error = gnsdk_musicid_initialize(sdkmgr_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
	}

	/* Initialize the Link Content Library */
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

} /* _init_gnsdk() */


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
 *    _GET_GENRE_LIST
 *
 ***************************************************************************/
static int
_get_genre_list(
	gnsdk_user_handle_t  user_handle,
	gnsdk_list_handle_t* p_genre_list_handle
	)
{
	gnsdk_error_t       error       = GNSDK_SUCCESS;
	gnsdk_list_handle_t list_handle = GNSDK_NULL;
	
	
	/* Get the genre list handle. This will come from our pre-loaded locale.
	 Be sure these params match the ones used in get_locale to avoid loading a different list into memory.
	 
	 NB: If you plan to do many genre searches, it is most efficient to get this handle once during
	 initialization (after setting your locale) and then only release it before shutdown.
	 */
	error = gnsdk_manager_list_retrieve(
		GNSDK_LIST_TYPE_GENRES,
		GNSDK_LANG_ENGLISH,
		GNSDK_REGION_DEFAULT,
		GNSDK_DESCRIPTOR_SIMPLIFIED,
		user_handle,
		GNSDK_NULL,                                 /* optional status callback */
		GNSDK_NULL,                                 /* optional data to be passed to the callback */
		&list_handle
	);
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		return -1;
	}
	
	*p_genre_list_handle = list_handle;
	return 0;
	
}  /* _get_genre_list() */


/***************************************************************************
 *
 *    _DO_LIST_SEARCH
 *
 ***************************************************************************/
static int
_do_list_search(
	const char*                  input,
	gnsdk_list_handle_t          list_handle,
	gnsdk_list_element_handle_t* p_element_handle
	)
{
	gnsdk_list_element_handle_t element_handle = GNSDK_NULL;
	gnsdk_cstr_t                value          = GNSDK_NULL;
	gnsdk_uint32_t              level          = 0;
	int                         rc             = 0;
	gnsdk_error_t               error          = GNSDK_SUCCESS;


	error = gnsdk_manager_list_get_element_by_string(list_handle, input, &element_handle);
	if (GNSDK_SUCCESS != error)
	{
		if (GNSDKERR_NotFound == GNSDKERR_ERROR_CODE(error))
		{
			printf("Unable to find list element for the input string.\n");
		}
		else
		{
			_display_last_error(__LINE__);
		}
	}
	else
	{
		error = gnsdk_manager_list_element_get_level(element_handle, &level);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			error = gnsdk_manager_list_element_get_display_string(element_handle, &value);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}
			else
			{
				printf("List element result: %s (level %d)\n", value, level);
			}
		}
		*p_element_handle = element_handle;
	}

	if (GNSDK_SUCCESS != error)
	{
		rc = -1;
	}

	return rc;

} /* _do_list_search() */


/***************************************************************************
 *
 *    _FETCH_IMAGE
 *
 ***************************************************************************/
static int
_fetch_image(
	gnsdk_link_query_handle_t query_handle,
	gnsdk_link_content_type_t image_type,
	const char*               image_type_str
	)
{
	gnsdk_link_data_type_t data_type   = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer      = GNSDK_NULL;
	gnsdk_size_t           buffer_size = 0;
	int                    rc          = 0;
	gnsdk_error_t          error       = GNSDK_SUCCESS;

	error = gnsdk_link_query_content_retrieve(query_handle, image_type, 1, &data_type, &buffer, &buffer_size);
	if (GNSDK_SUCCESS == error)
	{
		/* data_type will always be == gnsdk_link_data_image_jpeg */

		/* Do something with the image, e.g. display, save, etc. Here we just print the size. */
		printf("\nRETRIEVED: %s: %d byte JPEG\n", image_type_str, (gnsdk_uint32_t)buffer_size);

		/* free the data when you are done with it */
		error = gnsdk_link_query_content_free(buffer);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
	}
	else
	{
		rc = -1;
		if (GNSDKERR_NotFound != GNSDKERR_ERROR_CODE(error))
		{
			_display_last_error(__LINE__);
		}
		else
		{
			/* Do not return error code for not found. */
			/* For image to be fetched, it must exist in the size specified and you must be entitled to fetch images. */
			printf("NOT FOUND: %s\n", image_type_str);
		}
	}

	return rc;

}  /* _fetch_image() */


/***************************************************************************
 *
 *    _PERFORM_IMAGE_FETCH
 *
 * This function performs a text lookup and image fetch
 *
 ***************************************************************************/
static int
_perform_image_fetch(
	gnsdk_gdo_handle_t  match_gdo,
	gnsdk_cstr_t        gdo_type,
	gnsdk_user_handle_t user_handle,
	int                 use_local
	)
{
	gnsdk_link_query_handle_t query_handle         = GNSDK_NULL;
	gnsdk_error_t             error                = GNSDK_SUCCESS;
	gnsdk_cstr_t              request_image_size   = GNSDK_NULL;
	int                       rc                   = -1;

	if ((match_gdo == GNSDK_NULL) || (gdo_type == GNSDK_NULL))
	{
		printf("Must pass a GDO and type\n");
		return rc;
	}

	/* Create the query handle without a callback or callback data (GNSDK_NULL) */
	if (gnsdk_link_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle) != GNSDK_SUCCESS)
	{
		_display_last_error(__LINE__);
		return rc;
	}

	/* Set the input GDO */
	error = gnsdk_link_query_set_gdo(query_handle, match_gdo);

	if (error != GNSDK_SUCCESS)
	{
		_display_last_error(__LINE__);
	}

	/* set our desired image size */
	if (!use_local)
	{
		/* Set preferred image size */
		request_image_size = GNSDK_CONTENT_DATA_SIZE_VALUE_170;
	}
	else 
	{
		/* Select an image size available in our local store */
		error = gnsdk_lookup_local_storage_info_get(
					GNSDK_LOOKUP_LOCAL_STORAGE_CONTENT,
					GNSDK_LOOKUP_LOCAL_STORAGE_IMAGE_SIZE,
					1,
					&request_image_size
				);

		if (error != GNSDK_SUCCESS)
		{
			_display_last_error(__LINE__);
		}
	}

	/* Specify the desired image size */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_link_query_option_set(
			query_handle,
			GNSDK_LINK_OPTION_KEY_IMAGE_SIZE,
			request_image_size
			);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			/* Perform the image fetch */
			if (0 == strcmp(gdo_type, GNSDK_GDO_TYPE_ALBUM))
			{
				/* If album type get cover art */
				rc = _fetch_image(query_handle, gnsdk_link_content_cover_art, "cover art");

				/* if no cover art, try to get the album's artist image */
				if (rc != 0)
				{
					rc = _fetch_image(query_handle, gnsdk_link_content_image_artist, "artist image");

					/* if no artist image, try to get the album's genre image so we have something to display */
					if (rc != 0)
					{
						rc = _fetch_image(query_handle, gnsdk_link_content_genre_art, "genre image");
					}
				}

			}
			else if (0 == strcmp(gdo_type, GNSDK_GDO_TYPE_CONTRIBUTOR))
			{
				/* If contributor type get artist image */
				rc = _fetch_image(query_handle, gnsdk_link_content_image_artist, "artist image");

				/* if no artist image, try to get the contributor's genre image so we have *something* to display */
				if (rc != 0)
				{
					rc = _fetch_image(query_handle, gnsdk_link_content_genre_art, "genre image");
				}
			}
			else
			{
				printf("Unsupported gdo_type, must be ALBUM or CONTRIBUTOR\n");
			}
		}
	}

	/* Release the Link query handle */
	gnsdk_link_query_release(query_handle);

	return rc;

}   /* _perform_image_fetch() */


/***************************************************************************
 *
 *    _FIND_GENRE_IMAGE
 *
 * This function performs a text lookup of a genre string.
 * If there is a match, the genre image is fetched.
 *
 ***************************************************************************/
static void
_find_genre_image(
	gnsdk_user_handle_t user_handle,
	int                 use_local,
	const char*         genre,
	gnsdk_list_handle_t genre_list_handle,
	int*                p_got_match
	)
{
	gnsdk_error_t               error                = GNSDK_SUCCESS;
	gnsdk_link_query_handle_t   query_handle         = GNSDK_NULL;
	gnsdk_list_element_handle_t element_handle       = GNSDK_NULL;
	gnsdk_cstr_t				request_image_size   = GNSDK_NULL;
	int                         got_match            = 0;

	printf("Genre String Search\n");

	if (genre == NULL)
	{
		printf("Must pass a genre\n");
		return;
	}

	printf( "%-15s: %s\n", "genre", genre );

	/* Set the query handle */
	error = gnsdk_link_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);

	if (error != GNSDK_SUCCESS)
	{
		_display_last_error(__LINE__);
		return;
	}

	/* Find the list element for our input string */
	error = _do_list_search(genre, genre_list_handle, &element_handle);
	if (error == GNSDK_SUCCESS)
	{
		/* we were able to idenfity the input genre string */
		got_match = 1;

		error = gnsdk_link_query_set_list_element(query_handle, element_handle);
		if (error != GNSDK_SUCCESS)
		{
			_display_last_error(__LINE__);
		}
		gnsdk_manager_list_element_release(element_handle);
	}

	/* set our desired image size */
	if (!use_local)
	{
		/* Set preferred image size */
		request_image_size = GNSDK_CONTENT_DATA_SIZE_VALUE_170;
	}
	else 
	{
		/* Select an image size available in our local store */
		error = gnsdk_lookup_local_storage_info_get(
			GNSDK_LOOKUP_LOCAL_STORAGE_CONTENT,
			GNSDK_LOOKUP_LOCAL_STORAGE_IMAGE_SIZE,
			1,
			&request_image_size
			);

		if (error != GNSDK_SUCCESS)
		{
			_display_last_error(__LINE__);
		}
	}

	/* Specify the desired image size */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_link_query_option_set(
			query_handle,
			GNSDK_LINK_OPTION_KEY_IMAGE_SIZE,
			request_image_size
			);
			
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			/* Perform the image fetches */
			_fetch_image(query_handle, gnsdk_link_content_genre_art, "genre image");
		}
	}

	/* Release the Link query handle */
	gnsdk_link_query_release(query_handle);

	if (p_got_match)
	{
		*p_got_match = got_match;
	}

}  /* _find_genre_image */


/***************************************************************************
 *
 *    _DO_SAMPLE_TEXT_QUERY
 *
 * This function performs a text lookup using musicid. If there is a match,
 * the associated image is fetched.
 *
 ***************************************************************************/
static int
_do_sample_text_query(
	gnsdk_user_handle_t user_handle,
	int                 use_local,
	const char*         album_title,
	const char*         artist_name,
	int*                p_got_match
	)
{
	gnsdk_error_t                error        = GNSDK_SUCCESS;
	gnsdk_musicid_query_handle_t query_handle = GNSDK_NULL;
	gnsdk_gdo_handle_t           response_gdo = GNSDK_NULL;
	gnsdk_gdo_handle_t           match_gdo    = GNSDK_NULL;
	gnsdk_cstr_t                 gdo_type     = GNSDK_NULL;
	gnsdk_uint32_t               count        = 0;
	int                          got_match    = 0;
	int                          rc           = 0;


	printf("MusicID Text Match Query\n");

	if ((album_title == NULL) && (artist_name == NULL))
	{
		printf("Must pass album title or artist name\n");
		return -1;
	}

	/* Set the input text. */
	error = gnsdk_musicid_query_create(user_handle, GNSDK_NULL, GNSDK_NULL, &query_handle);

	if (error != GNSDK_SUCCESS)
	{
		_display_last_error(__LINE__);
		return -1;
	}

	if (album_title != GNSDK_NULL)
	{
		error = gnsdk_musicid_query_set_text( query_handle, GNSDK_MUSICID_FIELD_ALBUM, album_title );
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			printf( "%-15s: %s\n", "album title", album_title );    /*    show the fields that we have set    */
		}
	}

	if ((GNSDK_SUCCESS == error) && (artist_name != GNSDK_NULL))
	{
		error = gnsdk_musicid_query_set_text( query_handle, GNSDK_MUSICID_FIELD_TRACK_ARTIST, artist_name );
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			printf( "%-15s: %s\n", "artist name", artist_name );
		}
	}

	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_musicid_query_option_set(query_handle, GNSDK_MUSICID_OPTION_ENABLE_CONTENT_DATA, GNSDK_VALUE_TRUE);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
	}
	/* Perform the query */
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_musicid_query_find_matches(query_handle, &response_gdo);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
		else
		{
			error = gnsdk_manager_gdo_child_count(response_gdo, GNSDK_GDO_CHILD_MATCH, &count);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}
			else
			{
				printf( "Number matches = %d\n\n", count);

				/* Get the first match type */
				if (count > 0)
				{
					/* OK, we got at least one match. */
					got_match = 1;

					/* Just use the first match for demonstration. */
					error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_MATCH, 1, &match_gdo);
					if (error != GNSDK_SUCCESS)
					{
						_display_last_error(__LINE__);
					}
					else
					{
						error = gnsdk_manager_gdo_get_type(match_gdo, &gdo_type);
						if (GNSDK_SUCCESS != error)
						{
							_display_last_error(__LINE__);
						}
						else
						{
							printf( "First Match GDO type: %s\n", gdo_type);

							/* Get the best image for the match */
							rc = _perform_image_fetch(match_gdo, gdo_type, user_handle, use_local);
						}
					}
				}
			}
		}
	}  /* if GNSDK_SUCCESS */

	/* Clean up */
	gnsdk_musicid_query_release(query_handle);
	gnsdk_manager_gdo_release(response_gdo);
	gnsdk_manager_gdo_release(match_gdo);

	if (GNSDK_SUCCESS != error)
	{
		rc = -1;
	}

	if ((rc == 0) && (p_got_match))
	{
		*p_got_match = got_match;
	}

	return rc;

}  /* _do_sample_text_query() */


/***************************************************************************
 *
 *    _PROCESS_SAMPLE_MP3
 *
 ***************************************************************************/
static void
_process_sample_mp3s(
	gnsdk_user_handle_t user_handle,
	int                 use_local
	)
{
	gnsdk_list_handle_t genre_list_handle  = GNSDK_NULL;
	gnsdk_uint32_t      file_index         = 0;
	mp3_file_t*         mp3_file           = GNSDK_NULL;
	int                 got_match          = 0;
	int                 rc                 = 0;
	
	/* Get a handle to the genre list */
	rc = _get_genre_list(user_handle, &genre_list_handle);
	if (rc == 0)
	{
		/* Simulate iterating a sample of mp3s. */
		for (file_index = 0; file_index < sizeof(_mp3_folder)/sizeof(mp3_file_t); file_index++)
		{
			printf("\n\n***** Processing File %d *****\n", file_index);
			mp3_file = &_mp3_folder[file_index];

			/* Do a music text query and fetch image from result. */
			_do_sample_text_query(user_handle, use_local, mp3_file->album_title_tag, mp3_file->artist_name_tag, &got_match);

			/* If there were no results from the musicid query, try getting the genre image. */
			if (0 == got_match)
			{
				if (GNSDK_NULL != mp3_file->genre_tag)
				{
					_find_genre_image(user_handle, use_local, mp3_file->genre_tag, genre_list_handle, &got_match);
				}
			}

			/* did we succesfully find a relevant image? */
			if (0 == got_match)
			{
				printf("\nBecause there was no match result for any of the input tags, you may want to associated the\ngeneric music image with this track, music_75x75.jpg, music_170x170.jpg or music_300x300.jpg\n");
			}
		}
		gnsdk_manager_list_release(genre_list_handle);
	}

}  /* _process_sample_mp3s() */
