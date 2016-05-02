/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_LINK_HPP_
#define _GNSDK_LINK_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"
#include "gnsdk_list.hpp"
#include "metadata_music.hpp"

namespace gracenote
{
	namespace link
	{
#if GNSDK_LINK

		class GnLink;
		class GnLinkContent;

		/**
		 * GnImagePreference
		 */
		enum GnImagePreference
		{
			/**
			 * Retrieve exact size as specified by GnImageSize
			 */
			exact = 1,

			/**
			 * Retrieve exact or smaller size as specified by GnImageSize
			 */
			largest,

			/**
			 * Retrieve exact or larger size as specified by GnImageSize
			 */
			smallest

		};

		/**
		 *  Indicates available content types that can be retrieved for Albums, Lyrics, Tracks, Video
		 *  Products, Contributors, Works, Seasons, or Series (or some combination of these object types). Not
		 *  all content types are available for all objects.
		 */
		enum GnLinkContentType
		{
			/** @internal kLinkContentUnknown @endinternal
			 *
			 *   Indicates an invalid content type.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentUnknown = 0,

			/** @internal kLinkContentCoverArt @endinternal
			 *
			 *   Retrieves cover artwork; this is Album-level and Video Product-level
			 *   content.
			 *
			 *   Use with #GNSDK_GDO_TYPE_ALBUM and #GNSDK_GDO_TYPE_VIDEO_PRODUCT.
			 *
			 *   Do not use with #GNSDK_GDO_TYPE_VIDEO_WORK,
			 *   #GNSDK_GDO_TYPE_VIDEO_SERIES, #GNSDK_GDO_TYPE_VIDEO_SEASON, or
			 *   #GNSDK_GDO_TYPE_CONTRIBUTOR.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentCoverArt,

			/** @internal kLinkContentGenreArt @endinternal
			 *
			 *   Retrieves artwork for the object's primary genre; this is Album-level
			 *   and Track-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentGenreArt,

			/** @internal kLinkContentReview @endinternal
			 *
			 *   Retrieves a review for the object; this is Album-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentReview,

			/** @internal kLinkContentBiography @endinternal
			 *
			 *   Retrieves a biography for the object; this is Album-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentBiography,

			/** @internal kLinkContentArtistNews @endinternal
			 *
			 *   Retrieves news for the artist; this is Album-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentArtistNews,

			/** @internal kLinkContentLyricXML @endinternal
			 *
			 *   Retrieves lyrics in XML form; this is Lyric-level and Track-level
			 *   data.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentLyricXML,

			/** @internal kLinkContentLyricText @endinternal
			 *
			 *   Retrieves lyrics in plain text form; this is Lyric-level and
			 *   Track-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentLyricText,

			/** @internal kLinkContentDspData @endinternal
			 *
			 *   Retrieves DSP content; this is Track-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentDspData,

			/** @internal kLinkContentCommentsListener @endinternal
			 *
			 *   Retrieves listener comments; this is Album-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentCommentsListener,

			/** @internal kLinkContentCommentsRelease @endinternal
			 *
			 *   Retrieves new release comments; this is Album-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentCommentsRelease,

			/** @internal kLinkContentNews @endinternal
			 *
			 *   Retrieves news for the object; this is Album-level content.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentNews,

			/** @internal kLinkContentImage @endinternal
			 *
			 *   Retrieves an image for specific Video types.
			 *
			 *   Use with #GNSDK_GDO_TYPE_VIDEO_WORK, #GNSDK_GDO_TYPE_VIDEO_SERIES,
			 *   #GNSDK_GDO_TYPE_VIDEO_SEASON, and video #GNSDK_GDO_TYPE_CONTRIBUTOR.
			 *
			 *   Do not use with #GNSDK_GDO_TYPE_VIDEO_PRODUCT.
			 *
			 *   Note: At the time of this guide's publication, support for Video
			 *   Explore Seasons and Series image retrieval through Seasons, Series, and
			 *   Works queries is limited. Contact your Gracenote Professional Services
			 *   representative for updates on the latest supported images.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentImage,

			/** @internal kLinkContentImageArtist @endinternal
			 * Retrieves an artist image for the object; this can be album-level or contributor-level content.
			 * Use with #GNSDK_GDO_TYPE_ALBUM or #GNSDK_GDO_TYPE_CONTRIBUTOR.
			 * There are three ways to retrieve an artist image:
			 * <ul><li>If the GDO is the result of an album match, you can retrieve the artist image from the album GDO.</li>
			 * <li>If the GDO is the result of an album match, you can retrieve a contributor GDO from the album GDO,
			 * and then retrieve the artist image from the contributor GDO.</li>
			 * <li>If the GDO is the result of a contributor match, which can only come from a local text query,
			 * you can use the GDO to retrieve the artist image from the local image database.
			 * However, you cannot retrieve the artist image from the online database using this GDO.</li></ul>
			 *
			 * The GDO used to retrieve an artist image can be the full object or a recently deserialized object.
			 *
			 *   Note: At the time of this guide's publication, the available Album
			 *   artist images are limited. Contact your Gracenote Professional Services
			 *   representative for updates on the latest supported images.
			 * @ingroup Link_TypesEnums
			 */
			kLinkContentImageArtist

		};

		/** @internal GnLinkDataType @endinternal
		 *  Indicates possible data formats for the retrieved content.
		 * @ingroup Link_TypesEnums
		 */
		enum GnLinkDataType
		{
			/** @internal kLinkDataUnknown @endinternal
			 *
			 *   Indicates an invalid data type.
			 * @ingroup Link_TypesEnums
			 */
			kLinkDataUnknown     = 0,

			/** @internal kLinkDataTextPlain @endinternal
			 *
			 *   Indicates the content buffer contains plain text data (null terminated).
			 * @ingroup Link_TypesEnums
			 */
			kLinkDataTextPlain   = 1,

			/** @internal kLinkDataTextXML @endinternal
			 *
			 *   Indicates the content buffer contains XML data (null terminated).
			 * @ingroup Link_TypesEnums
			 */
			kLinkDataTextXML     = 2,

			/** @internal kLinkDataNumber @endinternal
			 *
			 *   Indicates the content buffer contains a numerical value
			 *   (gnsdk_uint32_t). Unused.
			 * @ingroup Link_TypesEnums
			 */
			kLinkDataNumber      = 10,

			/** @internal kLinkDataImageJpeg @endinternal
			 *
			 *   Indicates the content buffer contains jpeg image data.
			 * @ingroup Link_TypesEnums
			 */
			kLinkDataImageJpeg   = 20,


			/** @internal kLinkDataImagePng @endinternal
			 *
			 *   Indicates the content buffer contains png image data.
			 * @ingroup Link_TypesEnums
			 */
			kLinkDataImagePng    = 30,


			/** @internal kLinkDataImageBinary @endinternal
			 *
			 *   Indicates the content buffer contains externally defined binary data.
			 * @ingroup Link_TypesEnums
			 */
			kLinkDataImageBinary = 100

		};

		class GnLinkOptions
		{
		public:
			GNWRAPPER_ANNOTATE

			/** Set this link query lookup mode.
			* @param lookupMode		Lookup mode
			*/
			void
			LookupMode(GnLookupMode lookupMode) throw (GnError);
			
			/**
			 *  Explicitly identifies the track of interest by its ordinal number. This option takes precedence
			 *   over any provided by track indicator.
			 * @ingroup Link_OptionKeys
			 */
			void
			TrackOrdinal(gnsdk_uint32_t number) throw (GnError);
			
			/**
			 *  This option sets the source provider of the content (for example, "Acme").
			 * @ingroup Link_OptionKeys
			 */
			void
			DataSource(gnsdk_cstr_t datasource) throw (GnError);
			
			/**
			 *  This option sets the type of the provider content (for example, "cover").
			 * @ingroup Link_OptionKeys
			 */
			void
			DataType(gnsdk_cstr_t datatype) throw (GnError);
			
			/**
			 * This option allows setting of a specific network interface to be used with connections made by  
			 * this object. Choosing which interface to use can be beneficial for systems with multiple 
			 * network interfaces. Without setting this option, connections will be made of the default network interface
			 * as decided by the operating system.
			 *  @param ipAddress [in] local IP address for the desired network interface
			 */
			void
			NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError);

			/**
			 *  Clears all options currently set for a given Link query.
			 *  <p><b>Remarks:</b></p>
			 *  As Link query handles can be used to retrieve multiple enhanced data items, it may be appropriate
			 *   to specify different options between data retrievals. You can use this function to clear all options
			 *   before setting new ones.
			 * @ingroup Link_QueryFunctions
			 */
			void
			Clear() throw (GnError);
			
		protected:
			GnLinkOptions() : weakhandle_(GNSDK_NULL) {}

			DISALLOW_COPY_AND_ASSIGN(GnLinkOptions);
			friend class GnLink;
			gnsdk_link_query_handle_t weakhandle_;
		};
		
		/**
		 * GnLink
		 */
		class GnLink : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnLink(const metadata::GnDataObject& gnDataObject, const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

			GnLink(const GnListElement& listElement, const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

			virtual
			~GnLink();

			/**
			 * Retrieves the Link library version string.
			 * This API can be called at any time, after getting GnManager instance successfully. The returned
			 * string is a constant. Do not attempt to modify or delete.
			 *
			 * Example: <code>1.2.3.123</code> (Major.Minor.Improvement.Build)<br>
			 * Major: New functionality<br>
			 * Minor: New or changed features<br>
			 * Improvement: Improvements and fixes<br>
			 * Build: Internal build number<br>
			 */
			static gnsdk_cstr_t
			Version();

			/**
			 *  Retrieves Link library build date string.
			 *  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting GnManager instance successfully. The returned
			 *  string is a constant. Do not attempt to modify or delete.
			 *  Example build date string: 2008-02-12 00:41 UTC
			 */
			static gnsdk_cstr_t
			BuildDate();

			/**
			 * Retrieves count for the specified content
			 * @param contentType Type of content to count
			 * @return Count
			 * <p><b>Remarks:</b></p>
			 * <code>Count()</code> can be called repeatedly on the same GnLink object with
			 * different content type requests to
			 * retrieve the count for differing values of content type.
			 */
			gnsdk_uint32_t
			Count(GnLinkContentType contentType) throw (GnError);

			
			GnLinkOptions&  Options() { return options_;}

			/* image contents */

			/**
			 * Retrieves CoverArt data.
			 * @param imageSize size of the image to retrieve
			 * @param imagePreference image retrieval preference
			 * @param item_ord Nth CoverArt
			 * @return GnLinkContent
			 *  <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different size and ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			CoverArt(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves GenreArt data.
			 * @param imageSize size of the image to retrieve
			 * @param imagePreference image retrieval preference
			 * @param item_ord Nth GenreArt
			 * @return GnLinkContent
			 *  <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different size and ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			GenreArt(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves Image data.
			 * @param imageSize size of the image to retrieve
			 * @param imagePreference image retrieval preference
			 * @param item_ord  Nth Image
			 * @return GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different size and ordinal parameters
			 * @ingroup Link_QueryFunctions
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			Image(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves ArtistImage data.
			 * @param  imageSize size of the image to retrieve
			 * @param imagePreference image retrieval preference
			 * @param item_ord Nth ArtistImage
			 * @return  GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different size and ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			ArtistImage(GnImageSize imageSize, GnImagePreference imagePreference, gnsdk_uint32_t item_ord = 1) throw (GnError);

			/* text contents */

			/**
			 * Retrieves Review data.
			 * @param item_ord Nth Review
			 * @return  GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			Review(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves Biography data.
			 * @param item_ord [in] Nth Biography
			 * @return GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			Biography(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves AristNews data.
			 * @param item_ord Nth AristNews
			 * @return GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			ArtistNews(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves LyricXML data.
			 * @param item_ord Nth LyricXML
			 * @return  GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			LyricXML(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves LyricText data.
			 * @param item_ord Nth LyricText
			 * @return  GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			LyricText(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves CommentsListener data.
			 * @param item_ord [in] Nth CommentsListener
			 * @return GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			CommentsListener(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves CommentsRelease data.
			 * @param item_ord [in] Nth CommentsRelease
			 * @return GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			CommentsRelease(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/**
			 * Retrieves News data.
			 * @param item_ord Nth News
			 * @return GnLinkContent
			 * <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			News(gnsdk_uint32_t item_ord = 1) throw (GnError);

			/* binary contents */

			/**
			 * Retrieves DspData data.
			 * @param item_ord Nth DspData
			 * @return GnLinkContent
			 *  <p><b>Remarks:</b></p>
			 * This API can be called repeatedly on the same link query handle with
			 * different ordinal parameters
			 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
			 */
			GnLinkContent
			DspData(gnsdk_uint32_t item_ord = 1) throw (GnError);

			IGnStatusEvents* EventHandler() { return eventhandler_;}

			/*-----------------------------------------------------------------------------
			** IGnCancellable members
			*/
			virtual void
			SetCancel(bool bCancel)
			{
				cancelled_ = bCancel;
			}

			virtual bool
			IsCancelled()
			{
				return cancelled_;
			}

		private:
			IGnStatusEvents*    eventhandler_;
			GnLinkOptions       options_;
			bool				cancelled_;

			/* disallow assignment operator */
			DISALLOW_COPY_AND_ASSIGN(GnLink);
		};


		/**
		 * GnLinkContent
		 */
		class GnLinkContent : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnLinkContent();
			GnLinkContent(const gnsdk_byte_t* contentData, gnsdk_size_t dataSize, GnLinkContentType contentType, GnLinkDataType dataType) throw (GnError);

			virtual
			~GnLinkContent();

			/**
			 * Copy content data to provided buffer (must be of at least DataSize() )
			 * @param pre_allocaled_byte_buffer
			 */
			void
			DataBuffer(gnsdk_byte_t* pre_allocated_byte_buffer);      /* deprecate */

			/**
			 * Retrieves content data buffer
			 */
			const void*
			ContentData() const;

			/**
			 * Retrieves content data buffer size
			 */
			gnsdk_size_t
			DataSize() const;

			/**
			 * Retrieves content data type
			 */
			GnLinkDataType
			DataType() const;


		private:

			gnsdk_link_content_type_t mContentType;
			gnsdk_link_data_type_t    mDataType;
			const gnsdk_byte_t*       mData;
			gnsdk_size_t              mDataSize;
		};


#endif /* GNSDK_LINK */

	}

}
#endif /* _GNSDK_LINK_HPP_ */

