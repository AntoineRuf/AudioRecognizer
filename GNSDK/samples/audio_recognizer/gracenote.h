#define GNSDK_MUSICID_STREAM        1
#define GNSDK_STORAGE_SQLITE        1
#define GNSDK_LOOKUP_LOCAL          1
#define GNSDK_LOOKUP_LOCALSTREAM    1
#define GNSDK_DSP                   1
#include "gnsdk.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
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
_do_sample_musicid_stream(
	gnsdk_user_handle_t user_handle
	);

gnsdk_void_t GNSDK_CALLBACK_API
_musicidstream_identifying_status_callback(
	gnsdk_void_t* callback_data,
	gnsdk_musicidstream_identifying_status_t status,
	gnsdk_bool_t* pb_abort
	);

gnsdk_void_t GNSDK_CALLBACK_API
_musicidstream_result_available_callback(
	gnsdk_void_t* callback_data,
	gnsdk_musicidstream_channel_handle_t channel_handle,
	gnsdk_gdo_handle_t response_gdo,
	gnsdk_bool_t* pb_abort
	);

gnsdk_void_t GNSDK_CALLBACK_API
_musicidstream_completed_with_error_callback(
	gnsdk_void_t* callback_data,
	gnsdk_musicidstream_channel_handle_t channel_handle,
	const gnsdk_error_info_t* p_error_info
	);

void identification();
