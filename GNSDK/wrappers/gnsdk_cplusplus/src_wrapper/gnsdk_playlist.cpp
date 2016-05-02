/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_playlist.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk_manager.hpp"

#if GNSDK_PLAYLIST

#include "gnsdk_playlist.hpp"
#include "gnsdk_list.hpp"

using namespace gracenote;
using namespace gracenote::playlist;

static void _add(gnsdk_playlist_collection_handle_t handle, gnsdk_cstr_t mediaIdentifier, gnsdk_gdo_handle_t gdo) throw (GnError);
static int BUFFER_SZ = 256;

/******************************************************************************
 *  GnPlaylist
 */
GnPlaylist::GnPlaylist() throw (GnError)
{
	_gnsdk_internal::module_initialize(GNSDK_MODULE_PLAYLIST);
}


/*-----------------------------------------------------------------------------
 *  Version
 */
gnsdk_cstr_t
GnPlaylist::Version()
{
	return gnsdk_playlist_get_version();
}


/*-----------------------------------------------------------------------------
 *  BuildDate
 */
gnsdk_cstr_t
GnPlaylist::BuildDate()
{
	return gnsdk_playlist_get_build_date();
}




/* ***************************************************************************************************************************** */
/* GnPlaylistResult result_provider */
/* ***************************************************************************************************************************** */

GnPlaylistIdentifier
result_provider::get_data(gnsdk_uint32_t pos) const
{
	gnsdk_cstr_t  media_ident = GNSDK_NULL;
	gnsdk_cstr_t  coll_name   = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_playlist_results_enum(weak_handle_, pos, &media_ident, &coll_name);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
 
	return GnPlaylistIdentifier(media_ident, coll_name);
}


/*-----------------------------------------------------------------------------
 *  count
 */
gnsdk_uint32_t
result_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error = PLERR_NoError;

	error = gnsdk_playlist_results_count(weak_handle_, &count);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return count;
}


/* ***************************************************************************************************************************** */
/* GnPlaylistCollection  collection_ident_provider */
/* ***************************************************************************************************************************** */

GnPlaylistIdentifier
collection_ident_provider::get_data(gnsdk_uint32_t pos) const
{
	gnsdk_cstr_t  media_ident = GNSDK_NULL;
	gnsdk_cstr_t  coll_name   = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_ident_enum(weak_handle_, pos, &media_ident, &coll_name);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return GnPlaylistIdentifier(media_ident, coll_name);
}

gnsdk_uint32_t 
collection_ident_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error = PLERR_NoError;

	error = gnsdk_playlist_collection_ident_count(weak_handle_, &count);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return count;

}
/* ***************************************************************************************************************************** */
/* GnPlaylistCollection  collection_join_provider */
/* ***************************************************************************************************************************** */

GnPlaylistCollection
collection_join_provider::get_data(gnsdk_uint32_t pos) const
{
	gnsdk_playlist_collection_handle_t coll  = GNSDK_NULL;
	gnsdk_error_t                      error = PLERR_NoError;

	error = gnsdk_playlist_collection_join_enum(weak_handle_, pos, &coll);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	GnPlaylistCollection tmp(coll);
	gnsdk_handle_release(coll);
	return tmp;
}

gnsdk_uint32_t 
collection_join_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error = PLERR_NoError;

	error = gnsdk_playlist_collection_join_count(weak_handle_, &count);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return count;

}


/* ***************************************************************************************************************************** */
/* GnPlaylistCollection */
/* ***************************************************************************************************************************** */

GnPlaylistCollection::GnPlaylistCollection(gnsdk_playlist_collection_handle_t handle) : GnObject(handle)
{
	_gnsdk_internal::module_initialize(GNSDK_MODULE_PLAYLIST);
	this->options_.weakhandle_ = handle;
}


GnPlaylistCollection::GnPlaylistCollection(gnsdk_byte_t* buffer, gnsdk_size_t size)
{
	gnsdk_playlist_collection_handle_t h_collection;
	gnsdk_error_t                      error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_PLAYLIST);

	error = gnsdk_playlist_collection_deserialize(buffer, size, &h_collection);
	if (error) { throw GnError(); }

	this->AcceptOwnership(h_collection);
	this->options_.weakhandle_ = h_collection;
}


GnPlaylistCollection::GnPlaylistCollection(gnsdk_cstr_t collectionName)
{
	gnsdk_playlist_collection_handle_t h_collection;
	gnsdk_error_t                      error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_PLAYLIST);

	error = gnsdk_playlist_collection_create(collectionName, &h_collection);
	if (error) { throw GnError(); }

	this->AcceptOwnership(h_collection);
	this->options_.weakhandle_ = h_collection;
}


GnPlaylistCollection::GnPlaylistCollection(const GnPlaylistCollection& other) : GnObject(other.Handle())
{
	this->options_.weakhandle_ = this->get<gnsdk_playlist_collection_handle_t>();
}


/*-----------------------------------------------------------------------------
 *  operator =
 */
GnPlaylistCollection&
GnPlaylistCollection::operator =(const GnPlaylistCollection& other)
{
	if ( this != &other)
	{
		GnObject::operator=(other);
		this->options_.weakhandle_ = this->get<gnsdk_playlist_collection_handle_t>();
	}
	return *this;
}


/*-----------------------------------------------------------------------------
 *  Name
 */
gnsdk_cstr_t
GnPlaylistCollection::Name() const throw (GnError)
{
	gnsdk_cstr_t  name = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_get_name(this->get<gnsdk_playlist_collection_handle_t>(), &name);
	if (error) { throw GnError(); }

	return name;
}


/*-----------------------------------------------------------------------------
 *  Name
 */
void
GnPlaylistCollection::Name(gnsdk_cstr_t updatedName) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_update_name(this->get<gnsdk_playlist_collection_handle_t>(), updatedName);
	if (error) { throw GnError(); }
}


/* Add an Ident to the collection. */
void
GnPlaylistCollection::Add(gnsdk_cstr_t mediaIdentifier) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_add_ident(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier);
	if (error) { throw GnError(); }
}


/* Add a GnAlbum to the collection. */
void
GnPlaylistCollection::Add(gnsdk_cstr_t mediaIdentifier, const metadata::GnAlbum& album) throw (GnError)
{
	_add(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, album.native() );
}


/* Add a GnTrack to the collection. */
void
GnPlaylistCollection::Add(gnsdk_cstr_t mediaIdentifier, const metadata::GnTrack& track) throw (GnError)
{
	_add(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, track.native() );
}


/* Add a GnContributor to the Collection. */
void
GnPlaylistCollection::Add(gnsdk_cstr_t mediaIdentifier, const metadata::GnContributor& contributor) throw (GnError)
{
	_add(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, contributor.native() );
}


/* Add a GnPlaylistAttributes to the Collection. */
void
GnPlaylistCollection::Add(gnsdk_cstr_t mediaIdentifier, const GnPlaylistAttributes& playlistMetadata) throw (GnError)
{
	_add(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, playlistMetadata.native() );
}


/*-----------------------------------------------------------------------------
 *  Add
 */
void
GnPlaylistCollection::Add(gnsdk_cstr_t mediaIdentifier, const GnListElement& listElement ) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_add_list_element(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, listElement.native());
	if (error) { throw GnError(); }
}


/* Remove and media identifier from the collection. */
void
GnPlaylistCollection::Remove(gnsdk_cstr_t mediaIdentifier) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_ident_remove(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Contains
 */
bool
GnPlaylistCollection::Contains(gnsdk_cstr_t mediaIdentifier) const throw (GnError)
{
	gnsdk_cstr_t   coll_name = GNSDK_NULL;
	gnsdk_uint32_t found     = 0;
	gnsdk_error_t  error;

	error = gnsdk_playlist_collection_ident_find(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, 0, &found, &coll_name);
	if (error && ( PLERR_NotFound != error) ) { throw GnError(); }

	return (found != 0);
}


/*-----------------------------------------------------------------------------
 *  Find
 */
ident_iterator
GnPlaylistCollection::Find(gnsdk_cstr_t mediaIdentifier, gnsdk_uint32_t start) const throw (GnError)
{
	gnsdk_cstr_t   coll_name = GNSDK_NULL;
	gnsdk_uint32_t found     = 0;
	gnsdk_error_t  error;

	error = gnsdk_playlist_collection_ident_find(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, start, &found, &coll_name);
	collection_ident_provider provider(get<gnsdk_playlist_collection_handle_t>() );
	if (GNSDKERR_SEVERE(error) ) 
	{
		throw GnError();
	}
	else if (error)
	{
		return ident_iterator(collection_ident_provider(get<gnsdk_playlist_collection_handle_t>()), GN_UINT32_MAX);
	}

	return ident_iterator(provider, found);
}


/*-----------------------------------------------------------------------------
 *  Attributes
 */
GnPlaylistAttributes
GnPlaylistCollection::Attributes(const GnUser& user, const GnPlaylistIdentifier& mediaIdentifier) const throw (GnError)
{
	gnsdk_error_t                      error  = PLERR_NoError;
	gnsdk_playlist_collection_handle_t h_coll = GNSDK_NULL;
	gnsdk_gdo_handle_t                 h_gdo  = GNSDK_NULL;

	error = gnsdk_playlist_collection_join_get(get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier.CollectionName(), &h_coll);
	if (error) { throw GnError(); }

	error = gnsdk_playlist_collection_get_gdo(h_coll, user.native(), mediaIdentifier.MediaIdentifier(), &h_gdo);
	gnsdk_playlist_collection_release(h_coll);

	GnPlaylistAttributes tmp(h_gdo);
	gnsdk_manager_gdo_release(h_gdo);

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  Attributes
 */
GnPlaylistAttributes
GnPlaylistCollection::Attributes(const GnUser& user, gnsdk_cstr_t mediaIdentifier, gnsdk_cstr_t joinedCollectionName) const throw (GnError)
{
	gnsdk_playlist_collection_handle_t h_coll = GNSDK_NULL;
	gnsdk_gdo_handle_t                 h_gdo  = GNSDK_NULL;
	gnsdk_error_t                      error;

	error = gnsdk_playlist_collection_join_get(get<gnsdk_playlist_collection_handle_t>(), joinedCollectionName, &h_coll);
	if (error) { throw GnError(); }

	error = gnsdk_playlist_collection_get_gdo(h_coll, user.native(), mediaIdentifier, &h_gdo);
	gnsdk_playlist_collection_release(h_coll);

	GnPlaylistAttributes tmp(h_gdo);
	gnsdk_manager_gdo_release(h_gdo);

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  StatementValidate
 */
GnError
GnPlaylistCollection::StatementValidate(gnsdk_cstr_t pdlStatement)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_statement_validate(pdlStatement, get<gnsdk_playlist_collection_handle_t>(), GNSDK_NULL);
	return GnError();
}


/*-----------------------------------------------------------------------------
 *  StatementAnalyzeIdent
 */
GnString
GnPlaylistCollection::StatementAnalyzeIdent(gnsdk_cstr_t pdlStatement, gnsdk_cstr_t mediaIdentifier) const throw (GnError)
{
	gnsdk_str_t   pdl_outcome = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_playlist_statement_analyze_ident(pdlStatement, get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier, &pdl_outcome);
	if (error) { throw GnError(); }

	return GnString::manage(pdl_outcome);
}


/*-----------------------------------------------------------------------------
 *  StatementRequiresSeed
 */
bool
GnPlaylistCollection::StatementRequiresSeed(gnsdk_cstr_t pdlStatement) const throw (GnError)
{
	gnsdk_bool_t  b_seed_needed = GNSDK_FALSE;
	gnsdk_error_t error;

	error = gnsdk_playlist_statement_validate(pdlStatement, get<gnsdk_playlist_collection_handle_t>(), &b_seed_needed);
	if (error) { throw GnError(); }

	if (b_seed_needed)
		return true;

	return false;
}


/*-----------------------------------------------------------------------------
 *  GeneratePlaylist
 */
GnPlaylistResult
GnPlaylistCollection::GeneratePlaylist(const GnUser& user, gnsdk_cstr_t pdlStatement, const metadata::GnDataObject& playlistSeed) throw (GnError)
{
	gnsdk_playlist_results_handle_t h_results = GNSDK_NULL;
	gnsdk_error_t                   error;

	error = gnsdk_playlist_generate_playlist(user.native(), pdlStatement, get<gnsdk_playlist_collection_handle_t>(), playlistSeed.native(), &h_results);
	if (error) { throw GnError(); }

	GnPlaylistResult retVal(h_results);

	error = gnsdk_playlist_results_release(h_results);
	if (error) { throw GnError(); }

	return retVal;
}


/*-----------------------------------------------------------------------------
 *  GeneratePlaylist
 */
GnPlaylistResult
GnPlaylistCollection::GeneratePlaylist(const GnUser& user, gnsdk_cstr_t pdlStatement) throw (GnError)
{
	gnsdk_playlist_results_handle_t h_results = GNSDK_NULL;
	gnsdk_error_t                   error;

	error = gnsdk_playlist_generate_playlist(user.native(), pdlStatement, get<gnsdk_playlist_collection_handle_t>(), GNSDK_NULL, &h_results);
	if (error) { throw GnError(); }

	GnPlaylistResult retVal(h_results);

	error = gnsdk_playlist_results_release(h_results);
	if (error) { throw GnError(); }

	return retVal;
}


/*-----------------------------------------------------------------------------
 *  GenerateMoreLikeThis
 */
GnPlaylistResult
GnPlaylistCollection::GenerateMoreLikeThis(const GnUser& user, const metadata::GnDataObject& playlistSeed) throw (GnError)
{
	gnsdk_playlist_results_handle_t h_results = GNSDK_NULL;
	gnsdk_error_t                   error;

	error = gnsdk_playlist_generate_morelikethis(user.native(), get<gnsdk_playlist_collection_handle_t>(), playlistSeed.native(), &h_results);
	if (error) { throw GnError(); }

	GnPlaylistResult retVal(h_results);

	error = gnsdk_playlist_results_release(h_results);
	if (error) { throw GnError(); }

	return retVal;
}






/*-----------------------------------------------------------------------------
 *  JoinSearchByName
 */
GnPlaylistCollection
GnPlaylistCollection::JoinFindByName(gnsdk_cstr_t collectionName) const throw (GnError)
{
	gnsdk_playlist_collection_handle_t coll = GNSDK_NULL;
	gnsdk_error_t                      error;

	error = gnsdk_playlist_collection_join_get_by_name(get<gnsdk_playlist_collection_handle_t>(), collectionName, &coll);
	if (error) { throw GnError(); }

	GnPlaylistCollection tmp(coll);

	gnsdk_handle_release(coll);
	return tmp;
}


/*-----------------------------------------------------------------------------
 *  Join
 */
void
GnPlaylistCollection::Join(const GnPlaylistCollection& toJoin) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_join(get<gnsdk_playlist_collection_handle_t>(), toJoin.get<gnsdk_playlist_collection_handle_t>() );
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  JoinRemove
 */
void
GnPlaylistCollection::JoinRemove(const GnPlaylistCollection& toRemove) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_join_remove(get<gnsdk_playlist_collection_handle_t>(), toRemove.Name() );
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  GnPlaylistMoreLikeThisOptions
 */

static gnsdk_uint32_t
_get_mltoption(gnsdk_playlist_collection_handle_t handle, gnsdk_cstr_t key)
{
	gnsdk_cstr_t  value = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_playlist_morelikethis_option_get(handle, key, &value);
	if (error) { throw GnError(); }

	return gnstd::gn_atoi(value);
}


/*-----------------------------------------------------------------------------
 *  _set_mltoption
 */
static void
_set_mltoption(gnsdk_playlist_collection_handle_t handle, gnsdk_cstr_t key, gnsdk_uint32_t value)
{
	char buffer[16];
	gnsdk_error_t error;

	gracenote::gnstd::gn_itoa(buffer, 16, value);

	error = gnsdk_playlist_morelikethis_option_set(handle, key, buffer);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  MaxTracks
 */
gnsdk_uint32_t
GnPlaylistMoreLikeThisOptions::MaxTracks() const throw (GnError)
{
	return _get_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS);
}


/*-----------------------------------------------------------------------------
 *  MaxTracks
 */
void
GnPlaylistMoreLikeThisOptions::MaxTracks(gnsdk_uint32_t value) throw (GnError)
{
	return _set_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_TRACKS, value);
}


/*-----------------------------------------------------------------------------
 *  MaxPerArtist
 */
gnsdk_uint32_t
GnPlaylistMoreLikeThisOptions::MaxPerArtist() const throw (GnError)
{
	return _get_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST);
}


/*-----------------------------------------------------------------------------
 *  MaxPerArtist
 */
void
GnPlaylistMoreLikeThisOptions::MaxPerArtist(gnsdk_uint32_t value) throw (GnError)
{
	return _set_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ARTIST, value);
}


/*-----------------------------------------------------------------------------
 *  MaxPerAlbum
 */
gnsdk_uint32_t
GnPlaylistMoreLikeThisOptions::MaxPerAlbum() const throw (GnError)
{
	return _get_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM);
}


/*-----------------------------------------------------------------------------
 *  MaxPerAlbum
 */
void
GnPlaylistMoreLikeThisOptions::MaxPerAlbum(gnsdk_uint32_t value) throw (GnError)
{
	return _set_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_MAX_PER_ALBUM, value);
}


/*-----------------------------------------------------------------------------
 *  RandomSeed
 */
gnsdk_uint32_t
GnPlaylistMoreLikeThisOptions::RandomSeed() const throw (GnError)
{
	return _get_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOMSEED);
}


/*-----------------------------------------------------------------------------
 *  RandomSeed
 */
void
GnPlaylistMoreLikeThisOptions::RandomSeed(gnsdk_uint32_t value) throw (GnError)
{
	return _set_mltoption(weakhandle_, GNSDK_PLAYLIST_MORELIKETHIS_OPTION_RANDOMSEED, value);
}


/*-----------------------------------------------------------------------------
 *  Serialize
 */
gnsdk_size_t
GnPlaylistCollection::Serialize(gnsdk_byte_t* buffer, gnsdk_size_t buffer_sz) const throw (GnError)
{
	gnsdk_size_t  sz = buffer_sz;
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_serialize(get<gnsdk_playlist_collection_handle_t>(), buffer, &sz);
	if (error) { throw GnError(); }

	return sz;
}


/*-----------------------------------------------------------------------------
 *  CollectionSerializeSize
 */
gnsdk_size_t
GnPlaylistCollection::SerializeSize() const throw (GnError)
{
	gnsdk_size_t sz = 0;
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_serialize_size(get<gnsdk_playlist_collection_handle_t>(), &sz);
	if (error) { throw GnError(); }

	return sz;
}


/*-----------------------------------------------------------------------------
 *  PeformSyncProcess
 */
void
GnPlaylistCollection::SyncProcessExecute(IGnPlaylistCollectionSyncEvents& syncEvents) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_sync_process(this->get<gnsdk_playlist_collection_handle_t>(), IGnPlaylistCollectionSyncEvents::_collection_sync, &syncEvents);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  AddForSyncProcess
 */
void
GnPlaylistCollection::SyncProcessAdd(gnsdk_cstr_t mediaIdentifier) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_sync_ident_add(this->get<gnsdk_playlist_collection_handle_t>(), mediaIdentifier);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  _add
 */
void
_add(gnsdk_playlist_collection_handle_t handle, gnsdk_cstr_t mediaIdentifier, gnsdk_gdo_handle_t gdo) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_collection_add_gdo(handle, mediaIdentifier, gdo);
	if (error) { throw GnError(); }
}


/* ***************************************************************************************************************************** */
/* GnPlaylist Collection Storage Provider */
/* ***************************************************************************************************************************** */

collection_storage_provider::collection_storage_provider() : buffer_(GNSDK_NULL)
{ }


collection_storage_provider::~collection_storage_provider()
{
	if (buffer_)
		delete[] buffer_;
}


collection_storage_provider::collection_storage_provider(const collection_storage_provider& copy) : buffer_(GNSDK_NULL)
{
	if (copy.buffer_ && copy.buffer_[0] != GNSDK_NULL) {
		buffer_ = new char[BUFFER_SZ];
		gnstd::gn_strcpy(buffer_, BUFFER_SZ, copy.buffer_);

	}
}


/*-----------------------------------------------------------------------------
 *  operator =
 */
collection_storage_provider&
collection_storage_provider::operator = (const collection_storage_provider& copy)
{
	if (copy.buffer_ && copy.buffer_[0] != GNSDK_NULL )
	{
		buffer_ = new char[BUFFER_SZ];
		gnstd::gn_strcpy(buffer_, BUFFER_SZ, copy.buffer_);
	}
	return *this;
}



/*-----------------------------------------------------------------------------
 *  get_data
 */
gnsdk_cstr_t
collection_storage_provider::get_data(gnsdk_uint32_t pos)
{
	gnsdk_error_t error;
	// top test.
	if (pos == GN_UINT32_MAX) {
		return gnstd::kEmptyString;
	}

	// lazy construction. 
	if (!buffer_ ) {
		buffer_ = new char[BUFFER_SZ];
	}

	error = gnsdk_playlist_storage_enum_collections(pos, buffer_, BUFFER_SZ);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }
	
	if (error) 
	{
		buffer_[0] = GNSDK_NULL;
		return gnstd::kEmptyString;
	}
	return buffer_;
}
gnsdk_uint32_t
collection_storage_provider::count() const 
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t error = gnsdk_playlist_storage_count_collections(&count);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }
	return count;
}

/* ***************************************************************************************************************************** */
/* GnPlaylist Attribute Provider */
/* ***************************************************************************************************************************** */
gnsdk_cstr_t
attribute_provider::get_data(gnsdk_uint32_t pos) const
{
	gnsdk_cstr_t  attr_name = gnstd::kEmptyString;
	gnsdk_error_t error;

	if (weak_handle_)
		error = gnsdk_playlist_collection_attributes_enum(weak_handle_, pos, &attr_name);
	else
		error = gnsdk_playlist_attributes_enum(pos, &attr_name);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return attr_name;
}


/*-----------------------------------------------------------------------------
 *  count
 */
gnsdk_uint32_t
attribute_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	if (weak_handle_)
		error = gnsdk_playlist_collection_attributes_count(weak_handle_, &count);
	else
		error = gnsdk_playlist_attributes_count(&count);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return count;
}


/* ***************************************************************************************************************************** */
/* IGnPlaylistCollectionSyncEvents */
/* ***************************************************************************************************************************** */

void
IGnPlaylistCollectionSyncEvents::_collection_sync(gnsdk_void_t*                      callback_data,
												  gnsdk_playlist_collection_handle_t handle,
												  gnsdk_cstr_t                       ident,
												  gnsdk_playlist_status_t            status,
												  gnsdk_bool_t*                      p_cancel
												  )
{
	IGnPlaylistCollectionSyncEvents* events = reinterpret_cast<IGnPlaylistCollectionSyncEvents*>( callback_data );
	GnPlaylistCollection             coll(handle);
	GnPlaylistEventsIdentiferStatus  cppStatus = kIdentifierStatusUnknown;
	gn_canceller                     canceller;

	switch ( status )
	{
	case gnsdk_playlist_status_unknown:
		cppStatus = kIdentifierStatusUnknown;
		break;

	case gnsdk_playlist_status_new_ident:
		cppStatus = kIdentifierStatusNew;
		break;

	case gnsdk_playlist_status_old_ident:
		cppStatus = kIdentifierStatusOld;
		break;
	}

	events->OnUpdate(coll, GnPlaylistIdentifier(ident, coll.Name() ), cppStatus, canceller);

	if (canceller.IsCancelled())
	{
		*p_cancel = GNSDK_TRUE;
	}
}


/* ***************************************************************************************************************************** */
/* GnPlaylistStorage */
/* ***************************************************************************************************************************** */


/*-----------------------------------------------------------------------------
 *  CollectionStore
 */
GnPlaylistStorage::GnPlaylistStorage ()
{
	_gnsdk_internal::module_initialize(GNSDK_MODULE_PLAYLIST);
}


/*-----------------------------------------------------------------------------
 *  Store
 */
void
GnPlaylistStorage::Store(const GnPlaylistCollection& collection) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_storage_store_collection(collection.get<gnsdk_playlist_collection_handle_t>() );
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  CollectionLoad
 */
GnPlaylistCollection
GnPlaylistStorage::Load(storage_iterator itr) throw (GnError)
{
	gnsdk_playlist_collection_handle_t coll_handle = GNSDK_NULL;
	gnsdk_error_t                      error;

	error = gnsdk_playlist_storage_load_collection(*itr, &coll_handle);
	if (error) { throw GnError(); }

	GnPlaylistCollection tmp(coll_handle);

	gnsdk_handle_release(coll_handle);

	return tmp;

}


/*-----------------------------------------------------------------------------
 *  CollectionLoad
 */
GnPlaylistCollection
GnPlaylistStorage::Load(gnsdk_cstr_t collectionName) throw (GnError)
{
	gnsdk_playlist_collection_handle_t coll_handle = GNSDK_NULL;
	gnsdk_error_t                      error;

	error = gnsdk_playlist_storage_load_collection(collectionName, &coll_handle);
	if (error) { throw GnError(); }

	GnPlaylistCollection tmp(coll_handle);

	gnsdk_handle_release(coll_handle);

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  StorageRemove
 */
void
GnPlaylistStorage::Remove(const GnPlaylistCollection& collection) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_storage_remove_collection(collection.Name() );
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageRemove
 */
void
GnPlaylistStorage::Remove(gnsdk_cstr_t collectionName) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_storage_remove_collection(collectionName);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageLocation
 */
void
GnPlaylistStorage::Location(gnsdk_cstr_t location) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_storage_location_set(location);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageCompact
 */
void
GnPlaylistStorage::Compact() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_playlist_storage_compact();
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageIsValid
 */
GnError
GnPlaylistStorage::IsValid() const
{
	gnsdk_error_info_t error_info;
	gnsdk_error_t      error;

	error = gnsdk_playlist_storage_validate(&error_info);
	if (error)
		return GnError();

	return GnError(&error_info);
}



#endif

