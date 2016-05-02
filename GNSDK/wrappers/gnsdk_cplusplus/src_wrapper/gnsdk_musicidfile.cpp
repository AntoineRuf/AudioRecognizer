/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* musicidfile.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk_manager.hpp"
#include "gnsdk_convert.hpp"

#if GNSDK_MUSICID_FILE

#include "gnsdk_musicidfile.hpp"
#include "metadata_music.hpp"

using namespace gracenote;
using namespace gracenote::metadata;
using namespace gracenote::musicid_file;

/**************************************************************************
** GnMusicIdFile
*/

gnsdk_uint32_t GnMusicIdFile::kTimeValueInfinite = GNSDK_MUSICIDFILE_TIMEOUT_INFINITE;

static void GNSDK_CALLBACK_API
_callback_status(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo, gnsdk_musicidfile_callback_status_t status, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort);
static void GNSDK_CALLBACK_API
_callback_get_fingerprint(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort);
static void GNSDK_CALLBACK_API
_callback_get_metadata(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort);
static void GNSDK_CALLBACK_API
_callback_result_available(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_gdo_handle_t response_gdo, gnsdk_uint32_t current_album, gnsdk_uint32_t total_albums, gnsdk_bool_t* p_abort);
static void GNSDK_CALLBACK_API
_callback_result_not_found(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* _abort);
static void GNSDK_CALLBACK_API
_callback_musicid_complete(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_error_t musicidfile_complete_error);

static gnsdk_musicidfile_callbacks_t musicidfile_callbacks_ =
{
	_callback_status,
	_callback_get_fingerprint,
	_callback_get_metadata,
	_callback_result_available,
	_callback_result_not_found,
	_callback_musicid_complete
};

/**
 * gnsdk_musicidfile_fileinfo_callbacks_t
 */
static void GNSDK_CALLBACK_API
_callback_fileinfo_get_fingerprint(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort);
static void GNSDK_CALLBACK_API
_callback_fileinfo_get_metadata(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort);

gnsdk_musicidfile_fileinfo_callbacks_t musicidfile_callbacks_fileinfo_ =
{
	_callback_fileinfo_get_fingerprint,
	_callback_fileinfo_get_metadata
};


/*-----------------------------------------------------------------------------
 *  MusicIdFileOptions
 */

/*-----------------------------------------------------------------------------
 *  LookupMode
 */
void
GnMusicIdFileOptions::LookupMode(GnLookupMode lookupMode) throw (GnError)
{
	gnsdk_error_t error;

	switch (lookupMode)
	{
	case kLookupModeLocal:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_LOCAL);
		break;

	case kLookupModeOnline:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE);
		break;

	case kLookupModeOnlineNoCache:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_NOCACHE);
		break;

	case kLookupModeOnlineNoCacheRead:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_NOCACHEREAD);
		break;

	case kLookupModeOnlineCacheOnly:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_CACHEONLY);
		break;

	default:
		return;
	}

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  LookupData
 */
void
GnMusicIdFileOptions::LookupData(GnLookupData lookupData, bool enable) throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_enable = ( enable ) ? GNSDK_VALUE_TRUE : GNSDK_VALUE_FALSE;

	switch (lookupData)
	{
	case kLookupDataContent:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_ENABLE_CONTENT_DATA, sz_enable);
		break;

	case kLookupDataClassical:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_ENABLE_CLASSICAL_DATA, sz_enable);
		break;

	case kLookupDataSonicData:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_ENABLE_SONIC_DATA, sz_enable);
		break;

	case kLookupDataPlaylist:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_ENABLE_PLAYLIST, sz_enable);
		break;

	case kLookupDataExternalIds:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_ENABLE_EXTERNAL_IDS, sz_enable);
		break;

	case kLookupDataGlobalIds:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_ENABLE_GLOBALIDS, sz_enable);
		break;

	default:
		return;
	}

	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  NetworkInterface
 */
void
GnMusicIdFileOptions::NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_QUERY_OPTION_NETWORK_INTERFACE, ipAddress);
	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  Custom
 */
void
GnMusicIdFileOptions::Custom(gnsdk_cstr_t optionKey, bool enable) throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_enable = ( enable ) ? GNSDK_VALUE_TRUE : GNSDK_VALUE_FALSE;

	error = gnsdk_musicidfile_query_option_set(weakhandle_, optionKey, sz_enable);

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Custom
 */
void
GnMusicIdFileOptions::Custom(gnsdk_cstr_t option, gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_query_option_set(weakhandle_, option, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  BatchSize
 */
void
GnMusicIdFileOptions::BatchSize(gnsdk_uint32_t size) throw (GnError)
{
	char buffer[12] = {0};
	gnstd::gn_itoa(buffer, 12, size);

	gnsdk_error_t error = gnsdk_musicidfile_query_option_set(weakhandle_,
															 GNSDK_MUSICIDFILE_OPTION_BATCH_SIZE,
															 buffer);

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  ThreadPriority
 */
void
GnMusicIdFileOptions::ThreadPriority(GnThreadPriority value) throw (GnError)
{
	gnsdk_error_t error;

	switch (value)
	{
	case kThreadPriorityDefault:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_THREADPRIORITY, GNSDK_MUSICIDFILE_OPTION_VALUE_PRIORITY_DEFAULT);
		break;

	case kThreadPriorityIdle:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_THREADPRIORITY, GNSDK_MUSICIDFILE_OPTION_VALUE_PRIORITY_IDLE);
		break;

	case kThreadPriorityLow:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_THREADPRIORITY, GNSDK_MUSICIDFILE_OPTION_VALUE_PRIORITY_LOW);
		break;

	case kThreadPriorityNormal:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_THREADPRIORITY, GNSDK_MUSICIDFILE_OPTION_VALUE_PRIORITY_NORM);
		break;

	case kThreadPriorityHigh:
		error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_THREADPRIORITY, GNSDK_MUSICIDFILE_OPTION_VALUE_PRIORITY_HIGH);
		break;

	default:
		return;
	}

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  OnlineProcessing
 */
void
GnMusicIdFileOptions::OnlineProcessing(bool enable) throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_enable = ( enable ) ? GNSDK_VALUE_TRUE : GNSDK_VALUE_FALSE;

	error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_ONLINE_PROCESSING, sz_enable);

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  PreferResultLanguage
 */
void
GnMusicIdFileOptions::PreferResultLanguage(GnLanguage preferredLangauge) throw (GnError)
{
	gnsdk_error_t error = gnsdk_musicidfile_query_option_set(weakhandle_,
															 GNSDK_MUSICIDFILE_OPTION_PREFERRED_LANG,
															 gnconvert::_convertLangCppC(preferredLangauge) );

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  PreferResultExternalId
 */
void
GnMusicIdFileOptions::PreferResultExternalId(gnsdk_cstr_t preferredExternalId) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_query_option_set(weakhandle_, GNSDK_MUSICIDFILE_OPTION_PREFERRED_XID, preferredExternalId);

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  GnMusicIdFileInfoManager
 */
/*-----------------------------------------------------------------------------
 *  RemoveFileInfo
 */

/*-----------------------------------------------------------------------------
 *  CreateFileInfo
 */
GnMusicIdFileInfo
GnMusicIdFileInfoManager::Add(gnsdk_cstr_t uniqueIdentifier, IGnMusicIdFileInfoEvents* pEventHandler) throw (GnError)
{
	gnsdk_musicidfile_fileinfo_callbacks_t* pCallbacks     = &musicidfile_callbacks_fileinfo_;
	gnsdk_musicidfile_fileinfo_handle_t     fileInfoHandle = GNSDK_NULL;
	gnsdk_error_t                           error;

	if ( pEventHandler == GNSDK_NULL)
		pCallbacks = GNSDK_NULL;

	error = gnsdk_musicidfile_query_fileinfo_create(weakhandle_, uniqueIdentifier, pCallbacks, pEventHandler, &fileInfoHandle);
	if (error) { throw GnError(); }

	return GnMusicIdFileInfo(weakhandle_, fileInfoHandle);
}


/*-----------------------------------------------------------------------------
 *  Remove
 */
void
GnMusicIdFileInfoManager::Remove(const GnMusicIdFileInfo& fileInfo) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_query_fileinfo_remove(weakhandle_, fileInfo.fileInfohandle_);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  RenderToXml
 */
GnString
GnMusicIdFileInfoManager::RenderToXml() throw (GnError)
{
	gnsdk_str_t   str = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_musicidfile_query_fileinfo_render_to_xml(weakhandle_, &str);
	if (error) { throw GnError(); }

	return GnString::manage(str);
}


/*-----------------------------------------------------------------------------
 *  AddFromXml
 */
gnsdk_uint32_t
GnMusicIdFileInfoManager::AddFromXml(gnsdk_cstr_t xmlStr) throw (GnError)
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	error = gnsdk_musicidfile_query_fileinfo_create_from_xml(weakhandle_, xmlStr, &count);
	if (error) { throw GnError(); }

	return count;
}

GnMusicIdFileInfo
GnMusicIdFileInfoManager::GetByIdentifier(gnsdk_cstr_t ident) throw (GnError)
{
	gnsdk_musicidfile_fileinfo_handle_t	fileinfo_handle;
	gnsdk_error_t  error;

	error = gnsdk_musicidfile_query_fileinfo_get_by_ident(weakhandle_,ident,&fileinfo_handle);
	if (error) { throw GnError(); }

	return GnMusicIdFileInfo(weakhandle_, fileinfo_handle);
}

GnMusicIdFileInfo
GnMusicIdFileInfoManager::GetByFilename(gnsdk_cstr_t filename) throw (GnError)
{
	gnsdk_musicidfile_fileinfo_handle_t	fileinfo_handle;
	gnsdk_error_t  error;

	error = gnsdk_musicidfile_query_fileinfo_get_by_filename(weakhandle_,filename,&fileinfo_handle);
	if (error) { throw GnError(); }

	return GnMusicIdFileInfo(weakhandle_, fileinfo_handle);
}

GnMusicIdFileInfo
GnMusicIdFileInfoManager::GetByFolder(gnsdk_cstr_t folder, gnsdk_uint32_t index) throw (GnError)
{
	gnsdk_musicidfile_fileinfo_handle_t	fileinfo_handle;
	gnsdk_error_t  error;

	error = gnsdk_musicidfile_query_fileinfo_get_by_folder(weakhandle_,folder,index,&fileinfo_handle);
	if (error) { throw GnError(); }

	return GnMusicIdFileInfo(weakhandle_, fileinfo_handle);
}


/*-----------------------------------------------------------------------------
 *  GnMusicIdFile
 */

GnMusicIdFile::GnMusicIdFile(const GnUser& user, IGnMusicIdFileEvents* pEventHandler) throw (GnError) :
	eventhandler_(pEventHandler)
{
	gnsdk_musicidfile_query_handle_t	query_handle = GNSDK_NULL;
	gnsdk_error_t						error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_MUSICIDFILE);

	error = gnsdk_musicidfile_query_create(user.native(), &musicidfile_callbacks_, this, &query_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(query_handle);

	options_.weakhandle_ = query_handle;
	fileinfomanager_.weakhandle_ = query_handle;
}


GnMusicIdFile::~GnMusicIdFile()
{
}


/*-----------------------------------------------------------------------------
 *  Version
 */
gnsdk_cstr_t
GnMusicIdFile::Version()
{
	return gnsdk_musicidfile_get_version();
}


/*-----------------------------------------------------------------------------
 *  BuildDate
 */
gnsdk_cstr_t
GnMusicIdFile::BuildDate()
{
	return gnsdk_musicidfile_get_build_date();
}


/*-----------------------------------------------------------------------------
 *  DoTrackId
 */
void
GnMusicIdFile::DoTrackId(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throw (GnError)
{
	gnsdk_uint32_t queryflags = 0;
	gnsdk_error_t  error;



	if (processType == kQueryReturnAll)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_ALL;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_SINGLE;

	if (responseType == kResponseMatches)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_MATCHES;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_ALBUMS;

	error = gnsdk_musicidfile_query_do_trackid(get<gnsdk_musicidfile_query_handle_t>(), queryflags);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  DoTrackIdAsync
 */
void
GnMusicIdFile::DoTrackIdAsync(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throw (GnError)
{
	gnsdk_uint32_t queryflags = 0;
	gnsdk_error_t  error;

	if (processType == kQueryReturnAll)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_ALL;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_SINGLE;

	if (responseType == kResponseMatches)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_MATCHES;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_ALBUMS;

	queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_ASYNC;
	error       = gnsdk_musicidfile_query_do_trackid(get<gnsdk_musicidfile_query_handle_t>(), queryflags);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  DoAlbumId
 */
void
GnMusicIdFile::DoAlbumId(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throw (GnError)
{
	gnsdk_uint32_t queryflags = 0;
	gnsdk_error_t  error;


	if (processType == kQueryReturnAll)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_ALL;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_SINGLE;

	if (responseType == kResponseMatches)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_MATCHES;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_ALBUMS;

	error = gnsdk_musicidfile_query_do_albumid(get<gnsdk_musicidfile_query_handle_t>(), queryflags);
	if (GNSDKERR_SEVERE(error))	{throw GnError();}
		
	
}


/*-----------------------------------------------------------------------------
 *  DoAlbumIdAsync
 */
void
GnMusicIdFile::DoAlbumIdAsync(GnMusicIdFileProcessType processType, GnMusicIdFileResponseType responseType) throw (GnError)
{
	gnsdk_uint32_t queryflags = 0;
	gnsdk_error_t  error;


	if (processType == kQueryReturnAll)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_ALL;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_SINGLE;

	if (responseType == kResponseMatches)
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_MATCHES;
	else
		queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_ALBUMS;

	queryflags |= GNSDK_MUSICIDFILE_QUERY_FLAG_ASYNC;
	error       = gnsdk_musicidfile_query_do_albumid(get<gnsdk_musicidfile_query_handle_t>(), queryflags);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  DoLibraryId
 */
void
GnMusicIdFile::DoLibraryId(GnMusicIdFileResponseType responseType) throw (GnError)
{
	gnsdk_uint32_t queryFlags = 0;
	gnsdk_error_t  error;

	if (responseType == kResponseMatches)
		queryFlags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_MATCHES;
	else
		queryFlags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_ALBUMS;

	/* Return All is not supported by LibraryID, defaulting to Return Single for all queries */
	queryFlags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_SINGLE;

	error = gnsdk_musicidfile_query_do_libraryid(get<gnsdk_musicidfile_query_handle_t>(), queryFlags);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  DoLibraryIdAsync
 */
void
GnMusicIdFile::DoLibraryIdAsync(GnMusicIdFileResponseType responseType) throw (GnError)
{
	gnsdk_uint32_t queryFlags = 0;
	gnsdk_error_t  error;

	if (responseType == kResponseMatches)
		queryFlags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_MATCHES;
	else
		queryFlags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RESPONSE_ALBUMS;

	/* Return All is not supported by LibraryID, defaulting to Return Single for all queries */
	queryFlags |= GNSDK_MUSICIDFILE_QUERY_FLAG_RETURN_SINGLE;
	queryFlags |= GNSDK_MUSICIDFILE_QUERY_FLAG_ASYNC;

	error = gnsdk_musicidfile_query_do_libraryid(get<gnsdk_musicidfile_query_handle_t>(), queryFlags);
	if (error) { throw GnError(); }


}


/*-----------------------------------------------------------------------------
 *  _callback_status
 */
void GNSDK_CALLBACK_API
_callback_status(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo_handle, gnsdk_musicidfile_callback_status_t status, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort)
{
	GnMusicIdFile* p_midf = (GnMusicIdFile*)callback_data;

	(void)query_handle;

	if (p_midf->EventHandler())
	{
		GnMusicIdFileInfo			fileinfo = GnMusicIdFileInfo(query_handle, fileinfo_handle);
        GnMusicIdFileCallbackStatus cppStatus = kMusicIdFileCallbackStatusError;
        gn_canceller				canceller;

        switch ( status )
        {
            case gnsdk_musicidfile_status_fileinfo_processing_begin: 	cppStatus = kMusicIdFileCallbackStatusProcessingBegin; break;
			case gnsdk_musicidfile_status_fileinfo_query: 				cppStatus = kMusicIdFileCallbackStatusFileInfoQuery; break;
			case gnsdk_musicidfile_status_fileinfo_processing_complete: cppStatus = kMusicIdFileCallbackStatusProcessingComplete; break;
			case gnsdk_musicidfile_status_fileinfo_processing_error: 	cppStatus = kMusicIdFileCallbackStatusProcessingError; break;
			case gnsdk_musicidfile_status_error: 						cppStatus = kMusicIdFileCallbackStatusError; break;
        }

        p_midf->EventHandler()->MusicIdFileStatusEvent(fileinfo, cppStatus, current_file, total_files, canceller);
        if (canceller.IsCancelled() )
        {
            *p_abort = GNSDK_TRUE;
        }
		
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_get_fingerprint
 */
void GNSDK_CALLBACK_API
_callback_get_fingerprint(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo_handle, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort)
{
	GnMusicIdFile* p_midf = (GnMusicIdFile*)callback_data;

	GNSDK_UNUSED(query_handle);

	if (p_midf->EventHandler())
	{
		GnMusicIdFileInfo	fileinfo = GnMusicIdFileInfo(query_handle, fileinfo_handle);
        gn_canceller		canceller;

        p_midf->EventHandler()->GatherFingerprint(fileinfo, current_file, total_files, canceller);
        if (canceller.IsCancelled())
        {
            *p_abort = GNSDK_TRUE;
        }
		
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_get_metadata
 */
void GNSDK_CALLBACK_API
_callback_get_metadata(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo_handle, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort)
{
	GnMusicIdFile* p_midf = (GnMusicIdFile*)callback_data;

	GNSDK_UNUSED(query_handle);

	if (p_midf->EventHandler())
	{
		GnMusicIdFileInfo	fileinfo = GnMusicIdFileInfo(query_handle, fileinfo_handle);
        gn_canceller		canceller;

        p_midf->EventHandler()->GatherMetadata(fileinfo, current_file, total_files, canceller);
        if (canceller.IsCancelled())
        {
				*p_abort = GNSDK_TRUE;
        }
		
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_result_available
 */
void GNSDK_CALLBACK_API
_callback_result_available(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_gdo_handle_t response_gdo, gnsdk_uint32_t current_album, gnsdk_uint32_t total_albums, gnsdk_bool_t* p_abort)
{
	GnMusicIdFile* p_midf = (GnMusicIdFile*)callback_data;

	(void)query_handle;

	if (p_midf->EventHandler())
	{
        GnResponseAlbums	albumResponse(response_gdo);
        gn_canceller		canceller;

        if (albumResponse.IsType(GNSDK_GDO_TYPE_RESPONSE_MATCH) )
        {
            GnResponseDataMatches dataMatchResponse(response_gdo);
            p_midf->EventHandler()->MusicIdFileMatchResult(dataMatchResponse, current_album, total_albums, canceller);
        }
        else
        {
            p_midf->EventHandler()->MusicIdFileAlbumResult(albumResponse, current_album, total_albums, canceller);
        }

        if (canceller.IsCancelled())
        {
            *p_abort = GNSDK_TRUE;
        }
		
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_result_not_found
 */
void GNSDK_CALLBACK_API
_callback_result_not_found(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo_handle, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort)
{
	GnMusicIdFile* p_midf = (GnMusicIdFile*)callback_data;

	if (p_midf->EventHandler())
	{
		GnMusicIdFileInfo	fileinfo = GnMusicIdFileInfo(query_handle, fileinfo_handle);
        gn_canceller		canceller;

        p_midf->EventHandler()->MusicIdFileResultNotFound(fileinfo, current_file, total_files, canceller);
        if (canceller.IsCancelled())
        {
            *p_abort = GNSDK_TRUE;
        }
		
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_musicid_complete
 */
void GNSDK_CALLBACK_API
_callback_musicid_complete(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_error_t musicidfile_complete_error)
{
	GnMusicIdFile* p_midf = (GnMusicIdFile*)callback_data;

	GNSDK_UNUSED(query_handle);
	GNSDK_UNUSED(musicidfile_complete_error);

	if (p_midf->EventHandler())
	{
		/* TODO: The C API should allow for gnsdk_error_info_t, not gnsdk_error_t */

		gnsdk_error_info_t	errorInfo = {0};
		errorInfo.error_code = musicidfile_complete_error;
        
        GnError error(&errorInfo);
		p_midf->EventHandler()->MusicIdFileComplete(error);
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_fileinfo_get_fingerprint
 */
void GNSDK_CALLBACK_API
_callback_fileinfo_get_fingerprint(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo_handle, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort)
{
	IGnMusicIdFileInfoEvents*	pEventHandler = (IGnMusicIdFileInfoEvents*)callback_data;
	gn_canceller				canceller;

	if (pEventHandler)
	{
		GnMusicIdFileInfo fileinfo = GnMusicIdFileInfo(query_handle, fileinfo_handle);
		pEventHandler->GatherFingerprint(fileinfo, current_file, total_files, canceller);
	}

	if ( canceller.IsCancelled() )
	{
		*p_abort = GNSDK_TRUE;
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_fileinfo_get_metadata
 */
void GNSDK_CALLBACK_API
_callback_fileinfo_get_metadata(void* callback_data, gnsdk_musicidfile_query_handle_t query_handle, gnsdk_musicidfile_fileinfo_handle_t fileinfo_handle, gnsdk_uint32_t current_file, gnsdk_uint32_t total_files, gnsdk_bool_t* p_abort)
{
	IGnMusicIdFileInfoEvents*	pEventHandler = (IGnMusicIdFileInfoEvents*)callback_data;
	gn_canceller				canceller;

	if (pEventHandler)
	{
		GnMusicIdFileInfo fileinfo = GnMusicIdFileInfo(query_handle, fileinfo_handle);
		pEventHandler->GatherMetadata(fileinfo, current_file, total_files, canceller);
	}

	if ( canceller.IsCancelled() )
	{
		*p_abort = GNSDK_TRUE;
	}
}


/*-----------------------------------------------------------------------------
 *  WaitForComplete
 */
void
GnMusicIdFile::WaitForComplete(gnsdk_uint32_t timeoutValue) throw (GnError)
{
	gnsdk_error_t pMidFComplteError;
	gnsdk_error_t error;

	error = gnsdk_musicidfile_query_wait_for_complete(get<gnsdk_musicidfile_query_handle_t>(), timeoutValue, &pMidFComplteError);
	if (GNSDKERR_SEVERE(error) || GNSDKERR_SEVERE(pMidFComplteError)) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  WaitForComplete - 
 */
 // see http://jira/browse/GFM-710
void
GnMusicIdFile::WaitForComplete() throw (GnError)
{
	gnsdk_error_t pMidFComplteError;
	gnsdk_error_t error;

	error = gnsdk_musicidfile_query_wait_for_complete(get<gnsdk_musicidfile_query_handle_t>(), GnMusicIdFile::kTimeValueInfinite, &pMidFComplteError);
	if (GNSDKERR_SEVERE(error) || GNSDKERR_SEVERE(pMidFComplteError)) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  SetCancel
 */
void
GnMusicIdFile::Cancel()
{
	gnsdk_error_t error;

    error = gnsdk_musicidfile_query_cancel(get<gnsdk_musicidfile_query_handle_t>());
    if (GNSDKERR_SEVERE(error)) { throw GnError(); }
	
}


/**************************************************************************
** GnMusicIdFileInfo
**
**   NOtes: Currently life cycle management of a GnMusicIdFileInfo is determined by
**     :  the object . i.e. it holds onto its parent to stay relevant . the
**        bad behaviour is that a FileInfo holds onto the life cycles the Query
**        and all its remaining fileInfos.
*/
gnsdk_cstr_t
GnMusicIdFileInfo::Identifier() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_IDENT, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  GetFileName
 */
gnsdk_cstr_t
GnMusicIdFileInfo::FileName() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_FILENAME, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  FileName
 */
void
GnMusicIdFileInfo::FileName(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_FILENAME, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  CddbId
 */
gnsdk_cstr_t
GnMusicIdFileInfo::CddbId() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_CDDB_IDS, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  CddbId
 */
void
GnMusicIdFileInfo::CddbId(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_CDDB_IDS, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  AlbumArtist
 */
gnsdk_cstr_t
GnMusicIdFileInfo::AlbumArtist() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_ALBUMARTIST, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  AlbumArtist
 */
void
GnMusicIdFileInfo::AlbumArtist(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_ALBUMARTIST, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  AlbumTitle
 */
gnsdk_cstr_t
GnMusicIdFileInfo::AlbumTitle() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_ALBUMTITLE, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  AlbumTitle
 */
void
GnMusicIdFileInfo::AlbumTitle(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_ALBUMTITLE, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  TrackArtist
 */
gnsdk_cstr_t
GnMusicIdFileInfo::TrackArtist() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TRACKARTIST, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  TrackArtist
 */
void
GnMusicIdFileInfo::TrackArtist(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TRACKARTIST, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  TrackTitle
 */
gnsdk_cstr_t
GnMusicIdFileInfo::TrackTitle() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TRACKTITLE, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  TrackTitle
 */
void
GnMusicIdFileInfo::TrackTitle(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TRACKTITLE, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  TrackNumber
 */
gnsdk_uint32_t
GnMusicIdFileInfo::TrackNumber() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TRACKNUMBER, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return gnstd::gn_atoi(sz_value);
}


/*-----------------------------------------------------------------------------
 *  TrackNumber
 */
void
GnMusicIdFileInfo::TrackNumber(gnsdk_uint32_t trackNumber) throw (GnError)
{
	gnsdk_char_t  buf[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buf, sizeof(buf), trackNumber);
	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TRACKNUMBER, buf);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  DiscNumber
 */
gnsdk_uint32_t
GnMusicIdFileInfo::DiscNumber() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = GNSDK_NULL;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_DISCNUMBER, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return gnstd::gn_atoi(sz_value);
}


/*-----------------------------------------------------------------------------
 *  DiscNumber
 */
void
GnMusicIdFileInfo::DiscNumber(gnsdk_uint32_t discNumber) throw (GnError)
{
	gnsdk_char_t  buf[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buf, sizeof(buf), discNumber);
	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_DISCNUMBER, buf);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  TagId
 */
gnsdk_cstr_t
GnMusicIdFileInfo::TagId() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TAGID, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  TagId
 */
void
GnMusicIdFileInfo::TagId(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TAGID, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Fingerprint
 */
gnsdk_cstr_t
GnMusicIdFileInfo::Fingerprint() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_FINGERPRINT, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  Fingerprint
 */
void
GnMusicIdFileInfo::Fingerprint(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_FINGERPRINT, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  MediaId
 */
gnsdk_cstr_t
GnMusicIdFileInfo::MediaId() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_MEDIA_ID, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  MediaId
 */
void
GnMusicIdFileInfo::MediaId(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_MEDIA_ID, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Mui
 */
gnsdk_cstr_t
GnMusicIdFileInfo::Mui() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_MUI, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  Mui
 */
void
GnMusicIdFileInfo::Mui(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_MUI, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  CdToc
 */
gnsdk_cstr_t
GnMusicIdFileInfo::CdToc() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TOC_OFFSETS, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  CdToc
 */
void
GnMusicIdFileInfo::CdToc(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TOC_OFFSETS, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Tui
 */
gnsdk_cstr_t
GnMusicIdFileInfo::Tui() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TUI, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  Tui
 */
void
GnMusicIdFileInfo::Tui(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TUI, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  TuiTag
 */
gnsdk_cstr_t
GnMusicIdFileInfo::TuiTag() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_value = gnstd::kEmptyString;

	error = gnsdk_musicidfile_fileinfo_metadata_get(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TUI_TAG, &sz_value, GNSDK_NULL);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return sz_value;
}


/*-----------------------------------------------------------------------------
 *  TuiTag
 */
void
GnMusicIdFileInfo::TuiTag(gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_metadata_set(fileInfohandle_, GNSDK_MUSICIDFILE_FILEINFO_VALUE_TUI_TAG, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  FingerprintBegin
 */
void
GnMusicIdFileInfo::FingerprintBegin(gnsdk_uint32_t audioSampleRate, gnsdk_uint32_t audioSampleSize, gnsdk_uint32_t audioChannels)
throw (GnError)
{
	gnsdk_error_t error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_DSP);

	error = gnsdk_musicidfile_fileinfo_fingerprint_begin(fileInfohandle_, audioSampleRate, audioSampleSize, audioChannels);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  FingerprintWrite
 */
bool
GnMusicIdFileInfo::FingerprintWrite(const gnsdk_byte_t* audioData, gnsdk_size_t audioDataSize) throw (GnError)
{
	gnsdk_char_t  b_complete = GNSDK_FALSE;
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_fingerprint_write(fileInfohandle_, audioData, audioDataSize, &b_complete);
	if (error) { throw GnError(); }

	if (b_complete)
	{
		return true;
	}
	return false;
}


/*-----------------------------------------------------------------------------
 *  FingerprintEnd
 */
void
GnMusicIdFileInfo::FingerprintEnd() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidfile_fileinfo_fingerprint_end(fileInfohandle_);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  FingerprintFromSource
 */
void
GnMusicIdFileInfo::FingerprintFromSource(IGnAudioSource& audioSource)  throw (GnError)
{
	gnsdk_uint32_t	audioSizeInBytes;
	gnsdk_byte_t*	pAudioBuffer = GNSDK_NULL;
	gnsdk_size_t	audioDataSize;
	gnsdk_bool_t  	bComplete;
	gnsdk_error_t 	error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_DSP);

	error = audioSource.SourceInit();
	if (error)
	{
		gnsdk_error_info_t error_info;
		error_info.error_api = "GnMusicIdFileInfo::FingerprintFromSource";
		error_info.error_code = error;
		error_info.error_description = "Failed to initialize audio source";
		error_info.error_module = "GnMusicIdFile";
		error_info.source_error_code = error_info.error_code;
		error_info.source_error_module = error_info.error_module;
		throw GnError(&error_info);
	}

	bComplete = GNSDK_FALSE;

	error = gnsdk_musicidfile_fileinfo_fingerprint_begin(fileInfohandle_, audioSource.SamplesPerSecond(), audioSource.SampleSizeInBits(), audioSource.NumberOfChannels() );
	if (!error)
	{
		// need to create a buffer to carry the raw audio, make it relative to the total size
		// the raw audio we expect we need for generating the fingerprint
		audioSizeInBytes = audioSource.SamplesPerSecond() * (audioSource.SampleSizeInBits()/8) * audioSource.NumberOfChannels() * 4; // 4 for 4 seconds
		if ( audioSizeInBytes != 0 )
		{
			pAudioBuffer = new gnsdk_byte_t[audioSizeInBytes];
			if ( pAudioBuffer == GNSDK_NULL )
				error = GNSDKERR_NoMemory;

			if (!error)
			{
				while (0 < ( audioDataSize = audioSource.GetData(pAudioBuffer, audioSizeInBytes ) ) )
				{
					error = gnsdk_musicidfile_fileinfo_fingerprint_write(fileInfohandle_, pAudioBuffer, audioDataSize, &bComplete);
					if (error)
					{
						break;
					}

					if (bComplete)
					{
						break;
					}
				}

				delete[] pAudioBuffer;
			}

			if (!bComplete)
			{
				error = gnsdk_musicidfile_fileinfo_fingerprint_end(fileInfohandle_);
			}
		}
	}

	audioSource.SourceClose();

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Status
 */
GnMusicIdFileInfoStatus
GnMusicIdFileInfo::Status() throw (GnError)
{
	gnsdk_musicidfile_fileinfo_status_t status;
	const gnsdk_error_info_t*           pErrorInfo;
	gnsdk_error_t                       error;
	GnMusicIdFileInfoStatus				cppStatus = kMusicIdFileInfoStatusError;

	error = gnsdk_musicidfile_fileinfo_status(fileInfohandle_, &status, &pErrorInfo);
	if (error) { throw GnError(); }

	switch ( status )
	{
	case gnsdk_musicidfile_fileinfo_unprocessed:	cppStatus = kMusicIdFileInfoStatusUnprocessed; break;
	case gnsdk_musicidfile_fileinfo_processing:		cppStatus = kMusicIdFileInfoStatusProcessing; break;
	case gnsdk_musicidfile_fileinfo_error:			cppStatus = kMusicIdFileInfoStatusError; break;
	case gnsdk_musicidfile_fileinfo_result_none:	cppStatus = kMusicIdFileInfoStatusResultNone; break;
	case gnsdk_musicidfile_fileinfo_result_single:	cppStatus = kMusicIdFileInfoStatusResultSingle; break;
	case gnsdk_musicidfile_fileinfo_result_all:		cppStatus = kMusicIdFileInfoStatusResultAll; break;
	}

	return cppStatus;
}


/*-----------------------------------------------------------------------------
 *  ErrorInformation
 */
GnError
GnMusicIdFileInfo::ErrorInformation() throw (GnError)
{
	gnsdk_musicidfile_fileinfo_status_t status;
	const gnsdk_error_info_t*           pErrorInfo;
	gnsdk_error_t                       error;

	error = gnsdk_musicidfile_fileinfo_status(fileInfohandle_, &status, &pErrorInfo);
	if (error) { throw GnError(); }

	GnError errorObj(pErrorInfo);

	return errorObj;
}


/*-----------------------------------------------------------------------------
 *  AlbumResponse
 */
GnResponseAlbums
GnMusicIdFileInfo::AlbumResponse() throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo;
	gnsdk_error_t      error;

	error = gnsdk_musicidfile_fileinfo_get_response_gdo(fileInfohandle_, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseAlbums result(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return result;
}


/*-----------------------------------------------------------------------------
 *  DataMatchResponse
 */
GnResponseDataMatches
GnMusicIdFileInfo::DataMatchResponse() throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo;
	gnsdk_error_t      error;

	error = gnsdk_musicidfile_fileinfo_get_response_gdo(fileInfohandle_, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseDataMatches result(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return result;
}


#endif /* GNSDK_MUSICID_FILE */

