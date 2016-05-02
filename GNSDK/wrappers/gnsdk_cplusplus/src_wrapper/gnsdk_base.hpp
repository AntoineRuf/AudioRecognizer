/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_BASE_HPP_
#define _GNSDK_BASE_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4290 ) /* disable "warning C4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)" */
#endif

#if defined(SWIG) && defined(SWIGPYTHON)
	#define		GNWRAPPER_ANNOTATE		%feature("autodoc", "1");
#else
	#define		GNWRAPPER_ANNOTATE
#endif

#include "gnsdk.h"
#include "gnsdk_std.hpp"
#include "gnsdk_error.hpp"
#include "gn_userstore.hpp"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName &);            \
	void operator = (const TypeName&)


#define GNSDK_CHECKED_CAST(TypeName, gdoType)                                              \
	static gnsdk_cstr_t GnType() { return gdoType; }                                       \
	static TypeName From(const GnDataObject &obj) throw (GnError) {                        \
		gnsdk_error_t error = gnsdk_manager_gdo_is_type(obj.native(), TypeName::GnType()); \
		if (error) {throw GnError(); }                                                     \
		return TypeName(obj.native());                                                     \
	}

#define GNSDK_NULL_GDO		(gnsdk_gdo_handle_t)GNSDK_NULL

#define GN_UINT32_MAX		4294967295 

#define GN_GDO_START		1
#define GN_BASE_START		0

namespace gracenote
{
	/*=========================================================================
	 * Enums
	 */

	/**
	 * Modes for accessing Gracenote data and performing searches.
	 * GNSDK can, where available, access data and search from both local and online
	 * sources.
	 */
	enum GnLookupMode
	{
		/**
		 * Invalid lookup mode
		 */
		kLookupModeInvalid = 0,

		/**
		 * This mode forces the lookup to be done against the local database only. Local caches created from (online) query
		 * results are not queried in this mode.
		 * If no local database exists, the query will fail.
		 */
		kLookupModeLocal,

		/**
		 * This is the default lookup mode. If a cache exists, the query checks it first for a match.
		 * If a no match is found in the cache, then an online query is performed against Gracenote Service.
		 * If a result is found there, it is stored in the local cache.  If no online provider exists, the query will fail.
		 * The length of time before cache lookup query expires can be set via the user object.
		 */
		kLookupModeOnline,

		/**
		 * This mode forces the query to be done online only and will not perform a local cache lookup first.
		 * If no online provider exists, the query will fail. In this mode online queries and lists are not
		 * written to local storage, even if a storage provider has been initialize.
		 */
		kLookupModeOnlineNoCache,

		/**
		 * This mode forces the query to be done online only and will not perform a local cache lookup first.
		 * If no online provider exists, the query will fail. If a storage provider has been initialized,
		 * queries and lists are immediately written to local storage, but are never read unless the lookup mode is changed.
		 */
		kLookupModeOnlineNoCacheRead,

		/**
		 * This mode forces the query to be done against the online cache only and will not perform a network lookup.
		 * If no online provider exists, the query will fail.
		 */
		kLookupModeOnlineCacheOnly

	};

	/**
	 * Types of data that can be delivered in a search response
	 */
	enum GnLookupData
	{
		kLookupDataInvalid = 0,

		/**
		 * Indicates whether a response should include data for use in fetching content (like images).
		 * <p><b>Remarks:</b></p>
		 * An application's client ID must be entitled to retrieve this specialized data. Contact your
		 *	Gracenote Global Services and Support representative with any questions about this enhanced
		 *	functionality.
		 */
		kLookupDataContent,

		/**
		 * Indicates whether a response should include any associated classical music data.
		 * <p><b>Remarks:</b></p>
		 * An application's license must be entitled to retrieve this specialized data. Contact your
		 * Gracenote Global Services and Support representative with any questions about this enhanced functionality.
		 */
		kLookupDataClassical,

		/**
		 * Indicates whether a response should include any associated sonic attribute data.
		 * <p><b>Remarks:</b></p>
		 * An application's license must be entitled to retrieve this specialized data. Contact your
		 * Gracenote Global Services and Support representative with any questions about this enhanced functionality.
		 */
		kLookupDataSonicData,

		/**
		 * Indicates whether a response should include associated attribute data for GNSDK Playlist.
		 * <p><b>Remarks:</b></p>
		 * An application's license must be entitled to retrieve this specialized data. Contact your
		 * Gracenote Global Services and Support representative with any questions about this enhanced functionality.
		 */
		kLookupDataPlaylist,

		/**
		 * Indicates whether a response should include external IDs (third-party IDs).
		 * <p><b>Remarks:</b></p>
		 * External IDs are third-party IDs associated with the results (such as an Amazon ID),
		 *	configured specifically for your application.
		 * An application's client ID must be entitled to retrieve this specialized data. Contact your
		 * Gracenote Global Services and Support representative with any questions about this enhanced functionality.
		 * External IDs can be retrieved from applicable query response objects.
		 */
		kLookupDataExternalIds,

		/**
		 * Indicates whether a response should include global IDs.
		 */
		kLookupDataGlobalIds,

		/**
		 * Indicates whether a response should include additional credits.
		 */
		kLookupDataAdditionalCredits

	};

	/**
	 * Thread priority values for GNSDK multi-threaded functionality such as  MusicID-File.
	 */
	enum GnThreadPriority
	{
		kThreadPriorityInvalid = 0,

		/**
		 * Use of default thread priority.
		 */
		kThreadPriorityDefault,

		/**
		 * Use idle thread priority.
		 */
		kThreadPriorityIdle,

		/**
		 * Use low thread priority (default).
		 */
		kThreadPriorityLow,

		/**
		 * Use normal thread priority.
		 */
		kThreadPriorityNormal,

		/**
		 * Use high thread priority.
		 */
		kThreadPriorityHigh

	};

	/**
	 * Fingerprint algorithm type.
	 */
	enum GnFingerprintType
	{
		/**
		 * Invalid fingerprint type
		 */
		kFingerprintTypeInvalid = 0,

		/**
		 * Specifies a fingerprint data type for generating fingerprints used with MusicID-File.
		 * <p><b>Remarks:</b></p>
		 * A MusicID-File fingerprint is a fingerprint of the beginning 16 seconds of the file.
		 * <p><b>Note:</b></p>
		 * Do not design your application to submit only 16 seconds of a file; the
		 * application must submit data until GNSDK indicates it has received enough input.
		 * Use this fingerprint type when identifying audio from a file source (MusicID-File).
		 */
		kFingerprintTypeFile,

		/**
		 *  Specifies a fingerprint used for identifying an ~3-second excerpt from an audio stream.
		 *  Use this fingerprint type when identifying a continuous stream of audio data and when retrieving
		 *  Track Match Position values. The fingerprint represents a
		 *  specific point in time of the audio stream as denoted by the audio provided when the fingerprint
		 *  is generated.
		 *  <p><b>Note:</b></p>
		 *  Do not design your application to submit only 3 seconds of audio data; the
		 *  application must submit audio data until GNSDK indicates it has received enough input.
		 *  You must use this fingerprint or its 6-second counterpart when generating results where match
		 *  position is required.
		 *  The usage of this type of fingerprint must be configured to your specific User ID, otherwise queries
		 *  of this type will not succeed.
		 */
		kFingerprintTypeStream3,

		/**
		 *  Specifies a fingerprint used for identifying an ~6-second excerpt from and audio stream.
		 *  This is the same as kFingerprintTypeStream3 but requires more audio data to generate
		 *  but could be more accurate.
		 *  For additional notes see kFingerprintTypeStream3.
		 */
		kFingerprintTypeStream6,

		/**
		 * @deprecated NB: This key has been marked as deprecated and will be removed from the next major release.
		 *      Use kFingerprintTypeFile instead.
		 */
		kFingerprintTypeCMX,

		/**
		 * @deprecated NB: This key has been marked as deprecated and will be removed from the next major release.
		 *      Use kFingerprintTypeStream3 or kFingerprintTypeStream6 instead.
		 */
		kFingerprintTypeGNFPX

	};

	/** @internal GnStatus @endinternal
	 *  Indicates messages that can be received in status callbacks.
	 * @ingroup StatusCallbacks_TypesEnums
	 */
	enum GnStatus
	{
		/** @internal kStatusUnknown @endinternal
		 * Status unknown.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusUnknown = 0,

		/* Basic messages */

		/** @internal kStatusBegin @endinternal
		 * Issued once per application function call, at the beginning of the call; percent_complete = 0.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusBegin,

		/** @internal kStatusProgress @endinternal
		 * Issued roughly 10 times per application function call; percent_complete values between 1-100.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusProgress,

		/** @internal kStatusComplete @endinternal
		 * Issued once per application function call, at the end of the call; percent_complete = 100.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusComplete,

		/** @internal kStatusErrorInfo @endinternal
		 * Issued when an error is encountered. If sent, call #gnsdk_manager_error_info().
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusErrorInfo,

		/* Advanced messages */

		/** @internal kStatusConnecting @endinternal
		 * Issued when connecting to network.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusConnecting,

		/** @internal kStatusSending @endinternal
		 * Issued when uploading.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusSending,

		/** @internal kStatusReceiving @endinternal
		 * Issued when downloading.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusReceiving,

		/** @internal kStatusDisconnected @endinternal
		 * Issued when disconnected from network.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusDisconnected,

		/** @internal kStatusReading @endinternal
		 * Issued when reading from storage.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusReading,

		/** @internal kStatusWriting @endinternal
		 * Issued when writing to storage.
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusWriting,            /* issued whenever writing to storage. */

		/** @internal gnsdk_status_cancelled @endinternal
		 * Issued when transaction/query is cancelled
		 * @ingroup StatusCallbacks_TypesEnums
		 */
		kStatusCancelled     

	};

	/**
	 * Languages used when specifying which locale or list to load and preferring a language for metadata returned in
	 * responses.
	 */
	enum GnLanguage
	{
		kLanguageInvalid = 0,

		kLanguageArabic,
		kLanguageBulgarian,
		kLanguageChineseSimplified,
		kLanguageChineseTraditional,
		kLanguageCroatian,
		kLanguageCzech,
		kLanguageDanish,
		kLanguageDutch,
		kLanguageEnglish,
		kLanguageFarsi,
		kLanguageFinnish,
		kLanguageFrench,
		kLanguageGerman,
		kLanguageGreek,
		kLanguageHungarian,
		kLanguageIndonesian,
		kLanguageItalian,
		kLanguageJapanese,
		kLanguageKorean,
		kLanguageNorwegian,
		kLanguagePolish,
		kLanguagePortuguese,
		kLanguageRomanian,
		kLanguageRussian,
		kLanguageSerbian,
		kLanguageSlovak,
		kLanguageSpanish,
		kLanguageSwedish,
		kLanguageThai,
		kLanguageTurkish,
		kLanguageVietnamese
	};

	/**
	 * Regions used when specifying which locale or list is loaded.
	 */
	enum GnRegion
	{
		/** Default region. A region will be selected based on what's available. */
		kRegionDefault = 0,

		/** Global region */
		kRegionGlobal,

		/** United States region */
		kRegionUS,

		/** Japan region */
		kRegionJapan,

		/** China region */
		kRegionChina,

		/** Taiwan region */
		kRegionTaiwan,

		/** Korea region */
		kRegionKorea,

		/** Europe region */
		kRegionEurope,

		/** Deprecated, will be removed in a future release, use kRegionUS. */
		kRegionNorthAmerica,

		/** Latin America region */
		kRegionLatinAmerica,

		/** India region */
		kRegionIndia
	};

	/**
	 * Verbosity of Gracenote data
	 */
	enum GnDescriptor
	{
		kDescriptorDefault = 0,

		kDescriptorSimplified,
		kDescriptorDetailed
	};

	/**
	 * Content types
	 */
	enum GnContentType
	{
		kContentTypeNull = 0,
		kContentTypeUnknown = 1,

		kContentTypeImageCover,
		kContentTypeImageArtist,
		kContentTypeImageVideo,
		kContentTypeBiography,
		kContentTypeReview,
		kContentTypeNews,
		kContentTypeArtistNews,
		kContentTypeListenerComments,
		kContentTypeReleaseComments
	};

	/**
	 * Image size
	 */
	enum GnImageSize
	{
		kImageSizeUnknown = 0,

		kImageSize75,
		kImageSize110,
		kImageSize170,
		kImageSize220,
		kImageSize300,
		kImageSize450,
		kImageSize720,
		kImageSize1080,

		/* Size aliases */
		kImageSizeThumbnail = kImageSize75,
		kImageSizeSmall     = kImageSize170,
		kImageSizeMedium    = kImageSize450,
		kImageSizeLarge     = kImageSize720,
		kImageSizeXLarge    = kImageSize1080

	};


	/**
	 * Base object for managing objects in natively running GNSDK.
	 */
	class GnObject
	{
	public:
		/**
		 *  Get flag indicating if GnObject contains no native object handle
		 *  @return True if null, false otherwise
		 */
		bool
		IsNull() const { return (GNSDK_NULL == handle_);}

		/**
			*  operator ==
			*/
		virtual bool operator == (const GnObject& rhs) const { return (handle_ == rhs.handle_); }
	
		/**
			*  operator !=
			*/
		virtual bool operator != (const GnObject& rhs) const { return !(operator==(rhs)); };
		
	protected:
		GnObject() throw (GnError) : handle_(GNSDK_NULL) { }
		GnObject(gnsdk_handle_t handle) throw (GnError);
		GnObject(const GnObject& copy) throw (GnError);

		virtual
		~GnObject();

		GnObject&
		operator= (const GnObject& rhs) throw (GnError);

		void
		AcceptOwnership(gnsdk_handle_t handle) throw (GnError);

		gnsdk_handle_t
		Handle() const { return handle_; }

		template<typename HandleType>
		HandleType
		get() const { return static_cast<HandleType>( handle_ ); }

	private:

		gnsdk_handle_t handle_;
	};


	/**
	 * Managed immutable string as returned by GNSDK.
	 */
	class GnString : public GnObject
	{
	public:
		GNWRAPPER_ANNOTATE

		/**
		 * Construct an empty GnString object
		 */
		GnString() : m_cstr_ref(GNSDK_NULL), m_cstr(GNSDK_NULL), m_str(GNSDK_NULL) { }

		/**
		 * Construct a GnString object from a native constant string
		 * @param str [in] Native string
		 */
		GnString(gnsdk_cstr_t str) : m_cstr_ref(GNSDK_NULL), m_cstr(GNSDK_NULL), m_str(GNSDK_NULL) { set_(str); }

		/**
		 * Construct a GnString object from an existing GnString object
		 * @param str [in] GnString object
		 */
		GnString(const GnString& str) : GnObject(str), m_cstr_ref(str.m_cstr_ref), m_cstr(str.m_cstr_ref), m_str(GNSDK_NULL)
		{
			if (!str.m_cstr_ref)
				set_(str.m_str);
		}

		virtual
		~GnString()
		{
			delete[] m_str;
		}

		GnString&
		operator=(const GnString& str)
		{
			if (str.m_cstr_ref)
			{
				if (str.m_cstr_ref != m_cstr_ref)
				{
					GnObject::operator=(str);
					m_cstr_ref = str.m_cstr_ref;
					m_cstr = m_cstr_ref;

					delete[] m_str;
					m_str = GNSDK_NULL;
				}
			}
			else
			{
				set_(str.m_cstr);
			}
			return *this;
		}

		GnString&
		operator=(gnsdk_cstr_t str)
		{
			set_(str);

			if (m_cstr_ref)
			{
				this->AcceptOwnership(GNSDK_NULL);
				m_cstr_ref = GNSDK_NULL;
			}
			return *this;
		}

#ifndef SWIG
		operator
		gnsdk_cstr_t() const { return m_cstr; }
#endif

		/**
		 * Get native string
		 * @return Native string
		 */
		const char*
		c_str() const { return m_cstr; }

		/**
		 * Get flag indicating if string object contains no string
		 * @return True of empty, false otherwise
		 */
		bool
		IsEmpty() const
		{
			if (m_cstr && *m_cstr)
				return false;
			return true;
		}

		/**
		 * Internally used factory for special SDK-managed strings
		 * @param str	[in] Native string
		 * @return Managed string
		 */
		static GnString
		manage(gnsdk_cstr_t str)
		{
			return GnString(str, true);
		}

	private:
		GnString(gnsdk_cstr_t str, bool bManaged) :
			m_cstr_ref(str), m_cstr(str), m_str(GNSDK_NULL)
		{
			(void)bManaged;
			this->AcceptOwnership((gnsdk_handle_t)str);
		}

		void
		set_(gnsdk_cstr_t str)
		{
			delete[] m_str;

			gnsdk_size_t len = gnstd::gn_strlen(str);
			m_str = new char[len+1];
			if (m_str)
			{
				gnstd::gn_strcpy(m_str, len+1, str);
				m_str[len] = 0;
			}

			m_cstr = m_str;
		}

		gnsdk_cstr_t	m_cstr_ref;
		gnsdk_cstr_t	m_cstr;
		gnsdk_str_t		m_str;
	};


	/**
	 * Interface for defining a Cancellable object
	 */
	class IGnCancellable
	{
	public:
		GNWRAPPER_ANNOTATE

		virtual
		~IGnCancellable() { }

		/**
		 * Set cancel state
		 * @param bCancel 	[in] Cancel state
		 */
		virtual void
		SetCancel(bool bCancel) = 0;

		/**
		 * Get cancel state
		 * @return True of cancelled, false otherwise
		 */
		virtual bool
		IsCancelled() = 0;
	};

	/**
	 * Delegate interface for receiving status updates as GNSDK operations are performed.
	 */
	class IGnStatusEvents
	{
	public:
		GNWRAPPER_ANNOTATE

		virtual
		~IGnStatusEvents() { }

		/**
		 * Status change notification method. Override to receive notification.
		 * @param status				[in] Status type
		 * @param percentComplete		[in] Operation progress
		 * @param bytesTotalSent		[in] Total number of bytes sent
		 * @param bytesTotalReceived	[in] Total number of bytes received
		 * @param canceller				[in] Object that can be used to canel the operation
		 */
		virtual void
		StatusEvent(GnStatus status, gnsdk_uint32_t percentComplete, gnsdk_size_t bytesTotalSent, gnsdk_size_t bytesTotalReceived, IGnCancellable& canceller) = 0;
	};


	class GnLocale;
	class GnList;

	/**
	 * Delegate interface for receiving system events
	 */
	class IGnSystemEvents
	{
	public:
		GNWRAPPER_ANNOTATE

		virtual
		~IGnSystemEvents() { }

		/**
		 * Notification event that the give Locale should be updated.
		 * @param locale	[in] Locale detected as out of date
		 */
		virtual void
		LocaleUpdateNeeded(GnLocale& locale) = 0;

		/**
		 * Notification event that the given List should be updated.
		 * @param list		[in] List detected as out of date
		 */
		virtual void
		ListUpdateNeeded(GnList& list) = 0;

		/**
		 * Notifcation that GNSDK memory usage has gone over the set warning limit
		 * @param curMemSize		[in] Current memory size
		 * @param memoryWarnSize	[in] Memory warning size
		 */
		virtual void
		SystemMemoryWarning(gnsdk_size_t curMemSize, gnsdk_size_t memoryWarnSize) = 0;
	};

	class GnUser;

	/**
	 * Configuration options for GnUser
	 */
	class GnUserOptions
	{
	public:
		GNWRAPPER_ANNOTATE

		/**
		 * Constructs empty GnUserOptions object. It is not associated with any GnUser object.
		 */
		GnUserOptions():weakhandle_(GNSDK_NULL) { }

		/**
		 * Get lookup mode.
		 * @return Lookup mode
		 */
		GnLookupMode
		LookupMode() throw (GnError);

		/**
		 * Set lookup mode.
		 * @param lookupMode	[in] Lookup mode
		 */
		void
		LookupMode(GnLookupMode lookupMode) throw (GnError);

		/**
		 * Get network proxy hostname
		 * @return Network proxy hostname
		 */
		gnsdk_cstr_t
		NetworkProxy() throw (GnError);

		/**
		 * Sets host name, username and password for proxy to route GNSDK queries through
		 * @param hostname	[in] Fully qualified host name with optional port number. If no port number
		 *                  is given the default port number is assumed to be 80.
		 *                  Example values are "http://proxy.mycompany.com:8080/", "proxy.mycompany.com:8080" and
		 *                  "proxy.mycompany.com"
		 * @param username  [in] Valid user name for the proxy server. Do not set this option if a username is not required.
		 * @param password  [in] Valid password for the proxy server. Do not set this option if a password is not required.
		 */
		void
		NetworkProxy(gnsdk_cstr_t hostname, gnsdk_cstr_t username, gnsdk_cstr_t password) throw (GnError);

		/**
		 * Gets the network time-out for all GNSDK queries
		 * @return Netwrk timeout
		 */
		gnsdk_uint32_t
		NetworkTimeout() throw (GnError);

		/**
		 * Sets the network time-out for all GNSDK queries in milliseconds.
		 * Value for this option is a string with a numeric value that indicates the number of milliseconds
		 * to set for network time-outs. For example for a 30-second time-out set option value as 30000
		 * @param timeout_ms	[in] Time-out in milliseconds
		 */
		void
		NetworkTimeout(gnsdk_uint32_t timeout_ms) throw (GnError);

		/**
		 * Get network local balance state
		 * @return Network load balance state
		 */
		bool
		NetworkLoadBalance() throw (GnError);

		/**
		 * Enables/Disable distributing queries across multiple Gracenote co-location facilities
		 * When not enabled, queries will generally resolve to a single co-location.
		 * To implement load balancing, enable this option.
		 * Value to enable this option must be a boolean value that indicates true.
		 * @param bEnable  [in] True to enable load balancing, false otherwise.
		 * <p><b>Note:</b></p>
		 * Ensure that any security settings (such as a firewall) in your network infrastructure do not
		 * affect outbound access and prevent GNSDK from transmitting queries to various hosts with unique IP
		 * addresses.
		 */
		void
		NetworkLoadBalance(bool bEnable) throw (GnError);

		/**
		 * Get the IP address of the network interface as configured for this User object
		 * @return IP address
		 */
		gnsdk_cstr_t
		NetworkInterface() throw (GnError);

		/**
		 * Set a specific network interface to be used with connections made by GNSDK utilizing this GnUser object.
		 * Choosing which interface to use can be beneficial for systems with multiple network interfaces. Without
		 * setting this option, connections will be made of the default network interface as decided by the
		 * operating system. To enable this option a valid local IP address of the desired network interface must be
		 * provided.
		 * @param nicIpAddress	IP address of a local network interface
		 */
		void
		NetworkInterface(gnsdk_cstr_t nicIpAddress) throw (GnError);

		/**
		 * Set information about this user
		 * @param location_id	[in] Set an IP address or country code to represent the location of user performing requests.
		 *                      Value for this parameter is a string with the IP address, or a 3-character country code
		 *                      for the client making the request. This is generally required when setting a proxy for
		 *                      GNSDK queries. Example values are "192.168.1.1", "usa" and "jpn".
		 * @param mfg			[in] The manufacturer of the device running the SDK. Used mostly by Gracenote Service to collect
		 *                      runtime statistics.
		 * @param os			[in] The OS version of the device running the SDK. Used mostly by Gracenote Service to collect
		 *                      runtime statistics.
		 * @param uid			[in] Unique ID of the device running the SDK, such as ESN. Used mostly by Gracenote Service to
		 *                      collect runtime statistics.
		 */
		void
		UserInfo(gnsdk_cstr_t location_id, gnsdk_cstr_t mfg, gnsdk_cstr_t os, gnsdk_cstr_t uid) throw (GnError);

		/**
		 * Gets cache expiration time in seconds
		 * @return Cache expiration time
		 */
		gnsdk_uint32_t
		CacheExpiration() throw (GnError);

		/**
		 * Sets the maximum duration for which an item in the GNSDK query cache is valid. This duration is in
		 * seconds, and must exceed one day.
		 * The value set for this option is a string with a numeric value that indicates the number of
		 * seconds to set for the expiration of cached queries. The maximum duration is set by Gracenote and
		 * varies by requirements.
		 * @param durationSec		[in] Expiration duration in seconds. For example, for a one day expiration
		 * 							set an option value of "86400" (60 seconds * 60 minutes * 24 hours); for a
		 * 							seven day expiration set an option value of "604800"
		 * 							(60 seconds * 60 minutes * 24 hours * 7 days).
		 * <p><b>Note:</b></p>
		 * Setting this option to a zero value (0) causes the cache to start deleting records upon cache
		 * hit, and not write new or updated records to the cache; in short, the cache effectively flushes
		 * itself. The cache will start caching records again once this option is set to a value greater than
		 * 0. Setting this option to a value less than 0 (for example: -1) causes the cache to use default
		 * expiration values.
		 *
		 * For mobile platforms Android, iOS and Windows Mobile the default cache expiration is zero.
		 *
		 * Cache expiration only has an effect if the application initializes a GNSDK storage provider such as
		 * GnStorageSqlite. Without a storage provider no cache can be created.
		 *
		 */
		void
		CacheExpiration(gnsdk_uint32_t durationSec) throw (GnError);

		/**
		 * Gets user option
		 * @param key	[in] Option key
		 * @return Option value
		 */
		gnsdk_cstr_t
		Custom(gnsdk_cstr_t key) throw (GnError);

		/**
		 * Sets User option
		 * @param key	[in] Option key
		 * @param value	[in] Option value
		 */
		void
		Custom(gnsdk_cstr_t key, gnsdk_cstr_t value) throw (GnError);

	private:
		friend class GnUser;

		gnsdk_user_handle_t weakhandle_;
	};

	/**
	 * Gracenote user
	 */
	class GnUser : public GnObject
	{
	public:
		GNWRAPPER_ANNOTATE

		/**
		 * Constructs empty GnUser object, no GnUser is created.
		 */
		GnUser() {}

		/**
		 * Reconstitutes user from serialized user handle data.
		 * Use this constructor to reconstitute a previously serialized GnUser. Reconstitution does not
		 * count towards the user count for your client in Gracenote Service.
		 * @param serializedUser		[in] String of serialized user handle data
		 * @param clientIdTest			[in_opt] Serialized user's expected Client ID
		 */
		GnUser(gnsdk_cstr_t serializedUser, gnsdk_cstr_t clientIdTest = GNSDK_NULL) throw (GnError);

		/**
		 * Create a GnUser with the provided Client ID and Client Tag. Check user storage for an
		 * existing user and if found reconstitutes the user. Reconstitution does not
		 * count towards the user count for your client in Gracenote Service. If not found in
		 * user storage a new user is created.
		 * @param userStore				[in] User store delegate
		 * @param clientId				[in] Client Identifer
		 * @param clientTag				[in] Client Tag
		 * @param applicationVersion	[in] Application version
		 */
		GnUser(IGnUserStore& userStore, gnsdk_cstr_t clientId, gnsdk_cstr_t clientTag, gnsdk_cstr_t applicationVersion) throw (GnError);

		/**
		 * Gets flag indicating if the current user is only registered for local queries
		 * @return True if local only user, fals eotherwise
		 */
		bool
		IsLocalOnly() const throw (GnError);

		/**
		 * Receive user options object. Use to set user options.
		 * @return User options object
		 */
		GnUserOptions&
		Options() { return options_; }

		/**
		 * Retrieve this user's native handle.
		 * @return Native handle
		 */
		gnsdk_user_handle_t
		native() const { return get<gnsdk_user_handle_t>(); }

	private:
		GnUserOptions             options_;
	};

	/**
	 *  License submission options
	 *  When your app allocates an SDK Manager object (GnManager) it passes the license data you obtained from GSS.
	 *  Your license determines the content you can access from the Gracenote service
	 *  License data can be submitted in different ways, as these enums indicate
	 */
	enum GnLicenseInputMode
	{
		kLicenseInputModeInvalid = 0,

	   /**
		* Submit license content as string
		*/
		kLicenseInputModeString,

	   /**
		* Submit license content in file
		*/
		kLicenseInputModeFilename,

	   /**
		* Submit license content from stdin
		*/
		kLicenseInputModeStandardIn
	};

	/**
	 * Gracenote user registration mode
	 */
	enum GnUserRegisterMode
	{
		/**
		 * Register a user via a netowrk connection with Gracenote Service. A user
		 * must be registered online before any online queries can be made against
		 * Gracenote Service.
		 */
		kUserRegisterModeOnline = 1,

		/**
		 * Register a user for local use only. User's registered locally can only
		 * perform queries against local databases and not against Gracenote
		 * Service.
		 */
		kUserRegisterModeLocalOnly
	};

	// compile time check of Template type . 
	template<typename T>
	struct is_pointer {  enum { result = false }; };

	template<typename T>
	struct is_pointer<T*> { enum { result = true }; };

	

	template <int v> class _int_to_type
	{
		enum { value  = v}; 
	};

	template<typename T, typename _Provider>
	class gn_facade_range_iterator
	{
	public:
		// typedefs for iterator_traits
		typedef T                value_type;
		typedef gnsdk_uint32_t   difference_type;
		typedef T*               pointer;
		typedef T&               reference;
		   
		// destructor and interface.
		~gn_facade_range_iterator() { }
		// this will never work for pointers to chars 
		bool operator == (const gn_facade_range_iterator& rhs) const { return ((rhs.pos_ == GN_UINT32_MAX || pos_ == GN_UINT32_MAX)?(current_ == rhs.current_) : (pos_ == rhs.pos_)); }
		bool operator != (const gn_facade_range_iterator& rhs) const { return !(*this == rhs); }

		reference operator* () throw (GnError){ return current_ ;}
		pointer operator-> () throw (GnError){ return &current_ ; }

		const gn_facade_range_iterator& operator++ () { current_ = provider_.get_data(++pos_); return *this; }
		gn_facade_range_iterator operator++(int) {  gn_facade_range_iterator result = *this; ++(*this) ; return result;}
		const gn_facade_range_iterator& operator+= (gnsdk_uint32_t offset) { pos_ += offset; current_ = provider_.get_data(pos_);return *this; }
#if defined (SWIG) || defined (SWIGCPP) 		
		// SWIG Specific interface.
		value_type next() throw (GnError) { return (current_ = provider_.get_data(pos_++)); }
		bool hasNext() { return  ! ((provider_.get_data(pos_)) == provider_.get_data(GN_UINT32_MAX)); }
#endif 
		difference_type distance(const gn_facade_range_iterator& itr) const { return ( itr.pos_ > pos_ ) ? itr.pos_ - pos_ : pos_ - itr.pos_; }

		gn_facade_range_iterator(_Provider provider, gnsdk_uint32_t pos)
			: provider_(provider), pos_(pos)
		{  if (pos_ < GN_UINT32_MAX) current_ = provider_.get_data(pos_); }
	private:
		_Provider      provider_;
		gnsdk_uint32_t pos_;
		T              current_;
	};
	
	// Partial template specialization for gnsdk_cstr_t types.
	// Notes: this is due to provider buffering. 
	template<typename _Provider>
	class gn_facade_range_iterator<gnsdk_cstr_t,_Provider>
	{
	public:
		// typedefs for iterator_traits
		typedef gnsdk_cstr_t     value_type;
		typedef gnsdk_uint32_t   difference_type;
		typedef gnsdk_cstr_t*    pointer;
		typedef gnsdk_cstr_t&    reference;
		   
		// destructor and interface.
		~gn_facade_range_iterator() { }
		// this will never work for pointers to chars 
		bool operator == (const gn_facade_range_iterator& rhs) const { return ((rhs.pos_ == GN_UINT32_MAX || pos_ == GN_UINT32_MAX)?( 0 == gnstd::gn_strcmp(current_,rhs.current_))  : (pos_ == rhs.pos_)); }
		bool operator != (const gn_facade_range_iterator& rhs) const { return !(*this == rhs); }

		reference operator* () { return current_ ;}
		pointer operator-> () { return &current_ ; }

		const gn_facade_range_iterator& operator++ () { current_ = provider_.get_data(++pos_); return *this; }
		gn_facade_range_iterator operator++(int) {  gn_facade_range_iterator result = *this; ++(*this) ; return result;}
		const gn_facade_range_iterator& operator+= (gnsdk_uint32_t offset) { pos_ += offset; current_ = provider_.get_data(pos_);return *this; }
#if defined (SWIG) || defined (SWIGCPP) 		
		// SWIG Specific interface.
		value_type next() throw (GnError) {return (current_ = provider_.get_data(pos_++)); }
		bool hasNext() { return ( 0 != gnstd::gn_strcmp(provider_.get_data(pos_),gnstd::kEmptyString)); }
#endif 
		difference_type distance(const gn_facade_range_iterator& itr) const { return ( itr.pos_ > pos_ ) ? itr.pos_ - pos_ : pos_ - itr.pos_; }

		gn_facade_range_iterator(_Provider provider, gnsdk_uint32_t pos)
			: provider_(provider), pos_(pos), current_(gnstd::kEmptyString)
		{ if (pos < GN_UINT32_MAX) current_ = provider_.get_data(pos_); }
		gn_facade_range_iterator(const gn_facade_range_iterator& copy)
			: provider_(copy.provider_), pos_(copy.pos_), current_(gnstd::kEmptyString)
		{ if (pos_ < GN_UINT32_MAX) {current_ = provider_.get_data(pos_);} }
		const gn_facade_range_iterator& operator=(const gn_facade_range_iterator& copy)
		{
			pos_ = copy.pos_;
			provider_ = copy.provider_; // is this necessary ? 
			current_ = (pos_ < GN_UINT32_MAX) ? provider_.get_data(pos_):gnstd::kEmptyString; 
		}

	private:
		_Provider      provider_;
		gnsdk_uint32_t pos_;
		gnsdk_cstr_t   current_;
	};
	

	template<typename T, typename _Provider>
	class gn_iterable_container
	{
//		enum { definedtype = is_pointer<T>::result };
	public:
		typedef gn_facade_range_iterator<T,_Provider>  iterator;
		gn_iterable_container(_Provider provider, gnsdk_uint32_t start)
			:provider_(provider), start_(start)
		{}
	
		
		typedef gnsdk_uint32_t   difference_type;

		// Interface for gn_iterable_container.
		iterator            begin() const              { return iterator(provider_, start_); }
		iterator            end() const				   { return iterator(provider_, GN_UINT32_MAX); }
	
		difference_type count() const				{ return provider_.count(); }
		iterator            at(difference_type index)  { return iterator(provider_, start_ + index); }
		iterator operator   [] (difference_type index) { return iterator(provider_, start_ + index); }
	private :
		
		_Provider provider_;
		gnsdk_uint32_t start_;
//		iterator _end(_int_to_type<false>) const { return iterator(provider_, GN_UINT32_MAX, T());}
//		iterator _end(_int_to_type<true>) const { return iterator(provider_, GN_UINT32_MAX, GNSDK_NULL); }
	
	};
	

	/*-------------------------------------------------------------------------
	** gn_canceller
	*/
	class gn_canceller : public IGnCancellable
	{
	public:
		gn_canceller() : m_bCancelled(false) { }
		virtual ~gn_canceller() { }
		virtual void SetCancel(bool bCancel) { m_bCancelled = bCancel; };
		virtual bool IsCancelled() { return m_bCancelled; };
	private:
		bool m_bCancelled;
	};

} /* namespace gracenote */


#endif /* _GNSDK_BASE_HPP_ */

