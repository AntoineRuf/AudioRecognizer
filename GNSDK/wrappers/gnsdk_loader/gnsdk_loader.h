/** Public header file for Gracenote SDK Dynamic Loader
  * Author:
  *   Copyright (c) 2013 Gracenote, Inc.
  *
  *   This software may not be used in any way or distributed without
  *   permission. All rights reserved.
  *
  *   Some code herein may be covered by US and international patents.
*/

#ifndef _GNSDK_LOADER_H_
#define _GNSDK_LOADER_H_

#include "gnsdk.h"

#ifdef __cplusplus
extern "C"{
#endif


/******************************************************************************
** GNSDK Loader API
** This API must be called before any GNSDK API.
** Parameters:
**	gnsdk_lib_path: path to folder with GNSDK libraries
*/
gnsdk_error_t	gnsdk_loader_set_gnsdk_path(
	gnsdk_cstr_t			gnsdk_lib_path
	);

#ifdef __cplusplus
}
#endif

#endif /* _GNSDK_LOADER_H_ */
