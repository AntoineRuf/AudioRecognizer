/*
 * Copyright (c) 2014 Gracenote.

 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_lookup_localstream.cpp
 *
 * Implementation of C++ wrapper for GNSDK Lookup FP Local
 *
 */
#include "gnsdk_manager.hpp"

#if GNSDK_LOOKUP_LOCALSTREAM

#include "gnsdk_lookup_localstream.hpp"

using namespace gracenote;
using namespace gracenote::lookup_localstream;


/*-----------------------------------------------------------------------------
 *  _callback_status
 */
static gnsdk_void_t GNSDK_CALLBACK_API
_callback_status(void* callback_data, gnsdk_lookup_localstream_status_t status, gnsdk_cstr_t bundle_id, gnsdk_bool_t* p_abort)
{
	GnLookupLocalStreamIngest* ingestor = (GnLookupLocalStreamIngest*) callback_data;
	gn_canceller               canceller;
	if (ingestor->EventHandler())
	{
		ingestor->EventHandler()->StatusEvent((GnLookupLocalStreamIngestStatus) status, bundle_id, canceller);
	}
	if (canceller.IsCancelled())
	{
		*p_abort = true;
	}
}


/*-----------------------------------------------------------------------------
 *  Version
 */
gnsdk_cstr_t
GnLookupLocalStream::Version()
{
	return gnsdk_lookup_localstream_get_version();
}


/*-----------------------------------------------------------------------------
 *  BuildDate
 */
gnsdk_cstr_t
GnLookupLocalStream::BuildDate()
{
	return gnsdk_lookup_localstream_get_build_date();
}


/*-----------------------------------------------------------------------------
 *  Enable
 */
GnLookupLocalStream&
GnLookupLocalStream::Enable() throw (GnError)
{
	static GnLookupLocalStream s_lookup_localstream;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_LOOKUP_LOCALSTREAM);
	return s_lookup_localstream;
}


/*-----------------------------------------------------------------------------
 *  StorageLocation
 */
void
GnLookupLocalStream::StorageLocation(gnsdk_cstr_t location) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_lookup_localstream_storage_location_set(location);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  EngineType
 */
void
GnLookupLocalStream::EngineType(GnLocalStreamEngineType engineType) throw (GnError)
{
	gnsdk_cstr_t option_value = GNSDK_NULL;
	gnsdk_error_t error;

	switch (engineType)
	{
	case kLocalStreamEngineMMap:
		option_value = GNSDK_LOOKUP_LOCALSTREAM_ENGINE_MMAP;
		break;

	case kLocalStreamEngineInMemory:
		option_value = GNSDK_LOOKUP_LOCALSTREAM_ENGINE_INMEMORY;
		break;

	case kLocalStreamEngineInvalid:
		option_value = GNSDK_NULL;
		break;
	}

	error = gnsdk_lookup_localstream_option_set(GNSDK_LOOKUP_LOCALSTREAM_OPTION_ENGINE_TYPE, option_value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  EngineType
 */
GnLocalStreamEngineType
GnLookupLocalStream::EngineType(void) throw (GnError)
{
	gnsdk_cstr_t option_value = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_lookup_localstream_option_get(GNSDK_LOOKUP_LOCALSTREAM_OPTION_ENGINE_TYPE, &option_value);
	if (error) { throw GnError(); }

	if (gnstd::gn_strcmp(option_value, GNSDK_LOOKUP_LOCALSTREAM_ENGINE_INMEMORY))
		return kLocalStreamEngineInMemory;
	return kLocalStreamEngineMMap;
}


/*-----------------------------------------------------------------------------
 *  StorageClear
 */
void
GnLookupLocalStream::StorageClear() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_lookup_localstream_storage_clear();
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageRemove
 */
void
GnLookupLocalStream::StorageRemove(gnsdk_cstr_t bundleId) throw (GnError)
{
	gnsdk_error_t error = gnsdk_lookup_localstream_storage_remove(bundleId);
	if (error) { throw GnError(); }
}


/* ***************************************************************************************************************************** */
/*  GnLookupLocalStreamIngest */
/* ***************************************************************************************************************************** */
GnLookupLocalStreamIngest::GnLookupLocalStreamIngest( IGnLookupLocalStreamIngestEvents* pEventDelegate) throw (GnError)
	: eventhandler_(pEventDelegate)
{
	_gnsdk_internal::module_initialize(GNSDK_MODULE_LOOKUP_LOCALSTREAM);

	gnsdk_lookup_localstream_ingest_handle_t handle = GNSDK_NULL;

	gnsdk_error_t error = gnsdk_lookup_localstream_ingest_create(_callback_status, this, &handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(handle);
}


/*-----------------------------------------------------------------------------
 *  Write
 */
void
GnLookupLocalStreamIngest::Write(gnsdk_byte_t* bundleData, gnsdk_size_t dataLength) throw (GnError)
{
	gnsdk_error_t error = gnsdk_lookup_localstream_ingest_write( get<gnsdk_lookup_localstream_ingest_handle_t>(), (void*)bundleData, dataLength);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Flush
 */
void
GnLookupLocalStreamIngest::Flush() throw (GnError)
{
	gnsdk_error_t error = gnsdk_lookup_localstream_ingest_flush(get<gnsdk_lookup_localstream_ingest_handle_t>());
	if (error) { throw GnError(); }
}


#endif /*GNSDK_LOOKUP_LOCALSTREAM*/

