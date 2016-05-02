/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_tastepersona.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk.hpp"

#if GNSDK_TASTE

#include "metadata.hpp"
#include "gnsdk_taste.hpp"

using namespace gracenote;
using namespace gracenote::taste;

static gnsdk_taste_action_t _MapAction(GnPersonaAction action);


/* ****************************************************************************	*/
/* GnPersonaOptions - Functions													*/
/* ****************************************************************************	*/
/*-----------------------------------------------------------------------------
 *  OptionCustom
 */
void
GnPersonaOptions::Custom(gnsdk_cstr_t option, gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_persona_option_set(weakhandle_, option, value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  OptionCustom
 */
void
GnPersonaOptions::Custom(gnsdk_cstr_t option, bool bEnable) throw (GnError)
{
	gnsdk_error_t error;

	if (bEnable)
	{
		error = gnsdk_taste_persona_option_set(weakhandle_, option, GNSDK_VALUE_TRUE);
	}
	else
	{
		error = gnsdk_taste_persona_option_set(weakhandle_, option, GNSDK_VALUE_FALSE);
	}

	if (error) { throw GnError(); }
}


/* ****************************************************************************	*/
/* GnTasteChannel - Functions														*/
/* ****************************************************************************	*/
GnTasteChannelComponent
channel_component_provider::get_data(gnsdk_uint32_t pos) throw (GnError)
{
	gnsdk_list_element_handle_t listelemhandle;
	gnsdk_flt32_t               weight;
	gnsdk_error_t               error = GNSDK_SUCCESS;

	if (pos < GN_UINT32_MAX)
	{
		error = gnsdk_taste_channel_component_enum(weakhandle_, component_, pos, &listelemhandle, &weight);
		if (GNSDKERR_SEVERE(error)) { throw GnError(); }
		if (!error)
		{
			GnListElement elem(listelemhandle);
			gnsdk_handle_release(listelemhandle);
			return GnTasteChannelComponent(elem, weight);
		}
	}
	return GnTasteChannelComponent();
}


/*-----------------------------------------------------------------------------
 *  count
 */
gnsdk_uint32_t
channel_component_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	error = gnsdk_taste_channel_component_count(weakhandle_, component_, &count);
	if ( GNSDKERR_SEVERE(error)) { throw GnError(); }

	return count;
}


/*-----------------------------------------------------------------------------
 *  GnTasteChannel
 */

/*-----------------------------------------------------------------------------
 *  GnTasteChannel
 */
GnTasteChannel::GnTasteChannel(gnsdk_taste_channel_handle_t handle)  throw (GnError) :
	GnObject(handle)
{ }


/*-----------------------------------------------------------------------------
 *  ObservationCount
 */
gnsdk_uint32_t
GnTasteChannel::ObservationCount() throw (GnError)
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	error = gnsdk_taste_channel_observation_count(this->get<gnsdk_taste_channel_handle_t>(), &count);
	if (error) { throw GnError(); }

	return count;
}


/*-----------------------------------------------------------------------------
 *  PdlStatement
 */
gnsdk_cstr_t
GnTasteChannel::PdlStatement(bool b_friendly) throw (GnError)
{
	gnsdk_uint32_t flags = GNSDK_TASTE_PDL_RENDER_STANDARD;
	gnsdk_cstr_t   pdl   = GNSDK_NULL;
	gnsdk_error_t  error;

	if (b_friendly)
		flags = GNSDK_TASTE_PDL_RENDER_FRIENDLY;

	error = gnsdk_taste_channel_pdl_get(this->get<gnsdk_taste_channel_handle_t>(), flags, &pdl);
	if (error) { throw GnError(); }

	return pdl;
}


/* ****************************************************************************	*/
/* channel_provider - Functions												*/
/* ****************************************************************************	*/

GnTasteChannel
taste_channel_provider::get_data(gnsdk_uint32_t pos)
{
	gnsdk_taste_channel_handle_t channelhandle = GNSDK_NULL;
	if (pos < GN_UINT32_MAX)
	{
		gnsdk_error_t error = gnsdk_taste_channelset_channel_enum(weakhandle_, pos, &channelhandle);
		if ( GNSDKERR_SEVERE(error)) { throw GnError(); }
	}
	GnTasteChannel channel(channelhandle);
	gnsdk_handle_release(channelhandle);
	return channel;
}


/*-----------------------------------------------------------------------------
 *  count
 */
gnsdk_uint32_t
taste_channel_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error = gnsdk_taste_channelset_count(weakhandle_, &count);
	if ( GNSDKERR_SEVERE(error)) { throw GnError(); }
	return count;
}


/* ***************************************************************************************************************************** */
/* GnTaste Persona Storage Provider */
/* ***************************************************************************************************************************** */

persona_storage_provider::persona_storage_provider()
{ }

/*-----------------------------------------------------------------------------
 *  get_data
 */
gnsdk_cstr_t
persona_storage_provider::get_data(gnsdk_uint32_t pos)
{
	gnsdk_cstr_t  persona_name = gnstd::kEmptyString;
	gnsdk_error_t error;
	if (pos < GN_UINT32_MAX)
	{
		error = gnsdk_taste_storage_enum_personas(pos, &persona_name);
		if (GNSDKERR_SEVERE(error)) { throw GnError(); }
		if (error)
		{
			persona_name = gnstd::kEmptyString;
		}
	}

	return persona_name;
}


/*-----------------------------------------------------------------------------
 *  count
 */
gnsdk_uint32_t
persona_storage_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	error = gnsdk_taste_storage_count_personas(&count);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return count;
}


/* ****************************************************************************	*/
/* GnTasteChannelSet - Functions												*/
/* ****************************************************************************	*/

GnTasteChannelSet::GnTasteChannelSet(gnsdk_taste_channelset_handle_t handle) throw (GnError) :
	GnObject(handle)
{ }


/* ****************************************************************************	*/
/* GnPersona - Functions														*/
/* ****************************************************************************	*/

GnPersona::GnPersona(const GnUser& user, gnsdk_cstr_t name) throw (GnError)
{
	gnsdk_taste_persona_handle_t handle;
	gnsdk_error_t                error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_TASTE);

	error = gnsdk_taste_persona_create(user.native(), name, &handle);
	if (error) { throw GnError(); }

	AcceptOwnership(handle);

	options_.weakhandle_ = handle;
}


/*-----------------------------------------------------------------------------
 *  GnPersona
 */
GnPersona::GnPersona(const GnUser& user, gnsdk_byte_t* p_buf, gnsdk_size_t size) throw (GnError)
{
	gnsdk_taste_persona_handle_t handle;
	gnsdk_error_t                error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_TASTE);

	error = gnsdk_taste_persona_deserialize(user.native(), p_buf, size, &handle);
	if (error) { throw GnError(); }

	AcceptOwnership(handle);
}


GnPersona::GnPersona(gnsdk_taste_persona_handle_t handle) :
	GnObject(handle)
{
	_gnsdk_internal::module_initialize(GNSDK_MODULE_TASTE);
	this->options_.weakhandle_ = handle;
}


/*-----------------------------------------------------------------------------
 *  Add
 */
void
GnPersona::Add(const metadata::GnAlbum& album, GnPersonaAction action) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_persona_add_gdo(get<gnsdk_taste_persona_handle_t>(), album.native(), _MapAction(action));
	if (error) { throw GnError(); }
}


#if GNSDK_PLAYLIST
/*-----------------------------------------------------------------------------
 *  Add
 */
void
GnPersona::Add(const playlist::GnPlaylistAttributes& playlistAttributes, GnPersonaAction action) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_persona_add_gdo(get<gnsdk_taste_persona_handle_t>(), playlistAttributes.native(), _MapAction(action));
	if (error) { throw GnError(); }
}
#endif /* GNSDK_PLAYLIST */


/*-----------------------------------------------------------------------------
 *  ChannelCreate
 */

GnTasteChannelSet
GnPersona::CreateChannelSet(GnLocale locale,  gnsdk_uint32_t channels) throw (GnError)
{
	gnsdk_taste_channelset_handle_t channelsethandle;
	gnsdk_error_t                   error;

	error = gnsdk_taste_channelset_create(get<gnsdk_taste_persona_handle_t>(), locale.native(), channels, &channelsethandle);
	if (error) { throw GnError(); }

	GnTasteChannelSet temp;
	temp.AcceptOwnership(channelsethandle);

	return temp;
}


/*-----------------------------------------------------------------------------
 *  Name
 */
gnsdk_cstr_t
GnPersona::Name() const throw (GnError)
{
	gnsdk_cstr_t  name;
	gnsdk_error_t error;

	error = gnsdk_taste_persona_get_name(get<gnsdk_taste_persona_handle_t>(), &name);
	if (error) { throw GnError(); }

	return name;
}


/*-----------------------------------------------------------------------------
 *  SetName
 */
void
GnPersona::SetName(gnsdk_cstr_t name) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_persona_set_name(get<gnsdk_taste_persona_handle_t>(), name);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  ObservationCount
 */
gnsdk_uint32_t
GnPersona::ObservationCount() const throw (GnError)
{
	gnsdk_error_t  error;
	gnsdk_uint32_t count = 0;

	error = gnsdk_taste_persona_observation_count(get<gnsdk_taste_persona_handle_t>(), &count);
	if (error) { throw GnError(); }

	return count;
}


/*-----------------------------------------------------------------------------
 *  Serialize
 */
gnsdk_size_t
GnPersona::Serialize(gnsdk_byte_t* p_buffer, gnsdk_size_t size) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_persona_serialize(get<gnsdk_taste_persona_handle_t>(), p_buffer, &size);
	if (error) { throw GnError(); }

	return size;
}


/*-----------------------------------------------------------------------------
 *  SerializeSize
 */
gnsdk_size_t
GnPersona::SerializeSize() throw (GnError)
{
	gnsdk_size_t  size = 0;
	gnsdk_error_t error;

	error = gnsdk_taste_persona_serialize_size(get<gnsdk_taste_persona_handle_t>(), &size);
	if (error) { throw GnError(); }

	return size;
}


/*-----------------------------------------------------------------------------
 *  _MapAction
 */
static gnsdk_taste_action_t
_MapAction(GnPersonaAction action)
{
	gnsdk_taste_action_t map = gnsdk_taste_action_default;

	switch (action)
	{
	case kPersonaActionUnknown:
		map = gnsdk_taste_action_unknown;
		break;

	case kPersonaActionAdded:
	case kPersonaActionPlayed:
	case kPersonaActionSkipped:
	case kPersonaActionLiked:
	case kPersonaActionDisliked:
		break;
	}

	return map;
}


/* ***************************************************************************************************************************** */
/* GnPersonaStorage */
/* ***************************************************************************************************************************** */


/*-----------------------------------------------------------------------------
 *  GnPersonaStorage
 */
GnPersonaStorage::GnPersonaStorage()
{
	_gnsdk_internal::module_initialize(GNSDK_MODULE_TASTE);
}


/*-----------------------------------------------------------------------------
 *  Store
 */
void
GnPersonaStorage::Store(const GnPersona& persona) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_storage_store_persona(persona.get<gnsdk_taste_persona_handle_t>() );
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Load
 */
GnPersona
GnPersonaStorage::Load(persona_storage_iterator itr) throw (GnError)
{
	gnsdk_taste_persona_handle_t h_persona = GNSDK_NULL;
	gnsdk_error_t                error;

	error = gnsdk_taste_storage_load_persona(*itr, &h_persona);
	if (error) { throw GnError(); }

	GnPersona tmp(h_persona);

	gnsdk_handle_release(h_persona);

	return tmp;

}


/*-----------------------------------------------------------------------------
 *  CollectionLoad
 */
GnPersona
GnPersonaStorage::Load(gnsdk_cstr_t collectionName) throw (GnError)
{
	gnsdk_taste_persona_handle_t h_persona = GNSDK_NULL;
	gnsdk_error_t                error;

	error = gnsdk_taste_storage_load_persona(collectionName, &h_persona);
	if (error) { throw GnError(); }

	GnPersona tmp(h_persona);

	gnsdk_handle_release(h_persona);

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  StorageRemove
 */
void
GnPersonaStorage::Remove(const GnPersona& collection) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_storage_remove_persona(collection.Name() );
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageRemove
 */
void
GnPersonaStorage::Remove(gnsdk_cstr_t collectionName) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_storage_remove_persona(collectionName);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageLocation
 */
void
GnPersonaStorage::Location(gnsdk_cstr_t location) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_storage_location_set(location);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageCompact
 */
void
GnPersonaStorage::Compact() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_taste_storage_compact();
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  StorageIsValid
 */
GnError
GnPersonaStorage::IsValid() const
{
	gnsdk_error_info_t error_info;
	gnsdk_error_t      error;

	error = gnsdk_taste_storage_validate(&error_info);
	if (error)
		return GnError();

	return GnError(&error_info);
}


/* ****************************************************************************	*/
/* GnTaste - Functions															*/
/* ****************************************************************************	*/


/*-----------------------------------------------------------------------------
 *  Version
 */
gnsdk_cstr_t
GnTaste::Version()
{
	return gnsdk_taste_get_version();
}


/*-----------------------------------------------------------------------------
 *  BuildDate
 */
gnsdk_cstr_t
GnTaste::BuildDate()
{
	return gnsdk_taste_get_build_date();
}


#endif /* GNSDK_TASTE */

