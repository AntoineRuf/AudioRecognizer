/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_STORAGE_SQLITE_HPP_
#define _GNSDK_STORAGE_SQLITE_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"


namespace gracenote
{
	namespace storage_sqlite
	{
#if GNSDK_STORAGE_SQLITE

		/**
		 * GNSDK SQLite storage provider
		 */
		class GnStorageSqlite
		{
			static GnStorageSqlite&
			_Enable() throw (GnError);

		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Sets the path to an external shared SQLite library to use instead of out internal copy
			 * <p><b>Remarks:</b></p>
			 * If used, this must be called before <code>Enable()</code>
			 */
			static void
			UseExternalLibrary(gnsdk_cstr_t sqlite3_filepath) throw (GnError);

			/**
			 * Enable SQLite storage provider
			 * @return Storage provider instance
			 */
			static GnStorageSqlite&
			Enable() throw (GnError);

			/**
			 *  Retrieves the version string of the Storage SQLite library.
			 */
			static gnsdk_cstr_t Version();

			/**
			 *  Retrieves the build date string of the Storage SQLite library.
			 */
			static gnsdk_cstr_t BuildDate();

			/**
			 *  Retrieves the version string of the internal SQLite database engine.
			 */
			static gnsdk_cstr_t SqliteVersion();

			/**
			 *  Sets a folder location for GNSDK SQLite storage
			 *  @param folderPath	[in] Relative path name for storage
			 * <p><b>Remarks:</b></p>
			 *  This API sets the folder location for ALL GNSDK SQLite storage - to set specific cache or database
			 *  locations use StorageLocation methods of the appropriate class.
			 */
			void
			StorageLocation(gnsdk_cstr_t folderPath) throw (GnError);

			/**
			 * Get storage location folder for GNSDK SQLite storage
			 */
			gnsdk_cstr_t
			StorageLocation() throw (GnError);

			/**
			 * Get the temporary storage location folder for GNSDK SQLite storage
			 */
			gnsdk_cstr_t
			TemporaryStorageLocation() throw (GnError);

			/**
			 *  Sets a temporary folder location for GNSDK SQLite storage
			 *  @param folderPath	[in] Relative path name for storage
			 * <p><b>Remarks:</b></p>
			 *  This API sets the temporary folder location for ALL GNSDK SQLite storage.
			 */
			void
			TemporaryStorageLocation(gnsdk_cstr_t folderPath) throw (GnError);

			/**
			 * Sets the maximum size the GNSDK cache can grow to; for example '100' for 100 Kb or '1024' for 1
			 *  MB. This limit applies to each cache that is created.
			 *
			 *  The value passed for this option is the maximum number of Kilobytes that the cache files can grow
			 *  to. For example, '100' sets the maximum to 100 KB, and '1024' sets the maximum to 1 MB.
			 *
			 *  If the cache files' current size already exceeds the maximum when this option is set, then the
			 *  set maximum is not applied.
			 *
			 *  When the maximum size is reached, new cache entries are not written to the database.
			 *  Additionally, a maintenance thread is run that attempts to clean up expired records from the
			 *  database and create space for new records.
			 *
			 *  If this option is not set the cache files default to having no maximum size.
             *
             *  @param maxCacheSize	[in] Maximum cache file size
			 */
			void
			MaximumCacheFileSize(gnsdk_uint32_t maxCacheSize) throw (GnError);

			/**
			 * Get maximum cache file size
			 */
			gnsdk_uint32_t
			MaximumCacheFileSize() throw (GnError);

			/**
			 *  Sets the maximum amount of memory SQLite can use to buffer cache data.
			 *
			 *  The value passed for this option is the maximum number of Kilobytes of memory that can be used.
			 *  For example, '100' sets the maximum to 100 KB, and '1024' sets the maximum to 1 MB.
			 *
             *  @param maxMemSize [in]  Maximum cache memory size
			 */
			void
			MaximumCacheMemory(gnsdk_uint32_t maxMemSize) throw (GnError);

			/**
			 * Get maximum cache memory
			 */
			gnsdk_uint32_t
			MaximumCacheMemory() throw (GnError);

			/**
			 *  Sets the method that SQLite uses to write to the cache files.
			 *
			 *  This option is available for SQLite performance tuning. Valid values for this option are:
             *  @param mode [in]:
             *  <ul>
			 *  <li>OFF (default setting): No synchronous writing; the quickest but least safe method.</li>
			 *  <li>NORMAL: Synchronous writing only at critical times; the generally quick and safe method.</li>
			 *  <li>FULL: Always synchronous writing; the slowest and safest method.</li>
			 *  </ul>
			 *
			 *  If the threat of losing a cache file due to hardware failure is high, then set this option in
			 *  your application to NORMAL or FULL.
             */
			void
			SynchronousMode(gnsdk_cstr_t mode) throw (GnError);

			/**
			 * Get synchronous mode setting
			 */
			gnsdk_cstr_t
			SynchronousMode() throw (GnError);

			/**
			 *  Sets how the SQLite journal file is managed for database transactions.
			 *
			 *  This option is available for SQLite performance tuning. Valid values for this option are:
             *  @param mode [in]:
             *  <ul>
			 *  <li>DELETE: Journal file is deleted after each transaction.</li>
			 *  <li>TRUNCATE: Journal file is truncated (but not deleted) after each transaction.</li>
			 *  <li>PERSIST: Journal file remains after each transaction.</li>
			 *  <li>MEMORY (default setting): Journal file is only stored in memory for each transaction.</li>
			 *  <li>OFF: No journaling is performed.</li>
			 *  </ul>
			 **/
			void
			JournalMode(gnsdk_cstr_t mode) throw (GnError);

			/**
			 * Get journalling mode setting
			 */
			gnsdk_cstr_t
			JournalMode() throw (GnError);
			
		private:
			GnStorageSqlite() {};

			DISALLOW_COPY_AND_ASSIGN(GnStorageSqlite);
		};

#endif /* GNSDK_STORAGE_SQLITE */
	} // namespace storage_sqlite

}     // namespace gracenote

#endif // _GNSDK_STORAGE_SQLITE_HPP_

