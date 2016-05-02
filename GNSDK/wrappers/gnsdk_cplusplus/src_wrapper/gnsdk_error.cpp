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

#include "gnsdk_error.hpp"
#include "gnsdk_log.hpp"

using namespace gracenote;


/******************************************************************************
** GnError
*/
GnError::GnError()
{
	const gnsdk_error_info_t* pErrorInfo = gnsdk_manager_error_info();
	_copy_errorinfo(pErrorInfo);

	if (m_pErrorInfo->error_code)
	{
		GnLog::Write(0, GNSDK_NULL, GNSDKPKG_Wrapper, kLoggingMessageTypeError, "GnError (%0x08X) \"%s\"", 
			m_pErrorInfo->error_code,
			m_pErrorInfo->error_description
			);
	}
}


GnError::GnError(const gnsdk_error_info_t* pErrorInfo)
{
	_copy_errorinfo(pErrorInfo);
}

GnError::GnError(gnsdk_uint32_t errorCode, gnsdk_cstr_t errorDescription)
{
	gnsdk_error_info_t errorInfo;

	errorInfo.error_code = errorCode;
	errorInfo.source_error_code = errorCode;
	errorInfo.error_description = errorDescription;
	errorInfo.error_module = GNSDK_NULL;
	errorInfo.error_api = GNSDK_NULL;
	errorInfo.source_error_module = GNSDK_NULL;

	_copy_errorinfo(&errorInfo);
}

GnError::GnError(const GnError& gnError)
{
	_copy_errorinfo(gnError.m_pErrorInfo);
}

GnError& GnError::operator= (const GnError& rhs)
{
	/* Check for self assignment */
	if (this == &rhs)
	{
		return *this;
	}

	_copy_errorinfo(rhs.m_pErrorInfo);
	return *this;
}

/*-----------------------------------------------------------------------------
 *  _copy_errorinfo
 */
void
GnError::_copy_errorinfo(const gnsdk_error_info_t* pErrorInfo)
{
	char*        ptr;
    char*        ptr_end;
	gnsdk_size_t count;

	/* pack strings into _buf:
	** [ gnsdk_error_info_t, error_api, 0, error_description, 0, error_module, 0, source_error_module, 0 ]
	*/
	m_pErrorInfo = (gnsdk_error_info_t*)_buf;
    ptr_end = _buf + sizeof(_buf);

	/* numeric values */
	m_pErrorInfo->error_code        = pErrorInfo->error_code;
	m_pErrorInfo->source_error_code = pErrorInfo->source_error_code;

	/* copy error_api */
	ptr                     = (char*)m_pErrorInfo + sizeof( gnsdk_error_info_t );
    count                   = ptr_end - ptr;
	count                   = gnstd::gn_strcpy(ptr, count, pErrorInfo->error_api);
	ptr[count]              = 0;
	m_pErrorInfo->error_api = ptr;

	/* copy error_module */
	ptr                       += count + 1;
    count                      = ptr_end - ptr - 2;
	count                      = gnstd::gn_strcpy(ptr, count, pErrorInfo->error_module);
	ptr[count]                 = 0;
	m_pErrorInfo->error_module = ptr;

	/* copy source_error_module */
	ptr                              += count + 1;
    count                             = ptr_end - ptr - 2;
	count                             = gnstd::gn_strcpy(ptr, count, pErrorInfo->source_error_module);
	ptr[count]                        = 0;
	m_pErrorInfo->source_error_module = ptr;

    /* copy error_description */
    ptr                            += count + 1;
    count                           = ptr_end - ptr - 2;
    count                           = gnstd::gn_strcpy(ptr, count, pErrorInfo->error_description);
    ptr[count]                      = 0;
    m_pErrorInfo->error_description = ptr;
}


/*-----------------------------------------------------------------------------
 *  ErrorAPI
 */
gnsdk_cstr_t
GnError::ErrorAPI() const
{
	return m_pErrorInfo->error_api;
}


/*-----------------------------------------------------------------------------
 *  ErrorCode
 */
gnsdk_error_t
GnError::ErrorCode() const
{
	return m_pErrorInfo->error_code;
}


/*-----------------------------------------------------------------------------
 *  ErrorDescription
 */
gnsdk_cstr_t
GnError::ErrorDescription() const
{
	return m_pErrorInfo->error_description;
}


/*-----------------------------------------------------------------------------
 *  ErrorModule
 */
gnsdk_cstr_t
GnError::ErrorModule() const
{
	return m_pErrorInfo->error_module;
}


/*-----------------------------------------------------------------------------
 *  SourceErrorCode
 */
gnsdk_error_t
GnError::SourceErrorCode() const
{
	return m_pErrorInfo->source_error_code;
}


/*-----------------------------------------------------------------------------
 *  SourceErrorModule
 */
gnsdk_cstr_t
GnError::SourceErrorModule() const
{
	return m_pErrorInfo->source_error_module;
}



