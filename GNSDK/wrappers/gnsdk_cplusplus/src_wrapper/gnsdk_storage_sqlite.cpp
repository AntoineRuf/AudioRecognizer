/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_storage_sqlite.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk_manager.hpp"

#if GNSDK_STORAGE_SQLITE

#include "gnsdk_storage_sqlite.hpp"

using namespace gracenote;
using namespace gracenote::storage_sqlite;

void
GnStorageSqlite::UseExternalLibrary(gnsdk_cstr_t sqlite3_filepath) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_storage_sqlite_use_external_library(sqlite3_filepath);
	if (error) { throw GnError(); }
}

GnStorageSqlite&
GnStorageSqlite::Enable() throw (GnError)
{
	static GnStorageSqlite	s_storage_sqlite;
	_gnsdk_internal::module_initialize(GNSDK_MODULE_STORAGE_SQLITE);
	return s_storage_sqlite;
}

gnsdk_cstr_t
GnStorageSqlite::Version()
{
	return gnsdk_storage_sqlite_get_version();
}

gnsdk_cstr_t
GnStorageSqlite::BuildDate()
{
	return gnsdk_storage_sqlite_get_build_date();
}

gnsdk_cstr_t
GnStorageSqlite::SqliteVersion()
{
	return gnsdk_storage_sqlite_get_sqlite_version();
}

void
GnStorageSqlite::StorageLocation(gnsdk_cstr_t folderPath) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_storage_sqlite_option_set(GNSDK_STORAGE_SQLITE_OPTION_STORAGE_FOLDER, folderPath);
	if (error) { throw GnError(); }
}

gnsdk_cstr_t
GnStorageSqlite::StorageLocation() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  storageFolder = GNSDK_NULL;

	error = gnsdk_storage_sqlite_option_get(GNSDK_STORAGE_SQLITE_OPTION_STORAGE_FOLDER, &storageFolder);
	if (error) { throw GnError(); }

	return storageFolder;
}

void
GnStorageSqlite::TemporaryStorageLocation(gnsdk_cstr_t folderPath) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_storage_sqlite_option_set(GNSDK_STORAGE_SQLITE_OPTION_STORAGE_TEMPORARY_FOLDER, folderPath);
	if (error) { throw GnError(); }
}

gnsdk_cstr_t
GnStorageSqlite::TemporaryStorageLocation() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  storageFolder = GNSDK_NULL;

	error = gnsdk_storage_sqlite_option_get(GNSDK_STORAGE_SQLITE_OPTION_STORAGE_TEMPORARY_FOLDER, &storageFolder);
	if (error) { throw GnError(); }

	return storageFolder;
}

void
GnStorageSqlite::MaximumCacheFileSize(gnsdk_uint32_t maxCacheSize) throw (GnError)
{
	char          buffer[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buffer, sizeof(buffer), maxCacheSize);
	error = gnsdk_storage_sqlite_option_set(GNSDK_STORAGE_SQLITE_OPTION_CACHE_FILESIZE, buffer);
	if (error) { throw GnError(); }
}

gnsdk_uint32_t
GnStorageSqlite::MaximumCacheFileSize() throw (GnError)
{
	gnsdk_cstr_t  sz_value = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_storage_sqlite_option_get(GNSDK_STORAGE_SQLITE_OPTION_CACHE_FILESIZE, &sz_value);
	if (error) { throw GnError(); }

	return gnstd::gn_atoi(sz_value);
}

void
GnStorageSqlite::MaximumCacheMemory(gnsdk_uint32_t maxMemSize) throw (GnError)
{
	char          buffer[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buffer, sizeof(buffer), maxMemSize);
	error = gnsdk_storage_sqlite_option_set(GNSDK_STORAGE_SQLITE_OPTION_CACHE_MEMSIZE, buffer);
	if (error) { throw GnError(); }
}

gnsdk_uint32_t
GnStorageSqlite::MaximumCacheMemory() throw (GnError)
{
	gnsdk_cstr_t  sz_value = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_storage_sqlite_option_get(GNSDK_STORAGE_SQLITE_OPTION_CACHE_MEMSIZE, &sz_value);
	if (error) { throw GnError(); }

	return gnstd::gn_atoi(sz_value);
}

void
GnStorageSqlite::SynchronousMode(gnsdk_cstr_t option) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_storage_sqlite_option_set(GNSDK_STORAGE_SQLITE_OPTION_SYNCHRONOUS, option);
	if (error) { throw GnError(); }
}

gnsdk_cstr_t
GnStorageSqlite::SynchronousMode() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  syncOption = GNSDK_NULL;

	error = gnsdk_storage_sqlite_option_get(GNSDK_STORAGE_SQLITE_OPTION_SYNCHRONOUS, &syncOption);
	if (error) { throw GnError(); }

	return syncOption;
}

void
GnStorageSqlite::JournalMode(gnsdk_cstr_t mode) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_storage_sqlite_option_set(GNSDK_STORAGE_SQLITE_OPTION_JOURNAL_MODE, mode);
	if (error) { throw GnError(); }
}

gnsdk_cstr_t
GnStorageSqlite::JournalMode() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  journalMode = GNSDK_NULL;

	error = gnsdk_storage_sqlite_option_get(GNSDK_STORAGE_SQLITE_OPTION_JOURNAL_MODE, &journalMode);
	if (error) { throw GnError(); }

	return journalMode;
}


#endif /* GNSDK_STORAGE_SQLITE */
