/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_LOCALE_HPP_
#define _GNSDK_LOCALE_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4290 ) /* disable "warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)" */
#endif

#include "gnsdk_base.hpp"

namespace gracenote
{
	/**
	 * Locale groups used when specifying which locale to load.
	 */
	enum GnLocaleGroup
	{
		kLocaleGroupInvalid = 0,

		kLocaleGroupMusic,
		kLocaleGroupVideo,
		kLocaleGroupPlaylist,
		kLocaleGroupEpg
	};


	/**
	 * Encapsulates information about a GnLocale instance. Used where GNSDK delivers a locale description such as
	 * iterating the available locales or when querying a GnLocale instance for information.
	 */
	class GnLocaleInfo : public GnObject
	{
	public:
		GNWRAPPER_ANNOTATE
		
		/**
		 * Construct GnLocaleInfo object with default values.
		 */
		 GnLocaleInfo() :group_(kLocaleGroupInvalid), language_(kLanguageInvalid), region_(kRegionDefault), descriptor_(kDescriptorDefault) { }
		
		/**
		 * Construct GnLocaleInfo object with default values.
		 * @param GnLocaleGroup group - locale group
		 * @param GnLanguage language - locale language
		 * @param GnRegion region - locale region
		 * @param GnDescriptor descriptor - locale descriptor
		 */
		GnLocaleInfo(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor) :
			group_(group), language_(language), region_(region), descriptor_(descriptor) { }
		
		/**
		 * Get locale group
		 * @return Group
		 */
		GnLocaleGroup
		Group(void) const { return group_;}

		/**
		 * Get locale language
		 * @return Language
		 */
		GnLanguage 
		Language(void) const  { return language_; }
		
		/**
		 * Get locale region
		 * @return Region
		 */
		GnRegion
		Region(void) const { return region_;}

		/**
		 * Get locale descriptor
		 * @return Descriptor
		 */
		GnDescriptor
		Descriptor(void) const {return descriptor_;}
		
		/**
		*  operator ==
		*/
		bool
		operator == (const GnLocaleInfo& rhs) const
		{
			return ( group_ == rhs.group_ ) && ( language_ == rhs.language_ ) && ( region_ == rhs.region_) &&( descriptor_ == rhs.descriptor_);
		}
		
	private:
		GnLocaleGroup 	group_;
		GnLanguage 		language_;
		GnRegion 		region_;
		GnDescriptor	descriptor_;
	};


	/**
	 * GNSDK internal provider class
	 */
	class locale_info_provider
	{
	public:
		/**
		* Constructor
		*/
		locale_info_provider() { }
		
		/**
		* Destructor
		*/
		~locale_info_provider() { }

		/**
		 * Get locale available data at position
		 * @param pos - position of GnLocale info to get
		 * @return Locale info
		 */
		GnLocaleInfo
		get_data(gnsdk_uint32_t pos) const throw (GnError);

		/**
		 * Get total count of locales available
		 * @return Count
		 */
		gnsdk_uint32_t
		count() const 
		{
			gnsdk_uint32_t count = 0;

			gnsdk_manager_locale_available_count(&count);
			return count;
		}

		/**
		 * Iterator ordinal start
		 */
		static const gnsdk_uint32_t kOrdinalStart = 1;

		/**
		 * Iterator ordinal offset
		 */
		static const gnsdk_uint32_t kCountOffset  = 1;
	};

	/**
	 * locale_info_iterator
	 */
	typedef gn_facade_range_iterator<GnLocaleInfo, locale_info_provider>   locale_info_iterator;
	
	/**
	 * locale_info_iterable
	 */	
	typedef gn_iterable_container<GnLocaleInfo, locale_info_provider>   locale_info_iterable;

	/**
	 * Loads Gracenote data for the specified locale
	 *
	 * Locales are used by GNSDK for various reasons and it's the best practice to have an appropriate
	 * locale loaded. Typically an application uses user preferences or device settings to determine the
	 * region and language of the loaded locale. To determine what locale group and descriptor to load
	 * work with your Gracenote support representative.
	 *
	 * Locale data is only loaded if it not already loaded. It can be loaded from Gracenote Service or from a
	 * local database. To use a local database a storage provider must be enabled, such as GnStorageSqlite.
	 * Where a local database is used GNSDK will attempt to load locale data from it, if not found locale data
	 * will be downloaded from Gracenote Service and written to the local database.
	 *
	 * Locale load can be canceled at any time by setting the "canceller" provided in any IGnStatusEvents
	 * delegate method. No cancel method is provided on GnLocale object because loading can happen on object
	 * construction.
	 *
	 * Loading a locale can be lengthy, so some applications may wish to perform this operation on a background
	 * thread to avoid stalling the main thread.
	 *
	 * Once a locale is loaded it can be set as the group default. The default locale is automatically
	 * associated with appropriate response objects returned by GNSDK, allowing Gracenote descriptive data,
	 * such as genres, to be returned according to the locales region and language.
	 *
	 * Gracenote data is regularly updated; therefore Locale data should also be updated. GNSDK can detect
	 * when an application should update a locale and call an IGnSystemEvents delegate method providing the GnLocale
	 * object. Your application can register for system events via a GnManager instance. Alternatively your
	 * application can keep the GnLocale object and periodically invoke update. It is Gracenote best practice
	 * that your application implement a locale update procedure.
	 */
	class GnLocale : public GnObject
	{
	public:
		GNWRAPPER_ANNOTATE

		/**
		 * Constructs empty GnLocale object, no local is loaded.
		 */
		GnLocale() :localeinfo_() { }

		/**
		* Constructs GnLocale object
		*/
		GnLocale(const GnLocaleInfo& localeInfo, const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL)  throw (GnError);
		
		/**
		 * Loads the specified locale
		 * @param group				Locale group specifies which locale data is loaded
		 * @param language			Language of locale data
		 * @param region			Region of the locale data where applicable
		 * @param descriptor		Descriptor, or verbosity, of the locale data where applicable
		 * @param user				User object
		 * @param pEventHandler     Status events delegate
		 * <p><b>Note</b><p> This method blocks the current thread until the load is complete;
		 * set an IGnStatusEvents delegate to receive progress messages.
		 *
		 * Long Running Potential: Network I/O, File system I/O
		 */
		GnLocale(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor, const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL)  throw (GnError);

		/**
		 * Loads the specified locale
		 * @param group				Locale group specifies which locale data is loaded
		 * @param langIsoCode		Language of locale data as an ISO code
		 * @param region			Region of the locale data where applicable
		 * @param descriptor		Descriptor, or verbosity, of the locale data where applicable
		 * @param user				User object
		 * @param pEventHandler     Status events delegate
		 * <p><b>Note</b><p> This method blocks the current thread until the load is complete;
		 * set an IGnStatusEvents delegate to receive progress messages.
		 *
		 * Long Running Potential: Network I/O, File system I/O
		 */
		GnLocale(GnLocaleGroup group, gnsdk_cstr_t langIsoCode, GnRegion region, GnDescriptor descriptor, const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL)  throw (GnError);

		/**
		 * Create GnLocale instance from native handle
		 * @param localeHandle		Native locale handle
		 */
		GnLocale(gnsdk_locale_handle_t localeHandle) throw (GnError);

		/**
		 * Reconstitutes locale from serialized locale data.
		 * @param serializedLocale	String of serialized locale handle data
		 */
		GnLocale(gnsdk_cstr_t serializedLocale) throw (GnError);

		virtual
		~GnLocale();

		/**
		* Get Locale information 95
		*/
		const GnLocaleInfo& LocaleInformation() const { return localeinfo_;} 
		/**
		 * Retrieves this locale's revision string.
		 * @return Revision
		 */
		gnsdk_cstr_t
		Revision() const throw (GnError);

		/**
		 * Sets this locale as the default locale for the 'locale group' (see GnLocaleGroup).
		 */
		void
		SetGroupDefault() throw (GnError);

		/**
		 * Retrieve iterator for locales available from locale lists cache
		 * @return Locale info iterator
		 */
		static locale_info_iterable
		StoredLocales()  
		{
			return locale_info_iterable(locale_info_provider(), GN_GDO_START);
		}

		/**
		 * Updates a locale with new versions of the locale data, if available.
		 * The application must ensure Gracenote Service can be contacted to test for a new list version
		 * by appropriately configuring the user's lookup mode to allow online access.
		 *
		 * The application can cancel the update procedure by setting the "canceller" in any method
		 * called in the status event delegate.
		 *
		 * @param user				User requesting the locale update
		 * @param pEventHandler		Status events delegate
		 * @return True indicates updates were applied, false indicates no updates are available
		 *
		 * <p><b>Note</b></p>
		 * This methods blocks the current thread until the update procedure is complete;
		 * set a status events delegate to receive progress messages.
		 *
		 * Long Running Potential: Network I/O, File system I/O
		 */
		bool
		Update(const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

		/**
		 * Tests a locale to determine if a newer revision of any locale data is available. If available the new data
		 * is not downloaded. To download the application must invoke update.
		 * The application must ensure Gracenote Service can be contacted to test for a new list version
		 * by appropriately configuring the user's lookup mode to allow online access.
		 *
		 * The application can cancel the update check procedure by setting the "canceller" in any method
		 * called in the status event delegate.
		 *
		 * @param user				User requesting the locale update check
		 * @param pEventHandler		Status event delegate
		 * @return True indicates updates are available, false otherwise.
		 *
		 * <p><b>Remarks:</b></p>
		 * This method can be invoked periodically to check Gracenote Service for updates to locale data.
		 *
		 * <p><b>Note:</b></p>
		 * You should immediately check for updates after constructing a locale object from a saved serialized locale
		 * string as it may be out of date.
		 *
		 * This methods blocks the current thread until the update procedure is complete;
		 * set a status events delegate to receive progress messages.
		 *
		 * Long Running Potential: Network I/O
		 */
		bool
		UpdateCheck(const GnUser& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

		/**
		 * Serializes locale data into encrypted text string that the application can store locally for later use.
		 * <p><b>Note:</b></p>
		 * If the application is using a GNSDK local storage solution locale data is automatically stored
		 * and retrieved from a local store according to the configuration of user lookup option.
		 * Applications implementing their own local storage functionality can use this method to
		 * render a locale into a format that can be stored persistently and restored at a later time using
		 * the appropriate constructor.
		 * @return Serialize locale data
		 */
		GnString
		Serialize() const throw (GnError);

		/**
		 * Retrieve this locale's native handle.
		 * @return Locale native handle
		 */
		gnsdk_locale_handle_t
		native() const { return get<gnsdk_locale_handle_t>(); }

	private:
		GnLocaleInfo localeinfo_;
	};


} /* namespace gracenote */


#endif /* _GNSDK_LOCALE_HPP_ */

