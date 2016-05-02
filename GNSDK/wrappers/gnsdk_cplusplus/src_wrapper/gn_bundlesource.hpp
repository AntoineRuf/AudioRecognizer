/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

/* gn_bundlesource.hpp: Gracenote bundle ingest delegate class */

#ifndef _GNBUNDLESOURCE_HPP_
#define _GNBUNDLESOURCE_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk.h"

namespace gracenote
{
	/**
	 * Delegate interface for providing bundle ingest bundle data
	 */
	class IGnBundleSource
	{
	public:
		virtual ~IGnBundleSource() { }

		/**
		 * Get bundle data. Override to provide bundle data for the ingestion process.
		 * @param dataBuffer		Buffer to write bundle data
		 * @param dataSize			Size of buffer
		 * @return Number of bytes written to buffer
		 */
		virtual gnsdk_size_t
		GetBundleData(gnsdk_byte_t* dataBuffer, gnsdk_size_t dataSize, IGnCancellable& canceller) = 0;
	};

}  // namespace gracenote

#endif // _GNBUNDLESOURCE_HPP_
