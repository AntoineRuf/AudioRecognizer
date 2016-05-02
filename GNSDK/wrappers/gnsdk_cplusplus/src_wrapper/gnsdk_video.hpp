/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_VIDEO_HPP_
#define _GNSDK_VIDEO_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"
#include "gnsdk_list.hpp"
#include "metadata_video.hpp"

namespace gracenote
{
	namespace video
	{
#if GNSDK_VIDEO

		/**
		 *  The type of text search that is used to find results.
		 */
		enum GnVideoSearchType
		{
			/**
			 *   Unknown search type; the default state.
			 */
			kSearchTypeUnknown = 0,

			/**
			 *   Anchored text search, used for product title and suggestion searches.
			 *   Retrieves results that begin with the same characters as exactly
			 *   specified; for example, entering <i>dar</i>, <i>dark</i>, <i>dark k</i>,
			 *   or <i>dark kni</i> retrieves the title <i>Dark Knight,</i> but entering<i>
			 *   knight</i> will not retrieve<i> Dark Knight</i>. Note that this search
			 *   type recognizes both partial and full words.
			 */
			kSearchTypeAnchored,

			/**
			 *   Normal keyword filter search for contributor, product, and work title
			 *   searches; for example, a search using a keyword of <i>dark</i>, <i>knight</i>,
			 *   or <i>dark knight </i>retrieves the title <i>Dark Knight</i>. Note that
			 *   this search type recognizes only full words, not partial words; this
			 *   means that entering only <i>dar</i> for <i>dark</i> is not recognized.
			 */
			kSearchTypeDefault

		};

		/**
		 *  The type of text search field that is used to find results.
		 */
		enum GnVideoSearchField
		{
			/**
			 *  Contributor name search field.
			 */
			kSearchFieldContributorName = 1,

			/**
			 *  Character name search field.
			 */
			kSearchFieldCharacterName,

			/**
			 *  Work franchise search field.
			 */
			kSearchFieldWorkFranchise,

			/**
			 *  Work series search field.
			 */
			kSearchFieldWorkSeries,

			/**
			 *  Work title search field.
			 */
			kSearchFieldWorkTitle,

			/**
			 *
			 *  Product title search field.
			 */
			kSearchFieldProductTitle,

			/**
			 *
			 *  Series title search field.
			 */
			kSearchFieldSeriesTitle,

			/**
			 *  Comprehensive search field.
			 *  <p><b>Remarks:</b></p>
			 *  This option searches all relevant search fields and returns any
			 *  data found. Note, however, that you cannot use this search field for
			 *  suggestion search queries.
			 */
			kSearchFieldAll

		};

		/**
		 *  The TOC Flag type.
		 */
		enum GnVideoTOCFlag
		{
			/**
			 *  Generally recommended flag to use when setting a video TOC.
			 *  <p><b>Remarks:</b></p>
			 *  Use this flag for the TOC flag parameter that is set with the
			 *  FindProducts() API, for all general cases; this includes when using the Gracenote
			 *  Video Thin Client component to produce TOC strings.
			 *  For cases when other VideoID TOC flags seem necessary, contact Gracenote for guidance on setting
			 *  the correct flag.
			 */
			kTOCFlagDefault = 0,

			/**
			 *  Flag to indicate a given simple video TOC is from a PAL (Phase Alternating Line) disc.
			 *  <p><b>Remarks:</b></p>
			 *  Use this flag only when directed to by Gracenote. Only special video TOCs that are provided by
			 *  Gracenote and external to the
			 *  GNSDK may require this flag.
			 */
			kTOCFlagPal,

			/**
			 *  Flag to indicate a given simple video TOC contains angle data.
			 *  <p><b>Remarks:</b></p>
			 *  Use this flag only if Gracenote directs you to. Only special video TOCs that Gracenote provides
			 *  and that are external to the GNSDK may require this flag.
			 */
			kTOCFlagAngles

		};

		/**
		 *  The list element filter type.
		 */
		enum GnVideoListElementFilterType
		{
			/**
			 *  List-based filter to include/exclude genres.
			 */
			kListElementFilterGenre = 1,

			/**
			 *  List-based filter to include/exclude production types.
			 */
			kListElementFilterProductionType,

			/**
			 *  List-based filter to include/exclude serial types.
			 */
			kListElementFilterSerialType,

			/**
			 *  List-based filter to include/exclude origin.
			 */
			kListElementFilterOrigin

		};

		/**
		 *  The video filter type.
		 */
		enum GnVideoFilterType
		{
			/**
			 *  Filter for Season numbers; not list-based.
			 */
			kFilterSeasonNumber = 1,

			/**
			 *  Filter for season episode numbers; not list-based.
			 */
			kFilterSeasonEpisodeNumber,

			/**
			 *  Filter for series episode numbers; not list-based.
			 */
			kFilterSeriesEpisodeNumber

		};

		/**
		 *  The video external ID type.
		 */
		enum GnVideoExternalIdType
		{
			/**
			 *  Sets a Universal Product Code (UPC) value as an external ID for a Products query.
			 *  <p><b>Remarks:</b></p>
			 *  Use as the external ID type parameter set with the ExternalIdTypeSet() API when
			 *  providing a video UPC value for identification.
			 */
			kExternalIdTypeUPC = 1,

			/**
			 *
			 *  Sets a International Standard Audiovisual Number (ISAN) code as an external ID for a Works
			 *  query.
			 *  <p><b>Remarks:</b></p>
			 *  Use as the external ID Type parameter set with the ExternalIdTypeSet() API when
			 *   providing a video ISAN value for identification.
			 */
			kExternalIdTypeISAN

		};

	   /**
		* GnVideoOptions
		*/
		class GnVideoOptions
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Specifies the preferred language for returned results. This option applies only to TOC
			 *  Lookups.
			 *  @param preferredLanguage Set language option
			 */
			void
			ResultPreferLanguage(GnLanguage preferredLanguage) throw (GnError);

			/**
			 *  Set ordinal for the first result to be returned
			 *  @param resultStart Set the starting position for the result
			 *  <p><b>Remarks:</b></p>
			 *  This option is useful for paging through results.
			 * <p><b>Note:</b></p>
			 *   Gracenote Service limits the range size for some queries. If you specify a range size greater
			 *   than the limit, the results are constrained. Additionally, neither Gracenote Service nor GNSDK
			 *   returns an error about this behavior.
			 *  <p><b>Important:</b></p>
			 *   The number of results actually returned for a query may not equal the number of results initially
			 *   requested. To accurately iterate through results, always check the range start, end, and total
			 *   values and the responses Gracenote returns for the query (or queries). Ensure that you
			 *   are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
			 *   using the initial requested value.
			 */
			void
			ResultRangeStart(gnsdk_uint32_t resultStart) throw (GnError);

			/**
			 *  Set number of results to be returned
			 *  @param resultCount 	[in] Maximum number of results a response can return.
			 *
			 *  <p><b>Remarks:</b></p>
			 *  This option is useful for paging through results.
			 * <p><b>Note:</b></p>
			 *   Gracenote Service limits the range size for some queries. If you specify a range size greater
			 *   than the limit, the results are constrained. Additionally, neither Gracenote Service nor GNSDK
			 *   returns an error about this behavior.
			 *  <p><b>Important:</b></p>
			 *  The number of results actually returned for a query may not equal the number of results initially
			 *   requested. To accurately iterate through results, always check the range start, end, and total
			 *   values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
			 *   are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
			 *   using the initial requested value.
			 */
			void
			ResultCount(gnsdk_uint32_t resultCount) throw (GnError);


			/**
			 *  Indicates the lookup data value for the Video query.
			 *  @param lookupData [in] One of the #GnLookupData values
			 *  @param bEnable    [in] Set lookup data
			 */
			void
			LookupData(GnLookupData lookupData, bool bEnable) throw (GnError);


			/**
			 *  Indicates whether a response is not automatically stored in the cache.
			 *  @param bNoCache Set boolean to enable caching
			 *  <p><b>Remarks:</b></p>
			 *  Set this option to True to retrieve query data from a call to Gracenote Service; doing this
			 *   ensures retrieving the most recent available data.
			 *  Set this option to False to retrieve query data that already exists in the lookup cache. When no
			 *   data exists in the cache, VideoID
			 *  or Video Explore automatically calls Gracenote Service with the query request.
			 */
			void
			QueryNoCache(bool bNoCache) throw (GnError);

			/**
			 *  Specifies that a TOC lookup includes the disc's commerce type.
			 *  @param bEnableCommerceType Set boolean to enable commerce type
			 */
			void
			QueryCommerceType(bool bEnableCommerceType) throw (GnError);

			/**
			 *  Sets a filter for a Video Explore query handle, using a list value.
			 *  @param bInclude [in] Set Boolean value to True to include filter key; set to False to exclude the filter
			 *  @param listElementFilterType [in] One of the #GnVideoListElementFilterType filter types
			 *  @param listElement [in] A list element handle used to populate the filter value. The list
			 *   element must be from a list that corresponds to the filter name.
			 *
			 *  <p><b>Remarks:</b></p>
			 *  Use this function with the GNSDK Manager Lists functionality to apply filters on and improve the
			 *   relevance for specific Video Explore search results. Your application must have Video Explore
			 *   licensing to use this function.
			 * <p><b>Note:</b></p>
			 *  The system disregards filters when performing non-text related video queries, and filtering
			 *   by list elements is restricted to performing a Works search using the following Filter Values:
			 *  <ul>
			 *  <li>kListElementFilterGenre</li>
			 *  <li>kListElementFilterProductionType</li>
			 *  <li>kListElementFilterSerialType</li>
			 *  <li>kListElementFilterOrigin</li>
			 *  </ul>
			 */
			void
			ResultFilter(GnVideoListElementFilterType listElementFilterType, const GnListElement& listElement, bool bInclude) throw (GnError);

			/**
			 *
			 *  Sets a filter for a VideoID or Video Explore query handle.
			 *  @param filterValue [in] String value for corresponding data key
			 *  @param filterType [in] One of the #GnVideoFilterType filter types
			 *  <p><b>Remarks:</b></p>
			 *  Use this function to apply certain filters on and improve the relevance of Work text search query
			 *   results.
			 * <p><b>Note:</b></p>
			 *  The system disregards filters when performing non-text related video queries, and that filtering by<br>
			 *  list elements is restricted to performing a Works search using the following Filter Values:
			 *  <ul>
			 *  <li>kFilterSeasonNumber text (integer as a string)</li>
			 *  <li>kFilterSeasonEpisodeNumber text (integer as a string)</li>
			 *  <li>kFilterSeriesEpisodeNumber text (integer as a string)</li>
			 *  </ul>
			 *
			 */
			void
			ResultFilter(GnVideoFilterType filterType, gnsdk_cstr_t filterValue) throw (GnError);

			/**
			 * Use this  option to set a specific network interface for this object's connections.
			 * Setting this can be beneficial for systems with multiple
			 * network interfaces. Without setting this option, the operating system will dicate which network interface
			 * gets used for connections.
			 *  @param ipAddress [in] local IP address for the desired network interface
			 */
			void
			NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError);

			/**
			 *  General option setting for custom string options
			 *  @param optionKey   [in] Option name
			 *  @param value	   [in] Option value
			 */
			void
			Custom(gnsdk_cstr_t optionKey, gnsdk_cstr_t value) throw (GnError);

		protected:
			GnVideoOptions() : weakhandle_(GNSDK_NULL) {};

			DISALLOW_COPY_AND_ASSIGN(GnVideoOptions);
			friend class GnVideo;
			gnsdk_video_query_handle_t weakhandle_;
		};

	   /**
		* GnVideo
		*/
		class GnVideo : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Initializes Gracenote's VideoID and Video Explore libraries.
			 *  @param user
			 *  @param pEventHandler
			 */
			GnVideo(const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

			/**
			 * Initializes Gracenote's VideoID and Video Explore libraries.
			 * @param user
			 * @param locale
			 * @param pEventHandler
			 */
			GnVideo(const GnUser& user, const GnLocale& locale, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

			/**
			 *  Shuts down and releases VideoID and Video Explore resources.
			 */
			virtual
			~GnVideo();

			/**
			 *  Retrieves the VideoID and Video Explore library's version string.
			 *
			 *  This API can be called at any time, even before initialization and after shutdown. The returned
			 *  string is a constant. Do not attempt to modify or delete.
			 *
			 *  Example: <code>1.2.3.123</code> (Major.Minor.Improvement.Build)<br>
			 *  Major: New functionality<br>
			 *  Minor: New or changed features<br>
			 *  Improvement: Improvements and fixes<br>
			 *  Build: Internal build number<br>
			 */
			static gnsdk_cstr_t
			Version();

			/**
			 *  Retrieves the VideoID and Video Explore library's build date as a string.
			 *  This API can be called at any time, even before initialization and after shutdown. The returned
			 *  string is a constant. Do not attempt to modify or delete.
			 *  @return String with format: YYYY-MM-DD hh:mm UTC
			 *
			 *  Example:<code>"2008-02-12 00:41 UTC"</code>
			 */
			static gnsdk_cstr_t
			BuildDate();

			/**
			 *  Options
			 */
			GnVideoOptions&
			Options() { return options_; }

			/**
			 *  Find video products using a TOC (Table of Contents) string.
			 *  @param videoTOC [in] TOC string; must be an XML string constructed by the Gracenote Video Thin Client component.
			 *  @param TOCFlag [in] TOC string flag; for flags types, see #GnVideoTOCFlag
			 *  @return GnResponseVideoProduct
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
			 *  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
			 *  Use this API to find a video product by its TOC.
			 */
			metadata::GnResponseVideoProduct
			FindProducts(gnsdk_cstr_t videoTOC, GnVideoTOCFlag TOCFlag) throw (GnError);

			/**
			 *  Find video products using a partial GnVideoProduct object.
			 *  @param videoProduct
			 *  @return GnResponseVideoProduct
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A partial GnVideoProduct object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 *  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
			 *  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
			 */
			metadata::GnResponseVideoProduct
			FindProducts(const metadata::GnVideoProduct& videoProduct) throw (GnError);

			/**
			 *  Find video products using a partial GnVideoWork object.
			 *  @param videoWork
			 *  @return GnResponseVideoProduct
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 *  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
			 *  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
			 */
			metadata::GnResponseVideoProduct
			FindProducts(const metadata::GnVideoWork& videoWork) throw (GnError);

			/**
			 *  Find video products using supported GnDataObject types.
			 *  @param gnObj
			 *  @return GnResponseVideoProduct
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
			 *  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
			 */
			metadata::GnResponseVideoProduct
			FindProducts(const metadata::GnDataObject& gnObj) throw (GnError);

			/**
			 *  Find video products using a text search
			 *  @param textInput [in] Text string.
			 *  @param searchField [in] Can be #GnVideoSearchField.kSearchFieldProductTitle or #GnVideoSearchField.kSearchFieldAll
			 *  @param searchType [in] Video search type; see #GnVideoSearchType
			 *  @return GnResponseVideoProduct
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
			 *  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
			 */
			metadata::GnResponseVideoProduct
			FindProducts(gnsdk_cstr_t textInput, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError);

			/**
			 *  Find video products using an external ID
			 *  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
			 *  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
			 *  @return GnResponseVideoProduct
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
			 *  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
			 */
			metadata::GnResponseVideoProduct
			FindProducts(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError);

			/**
			 *  Find video works using a partial GnVideoProduct object.
			 *  @param videoProduct [in]
			 *  @return GnResponseVideoWork
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A partial GnVideoProduct can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(const metadata::GnVideoProduct& videoProduct) throw (GnError);

			/**
			 *  Find video works using a partial GnVideoWork object.
			 *  @param videoWork [in]
			 *  @return GnResponseVideoWork
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(const metadata::GnVideoWork& videoWork) throw (GnError);

			/**
			 *  Find video works using a partial GnContributor object.
			 *  @param contributor [in]
			 *  @return GnResponseVideoWork
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(const metadata::GnContributor& contributor) throw (GnError);

			/**
			 *  Find video works using a partial GnVideoSeason object.
			 *  @param videoSeason [in]
			 *  @return GnResponseVideoWork
			 *
			 *  <p><b>Remarks:</b></p>
             *  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
             *  (Season Two), CSI: Miami (Season Three).
			 *  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(const metadata::GnVideoSeason& videoSeason) throw (GnError);

			/**
			 *  Find video works using a  partial GnVideoSeries object.
			 *  @param videoSeries [in]
			 *  @return GnResponseVideoWork
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
			 *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
			 *  A partial GnVideoSeries object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(const metadata::GnVideoSeries& videoSeries) throw (GnError);

			/**
			 *  Find video works using supported GnDataObject types.
			 *  @param gnObj [in]
			 *  @return GnResponseVideoWork
			 *
			 *  <p><b>Remarks:</b></p>
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(const metadata::GnDataObject& gnObj) throw (GnError);

			/**
			 *  Find video works using a text search.
			 *  @param textInput [in] text string.
			 *  @param searchField [in] Can be any #GnVideoSearchField option except #GnVideoSearchField.kSearchFieldProductTitle
			 *  @param searchType [in] Video search type, see #GnVideoSearchType
			 *
			 *  @return GnResponseVideoWork
			 *  <p><b>Remarks:</b></p>
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(gnsdk_cstr_t textInput, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError);

			/**
			 *  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
			 *  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
			 *
			 *  @return GnResponseVideoWork
			 *  <p><b>Remarks:</b></p>
			 *  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
			 *  body of work, or, more specifically, to indicate a particular movie or television show.
			 */
			metadata::GnResponseVideoWork
			FindWorks(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError);

			/**
			 *  Find video seasons using a partial GnVideoWork object.
			 *  @param videoWork [in]
			 *  @return GnResponseVideoSeasons
			 *
			 *  <p><b>Remarks:</b></p>
             *  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
             *  (Season Two), CSI: Miami (Season Three).
			 *  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeasons
			FindSeasons(const metadata::GnVideoWork& videoWork) throw (GnError);

			/**
			 *  Find video seasons using a partial GnContributor object.
			 *  @param contributor [in]
			 *  @return GnResponseVideoSeasons
			 *
			 *  <p><b>Remarks:</b></p>
             *  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
             *  (Season Two), CSI: Miami (Season Three).
			 *  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeasons
			FindSeasons(const metadata::GnContributor& contributor) throw (GnError);

			/**
			 *  Find video seasons using a partial GnVideoSeason object.
			 *  @param videoSeason [in]
			 *  @return GnResponseVideoSeasons
			 *
			 *  <p><b>Remarks:</b></p>
             *  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
             *  (Season Two), CSI: Miami (Season Three).
			 *  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeasons
			FindSeasons(const metadata::GnVideoSeason& videoSeason) throw (GnError);

			/**
			 *  Find video seasons using a partial GnVideoSeries object.
			 *  @param videoSeries [in]
			 *  @return GnResponseVideoSeasons
			 *
			 *  <p><b>Remarks:</b></p>
             *  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
             *  (Season Two), CSI: Miami (Season Three).
			 *  A partial GnVideoSeries object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeasons
			FindSeasons(const metadata::GnVideoSeries& videoSeries) throw (GnError);

			/**
			 *  Find video seasons using supported GnDataObject types.
			 *  @param gnObj [in]
			 *  @return GnResponseVideoSeasons
			 *
			 *  <p><b>Remarks:</b></p>
             *  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
             *  (Season Two), CSI: Miami (Season Three).
			 */
			metadata::GnResponseVideoSeasons
			FindSeasons(const metadata::GnDataObject& gnObj) throw (GnError);

			/**
			 *  Find video seasons using an external ID.
			 *  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
			 *  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
			 *  @return GnResponseVideoSeasons
			 *
			 *  <p><b>Remarks:</b></p>
             *  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
             *  (Season Two), CSI: Miami (Season Three).
			 */
			metadata::GnResponseVideoSeasons
			FindSeasons(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError);

			/**
			 *  Find video series using a partial GnVideoWork object.
			 *  @param videoWork [in]
			 *  @return GnResponseVideoSeries
			 *
			 *   <p><b>Remarks:</b></p>
             *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
             *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
			 *  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeries
			FindSeries(const metadata::GnVideoWork& videoWork) throw (GnError);

			/**
			 *  Find video series using a contributor Tui and TuiTag or partial GnContributor object.
			 *  @param contributor [in]
			 *  @return GnResponseVideoSeries
			 *
			 *   <p><b>Remarks:</b></p>
             *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
             *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
			 *  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeries
			FindSeries(const metadata::GnContributor& contributor) throw (GnError);

			/**
			 *  Find video series using a video season Tui and TuiTag or partial GnVideoSeason.
			 *  @param videoSeason [in]
			 *  @return GnResponseVideoSeries
			 *
			 *   <p><b>Remarks:</b></p>
             *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
             *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
			 *  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeries
			FindSeries(const metadata::GnVideoSeason& videoSeason) throw (GnError);

			/**
			 *  Find video series using a partial GnVideoSeries object.
			 *  @param videoSeries [in]
			 *  @return GnResponseVideoSeries
			 *
			 *   <p><b>Remarks:</b></p>
             *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
             *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
			 *  A partial GnVideoSeries object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseVideoSeries
			FindSeries(const metadata::GnVideoSeries& videoSeries) throw (GnError);

			/**
			 *  Find video series using supported GnDataObject types.
			 *  @param gnObj [in]
			 *  @return GnResponseVideoSeries
			 *
			 *   <p><b>Remarks:</b></p>
             *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
             *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
			 */
			metadata::GnResponseVideoSeries
			FindSeries(const metadata::GnDataObject& gnObj) throw (GnError);

			/**
			 *  Find video series using a text search.
			 *  @param textInput [in]  Video series title
			 *  @param searchType [in] Can only be #GnVideoSearchType.kSearchFieldSeriesTitle - you cannot search for a Series
			 *  using #GnVideoSearchType.kSearchFieldAll
			 *  @return GnResponseVideoSeries
			 *
			 *   <p><b>Remarks:</b></p>
             *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
             *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
			 */
			metadata::GnResponseVideoSeries
			FindSeries(gnsdk_cstr_t textInput, GnVideoSearchType searchType) throw (GnError);

			/**
			 *  Find video series using an external ID.
			 *  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
			 *  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
			 *  @return GnResponseVideoSeries
			 *
			 *   <p><b>Remarks:</b></p>
             *  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
             *  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigati
			 */
			metadata::GnResponseVideoSeries
			FindSeries(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError);

			/**
			 *  Find contributors associated with a partial GnVideoWork object.
			 *  @param videoWork [in]
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A contributor is a person involved in the creation of a work (such as an actor or a director) or
			 *  an entity (such as a production company).
			 *  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseContributors
			FindContributors(const metadata::GnVideoWork& videoWork) throw (GnError);

			/**
			 *  Find contributors using a partial GnContributor objet.
			 *  @param contributor [in]
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
			 *  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseContributors
			FindContributors(const metadata::GnContributor& contributor) throw (GnError);

			/**
			 *  Find contributors associated with a video season using a partial GnVideoSeason.
			 *  @param videoSeason [in]
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
		     *  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
			 *  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseContributors
			FindContributors(const metadata::GnVideoSeason& videoSeason) throw (GnError);

			/**
			 *  Find contributors associated with a partial GnVideoSeries object.
			 *  @param videoSeries [in]
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
		     *  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
		     *  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
			 *  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
			 */
			metadata::GnResponseContributors
			FindContributors(const metadata::GnVideoSeries& videoSeries) throw (GnError);

			/**
			 *  Find contributors using supported GnDataObject types.
			 *  @param gnObj [in]
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
		     *  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
			 */
			metadata::GnResponseContributors
			FindContributors(const metadata::GnDataObject& gnObj) throw (GnError);

			/**
			 *  @deprecated This method has been deprecated.
			 *  Find contributors using a text search.
			 *  @param textInput [in]
			 *  @param searchType [in]
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
		     *  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
			 */
			metadata::GnResponseContributors
			FindContributors(gnsdk_cstr_t textInput, GnVideoSearchType searchType) throw (GnError);

			/**
			 *  Find contributors using a text search.
			 *  @param searchText [in]
			 *  @param searchField [in] Can be #GnVideoSearchField.kSearchFieldContributorName or #GnVideoSearchField.kSearchFieldAll
			 *  @param searchType [in] Video search type, see #GnVideoSearchType
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
		     *  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
			 */
			metadata::GnResponseContributors
			FindContributors(gnsdk_cstr_t searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError);
			/**
			 *  Find contributors using an external ID.
			 *  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
			 *  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
			 *  @return GnResponseContributors
			 *
			 *  <p><b>Remarks:</b></p>
			 *  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
			 */
			metadata::GnResponseContributors
			FindContributors(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError);

			/**
			 *  Performs a Video Explore query for any type of video object. Use this function to retrieve a specific
			 *  Video Explore object referenced by a GnDataObject.
			 *  @param gnObj [in]
			 *  @return GnResponseVideoObjects
			 *
			 */
			metadata::GnResponseVideoObjects
			FindObjects(const metadata::GnDataObject& gnObj) throw (GnError);

			/**
			 *  Performs a Video Explore query for any type of video object. Use this function to retrieve
			 *  all the Video Explore objects (Contributors, Products, Seasons, Series, and Works) associated with a
			 *  particular external ID.
			 *  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
			 *  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
			 *  @return GnResponseVideoObjects
			 */
			metadata::GnResponseVideoObjects
			FindObjects(gnsdk_cstr_t externalId, GnVideoExternalIdType externalIdType) throw (GnError);

			/**
			 *  Performs a VideoID or Video Explore query for search suggestion text. Use this function to suggest potential matching titles,
			 *  names, and series as a user enters text in a search query. A suggestion search cannot be performed using #GnVideoSearchField.kSearchFieldAll.
			 *  @param searchText [in] Text string.
			 *  @param searchField [in] Can be any #GnVideoSearchField option except #GnVideoSearchType.kSearchFieldAll
			 *  @param searchType [in] Video search type, see #GnVideoSearchType
			 *  @return GnResponseVideoSuggestions
			 */
			metadata::GnResponseVideoSuggestions
			FindSuggestions(gnsdk_cstr_t searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) throw (GnError);

			/*-----------------------------------------------------------------------------
			 *  EventHandler
			 */
			IGnStatusEvents*
			EventHandler() const { return eventhandler_; }

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
			GnVideoOptions		options_;
			bool				cancelled_;

			/* dissallow assignment operator */
			DISALLOW_COPY_AND_ASSIGN(GnVideo);
		};


#endif /* GNSDK_VIDEO */
	} /* namespace video */

}     /* namespace gracenote */

#endif /* _GNSDK_VIDEO_HPP_ */

