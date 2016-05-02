/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_video.cpp
 *
 * Implementation of C++ wrapper for GNSDK Video
 *
 */
#include "gnsdk_manager.hpp"
#include "gnsdk_convert.hpp"

#if GNSDK_VIDEO

#include "gnsdk_video.hpp"

using namespace gracenote;
using namespace gracenote::video;
using namespace gracenote::metadata;


static metadata::GnResponseVideoProduct		_intFindProduct(gnsdk_video_query_handle_t handle) throw (GnError) ;
static metadata::GnResponseVideoWork		_intFindWorks(gnsdk_video_query_handle_t handle) throw (GnError);
static metadata::GnResponseVideoSeasons		_intFindSeasons(gnsdk_video_query_handle_t handle) throw (GnError);
static metadata::GnResponseVideoSeries		_intFindSeries(gnsdk_video_query_handle_t handle) throw (GnError);
static metadata::GnResponseContributors		_intFindContributors(gnsdk_video_query_handle_t handle) throw (GnError);
static metadata::GnResponseVideoObjects		_intFindObjects(gnsdk_video_query_handle_t handle) throw (GnError);
static metadata::GnResponseVideoSuggestions	_intFindSuggestions(gnsdk_video_query_handle_t handle) throw (GnError);

static void			_intSetExternalId(gnsdk_video_query_handle_t handle, gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError);
static gnsdk_cstr_t	_MapSearchField(GnVideoSearchField searchField);

static void GNSDK_CALLBACK_API
_video_callback_status(void* callback_data, gnsdk_status_t status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t*  p_abort);



/**
 * GnVideoOptions
 */

/**
 *  OptionResultPreferLanguage
 */
void
GnVideoOptions::ResultPreferLanguage(GnLanguage preferredLanguage) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_PREFERRED_LANG, gnconvert::_convertLangCppC(preferredLanguage));
	if (error) { throw GnError(); }
}


/**
 *  ResultRangeStart
 */
void
GnVideoOptions::ResultRangeStart(gnsdk_uint32_t resultStart) throw (GnError)
{
	char          buffer[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buffer, sizeof(buffer), resultStart);
	error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_RESULT_RANGE_START, buffer);
	if (error) { throw GnError(); }
}


/**
 *  ResultCount
 */
void
GnVideoOptions::ResultCount(gnsdk_uint32_t resultCount) throw (GnError)
{
	char          buffer[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buffer, sizeof(buffer), resultCount);
	error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_RESULT_RANGE_SIZE, buffer);
	if (error) { throw GnError(); }
}


/**
 *  OptionLookupData
 */
void
GnVideoOptions::LookupData(GnLookupData lookupData, bool bEnable) throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t  sz_enable;

	if (bEnable)
	{
		sz_enable = GNSDK_VALUE_TRUE;
	}
	else
	{
		sz_enable = GNSDK_VALUE_FALSE;
	}

	switch (lookupData)
	{
		case kLookupDataContent:
			error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_ENABLE_CONTENT_DATA, sz_enable);
			break;

		case kLookupDataExternalIds:
			error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_ENABLE_EXTERNAL_IDS, sz_enable);
			break;

		case kLookupDataClassical:
		case kLookupDataSonicData:
		case kLookupDataPlaylist:
		case kLookupDataGlobalIds:
		case kLookupDataAdditionalCredits:
		default:
			return;
	}

	if (error) { throw GnError(); }
}


/**
 *  OptionQueryNoCache
 */
void
GnVideoOptions::QueryNoCache(bool bNoCache) throw (GnError)
{
	gnsdk_error_t error;

	if (bNoCache)
	{
		error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_QUERY_NOCACHE, GNSDK_VALUE_TRUE);
	}
	else
	{
		error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_QUERY_NOCACHE, GNSDK_VALUE_FALSE);
	}

	if (error) { throw GnError(); }
}


/**
 *  OptionQueryCommerceType
 */
void
GnVideoOptions::QueryCommerceType(bool bEnableCommerceType) throw (GnError)
{
	gnsdk_error_t error;

	if (bEnableCommerceType)
	{
		error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_QUERY_ENABLE_COMMERCE_TYPE, GNSDK_VALUE_TRUE);
	}
	else
	{
		error = gnsdk_video_query_option_set(weakhandle_, GNSDK_VIDEO_OPTION_QUERY_ENABLE_COMMERCE_TYPE, GNSDK_VALUE_FALSE);
	}

	if (error) { throw GnError(); }
}


/**
 *  OptionResultFilter
 */
void
GnVideoOptions::ResultFilter(GnVideoListElementFilterType listElementFilterType, const gracenote::GnListElement& listElement, bool bInclude) throw (GnError)
{
	gnsdk_cstr_t  filter_key = GNSDK_NULL;
	gnsdk_error_t error;

	switch (listElementFilterType)
	{
		case kListElementFilterGenre:
			filter_key = bInclude ? GNSDK_VIDEO_FILTER_KEY_GENRE_INCLUDE : GNSDK_VIDEO_FILTER_KEY_GENRE_EXCLUDE;
			break;

		case kListElementFilterProductionType:
			filter_key = bInclude ? GNSDK_VIDEO_FILTER_KEY_PRODUCTION_TYPE_INCLUDE : GNSDK_VIDEO_FILTER_KEY_PRODUCTION_TYPE_EXCLUDE;
			break;

		case kListElementFilterSerialType:
			filter_key = bInclude ? GNSDK_VIDEO_FILTER_KEY_SERIAL_TYPE_INCLUDE : GNSDK_VIDEO_FILTER_KEY_SERIAL_TYPE_EXCLUDE;
			break;

		case kListElementFilterOrigin:
			filter_key = bInclude ? GNSDK_VIDEO_FILTER_KEY_ORIGIN_INCLUDE : GNSDK_VIDEO_FILTER_KEY_ORIGIN_EXCLUDE;
			break;

		default:
			break;
	}

	error = gnsdk_video_query_set_filter_by_list_element(weakhandle_, filter_key, listElement.native() );
	if (error) { throw GnError(); }
}


/**
 *  OptionResultFilter
 */
void
GnVideoOptions::ResultFilter(GnVideoFilterType filterType, gnsdk_cstr_t filterValue) throw (GnError)
{
	gnsdk_cstr_t  filter_key = GNSDK_NULL;
	gnsdk_error_t error;

	switch (filterType)
	{
		case kFilterSeasonNumber:
			filter_key = GNSDK_VIDEO_FILTER_KEY_SEASON_NUM;
			break;

		case kFilterSeasonEpisodeNumber:
			filter_key = GNSDK_VIDEO_FILTER_KEY_SEASON_EPISODE_NUM;
			break;

		case kFilterSeriesEpisodeNumber:
			filter_key = GNSDK_VIDEO_FILTER_KEY_SERIES_EPISODE_NUM;
			break;

		default:
			break;
	}

	error = gnsdk_video_query_set_filter(weakhandle_, filter_key, filterValue);
	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  NetworkInterface
 */
void
GnVideoOptions::NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_video_query_option_set(weakhandle_, GNSDK_QUERY_OPTION_NETWORK_INTERFACE, ipAddress);
	if (error) { throw GnError(); }
}

/**
 *  Custom
 */
void
GnVideoOptions::Custom(gnsdk_cstr_t optionKey, gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_video_query_option_set(weakhandle_, optionKey, value);
	if (error) { throw GnError(); }
}


/******************************************************************************
** GnVideo
*/
GnVideo::GnVideo(const GnUser& user, IGnStatusEvents* pEventHandler) throw (GnError) :
	eventhandler_(pEventHandler), cancelled_(false)
{
	gnsdk_video_query_handle_t	query_handle = GNSDK_NULL;
	gnsdk_error_t				error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_VIDEO);

	error = gnsdk_video_query_create(user.native(), _video_callback_status, this, &query_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(query_handle);

	options_.weakhandle_ = query_handle;
}


GnVideo::GnVideo(const GnUser& user, const GnLocale& locale, IGnStatusEvents* pEventHandler) throw (GnError) :
	eventhandler_(pEventHandler), cancelled_(false)
{
	gnsdk_video_query_handle_t	query_handle = GNSDK_NULL;
	gnsdk_error_t				error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_VIDEO);

	error = gnsdk_video_query_create(user.native(), _video_callback_status, this, &query_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(query_handle);

	error = gnsdk_video_query_set_locale(query_handle, locale.native());
	if (error) { throw GnError(); }

	options_.weakhandle_ = query_handle;
}


GnVideo::~GnVideo()
{
}


/**
 *  Version
 */
gnsdk_cstr_t
GnVideo::Version()
{
	return gnsdk_video_get_version();
}


/**
 *  BuildDate
 */
gnsdk_cstr_t
GnVideo::BuildDate()
{
	return gnsdk_video_get_build_date();
}


/**
 *  FindProducts by GnVideoProduct
 */
GnResponseVideoProduct
GnVideo::FindProducts(const GnVideoProduct& videoProduct) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoProduct.native() );
	if (error) { throw GnError(); }

	return _intFindProduct(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindProducts by GnVideoWork
 */
GnResponseVideoProduct
GnVideo::FindProducts(const GnVideoWork& videoWork) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoWork.native() );
	if (error) { throw GnError(); }

	return _intFindProduct(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindProducts by GnDataObject
 */
GnResponseVideoProduct
GnVideo::FindProducts(const GnDataObject& gnObj) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), gnObj.native() );
	if (error) { throw GnError(); }

	return _intFindProduct(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindProducts by text
 */
GnResponseVideoProduct
GnVideo::FindProducts(gnsdk_cstr_t search_text, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError)
{
	gnsdk_cstr_t  field_key;
	gnsdk_error_t error;

	field_key = _MapSearchField(searchField);

	error = gnsdk_video_query_set_text(get<gnsdk_video_query_handle_t>(), field_key, search_text, (gnsdk_video_search_type_t)searchType);
	if (error) { throw GnError(); }

	return _intFindProduct(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindProducts by TOC
 */
GnResponseVideoProduct
GnVideo::FindProducts(gnsdk_cstr_t videoTOC, GnVideoTOCFlag TOCFlag) throw (GnError)
{
	gnsdk_uint32_t toc_flag = GNSDK_NULL;
	gnsdk_error_t  error;

	cancelled_ = false;

	switch (TOCFlag)
	{
	case kTOCFlagDefault:
		toc_flag = GNSDK_VIDEO_TOC_FLAG_DEFAULT;
		break;

	case kTOCFlagPal:
		toc_flag = GNSDK_VIDEO_TOC_FLAG_PAL;
		break;

	case kTOCFlagAngles:
		toc_flag = GNSDK_VIDEO_TOC_FLAG_ANGLES;
		break;

	default:
		break;
	}

	error = gnsdk_video_query_set_toc_string(get<gnsdk_video_query_handle_t>(), videoTOC, toc_flag);
	if (error) { throw GnError(); }

	return _intFindProduct(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindProducts by external ID
 */
GnResponseVideoProduct
GnVideo::FindProducts(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError)
{
	cancelled_ = false;

	_intSetExternalId(get<gnsdk_video_query_handle_t>(), externalId, externalIdType);
	return _intFindProduct(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindWorks by GnVideoProduct
 */
GnResponseVideoWork
GnVideo::FindWorks(const GnVideoProduct& videoProduct) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoProduct.native() );
	if (error) { throw GnError(); }

	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindWorks by GnVideoWork
 */
GnResponseVideoWork
GnVideo::FindWorks(const GnVideoWork& videoWork) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoWork.native() );
	if (error) { throw GnError(); }

	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindWorks by GnContributor
 */
GnResponseVideoWork
GnVideo::FindWorks(const GnContributor& contributor) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), contributor.native() );
	if (error) { throw GnError(); }

	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindWorks by GnVideoSeason
 */
GnResponseVideoWork
GnVideo::FindWorks(const GnVideoSeason& videoSeason) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeason.native() );
	if (error) { throw GnError(); }

	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindWorks by GnVideoSeries
 */
GnResponseVideoWork
GnVideo::FindWorks(const GnVideoSeries& videoSeries) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeries.native() );
	if (error) { throw GnError(); }

	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindWorks by GnDataObject
 */
GnResponseVideoWork
GnVideo::FindWorks(const GnDataObject& gnObj) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), gnObj.native() );
	if (error) { throw GnError(); }

	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindWorks by text search
 */
GnResponseVideoWork
GnVideo::FindWorks(gnsdk_cstr_t search_text, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError)
{
	gnsdk_cstr_t  field_key;
	gnsdk_error_t error;

	cancelled_ = false;

	field_key = _MapSearchField(searchField);

	error = gnsdk_video_query_set_text(get<gnsdk_video_query_handle_t>(), field_key, search_text, (gnsdk_video_search_type_t)searchType);
	if (error) { throw GnError(); }

	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindWorks by external ID
 */
GnResponseVideoWork
GnVideo::FindWorks(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError)
{
	cancelled_ = false;

	_intSetExternalId(get<gnsdk_video_query_handle_t>(), externalId, externalIdType);
	return _intFindWorks(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindSeasons by GnVideoWork
 */
GnResponseVideoSeasons
GnVideo::FindSeasons(const GnVideoWork& videoWork) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoWork.native() );
	if (error) { throw GnError(); }

	return _intFindSeasons(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeasons by GnContributor
 */
GnResponseVideoSeasons
GnVideo::FindSeasons(const GnContributor& contributor) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), contributor.native() );
	if (error) { throw GnError(); }

	return _intFindSeasons(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindSeasons by GnVideoSeason
 */
GnResponseVideoSeasons
GnVideo::FindSeasons(const GnVideoSeason& videoSeason) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeason.native() );
	if (error) { throw GnError(); }

	return _intFindSeasons(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeasons by GnVideoSeries
 */
GnResponseVideoSeasons
GnVideo::FindSeasons(const GnVideoSeries& videoSeries) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeries.native() );
	if (error) { throw GnError(); }

	return _intFindSeasons(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeasons by GnDataObject
 */
GnResponseVideoSeasons
GnVideo::FindSeasons(const GnDataObject& gnObj) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), gnObj.native() );
	if (error) { throw GnError(); }

	return _intFindSeasons(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeasons
 */
GnResponseVideoSeasons
GnVideo::FindSeasons(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError)
{
	cancelled_ = false;

	_intSetExternalId(get<gnsdk_video_query_handle_t>(), externalId, externalIdType);
	return _intFindSeasons(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindSeries by GnVideoWork
 */
GnResponseVideoSeries
GnVideo::FindSeries(const GnVideoWork& videoWork) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoWork.native() );
	if (error) { throw GnError(); }

	return _intFindSeries(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeries by GnContributor
 */
GnResponseVideoSeries
GnVideo::FindSeries(const GnContributor& contributor) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), contributor.native() );
	if (error) { throw GnError(); }

	return _intFindSeries(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeries by GnVideoSeason
 */
GnResponseVideoSeries
GnVideo::FindSeries(const GnVideoSeason& videoSeason) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeason.native() );
	if (error) { throw GnError(); }

	return _intFindSeries(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeries by GnVideoSeries
 */
GnResponseVideoSeries
GnVideo::FindSeries(const GnVideoSeries& videoSeries) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeries.native() );
	if (error) { throw GnError(); }

	return _intFindSeries(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeries by GnDataObject
 */
GnResponseVideoSeries
GnVideo::FindSeries(const GnDataObject& gnObj) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), gnObj.native() );
	if (error) { throw GnError(); }

	return _intFindSeries(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSeries by text search
 */
GnResponseVideoSeries
GnVideo::FindSeries(gnsdk_cstr_t textInput, GnVideoSearchType searchType) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_text(get<gnsdk_video_query_handle_t>(), GNSDK_VIDEO_SEARCH_FIELD_SERIES_TITLE, textInput, (gnsdk_video_search_type_t)searchType);
	if (error) { throw GnError(); }

	return _intFindSeries(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindSeries by external ID
 */
GnResponseVideoSeries
GnVideo::FindSeries(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError)
{
	cancelled_ = false;

	_intSetExternalId(get<gnsdk_video_query_handle_t>(), externalId, externalIdType);
	return _intFindSeries(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindContributors by GnVideoWork
 */
GnResponseContributors
GnVideo::FindContributors(const GnVideoWork& videoWork) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoWork.native() );
	if (error) { throw GnError(); }

	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindContributors by GnContributor
 */
GnResponseContributors
GnVideo::FindContributors(const GnContributor& contributor) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), contributor.native() );
	if (error) { throw GnError(); }

	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindContributors by GnVideoSeason
 */
GnResponseContributors
GnVideo::FindContributors(const GnVideoSeason& videoSeason) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeason.native() );
	if (error) { throw GnError(); }

	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindContributors by GnVideoSeries
 */
GnResponseContributors
GnVideo::FindContributors(const GnVideoSeries& videoSeries) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), videoSeries.native() );
	if (error) { throw GnError(); }

	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindContributors by GnDataObject
 */
GnResponseContributors
GnVideo::FindContributors(const GnDataObject& gnObj) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), gnObj.native() );
	if (error) { throw GnError(); }

	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindContributors by text search
 */
GnResponseContributors
GnVideo::FindContributors(gnsdk_cstr_t textInput, GnVideoSearchType searchType) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_text(get<gnsdk_video_query_handle_t>(), GNSDK_VIDEO_SEARCH_FIELD_CONTRIBUTOR_NAME, textInput, (gnsdk_video_search_type_t)searchType);
	if (error) { throw GnError(); }

	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}

GnResponseContributors
GnVideo::FindContributors(gnsdk_cstr_t searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError)
{
	gnsdk_cstr_t  field_key;
	gnsdk_error_t error;

	cancelled_ = false;

	field_key = _MapSearchField(searchField);

	error = gnsdk_video_query_set_text(get<gnsdk_video_query_handle_t>(), field_key, searchText, (gnsdk_video_search_type_t)searchType);
	if (error) { throw GnError(); }

	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindContributors by external ID
 */
GnResponseContributors
GnVideo::FindContributors(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError)
{
	cancelled_ = false;

	_intSetExternalId(get<gnsdk_video_query_handle_t>(), externalId, externalIdType);
	return _intFindContributors(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindObjects
 */
GnResponseVideoObjects
GnVideo::FindObjects(const GnDataObject& gnObj) throw (GnError)
{
	gnsdk_error_t error;

	cancelled_ = false;

	error = gnsdk_video_query_set_gdo(get<gnsdk_video_query_handle_t>(), gnObj.native() );
	if (error) { throw GnError(); }

	return _intFindObjects(get<gnsdk_video_query_handle_t>());
}


/**
 *  FindObjects
 */
GnResponseVideoObjects
GnVideo::FindObjects(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError)
{
	cancelled_ = false;

	_intSetExternalId(get<gnsdk_video_query_handle_t>(), externalId, externalIdType);
	return _intFindObjects(get<gnsdk_video_query_handle_t>());
}

/**
 *  FindSuggestions
 */
GnResponseVideoSuggestions
GnVideo::FindSuggestions(gnsdk_cstr_t searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError)
{
	gnsdk_cstr_t  field_key;
	gnsdk_error_t error;

	cancelled_ = false;

	field_key = _MapSearchField(searchField);

	error = gnsdk_video_query_set_text(get<gnsdk_video_query_handle_t>(), field_key, searchText, (gnsdk_video_search_type_t)searchType);
	if (error) { throw GnError(); }

	return _intFindSuggestions(get<gnsdk_video_query_handle_t>());
}


/*-----------------------------------------------------------------------------
 *  _intFindSuggestions
 */
GnResponseVideoSuggestions
_intFindSuggestions(gnsdk_video_query_handle_t handle) throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;
	gnsdk_error_t      error;

	error = gnsdk_video_query_find_suggestions(handle, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseVideoSuggestions tmp = GnResponseVideoSuggestions(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  _intFindObjects
 */
GnResponseVideoObjects
_intFindObjects(gnsdk_video_query_handle_t handle) throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;
	gnsdk_error_t      error;

	error = gnsdk_video_query_find_objects(handle, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseVideoObjects tmp = GnResponseVideoObjects(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  _intFindContributors
 */
GnResponseContributors
_intFindContributors(gnsdk_video_query_handle_t handle) throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;
	gnsdk_error_t      error;

	error = gnsdk_video_query_find_contributors(handle, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseContributors tmp = GnResponseContributors(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  _intFindSeries
 */
GnResponseVideoSeries
_intFindSeries(gnsdk_video_query_handle_t handle) throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;
	gnsdk_error_t      error;

	error = gnsdk_video_query_find_series(handle, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseVideoSeries tmp = GnResponseVideoSeries(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  _intFindSeasons
 */
GnResponseVideoSeasons
_intFindSeasons(gnsdk_video_query_handle_t handle) throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;

	gnsdk_error_t   error = gnsdk_video_query_find_seasons(handle, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseVideoSeasons tmp = GnResponseVideoSeasons(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  _intFindWorks
 */
GnResponseVideoWork
_intFindWorks(gnsdk_video_query_handle_t handle) throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;
	gnsdk_error_t      error;

	error = gnsdk_video_query_find_works(handle, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseVideoWork tmp = GnResponseVideoWork(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  _intFindProduct
 */
GnResponseVideoProduct
_intFindProduct(gnsdk_video_query_handle_t handle) throw (GnError)
{
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;
	gnsdk_error_t      error;

	error = gnsdk_video_query_find_products(handle, &response_gdo);
	if (error) { throw GnError(); }

	GnResponseVideoProduct tmp = GnResponseVideoProduct(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}


/*-----------------------------------------------------------------------------
 *  _intSetExternalId
 */
void
_intSetExternalId(gnsdk_video_query_handle_t handle, gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError)
{
	gnsdk_cstr_t  id_key = GNSDK_NULL;
	gnsdk_error_t error;

	switch (externalIdType)
	{
	case kExternalIdTypeISAN:
		id_key = GNSDK_VIDEO_EXTERNAL_ID_TYPE_ISAN;
		break;

	case kExternalIdTypeUPC:
		id_key = GNSDK_VIDEO_EXTERNAL_ID_TYPE_UPC;
		break;

	default:
		break;
	}

	error = gnsdk_video_query_set_external_id(handle, externalId, id_key, GNSDK_VIDEO_EXTERNAL_ID_SOURCE_DEFAULT);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  _MapSearchField
 */
gnsdk_cstr_t
_MapSearchField(GnVideoSearchField searchField)
{
	gnsdk_cstr_t field_key = GNSDK_NULL;

	switch (searchField)
	{
	case kSearchFieldContributorName:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_CONTRIBUTOR_NAME;
		break;

	case kSearchFieldCharacterName:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_CHARACTER_NAME;
		break;

	case kSearchFieldWorkFranchise:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_WORK_FRANCHISE;
		break;

	case kSearchFieldWorkSeries:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_WORK_SERIES;
		break;

	case kSearchFieldWorkTitle:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_WORK_TITLE;
		break;

	case kSearchFieldProductTitle:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_PRODUCT_TITLE;
		break;

	case kSearchFieldSeriesTitle:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_SERIES_TITLE;
		break;

	case kSearchFieldAll:
		field_key = GNSDK_VIDEO_SEARCH_FIELD_ALL;
		break;

	default:
		break;
	}

	return field_key;
}


/*-----------------------------------------------------------------------------
 *  _video_callback_status
 */
void GNSDK_CALLBACK_API
_video_callback_status(void*          callback_data,
					   gnsdk_status_t status,
					   gnsdk_uint32_t percent_complete,
					   gnsdk_size_t   bytes_total_sent,
					   gnsdk_size_t   bytes_total_received,
					   gnsdk_bool_t*  p_abort
					   )
{
	GnVideo*		p_video = (GnVideo*)callback_data;

	if (p_video->EventHandler())
	{
		if (!p_video->IsCancelled())
		{
			gn_canceller	canceller;

			p_video->EventHandler()->StatusEvent((GnStatus)status, percent_complete, bytes_total_sent, bytes_total_received, canceller);
			if (canceller.IsCancelled() || p_video->IsCancelled())
			{
				*p_abort = GNSDK_TRUE;
			}
		}
	}
}


#endif /* GNSDK_VIDEO */

