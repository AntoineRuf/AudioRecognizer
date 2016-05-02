/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/*
 *	Name: playlist
 *	Description:
 *	Playlist is the GNSDK library that generates playlists when integrated with the GNSDK MusicID or MusicID-File
 *	library (or both). Playlist APIs enable an application to:
 *	01. Create, administer, populate, and synchronize a collection summary.
 *	02. Store a collection summary within a local storage solution.
 *	03. Validate PDL statements.
 *	04. Generate Playlists using either the More Like This function or the general playlist generation function.
 *	05. Manage results.
 *	Streamline your Playlist implementation by using the provided More Like This function
 *	(gnsdk_playlist_generate_morelikethis), which contains the More Like This algorithm to generate
 *	optimal playlist results and eliminates the need to create and validate Playlist Definition
 *	Language statements.
 *	Steps:
 *	See inline comments below.
 *
 *	Command-line Syntax:
 *  sample <client_id> <client_id_tag> <license> [local|online]
 */

/* GNSDK headers
 *
 * Define the modules your application needs.
 * These constants enable inclusion of headers and symbols in gnsdk.h.
 * Define GNSDK_LOOKUP_LOCAL because this program has the potential to do local queries.
 * For local queries, a Gracenote local database must be present.
 */
#define GNSDK_PLAYLIST          1
#define GNSDK_MUSICID           1
#define GNSDK_STORAGE_SQLITE    1
#define GNSDK_LOOKUP_LOCAL              1
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
_perform_sample_playlist(
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
				/* Create collection summary from simulated collection and generate playlists. */
				_perform_sample_playlist(user_handle, use_local);
				
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
	gnsdk_locale_handle_t playlist_locale_handle = GNSDK_NULL;
	gnsdk_locale_handle_t music_locale_handle = GNSDK_NULL;
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
		&playlist_locale_handle			        /* Return handle */
	);
	if (GNSDK_SUCCESS == error)
	{
		/* Setting the 'locale' as default
		 * If default not set, no locale-specific results would be available
		 */
		error = gnsdk_manager_locale_set_group_default(playlist_locale_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
		
		/* The manager will hold onto the locale when set as default
		 * so it's ok to release our reference to it here
		 */
		gnsdk_manager_locale_release(playlist_locale_handle);
	}
	else
	{
		_display_last_error(__LINE__);
		rc = -1;
	}

	if (!rc)
	{
		error = gnsdk_manager_locale_load(
			GNSDK_LOCALE_GROUP_MUSIC,    	        /* Locale group */
			GNSDK_LANG_ENGLISH,                     /* Language */
			GNSDK_REGION_DEFAULT,                   /* Region */
			GNSDK_DESCRIPTOR_SIMPLIFIED,            /* Descriptor */
			user_handle,                            /* User handle */
			GNSDK_NULL,                             /* User callback function */
			0,                                      /* Optional data for user callback function */
			&music_locale_handle			        /* Return handle */
		);
		if (GNSDK_SUCCESS == error)
		{
			/* Setting the 'locale' as default
			 * If default not set, no locale-specific results would be available
			 */
			error = gnsdk_manager_locale_set_group_default(music_locale_handle);
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}

			/* The manager will hold onto the locale when set as default
			 * so it's ok to release our reference to it here
			 */
			gnsdk_manager_locale_release(music_locale_handle);
		}
		else
		{
			_display_last_error(__LINE__);
			rc = -1;
		}
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
			error = gnsdk_playlist_storage_location_set(".");
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
				rc = -1;
			}
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
*    _PLAYLIST_COLLECTION_POPULATE
*
*    Here we are doing basic MusicID queries on CDTOCs to populate a
*    Playlist Collection Summary.
*    Any GNSDK result GDO can be used for Collection Summary
*    population.
*
***************************************************************************/
static gnsdk_error_t
_playlist_collection_populate(
	gnsdk_user_handle_t                user_handle,
	int                                use_local,
	gnsdk_playlist_collection_handle_t h_playlist_collection
	)
{
	gnsdk_error_t                error              = GNSDK_SUCCESS;
	gnsdk_size_t                 count              = 0;
	gnsdk_uint32_t               count_ordinal      = 0;
	gnsdk_uint32_t               ident_count        = 0;
	gnsdk_musicid_query_handle_t query_handle       = GNSDK_NULL;
	gnsdk_gdo_handle_t           response_gdo       = GNSDK_NULL;
	gnsdk_gdo_handle_t           album_gdo          = GNSDK_NULL;
	gnsdk_cstr_t                 input_query_tocs[] =  {
		"150 13224 54343 71791 91348 103567 116709 132142 141174 157219 175674 197098 238987 257905",
		"182 23637 47507 63692 79615 98742 117937 133712 151660 170112 189281",
		"182 14035 25710 40955 55975 71650 85445 99680 115902 129747 144332 156122 170507",
		"150 10705 19417 30005 40877 50745 62252 72627 84955 99245 109657 119062 131692 141827 152207 164085 173597 187090 204152 219687 229957 261790 276195 289657 303247 322635 339947 356272",
		"150 14112 25007 41402 54705 69572 87335 98945 112902 131902 144055 157985 176900 189260 203342",
		"150 1307 15551 31744 45022 57486 72947 85253 100214 115073 128384 141948 152951 167014",
		"183 69633 96258 149208 174783 213408 317508",
		"150 19831 36808 56383 70533 87138 105157 121415 135112 151619 169903 189073",
		"182 10970 29265 38470 59517 74487 83422 100987 113777 137640 150052 162445 173390 196295 221582",
		"150 52977 87922 128260 167245 187902 215777 248265",
		"183 40758 66708 69893 75408 78598 82983 87633 91608 98690 103233 108950 111640 117633 124343 126883 132298 138783 144708 152358 175233 189408 201408 214758 239808",
		"150 92100 135622 183410 251160 293700 334140",
		"150 17710 33797 65680 86977 116362 150932 166355 183640 193035",
		"150 26235 51960 73111 93906 115911 142086 161361 185586 205986 227820 249300 277275 333000",
		"150 1032 27551 53742 75281 96399 118691 145295 165029 189661 210477 232501 254342 282525",
		"150 26650 52737 74200 95325 117675 144287 163975 188650 209350 231300 253137 281525 337875",
		"150 19335 35855 59943 78183 96553 111115 125647 145635 163062 188810 214233 223010 241800 271197",
		"150 17942 32115 47037 63500 79055 96837 117772 131940 148382 163417 181167 201745",
		"150 17820 29895 41775 52915 69407 93767 105292 137857 161617 171547 182482 204637 239630 250692 282942 299695 311092 319080",
		"182 21995 45882 53607 71945 80495 94445 119270 141845 166445 174432 187295 210395 230270 240057 255770 277745 305382 318020 335795 356120",
		"187 34360 64007 81050 122800 157925 195707 230030 255537 279212 291562 301852 310601",
		"150 72403 124298 165585 226668 260273 291185"
	};


	count = sizeof(input_query_tocs) / sizeof(input_query_tocs[0]);
	printf( "\nPopulating Collection Summary from sample TOCs" );
	/* Create the query handle */
	error = gnsdk_musicid_query_create(
		user_handle,
		GNSDK_NULL,     /* User callback function */
		GNSDK_NULL,     /* Optional data to be passed to the callback */
		&query_handle
		);

	/*
	   Set the option for retrieving DSP attributes.
	   Note: Please note that these attributes are entitlements to your user id. You must have them enabled in your licence.
	 */
	if (!error)
	{
		error =  gnsdk_musicid_query_option_set(
			query_handle,
			GNSDK_MUSICID_OPTION_ENABLE_SONIC_DATA,
			GNSDK_VALUE_TRUE
			);
	}
	/*
	   Set the option for retrieving Playlist attributes.
	   Note: Please note that these attributes are entitlements to your user id. You must have them enabled in your licence.
	 */
	if (!error)
	{
		error =  gnsdk_musicid_query_option_set(
			query_handle,
			GNSDK_MUSICID_OPTION_ENABLE_PLAYLIST,
			GNSDK_VALUE_TRUE
			);
	}

	if (!error)
	{
		if (use_local)
		{
			printf(" LOCAL lookup...");
			error = gnsdk_musicid_query_option_set(
				query_handle,
				GNSDK_MUSICID_OPTION_LOOKUP_MODE,
				GNSDK_LOOKUP_MODE_LOCAL
			);
		}
	}
	else
	{
		printf(" ONLINE lookup...");
	}

	for (count_ordinal = 0; count_ordinal < count && !error; ++count_ordinal)
	{
		/*Set the input TOC*/
		error = gnsdk_musicid_query_set_toc_string(query_handle, input_query_tocs[count_ordinal]);

		if (!error)
		{
			error = gnsdk_musicid_query_find_albums(query_handle, &response_gdo);
		}

		if (!error)
		{
			error = gnsdk_manager_gdo_child_get(response_gdo, GNSDK_GDO_CHILD_ALBUM, 1, &album_gdo);
		}

		/*  Add MusicID result to Playlist   */
		if (!error)
		{
			gnsdk_uint32_t     track_count       = 0;
			gnsdk_uint32_t     track_ordinal     = 0;
			gnsdk_gdo_handle_t track_gdo         = GNSDK_NULL;
			gnsdk_char_t       unique_ident[256] = {0};

			error = gnsdk_manager_gdo_child_count(album_gdo, GNSDK_GDO_CHILD_TRACK, &track_count);

			/*  To make playlist of tracks we add each and every track in the album to the collection summary */
			for (track_ordinal = 1; track_ordinal <= track_count && !error; ++track_ordinal)
			{
				error = gnsdk_manager_gdo_child_get(album_gdo, GNSDK_GDO_CHILD_TRACK, track_ordinal, &track_gdo);

				if (!error)
				{
					/* create a unique ident for every track that is added to the playlist.
					   Ideally the ident allows for the identification of which track it is.
					   e.g. path/filename.ext , or an id that can be externally looked up.
					 */
					if (sprintf(unique_ident, "%d_%d", count_ordinal, track_ordinal) > -1)
					{
						/*
							Add the the Album and Track GDO for the same ident so that we can
							query the Playlist Collection with both track and album level attributes.
						 */
						error = gnsdk_playlist_collection_add_gdo(h_playlist_collection, unique_ident, album_gdo);
						error = gnsdk_playlist_collection_add_gdo(h_playlist_collection, unique_ident, track_gdo);
					}
				}
				if (!error)
				{
					printf("..");
				}
				gnsdk_manager_gdo_release(track_gdo);
				track_gdo =  GNSDK_NULL;
			}
			gnsdk_manager_gdo_release(album_gdo);
			album_gdo = GNSDK_NULL;
		}

		/* cleanup */
		gnsdk_manager_gdo_release(response_gdo);
		response_gdo = GNSDK_NULL;
	}
	gnsdk_musicid_query_release(query_handle);

	/* count the albums recognized */
	error = gnsdk_playlist_collection_ident_count(h_playlist_collection, &ident_count);
	printf("\n Recognized %d tracks out of %d Album TOCS", ident_count, (gnsdk_uint32_t)count);

	if (ident_count == 0)
	{
		printf("\n Failed Recognition \n");
		error = -1;
	} 
	else
	{
		printf("\n Finished Recognition \n");
	}

	return error;

}  /* _playlist_collection_populate() */


/***************************************************************************
*
*    _PLAYLIST_COLLECTION_CREATE
*
*    Here we attempt to load an existing Playlist Collection Summary from the GNSDK
*    storage if one was previously stored. If not, we create a new Collection Summary
*    (which initially is empty) and populate it with media. We then store this
*    Collection Summary in the GNSDK storage.
*
***************************************************************************/
static gnsdk_error_t
_playlist_collection_create(
	gnsdk_user_handle_t                 user_handle,
	int                                 use_local,
	gnsdk_playlist_collection_handle_t* p_playlist_collection
	)
{
	gnsdk_error_t                      error               = GNSDK_SUCCESS;
	gnsdk_playlist_collection_handle_t playlist_collection = GNSDK_NULL;
	gnsdk_uint32_t                     count               = 0;
	gnsdk_char_t                       collection_name[300];


	error = gnsdk_playlist_storage_count_collections(&count);

	printf("\nCurrently stored collections :%d", count);

	if (count == 0)
	{
		printf("\nCreating a new collection");
		error = gnsdk_playlist_collection_create("sample_collection", &playlist_collection);

		if (!error)
		{
			error = _playlist_collection_populate(user_handle, use_local, playlist_collection);
		}
		if (!error)
		{
			printf("\nStoring collection... ");
			error = gnsdk_playlist_storage_store_collection(playlist_collection);
		}

		/*	Release the collection we created. */
		gnsdk_playlist_collection_release(playlist_collection);
	}

	/* get the count again */
	if (!error)
	{
		error = gnsdk_playlist_storage_count_collections(&count);
		printf("\nCurrently stored collections :%d", count);
	}

	if (!error)
	{
		error = gnsdk_playlist_storage_enum_collections(0, collection_name, sizeof(collection_name));
	}

	if (!error)
	{
		error = gnsdk_playlist_storage_load_collection(collection_name, &playlist_collection);
	}

	if (!error)
	{
		printf("\n Loading Collection '%s' from store", collection_name);
		*p_playlist_collection = playlist_collection;
	}
	else
	{
		printf("\n Failed to load Collection '%s' from store", collection_name);
		_display_last_error(__LINE__);
	}

	return error;

}  /* _playlist_collection_create() */



/***************************************************************************
*
*    _PLAYLIST_GET_ATTRIBUTE_VALUE
*
***************************************************************************/
static void
_playlist_get_attribute_value(
	gnsdk_gdo_handle_t                 h_playlist_gdo
	)
{
	gnsdk_error_t  error        = GNSDK_SUCCESS;
	gnsdk_cstr_t   attr_value   = GNSDK_NULL;

	/* Album name */
	error = gnsdk_manager_gdo_value_get(h_playlist_gdo, GNSDK_PLAYLIST_ATTRIBUTE_NAME_ALBUM, 1, &attr_value);
	if (!error) 
		printf("\t\t%s:%s\n", GNSDK_PLAYLIST_ATTRIBUTE_NAME_ALBUM, attr_value);


	/* Artist name */
	error = gnsdk_manager_gdo_value_get(h_playlist_gdo, GNSDK_PLAYLIST_ATTRIBUTE_NAME_ARTIST, 1, &attr_value);
	if (!error) 
		printf("\t\t%s:%s\n", GNSDK_PLAYLIST_ATTRIBUTE_NAME_ARTIST, attr_value);
			
	
	/* Artist Type */
	error = gnsdk_manager_gdo_value_get(h_playlist_gdo, GNSDK_PLAYLIST_ATTRIBUTE_NAME_ARTTYPE, 1, &attr_value);
	if (!error) 
		printf("\t\t%s:%s\n", GNSDK_PLAYLIST_ATTRIBUTE_NAME_ARTTYPE, attr_value);
			
	
	/*Artist Era */
	error = gnsdk_manager_gdo_value_get(h_playlist_gdo, GNSDK_PLAYLIST_ATTRIBUTE_NAME_ERA, 1, &attr_value);
	if (!error) 
		printf("\t\t%s:%s\n", GNSDK_PLAYLIST_ATTRIBUTE_NAME_ERA, attr_value);

	/*Artist Origin */
	error = gnsdk_manager_gdo_value_get(h_playlist_gdo, GNSDK_PLAYLIST_ATTRIBUTE_NAME_ORIGIN, 1, &attr_value);
	if (!error) 
		printf("\t\t%s:%s\n", GNSDK_PLAYLIST_ATTRIBUTE_NAME_ORIGIN, attr_value);

	/* Mood */
	error = gnsdk_manager_gdo_value_get(h_playlist_gdo, GNSDK_PLAYLIST_ATTRIBUTE_NAME_MOOD, 1, &attr_value);
	if (!error) 
		printf("\t\t%s:%s\n", GNSDK_PLAYLIST_ATTRIBUTE_NAME_MOOD, attr_value);
			
	
	/*Tempo*/
		error = gnsdk_manager_gdo_value_get(h_playlist_gdo, GNSDK_PLAYLIST_ATTRIBUTE_NAME_TEMPO, 1, &attr_value);
		if (!error) 
			printf("\t\t%s:%s\n", GNSDK_PLAYLIST_ATTRIBUTE_NAME_TEMPO, attr_value);

}  /* _playlist_get_attribute_value() */


/***************************************************************************
*
*    _ENUMERATE_PLAYLIST_RESULTS
*
*    The following illustrates how to get each  ident and its associated
*    GDO from a results handle.
*
***************************************************************************/
static void
_enumerate_playlist_results(
	gnsdk_user_handle_t                user_handle,
	gnsdk_playlist_collection_handle_t h_playlist_collection,
	gnsdk_playlist_results_handle_t    h_playlist_results
	)
{
	gnsdk_error_t                      error             = GNSDK_SUCCESS;
	gnsdk_gdo_handle_t                 h_gdo_attr        = GNSDK_NULL;
	gnsdk_cstr_t                       ident             = GNSDK_NULL;
	gnsdk_cstr_t                       collection_name   = GNSDK_NULL;
	gnsdk_uint32_t                     count_ordinal     = 0;
	gnsdk_uint32_t                     results_count     = 0;
	gnsdk_playlist_collection_handle_t h_temp_collection = GNSDK_NULL;


	error = gnsdk_playlist_results_count(h_playlist_results, &results_count);
	printf("Generated Playlist: %d\n", results_count);

	for (count_ordinal = 0; count_ordinal < results_count; ++count_ordinal)
	{
		error = gnsdk_playlist_results_enum(h_playlist_results, count_ordinal, &ident, &collection_name);
		printf("    %d: %s Collection Name:%s\n", count_ordinal+1, ident, collection_name);

		/*	The following illustrates how to get a collection handle
		   from the collection name string in the results enum function call.
		   It ensures that Joined collections as well as non joined collections will work with minimal overhead.
		 */
		if (!error)
		{
			error = gnsdk_playlist_collection_join_get_by_name(h_playlist_collection, collection_name, &h_temp_collection);
		}

		if (!error)
		{
			error = gnsdk_playlist_collection_get_gdo(h_temp_collection, user_handle, ident, &h_gdo_attr);
		}

		if (!error)
		{
			_playlist_get_attribute_value(h_gdo_attr);
		}

		/* cleanup */
		gnsdk_manager_gdo_release(h_gdo_attr);
		gnsdk_playlist_collection_release(h_temp_collection);
		h_temp_collection = GNSDK_NULL;
		h_gdo_attr        = GNSDK_NULL;
	}

}  /* _enumerate_playlist_results() */


/***************************************************************************
*
*    _PRINT_PLAYLIST_MORELLIKETHIS_OPTIONS
*
*    The following illustrates how to get the various morelikethis options.
*
***************************************************************************/
static void
_print_playlist_morelikethis_options(
	gnsdk_playlist_collection_handle_t h_playlist_collection
	)
{
	gnsdk_cstr_t value = GNSDK_NULL;


	gnsdk_playlist_morelikethis_option_get(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS,
		&value
		);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS :%s", value);

	gnsdk_playlist_morelikethis_option_get(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST,
		&value
		);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST :%s", value);

	gnsdk_playlist_morelikethis_option_get(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM,
		&value
		);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM :%s", value);

	gnsdk_playlist_morelikethis_option_get(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOM,
		&value
		);
	printf("\n GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOM :%s \n", value);

}  /* _print_playlist_morelikethis_options() */


/***************************************************************************
*
*    _DO_PLAYLIST_PDL
*
*    Here we perform playlist generation from our created Collection Summary via
*    custom PDL (Playlist Definition Language) statements.
*
***************************************************************************/
static void
_do_playlist_pdl(
	gnsdk_user_handle_t                user_handle,
	gnsdk_playlist_collection_handle_t h_playlist_collection
	)
{
	gnsdk_error_t                   error              = GNSDK_SUCCESS;
	gnsdk_uint32_t                  stmt_idx           = 0;
	gnsdk_uint32_t                  pdlstmt_count      = 0;
	gnsdk_bool_t                    b_seed_required    = GNSDK_FALSE;
	gnsdk_playlist_results_handle_t h_playlist_results = GNSDK_NULL;
	gnsdk_gdo_handle_t              h_gdo_seed         = GNSDK_NULL;
	gnsdk_cstr_t                    pdl_statements[]   =
	{
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 0",     /* like pop with a low score threshold (0)*/
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 300",   /* like pop with a reasonable score threshold (300)*/
		"GENERATE PLAYLIST WHERE GN_Genre = 2929",              /* exactly pop */
		"GENERATE PLAYLIST WHERE GN_Genre = 2821",              /* exactly rock */
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 0",     /* like rock with a low score threshold (0)*/
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 300",   /* like rock with a reasonable score threshold (300)*/
		"GENERATE PLAYLIST WHERE (GN_Genre LIKE SEED) > 300 LIMIT 20 RESULTS",
		"GENERATE PLAYLIST WHERE (GN_ArtistName LIKE 'Green Day') > 300 LIMIT 20 RESULTS, 2 PER GN_ArtistName;",
	};


	pdlstmt_count = sizeof(pdl_statements) / sizeof(pdl_statements[0]);

	for (stmt_idx = 0; stmt_idx < pdlstmt_count; stmt_idx++)
	{
		printf("\n PDL %d: %s \n", stmt_idx, pdl_statements[stmt_idx]);

		error = gnsdk_playlist_statement_validate(pdl_statements[stmt_idx], h_playlist_collection, &b_seed_required);
		if (error)
		{
			_display_last_error(__LINE__);
		}

		/*
			A seed gdo can be any recognized media gdo.
			In this example we are using the a gdo from a track in the playlist collection summary
		 */
		if (!error && b_seed_required)
		{
			gnsdk_cstr_t seed_ident = GNSDK_NULL;
			/* In this case , randomly selecting the 5th element */
			error = gnsdk_playlist_collection_ident_enum(h_playlist_collection, 4, &seed_ident, GNSDK_NULL);
			if (!error)
			{
				error = gnsdk_playlist_collection_get_gdo(h_playlist_collection, user_handle, seed_ident, &h_gdo_seed);
			}
		}

		if (!error)
		{
			error = gnsdk_playlist_generate_playlist(
				user_handle,
				pdl_statements[stmt_idx],
				h_playlist_collection,
				h_gdo_seed,
				&h_playlist_results
				);
			if (!error)
			{
				_enumerate_playlist_results(user_handle, h_playlist_collection, h_playlist_results);

				gnsdk_playlist_results_release(h_playlist_results);
			}
			else
			{
				_display_last_error(__LINE__);
			}
		}

		gnsdk_manager_gdo_release(h_gdo_seed);
		h_gdo_seed = GNSDK_NULL;
	}

}  /* _do_playlist_pdl() */


/***************************************************************************
*
*    _DO_PLAYLIST_MORELIKETHIS
*
*    Here we perform playlist 'morelikethis' generation from our created
*    Collection Summary
*
***************************************************************************/
static void
_do_playlist_morelikethis(
	gnsdk_user_handle_t                user_handle,
	gnsdk_playlist_collection_handle_t h_playlist_collection
	)
{
	gnsdk_error_t                   error              = GNSDK_SUCCESS;
	gnsdk_playlist_results_handle_t h_playlist_results = GNSDK_NULL;
	gnsdk_gdo_handle_t              h_gdo_seed         = GNSDK_NULL;
	gnsdk_uint32_t                  result_count       = 0;
	gnsdk_cstr_t                    seed_ident         = GNSDK_NULL;


	/*
	   A seed gdo can be any recognized media gdo.
	   In this example we are using the a gdo from a random track in the playlist collection summary
	 */
	error = gnsdk_playlist_collection_ident_enum(h_playlist_collection, 4, &seed_ident, GNSDK_NULL);
	if (!error)
	{
		error = gnsdk_playlist_collection_get_gdo(h_playlist_collection, user_handle, seed_ident, &h_gdo_seed);
	}

	if (error)
	{
		_display_last_error(__LINE__);
	}

	printf ("\n MoreLikeThis tests\n MoreLikeThis Seed details:\n");

	_playlist_get_attribute_value(h_gdo_seed);

	/* Generate a more Like this with the default settings */
	printf("\n MoreLikeThis with Default Options \n");

	/* Print the default More Like This options */
	_print_playlist_morelikethis_options(h_playlist_collection);

	error = gnsdk_playlist_generate_morelikethis(
		user_handle,
		h_playlist_collection,
		h_gdo_seed,
		&h_playlist_results
		);

	if (!error)
	{
		_enumerate_playlist_results(user_handle, h_playlist_collection, h_playlist_results);
	}
	else
	{
		_display_last_error(__LINE__);
	}

	/* cleanup */
	gnsdk_playlist_results_release(h_playlist_results);


	/* Generate a more Like this with the custom settings */
	printf("\n MoreLikeThis with Custom Options \n");

	/* Change the possible result set to be a maximum of 30 tracks.*/
	gnsdk_playlist_morelikethis_option_set(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS,
		"30"
		);

	/* Change the max per artist to be 20 */
	gnsdk_playlist_morelikethis_option_set(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST,
		"10"
		);

	/* Change the max per album to be 5 */
	gnsdk_playlist_morelikethis_option_set(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM,
		"5"
		);

	/* Change the random result to be 1 so that there is no randomization*/
	gnsdk_playlist_morelikethis_option_set(
		h_playlist_collection,
		GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOM,
		"1"
		);

	/* Print the customized More Like This options */
	_print_playlist_morelikethis_options(h_playlist_collection);

	error = gnsdk_playlist_generate_morelikethis(
		user_handle,
		h_playlist_collection,
		h_gdo_seed,
		&h_playlist_results
		);

	if (!error)
	{
		_enumerate_playlist_results(user_handle, h_playlist_collection, h_playlist_results);
	}
	else
	{
		_display_last_error(__LINE__);
	}

	/* cleanup */
	gnsdk_playlist_results_release(h_playlist_results);


	gnsdk_manager_gdo_release(h_gdo_seed);
	h_gdo_seed   = GNSDK_NULL;
	result_count = 0;

}  /* _do_playlist_morelikethis() */


/***************************************************************************
*
*    _PERFORM_SAMPLE_PLAYLIST
*
*    Our top level function that calls the required Playlist routines
*
***************************************************************************/
static void
_perform_sample_playlist(
	gnsdk_user_handle_t user_handle,
	int                 use_local
	)
{
	gnsdk_playlist_collection_handle_t playlist_collection = GNSDK_NULL;
	gnsdk_error_t                      error               = GNSDK_SUCCESS;


	error = _playlist_collection_create(user_handle, use_local, &playlist_collection);
	if (!error)
	{
		/* demonstrate PDL usage */
		_do_playlist_pdl(user_handle, playlist_collection);

		/* demonstrate MoreLike usage*/
		_do_playlist_morelikethis(user_handle, playlist_collection);
	}
	else
	{
		printf("\n Sample failed to create collection ");
	}


	/* cleanup */
	gnsdk_playlist_collection_release(playlist_collection);

}  /* _perform_sample_playlist() */

