/*
 * Copyright (c) 2000-2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
*/

/*
 *  Name: musicid_lookup_album_fpx
 *  Description:
 *  This example generates an FPX fingerprint and then queries it using MusicID.
 *  This is only supported by online queries.
 *
 *  Command-line Syntax:
 *  sample client_id client_id_tag license
*/

/* GNSDK headers
 *
 * Define the modules your application needs.
 * These constants enable inclusion of headers and symbols in gnsdk.h.
 */
#define GNSDK_MUSICID               1
#define GNSDK_STORAGE_SQLITE		1
#define GNSDK_DSP					1
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
	const char*				client_id,
	const char*				client_id_tag,
	const char*				client_app_version,
	const char*				license_path,
	gnsdk_user_handle_t*	p_user_handle
	);

static void
_shutdown_gnsdk(
	gnsdk_user_handle_t		user_handle
	);

static void
_do_sample_musicid_fpx(
	gnsdk_user_handle_t		user_handle
	);

/* Local data */
static gnsdk_cstr_t s_audio_file = "../../sample_data/teen_spirit_14s.wav";

/******************************************************************
 *
 *    MAIN
 *
 ******************************************************************/
int
main(int argc, char* argv[])
{
	gnsdk_user_handle_t		user_handle			= GNSDK_NULL;
	const char*				client_id			= NULL;
	const char*				client_id_tag		= NULL;
	const char*				client_app_version = "1.0.0.0"; /* Version of your application */
	const char*				license_path		= NULL;
	int						rc					= 0;
    
	if ((argc == 4) || (argc == 5))
	{
		client_id = argv[1];
		client_id_tag = argv[2];
		license_path = argv[3];
        
		/* GNSDK initialization */
        rc = _init_gnsdk(
            client_id,
            client_id_tag,
            client_app_version,
            license_path,
            &user_handle
        );
        if (0 == rc)
        {
            /* Perform a sample fpx query */
            _do_sample_musicid_fpx(user_handle);

            /* Clean up and shutdown */
            _shutdown_gnsdk( user_handle );
		}
	}
	else
	{
		printf( "\nUsage:\n%s clientid clientidtag license\n", argv[0] );
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
	const gnsdk_error_info_t*       error_info = gnsdk_manager_error_info();
    
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
    const char*			client_id,
    const char*			client_id_tag,
    const char*			client_app_version,
    gnsdk_user_handle_t*	p_user_handle
    )
{
	gnsdk_user_handle_t user_handle               = GNSDK_NULL;
	gnsdk_str_t         serialized_user           = GNSDK_NULL;
    gnsdk_bool_t        b_localonly               = GNSDK_FALSE;
	gnsdk_char_t		serialized_user_buf[1024] = {0};
	gnsdk_error_t		error                     = GNSDK_SUCCESS;
	FILE*               file                      = NULL;
	int					rc					      = 0;
    
	/* Creating a GnUser is required before performing any queries to Gracenote services,
	 * and such APIs in the SDK require a GnUser to be provided. GnUsers can be created
	 * 'Online' which means they are created by the Gracenote backend and fully vetted.
	 * Or they can be create 'Local Only' which means they are created locally by the
	 * SDK but then can only be used locally by the SDK.
	 */
    
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
			if (!b_localonly)
            {
				*p_user_handle = user_handle;
				return 0;
            }
			
			/* Need a user that has been registered online, but existing user is localonly.
             * Discard and register new online user.
             */
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
        GNSDK_USER_REGISTER_MODE_ONLINE,
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
    
}  /* _get_user_handle() */

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
	gnsdk_error_t	error	= GNSDK_SUCCESS;
	int				rc		= 0;
    
	error = gnsdk_manager_logging_enable(
        "sample.log",									/* Log file path */
        GNSDK_LOG_PKG_ALL,								/* Include entries for all packages and subsystems */
        GNSDK_LOG_LEVEL_ERROR|GNSDK_LOG_LEVEL_WARNING,	/* Include only error and warning entries */
        GNSDK_LOG_OPTION_ALL,							/* All logging options: timestamps, thread IDs, etc */
        0,												/* Max size of log: 0 means a new log file will be created each run */
        GNSDK_FALSE										/* GNSDK_TRUE = old logs will be renamed and saved */
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
    gnsdk_user_handle_t		user_handle
    )
{
	gnsdk_locale_handle_t	locale_handle	= GNSDK_NULL;
	gnsdk_error_t			error			= GNSDK_SUCCESS;
	int						rc				= 0;
    
	error = gnsdk_manager_locale_load(
        GNSDK_LOCALE_GROUP_MUSIC,		/* Locale group */
        GNSDK_LANG_ENGLISH,             /* Language */
        GNSDK_REGION_DEFAULT,			/* Region */
        GNSDK_DESCRIPTOR_SIMPLIFIED,	/* Descriptor */
        user_handle,					/* User handle */
        GNSDK_NULL,						/* User callback function */
        0,								/* Optional data for user callback function */
        &locale_handle					/* Return handle */
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
    const char*				client_id,
    const char*				client_id_tag,
    const char*				client_app_version,
    const char*				license_path,
    gnsdk_user_handle_t*	p_user_handle
    )
{
	gnsdk_manager_handle_t	sdkmgr_handle	= GNSDK_NULL;
	gnsdk_error_t			error			= GNSDK_SUCCESS;
	gnsdk_user_handle_t		user_handle		= GNSDK_NULL;
	int						rc				= 0;
    
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

    /* Initialize the DSP Library */
    if (0 == rc)
    {
        error = gnsdk_dsp_initialize(sdkmgr_handle);
        if (GNSDK_SUCCESS != error)
        {
            _display_last_error(__LINE__);
            rc = -1;
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
	gnsdk_error_t	error	= GNSDK_SUCCESS;
    
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
 *    _DISPLAY_ALBUM_GDO
 *
 ***************************************************************************/
static void
_display_album_gdo(
    gnsdk_gdo_handle_t album_gdo
    )
{
	gnsdk_error_t		error		= GNSDK_SUCCESS;
	gnsdk_gdo_handle_t	title_gdo	= GNSDK_NULL;
	gnsdk_cstr_t		value		= GNSDK_NULL;
    
	
	/* Album Title */
	error = gnsdk_manager_gdo_child_get( album_gdo, GNSDK_GDO_CHILD_TITLE_OFFICIAL, 1, &title_gdo );
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_manager_gdo_value_get( title_gdo, GNSDK_GDO_VALUE_DISPLAY, 1, &value );
		if (GNSDK_SUCCESS == error)
		{
			printf( "%16s %s\n", "Title:", value );
		}
		else
		{
			_display_last_error(__LINE__);
		}
		gnsdk_manager_gdo_release(title_gdo);
	}
	else
	{
		_display_last_error(__LINE__);
	}
    
}  /* _display_album_gdo() */


/***************************************************************************
 *
 *    _DISPLAY_FOR_RESOLVE
 *
 ***************************************************************************/
static void
_display_for_resolve(
    gnsdk_gdo_handle_t		response_gdo
    )
{
	gnsdk_error_t      error     = GNSDK_SUCCESS;
	gnsdk_gdo_handle_t album_gdo = GNSDK_NULL;
	gnsdk_uint32_t     count     = 0;
	gnsdk_uint32_t     ordinal   = 0;
    
	error = gnsdk_manager_gdo_child_count(response_gdo, GNSDK_GDO_CHILD_ALBUM, &count);
	if (GNSDK_SUCCESS == error)
	{
		printf( "%16s %d\n", "Album count:", count);
        
		/*	Note that the GDO accessors below are *ordinal* based, not index based.  so the 'first' of
         *	anything has a one-based ordinal of '1' - *not* an index of '0'
         */
		for (ordinal = 1; ordinal <= count; ordinal++)
		{
			/* Get the Album GDO */
			error = gnsdk_manager_gdo_child_get( response_gdo, GNSDK_GDO_CHILD_ALBUM, ordinal, &album_gdo );
			if (GNSDK_SUCCESS == error)
			{
				_display_album_gdo(album_gdo);
                
				/* Release the current album */
				gnsdk_manager_gdo_release(album_gdo);
				album_gdo = GNSDK_NULL;
			}
			else
			{
				_display_last_error(__LINE__);
			}
		}
	}
	else
	{
		_display_last_error(__LINE__);
	}
    
}  /* _display_for_resolve() */


/***************************************************************************
 *
 *    _DO_MATCH_SELECTION
 *
 ***************************************************************************/
static gnsdk_uint32_t
_do_match_selection(gnsdk_gdo_handle_t response_gdo)
{
	/*
     This is where any matches that need resolution/disambiguation are iterated
     and a single selection of the best match is made.
     
     For this simplified sample, we'll just echo the matches and select the first match.
     */
	_display_for_resolve(response_gdo);
    
	return 1;
    
}  /* _do_match_selection() */


/***************************************************************************
 *
 *    _SET_QUERY_FINGERPRINT
 *
 * This function simulates streaming audio into the Query handle to generate
 * the query fingerprint
 *
 ***************************************************************************/
static int
_set_query_fingerprint(
	gnsdk_musicid_query_handle_t	query_handle
	)
{
	gnsdk_error_t	error			= GNSDK_SUCCESS;
	gnsdk_bool_t	complete		= GNSDK_FALSE;
	size_t			read			= 0;
	FILE*			p_file			= NULL;
	char			pcm_audio[2048]	= {0};
	int				rc				= 0;

    /* check file for existence */
	p_file = fopen(s_audio_file, "rb");
	if (p_file == NULL)
	{
		printf("\n\n!!!!Failed to open input file: %s!!!\n\n", s_audio_file);
		return -1;
	}

	 /* skip the wave header (first 44 bytes). we know the format of our sample files */
	if (0 != fseek(p_file, 44, SEEK_SET))
	{
		fclose(p_file);
		return -1;
	}

	 /* initialize the fingerprinter
	Note: The sample file shipped is a 44100Hz 16-bit stereo (2 channel) wav file */
	error = gnsdk_musicid_query_fingerprint_begin(
        query_handle,
        GNSDK_MUSICID_FP_DATA_TYPE_STREAM3,
        44100,
        16,
        2
    );
	if (GNSDK_SUCCESS != error)
	{
		_display_last_error(__LINE__);
		fclose(p_file);
		return -1;
	}

	read = fread(pcm_audio, sizeof(char), 2048, p_file);
	while ((read > 0) && (GNSDK_FALSE == complete))
	{
		 /* write audio to the fingerprinter */
		error = gnsdk_musicid_query_fingerprint_write(
            query_handle,
            pcm_audio,
            read,
            &complete
        );
		if (GNSDK_SUCCESS != error)
		{
			if (GNSDKERR_SEVERE(error)) /* 'aborted' warnings could come back from write which should be expected */
			{
				_display_last_error(__LINE__);
			}
			rc = -1;
			break;
		}

		read = fread(pcm_audio, sizeof(char), 2048, p_file);
	}

	fclose(p_file);

	 /*signal that we are done*/
	if (GNSDK_SUCCESS == error)
	{
		error = gnsdk_musicid_query_fingerprint_end(query_handle);
		if (GNSDK_SUCCESS != error)
		{
			_display_last_error(__LINE__);
		}
	}

	return rc;

}  /* _set_query_fingerprint() */


/***************************************************************************
 *
 *    _DO_SAMPLE_MUSICID_STREAM
 *
 ***************************************************************************/
static void
_do_sample_musicid_fpx(
	gnsdk_user_handle_t     user_handle
	)
{
	gnsdk_error_t					error					= GNSDK_SUCCESS;
	gnsdk_musicid_query_handle_t	query_handle			= GNSDK_NULL;
	gnsdk_gdo_handle_t				response_gdo			= GNSDK_NULL;
	gnsdk_gdo_handle_t				album_gdo				= GNSDK_NULL;
	gnsdk_gdo_handle_t				followup_response_gdo	= GNSDK_NULL;
	gnsdk_uint32_t					count					= 0;
	gnsdk_uint32_t					choice_ordinal			= 0;
	gnsdk_cstr_t					needs_decision			= GNSDK_NULL;
	gnsdk_cstr_t					is_full					= GNSDK_NULL;
	int								rc						= 0;

	printf("\n*****Sample MID-Stream Query*****\n");

	/* Create the query handle */
	error = gnsdk_musicid_query_create(
        user_handle,
        GNSDK_NULL,	 /* User callback function */
        GNSDK_NULL,	 /* Optional data to be passed to the callback */
        &query_handle
    );

	/* Set the input fingerprint. */
	if (GNSDK_SUCCESS == error)
	{
		rc = _set_query_fingerprint(query_handle);
		if (0 == rc)
		{
			/* Perform the query */
			error = gnsdk_musicid_query_find_albums(
                query_handle,
                &response_gdo
            );
			if (GNSDK_SUCCESS != error)
			{
				_display_last_error(__LINE__);
			}

			/* See how many albums were found. */
			if (GNSDK_SUCCESS == error)
			{
				error = gnsdk_manager_gdo_child_count(
                    response_gdo,
                    GNSDK_GDO_CHILD_ALBUM,
                    &count
                );
				if (GNSDK_SUCCESS != error)
				{
					_display_last_error(__LINE__);
				}
			}

			/* See if we need any follow-up queries or disambiguation */
			if (GNSDK_SUCCESS == error)
			{
				if (count == 0)
				{
					printf("\nNo albums found for the input.\n");
				}
				else
				{
					/* we have at least one album, see if disambiguation (match resolution) is necessary. */
					error = gnsdk_manager_gdo_value_get(
                        response_gdo,
                        GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION,
                        1,
                        &needs_decision
                    );
					if (GNSDK_SUCCESS != error)
					{
						_display_last_error(__LINE__);
					}
					else
					{
						/* See if selection of one of the albums needs to happen */
						if (0 == strcmp(needs_decision, GNSDK_VALUE_TRUE))
						{
							choice_ordinal = _do_match_selection(response_gdo);
						}
						else
						{
							/* no need for disambiguation, we'll take the first album */
							choice_ordinal = 1;
						}

						error = gnsdk_manager_gdo_child_get(
                            response_gdo,
                            GNSDK_GDO_CHILD_ALBUM,
                            choice_ordinal,
                            &album_gdo
                        );
						if (GNSDK_SUCCESS != error)
						{
							_display_last_error(__LINE__);
						}
						else
						{
							/* See if the album has full data or only partial data. */
							error = gnsdk_manager_gdo_value_get(
                                album_gdo,
                                GNSDK_GDO_VALUE_FULL_RESULT,
                                1,
                                &is_full
                            );
							if (GNSDK_SUCCESS != error)
							{
								_display_last_error(__LINE__);
							}
							else
							{
								/* if we only have a partial result, we do a follow-up query to retrieve the full album */
								if (0 == strcmp(is_full, GNSDK_VALUE_FALSE))
								{
									/* do followup query to get full object. Setting the partial album as the query input. */
									error = gnsdk_musicid_query_set_gdo(
                                        query_handle,
                                        album_gdo
                                    );
									if (GNSDK_SUCCESS != error)
									{
										_display_last_error(__LINE__);
									}
									else
									{
										/* we can now release the partial album */
										gnsdk_manager_gdo_release(album_gdo);
										album_gdo = GNSDK_NULL;

										error = gnsdk_musicid_query_find_albums(
                                            query_handle,
                                            &followup_response_gdo
                                        );
										if (GNSDK_SUCCESS != error)
										{
											_display_last_error(__LINE__);
										}
										else
										{
											/* now our first album is the desired result with full data */
											error = gnsdk_manager_gdo_child_get(
                                                followup_response_gdo,
                                                GNSDK_GDO_CHILD_ALBUM,
                                                1,
                                                &album_gdo
                                            );

											/* Release the followup query's response object */
											gnsdk_manager_gdo_release(followup_response_gdo);
										}
									}
								}
							}

							/* We should now have our final, full album result. */
							if (GNSDK_SUCCESS == error)
							{
								printf( "%16s\n", "Final album:");

								_display_album_gdo(album_gdo);
							}

							gnsdk_manager_gdo_release(album_gdo);
							album_gdo = GNSDK_NULL;
						 }
					}
				}
			}
		}
	}

	/* Clean up */
    gnsdk_musicid_query_release(query_handle);
    gnsdk_manager_gdo_release(response_gdo);

}   /* _do_sample_musicid_fpx() */
