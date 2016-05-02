/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_HPP_
#define _GNSDK_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4290 ) /* disable "warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)" */
#endif

#include "gnsdk_base.hpp"
#include "gn_audiosource.hpp"

#include "gnsdk_log.hpp"
#include "gnsdk_list.hpp"
#include "gnsdk_locale.hpp"
#include "gnsdk_manager.hpp"

#if GNSDK_MUSICID
	#include "gnsdk_musicid.hpp"
#endif

#if GNSDK_MUSICID_FILE
	#include "gnsdk_musicidfile.hpp"
#endif

#if GNSDK_MUSICID_STREAM
	#include "gnsdk_musicidstream.hpp"
#endif

#if GNSDK_MUSICID_MATCH
	#include "gnsdk_musicidmatch.hpp"
#endif

#if GNSDK_VIDEO
	#include "gnsdk_video.hpp"
#endif

#if GNSDK_LINK
	#include "gnsdk_link.hpp"
#endif

#if GNSDK_SUBMIT
	#include "gnsdk_submit.hpp"
#endif

#if GNSDK_DSP
	#include "gnsdk_dsp.hpp"
#endif

#if GNSDK_PLAYLIST
	#include "gnsdk_playlist.hpp"
#endif

#if GNSDK_MOODGRID
	#include "gnsdk_moodgrid.hpp"
#endif

#if GNSDK_STORAGE_SQLITE
	#include "gnsdk_storage_sqlite.hpp"
#endif

#if GNSDK_LOOKUP_LOCAL
	#include "gnsdk_lookup_local.hpp"
#endif

#if GNSDK_LOOKUP_FPLOCAL
	#include "gn_bundlesource.hpp"
	#include "gnsdk_lookup_fplocal.hpp"
#endif

#if GNSDK_LOOKUP_LOCALSTREAM
	#include "gnsdk_lookup_localstream.hpp"
#endif

#if GNSDK_SUBMIT
	#include "gnsdk_submit.hpp"
#endif

#if GNSDK_ACR
	#include "gnsdk_acr.hpp"
#endif

#if GNSDK_EPG
	#include "gnsdk_epg.hpp"
#endif

#if GNSDK_TASTE
 #include "gnsdk_taste.hpp"
#endif

#if GNSDK_CORRELATES
	#include "gnsdk_correlates.hpp"
#endif


#endif /* _GNSDK_HPP_ */

