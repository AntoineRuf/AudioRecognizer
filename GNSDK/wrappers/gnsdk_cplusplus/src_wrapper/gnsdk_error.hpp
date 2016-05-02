/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_ERROR_HPP_
#define _GNSDK_ERROR_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4290 ) /* disable "warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)" */
#endif

#include "gnsdk.h"
#include "gnsdk_std.hpp"


namespace gracenote
{
	/**
	 * GNSDK error condition
	 */
	class GnError
	{
	public:

		/**
		 * Construct GnError with the last error condition experienced in the underlying SDK
		 */
		GnError();

		/**
		 * Construct GnError from native error information structure
		 * @param pErrorInfo	[in] Error information structure
		 */
		GnError(const gnsdk_error_info_t* pErrorInfo);

		/**
		 * Construct GnError with specific error code and description
		 * @param errorCode			[in] Error code
		 * @param errorDescription 	[in] Error description
		 */
		GnError(gnsdk_uint32_t errorCode, gnsdk_cstr_t errorDescription);


		/**
		 * Construct GnError from GnError
		 * @param gnError		[in] GnError class object
		 */
		GnError(const GnError& gnError);

		/**
		 * Operator = 
		 * @param other		[in] GnError class object
		 */
		GnError& operator= (const GnError& other);

		/**
		 * Error code.
		 * @return Code
		 */
		gnsdk_error_t
		ErrorCode() const;

		/**
		 * Error description.
		 * @return Description
		 */
		gnsdk_cstr_t
		ErrorDescription() const;

		/**
		 * API where error occurred
		 * @return API name
		 */
		gnsdk_cstr_t
		ErrorAPI() const;

		/**
		 * Module where error occurred
		 * @return Module
		 */
		gnsdk_cstr_t
		ErrorModule() const;

		/**
		 * Source error code
		 * @return Error code
		 */
		gnsdk_error_t
		SourceErrorCode() const;

		/**
		 * Source module where error occurred
		 * @return Module
		 */
		gnsdk_cstr_t
		SourceErrorModule() const;


	private:

		void
		_copy_errorinfo(const gnsdk_error_info_t* pErrorInfo);

		gnsdk_char_t        _buf[512];
		gnsdk_error_info_t* m_pErrorInfo;
	};

} /* namespace gracenote */


#endif /* _GNSDK_ERROR_HPP_ */

