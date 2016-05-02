/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_LIST_HPP_
#define _GNSDK_LIST_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_locale.hpp"
#include "metadata.hpp"

namespace gracenote
{
	class GnListElement;

	/**
	 * List types. GNSDK uses lists to provide media metadata via response objects. Response metadata depending
	 * on lists is known as list-based metadata. Lists are localized meaning, where applicable, the data they
	 * contain is specific to a region and/or translated into languages supported by Gracenote.
	 * Where a list is not available in the requested language the default language, English, is returned.
	 */
	enum GnListType
	{
		kListTypeInvalid = 0,

		/**
		 * This list contains languages that are supported by Gracenote, and are typically used to indicate
		 * the original language of an item.
		 */
		kListTypeLanguages,

		/**
		 * This list contains scripts that are supported by Gracenote
		 */
		kListTypeScripts,

		/**
		 * The list of supported music genres.
		 * <p><b>Remarks:</b></p>
		 * The genre list contains a hierarchy of genres available from Gracenote strictly for music data.
		 */
		kListTypeGenres,

		/**
		 * The list of supported geographic origins for artists.
		 */
		kListTypeOrigins,

		/**
		 * The list of supported music era categories.
		 */
		kListTypeEras,

		/**
		 * The list of supported artist type categories.
		 */
		kListTypeArtistTypes,

		/**
		 * This list contains role list elements supported Gracenote for album data, such as Vocalist and Bass Guitar.
		 */
		kListTypeRoles,

		/**
		 *  This list contains a hierarchy of genre list elements available from Gracenote, strictly for
		 * video data.
		 */
		kListTypeGenreVideos,

		/**
		 * This list contains movie rating list elements supported by Gracenote.
		 */
		kListTypeRatings,

		/**
		 * This list contains film content rating list elements supported by Gracenote.
		 */
		kListTypeRatingTypes,

		/**
		 * This list contains contributor role list elements available from Gracenote, such as Actor or
		 * Costume Design. These apply to video data.
		 */
		kListTypeContributors,

		/**
		 * The list of supported feature types for video data.
		 */
		kListTypeFeatureTypes,

		/**
		 *  The list of supported video regions.
		 */
		kListTypeVideoRegions,

		/**
		 * The list of supported video types, such as Documentary, Sporting Event, or Motion Picture.
		 */
		kListTypeVideoTypes,

		/**
		 * The list of supported media types for music and video, such as Audio CD, Blu-ray, DVD, or HD DVD.
		 */
		kListTypeMediaTypes,

		/**
		 * The list of supported video serial types, such as Series or Episode.
		 */
		kListTypeVideoSerialTypes,

		/**
		 * The list of supported work types for video data, such as Musical or Image.
		 */
		kListTypeWorkTypes,

		/**
		 * The list of supported media spaces for video data, such as Music, Film, or Stage.
		 */
		kListTypeMediaSpaces,

		/**
		 * The list of supported moods for music data. Moods are categorized into levels, from more general
		 * (Level 1, such as Blue) to more specific (Level 2, such as Gritty/Earthy/Soulful).
		 */
		kListTypeMoods,

		/**
		 * The list of supported tempos for music data, has three levels of granularity.
		 * The tempos are categorized in levels in increasing order of granularity.
		 * Level 1: The meta level, such as Fast Tempo.
		 * Level 2: The sub tempo level, such as Very Fast.
		 * Level 3: The micro level, which may be displayed as a numeric tempo range, such as 240-249, or a
		 * descriptive phrase.
		 */
		kListTypeTempos,

		/**
		 * The list of supported composition forms for classical music.
		 */
		kListTypeCompostionForm,

		/**
		 * The list of supported instrumentation for classical music.
		 */
		kListTypeInstrumentation,

		/**
		 * The list of supported overall story types for video data, such as Love Story.
		 * It includes general theme classifications such as such as Love Story, Family Saga, Road Trip,
		 * and Rags to Riches.
		 */
		kListTypeVideoStoryType,

		/**
		 * The list of supported audience types for video data.
		 * It includes general audience classifications by age, ethnicity, gender, and spiritual beliefs,
		 * such as Kids & Family, African-American, Female, Gay & Lesbian, and Buddhist.
		 */
		kListTypeVideoAudience,

		/**
		 * The list of supported moods for video data, such as Offbeat.
		 * It includes general classifications such as such as Offbeat, Uplifting, Mystical, and Sarcastic.
		 */
		kListTypeVideoMood,

		/**
		 * The list of supported film reputation types for video data, such as Classic.
		 * It includes general classifications such as such as Classic, Chick Flick, and Cult.
		 */
		kListTypeVideoReputation,

		/**
		 * The list of supported scenarios for video data. It
		 * includes general classifications such as such as Action, Comedy, and Drama.
		 */
		kListTypeVideoScenario,

		/**
		 * The language of the list is determined by the language value given to
		 */
		kListTypeVideoSettingEnv,

		/**
		 * The list of supported historical time settings for video data, such as Elizabethan Era,
		 * 1558-1603, or Jazz Age, 1919-1929.
		 */
		kListTypeVideoSettingPeriod,

		/**
		 * The list of supported story concept sources for video data, such as Fairy Tales & Nursery Rhymes.
		 * It includes story source classifications such as Novel, Video Game, and True Story.
		 */
		kListTypeVideoSource,

		/**
		 * The list of supported film style types for video data, such as Film Noir.It
		 * includes general style classifications such as Art House, Film Noir, and Silent.
		 */
		kListTypeVideoStyle,

		/**
		 * The list of supported film topics for video data, such as Racing or Teen Angst. It includes a diverse
		 * range of film topics, such as Politics, Floods, Mercenaries, Surfing, and Adventure. It also includes
		 * some list elements that can be considered sub-topics of a broader topic. For example, the list element Aliens (the broad topic),
		 * and Nice Aliens and Bad Aliens (the more defined topics).
		 */
		kListTypeVideoTopic,

		/**
		 * The list of supported viewing types for EPG data, such as live and rerun.
		 */
		kListTypeEpgViewingTypes,

		/**
		 * The list of supported audio types for EPG data, such as stereo and dolby.
		 */
		kListTypeEpgAudioTypes,

		/**
		 * The list of supported video types for EPG data, such as HDTV and PAL30.
		 */
		kListTypeEpgVideoTypes,

		/**
		 * The list of supported video types for EPG data, such as closed caption.
		 */
		kListTypeEpgCaptionTypes,

		/**
		 * The list of supported categories for IPG data, such as movie and TV series.
		 */
		kListTypeIpgCategoriesL1,

		/**
		 * The list of supported categories for IPG data, such as action and adventure.
		 */
		kListTypeIpgCategoriesL2,

		/**
		 * The list of supported production types for EPG data, such as news and documentary.
		 */
		kListTypeEpgProductionTypes,

		/**
		 * The list of supported device types for EPG data.
		 */
		kListTypeEpgDeviceTypes
	};


	/**
	 * Flags indicating rendering level for a list object, used when rendering a list to XML.
	 */
	enum GnListRenderFlags
	{
		kRenderDefault,

		/**
		 * Minimal information included.
		 */
		kRenderMinimal,

		/**
		 * All information included.
		 */
		kRenderFull

	};

	class list_element_child_provider
	{
	public:

		/** 
		* Constructor
		*/
		list_element_child_provider() : elementHandle_(GNSDK_NULL) { }
		
		/** 
		* Constructor
		*/
		list_element_child_provider(gnsdk_list_element_handle_t handle) : elementHandle_(handle) { }
		
		/* Provider Interface */
		
		/** 
		* Get list elment by position
		*/
		GnListElement
		get_data(gnsdk_uint32_t pos);

		/** 
		* Get child list element count
		*/
		gnsdk_uint32_t count() const;
	private:

		gnsdk_list_element_handle_t elementHandle_;
	};

	/**
	* list_element_child_iterator
	*/
	typedef gn_facade_range_iterator<GnListElement, list_element_child_provider>	list_element_child_iterator;
	
	/**
	* list_element_child_iterable
	*/
	typedef gn_iterable_container<GnListElement, list_element_child_provider>		list_element_child_iterable;

	/**
	 * Element of a Gracenote list.
	 */
	class GnListElement : public GnObject
	{
	public:
		GNWRAPPER_ANNOTATE

		/**
		 *    Constructor
		 */
		GnListElement() { }
		
		/**
		 *    Constructor
		 */
		explicit
		GnListElement(gnsdk_list_element_handle_t handle) : GnObject(handle) { }

		/**
		 *    Destructor
		 */		
		virtual
		~GnListElement() { }


		/**
		 * Retrieves a display string for a given list element.
		 * <p><b>Remarks:</b></p>
		 * Use this function to directly retrieve the display string from a list element.
		 */
		gnsdk_cstr_t
		DisplayString() const throw (GnError);

		/**
		 * Retrieves a specified list element ID for a given list element.
		 * <p><b>Remarks:</b></p>
		 * Use this function to retrieve the ID of a list element.
		 */
		gnsdk_uint32_t
		Id() const throw (GnError);

		/**
		 * Retrieves a list element ID for use in submitting parcels.
		 */
		gnsdk_uint32_t
		IdForSubmit() const throw (GnError);

		/**
		 * Retrieves the list element's description.
		 */
		gnsdk_cstr_t
		Description() const throw (GnError);

		/**
		 * The list element's Rating Type ID (available in content ratings list).
		 */
		gnsdk_cstr_t
		RatingTypeId() const throw (GnError);

		/**
		 * Retrieves the parent element of the given list element.
		 * <p><b>Remarks:</b></p>
		 * When GNSDK Manager throws an error exception with error code SDKMGRERR_NotFound,
		 * then the given element is the top-most parent element.
		 */
		GnListElement
		Parent() const throw (GnError);

		/**
		 * Retrieves the hierarchy level for a given list element.
		 */
		gnsdk_uint32_t
		Level() const throw (GnError);

		/**
		* Retrieves children for a given list element.
		*/
		list_element_child_iterable Children() const 
		{
			return list_element_child_iterable(list_element_child_provider(get<gnsdk_list_element_handle_t>()),GN_BASE_START);
		}

		/**
		 * Retrieve this list element's native handle.
		 */
		gnsdk_list_element_handle_t
		native() const { return get<gnsdk_list_element_handle_t>(); }


	private:

		friend class GnList;

	};


	class list_element_provider
	{
	public:
		/** 
		* Constructor
		*/
		list_element_provider() : listHandle_(GNSDK_NULL), level_(1) { }
		
		/** 
		* Constructor
		*/		
		list_element_provider(gnsdk_list_handle_t handle, gnsdk_uint32_t level) : listHandle_(handle), level_(level)  { }
	
		/* Provider Interface */
		
		/** 
		* Get list element by position
		*/
		GnListElement
		get_data(gnsdk_uint32_t pos) throw (GnError);

		/**
		* Get count 
		*/
		gnsdk_uint32_t count() const; 
		
	private:
		gnsdk_list_handle_t listHandle_;
		gnsdk_uint32_t      level_;

	};

	/** 
	* list_element_iterator
	*/
	typedef gn_facade_range_iterator<GnListElement, list_element_provider>   list_element_iterator;
	
	/** 
	* list_element_iterable
	*/
	typedef gn_iterable_container<GnListElement, list_element_provider>		list_element_iterable;

	/**
	 * Gracenote list.
	 */
	class GnList : public GnObject
	{
	public:
		GNWRAPPER_ANNOTATE
		
		/**
		* Default constuctor 
		*/
		GnList() { }

		/**
		* constuctor 
		*/		
		GnList(GnListType listType, GnLanguage language, GnRegion region, GnDescriptor descriptor, const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL)  throw (GnError);
		
		/**
		* constuctor 
		*/		
		GnList(GnListType listType, const GnLocale& locale, const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL)  throw (GnError);
		
		/**
		* constuctor 
		*/		
		GnList(gnsdk_cstr_t serializedList) throw (GnError);
		
		/**
		* constuctor 
		*/		
		GnList(gnsdk_list_handle_t listHandle) : GnObject(listHandle) { }

		/**
		 * Tests an existing list for updates and downloads a new list, if available. The application must
		 * ensure the List module can contact the Gracenote Service to test for a new list version, by
		 * appropriately configuring the user lookup option.
		 * Note: This function blocks the current thread until the download is complete; set a status callback function to receive progress messages.
		 * @param user				User making the list update request
		 * @return True if an update is available, false otherwise.
		 * <p><b>Remarks:</b></p>
		 * Use this function to periodically update a list. The list will be updated if an update is available.
		 * Optionally an application can check if an update is available before calling this method.
		 *
		 * Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
		 */
		bool
		Update(const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

		/**
		 * Tests an existing list to determine if a newer revision is available. If available, the new revision is not downloaded. To download
		 * the new revision the application must call GnList.Update().
		 * The application must ensure the List module can contact the Gracenote Service to test for a new list version, by
		 * appropriately configuring the user lookup option.
		 * Note: This function blocks the current thread until the check is complete; set a status callback function to receive progress messages.
		 * @param user				User making the list update check request
		 * @return True if an update is available, false otherwise.
		 * <p><b>Remarks:</b></p>
		 * Use this function to periodically check Gracenote Service for updates to an existing list handle.
		 * <p><b>Note:</b></p>
		 * You should configure application(s) to automatically check for list updates to ensure use of the
		 * most current data.
		 * You should immediately check for updates after constructing a list object from a saved serialized list string as it may
		 * be out of date.
		 * This function blocks the current thread until the download is complete;
		 * set a status callback function to receive progress messages.
		 *
		 * Long Running Potential: Network I/O
		 */
		bool
		UpdateCheck(const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

		/**
		 * Serializes a list into encrypted text, so the application can store it for later use.
		 * <p><b>Note:</b></p>
		 * If you application is using a GNSDK local storage solution, lists are automatically stored
		 * and retrieved from a local store according to the configuration of user option.
		 * Applications implementing their own local storage functionality can use this method
		 * to render a list into a format that can be stored persistently and restored at a later time using
		 * the appropriate constructor.
		 */
		GnString
		Serialize() throw (GnError);

		/**
		 *  Renders list data to XML.
		 *  @param levels			List level values to render
		 *  @param renderFlags		Flags configuring rendering output
		 */
		GnString
		RenderToXml(gnsdk_uint32_t levels, GnListRenderFlags renderFlags) throw (GnError);

		/**
		 * Retrieves this list's type.
		 */
		GnListType
		Type() throw (GnError);

		/**
		 * Retrieves this list's descriptor.
		 */
		GnDescriptor
		Descriptor() throw (GnError);

		/**
		 * Retrieves this list's language.
		 */
		GnLanguage
		Language() throw (GnError);

		/**
		 * Retrieves this list's region.
		 */
		GnRegion
		Region() throw (GnError);

		/**
		 * Retrieves this list's revision string.
		 */
		gnsdk_cstr_t
		Revision() throw (GnError);

		/**
		 * Retrieves a maximum number of levels in a hierarchy for a given list.
		 * <p><b>Remarks:</b></p>
		 * When this function succeeds, the returned parameter contains the number of levels in the given
		 * list's hierarchy. This level count value is needed when determining which level to access when
		 * retrieving elements or data from a list.
		 * Lists can be flat or hierarchical. A flat list has only one level. A hierarchical list has a
		 * parent-child relationship, where the parent's value is broad enough to encompass its child values
		 * (for example, a level 1 Rock genre is a parent to level 2 Country Rock and Punk Rock genres). You
		 * can configure an application to use a single level or the entire hierarchy.
		 * Level 1 indicates the top level of the list, which usually contains the more general data. The
		 * highest level value for a list contains the most fine-grained data.
		 */
		gnsdk_uint32_t
		LevelCount() throw (GnError);

		list_element_iterable ListElements(gnsdk_uint32_t level) 
		{
			return list_element_iterable(list_element_provider(get<gnsdk_list_handle_t>(), level),GN_BASE_START);
		}

		/**
		 * Retrieves a list element from a list using a specific list element ID.
		 * If no list element with the ID is found a null list element object is returned.
		 * @param itemId		List element item ID
		 */
		GnListElement
		ElementById(gnsdk_uint32_t itemId) throw (GnError);

		/**
		 * Retrieves list element whose range includes the specified value
		 * If no list element matching the range is found a null list element object is returned.
		 * @param range		Value for range comparison
		 */
		GnListElement
		ElementByRange(gnsdk_uint32_t range) throw (GnError);

		/**
		 * Retrieves list element whose string matches the specified value.	
		 * If no list element with the string is found a null list element object is returned.
		 * @param strEquality		Value of string to look up
		 */
		GnListElement
		ElementByString(gnsdk_cstr_t strEquality) throw (GnError);

		
		/**
		 * Retrieves list element corresponding to the data object.
		 * If no list element matching the data object is found a null list element object is returned.
		 * @param dataObject		Gracenote data object
		 * @param ordinal			Ordinal
		 * @param level				List level value
		 */
		GnListElement
		ElementByGnDataObject(const metadata::GnDataObject& dataObject, gnsdk_uint32_t ordinal, gnsdk_uint32_t level) throw (GnError);

		/**
		 * Retrieve this list element's native handle.
		 */
		gnsdk_list_handle_t
		native() const { return get<gnsdk_list_handle_t>(); }

	private:
		friend class GnLocale;
		friend class GnLocaleInfo;
	};


}
#endif /* _GNSDK_LIST_HPP_ */

