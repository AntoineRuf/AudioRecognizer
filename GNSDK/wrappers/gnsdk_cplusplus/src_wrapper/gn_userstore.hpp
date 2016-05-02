/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

/* IGnUserStore.hpp: Gracenote user storage helper class */

#ifndef _GNUSERSTORE_HPP_
#define _GNUSERSTORE_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk.h"

namespace gracenote
{
	class GnString;


	/**
	 * Delegate interface for providing persistent serialized Gracenote user object storage and retrieval
	 */
	class IGnUserStore
	{
	public:
		virtual ~IGnUserStore() {};

		virtual GnString	LoadSerializedUser(gnsdk_cstr_t clientId) = 0;
		virtual bool		StoreSerializedUser(gnsdk_cstr_t clientId, gnsdk_cstr_t userData) = 0;
	};

}  // namespace gracenote

#endif // _GNUSERSTORE_HPP_
