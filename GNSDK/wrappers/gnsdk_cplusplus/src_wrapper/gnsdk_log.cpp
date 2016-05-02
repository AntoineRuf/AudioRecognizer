/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */

#include "gnsdk_log.hpp"
#include "gnsdk_manager.hpp"

using namespace gracenote;

static void GNSDK_CALLBACK_API
_gnsdk_callback_logging(gnsdk_void_t* callback_data, gnsdk_uint16_t package_id, gnsdk_uint32_t filter_mask, gnsdk_uint32_t error_code, gnsdk_cstr_t message);


static gnsdk_uint16_t 
_log_package( GnLogPackageType package) 
{
	switch (package) 
	{
		case kLogPackageInternal			: return GNSDK_LOG_PKG_GCSL;
		case kLogPackageManager				: return GNSDKPKG_SDKManager;
		case kLogPackageMusicID				: return GNSDKPKG_MusicID;
		case kLogPackageMusicIDFile			: return GNSDKPKG_MusicID_File;
		case kLogPackageLink				: return GNSDKPKG_Link;
		case kLogPackageVideoID				: return GNSDKPKG_VideoID;
		case kLogPackageSubmit				: return GNSDKPKG_Submit;
		case kLogPackagePlaylist			: return GNSDKPKG_Playlist;
		case kLogPackageStorageSqlite		: return GNSDKPKG_Storage_SQLite;
		case kLogPackageDsp					: return GNSDKPKG_DSP;
		case kLogPackageMusicIdMatch		: return GNSDKPKG_MusicID_Match;
		case kLogPackageAcr					: return GNSDKPKG_ACR;
		case kLogPackageLookupLocal			: return GNSDKPKG_Lookup_Local;
		case kLogPackageEDBInstall			: return GNSDKPKG_EDBInstall;
		case kLogPackageEPG					: return GNSDKPKG_EPG;
		case kLogPackageMoodGrid			: return GNSDKPKG_MoodGrid;
		case kLogPackageStorageQNX			: return GNSDKPKG_Storage_QNX;
		case kLogPackageLookupFPLocal		: return GNSDKPKG_Lookup_FPLocal;
		case kLogPackageCorrelates			: return GNSDKPKG_Correlates;
		case kLogPackageTaste				: return GNSDKPKG_Taste;
		case kLogPackageMusicIDStream		: return GNSDKPKG_MusicID_Stream;
		case kLogPackageLookupLocalStream	: return GNSDKPKG_Lookup_LocalStream;
		case kLogPackageRhythm				: return GNSDKPKG_Rhythm;
		case kLogPackageAllGNSDK			: return GNSDK_LOG_PKG_GNSDK;
		case kLogPackageAll					: return GNSDK_LOG_PKG_ALL;
	}
	return 0;
}


static gnsdk_uint16_t 
_log_messageType( GnLogMessageType messageType ) 
{
	gnsdk_uint16_t msgFilter = 0;
		
	switch (messageType)
	{
	case kLoggingMessageTypeError:
		msgFilter = GNSDK_LOG_FILTER_ERROR;
		break;

	case kLoggingMessageTypeWarning:
		msgFilter = GNSDK_LOG_FILTER_WARNING;
		break;

	case kLoggingMessageTypeInfo:
		msgFilter = GNSDK_LOG_FILTER_INFO;
		break;

	case kLoggingMessageTypeDebug:
		msgFilter = GNSDK_LOG_FILTER_DEBUG;
		break;

	case kLoggingMessageTypeInvalid:
		break;
	}
	
	return msgFilter;
}


static GnLogMessageType 
_log_msgFilter( gnsdk_uint32_t msgFilter ) 
{
	GnLogMessageType messageType = kLoggingMessageTypeInvalid;
		
	switch (msgFilter)
	{
	case GNSDK_LOG_FILTER_ERROR:
		messageType = kLoggingMessageTypeError;
		break;

	case GNSDK_LOG_FILTER_WARNING:
		messageType = kLoggingMessageTypeWarning;
		break;

	case GNSDK_LOG_FILTER_INFO:
		messageType = kLoggingMessageTypeInfo;
		break;

	case GNSDK_LOG_FILTER_DEBUG:
		messageType = kLoggingMessageTypeDebug;
		break;
	}
	
	return messageType;
}

/******************************************************************************
** GnLog
*/

/*-----------------------------------------------------------------------------
 *  Logging callback
 */
void GNSDK_CALLBACK_API
_gnsdk_callback_logging(
	gnsdk_void_t*  callback_data,
	gnsdk_uint16_t package_id,
	gnsdk_uint32_t filter_mask,
	gnsdk_uint32_t error_code,
	gnsdk_cstr_t   message)
{
	IGnLogEvents* pLoggingDelegate = (IGnLogEvents*)callback_data;

	if ( pLoggingDelegate )
	{
		GnLogMessageType messageType = _log_msgFilter(filter_mask);
		pLoggingDelegate->LogMessage(package_id, messageType, error_code, message);
	}
}

/*-----------------------------------------------------------------------------
 *  GnLog
 */
GnLog::GnLog(gnsdk_cstr_t logFilePath, IGnLogEvents *pLoggingDelegate):
	mLoggingDelegate(pLoggingDelegate)
{
	gnstd::gn_strcpy(mLogFilePath, GN_LOGGER_FILEPATH_LENGTH, logFilePath);
}

GnLog::GnLog(gnsdk_cstr_t logFilePath,
			const GnLogFilters& filters,
			const GnLogColumns& columns,
			const GnLogOptions& options,
			IGnLogEvents *pLoggingDelegate
			)
{
	gnstd::gn_strcpy(mLogFilePath, sizeof(mLogFilePath), logFilePath);

	mLoggingColumns = columns;
	mLoggingDelegate = pLoggingDelegate;
	mLoggingFilters = filters;
	mLoggingOptions = options;
}

/*-----------------------------------------------------------------------------
 *  ~GnLog
 */
GnLog::~GnLog()
{
	if (GNSDK_NULL != mLoggingDelegate)
	{
		gnsdk_manager_logging_enable_callback(GNSDK_NULL, GNSDK_NULL, 0, 0, 0);
	}
}

/*-----------------------------------------------------------------------------
 *  Options
 */
void
GnLog::Options(GnLogOptions options)
{
	mLoggingOptions = options;
}

/*-----------------------------------------------------------------------------
 *  Filters
 */
void
GnLog::Filters(GnLogFilters filters)
{
	mLoggingFilters = filters;
}

/*-----------------------------------------------------------------------------
 *  Columns
 */
void
GnLog::Columns(GnLogColumns columns)
{
	mLoggingColumns= columns;
}

/*-----------------------------------------------------------------------------
 *  Enable
 */
GnLog&
GnLog::Enable(GnLogPackageType package) throw (GnError)
{
	return Enable(_log_package(package));
}

GnLog&
GnLog::Enable(gnsdk_uint16_t packageId) throw (GnError)
{
	gnsdk_error_t error = GNSDK_SUCCESS;

	if (mLogFilePath[0])
	{
		error= gnsdk_manager_logging_enable(
					mLogFilePath,packageId , mLoggingFilters.mFiltersMask,
					mLoggingColumns.mOptionsMask, mLoggingOptions.mMaxSize, mLoggingOptions.mArchive);
	}
	if ( !error && (GNSDK_NULL != mLoggingDelegate))
	{
		error= gnsdk_manager_logging_enable_callback(
					_gnsdk_callback_logging, (void*)mLoggingDelegate, packageId,
					mLoggingFilters.mFiltersMask, mLoggingColumns.mOptionsMask);
	}

	if (error) { throw GnError(); }

	return *this;
}

/*-----------------------------------------------------------------------------
 *  Disable
 */
GnLog&
GnLog::Disable(GnLogPackageType package) throw (GnError)
{
	return Disable(_log_package(package));
}

GnLog&
GnLog::Disable(gnsdk_uint16_t packageId) throw (GnError)
{
	gnsdk_error_t error= GNSDK_SUCCESS;

	if (mLogFilePath[0])
	{
		error = gnsdk_manager_logging_disable(mLogFilePath, packageId);
	}
	if ( !error )
	{
		error = gnsdk_manager_logging_enable_callback(GNSDK_NULL, GNSDK_NULL, packageId, 0, 0);
	}

	if (error) { throw GnError(); }

	return *this;
}

GnLog& 
GnLog::Register(gnsdk_uint16_t customPackageId, gnsdk_cstr_t customPackageName) throw (GnError)
{
	gnsdk_error_t error = gnsdk_manager_logging_register_package(customPackageId, customPackageName);
	if (error) { throw GnError(); }

	return *this;
}

void 
GnLog::vWrite(gnsdk_int32_t line, gnsdk_cstr_t fileName, gnsdk_uint16_t customPackageId, GnLogMessageType messageType, gnsdk_cstr_t format, va_list argptr)
{
	gnsdk_uint16_t msgFilter;

	if (!_gnsdk_internal::manager_initialized())
		return;	

	msgFilter = _log_messageType(messageType);
	gnsdk_manager_logging_vwrite(line, fileName, customPackageId, msgFilter, format, argptr);
}

/*-----------------------------------------------------------------------------
 *  Write
 */
void
GnLog::Write( gnsdk_int32_t line, gnsdk_cstr_t fileName, gnsdk_uint16_t customPackageId, GnLogMessageType messageType, gnsdk_cstr_t format, ... )
{
	va_list argptr;

	va_start(argptr, format);
	vWrite(line, fileName, customPackageId, messageType, format, argptr);
	va_end(argptr);
}

