/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_MANAGER_HPP_
#define _GNSDK_MANAGER_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4290 ) /* disable "warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)" */
#endif

#include "gnsdk_base.hpp"

#define GNSDK_MODULE_MANAGER           		0x01
#define GNSDK_MODULE_MUSICID           		0x02
#define GNSDK_MODULE_MUSICIDFILE       		0x04
#define GNSDK_MODULE_MUSICIDMATCH      		0x08
#define GNSDK_MODULE_MUSICIDSTREAM     		0x10
#define GNSDK_MODULE_ACR               		0x20
#define GNSDK_MODULE_EPG               		0x40
#define GNSDK_MODULE_DSP               		0x80
#define GNSDK_MODULE_LINK              		0x100
#define GNSDK_MODULE_VIDEO             		0x200
#define GNSDK_MODULE_PLAYLIST          		0x400
#define GNSDK_MODULE_MOODGRID          		0x800
#define GNSDK_MODULE_CORRELATES        		0x1000
#define GNSDK_MODULE_TASTE					0x2000
#define GNSDK_MODULE_TASTEPROFILE      		0x4000
#define GNSDK_MODULE_SUBMIT            		0x8000
#define GNSDK_MODULE_LOOKUP_LOCAL      		0x10000
#define GNSDK_MODULE_LOOKUP_FPLOCAL    		0x20000
#define GNSDK_MODULE_LOOKUP_LOCALSTREAM		0x40000
#define GNSDK_MODULE_STORAGE_SQLITE    		0x80000
#define GNSDK_MODULE_STORAGE_QNX			0x100000
#define GNSDK_MODULE_RHYTHM           		0x200000

namespace gracenote
{
	/**
	 * GNSDK persistent store configuration and maintenance operations
	 */
	class GnStoreOps
	{
	public:
		/**
		 *  Specify the location of the persistent store.
		 *
		 *  If location is not specified using this method the location set for the initialized storage SDK will be used.
		 *  For example, if the SQLite Storage SDK has been initialized, any path set using
		 *  <code>GnStorageSqlite.StorageLocation(..)</code> will be used.
		 *
		 *  The storage location must be a valid relative or absolute path to an existing folder that
		 *  has the necessary write permissions.
		 *
		 *  <p><b>Important:</b></p>
		 *  For Windows CE an absolute path must be used.
		 *  @param location [in] response cache location
		 */
		void
		Location(gnsdk_cstr_t location) throw (GnError);

		/**
		 *  Clears all records from the persistent store.
		 *
		 *  When the <code>bAsync</code> is set to true the function immediately
		 *  returns and the flush is performed in the background and on a separate thread.
		 *
		 *  Performance
		 *
		 *  If <code>bAsync</code> is true this API spawns a thread to perform the operation. This thread runs at the
		 *  lowest priority to minimize the impact on other running queries or operations of the SDK.
		 *
		 *  This function can cause performance issues due to creating a large amount of disk I/O.
		 *
		 *  This operation can be performed on different storages at the same time, but note that performing
		 *  multiple simultaneous calls will potentially further degrade performance.
		 *
		 *  @param bAsync [in] if true perform an asynchronous cache flush in the background on a separate thread
		 */
		void
		Flush(bool bAsync) throw (GnError);

		/**
		 *  Attempts to compact the persistent store and minimize the amount of space required.
		 *
		 *  When the <code>bAsync</code> is set to true the function immediately
		 *  returns and the compact is performed in the background and on a separate thread.
		 *
		 *  Performance
		 *
		 *  If <code>bAsync</code> is true this API spawns a thread to perform the operation. This thread runs at the
		 *  lowest priority to minimize the impact on other running queries or operations of the SDK.
		 *
		 *  This method can cause performance issues due to creating a large amount of disk I/O.
		 *
		 *  This operation can be performed on different storages at the same time, but note that performing
		 *  multiple simultaneous calls will potentially further degrade performance.
		 *
		 *  @param bAsync [in] if true perform an asynchronous cache compact in the background on a separate thread
		 */
		void
		Compact(bool bAsync) throw (GnError);

		/**
		 *  Searches the existing local store and removes any records that are expired or unneeded.
		 *
		 *  Operation
		 *
		 *  This API first decides if maintenance is required; this is determined by tracking when the next
		 *  record expiration is needed.
		 *
		 *  Maintenance is always run the first time this API is called; any subsequent calls only perform
		 *  maintenance if this is required. Consequently, calling this API multiple times does not result in
		 *  excessive maintenance.
		 *
		 *  Performance
		 *
		 *  If <code>bAsync</code> is true and if maintenance is necessary, this API spawns a thread to perform the clean-up.
		 *  This thread runs at the lowest priority to minimize the impact on other running queries or operations of the SDK.
		 *
		 *  This function can cause performance issues due to creating a large amount of disk I/O.
		 *
		 *  This operation can be performed on different storages at the same time, but note that performing
		 *  multiple simultaneous calls will potentially further degrade performance.
		 *
		 *  Expired Records
		 *
		 *  Expired records are those older than the maximum allowable, even if the record has been recently
		 *  read. Old but actively read records are removed because Gracenote Service may have an updated
		 *  matching record.
		 *
		 *  The maximum allowable age of a record varies by query type and is managed internally by
		 *  Gracenote. Applications can use GnUser option to adjust the age at which
		 *  records are expired.
		 *
		 *  @param bAsync [in] if true perform an asynchronous cache clean-up maintenance in the background on a separate thread
		 *
		 */
		void
		Cleanup(bool bAsync) throw (GnError);

		virtual
		~GnStoreOps() {};

	private:
		GnStoreOps(gnsdk_cstr_t cacheType) : cachetype_(cacheType) {};
		DISALLOW_COPY_AND_ASSIGN(GnStoreOps);
		gnsdk_cstr_t	cachetype_;

		friend class GnManager;
	};

	/**
	 * Provides core functionality necessary to all Gracenote objects. This class must
	 * be instantiated prior to any other Gracenote objects.
	 */
	class GnManager
	{
	public:
		GNWRAPPER_ANNOTATE

		/**
		 * Initializes GNSDK. You must initialize the GNSDK prior to instantiating any other GNSDK objects.
		 * Valid license data must be provided. Gracenote Global Services and Support team provides a license with the SDK.
		 * @param license			[in] license data
		 * @param licenseInputMode	[in] how the license data is being provided
		 */
		GnManager(gnsdk_cstr_t license, GnLicenseInputMode licenseInputMode) throw (GnError);

		virtual
		~GnManager() throw (GnError);


		/**
		 * Retrieves the GNSDK version string.
		 * This API can be called at any time after GnManager instance is constructed successfully. The returned
		 * string is a constant. Do not attempt to modify or delete.
		 * Example: 1.2.3.123 (Major.Minor.Improvement.Build)
		 * Major: New functionality
		 * Minor: New or changed features
		 * Improvement: Improvements and fixes
		 */
		static gnsdk_cstr_t
		Version();


		/**
		 * Retrieves the product version string.
		 * This API can be called at any time after GnManager instance is constructed successfully. The returned
		 * string is a constant. Do not attempt to modify or delete.
		 * Example: 1.2.3.123 (Major.Minor.Improvement.Build)
		 * Major: New functionality
		 * Minor: New or changed features
		 * Improvement: Improvements and fixes
		 * Build: Internal build number
		 */
		static gnsdk_cstr_t
		ProductVersion();


		/**
		 * Retrieves the GNSDK's build date string.
		 * This API can be called at any time after GnManager instance is constructed successfully. The returned
		 * string is a constant. Do not attempt to modify or delete.
		 * Example: 2008-02-12 00:41 UTC
		 */
		static gnsdk_cstr_t
		BuildDate();


		static gnsdk_cstr_t
		GlobalIdMagic();


		/**
		 * Creates a new Serialized User and also increments the user's Client ID user count with Gracenote Service.
		 * Use this constructor to create a new user; when successful, this call registers a new user for
		 * a specified client in Gracenote Service. Once the new user is registered and the user count
		 * incremented in Gracenote Service, the count cannot be reduced, nor can the same user be
		 * again retrieved.
		 * Newly registered user handles must be serialized and stored locally for that user to be used
		 * again for future queries; failing to do this quickly depletes the client's allotted user quota
		 * within the Gracenote Service.
		 * @param registerMode  		[in] register as online or local only user
		 * @param clientId     			[in] client ID that initiates requests with this handle; value provided by
		 *                      		Gracenote
		 * @param clientTag    			[in] client ID tag value that matches client ID; value provided by Gracenote
		 * @param applicationVersion  	[in] client application version; numeric value provided by application, and
		 *                      		this value is required
		 */
		GnString
		UserRegister(GnUserRegisterMode registerMode, gnsdk_cstr_t clientId, gnsdk_cstr_t clientTag, gnsdk_cstr_t applicationVersion) throw (GnError);

		/**
		 * Get query cache storage operations instance
		 */
		GnStoreOps&
		QueryCacheStore();

		/**
		 * Get content cache storage operations instance
		 */
		GnStoreOps&
		ContentCacheStore();

		/**
		 * Get locales storage operations instance
		 */
		GnStoreOps&
		LocalesStore();


		/**
		 * Provide a delegate to receive system events
		 * @param pEventHandler		[in] event handler delegate
		 */
		void
		SystemEventHandler(IGnSystemEvents* pEventHandler);

		void
		SystemMemoryEvent(gnsdk_size_t memoryWarnSize);
		gnsdk_size_t
		SystemMemoryCurrent();
		gnsdk_size_t
		SystemMemoryHighWater(gnsdk_bool_t bResetHighWater);

		void
		TestGracenoteConnection(const GnUser& user) throw (GnError);

		/**
		 * Get the system event handler if previously provided
		 * @return Event handler
		 */
		IGnSystemEvents*
		EventHandler() const { return eventhandler_; }

	private:
		IGnSystemEvents*      			eventhandler_;
		GnStoreOps						localestore_;
		GnStoreOps						querycachestore_;
		GnStoreOps						contentcachestore_;
		/* disallow assignment operator */
		DISALLOW_COPY_AND_ASSIGN(GnManager);
	};

	/* Used internally, do not call */
	struct _gnsdk_internal 
	{
		static void	module_initialize(gnsdk_uint32_t module_id) throw (GnError);
		static bool	manager_initialized();
		static void	manager_addref();
		static void	manager_release();
	};

} /* namespace gracenote */


#endif /* _GNSDK_MANAGER_HPP_ */

