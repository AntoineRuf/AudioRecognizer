/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_loader.c
 *
 * Implementation of delay loader for GNSDK
 *
 */

#include "gnsdk.h"

#if defined GNSDK_WINDOWS
	#include <windows.h>
#else /* LINUX, MAC, SOLARIS */
	#include <dlfcn.h>
#endif


typedef struct
{
	gnsdk_cstr_t	gnsdk_lib_name;
#if defined GNSDK_WINDOWS
	HMODULE			gnsdk_lib_handle;
#else /* LINUX, MAC, QNX, SOLARIS */
	void*			gnsdk_lib_handle;
#endif

} gnsdk_loaded_sdk;

typedef enum
{
	gnsdk_unknown		= 0,

	gnsdk_manager,
	gnsdk_musicid,
	gnsdk_musicid_file,
	gnsdk_musicid_match,
	gnsdk_musicid_stream,
	gnsdk_link,
	gnsdk_video,
	gnsdk_dsp,
	gnsdk_submit,
	gnsdk_playlist,
	gnsdk_acr,
	gnsdk_storage_sqlite,
	gnsdk_storage_qnx,
	gnsdk_lookup_local,
	gnsdk_lookup_fplocal,
	gnsdk_lookup_localstream,
	gnsdk_epg,
	gnsdk_moodgrid,
	gnsdk_correlates,
	gnsdk_tasteprofile,
	gnsdk_taste,
	gnsdk_rhythm,

	gnsdk_count

} gnsdk_enum_sdks;


static gnsdk_char_t			s_gnsdk_library_path[GNSDK_MAX_PATH+1] = {0};
static gnsdk_loaded_sdk		s_gnsdk_map[gnsdk_count];
static gnsdk_bool_t			s_loader_init = GNSDK_FALSE;
static gnsdk_uint32_t		s_loader_state = 1;

static gnsdk_error_info_t	s_error_info = {
	0, /* error code */
	0, /* source error code */
	GNSDK_NULL, /* error description */
	GNSDK_NULL, /* error API */
	"GNSDK Loader",
	"GNSDK Loader"
};

static gnsdk_void_t		_gnsdk_loader_init(void);
static gnsdk_error_t	_gnsdk_loader_load(gnsdk_enum_sdks sdk);
static gnsdk_cstr_t		_gnsdk_loader_pathcat(
	gnsdk_char_t*	buf,
	gnsdk_size_t	buf_size,
	gnsdk_cstr_t	path,
	gnsdk_cstr_t	file
	);

#if defined GNSDK_WINDOWS
	#define GNSDK_GET_API		GetProcAddress
#else /* LINUX, MAC, QNX, SOLARIS */
	#define GNSDK_GET_API		dlsym
#endif

/* pre-decl for error setting */
gnsdk_void_t GNSDK_API
manager_errorinfo_set(gnsdk_error_t error_code, gnsdk_error_t source_error_code, gnsdk_cstr_t error_api, gnsdk_cstr_t err_msg);

/* common API loaded macro */
#define GNSDK_LOADER_WRAPPED_API_0(sdk, api_type, api_ret, api_name)	\
	api_type GNSDK_API api_name(void) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(void) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(void))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_1(sdk, api_type, api_ret, api_name, type_1, param_1)	\
	api_type GNSDK_API api_name(type_1 param_1) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_2(sdk, api_type, api_ret, api_name, type_1, param_1, type_2, param_2)	\
	api_type GNSDK_API api_name(type_1 param_1, type_2 param_2) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1, type_2 param_2) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1, type_2))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1, param_2); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_3(sdk, api_type, api_ret, api_name, type_1, param_1, type_2, param_2, type_3, param_3)	\
	api_type GNSDK_API api_name(type_1 param_1, type_2 param_2, type_3 param_3) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1, type_2 param_2, type_3 param_3) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1, type_2, type_3))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1, param_2, param_3); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_4(sdk, api_type, api_ret, api_name, type_1, param_1, type_2, param_2, type_3, param_3, type_4, param_4)	\
	api_type GNSDK_API api_name(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1, type_2, type_3, type_4))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1, param_2, param_3, param_4); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_5(sdk, api_type, api_ret, api_name, type_1, param_1, type_2, param_2, type_3, param_3, type_4, param_4, type_5, param_5)	\
	api_type GNSDK_API api_name(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1, type_2, type_3, type_4, type_5))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1, param_2, param_3, param_4, param_5); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_6(sdk, api_type, api_ret, api_name, type_1, param_1, type_2, param_2, type_3, param_3, type_4, param_4, type_5, param_5, type_6, param_6)	\
	api_type GNSDK_API api_name(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5, type_6 param_6) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5, type_6 param_6) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1, type_2, type_3, type_4, type_5, type_6))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1, param_2, param_3, param_4, param_5, param_6); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_7(sdk, api_type, api_ret, api_name, type_1, param_1, type_2, param_2, type_3, param_3, type_4, param_4, type_5, param_5, type_6, param_6, type_7, param_7)	\
	api_type GNSDK_API api_name(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5, type_6 param_6, type_7 param_7) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5, type_6 param_6, type_7 param_7) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1, type_2, type_3, type_4, type_5, type_6, type_7))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1, param_2, param_3, param_4, param_5, param_6, param_7); \
		} \
		\
		return ret_val; \
	}

#define GNSDK_LOADER_WRAPPED_API_8(sdk, api_type, api_ret, api_name, type_1, param_1, type_2, param_2, type_3, param_3, type_4, param_4, type_5, param_5, type_6, param_6, type_7, param_7, type_8, param_8)	\
	api_type GNSDK_API api_name(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5, type_6 param_6, type_7 param_7, type_8 param_8) \
	{ \
		static gnsdk_uint32_t loader_state = 0; \
		static api_type (GNSDK_API *api_name##_fn)(type_1 param_1, type_2 param_2, type_3 param_3, type_4 param_4, type_5 param_5, type_6 param_6, type_7 param_7, type_8 param_8) = GNSDK_NULL; \
		api_type		ret_val = api_ret; \
		gnsdk_error_t	error = GNSDK_SUCCESS; \
		\
		if (loader_state != s_loader_state) { \
			error = _gnsdk_loader_load(sdk); \
			if (!error) { \
				api_name##_fn = (api_type (GNSDK_API *)(type_1, type_2, type_3, type_4, type_5, type_6, type_7, type_8))GNSDK_GET_API(s_gnsdk_map[sdk].gnsdk_lib_handle, #api_name); \
				if (GNSDK_NULL == api_name##_fn) { \
					error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded); \
					manager_errorinfo_set(error, error, #api_name, "API not found!"); \
				} else { \
					loader_state = s_loader_state; \
				} \
			} else { \
				s_error_info.error_api = #api_name; \
			} \
		} \
		\
		if (!error) { \
			ret_val = api_name##_fn(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8); \
		} \
		\
		return ret_val; \
	}


/******************************************************************************
** GNSDK Loader APIs
*/
gnsdk_error_t	gnsdk_loader_set_gnsdk_path(
	gnsdk_cstr_t	gnsdk_lib_path
	)
{
	if (GNSDK_NULL == gnsdk_lib_path)
	{
		return GNSDKERR_InvalidArg;
	}

	_gnsdk_loader_pathcat(s_gnsdk_library_path, GNSDK_MAX_PATH, gnsdk_lib_path, GNSDK_NULL);

	/* reset loader */
	_gnsdk_loader_init();
	s_loader_state += 1;
	s_loader_init = GNSDK_FALSE;


	return GNSDK_SUCCESS;
}


/*-----------------------------------------------------------------------------
-- Private GNSDK Loader APIs
*/
gnsdk_void_t
_gnsdk_loader_init(void)
{
	s_gnsdk_map[gnsdk_unknown].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_manager].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_musicid].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_musicid_file].gnsdk_lib_handle		= GNSDK_NULL;
	s_gnsdk_map[gnsdk_musicid_stream].gnsdk_lib_handle		= GNSDK_NULL;
	s_gnsdk_map[gnsdk_link].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_video].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_storage_sqlite].gnsdk_lib_handle		= GNSDK_NULL;
	s_gnsdk_map[gnsdk_lookup_local].gnsdk_lib_handle		= GNSDK_NULL;
	s_gnsdk_map[gnsdk_lookup_fplocal].gnsdk_lib_handle		= GNSDK_NULL;
	s_gnsdk_map[gnsdk_lookup_localstream].gnsdk_lib_handle	= GNSDK_NULL;
	s_gnsdk_map[gnsdk_dsp].gnsdk_lib_handle					= GNSDK_NULL;
	s_gnsdk_map[gnsdk_submit].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_playlist].gnsdk_lib_handle			= GNSDK_NULL;
	s_gnsdk_map[gnsdk_acr].gnsdk_lib_handle					= GNSDK_NULL;
	s_gnsdk_map[gnsdk_musicid_match].gnsdk_lib_handle		= GNSDK_NULL;
	s_gnsdk_map[gnsdk_epg].gnsdk_lib_handle					= GNSDK_NULL;
	s_gnsdk_map[gnsdk_moodgrid].gnsdk_lib_handle			= GNSDK_NULL;
	s_gnsdk_map[gnsdk_correlates].gnsdk_lib_handle			= GNSDK_NULL;
	s_gnsdk_map[gnsdk_tasteprofile].gnsdk_lib_handle		= GNSDK_NULL;
	s_gnsdk_map[gnsdk_taste].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_rhythm].gnsdk_lib_handle				= GNSDK_NULL;
	s_gnsdk_map[gnsdk_unknown].gnsdk_lib_handle				= GNSDK_NULL;

#if (defined GNSDK_WINDOWS)
	s_gnsdk_map[gnsdk_manager].gnsdk_lib_name				= "gnsdk_manager.dll";
	s_gnsdk_map[gnsdk_musicid].gnsdk_lib_name				= "gnsdk_musicid.dll";
	s_gnsdk_map[gnsdk_musicid_file].gnsdk_lib_name			= "gnsdk_musicid_file.dll";
	s_gnsdk_map[gnsdk_musicid_stream].gnsdk_lib_name		= "gnsdk_musicid_stream.dll";
	s_gnsdk_map[gnsdk_musicid_match].gnsdk_lib_name			= "gnsdk_musicid_match.dll";
	s_gnsdk_map[gnsdk_link].gnsdk_lib_name					= "gnsdk_link.dll";
	s_gnsdk_map[gnsdk_video].gnsdk_lib_name					= "gnsdk_video.dll";
	s_gnsdk_map[gnsdk_dsp].gnsdk_lib_name					= "gnsdk_dsp.dll";
	s_gnsdk_map[gnsdk_submit].gnsdk_lib_name				= "gnsdk_submit.dll";
	s_gnsdk_map[gnsdk_playlist].gnsdk_lib_name				= "gnsdk_playlist.dll";
	s_gnsdk_map[gnsdk_acr].gnsdk_lib_name					= "gnsdk_acr.dll";
	s_gnsdk_map[gnsdk_storage_sqlite].gnsdk_lib_name		= "gnsdk_storage_sqlite.dll";
	s_gnsdk_map[gnsdk_lookup_local].gnsdk_lib_name			= "gnsdk_lookup_local.dll";
	s_gnsdk_map[gnsdk_lookup_fplocal].gnsdk_lib_name		= "gnsdk_lookup_fplocal.dll";
	s_gnsdk_map[gnsdk_lookup_localstream].gnsdk_lib_name	= "gnsdk_lookup_localstream.dll";
	s_gnsdk_map[gnsdk_epg].gnsdk_lib_name					= "gnsdk_epg.dll";
	s_gnsdk_map[gnsdk_moodgrid].gnsdk_lib_name				= "gnsdk_moodgrid.dll";
	s_gnsdk_map[gnsdk_correlates].gnsdk_lib_name			= "gnsdk_correlates.dll";
	s_gnsdk_map[gnsdk_tasteprofile].gnsdk_lib_name			= "gnsdk_tasteprofile.dll";
	s_gnsdk_map[gnsdk_taste].gnsdk_lib_name					= "gnsdk_taste.dll";
	s_gnsdk_map[gnsdk_rhythm].gnsdk_lib_name				= "gnsdk_rhythm.dll";
#elif (defined GNSDK_MAC) || (defined GNSDK_IOS)
	s_gnsdk_map[gnsdk_manager].gnsdk_lib_name				= "libgnsdk_manager."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_musicid].gnsdk_lib_name				= "libgnsdk_musicid."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_musicid_file].gnsdk_lib_name			= "libgnsdk_musicid_file."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_musicid_stream].gnsdk_lib_name		= "libgnsdk_musicid_stream."GNSDK_VERSION_STR".dylib";	
	s_gnsdk_map[gnsdk_musicid_match].gnsdk_lib_name			= "libgnsdk_musicid_match."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_link].gnsdk_lib_name					= "libgnsdk_link."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_video].gnsdk_lib_name					= "libgnsdk_video."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_storage_sqlite].gnsdk_lib_name		= "libgnsdk_storage_sqlite."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_lookup_local].gnsdk_lib_name			= "libgnsdk_lookup_local."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_lookup_fplocal].gnsdk_lib_name		= "libgnsdk_lookup_fplocal."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_lookup_localstream].gnsdk_lib_name	= "libgnsdk_lookup_localstream."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_dsp].gnsdk_lib_name					= "libgnsdk_dsp."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_submit].gnsdk_lib_name				= "libgnsdk_submit."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_playlist].gnsdk_lib_name				= "libgnsdk_playlist."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_acr].gnsdk_lib_name					= "libgnsdk_acr."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_epg].gnsdk_lib_name					= "libgnsdk_epg."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_moodgrid].gnsdk_lib_name				= "libgnsdk_moodgrid."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_correlates].gnsdk_lib_name			= "libgnsdk_correlates."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_tasteprofile].gnsdk_lib_name			= "libgnsdk_tasteprofile."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_taste].gnsdk_lib_name					= "libgnsdk_taste."GNSDK_VERSION_STR".dylib";
	s_gnsdk_map[gnsdk_rhythm].gnsdk_lib_name				= "libgnsdk_rhythm."GNSDK_VERSION_STR".dylib";
#elif (defined GNSDK_LINUX) || (defined GNSDK_SOLARIS) || (defined GNSDK_TIZEN)
	s_gnsdk_map[gnsdk_manager].gnsdk_lib_name				= "libgnsdk_manager.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_musicid].gnsdk_lib_name				= "libgnsdk_musicid.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_musicid_file].gnsdk_lib_name			= "libgnsdk_musicid_file.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_musicid_stream].gnsdk_lib_name		= "libgnsdk_musicid_stream.so."GNSDK_VERSION_STR;	
	s_gnsdk_map[gnsdk_musicid_match].gnsdk_lib_name			= "libgnsdk_musicid_match.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_link].gnsdk_lib_name					= "libgnsdk_link.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_video].gnsdk_lib_name					= "libgnsdk_video.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_storage_sqlite].gnsdk_lib_name		= "libgnsdk_storage_sqlite.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_lookup_local].gnsdk_lib_name			= "libgnsdk_lookup_local.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_lookup_fplocal].gnsdk_lib_name		= "libgnsdk_lookup_fplocal.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_lookup_localstream].gnsdk_lib_name	= "libgnsdk_lookup_localstream.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_dsp].gnsdk_lib_name					= "libgnsdk_dsp.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_submit].gnsdk_lib_name				= "libgnsdk_submit.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_playlist].gnsdk_lib_name				= "libgnsdk_playlist.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_acr].gnsdk_lib_name					= "libgnsdk_acr.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_epg].gnsdk_lib_name					= "libgnsdk_epg.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_moodgrid].gnsdk_lib_name				= "libgnsdk_moodgrid.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_correlates].gnsdk_lib_name			= "libgnsdk_correlates.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_tasteprofile].gnsdk_lib_name			= "libgnsdk_tasteprofile.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_taste].gnsdk_lib_name					= "libgnsdk_taste.so."GNSDK_VERSION_STR;
	s_gnsdk_map[gnsdk_rhythm].gnsdk_lib_name				= "libgnsdk_rhythm.so."GNSDK_VERSION_STR;
#elif (defined GNSDK_ANDROID) || (defined GNSDK_QNX)
	s_gnsdk_map[gnsdk_manager].gnsdk_lib_name				= "libgnsdk_manager."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_musicid].gnsdk_lib_name				= "libgnsdk_musicid."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_musicid_file].gnsdk_lib_name			= "libgnsdk_musicid_file."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_musicid_stream].gnsdk_lib_name		= "libgnsdk_musicid_stream."GNSDK_VERSION_STR".so";	
	s_gnsdk_map[gnsdk_musicid_match].gnsdk_lib_name			= "libgnsdk_musicid_match."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_link].gnsdk_lib_name					= "libgnsdk_link."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_video].gnsdk_lib_name					= "libgnsdk_video."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_storage_sqlite].gnsdk_lib_name		= "libgnsdk_storage_sqlite."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_storage_qnx].gnsdk_lib_name			= "libgnsdk_storage_qnx."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_lookup_local].gnsdk_lib_name			= "libgnsdk_lookup_local."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_lookup_fplocal].gnsdk_lib_name		= "libgnsdk_lookup_fplocal."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_lookup_localstream].gnsdk_lib_name	= "libgnsdk_lookup_localstream."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_dsp].gnsdk_lib_name					= "libgnsdk_dsp."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_submit].gnsdk_lib_name				= "libgnsdk_submit."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_playlist].gnsdk_lib_name				= "libgnsdk_playlist."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_acr].gnsdk_lib_name					= "libgnsdk_acr."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_epg].gnsdk_lib_name					= "libgnsdk_epg."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_moodgrid].gnsdk_lib_name				= "libgnsdk_moodgrid."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_correlates].gnsdk_lib_name			= "libgnsdk_correlates."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_tasteprofile].gnsdk_lib_name			= "libgnsdk_tasteprofile."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_taste].gnsdk_lib_name					= "libgnsdk_taste."GNSDK_VERSION_STR".so";
	s_gnsdk_map[gnsdk_rhythm].gnsdk_lib_name				= "libgnsdk_rhythm."GNSDK_VERSION_STR".so";
#else
#error Cannot build gnsdk_loader. Unknown GNSDK platform
#endif
}

gnsdk_error_t
_gnsdk_loader_load(gnsdk_enum_sdks	sdk
				   )
{
#if !defined GNSDK_WINDOWS
	gnsdk_cstr_t		err_msg = GNSDK_NULL;
#endif
	gnsdk_error_t		error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded);

	if (s_loader_init == GNSDK_FALSE)
	{
		_gnsdk_loader_init();
		s_loader_init = GNSDK_TRUE;
	}

	if (GNSDK_NULL == s_gnsdk_map[sdk].gnsdk_lib_handle)
	{
		gnsdk_char_t	gnsdk_path[GNSDK_MAX_PATH];
		_gnsdk_loader_pathcat(gnsdk_path, GNSDK_MAX_PATH, s_gnsdk_library_path, s_gnsdk_map[sdk].gnsdk_lib_name);

#if defined GNSDK_WINDOWS
		s_gnsdk_map[sdk].gnsdk_lib_handle = LoadLibraryA(gnsdk_path);
#else /* LINUX, MAC, SOLARIS */
		if (gnsdk_manager == sdk)
			s_gnsdk_map[sdk].gnsdk_lib_handle = dlopen(gnsdk_path, RTLD_LAZY|RTLD_GLOBAL);
		else
			s_gnsdk_map[sdk].gnsdk_lib_handle = dlopen(gnsdk_path, RTLD_LAZY);
		err_msg = dlerror();
#endif
	}

	if (GNSDK_NULL != s_gnsdk_map[sdk].gnsdk_lib_handle)
	{
		error = GNSDKERR_NoError;
	}
	else
	{
		manager_errorinfo_set(error, error, s_gnsdk_map[sdk].gnsdk_lib_name, "Failed to load GNSDK module");
	}

	return error;
}

gnsdk_cstr_t
_gnsdk_loader_pathcat(
	gnsdk_char_t*	buf,
	gnsdk_size_t	buf_size,
	gnsdk_cstr_t	path,
	gnsdk_cstr_t	file
	)
{
	gnsdk_uint32_t	pos = 0;
	gnsdk_uint32_t	pos_file = 0;

	if (path)
	{
		while ((pos < (buf_size-1)) && (path[pos] != 0))
		{
#if defined GNSDK_WINDOWS
			if (path[pos] == '/')
			{
				buf[pos] = '\\';
			}
#else /* LINUX, MAC, SOLARIS */
			if (path[pos] == '\\')
			{
				buf[pos] = '/';
			}
#endif
			else
			{
				buf[pos] = path[pos];
			}
			pos += 1;
		}

		if ((pos > 0) && (pos < buf_size))
		{
#if defined GNSDK_WINDOWS
			if (buf[pos - 1] != '\\')
			{
				buf[pos] = '\\';
				pos += 1;
			}
#else /* LINUX, MAC, SOLARIS */
			if (buf[pos - 1] != '/')
			{
				buf[pos] = '/';
				pos += 1;
			}
#endif
		}
	}

	if (file)
	{
		while ((pos < (buf_size-1)) && (file[pos_file] != 0))
		{
			buf[pos] = file[pos_file];
			pos_file += 1;
			pos += 1;
		}
	}

	buf[pos] = 0;

	return buf;
}


/******************************************************************************
** GNSDK Manager APIs
*/
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_initialize,				gnsdk_manager_handle_t*, p_sdkmgr_handle, gnsdk_cstr_t, license_data, gnsdk_size_t, license_data_size)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_cstr_t,		GNSDK_NULL,					gnsdk_manager_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_cstr_t,		GNSDK_NULL,					gnsdk_manager_get_product_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_cstr_t,		GNSDK_NULL,					gnsdk_manager_get_build_date)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_cstr_t,		GNSDK_NULL,					gnsdk_manager_get_globalid_magic)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_string_free,				gnsdk_str_t, string)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_user_register,			gnsdk_cstr_t, register_mode, gnsdk_cstr_t, client_id, gnsdk_cstr_t, client_id_tag, gnsdk_cstr_t, client_app_ver, gnsdk_str_t*, p_serialized_user)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_user_set_autoregister,	gnsdk_user_handle_t , user_handle, gnsdk_user_store_fn, callback, gnsdk_void_t*, callback_data)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_user_create,				gnsdk_cstr_t, serialzed_user, gnsdk_cstr_t, client_id_test, gnsdk_user_handle_t*, p_user_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_user_is_localonly,		gnsdk_user_handle_t, user_handle, gnsdk_bool_t*, pb_local_only)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_user_option_set,			gnsdk_user_handle_t, user_handle, gnsdk_cstr_t, option_name, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_user_option_get,			gnsdk_user_handle_t, user_handle, gnsdk_cstr_t, option_name, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_user_release,				gnsdk_user_handle_t, user_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_logging_register_package,	gnsdk_uint16_t, package_id, gnsdk_cstr_t, package_name)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_logging_enable,			gnsdk_cstr_t, log_file_path, gnsdk_uint16_t, package_id, gnsdk_uint32_t, filter_mask, gnsdk_uint32_t, options_mask, gnsdk_uint64_t, max_size, gnsdk_bool_t, archive)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_logging_enable_callback,	gnsdk_manager_logging_callback_fn, callback, gnsdk_void_t*, callback_data, gnsdk_uint16_t, package_id, gnsdk_uint32_t, filter_mask, gnsdk_uint32_t, options_mask)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_logging_disable,			gnsdk_cstr_t, log_file_path, gnsdk_uint16_t, package_id)
GNSDK_LOADER_WRAPPED_API_8(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_load,				gnsdk_cstr_t, locale_group,	gnsdk_cstr_t, language, gnsdk_cstr_t, region, gnsdk_cstr_t, descriptor, gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn,	callback_fn, gnsdk_void_t*, callback_data, gnsdk_locale_handle_t*, p_locale_handle)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_update,			gnsdk_locale_handle_t, locale_handle, gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_bool_t*, p_updated)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_update_check,		gnsdk_locale_handle_t, locale_handle, gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_bool_t*, p_new_version_available)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_update_notify,		gnsdk_locale_update_callback_fn, callback_fn, gnsdk_void_t*, callback_data)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_set_group_default,	gnsdk_locale_handle_t, locale_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_unset_group_default, gnsdk_cstr_t, locale_group)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_info,				gnsdk_locale_handle_t,locale_handle,gnsdk_cstr_t*,p_group,gnsdk_cstr_t*,p_language,gnsdk_cstr_t*,p_region,gnsdk_cstr_t*,p_descriptor,gnsdk_cstr_t*,p_revision)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_serialize,			gnsdk_locale_handle_t, locale_handle, gnsdk_str_t*, p_serialized_locale_data)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_deserialize,		gnsdk_cstr_t, serialized_locale_data, gnsdk_locale_handle_t*, p_locale_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_release,			gnsdk_locale_handle_t, locale_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_available_count,	gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_locale_available_get,     gnsdk_uint32_t, ordinal, gnsdk_cstr_t*, p_type, gnsdk_cstr_t*, p_language, gnsdk_cstr_t*, p_region, gnsdk_cstr_t*, p_descriptor)

gnsdk_error_t	GNSDK_API gnsdk_manager_logging_write(
	gnsdk_int32_t	line,
	gnsdk_cstr_t	filename,
	gnsdk_uint16_t	packageid,
	gnsdk_uint32_t	mask,
	gnsdk_cstr_t	format,
	...
	)
{
	static gnsdk_uint32_t loader_state = 0;
	static gnsdk_error_t (GNSDK_API *gnsdk_manager_logging_vwrite_fn)(gnsdk_int32_t line, gnsdk_cstr_t filename, gnsdk_uint16_t packageid, gnsdk_uint32_t mask, gnsdk_cstr_t format, va_list argptr) = GNSDK_NULL;
	va_list			argptr;
	gnsdk_error_t	error = GNSDK_SUCCESS;

	if (loader_state != s_loader_state)
	{
		error = _gnsdk_loader_load(gnsdk_manager);
		if (!error)
		{
			gnsdk_manager_logging_vwrite_fn = (gnsdk_error_t (GNSDK_API *)(gnsdk_int32_t line, gnsdk_cstr_t filename, gnsdk_uint16_t packageid, gnsdk_uint32_t mask, gnsdk_cstr_t format, va_list argptr))GNSDK_GET_API(s_gnsdk_map[gnsdk_manager].gnsdk_lib_handle, "gnsdk_manager_logging_vwrite");
			if (GNSDK_NULL == gnsdk_manager_logging_vwrite_fn)
			{
				error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded);
				s_error_info.error_code = error;
				s_error_info.source_error_code = error;
				s_error_info.error_api = "gnsdk_manager_logging_vwrite";
				s_error_info.error_description = "API not found!";
			}
			else
			{
				loader_state = s_loader_state;
			}
		}
		else
		{
			s_error_info.error_api = "gnsdk_manager_logging_vwrite";
		}
	}

	if (!error)
	{
		va_start(argptr, format);
		error = gnsdk_manager_logging_vwrite_fn(line, filename, packageid, mask, format, argptr);
		va_end(argptr);
	}

	return error;
}

GNSDK_LOADER_WRAPPED_API_6(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_logging_vwrite,					gnsdk_int32_t, line, gnsdk_cstr_t, filename, gnsdk_uint16_t, packageid, gnsdk_uint32_t, mask, gnsdk_cstr_t, format, va_list, argptr)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_get_type,						gnsdk_gdo_handle_t, gdo_handle, gnsdk_cstr_t*, p_context)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_is_type,						gnsdk_gdo_handle_t, gdo_handle, gnsdk_cstr_t, gdo_type)

GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_value_count,					gnsdk_gdo_handle_t, gdo_handle, gnsdk_cstr_t, value_key, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_value_get,					gnsdk_gdo_handle_t, gdo_handle, gnsdk_cstr_t, value_key, gnsdk_uint32_t, ordinal, gnsdk_cstr_t*, p_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_child_count,					gnsdk_gdo_handle_t, gdo_handle, gnsdk_cstr_t, context_key, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_child_get,					gnsdk_gdo_handle_t, gdo_handle, gnsdk_cstr_t, context_key, gnsdk_uint32_t, flags, gnsdk_gdo_handle_t*, p_gdo_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_serialize,					gnsdk_gdo_handle_t, gdo_handle, gnsdk_str_t*, p_serialized_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_deserialize,					gnsdk_cstr_t, serialized_gdo, gnsdk_gdo_handle_t*, p_gdo_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_render,						gnsdk_gdo_handle_t, gdo_handle, gnsdk_uint32_t, render_flags, gnsdk_str_t*, p_render_str)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_create_from_id,				gnsdk_cstr_t, id_value, gnsdk_cstr_t, id_value_tag, gnsdk_cstr_t, id_source, gnsdk_gdo_handle_t*, p_gdo_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_create_from_xml,				gnsdk_cstr_t, xml_str,  gnsdk_gdo_handle_t*, p_gdo_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_set_locale,					gnsdk_gdo_handle_t, gdo_handle, gnsdk_locale_handle_t, locale_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_addref,						gnsdk_gdo_handle_t, gdo_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_gdo_release,						gnsdk_gdo_handle_t, gdo_handle)
GNSDK_LOADER_WRAPPED_API_8(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_retrieve, 					gnsdk_cstr_t, type, gnsdk_cstr_t, language, gnsdk_cstr_t, region, gnsdk_cstr_t, descriptor, gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback, gnsdk_void_t*, callback_data, gnsdk_list_handle_t*, p_list_handle)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_update,						gnsdk_list_handle_t, list_handle, gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback, gnsdk_void_t*, callback_data, gnsdk_list_handle_t*,	p_updated_list)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_update_check,				gnsdk_list_handle_t, list_handle, gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback, gnsdk_void_t*, callback_data, gnsdk_bool_t*, p_new_revision_available)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_update_notify,				gnsdk_list_update_callback_fn, callback_fn, gnsdk_void_t*, callback_data)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_release,						gnsdk_list_handle_t, list_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_serialize,					gnsdk_list_handle_t, list_handle, gnsdk_str_t*, p_serialized_list)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_deserialize,					gnsdk_cstr_t, serialized_list, gnsdk_list_handle_t*, p_list_handle)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_render_to_xml,				gnsdk_list_handle_t, list_handle, gnsdk_uint32_t, levels, gnsdk_uint32_t, render_flags, gnsdk_str_t*, p_xml_render)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_type,					gnsdk_list_handle_t, list_handle, gnsdk_cstr_t*, p_type)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_language,				gnsdk_list_handle_t, list_handle, gnsdk_cstr_t*, p_lang)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_region,					gnsdk_list_handle_t, list_handle, gnsdk_cstr_t*, p_region)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_descriptor,				gnsdk_list_handle_t, list_handle, gnsdk_cstr_t*, p_descriptor)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_revision,				gnsdk_list_handle_t, list_handle, gnsdk_cstr_t*, p_descriptor)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_level_count,				gnsdk_list_handle_t, list_handle, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_element_count,			gnsdk_list_handle_t, list_handle, gnsdk_uint32_t, level, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_element,					gnsdk_list_handle_t, list_handle, gnsdk_uint32_t, level, gnsdk_uint32_t, index,	gnsdk_list_element_handle_t*,	p_element_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_element_by_id,			gnsdk_list_handle_t, list_handle, gnsdk_uint32_t, item_id, gnsdk_list_element_handle_t*, p_element_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_element_by_range,		gnsdk_list_handle_t, list_handle, gnsdk_uint32_t, value, gnsdk_list_element_handle_t*, p_element_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_element_by_string,		gnsdk_list_handle_t, list_handle, gnsdk_cstr_t, value, gnsdk_list_element_handle_t*, p_element_handle)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_get_element_by_gdo,			gnsdk_list_handle_t, list_handle, gnsdk_gdo_handle_t, gdo_handle, gnsdk_uint32_t, ordinal, gnsdk_uint32_t, level, gnsdk_list_element_handle_t*, p_element_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_display_string,	gnsdk_list_element_handle_t, element_handle, gnsdk_cstr_t*, p_string)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_id,				gnsdk_list_element_handle_t, element_handle, gnsdk_uint32_t*, item_id)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_parent,			gnsdk_list_element_handle_t, element_handle, gnsdk_list_element_handle_t*, p_parent_element_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_level,			gnsdk_list_element_handle_t, element_handle, gnsdk_uint32_t*, p_level)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_child_count,		gnsdk_list_element_handle_t, element_handle, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_child,			gnsdk_list_element_handle_t, element_handle, gnsdk_uint32_t, index, gnsdk_list_element_handle_t*, p_child_element_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_id_for_submit,	gnsdk_list_element_handle_t,element_handle,gnsdk_uint32_t*,p_item_submit_id)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_get_value,			gnsdk_list_element_handle_t,element_handle,	gnsdk_cstr_t,list_value_key,gnsdk_cstr_t*,p_value)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_list_element_release,				gnsdk_list_element_handle_t, element_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_storage_cleanup,					gnsdk_cstr_t,storage_name,gnsdk_bool_t,b_async)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_storage_flush,					gnsdk_cstr_t,storage_name,gnsdk_bool_t,b_async)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_storage_compact,					gnsdk_cstr_t, storage_name,	gnsdk_bool_t,	b_async)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_storage_location_set,				gnsdk_cstr_t, storage_name,	gnsdk_cstr_t,	storage_location)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_storage_validate,					gnsdk_cstr_t, storage_name,	gnsdk_error_info_t*,	p_error_info)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_storage_version_get,				gnsdk_cstr_t, storage_name, gnsdk_cstr_t*,	p_version)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_query_interface,					gnsdk_cstr_t, szIntfName, gnsdk_void_t**, p_intf)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_test_gracenote_connection,		gnsdk_user_handle_t, user_handle)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_internals,						gnsdk_uint32_t, op, gnsdk_size_t*, p_current, gnsdk_size_t*, p_highwater, gnsdk_bool_t, b_reset_highwater)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_manager_memory_warn,						gnsdk_memory_warn_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_size_t, memory_warn_size)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_handle_addref,							gnsdk_handle_t, handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_handle_release,							gnsdk_handle_t, handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	gnsdk_handle_report)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_SDKManager, GNSDKERR_LibraryNotLoaded),	manager_init_inc)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_manager, gnsdk_uint32_t,	0,																		manager_init_dec)

const gnsdk_error_info_t* GNSDK_API
gnsdk_manager_error_info(void)
{
	static gnsdk_uint32_t loader_state = 0;
	static const gnsdk_error_info_t* (GNSDK_API *gnsdk_manager_error_info_fn)(void) = GNSDK_NULL;

	const gnsdk_error_info_t*	p_error_info;
	gnsdk_error_t				error = GNSDK_SUCCESS;

	if (loader_state != s_loader_state)
	{
		if (s_gnsdk_map[gnsdk_manager].gnsdk_lib_handle)
		{
			gnsdk_manager_error_info_fn = (const gnsdk_error_info_t* (GNSDK_API *)(void))GNSDK_GET_API(s_gnsdk_map[gnsdk_manager].gnsdk_lib_handle, "gnsdk_manager_error_info");
			if (GNSDK_NULL == gnsdk_manager_error_info_fn)
			{
				error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded);
				manager_errorinfo_set(error, error, "gnsdk_manager_error_info", "API not found!");
			}
			else
			{
				loader_state = s_loader_state;
			}
		}
		else
		{
			error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded);
		}
	}

	if (!error)
	{
		p_error_info = gnsdk_manager_error_info_fn();
	}
	else
	{
		p_error_info = &s_error_info;
	}

	return p_error_info;
}

gnsdk_void_t GNSDK_API
manager_errorinfo_set(gnsdk_error_t error_code, gnsdk_error_t source_error_code, gnsdk_cstr_t error_api, gnsdk_cstr_t err_msg)
{
	static gnsdk_uint32_t loader_state = 0;
	static gnsdk_void_t (GNSDK_API *manager_errorinfo_set_fn)(gnsdk_error_t error_code, gnsdk_error_t source_error_code, gnsdk_cstr_t error_api, gnsdk_cstr_t err_msg) = GNSDK_NULL;

	gnsdk_error_t	error = GNSDK_SUCCESS;

	if (loader_state != s_loader_state)
	{
		if (s_gnsdk_map[gnsdk_manager].gnsdk_lib_handle)
		{
			manager_errorinfo_set_fn = (gnsdk_void_t (GNSDK_API *)(gnsdk_error_t error_code, gnsdk_error_t source_error_code, gnsdk_cstr_t error_api, gnsdk_cstr_t err_msg))GNSDK_GET_API(s_gnsdk_map[gnsdk_manager].gnsdk_lib_handle, "manager_errorinfo_set");
			if (GNSDK_NULL == manager_errorinfo_set_fn)
			{
				error_code = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded);
				source_error_code = error_code;
				error_api = "manager_errorinfo_set";
				err_msg = "API not found!";
				
				error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded);
			}
			else
			{
				loader_state = s_loader_state;
			}
		}
		else
		{
			error = GNSDKERR_MAKE_ERROR(0, GNSDKERR_LibraryNotLoaded);
		}
	}

	if (!error)
	{
		manager_errorinfo_set_fn(error_code, source_error_code, error_api, err_msg);
	}
	else
	{
		s_error_info.error_code = error_code;
		s_error_info.source_error_code = source_error_code;
		s_error_info.error_api = error_api;
		s_error_info.error_description = err_msg;
	}
}

/******************************************************************************
** GNSDK MusicID APIs
*/
#if GNSDK_MUSICID
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_initialize,				gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid, gnsdk_cstr_t,		GNSDK_NULL,					gnsdk_musicid_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid, gnsdk_cstr_t,		GNSDK_NULL,					gnsdk_musicid_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_create,				gnsdk_user_handle_t, sdkmgr_user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_musicid_query_handle_t*, p_musicid_query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_option_set,			gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_option_get,			gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_set_toc_string,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_cstr_t, toc_string)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_add_toc_offset,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_uint32_t, toc_offset)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_set_text,			gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_cstr_t, search_field, gnsdk_cstr_t, search_text)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_set_fp_data,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_cstr_t, fp_data, gnsdk_cstr_t, fp_data_type)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_get_fp_data,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_cstr_t*, p_fp_data)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_set_gdo,			gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_gdo_handle_t, query_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_set_locale,			gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_locale_handle_t, query_locale)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_fingerprint_begin,	gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_cstr_t, fp_data_type, gnsdk_uint32_t, audio_sample_rate, gnsdk_uint32_t, audio_sample_size, gnsdk_uint32_t, audio_channels)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_fingerprint_write, 	gnsdk_musicid_query_handle_t, musicid_query_handle, const gnsdk_void_t*, audioData, gnsdk_size_t, audioData_size, gnsdk_bool_t*, pb_complete)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_fingerprint_end,	gnsdk_musicid_query_handle_t, musicid_query_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_find_albums,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_find_tracks,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_find_lyrics,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_find_matches,		gnsdk_musicid_query_handle_t, musicid_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID, GNSDKERR_LibraryNotLoaded),	gnsdk_musicid_query_release,			gnsdk_musicid_query_handle_t, musicid_query_handle)
#endif /* GNSDK_MUSICID */


/******************************************************************************
** GNSDK MusicID-File APIs
*/
#if GNSDK_MUSICID_FILE
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_initialize,						gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_file, gnsdk_cstr_t,	GNSDK_NULL,					gnsdk_musicidfile_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_file, gnsdk_cstr_t,	GNSDK_NULL,					gnsdk_musicidfile_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_create,						gnsdk_user_handle_t, user_handle, gnsdk_musicidfile_callbacks_t*, callbacks, gnsdk_void_t*, callback_data, gnsdk_musicidfile_query_handle_t*, p_musicidfile_query_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_release,					gnsdk_musicidfile_query_handle_t, musicidfile_query_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_do_trackid,					gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_uint32_t, query_flags)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_do_albumid,					gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_uint32_t, query_flags)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_do_libraryid,				gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_uint32_t, query_flags)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_cancel,						gnsdk_musicidfile_query_handle_t, musicidfile_query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_status,						gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_musicidfile_handle_status_t*, p_musicidfile_handle_status, gnsdk_error_t*, p_musicid_complete_error)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_wait_for_complete,			gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_uint32_t, timeout_value, gnsdk_error_t*, p_musicid_complete_error)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_option_set,					gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_option_get,					gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_get_response_gdo,			gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_create,			gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_cstr_t, ident_str, gnsdk_musicidfile_fileinfo_callbacks_t*, callbacks, gnsdk_void_t*, callback_data, gnsdk_musicidfile_fileinfo_handle_t* const, p_fileinfo_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_create_from_xml,	gnsdk_musicidfile_query_handle_t, musicidfile_query_handle,	gnsdk_cstr_t, fileinfo_xml, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_remove,			gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_count,				gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_get_by_index,		gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_uint32_t, index, gnsdk_musicidfile_fileinfo_handle_t* const, p_fileinfo_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_get_by_ident,		gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_cstr_t, ident_str, gnsdk_musicidfile_fileinfo_handle_t* const, p_fileinfo_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_get_by_filename,	gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_cstr_t, file_name, gnsdk_musicidfile_fileinfo_handle_t* const, p_fileinfo_handle)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_get_by_folder,		gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_cstr_t, folder_name, gnsdk_uint32_t, index, gnsdk_musicidfile_fileinfo_handle_t* const, p_fileinfo_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_query_fileinfo_render_to_xml,		gnsdk_musicidfile_query_handle_t, musicidfile_query_handle, gnsdk_str_t* , p_fileinfo_xml)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_metadata_set,			gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, gnsdk_cstr_t, data_key, gnsdk_cstr_t, data_value)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_metadata_get,			gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, gnsdk_cstr_t, data_key, gnsdk_cstr_t*, p_data_value, gnsdk_cstr_t*, p_data_value_source)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_status,					gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, gnsdk_musicidfile_fileinfo_status_t*, p_fileinfo_status, const gnsdk_error_info_t** ,pp_error_info)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_get_response_gdo,		gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_userdata_set,			gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, gnsdk_void_t*, userdata, gnsdk_musicidfile_fileinfo_userdata_delete_fn, delete_callback)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_userdata_get,			gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, gnsdk_void_t**, p_userdata)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_fingerprint_begin,		gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, gnsdk_uint32_t, audio_sample_rate, gnsdk_uint32_t, audio_sample_size, gnsdk_uint32_t, audio_channels)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_fingerprint_write,		gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle, const gnsdk_void_t*, audioData, gnsdk_size_t, audioData_size, gnsdk_bool_t*, p_complete)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_file, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_File, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidfile_fileinfo_fingerprint_end,			gnsdk_musicidfile_fileinfo_handle_t, fileinfo_handle)
#endif /* GNSDK_MUSICID_FILE */

/******************************************************************************
** GNSDK MusicID-Stream APIs
*/
#if GNSDK_MUSICID_STREAM
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_initialize,						gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_stream, gnsdk_cstr_t,	GNSDK_NULL,																	gnsdk_musicidstream_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_stream, gnsdk_cstr_t,	GNSDK_NULL,																	gnsdk_musicidstream_get_build_date)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_create,					gnsdk_user_handle_t, user_handle,gnsdk_musicidstream_preset_t, preset, gnsdk_musicidstream_callbacks_t*, p_callbacks, gnsdk_void_t*, callback_data, gnsdk_musicidstream_channel_handle_t*, p_musicidstream_channel_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_set_locale,				gnsdk_musicidstream_channel_handle_t, stream_handle, gnsdk_locale_handle_t, locale_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_option_set,				gnsdk_musicidstream_channel_handle_t, stream_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_option_get,				gnsdk_musicidstream_channel_handle_t, stream_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_audio_begin,			gnsdk_musicidstream_channel_handle_t, musicid_streamchannel_handle, gnsdk_uint32_t, samples_per_second, gnsdk_uint32_t, bits_per_sample, gnsdk_uint32_t, num_channels)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_audio_write,			gnsdk_musicidstream_channel_handle_t, musicid_streamchannel_handle, const gnsdk_byte_t*, p_audioData, gnsdk_size_t, audioData_length)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_audio_end,				gnsdk_musicidstream_channel_handle_t, musicid_streamchannel_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_identify,				gnsdk_musicidstream_channel_handle_t, musicid_streamchannel_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_identify_cancel,		gnsdk_musicidstream_channel_handle_t, musicid_streamchannel_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_wait_for_identify,		gnsdk_musicidstream_channel_handle_t, musicidstream_channel_handle,	gnsdk_uint32_t, timeout_ms)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_release,				gnsdk_musicidstream_channel_handle_t, stream_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_automatic_set,				gnsdk_musicidstream_channel_handle_t, stream_handle, gnsdk_bool_t, b_auto_set)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_automatic_get,				gnsdk_musicidstream_channel_handle_t, stream_handle, gnsdk_bool_t*, p_auto_set)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_event,				gnsdk_musicidstream_channel_handle_t, stream_handle, gnsdk_musicidstream_event_t, event_t)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_stream, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Stream, GNSDKERR_LibraryNotLoaded),	gnsdk_musicidstream_channel_broadcast_metadata_write,				gnsdk_musicidstream_channel_handle_t, stream_handle, gnsdk_cstr_t, broadcast_metadata_key, gnsdk_cstr_t, broadcast_metadata_value)

#endif /* GNSDK_MUSICID_STREAM */

/******************************************************************************
** GNSDK Link APIs
*/
#if GNSDK_LINK
GNSDK_LOADER_WRAPPED_API_1(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_initialize,					gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_link, gnsdk_cstr_t,	GNSDK_NULL,							gnsdk_link_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_link, gnsdk_cstr_t,	GNSDK_NULL,							gnsdk_link_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_create,				gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_link_query_handle_t*, p_link_query_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_release,				gnsdk_link_query_handle_t, link_query_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_set_gdo,				gnsdk_link_query_handle_t, link_query_handle, gnsdk_gdo_handle_t, input_gdo)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_option_set,			gnsdk_link_query_handle_t, link_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_option_get,			gnsdk_link_query_handle_t, link_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_options_clear,			gnsdk_link_query_handle_t, link_query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_content_count,			gnsdk_link_query_handle_t, link_query_handle, gnsdk_link_content_type_t, content_type, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_content_info,			gnsdk_link_query_handle_t, link_query_handle, gnsdk_link_content_type_t, content_type, gnsdk_uint32_t, ordinal, gnsdk_cstr_t*, p_datasource_val, gnsdk_cstr_t*, p_datasource_type)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_content_retrieve,		gnsdk_link_query_handle_t, link_query_handle, gnsdk_link_content_type_t, content_type, gnsdk_uint32_t, ordinal, gnsdk_link_data_type_t*, p_buffer_data_type, gnsdk_byte_t**, p_buffer, gnsdk_size_t*, p_buffer_size)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_content_free,			gnsdk_byte_t*, buffer)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_link, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Link, GNSDKERR_LibraryNotLoaded),			gnsdk_link_query_set_list_element,		gnsdk_link_query_handle_t, link_query_handle, gnsdk_list_element_handle_t, input_list_element)
#endif /* GNSDK_LINK */


/******************************************************************************
** GNSDK Video APIs
*/
#if GNSDK_VIDEO
GNSDK_LOADER_WRAPPED_API_1(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_initialize,				gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_video, gnsdk_cstr_t,	GNSDK_NULL,						gnsdk_video_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_video, gnsdk_cstr_t,	GNSDK_NULL,						gnsdk_video_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_create,			gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_video_query_handle_t*, p_video_query_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_release,			gnsdk_video_query_handle_t, video_query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_set_toc_string,	gnsdk_video_query_handle_t, video_query_handle, gnsdk_cstr_t, toc_string, gnsdk_uint32_t, toc_string_flags)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_set_external_id,	gnsdk_video_query_handle_t, video_query_handle, gnsdk_cstr_t, external_id, gnsdk_cstr_t, external_id_type, gnsdk_cstr_t, external_id_source)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_set_filter,		gnsdk_video_query_handle_t, video_query_handle, gnsdk_cstr_t, filter_key, gnsdk_cstr_t, filter_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_set_filter_by_list_element, gnsdk_video_query_handle_t, video_query_handle, gnsdk_cstr_t, filter_key, gnsdk_list_element_handle_t, list_element)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_set_text,			gnsdk_video_query_handle_t, video_query_handle, gnsdk_cstr_t, search_field, gnsdk_cstr_t, search_text, gnsdk_video_search_type_t, search_type)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_option_set,		gnsdk_video_query_handle_t, query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_option_get,		gnsdk_video_query_handle_t, query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_set_gdo,			gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t, query_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_set_locale,		gnsdk_video_query_handle_t, video_query_handle, gnsdk_locale_handle_t, query_locale)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_suggestions,	gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_products,	gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_works,		gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
//GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_programs,	gnsdk_video_query_handle_t,	video_query_handle,	gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_series,		gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_seasons,		gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_objects,		gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_video, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_VideoID, GNSDKERR_LibraryNotLoaded),		gnsdk_video_query_find_contributors,gnsdk_video_query_handle_t, video_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
#endif /* GNSDK_VIDEO */


/******************************************************************************
** GNSDK SQLite APIs
*/
#if GNSDK_STORAGE_SQLITE
GNSDK_LOADER_WRAPPED_API_1(gnsdk_storage_sqlite, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_SQLite, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_sqlite_initialize,					gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_storage_sqlite, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_SQLite, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_sqlite_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_storage_sqlite, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_storage_sqlite_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_storage_sqlite, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_storage_sqlite_get_build_date)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_storage_sqlite, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_storage_sqlite_get_sqlite_version)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_storage_sqlite, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_SQLite, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_sqlite_option_set,					gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_storage_sqlite, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_SQLite, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_sqlite_option_get,					gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
/* Experimental */
GNSDK_LOADER_WRAPPED_API_1(gnsdk_storage_sqlite, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_SQLite, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_sqlite_use_external_library,			gnsdk_cstr_t, sqlite3_filepath)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_storage_sqlite, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_SQLite, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_sqlite_initialize_external_library,	gnsdk_manager_handle_t, sdkmgr_handle, gnsdk_cstr_t, sqlite3_filepath)
#endif /* GNSDK_STORAGE_SQLITE */

/******************************************************************************
** GNSDK QNX APIs
*/
#if GNSDK_STORAGE_QNX
GNSDK_LOADER_WRAPPED_API_1(gnsdk_storage_qnx, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_QNX, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_qnx_initialize,				gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_storage_qnx, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_QNX, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_qnx_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_storage_qnx, gnsdk_cstr_t,			GNSDK_NULL,						gnsdk_storage_qnx_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_storage_qnx, gnsdk_cstr_t,			GNSDK_NULL,						gnsdk_storage_qnx_get_build_date)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_storage_qnx, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_QNX, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_qnx_option_set,				gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_storage_qnx, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Storage_QNX, GNSDKERR_LibraryNotLoaded),		gnsdk_storage_qnx_option_get,				gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
#endif /* GNSDK_STORAGE_QNX */

/******************************************************************************
** GNSDK Lookup LocalStream APIs
*/
#if GNSDK_LOOKUP_LOCALSTREAM
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_initialize,			gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_localstream, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_lookup_localstream_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_localstream, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_lookup_localstream_get_build_date)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded), 		gnsdk_lookup_localstream_option_set,			gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded), 		gnsdk_lookup_localstream_option_get,			gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_ingest_create,			gnsdk_lookup_localstream_status_fn, callback,	gnsdk_void_t*,	callback_data,gnsdk_lookup_localstream_ingest_handle_t*,ph_ingest_handle  )
GNSDK_LOADER_WRAPPED_API_3(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_ingest_write,			gnsdk_lookup_localstream_ingest_handle_t, h_ingest_handle,	gnsdk_void_t*,	p_ingest_data,	gnsdk_size_t,	data_size)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_ingest_flush,			gnsdk_lookup_localstream_ingest_handle_t,	h_ingest_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_ingest_release,		gnsdk_lookup_localstream_ingest_handle_t,	h_ingest_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_storage_location_set,	gnsdk_cstr_t,	storage_location)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_storage_clear)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_localstream, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_LocalStream, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_localstream_storage_remove,			gnsdk_cstr_t, bundle_id)


#endif /* GNSDK_LOOKUP_LOCAL */

/******************************************************************************
** GNSDK Lookup FP Local APIs
*/
#if GNSDK_LOOKUP_FPLOCAL
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_initialize,				gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_fplocal, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_lookup_fplocal_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_fplocal, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_lookup_fplocal_get_build_date)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_storage_location_set,		gnsdk_cstr_t, storage_name,	gnsdk_cstr_t,	storage_location)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_bundle_ingest,				gnsdk_void_t*, callback_data, 	gnsdk_lookup_fplocal_bundle_read_fn, bundle_read_fn)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_cache_clear)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_cache_count,				gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_cache_enum,				gnsdk_uint32_t,	index, gnsdk_cstr_t*, p_bundle_id)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_cache_delete,				gnsdk_cstr_t, bundle_id)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_deserialize_user_data,				gnsdk_cstr_t, serialized_user_data, gnsdk_byte_t**, deserialized_user_data, gnsdk_uint32_t*, deserialized_user_data_size)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_fplocal, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_FPLocal, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_fplocal_deserialize_free,				gnsdk_byte_t*, deserialized_user_data)
#endif /* GNSDK_LOOKUP_LOCAL */

/******************************************************************************
** GNSDK Lookup Local APIs
*/
#if GNSDK_LOOKUP_LOCAL
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_local, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_Local, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_local_initialize,				gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_local, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_Local, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_local_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_local, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_lookup_local_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_lookup_local, gnsdk_cstr_t,		GNSDK_NULL,						gnsdk_lookup_local_get_build_date)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_lookup_local, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_Local, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_local_storage_compact,				gnsdk_cstr_t, storage_name)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_lookup_local, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_Local, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_local_storage_location_set,		gnsdk_cstr_t, storage_name,	gnsdk_cstr_t,	storage_location)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_lookup_local, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_Local, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_local_storage_validate,			gnsdk_cstr_t, storage_name,	gnsdk_error_info_t*,	p_error_info)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_lookup_local, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_Local, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_local_storage_info_count,			gnsdk_cstr_t, storage_name,	gnsdk_cstr_t,	storage_info_key,	gnsdk_uint32_t*,	p_info_count)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_lookup_local, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_Lookup_Local, GNSDKERR_LibraryNotLoaded),		gnsdk_lookup_local_storage_info_get,			gnsdk_cstr_t,	storage_name,gnsdk_cstr_t,	storage_info_key,	gnsdk_uint32_t,	ordinal,	gnsdk_cstr_t*,	p_storage_info	)
#endif /* GNSDK_LOOKUP_LOCAL */

/******************************************************************************
** GNSDK DSP APIs
*/
#if GNSDK_DSP
GNSDK_LOADER_WRAPPED_API_1(gnsdk_dsp, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_DSP, GNSDKERR_LibraryNotLoaded),		gnsdk_dsp_initialize,					gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_dsp, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_DSP, GNSDKERR_LibraryNotLoaded),		gnsdk_dsp_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_dsp, gnsdk_cstr_t,			GNSDK_NULL,						gnsdk_dsp_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_dsp, gnsdk_cstr_t,			GNSDK_NULL,						gnsdk_dsp_get_build_date)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_dsp, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_DSP, GNSDKERR_LibraryNotLoaded),		gnsdk_dsp_feature_audio_begin, gnsdk_user_handle_t,				user_handle,	gnsdk_cstr_t,					feature_type,	gnsdk_uint32_t,					audio_sample_rate,gnsdk_uint32_t,					audio_sample_size,	gnsdk_uint32_t,					audio_channels,	gnsdk_dsp_feature_handle_t*,		p_feature_handle)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_dsp, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_DSP, GNSDKERR_LibraryNotLoaded),		gnsdk_dsp_feature_audio_write,	gnsdk_dsp_feature_handle_t,		feature_handle,	const gnsdk_byte_t*,				audioData,	gnsdk_size_t,					audioData_bytes,	gnsdk_bool_t*,					pb_complete	)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_dsp, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_DSP, GNSDKERR_LibraryNotLoaded),		gnsdk_dsp_feature_end_of_write,	gnsdk_dsp_feature_handle_t,		feature_handle	)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_dsp, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_DSP, GNSDKERR_LibraryNotLoaded),		gnsdk_dsp_feature_retrieve_data,	gnsdk_dsp_feature_handle_t,		feature_handle,	gnsdk_dsp_feature_qualities_t*,	p_feature_qualities,	gnsdk_cstr_t*,					p_feature_data	)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_dsp, gnsdk_error_t,		GNSDKERR_MAKE_ERROR(GNSDKPKG_DSP, GNSDKERR_LibraryNotLoaded),		gnsdk_dsp_feature_release,	gnsdk_dsp_feature_handle_t,		feature_handle	)

#endif /* GNSDK_DSP */


/******************************************************************************
** GNSDK Playlist APIs
*/
#if GNSDK_PLAYLIST
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_initialize,					gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_playlist, gnsdk_cstr_t,	GNSDK_NULL,						gnsdk_playlist_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_playlist, gnsdk_cstr_t,	GNSDK_NULL,						gnsdk_playlist_get_build_date)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_attributes_count,			gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_attributes_enum,				gnsdk_uint32_t, index, gnsdk_cstr_t*, p_attribute_name)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_create,			gnsdk_cstr_t, collection_name, gnsdk_playlist_collection_handle_t*, ph_collection)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_get_name,			gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t*, p_collection_name)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_update_name,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, collection_name)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_release,			gnsdk_playlist_collection_handle_t, h_collection)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_join,				gnsdk_playlist_collection_handle_t, h_destination, gnsdk_playlist_collection_handle_t,	h_join)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_join_count,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_join_enum,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_uint32_t, index, gnsdk_playlist_collection_handle_t*,	p_joined_collection)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_join_get,			gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, collection_name, gnsdk_playlist_collection_handle_t*, p_joined_collection)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_add_ident,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, ident)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_add_gdo,			gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, ident, gnsdk_gdo_handle_t, media_gdo)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_add_list_element,	gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, ident, gnsdk_list_element_handle_t, media_list_element)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_ident_find,		gnsdk_playlist_collection_handle_t,	h_collection, gnsdk_cstr_t,	media_ident, 	gnsdk_uint32_t,	start_index, gnsdk_uint32_t*,	p_found_index, 	gnsdk_cstr_t*,	p_collection_name)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_ident_count,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_ident_enum,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_uint32_t, index, gnsdk_cstr_t*, p_ident, gnsdk_cstr_t*, p_collection_name)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_get_gdo,	        gnsdk_playlist_collection_handle_t, h_collection, gnsdk_user_handle_t, user_handle, gnsdk_cstr_t, ident, gnsdk_gdo_handle_t*, ph_gdo_ident)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_ident_remove,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, ident)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_sync_ident_add,	gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, ident)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_sync_process,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_playlist_update_callback_fn, callback_fn, gnsdk_void_t*, callback_data)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_serialize_size,	gnsdk_playlist_collection_handle_t, h_collection, gnsdk_size_t*, p_size)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_serialize,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_byte_t*, p_collection_buf, gnsdk_size_t*, p_buf_size)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_deserialize,		gnsdk_byte_t*, p_collection_buf, gnsdk_size_t, buf_size, gnsdk_playlist_collection_handle_t*, ph_collection)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_attributes_count,	gnsdk_playlist_collection_handle_t, h_collection, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_attributes_enum,	gnsdk_playlist_collection_handle_t, h_collection, gnsdk_uint32_t, index, gnsdk_cstr_t*, p_attribute_name)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_statement_validate,			gnsdk_cstr_t, pdl_statement, gnsdk_playlist_collection_handle_t, h_collection, gnsdk_bool_t*, pb_seed_required)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_statement_analyze_ident,		gnsdk_cstr_t, pdl_statement, gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, ident, gnsdk_str_t*, p_pdl_outcome)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_generate_playlist,			gnsdk_user_handle_t, user_handle, gnsdk_cstr_t, pdl_statement, gnsdk_playlist_collection_handle_t, h_collection, gnsdk_gdo_handle_t, h_gdo_seed, gnsdk_playlist_results_handle_t*, ph_results)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_generate_morelikethis,		gnsdk_user_handle_t, user_handle, gnsdk_playlist_collection_handle_t, h_collection, gnsdk_gdo_handle_t, h_gdo_seed, gnsdk_playlist_results_handle_t*, ph_results)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_results_count,				gnsdk_playlist_results_handle_t, h_results, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_results_enum,				gnsdk_playlist_results_handle_t, h_results, gnsdk_uint32_t, index, gnsdk_cstr_t*, p_ident,gnsdk_cstr_t*,p_collection_name)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_results_release,				gnsdk_playlist_results_handle_t, h_results)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_morelikethis_option_get,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_morelikethis_option_set,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, option_key, gnsdk_cstr_t,  option_value)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_store_collection,	gnsdk_playlist_collection_handle_t, h_collection)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_load_collection,		gnsdk_cstr_t, collection_name, gnsdk_playlist_collection_handle_t*, ph_collection)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_count_collections,	gnsdk_uint32_t*, p_collection_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_enum_collections,	gnsdk_uint32_t, index, gnsdk_char_t*, collection_name_buf, gnsdk_size_t, buf_size)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_remove_collection,	gnsdk_cstr_t, collection_name)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_compact)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_location_set,		gnsdk_cstr_t,	storage_location)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_validate,			gnsdk_error_info_t*, p_valid)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_storage_version_get,			gnsdk_cstr_t*,	p_version)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_playlist, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Playlist, GNSDKERR_LibraryNotLoaded),		gnsdk_playlist_collection_join_remove,		gnsdk_playlist_collection_handle_t, h_collection, gnsdk_cstr_t, collection_name)
#endif /* GNSDK_PLAYLIST */

/******************************************************************************
** GNSDK SUBMIT APIs
*/
#if GNSDK_SUBMIT
GNSDK_LOADER_WRAPPED_API_1(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_initialize,			gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_submit, gnsdk_cstr_t,	GNSDK_NULL,				   gnsdk_submit_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_submit, gnsdk_cstr_t,	GNSDK_NULL,				   gnsdk_submit_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_create,			gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_submit_parcel_handle_t*, p_parcel_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_release,			gnsdk_submit_parcel_handle_t, parcel_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_data_add_gdo,		gnsdk_submit_parcel_handle_t, parcel_handle, gnsdk_gdo_handle_t, gdo, gnsdk_cstr_t ,data_ident)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_data_init_features,	gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_gdo_handle_t, gdo, gnsdk_uint32_t, flags,	gnsdk_bool_t* ,p_something_to_do)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_feature_init_audio,	gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_cstr_t, data_id, gnsdk_uint32_t, track_num, gnsdk_uint32_t, audio_rate, gnsdk_submit_audio_format_t, audio_format, gnsdk_uint32_t ,audio_channels)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_feature_option_set,	gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_cstr_t, data_id, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_feature_option_get,	gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_cstr_t, data_id, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_feature_write_audio_data,gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_cstr_t, data_id, const gnsdk_byte_t*, audioData,	gnsdk_size_t, audioData_bytes,gnsdk_bool_t*, p_complete)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_feature_finalize,	gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_cstr_t, data_id, gnsdk_bool_t, abort)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_upload,			gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_uint32_t, flags,	gnsdk_submit_state_t*, p_state)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_parcel_data_get_state,		gnsdk_submit_parcel_handle_t, parcel_handle,	gnsdk_cstr_t, id, gnsdk_submit_state_t*, p_state, gnsdk_error_t*, p_error, gnsdk_cstr_t*, p_info)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_create_album_from_toc,		gnsdk_cstr_t,		toc,			gnsdk_gdo_handle_t*,			p_edit_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_create_empty,			gnsdk_cstr_t,		context,		gnsdk_gdo_handle_t*,			p_edit_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_create_from_gdo,		gnsdk_gdo_handle_t,	source_gdo,		gnsdk_gdo_handle_t*,			p_edit_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_create_from_xml,		gnsdk_cstr_t,		xml,			gnsdk_gdo_handle_t*,			p_edit_gdo)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_value_set,			gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_cstr_t,				key,	gnsdk_uint32_t,	ordinal,gnsdk_cstr_t,	value)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_value_has_changed,		gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_cstr_t,				key,	gnsdk_uint32_t,	ordinal,gnsdk_bool_t*,	p_has_changed)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_child_add_empty,		gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_cstr_t,				child_key,gnsdk_gdo_handle_t*,	p_edit_gdo)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_child_add_from_gdo,		gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_cstr_t,				child_key,gnsdk_gdo_handle_t,	child_gdo_handle,gnsdk_gdo_handle_t*,	p_edit_gdo)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_child_add_from_xml,		gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_cstr_t,				child_key,	gnsdk_cstr_t,	child_xml,	gnsdk_gdo_handle_t*,	p_edit_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_child_remove,			gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_gdo_handle_t,			edit_gdo_child_handle)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_list_value_set_by_submit_id,	gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_cstr_t,				list_type,	gnsdk_uint32_t,	ordinal,	gnsdk_uint32_t,	list_item_submit_id)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_list_value_get_submit_id,	gnsdk_gdo_handle_t,	edit_gdo_handle,	gnsdk_cstr_t,				list_type,	gnsdk_uint32_t,	ordinal,	gnsdk_uint32_t*, p_list_item_submit_id)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_submit, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Submit, GNSDKERR_LibraryNotLoaded), gnsdk_submit_edit_gdo_validate,	gnsdk_gdo_handle_t, edit_gdo_handle,	gnsdk_submit_gdo_validate_callback_fn, callback_fn, gnsdk_void_t*, callback_data, const gnsdk_error_info_t**, p_last_error)
#endif /* GNSDK_SUBMIT */


/******************************************************************************
** GNSDK ACR APIs
*/
#if GNSDK_ACR
GNSDK_LOADER_WRAPPED_API_1(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_initialize,			gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_acr, gnsdk_cstr_t,		GNSDK_NULL,				   gnsdk_acr_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_acr, gnsdk_cstr_t,		GNSDK_NULL,				   gnsdk_acr_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_create,	gnsdk_user_handle_t,	user_handle,gnsdk_acr_callbacks_t*,	callbacks, gnsdk_void_t*, callback_data, gnsdk_acr_query_handle_t*, query_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_wait_for_complete,	gnsdk_acr_query_handle_t,	query_handle,gnsdk_uint32_t, timout)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_release,	gnsdk_acr_query_handle_t, query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_option_set,	gnsdk_acr_query_handle_t,	query_handle, gnsdk_cstr_t,	option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_option_get,	gnsdk_acr_query_handle_t,	query_handle, gnsdk_cstr_t,	option_key, gnsdk_cstr_t*, option_value)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_init_audio_stream,	gnsdk_acr_query_handle_t,	query_handle, gnsdk_acr_audio_alg_t,	alg,gnsdk_uint32_t,	sammple_rate,gnsdk_acr_audio_sample_format_t,	sample_formate,gnsdk_uint32_t, channels)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_write_audio_data,gnsdk_acr_query_handle_t,acr_query_handle,const gnsdk_void_t*,audioData,gnsdk_size_t,audioData_bytes,gnsdk_time_us_t,timestamp)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_write_complete,	gnsdk_acr_query_handle_t, query_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_manual_lookup,	gnsdk_acr_query_handle_t, query_handle)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_video_query_create,	gnsdk_user_handle_t, user_handle, gnsdk_acr_callbacks_t*, callbacks, gnsdk_void_t*, callback_data, gnsdk_acr_query_handle_t*, p_acr_query_handle)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_init_video_stream, gnsdk_acr_query_handle_t, acr_query_handle, gnsdk_acr_video_alg_t, video_alg, gnsdk_flt32_t, video_frame_rate,	gnsdk_acr_video_frame_format_t, video_frame_format, gnsdk_acr_video_origin_t, origin)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_write_video_frame, gnsdk_acr_query_handle_t, acr_query_handle, const gnsdk_void_t*, video_frame, gnsdk_size_t, video_frame_bytes,	gnsdk_uint32_t, width, gnsdk_uint32_t, height, gnsdk_time_us_t, timestamp)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_acr, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_ACR, GNSDKERR_LibraryNotLoaded), gnsdk_acr_query_music_lookup, gnsdk_acr_query_handle_t, query_handle)
#endif /*GNSDK_ACR*/


/******************************************************************************
** GNSDK MUSICID MATCH APIs
*/
#if GNSDK_MUSICID_MATCH
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_initialize,				gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_match, gnsdk_cstr_t,	GNSDK_NULL,				   gnsdk_musicidmatch_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_musicid_match, gnsdk_cstr_t,	GNSDK_NULL,				   gnsdk_musicidmatch_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_create,				gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_musicidmatch_query_handle_t*, p_musicid_match_query_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_release,			gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_set_id_datasource,	gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle, gnsdk_cstr_t, id_source)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_set_lookup_fp,		gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle, gnsdk_cstr_t, ident, gnsdk_cstr_t, fp_data)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_set_compare_fp,		gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle, gnsdk_cstr_t, ident, gnsdk_cstr_t, fp_data)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_set_compare_data,	gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle, gnsdk_cstr_t, ident, gnsdk_cstr_t, id_data)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_option_set,			gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_option_get,			gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_find_matches,		gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_musicid_match, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MusicID_Match, GNSDKERR_LibraryNotLoaded), gnsdk_musicidmatch_query_get_response,		gnsdk_musicidmatch_query_handle_t,	musicid_match_query_handle, gnsdk_cstr_t, ident, gnsdk_gdo_handle_t*, p_response_gdo)
#endif /*GNSDK_MUSICID_MATCH*/


/******************************************************************************
** GNSDK EPG APIs
*/
#if GNSDK_EPG

GNSDK_LOADER_WRAPPED_API_1(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_initialize, gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_epg, gnsdk_cstr_t,		GNSDK_NULL, 				gnsdk_epg_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_epg, gnsdk_cstr_t,		GNSDK_NULL, 				gnsdk_epg_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_create,  			gnsdk_user_handle_t,		user_handle,	gnsdk_status_callback_fn,		callback_fn,		gnsdk_void_t*,				callback_data,	gnsdk_epg_query_handle_t*,	p_epg_query_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_release, 			gnsdk_epg_query_handle_t,	epg_query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_option_set,			gnsdk_epg_query_handle_t,	query_handle,	gnsdk_cstr_t,				option_key,			gnsdk_cstr_t,				option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_option_get,			gnsdk_epg_query_handle_t,	query_handle,	gnsdk_cstr_t,				option_key,			gnsdk_cstr_t*,				p_option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_set_postalcode,		gnsdk_epg_query_handle_t,	query_handle,	gnsdk_cstr_t,				postalcode_country,	gnsdk_cstr_t,				postalcode)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_add_channel_id,		gnsdk_epg_query_handle_t,	query_handle,	gnsdk_cstr_t,				type,				gnsdk_cstr_t,				id,					gnsdk_cstr_t,				ident)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_add_tvchannel_gdo,	gnsdk_epg_query_handle_t,	query_handle,	gnsdk_gdo_handle_t,			channel_gdo,		gnsdk_cstr_t,				ident)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_set_gdo,			gnsdk_epg_query_handle_t,	query_handle,	gnsdk_gdo_handle_t,			query_gdo)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_set_text,			gnsdk_epg_query_handle_t,	query_handle,	gnsdk_cstr_t,				field,				gnsdk_cstr_t,				text)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_set_time_start,		gnsdk_epg_query_handle_t,	query_handle,	gnsdk_uint32_t, 			year,				gnsdk_uint32_t, 			month,				gnsdk_uint32_t, 			day,				gnsdk_uint32_t, 	hour,	gnsdk_uint32_t, minute)
GNSDK_LOADER_WRAPPED_API_6(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_set_time_end,		gnsdk_epg_query_handle_t,	query_handle,	gnsdk_uint32_t, 			year,				gnsdk_uint32_t, 			month,				gnsdk_uint32_t, 			day,				gnsdk_uint32_t, 	hour,	gnsdk_uint32_t, minute)
GNSDK_LOADER_WRAPPED_API_7(gnsdk_epg, gnsdk_error_t, 	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_timestamp_parse,			gnsdk_cstr_t*, 				timestamp,		gnsdk_uint32_t*, 			year,				gnsdk_uint32_t*,			month,				gnsdk_uint32_t*, 			day,				gnsdk_uint32_t*, 	hour,	gnsdk_uint32_t*, minute, gnsdk_uint32_t*, second)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_find_programs,		gnsdk_epg_query_handle_t,	query_handle,	gnsdk_gdo_handle_t*,		p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_find_tvproviders,	gnsdk_epg_query_handle_t,	query_handle,	gnsdk_gdo_handle_t*,		p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_find_channels,		gnsdk_epg_query_handle_t,	query_handle,	gnsdk_gdo_handle_t*,		p_response_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_epg, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_EPG, GNSDKERR_LibraryNotLoaded), 	gnsdk_epg_query_find_tvairings,		gnsdk_epg_query_handle_t,	query_handle,	gnsdk_gdo_handle_t*,		p_response_gdo)
#endif /*GNSDK_EPG*/

/******************************************************************************
** GNSDK MOODGRID APIs
*/
#if GNSDK_MOODGRID

GNSDK_LOADER_WRAPPED_API_1(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_initialize,									gnsdk_manager_handle_t,						sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_moodgrid, gnsdk_cstr_t,	GNSDK_NULL, 			gnsdk_moodgrid_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_moodgrid, gnsdk_cstr_t,	GNSDK_NULL, 			gnsdk_moodgrid_get_build_date)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_provider_count,								gnsdk_uint32_t*,							p_count)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_provider_enum,								gnsdk_uint32_t,								index,				gnsdk_moodgrid_provider_handle_t*,	ph_provider)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_provider_get_data,							gnsdk_moodgrid_provider_handle_t,			h_provider,			gnsdk_cstr_t,						key,				gnsdk_cstr_t*,						p_value)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_provider_release,							gnsdk_moodgrid_provider_handle_t,			h_provider)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_type_dimension,					gnsdk_moodgrid_presentation_type_t,			presentation_type, 	gnsdk_uint32_t*	,					p_x_size,			gnsdk_uint32_t*,					p_y_size)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_create,							gnsdk_user_handle_t,						user_handle,		gnsdk_moodgrid_presentation_type_t,	presentation_type,	gnsdk_status_callback_fn,		callback_fn, gnsdk_void_t*,	callback_data,	gnsdk_moodgrid_presentation_handle_t* ,	ph_presentation)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_release,						gnsdk_moodgrid_presentation_handle_t,		h_presentation)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_get_type,						gnsdk_moodgrid_presentation_handle_t,		h_presentation,		gnsdk_moodgrid_presentation_type_t*,p_presentation_type)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_get_mood_name,					gnsdk_moodgrid_presentation_handle_t,		h_presentation,		gnsdk_uint32_t,						x_ordinal,			gnsdk_uint32_t,						y_ordinal, 	gnsdk_cstr_t*, p_mood_name)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_get_mood_id,					gnsdk_moodgrid_presentation_handle_t,		h_presentation,		gnsdk_uint32_t,						x_ordinal,			gnsdk_uint32_t,						y_ordinal,	gnsdk_cstr_t*,					p_mood_id)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_moodgrid, gnsdk_error_t, 	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_find_recommendations,			gnsdk_moodgrid_presentation_handle_t,		h_presentation,		gnsdk_moodgrid_provider_handle_t,   h_provider,			gnsdk_uint32_t,						x_ordinal,	gnsdk_uint32_t,					y_ordinal,	gnsdk_moodgrid_result_handle_t*,ph_result)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_find_recommendations_estimate,	gnsdk_moodgrid_presentation_handle_t,		h_presentation,		gnsdk_moodgrid_provider_handle_t,   h_provider,			gnsdk_uint32_t,						x_ordinal,	gnsdk_uint32_t,					y_ordinal,	gnsdk_uint32_t*,				p_estimate)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_filter_set,						gnsdk_moodgrid_presentation_handle_t,		h_presentation,		gnsdk_cstr_t,						ident,				gnsdk_cstr_t,						list_type,	gnsdk_cstr_t ,					item_value_id,gnsdk_cstr_t,condition_type)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_filter_remove,					gnsdk_moodgrid_presentation_handle_t,		h_presentation,		gnsdk_cstr_t,						ident)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_presentation_filter_remove_all,				gnsdk_moodgrid_presentation_handle_t,		h_presentation)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_results_count,								gnsdk_moodgrid_result_handle_t,				h_results,			gnsdk_uint32_t*,					p_count)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_results_enum,								gnsdk_moodgrid_result_handle_t,				h_results,			gnsdk_uint32_t,						index,				gnsdk_cstr_t*,						p_ident,gnsdk_cstr_t*, 							p_group)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_moodgrid, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_MoodGrid, GNSDKERR_LibraryNotLoaded), 	gnsdk_moodgrid_results_release,								gnsdk_moodgrid_result_handle_t,				h_results)
#endif /*GNSDK_MOODGRID*/

/******************************************************************************
** GNSDK CORRELATES APIs
*/
#if GNSDK_CORRELATES
GNSDK_LOADER_WRAPPED_API_1(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded), 	gnsdk_correlates_initialize,							gnsdk_manager_handle_t,						sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded), 	gnsdk_correlates_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_correlates, gnsdk_cstr_t,	GNSDK_NULL, 															gnsdk_correlates_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_correlates, gnsdk_cstr_t,	GNSDK_NULL, 															gnsdk_correlates_get_build_date)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded),	gnsdk_correlates_retrieve,							 	gnsdk_cstr_t, correlates_type, gnsdk_user_handle_t,	user_handle, gnsdk_status_callback_fn, callback, gnsdk_void_t*, callback_data, gnsdk_list_correlates_handle_t*, p_correlates_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded),	gnsdk_correlates_data_revision,							gnsdk_list_correlates_handle_t, correlates_handle, gnsdk_uint32_t*, p_revision)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded),	gnsdk_correlates_render_set,							gnsdk_list_correlates_handle_t, correlates_handle, gnsdk_uint32_t, master_id, gnsdk_str_t*, p_xml)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded),	gnsdk_correlates_get_correlates_for_id,					gnsdk_list_correlates_handle_t, correlates_handle, gnsdk_uint32_t, master_id, gnsdk_list_correlateset_handle_t*, p_correlateset_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded),	gnsdk_correlates_get_correlation,						gnsdk_list_correlateset_handle_t, correlateset_handle, gnsdk_uint32_t, master_id, gnsdk_int32_t*, p_weight)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_correlates, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Correlates, GNSDKERR_LibraryNotLoaded), 	gnsdk_correlates_release,								gnsdk_list_correlates_handle_t,	correlates_handle)
#endif /*GNSDK_CORRELATES*/

/******************************************************************************
 ** GNSDK TASTEPROFILE APIs
 */
#if GNSDK_TASTEPROFILE
GNSDK_LOADER_WRAPPED_API_1(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_initialize, gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_tasteprofile, gnsdk_cstr_t,	GNSDK_NULL, 													gnsdk_tasteprofile_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_tasteprofile, gnsdk_cstr_t,	GNSDK_NULL, 													gnsdk_tasteprofile_get_build_date)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_create, gnsdk_cstr_t, persona_name, gnsdk_tasteprofile_persona_handle_t*, p_taste_persona_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_get_name, gnsdk_tasteprofile_persona_handle_t, taste_persona_handle, gnsdk_cstr_t*, p_persona_name)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_release, gnsdk_tasteprofile_persona_handle_t,	taste_persona_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_serialize, gnsdk_tasteprofile_persona_handle_t, taste_persona_handle, gnsdk_byte_t*, p_buf, gnsdk_size_t*, p_buf_size)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_serialize_size, gnsdk_tasteprofile_persona_handle_t, taste_persona_handle, gnsdk_size_t*, p_size)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_deserialize, gnsdk_byte_t*, p_buf, gnsdk_size_t, buf_size, gnsdk_tasteprofile_persona_handle_t*,    p_taste_persona_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_option_set, gnsdk_tasteprofile_persona_handle_t, taste_persona_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_option_get, gnsdk_tasteprofile_persona_handle_t, taste_persona_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_persona_add_gdo,	gnsdk_tasteprofile_persona_handle_t, taste_persona_handle, gnsdk_gdo_handle_t,  gdo, gnsdk_tasteprofile_action_t, action)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_channelset_create, gnsdk_tasteprofile_persona_handle_t, taste_persona_handle, gnsdk_tasteprofile_channelset_handle_t*, p_channelset_handle, gnsdk_uint32_t, max_channels)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_channelset_release, gnsdk_tasteprofile_channelset_handle_t, channelset_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_channelset_count, gnsdk_tasteprofile_channelset_handle_t, channelset_handle, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_channelset_pdl_enum, gnsdk_tasteprofile_channelset_handle_t, channelset_handle, gnsdk_uint32_t,   index, gnsdk_cstr_t*, pdl_statement)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_tasteprofile, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_tasteprofile_channelset_composition_enum, gnsdk_tasteprofile_channelset_handle_t, channelset_handle, gnsdk_uint32_t, index, gnsdk_void_t**, p_composition)
#endif /*GNSDK_TASTEPROFILE*/

/******************************************************************************
 ** GNSDK TASTE APIs
 */
#if GNSDK_TASTE
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_initialize, gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_taste, gnsdk_cstr_t,	GNSDK_NULL, 													gnsdk_taste_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_taste, gnsdk_cstr_t,	GNSDK_NULL, 													gnsdk_taste_get_build_date)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_create,				gnsdk_user_handle_t, user_handle, gnsdk_cstr_t, persona_name, gnsdk_taste_persona_handle_t*, p_taste_persona_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_get_name,			gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_cstr_t*, p_persona_name)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_set_name,			gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_cstr_t, persona_name)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_observation_count,	gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_release,			gnsdk_taste_persona_handle_t, taste_persona_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_serialize,			gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_byte_t*, p_buf, gnsdk_size_t*, p_buf_size)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_serialize_size,		gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_size_t*, p_size)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_deserialize,		gnsdk_user_handle_t, user_handle, gnsdk_byte_t*, p_buf, gnsdk_size_t, buf_size, gnsdk_taste_persona_handle_t*, p_taste_persona_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_option_set,			gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_option_get,			gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_persona_add_gdo,			gnsdk_taste_persona_handle_t, taste_persona_handle, gnsdk_gdo_handle_t,  gdo, gnsdk_taste_action_t, action)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channelset_create,			gnsdk_taste_persona_handle_t, taste_persona_handle,gnsdk_locale_handle_t, locale, gnsdk_uint32_t, max_channels, gnsdk_taste_channelset_handle_t*, p_channelset_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channelset_release,			gnsdk_taste_channelset_handle_t, channelset_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channelset_count,			gnsdk_taste_channelset_handle_t, channelset_handle, gnsdk_uint32_t*, p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channelset_channel_enum,	gnsdk_taste_channelset_handle_t, channelset_handle, gnsdk_uint32_t, index, gnsdk_taste_channel_handle_t*, p_channel_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channel_pdl_get,			gnsdk_taste_channel_handle_t, channel_handle, gnsdk_uint32_t, flags, gnsdk_cstr_t*, p_pdl_statement)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channel_observation_count,	gnsdk_taste_channel_handle_t, channel_handle, gnsdk_uint32_t*, p_observation_count)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channel_attribute_count,	gnsdk_taste_channel_handle_t, channel_handle, gnsdk_uint32_t*,   p_count)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channel_attribute_enum,		gnsdk_taste_channel_handle_t, channel_handle, gnsdk_uint32_t, index, gnsdk_cstr_t*, component_name)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channel_component_count,	gnsdk_taste_channel_handle_t, channel_handle, gnsdk_cstr_t , component_name,  gnsdk_uint32_t*,   p_count)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channel_component_enum,		gnsdk_taste_channel_handle_t, channel_handle, gnsdk_cstr_t , component_name, gnsdk_uint32_t, index,gnsdk_list_element_handle_t*, p_list_element, gnsdk_flt32_t*, p_weight)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded), gnsdk_taste_channel_release,			gnsdk_taste_channel_handle_t, channel_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_store_persona,		gnsdk_taste_persona_handle_t, h_persona)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_load_persona,		gnsdk_cstr_t, persona_name, gnsdk_taste_persona_handle_t*, ph_persona)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_count_personas,		gnsdk_uint32_t*, p_persona_count)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_enum_personas,		gnsdk_uint32_t, index, gnsdk_cstr_t*, p_persona_name)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_remove_persona,		gnsdk_cstr_t, persona_name)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_compact)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_location_set,		gnsdk_cstr_t, storage_location)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_validate,			gnsdk_error_info_t*, p_valid)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_taste, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Taste, GNSDKERR_LibraryNotLoaded),	gnsdk_taste_storage_version_get,		gnsdk_cstr_t*,	p_version)
#endif /*GNSDK_TASTE*/

/******************************************************************************
 ** GNSDK TASTE APIs
 */
#if GNSDK_RHYTHM
GNSDK_LOADER_WRAPPED_API_1(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_initialize,						gnsdk_manager_handle_t, sdkmgr_handle)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_shutdown)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_rhythm, gnsdk_cstr_t,	GNSDK_NULL, 													 gnsdk_rhythm_get_version)
GNSDK_LOADER_WRAPPED_API_0(gnsdk_rhythm, gnsdk_cstr_t,	GNSDK_NULL, 													 gnsdk_rhythm_get_build_date)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_query_create,						gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_rhythm_query_handle_t*, p_rhythm_query_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_query_release,					gnsdk_rhythm_query_handle_t, rhythm_query_handle)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_query_option_set,					gnsdk_rhythm_query_handle_t, rhythm_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_query_option_get,					gnsdk_rhythm_query_handle_t, rhythm_query_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_query_set_gdo,					gnsdk_rhythm_query_handle_t, rhythm_query_handle, gnsdk_gdo_handle_t, seed_gdo)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_query_generate_recommendations,	gnsdk_rhythm_query_handle_t, rhythm_query_handle, gnsdk_gdo_handle_t*, p_response_gdo)
GNSDK_LOADER_WRAPPED_API_4(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_query_generate_station,			gnsdk_rhythm_query_handle_t, rhythm_query_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_rhythm_station_handle_t*, p_rhythm_station_handle)
GNSDK_LOADER_WRAPPED_API_5(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_station_lookup,					gnsdk_cstr_t, station_id, gnsdk_user_handle_t, user_handle, gnsdk_status_callback_fn, callback_fn, gnsdk_void_t*, callback_data, gnsdk_rhythm_station_handle_t*, p_rhythm_station_handle)
GNSDK_LOADER_WRAPPED_API_1(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_station_release,					gnsdk_rhythm_station_handle_t, rhythm_station_handle)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_station_id,						gnsdk_rhythm_station_handle_t, rhythm_station_handle, gnsdk_cstr_t*, p_station_id)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_station_option_set,				gnsdk_rhythm_station_handle_t, rhythm_station_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t, option_value)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_station_option_get,				gnsdk_rhythm_station_handle_t, rhythm_station_handle, gnsdk_cstr_t, option_key, gnsdk_cstr_t*, p_option_value)
GNSDK_LOADER_WRAPPED_API_2(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_station_generate_playlist,		gnsdk_rhythm_station_handle_t, rhythm_station_handle, gnsdk_gdo_handle_t*, p_results_gdo)
GNSDK_LOADER_WRAPPED_API_3(gnsdk_rhythm, gnsdk_error_t,	GNSDKERR_MAKE_ERROR(GNSDKPKG_Rhythm, GNSDKERR_LibraryNotLoaded), gnsdk_rhythm_station_event,					gnsdk_rhythm_station_handle_t, rhythm_station_handle, gnsdk_rhythm_event_t, event_type, gnsdk_gdo_handle_t, event_gdo)
#endif /*GNSDK_TASTE*/
