/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_LOG_HPP_
#define _GNSDK_LOG_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4290 ) /* disable "warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)" */
#endif

#include "gnsdk_base.hpp"

namespace gracenote
{
	/**
	 * Logging message type. Specifies the message type when writing your own messages to the GNSDK log.
	 */
	enum GnLogMessageType
	{
		kLoggingMessageTypeInvalid = 0,

		kLoggingMessageTypeError,
		kLoggingMessageTypeWarning,
		kLoggingMessageTypeInfo,
		kLoggingMessageTypeDebug

	};

	/**
	 * Delegate interface for receiving logging messages from GNSDK
	 */
	class IGnLogEvents
	{
	public:
		GNWRAPPER_ANNOTATE

		virtual
		~IGnLogEvents() { };

		/**
		 * Implement to receive logging messages from GNSDK
		 * @param packageId  Package Id that generated this message
		 * @param messageType  Type of logging message
		 * @param errorCode  Error code related to message
		 * @param message  Logging message (includes configured column formatting)
		 */
		virtual bool
		LogMessage(gnsdk_uint16_t packageId, GnLogMessageType messageType, gnsdk_uint32_t errorCode, gnsdk_cstr_t message) = 0;
	};


	/**
	 * Logging Filters
	 */
	class GnLogFilters
	{
	public:
		GNWRAPPER_ANNOTATE

		GnLogFilters() : mFiltersMask(0){ }

		/** Include error logging messages */
		GnLogFilters&
		Clear(){mFiltersMask = 0; return *this; }

		/** Include error logging messages */
		GnLogFilters&
		Error(){mFiltersMask |= GNSDK_LOG_FILTER_ERROR; return *this; }

		/** Include warning logging messages */
		GnLogFilters&
		Warning(){mFiltersMask |= GNSDK_LOG_FILTER_WARNING; return *this; }

		/** Include informative logging messages */
		GnLogFilters&
		Info(){mFiltersMask |= GNSDK_LOG_FILTER_INFO; return *this; }

		/** Include debugging logging messages */
		GnLogFilters&
		Debug(){mFiltersMask |= GNSDK_LOG_FILTER_DEBUG; return *this; }

		/** Include all logging messages */
		GnLogFilters&
		All(){mFiltersMask |= GNSDK_LOG_LEVEL_ALL; return *this; }


	private:
		gnsdk_uint32_t mFiltersMask;

		friend class GnLog;
	};


	/**
	 * Enum specifying logging packages for the purpose of communicating
	 * those packages to the logging sub-system.
	 */
	enum GnLogPackageType 
	{
		kLogPackageAll = 1,
		kLogPackageAllGNSDK,

		kLogPackageManager,		
		kLogPackageMusicID,
		kLogPackageMusicIDFile,
		kLogPackageMusicIDStream,
		kLogPackageMusicIdMatch,
		kLogPackageVideoID,
		kLogPackageLink,
		kLogPackageDsp,
		kLogPackageAcr,
		kLogPackageEPG,
		kLogPackageSubmit,
		kLogPackageTaste,
		kLogPackageRhythm,
		kLogPackagePlaylist,
		kLogPackageStorageSqlite,
		kLogPackageStorageQNX,
		kLogPackageLookupLocal,
		kLogPackageLookupFPLocal,
		kLogPackageLookupLocalStream,
		kLogPackageEDBInstall,
		kLogPackageMoodGrid,
		kLogPackageCorrelates,
		kLogPackageInternal
	};


	/**
	 * Logging columns specifies what columns are written for each entry in the GNSDK log
	 */
	class GnLogColumns
	{
	public:
		GNWRAPPER_ANNOTATE

		GnLogColumns() : mOptionsMask(0){ }

		/**
		 * Clear options currently set
		 */
		void
		None(){mOptionsMask = 0; }

		/**
		 * Specify to include a time stamp for each entry of the format: Wed Jan 30 18:56:37 2008
		 */
		GnLogColumns&
		TimeStamp(){mOptionsMask |= GNSDK_LOG_OPTION_TIMESTAMP; return *this; }

		/**
		 * Specify to categorizes the log entries by headings such as ERROR, INFO, and so on.
		 */
		GnLogColumns&
		Category(){mOptionsMask |= GNSDK_LOG_OPTION_CATEGORY; return *this; }

		/**
		 * Specify to include the Package Name, or the Package ID if the name is unavailable.
		 */
		GnLogColumns&
		PackageName(){mOptionsMask |= GNSDK_LOG_OPTION_PACKAGE; return *this; }

		/**
		 * Specify to include the Thread ID.
		 */
		GnLogColumns&
		Thread(){mOptionsMask |= GNSDK_LOG_OPTION_THREAD; return *this; }

		/**
		 * Specify to include the source information
		 */
		GnLogColumns&
		SourceInfo(){mOptionsMask |= GNSDK_LOG_OPTION_SOURCEINFO; return *this; }

		/**
		 * Specify to include a trailing newline in the format: "\r\n"
		 */
		GnLogColumns&
		NewLine(){mOptionsMask |= GNSDK_LOG_OPTION_NEWLINE; return *this; }

		/**
		 * Specify to include all log formatting options.
		 */
		GnLogColumns&
		All(){mOptionsMask |= GNSDK_LOG_OPTION_ALL; return *this; }


	private:
		gnsdk_uint32_t mOptionsMask;

		friend class GnLog;
	};


	/**
	 *  Logging options specifies what options are applied to the GNSDK log
	 */
	class GnLogOptions
	{
	public:
		GNWRAPPER_ANNOTATE

		GnLogOptions() : mOptionsMask(0), mMaxSize(0), mArchive(GNSDK_FALSE){ }

		/**
		 * Specify true for the log to be written synchronously (no background thread).
		 * By default logs are written to asynchronously. No internal logging
		 * thread is created if all GnLog instances are specified for synchronous
		 * writing.
		 * @param bSyncWrite  Set true to enable synchronized writing, false for asynchrounous (default)
		 */
		GnLogOptions&
		Synchronous(bool bSyncWrite){bSyncWrite ? mOptionsMask |= GNSDK_LOG_OPTION_SYNCHRONOUS : mOptionsMask &= ~GNSDK_LOG_OPTION_SYNCHRONOUS; return *this; }

		/**
		 * Specify true to retain and rename old logs. 
		 * Default behavior is to delete old logs.
		 * @param bArchive  Set true to keep rolled log files, false to delete rolled logs (default)
		 */
		GnLogOptions&
		Archive(bool bArchive){mArchive = bArchive; return *this; }

		/**
		 * Specify that when archive is also specified the logs to archive (roll)
		 * at the start of each day (12:00 midnight). Archiving by the given size
		 * parameter will still occur normally as well.
		 */
		GnLogOptions&
		ArchiveDaily(){mOptionsMask |= GNSDK_LOG_OPTION_ARCHIVEDAILY; return *this; }

		/**
		 * Specify the maximum size of log before new log is created. Enter a value of zero (0) to
		 * always create new log on open
		 * @param maxSize  Set to maximum size log file should reach to be rolled. 
		 * Set to zero to always roll log on creation (default)
		 */
		GnLogOptions&
		MaxSize(gnsdk_uint64_t maxSize){mMaxSize = maxSize; return *this; }


	private:
		gnsdk_uint32_t mOptionsMask;
		gnsdk_uint64_t mMaxSize;
		bool           mArchive;

		friend class GnLog;
	};


	/**
	 * Configures and enables GNSDK logging including registering custom logging packages
	 * and writing your own logging message to the GNSDK log
	 */
	class GnLog
	{
	public:
		GNWRAPPER_ANNOTATE
		
		/**
		 * Instantiate a GNSDK logging instance
		 * @param logFilePath		[in] File path of the logging file
		 * @param pLoggingDelegate	[in] Optional delegate to receive logging messages
		 */
		GnLog(gnsdk_cstr_t logFilePath, IGnLogEvents* pLoggingDelegate = GNSDK_NULL);

		/**
		 * Instantiate a GNSDK logging instance
		 * <p><b>Remarks:</b></p>
		 * GnLog instances setup individual logs. Any number of logs can be
		 * started with any configurations. Messages that filter to multiple logs will
		 * be written to all applicable logs. 
		 * Logging instances are distinguished by the logFilePath. Creating GnLog instances
		 * with the same logFilePath as one already started will modify the configuration for 
		 * the existing log.
		 * Logging is not started until GnLog::Enable() is called.
		 * Logging continues until GnLog::Disable() is called. Destruction of GnLog instance
		 * does not terminate logging setup by that instance.
		 * @param logFilePath		[in] Path and name of the logging file
		 * @param filters			[in] Logging filters
		 * @param columns			[in] Logging columns
		 * @param options			[in] Logging options
		 * @param pLoggingDelegate	[in] Optional Delegate to receive logging messages
		 */
		GnLog(gnsdk_cstr_t         logFilePath,
		      const GnLogFilters&  filters,
		      const GnLogColumns&  columns,
		      const GnLogOptions&  options,
		      IGnLogEvents*        pLoggingDelegate = GNSDK_NULL
		      );

		virtual
		~GnLog();

		/**
		 * Set logger instance options
		 * @param options  Selection of logging options via GnLogOptions
		 */
		void
		Options(GnLogOptions options);


		/**
		 * Set logger instance filters
		 * @param filters  Selection of log message filters via GnLogFilters
		 */
		void
		Filters(GnLogFilters filters);

		/**
		 * Set logger instance columns
		 * @param columns  Selection of log column format via GnLogColumns
		 */
		void
		Columns(GnLogColumns columns);

		/**
		 * Enable logging for the given package with the current logging options and filters.
		 * Enable can be called multiple times to enable logging of multiple packages to the same log.
		 * <p><b>Remarks:</b></p>
		 * Changes to logging options and filters do not take affect until the logger is next enabled.
		 * @param package [in] GnLogPackage to enable for this log.
		 * @return This GnLog object to allow method chaining.
		 */
		GnLog&
		Enable(GnLogPackageType package) throw (GnError);

		/**
		 * Enable logging for the custom package id with the current logging options and filters.
		 * Applications can register a package id using the Register() member. This allows applications 
		 * to use GnLog to write their own messages to configured log files.
		 * Enable can be called multiple times to enable logging of multiple packages to the same log.
		 * <p><b>Remarks:</b></p>
		 * Changes to logging options and filters do not take affect until the logger is next enabled.
		 * @param package [in] GnLogPackage to enable for this log.
		 * @return This GnLog object to allow method chaining.
		 */
		GnLog&
		Enable(gnsdk_uint16_t customPackageId) throw (GnError);

		/**
		 * Disable logging for the given package for the current log.
		 * If no other packages are enabled for the log, the log will be closed
		 * @param package [in] GnLogPackage to disable for this log.
		 * @return This GnLog object to allow method chaining.
		 */
		GnLog&
		Disable(GnLogPackageType package) throw (GnError);

		/**
		 * Disable logging for the custom package id for the current log.
		 * If no other packages are enabled for the log, the log will be closed
		 * @param package [in] GnLogPackage to disable for this log.
		 * @return This GnLog object to allow method chaining.
		 */
		GnLog&
		Disable(gnsdk_uint16_t customPackageId) throw (GnError);

		/**
		 * Register an application with a unique packageid and package name 
		 * @param customPackageId		[in] Custom Package ID : must be unique and be within the custom package range.
		 * @param customPackageName     [in] Custom tag to identfiy each log message. e.g. "MYAPP" .
		 * @return This GnLog object to allow method chaining.
		 * <p><b>Remarks:</b></p>
		 * This function enables an application register a custom package Id and package Name for writing to the log
		 * system. 
		 */
		GnLog& 
		Register( gnsdk_uint16_t customPackageId, gnsdk_cstr_t customPackageName) throw (GnError);


		static const gnsdk_uint16_t kMinimumCustomPackageIdValue = GNSDKPKG_ID_APP_START;

		static const gnsdk_uint16_t kMaximumCustomPackageIdValue = GNSDKPKG_ID_APP_MAX;
		/**
		 * Write a message to the custom registered log 
		 * @param line              [in] Source line number of this call
		 * @param fileName          [in] Source file name of this call
		 * @param customPackageId   [in] Custom Package ID of application making call
		 * @param messageType       [in] Logging message type
		 * @param format            [in] Log message format
		 * <p><b>Remarks:</b></p>
		 * This function enables an application to write a logging message to the GNSDK logging
		 * system. If a logging events delegate is provided that handles the given package ID and enabled log filters,
		 * then this message is written to those log(s). The customer Package ID must be one previously registered by the
		 * application.
		 */
		static void
		Write( gnsdk_int32_t line, gnsdk_cstr_t fileName, gnsdk_uint16_t customPackageId, GnLogMessageType messageType, gnsdk_cstr_t format, ... );

		static void 
		vWrite(gnsdk_int32_t line, gnsdk_cstr_t fileName, gnsdk_uint16_t customPackageId, GnLogMessageType messageType, gnsdk_cstr_t format, va_list argptr);

	private:
		#define GN_LOGGER_FILEPATH_LENGTH   1024
		char mLogFilePath[GN_LOGGER_FILEPATH_LENGTH];

		IGnLogEvents* mLoggingDelegate;

		GnLogColumns  mLoggingColumns;
		GnLogOptions  mLoggingOptions;
		GnLogFilters  mLoggingFilters;

		DISALLOW_COPY_AND_ASSIGN(GnLog);
	};


} /* namespace gracenote */


#endif /* _GNSDK_LOG_HPP_ */

