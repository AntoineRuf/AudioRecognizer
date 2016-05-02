/** Public header file for Gracenote SDK C++ Wrapper
 *	gnsdk_lookup_localstream.hpp
 *
 *	Author:
 *	Copyright (c) 2014 Gracenote, Inc.
 *
 *	This software may not be used in any way or distributed without
 *	permission. All rights reserved.
 *
 *	Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_LOOKUP_LOCALSTREAM_HPP_
#define _GNSDK_LOOKUP_LOCALSTREAM_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"

namespace gracenote
{
	namespace lookup_localstream
	{
#if GNSDK_LOOKUP_LOCALSTREAM

		enum GnLocalStreamEngineType
		{
			kLocalStreamEngineInvalid = 0,

			kLocalStreamEngineMMap,
			kLocalStreamEngineInMemory
		};

		/**
		 * Provides services for local lookup of MusicID-Stream queries
		 *
		 * GnLookupLocalStream is a MusicID-Stream local lookup provider, providing a local
		 * database of MusicID-Stream tracks suitable for lookup via GnMusicIdStream or GnMusicId.
		 *
		 * The local database is a Gracenote storage; therefore a storage provider, such as GnStorageSqlite,
		 * must be enabled as a pre-requisite to successfully using this class.
		 *
		 * <b>Bundle Ingestion</b>
		 *
		 * The MusicID-Stream local database is constructed from "bundles" provided periodically by Gracenote.
		 * Your application must ingest the bundle, a process that adds the tracks from the bundle to the local
		 * database making them available for local recognition.
		 *
		 * To ingest a bundle create an instance of GnLookupLocalStreamIngest and write the bundle bytes
		 * as received when streaming the bundle from your online service.
		 *
		 * Multiple bundles can be ingested by the same application. If the same track exists in multiple
		 * ingested bundles it is added to the local database only once and only the most recent/up-to-date track
		 * information is written to the database.
		 *
		 * The process of ingestion can be lengthy. Some applications may wish to perform ingestion on a
		 * background thread to avoid stalling the main application thread.
		 *
		 * <b>Bundle Management</b>
		 *
		 * Bundles are regularly generated for multiple global regions and in multiple flavors being
		 * incremental (only differences from previous bundle for that region) or full (all records for the
		 * region).
		 *
		 * Incremental bundles are intended for applications that have installed the previous bundles in the
		 * sequence. If your application skips a bundle it should clear it's MusicID-Stream local database
		 * and install the full bundle.
		 *
		 * Your bundle management system must provide the means to regularly distribute the correct bundle to
		 * your application, ensuring it provides the bundle for the correct region and, as appropriate, the
		 * full or incremental bundle.
		 *
		 * A typical bundle management system is:<br>
		 * - retrieve bundles as produced by Gracenote (manual step)<br>
		 * - place bundle in online location where application can fetch it<br>
		 * - application downloads and ingests the bundle
		 *
		 * Note: Bundles should be retrieved from an online source. Gracenote recommends when your application
		 * is installed/initialized it download and ingest the latest bundle rather than ship with a bundle as
		 * part of the application binaries.
		 */
		class GnLookupLocalStream
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Enable Lookup local Stream provider.
			 * @return Storage provider instance
			 */
			static GnLookupLocalStream&
			Enable() throw (GnError);
			/**
			 *  Retrieves GnLookupLocalStream SDK version string.
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 *  string is a constant. Do not attempt to modify or delete.
			 *  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
			 *  Major: New functionality
			 *  Minor: New or changed features
			 *  Improvement: Improvements and fixes
			 *  Build: Internal build number
			 */
			static gnsdk_cstr_t
			Version();

			/**
			 *  Retrieves the GnLookupLocalStream SDK's build date string.
			 *  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 * string is a constant. Do not attempt to modify or delete.
			 *  Example build date string: 2008-02-12 00:41 UTC
			 */
			static gnsdk_cstr_t
			BuildDate();

			/**
			 *  Sets a folder location for GNSDK LookupLocalStream
			 *  @param folderPath	[in] Relative path name for storage
			 * <p><b>Remarks:</b></p>
			 *  This API overrides the (default or explicit) folder location of GNSDK SQLite storage - for this database.
			 */
			void
			StorageLocation(gnsdk_cstr_t location) throw (GnError);

			void
			EngineType(GnLocalStreamEngineType engineType) throw (GnError);

			GnLocalStreamEngineType
			EngineType(void) throw (GnError);

			/**
			 * Clear all tracks from the MusicID-Stream local database storage file
			 */
			void
			StorageClear() throw (GnError);

			/**
			 * Remove an item from the MusicID-Stream local database identified by
			 * Bundle Item ID.
			 * @param	bundleItemId	[in] Bundle Item ID
			 */
			void
			StorageRemove(gnsdk_cstr_t bundleItemId) throw (GnError);


		private:
			GnLookupLocalStream() throw (GnError) { };
		};


		enum GnLookupLocalStreamIngestStatus
		{
			kIngestStatusInvalid = 0,
			kIngestStatusItemBegin,
			kIngestStatusItemAdd,
			kIngestStatusItemDelete

		};

		class IGnLookupLocalStreamIngestEvents
		{
		public:

			virtual ~IGnLookupLocalStreamIngestEvents() {};

			virtual void
			StatusEvent( GnLookupLocalStreamIngestStatus status, gnsdk_cstr_t bundleId, IGnCancellable& canceller) = 0;
		};


		class GnLookupLocalStreamIngest : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Constructor for creating a GnLookupLocalStreamIngest Object
			 *  @param pEventDelegate           [in] Delegate to receive events .
			 *  @param callbackData             [in] Optional user data that will be sent to the Delegate
			 */
			GnLookupLocalStreamIngest( IGnLookupLocalStreamIngestEvents* pEventDelegate ) throw (GnError);

			/**
			 * Write to the ingestion process . This can be called multiple times to ensure that data is written as and when it is available.
			 *  @param data             [in] data to ingest
			 *  @param dataLength       [in] size of data being written
			 */
			void
			Write(gnsdk_byte_t* bundleData, gnsdk_size_t dataSize) throw (GnError);

			/**
			 * Flushes the memory cache to the file storage and commits the changes. This call will result in IO .
			 * Use this method to ensure that everything written is commited to the file system.
			 * Note: This is an optional call as internally data is flushed when it exceed the cache size and when the object goes out of scope..
			 */
			void
			Flush() throw (GnError);


			/*-----------------------------------------------------------------------------
			 *  EventHandler
			 */
			IGnLookupLocalStreamIngestEvents*
			EventHandler() { return eventhandler_; }


		private:
			DISALLOW_COPY_AND_ASSIGN(GnLookupLocalStreamIngest);
			IGnLookupLocalStreamIngestEvents* eventhandler_;

		};


#endif /* GNSDK_LOOKUP_LOCALSTREAM */

	} /* namespace lookup_localstream */
}     /* namespace GracenoteSDK */

#endif /* _GNSDK_LOOKUP_LOCALSTREAM_HPP_ */

