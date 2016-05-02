/**
 * Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */
 
 /**
 * @file metadata_epg.hpp
 */

#ifndef _GNSDK_METADATA_ACR_HPP_
#define _GNSDK_METADATA_ACR_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "metadata_epg.hpp"
#include "metadata_music.hpp"
 /**
 * \namespace gracenote
 */

namespace gracenote
{
#if GNSDK_ACR



     /**
     * \namespace metadata
     */
	namespace metadata
	{
		// forward declaration
		class GnAcrMatch;
		typedef gn_facade_range_iterator<GnAcrMatch, gn_gdo_provider<GnAcrMatch> >           acr_iterator;
		typedef gn_iterable_container<GnAcrMatch, gn_gdo_provider<GnAcrMatch> >				acr_iterable;

		/**
		 * \class GnVideoAdvert
		 * Class for video advertisement metadata
		 */
		class GnVideoAdvert: public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoAdvert, GNSDK_GDO_TYPE_VIDEO_ADVERT);

			/**
			 * Constructs an empty GnVideoAdvert object
			 */
			GnVideoAdvert() { }

			/**
			 * Constructs a GnVideoAdvert object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnVideoAdvert(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnVideoAdvert() { }

			/**
			 * Retrieves the Gracenote Tui (title-unique identifier)
			 * @return Tui
			 */
			gnsdk_cstr_t 
			Tui() const 
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}
			/**
			 * Retrieves the Gracenote Tui Tag
			 * @return Tui Tag
			 */
			gnsdk_cstr_t 
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 * Retrieves the Gracenote unique identifier.
			 * @return Gracenote unique identifier
			 */
			gnsdk_cstr_t 
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 * Indicates whether the video advertisement response result is full (not partial). 
			 */
			bool
			IsFullResult() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FULL_RESULT);
				return gnstd::gn_strtobool(return_value);
			}

			
			/**
			 * Retrieves the official title.
			 * @return Title
			 */
			GnTitle     
			Title() const 
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}
			
			/**
			 * Retrieves the brand name.
			 * @return Name
			 */
			GnName		
			Brand() const
			{
				return ChildGet<GnName>(GNSDK_GDO_CHILD_NAME_BRAND);
			}

			/**
			 * Retrieves the iterator for external identifiers.
			 * @return Iterator
			 */
			externalid_iterable ExternalIds() const
			{
				return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}
		};


 	   /**
		* \class GnAcrMatch
		* Class for Automatic Content Recognition match response
		*/
		class GnAcrMatch : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnAcrMatch, GNSDK_GDO_TYPE_MATCH_ACR);
			
			GnAcrMatch() { }

			GnAcrMatch(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnAcrMatch() { }

			/**
			 *	Match position
			 *	@ingroup GDO_ValueKeys_ACR
			 */
			gnsdk_uint32_t
			MatchPosition() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCH_POSITION_MS);
				return gnstd::gn_atoi(return_value);
			}
		   
            /**
			 * Current position in milliseconds of the matched track.
			 * The current position tracks the approximate real time position of the
			 * playing content 
			 * @return Current position in milliseconds
			 */
			gnsdk_uint32_t
			CurrentPosition() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_CURRENT_POSITION_MS);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 * The date this content was ingested into the Gracenote Service 
			 * Uses ISO 8601 Date format, e.g. 2014-01-01T00:00:01,000000000
			 * @return fingerprint creation date 
			 */
			gnsdk_cstr_t
			FingerprintCreationDate() const
			{
				return StringValue(GNSDK_GDO_VALUE_FP_CREATION_DATE);
			}

			/**
			 *	Official title
			 *	@ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *	Subtitle. Used primarily with TV programs.
			 *	@ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			Subtitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_SUBTITLE);
			}

			/**
			 * Video work
			 */
            GnVideoWork 
			AvWork() const 
            {
                return ChildGet<GnVideoWork>(GNSDK_GDO_CHILD_VIDEO_WORK);
            }
            
			/**
			 * TV airing
			 */
            GnTVAiring 
			TvAiring() const 
            {
                return ChildGet<GnTVAiring>(GNSDK_GDO_CHILD_TVAIRING);
            }

			/*
			* Video Advert 
			*/
			GnVideoAdvert 
			AvAdvert() const 
			{
				 return ChildGet<GnVideoAdvert>(GNSDK_GDO_CHILD_VIDEO_ADVERT);
			}

			/*
			 * Album
			 */
			GnAlbum
			Album() const
			{
				 return ChildGet<GnAlbum>(GNSDK_GDO_CHILD_ALBUM);
			}

			/**
			 * Retrieves the iterator for external identifiers associated with this fingerprint match.
			 */
			externalid_iterable ExternalIds() const
			{
				return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}
		};

	   /**
		*  \class GnResponseAcrMatch
		*
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseAcrMatch : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseAcrMatch, GNSDK_GDO_TYPE_RESPONSE_ACR);

			GnResponseAcrMatch() { }
			GnResponseAcrMatch(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseAcrMatch() { }

			/**
			 *  Total number of result matches
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the first result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the last result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Estimated total number of results possible.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Iterator for child acr products.
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child	acr product to retrieve.
			 * @ingroup GDO_ChildKeys_ACR
			 */
			acr_iterable AcrMatches() const
			{
				return acr_iterable(gn_gdo_provider<GnAcrMatch> (*this, GNSDK_GDO_CHILD_MATCH_ACR), GN_GDO_START);
			}

		};

	
	} // namespace metadata
#endif // GNSDK_ACR
}     // namespace gracenote

#endif // _GNSDK_METADATA_ACR_HPP_
