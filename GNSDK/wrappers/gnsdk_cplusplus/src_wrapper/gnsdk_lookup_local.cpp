/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_lookup_local.cpp
 *
 * Implementation of C++ wrapper for GNSDK Lookup FP Local
 *
 */
#include "gnsdk_manager.hpp"

#if GNSDK_LOOKUP_LOCAL

#include "gnsdk_lookup_local.hpp"

using namespace gracenote;
using namespace gracenote::lookup_local;


static gnsdk_cstr_t
_convertLocalStorageNameCppC(GnLocalStorageName storageName) throw (GnError)
{
	gnsdk_cstr_t  storage_name = GNSDK_NULL;

	switch (storageName)
	{
	case kLocalStorageContent:
		storage_name = GNSDK_LOOKUP_LOCAL_STORAGE_CONTENT;
		break;

	case kLocalStorageMetadata:
		storage_name = GNSDK_LOOKUP_LOCAL_STORAGE_METADATA;
		break;

	case kLocalStorageTOCIndex:
		storage_name = GNSDK_LOOKUP_LOCAL_STORAGE_TOCINDEX;
		break;

	case kLocalStorageTextIndex:
		storage_name = GNSDK_LOOKUP_LOCAL_STORAGE_TEXTINDEX;
		break;

	case kLocalStorageAll:
		storage_name = GNSDK_LOOKUP_LOCAL_STORAGE_ALL;
		break;

	default:
		// if unknown leave return value as null
		break;
	}

	return storage_name;
}


static gnsdk_cstr_t
_convertLocalStorageInfoCppC(GnLocalStorageInfo storageInfo) throw (GnError)
{
	gnsdk_cstr_t  storage_info = GNSDK_NULL;

	switch (storageInfo)
	{
	case kLocalStorageInfoVersion:
		storage_info = GNSDK_LOOKUP_LOCAL_STORAGE_GDB_VERSION;
		break;

	case kLocalStorageInfoImageSize:
		storage_info = GNSDK_LOOKUP_LOCAL_STORAGE_IMAGE_SIZE;
		break;

	case kLocalStorageInfoInvalid:
		break;
	}

	return storage_info;
}

GnLookupLocal&
GnLookupLocal::Enable() throw (GnError)
{
	static GnLookupLocal s_lookup_local;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_LOOKUP_LOCAL);
	return s_lookup_local;
}

gnsdk_cstr_t
GnLookupLocal::Version()
{
	return gnsdk_lookup_local_get_version();
}

gnsdk_cstr_t
GnLookupLocal::BuildDate()
{
	return gnsdk_lookup_local_get_build_date();
}

void
GnLookupLocal::StorageCompact(GnLocalStorageName storageName) throw (GnError)
{
	gnsdk_cstr_t  storage_name;
	gnsdk_error_t error;

	storage_name = _convertLocalStorageNameCppC(storageName);

	error = gnsdk_lookup_local_storage_compact(storage_name);
	if (error) { throw GnError(); }
}

void
GnLookupLocal::StorageLocation(GnLocalStorageName storageName, gnsdk_cstr_t storageLocation) throw (GnError)
{
	gnsdk_cstr_t  storage_name;
	gnsdk_error_t error;

	storage_name = _convertLocalStorageNameCppC(storageName);

	error = gnsdk_lookup_local_storage_location_set(storage_name, storageLocation);
	if (error) { throw GnError(); }
}

void
GnLookupLocal::StorageValidate(GnLocalStorageName storageName) throw (GnError)
{
	gnsdk_error_info_t	error_info;
	gnsdk_cstr_t		storage_name;
	gnsdk_error_t		error;

	storage_name = _convertLocalStorageNameCppC(storageName);

	error = gnsdk_lookup_local_storage_validate(storage_name, &error_info);
	if (error) { throw GnError(); }
}

gnsdk_cstr_t
GnLookupLocal::StorageInfo(GnLocalStorageName storageName, GnLocalStorageInfo storageInfo, gnsdk_uint32_t ordinal) throw (GnError)
{
	gnsdk_cstr_t	info = GNSDK_NULL;
	gnsdk_cstr_t	storage_name;
	gnsdk_cstr_t	storage_info;
	gnsdk_error_t	error;

	storage_name = _convertLocalStorageNameCppC(storageName);
	storage_info = _convertLocalStorageInfoCppC(storageInfo);

	error = gnsdk_lookup_local_storage_info_get(storage_name, storage_info, ordinal, &info);
	if (error) { throw GnError(); }

	return info;
}

gnsdk_uint32_t
GnLookupLocal::StorageInfoCount(GnLocalStorageName storageName, GnLocalStorageInfo storageInfo) throw (GnError)
{
	gnsdk_cstr_t	storage_info;
	gnsdk_cstr_t	storage_name;
	gnsdk_uint32_t	count = 0;
	gnsdk_error_t	error;

	storage_name = _convertLocalStorageNameCppC(storageName);
	storage_info = _convertLocalStorageInfoCppC(storageInfo);

	error = gnsdk_lookup_local_storage_info_count(storage_name, storage_info, &count);
	if (error) { throw GnError(); }

	return count;
}

#endif /* GNSDK_LOOKUP_LOCAL */
