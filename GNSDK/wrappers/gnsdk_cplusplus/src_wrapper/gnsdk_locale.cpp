/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */

#include "gnsdk_locale.hpp"
#include "gnsdk_convert.hpp"

using namespace gracenote;

static void GNSDK_CALLBACK_API
_locale_status_callback(void* callback_data, gnsdk_status_t status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t* p_abort);

static GnLocaleGroup
_convertLocaleGroupCCpp( gnsdk_cstr_t c_group )
{
	GnLocaleGroup group = kLocaleGroupMusic;

	if ( gnstd::gn_strcmp( c_group, GNSDK_LOCALE_GROUP_MUSIC ) == 0 )
	{
		group = kLocaleGroupMusic;
	}
	else if ( gnstd::gn_strcmp( c_group, GNSDK_LOCALE_GROUP_VIDEO ) == 0 )
	{
		group = kLocaleGroupVideo;
	}
	else if ( gnstd::gn_strcmp( c_group, GNSDK_LOCALE_GROUP_PLAYLIST ) == 0 )
	{
		group = kLocaleGroupPlaylist;
	}
	else if ( gnstd::gn_strcmp( c_group, GNSDK_LOCALE_GROUP_EPG ) == 0 )
	{
		group = kLocaleGroupEpg;
	}

	return group;
}

static gnsdk_cstr_t
_convertGroupCppC( GnLocaleGroup descriptor )
{
	switch ( descriptor )
	{
	case kLocaleGroupInvalid:  return GNSDK_NULL;
	case kLocaleGroupMusic:    return GNSDK_LOCALE_GROUP_MUSIC;
	case kLocaleGroupVideo:    return GNSDK_LOCALE_GROUP_VIDEO;
	case kLocaleGroupPlaylist: return GNSDK_LOCALE_GROUP_PLAYLIST;
	case kLocaleGroupEpg:      return GNSDK_LOCALE_GROUP_EPG;
	}

	return GNSDK_LOCALE_GROUP_MUSIC;
}


/******************************************************************************
** GnLocale
*/
GnLocale::GnLocale(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor, const GnUser& user, IGnStatusEvents* locale_events) throw (GnError)
{
	gnsdk_locale_handle_t 	locale_handle = GNSDK_NULL;
	gnsdk_cstr_t			c_region;
	gnsdk_cstr_t			c_desc;
	gnsdk_error_t			error;

	error = gnsdk_manager_locale_load(
				_convertGroupCppC(group),
				gnconvert::_convertLangCppC(language),
				gnconvert::_convertRegionCppC(region),
				gnconvert::_convertDescCppC(descriptor),
				user.native(),
				_locale_status_callback,
				locale_events,
				&locale_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(locale_handle);

	/* must map descriptor and region as if they are "default" we need to determine what the SDK actually delivered */
	error = gnsdk_manager_locale_info(locale_handle, GNSDK_NULL, GNSDK_NULL, &c_region, &c_desc, GNSDK_NULL);
	if (error) { throw GnError(); }

	localeinfo_ = GnLocaleInfo( group ,
								language,
								gnconvert::_convertRegionCCpp(c_region),
								gnconvert::_convertDescriptorCCpp(c_desc));
}

GnLocale::GnLocale(const GnLocaleInfo& localeInfo, const GnUser& user, IGnStatusEvents* locale_events)  throw (GnError)
{
	gnsdk_locale_handle_t 	locale_handle = GNSDK_NULL;
	gnsdk_cstr_t			c_region;
	gnsdk_cstr_t			c_desc;
	gnsdk_error_t			error;
	error = gnsdk_manager_locale_load(
		_convertGroupCppC(localeInfo.Group()),
		gnconvert::_convertLangCppC(localeInfo.Language()),
		gnconvert::_convertRegionCppC(localeInfo.Region()),
		gnconvert::_convertDescCppC(localeInfo.Descriptor()),
		user.native(),
		_locale_status_callback,
		locale_events,
		&locale_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(locale_handle);

	/* must map descriptor and region as if they are "default" we need to determine what the SDK actually delivered */
	error = gnsdk_manager_locale_info(locale_handle, GNSDK_NULL, GNSDK_NULL, &c_region, &c_desc, GNSDK_NULL);
	if (error) { throw GnError(); }

	localeinfo_ = GnLocaleInfo( localeInfo.Group(),
								localeInfo.Language(),
								gnconvert::_convertRegionCCpp(c_region),
								gnconvert::_convertDescriptorCCpp(c_desc));
}

GnLocale::GnLocale(GnLocaleGroup group, gnsdk_cstr_t langIsoCode, GnRegion region, GnDescriptor descriptor, const GnUser& user, IGnStatusEvents* locale_events) throw (GnError)
{
	gnsdk_locale_handle_t 	locale_handle = GNSDK_NULL;
	gnsdk_cstr_t			c_region;
	gnsdk_cstr_t			c_desc;
	gnsdk_error_t			error;

	error = gnsdk_manager_locale_load(
				_convertGroupCppC(group),
				langIsoCode,
				gnconvert::_convertRegionCppC(region),
				gnconvert::_convertDescCppC(descriptor),
				user.native(),
				_locale_status_callback,
				locale_events,
				&locale_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(locale_handle);

	/* must map descriptor and region as if they are "default" we need to determine what the SDK actually delivered */
	error = gnsdk_manager_locale_info(locale_handle, GNSDK_NULL, GNSDK_NULL, &c_region, &c_desc, GNSDK_NULL);
	if (error) { throw GnError(); }

	localeinfo_ = GnLocaleInfo( group ,
								gnconvert::_convertLanguageCCpp(langIsoCode),
								gnconvert::_convertRegionCCpp(c_region),
								gnconvert::_convertDescriptorCCpp(c_desc));

}


GnLocale::GnLocale(gnsdk_locale_handle_t localeHandle) throw (GnError) :
	GnObject(localeHandle)
{
	gnsdk_cstr_t		c_group;
	gnsdk_cstr_t		c_language;
	gnsdk_cstr_t		c_region;
	gnsdk_cstr_t		c_desc;
	gnsdk_error_t		error;

	if (localeHandle)
	{
		/* must map descriptor and region as if they are "default" we need to determine what the SDK actually delivered */
		error = gnsdk_manager_locale_info(localeHandle, &c_group, &c_language, &c_region, &c_desc, GNSDK_NULL);
		if (error) { throw GnError(); }

		localeinfo_ = GnLocaleInfo( _convertLocaleGroupCCpp(c_group) ,
								gnconvert::_convertLanguageCCpp(c_language),
								gnconvert::_convertRegionCCpp(c_region),
								gnconvert::_convertDescriptorCCpp(c_desc));

	}
	
}


GnLocale::GnLocale(gnsdk_cstr_t serializedLocale) throw (GnError)
{
	gnsdk_locale_handle_t 	locale_handle = GNSDK_NULL;
	gnsdk_cstr_t			c_group;
	gnsdk_cstr_t			c_language;
	gnsdk_cstr_t			c_region;
	gnsdk_cstr_t			c_desc;
	gnsdk_error_t			error;

	error = gnsdk_manager_locale_deserialize(serializedLocale, &locale_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(locale_handle);

	/* do mapping of locale attributes as part of load, this way any overhead is added to deserialize overhead */
	error = gnsdk_manager_locale_info(locale_handle, &c_group, &c_language, &c_region, &c_desc, GNSDK_NULL);
	if (error) { throw GnError(); }

	localeinfo_ = GnLocaleInfo( _convertLocaleGroupCCpp(c_group) ,
								gnconvert::_convertLanguageCCpp(c_language),
								gnconvert::_convertRegionCCpp(c_region),
								gnconvert::_convertDescriptorCCpp(c_desc));

	
}


GnLocale::~GnLocale()
{
}




/*-----------------------------------------------------------------------------
 *  Revision
 */
gnsdk_cstr_t
GnLocale::Revision() const throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  value = GNSDK_NULL;

	error = gnsdk_manager_locale_info(get<gnsdk_locale_handle_t>(), GNSDK_NULL, GNSDK_NULL, GNSDK_NULL, GNSDK_NULL, &value);
	if (error) { throw GnError(); }
	return value;
}


/*-----------------------------------------------------------------------------
 *  SetGroupDefault
 */
void
GnLocale::SetGroupDefault() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_manager_locale_set_group_default(native());
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  Update
 */
bool
GnLocale::Update(const GnUser& user, IGnStatusEvents* pEventHandler) throw (GnError)
{
	gnsdk_bool_t  b_updated = GNSDK_FALSE;
	gnsdk_error_t error;

	error = gnsdk_manager_locale_update(get<gnsdk_locale_handle_t>(), user.native(), _locale_status_callback, pEventHandler, &b_updated);
	if (error) { throw GnError(); }

	if (b_updated)
	{
		return true;
	}
	return false;
}


/*-----------------------------------------------------------------------------
 *  UpdateCheck
 */
bool
GnLocale::UpdateCheck(const GnUser& user, IGnStatusEvents* pEventHandler) throw (GnError)
{
	gnsdk_bool_t  b_new_revision_available = GNSDK_FALSE;
	gnsdk_error_t error;

	error = gnsdk_manager_locale_update_check(get<gnsdk_locale_handle_t>(), user.native(), _locale_status_callback, pEventHandler, &b_new_revision_available);
	if (error) { throw GnError(); }

	if (b_new_revision_available)
	{
		return true;
	}
	return false;
}


/*-----------------------------------------------------------------------------
 *  Serialize
 */
GnString
GnLocale::Serialize() const throw (GnError)
{
	gnsdk_str_t   serializedLocale = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_manager_locale_serialize(get<gnsdk_locale_handle_t>(), &serializedLocale);
	if (error) { throw GnError(); }

	return GnString::manage(serializedLocale);
}


/*-----------------------------------------------------------------------------
 *  _locale_status_callback
 */
void GNSDK_CALLBACK_API
_locale_status_callback(void* callback_data, gnsdk_status_t mid_status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t* p_abort)
{
	IGnStatusEvents*	pEventHandler = (IGnStatusEvents*)callback_data;

	if (pEventHandler)
	{
		gn_canceller	canceller;

		pEventHandler->StatusEvent((GnStatus)mid_status, percent_complete, bytes_total_sent, bytes_total_received, canceller);
		if (canceller.IsCancelled())
		{
			*p_abort = GNSDK_TRUE;
		}
	}
}


/******************************************************************************
** locale_info_provider
*/
GnLocaleInfo
locale_info_provider::get_data(gnsdk_uint32_t pos) const throw (GnError)
{
	gnsdk_error_t error = GNSDK_SUCCESS;
	gnsdk_cstr_t  type, language, descriptor, region;

	error = gnsdk_manager_locale_available_get(pos, &type, &language, &region, &descriptor);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	if (error)
	{
		return GnLocaleInfo();
	}

	return GnLocaleInfo(
			_convertLocaleGroupCCpp(type),
			gnconvert::_convertLanguageCCpp(language),
			gnconvert::_convertRegionCCpp(region),
			gnconvert::_convertDescriptorCCpp(descriptor));
}

