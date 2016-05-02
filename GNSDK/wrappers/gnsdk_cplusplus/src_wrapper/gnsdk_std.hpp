/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_STD_HPP_
#define _GNSDK_STD_HPP_

#include "gnsdk.h"

#ifndef __cplusplus
#error "C++ compiler required"
#endif

namespace gracenote
{
	class gnstd
	{
	public:
		static const char*  kEmptyString;
		static bool
		gn_strtobool(gnsdk_cstr_t value);

		static gnsdk_int32_t
		gn_atoi(gnsdk_cstr_t value);

		static bool
		gn_itoa(char* buffer, gnsdk_size_t buffer_sz, int value);

		static gnsdk_int32_t
		gn_strcmp(gnsdk_cstr_t lhs, gnsdk_cstr_t rhs);

		static gnsdk_size_t
		gn_strlen(gnsdk_cstr_t s);

		static gnsdk_size_t
		gn_strcpy(char* dest, gnsdk_size_t dest_size, gnsdk_cstr_t src);
	};

}

#endif // _GNSDK_STD_HPP_
