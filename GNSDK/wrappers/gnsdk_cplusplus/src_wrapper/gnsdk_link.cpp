/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* link.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk_manager.hpp"

#if GNSDK_LINK

#include "gnsdk_link.hpp"
#include "metadata_music.hpp"

using namespace gracenote;
using namespace gracenote::link;
using namespace gracenote::metadata;

static void GNSDK_CALLBACK_API
_CallbackStatus(void* callback_data, gnsdk_status_t status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t* p_abort);

static gnsdk_cstr_t _MapImgSizeToCstr(GnImageSize imgSize);

static GnLinkContent _GnImageArt(gnsdk_link_query_handle_t handle, GnImageSize imageSize, GnImagePreference imagePreference, GnLinkContentType linkContentType, gnsdk_uint32_t item_ord) throw (GnError);

/******************************************************************************
 ** GnLinkOptions
 */

/*-----------------------------------------------------------------------------
 *  OptionLookupMode
 */
void
GnLinkOptions::LookupMode(gracenote::GnLookupMode lookupMode) throw (GnError)
{
	gnsdk_cstr_t  lookup_mode_value = GNSDK_NULL;
	gnsdk_error_t error;
	
	switch (lookupMode)
	{
		case kLookupModeLocal:
			lookup_mode_value = GNSDK_LOOKUP_MODE_LOCAL;
			break;
			
		case kLookupModeOnline:
			lookup_mode_value = GNSDK_LOOKUP_MODE_ONLINE;
			break;
			
		case kLookupModeOnlineCacheOnly:
			lookup_mode_value = GNSDK_LOOKUP_MODE_ONLINE_CACHEONLY;
			break;
			
		case kLookupModeOnlineNoCache:
			lookup_mode_value = GNSDK_LOOKUP_MODE_ONLINE_NOCACHE;
			break;
			
		case kLookupModeOnlineNoCacheRead:
			lookup_mode_value = GNSDK_LOOKUP_MODE_ONLINE_NOCACHEREAD;
			break;
			
		default:
			break;
	}
	
	error = gnsdk_link_query_option_set(weakhandle_, GNSDK_LINK_OPTION_LOOKUP_MODE, lookup_mode_value);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  OptionTrackOrd
 */
void
GnLinkOptions::TrackOrdinal(gnsdk_uint32_t ordinal) throw (GnError)
{
	gnsdk_error_t error;
	char buffer[12] = {0};
	gnstd::gn_itoa(buffer, 12, ordinal);
	error = gnsdk_link_query_option_set(weakhandle_, GNSDK_LINK_OPTION_KEY_TRACK_ORD, buffer);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  OptionDataSource
 */
void
GnLinkOptions::DataSource(gnsdk_cstr_t datasource) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_link_query_option_set(weakhandle_, GNSDK_LINK_OPTION_KEY_DATASOURCE, datasource);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  OptionDataType
 */
void
GnLinkOptions::DataType(gnsdk_cstr_t datatype) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_link_query_option_set(weakhandle_, GNSDK_LINK_OPTION_KEY_DATATYPE, datatype);
	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  NetworkInterface
 */
void
GnLinkOptions::NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_link_query_option_set(weakhandle_, GNSDK_QUERY_OPTION_NETWORK_INTERFACE, ipAddress);
	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  ClearOptions
 */
void
GnLinkOptions::Clear() throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_link_query_options_clear(weakhandle_);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  _MapImgSizeToCstr
 */
gnsdk_cstr_t
_MapImgSizeToCstr
(GnImageSize imgSize)
{
	gnsdk_cstr_t coverSize = GNSDK_NULL;
	
	switch (imgSize)
	{
	case kImageSize75:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_75;
		break;

	case kImageSize110:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_110;
		break;

	case kImageSize170:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_170;
		break;

	case kImageSize220:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_220;
		break;

	case kImageSize300:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_300;
		break;

	case kImageSize450:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_450;
		break;

	case kImageSize720:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_720;
		break;

	case kImageSize1080:
		coverSize = GNSDK_LINK_OPTION_VALUE_IMAGE_SIZE_1080;
		break;

	case kImageSizeUnknown:
		coverSize = GNSDK_NULL;
		break;
	}
	
	return coverSize;
}


/******************************************************************************
** GnLink
*/
GnLink::GnLink(const GnDataObject& gnDataObject, const GnUser& user, IGnStatusEvents* pEventHandler)  throw (GnError) :
	eventhandler_(pEventHandler), cancelled_(false)
{
	gnsdk_link_query_handle_t	query_handle = GNSDK_NULL;
	gnsdk_error_t				error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_LINK);

	error = gnsdk_link_query_create(user.native(), _CallbackStatus, this, &query_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(query_handle);

	error = gnsdk_link_query_set_gdo(query_handle, gnDataObject.native() );
	if (error) { throw GnError(); }
	
	options_.weakhandle_ = query_handle;
}


GnLink::GnLink(const GnListElement& listElement, const GnUser& user, IGnStatusEvents* pEventHandler)  throw (GnError) :
	eventhandler_(pEventHandler), cancelled_(false)
{
	gnsdk_link_query_handle_t	query_handle = GNSDK_NULL;
	gnsdk_error_t				error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_LINK);

	error = gnsdk_link_query_create(user.native(), _CallbackStatus, this, &query_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(query_handle);

	error = gnsdk_link_query_set_list_element(query_handle, listElement.native() );
	if (error) { throw GnError(); }
	
	 options_.weakhandle_ = query_handle;
}


GnLink::~GnLink()
{
}


/*-----------------------------------------------------------------------------
 *  Version
 */
gnsdk_cstr_t
GnLink::Version()
{
	return gnsdk_link_get_version();
}


/*-----------------------------------------------------------------------------
 *  BuildDate
 */
gnsdk_cstr_t
GnLink::BuildDate()
{
	return gnsdk_link_get_build_date();
}



/*-----------------------------------------------------------------------------
 *  _CallbackStatus
 */
void GNSDK_CALLBACK_API
_CallbackStatus(void* callback_data, gnsdk_status_t link_status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t* p_abort)
{
	GnLink* p_link = (GnLink*)callback_data;

	if (p_link->EventHandler())
	{
		if (!p_link->IsCancelled())
		{
			gn_canceller	canceller;

			p_link->EventHandler()->StatusEvent((GnStatus)link_status, percent_complete, bytes_total_sent, bytes_total_received, canceller);
			if (canceller.IsCancelled() || p_link->IsCancelled())
			{
				*p_abort = GNSDK_TRUE;
			}
		}
	}
}


/*-----------------------------------------------------------------------------
 *  _GnImageArt
 */
GnLinkContent
_GnImageArt(gnsdk_link_query_handle_t handle, GnImageSize imageSize, GnImagePreference imagePreference, GnLinkContentType linkContentType, gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_int32_t          img_size         = (gnsdk_int32_t)imageSize;
	gnsdk_error_t          error;


	if (imagePreference == exact)
	{
		error = gnsdk_link_query_option_set(handle, GNSDK_LINK_OPTION_KEY_IMAGE_SIZE, _MapImgSizeToCstr(imageSize) );
		if (error) { throw GnError(); }
	}
	else if (imagePreference == largest)
	{
		// zero is invalid kImageSizeUnknown
		while (img_size > 0)
		{
			error = gnsdk_link_query_option_set(handle, GNSDK_LINK_OPTION_KEY_IMAGE_SIZE, _MapImgSizeToCstr( (GnImageSize)img_size) );
			if (error) { throw GnError(); }

			img_size--;
		}
	}
	else if (imagePreference == smallest)
	{
		while (img_size <= kImageSize1080)
		{
			error = gnsdk_link_query_option_set(handle, GNSDK_LINK_OPTION_KEY_IMAGE_SIZE, _MapImgSizeToCstr( (GnImageSize)img_size) );
			if (error) { throw GnError(); }

			img_size++;
		}
	}

	error = gnsdk_link_query_content_retrieve(handle, (gnsdk_link_content_type_t)linkContentType, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, (GnLinkContentType)linkContentType, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  CoverArt
 */
GnLinkContent
GnLink::CoverArt(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	return _GnImageArt(get<gnsdk_link_query_handle_t>(), imageSize, imagePreference, kLinkContentCoverArt, itemOrdinal);
}


/*-----------------------------------------------------------------------------
 *  GenreArt
 */
GnLinkContent
GnLink::GenreArt(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	return _GnImageArt(get<gnsdk_link_query_handle_t>(), imageSize, imagePreference, kLinkContentGenreArt, itemOrdinal);
}


/*-----------------------------------------------------------------------------
 *  Image
 */
GnLinkContent
GnLink::Image(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	return _GnImageArt(get<gnsdk_link_query_handle_t>(), imageSize, imagePreference, kLinkContentImage, itemOrdinal);
}


/*-----------------------------------------------------------------------------
 *  ArtistImage
 */
GnLinkContent
GnLink::ArtistImage(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	return _GnImageArt(get<gnsdk_link_query_handle_t>(), imageSize, imagePreference, kLinkContentImageArtist, itemOrdinal);
}


/*-----------------------------------------------------------------------------
 *  Review
 */
GnLinkContent
GnLink::Review(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_review, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentReview, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  Biography
 */
GnLinkContent
GnLink::Biography(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_biography, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentBiography, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  ArtistNews
 */
GnLinkContent
GnLink::ArtistNews(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_artist_news, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentArtistNews, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  LyricXML
 */
GnLinkContent
GnLink::LyricXML(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_lyric_xml, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentLyricXML, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  LyricText
 */
GnLinkContent
GnLink::LyricText(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_lyric_text, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentLyricText, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  DspData
 */
GnLinkContent
GnLink::DspData(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_dsp_data, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentDspData, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  CommentsListener
 */
GnLinkContent
GnLink::CommentsListener(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_comments_listener, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentCommentsListener, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  CommentsRelease
 */
GnLinkContent
GnLink::CommentsRelease(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_comments_release, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentCommentsRelease, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  News
 */
GnLinkContent
GnLink::News(gnsdk_uint32_t itemOrdinal) throw (GnError)
{
	gnsdk_link_data_type_t buffer_data_type = gnsdk_link_data_unknown;
	gnsdk_byte_t*          buffer           = GNSDK_NULL;
	gnsdk_size_t           buffer_size      = 0;
	gnsdk_error_t          error;

	error = gnsdk_link_query_content_retrieve(get<gnsdk_link_query_handle_t>(), gnsdk_link_content_news, itemOrdinal, &buffer_data_type, &buffer, &buffer_size);
	if (error) { throw GnError(); }

	return GnLinkContent(buffer, buffer_size, kLinkContentNews, (GnLinkDataType)buffer_data_type);
}


/*-----------------------------------------------------------------------------
 *  Count
 */
gnsdk_uint32_t
GnLink::Count(GnLinkContentType contentType) throw (GnError)
{
	gnsdk_uint32_t count = 0;

	gnsdk_error_t error = gnsdk_link_query_content_count(get<gnsdk_link_query_handle_t>(), (gnsdk_link_content_type_t)contentType, &count);
	if (error) { throw GnError(); }

	return count;
}


/*-----------------------------------------------------------------------------
 *  GnLinkContent
 */
GnLinkContent::GnLinkContent() :
	mContentType(gnsdk_link_content_unknown), mDataType(gnsdk_link_data_unknown), mData(GNSDK_NULL), mDataSize(0)
{
}


/*-----------------------------------------------------------------------------
 *  GnLinkContent
 */
GnLinkContent::GnLinkContent(const gnsdk_byte_t* contentData, gnsdk_size_t dataSize, GnLinkContentType contentType, GnLinkDataType dataType) throw (GnError) :
	GnObject((gnsdk_handle_t)contentData), mContentType((gnsdk_link_content_type_t)contentType), mDataType((gnsdk_link_data_type_t)dataType), mData(contentData), mDataSize(dataSize)
{ }


/*-----------------------------------------------------------------------------
 *  DataBuffer
 */
void
GnLinkContent::DataBuffer(gnsdk_byte_t* contentData)
{
	gnsdk_uint32_t i = 0;

	for (i = 0; i < mDataSize; i++)
	{
		contentData[i] = ((const unsigned char*)mData)[i];
	}
}


/*-----------------------------------------------------------------------------
 *  ContentData
 */
const void*
GnLinkContent::ContentData() const
{
	return mData;
}


/*-----------------------------------------------------------------------------
 *  DataSize
 */
gnsdk_size_t
GnLinkContent::DataSize() const
{
	return mDataSize;
}


/*-----------------------------------------------------------------------------
 *  DataType
 */
GnLinkDataType
GnLinkContent::DataType() const
{
	return (GnLinkDataType)mDataType;
}


GnLinkContent::~GnLinkContent()
{
}


#endif /* GNSDK_LINK */

