/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_MUSICID_STREAM_HPP_
#define _GNSDK_MUSICID_STREAM_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"
#include "metadata_music.hpp"
#include "gn_audiosource.hpp"

namespace gracenote
{
	namespace musicid_stream
	{
#if GNSDK_MUSICID_STREAM

		class GnMusicIdStream;
		class IGnMusicIdStreamEvents;


		/**
		 * GnMusicIdStreamProcessingStatus is currently considered to be experimental.
		 * An application should only use this option if it is advised by Gracenote Global Services and Support representative.
		 * Contact your Gracenote Global Services and Support representative with any questions about this enhanced functionality.
		 * @ingroup Music_MusicIDStream_TypesEnums
		 */
		enum GnMusicIdStreamProcessingStatus
		{
			kStatusProcessingInvalid = 0,

			kStatusProcessingAudioNone,
			kStatusProcessingAudioSilence,
			kStatusProcessingAudioNoise,
			kStatusProcessingAudioSpeech,
			kStatusProcessingAudioMusic,

			kStatusProcessingTransitionNone,
			kStatusProcessingTransitionChannelChange,
			kStatusProcessingTransitionContentToContent,

			kStatusProcessingErrorNoClassifier,

			kStatusProcessingAudioStarted,
			kStatusProcessingAudioEnded
		};

		/**
		 * The status of the channel or current identification query.
		 *  As a channel processes audio or as an identification query progresses
		 *  status notifications are provided via the events delegate.
		 * @ingroup Music_MusicIDStream_TypesEnums
		 */
		enum GnMusicIdStreamIdentifyingStatus
		{
			/** Invalid status
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingInvalid = 0,


			/** Identification query started
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingStarted,

			/** Fingerprint generated for sample audio
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingFpGenerated,

			/** Local query started for identification
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingLocalQueryStarted,

			/** Local query ended for identification
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingLocalQueryEnded,

			/** Online query started for identification
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingOnlineQueryStarted,

			/** Online query ended for identification
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingOnlineQueryEnded,

			/** Identification query ended
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kStatusIdentifyingEnded

		};

		
		enum GnMusicIdStreamApplicationEventType
		{
			/** No event
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kApplicationEventNone = 0,
			
			/** Metadata change event
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kApplicationEventMetadataChange,
			
			/** Broadcast channel change event
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kApplicationEventBroadcastChange,
			
			/** Broadcast pause event
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kApplicationEventPause,
			
			/** Broadcast resume event
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kApplicationEventResume
		};
		
		enum GnMusicIdStreamPreset
		{
			kPresetInvalid = 0,
		
			/** Application type mobile, i.e. audio is captured by microphone
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kPresetMicrophone,
			
			/** Application type radio, i.e. audio is captured at source (e.g. speaker)
			 * @ingroup Music_MusicIDStream_TypesEnums
			 */
			kPresetRadio
		};
		
		enum GnMusicIdStreamEvent
		{
			kEventInvalid = 0,
			
			kEventBroadcastMetadataChange
		};
		

		/**
		 * Configures options for GnMusicIdStream
		 */
		class GnMusicIdStreamOptions
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Specifies whether identification should be performed against local embedded databases or online.
			 *  @param lookupMode  [in] One of the GnLookupMode values
			 */
			void
			LookupMode(GnLookupMode lookupMode) throw (GnError);


			/**
			 *  Specifies which data should be included in the response
			 *  @param val 		[in] Set One of the #GnLookupData values
			 *  @param enable 	[in] True or false to enable or disable
			 */
			void
			LookupData(GnLookupData val, bool enable) throw (GnError);

			/**
			*  @deprecated To set language provide appropriate GnLocale object with GnMusicIdStream constructor
			*  @param preferredLanguage		[in] preferred language for result
			*/
			void
			PreferResultLanguage(GnLanguage preferredLanguage) throw (GnError);


			/**
			 * Specifies preference for results that contain the provided external identifier
			 * <p><b>Remarks:</b></p>
			 * This option is currently only supported when online processing is enabled and single
			 * result is specified.
			 * @param preferredExternalId 	[in] The name of an external identifier that should be preferred when selecting matches
			 */
			void
			PreferResultExternalId(gnsdk_cstr_t preferredExternalId) throw (GnError);


			/**
			 *  Specifies preference for results that have cover art associated
			 *  @param bEnable 	[in] Set prefer cover art.
			 */
			void
			PreferResultCoverart(bool bEnable) throw (GnError);


			/**
			 *  Specifies whether a response must return only the single best result.
			 *  When enabled a single full result is returned, when disabled multiple partial results may be returned.
			 *  @param bEnable 	[in] Option, default is true. True to enable, false to disable.
			 */
			void
			ResultSingle(bool bEnable) throw (GnError);


			/**
			 *  Specifies whether a response must return a range of results that begin at the specified values
			 *  @param resultStart  [in] Result range start value
			 *  <p><b>Remarks:</b></p>
			 *  This Option is useful for paging through results.
			 *  <p><b>Note:</b></p>
			 *  Gracenote Service enforces that the range start value must be less than or equal to the total
			 *  number of results. If you specify a range start value that is greater than the total number of
			 *  results, no results are returned.
			 */
			void
			ResultRangeStart(gnsdk_uint32_t resultStart) throw (GnError);

			/**
			 * Specifies the number of results to return in the response
			 * @param resultCount 	[in] Number of results
			 *
			 */
			void
			ResultCount(gnsdk_uint32_t resultCount) throw (GnError);
			
			/*
			 *  Specifies if revision check should be performed.
			 *  @param bEnable 	[in] Optional, default is true. True to enable, false to disable.
			 */
			/* RevisionCheck has not been implemented in C core yet */
			/* void
			RevisionCheck(bool bEnable) throw (GnError);
			*/
			
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
			 *  General option setting for custom string options
			 *  @param optionKey   [in] Option name
			 *  @param value	   [in] Option value
			 */
			void
			Custom(gnsdk_cstr_t optionKey, gnsdk_cstr_t value) throw (GnError);


		protected:
			GnMusicIdStreamOptions() : weakhandle_(GNSDK_NULL) { }

		private:
			DISALLOW_COPY_AND_ASSIGN(GnMusicIdStreamOptions);
			friend class GnMusicIdStream;
			gnsdk_musicidstream_channel_handle_t weakhandle_;

		};

		/**
		 * Identifies raw audio received in a continuous stream.
		 *
		 * GnMusicIdStream provides services for identifying music within a continuous audio stream.
		 * As data is received from the audio stream it is provided to GnMusicIdStream, when the application
		 * wishes to identify the audio it initializes an identification. The results of the identification
		 * are delivered asynchronously to a delegate object.
		 *
		 * GnMusicIdStream is a long-life object and, for a single audio stream, a single instance should
		 * be kept for as long as the application wishes to identify that audio stream. Where multiple audio
		 * streams require identification multiple instances of GnMusicIdStream are also required.
		 *
		 * GnMusicIdStream can be started and stopped as the audio stream starts and stops. There is no need
		 * to destroy and recreate a GnMusicIdStream instance due to breaks in the audio stream.
		 *
		 * <b>Audio Processing</b>
		 *
		 * After instantiating a GnMusicIdStream object the next step is to start audio processing and provide
		 * raw audio. Raw audio can be provided automatically or manually.
		 *
		 * To provide audio automatically your audio stream must be represented by an object that implements
		 * IGnAudioSource interface. Gracenote provides GnMic class on some platforms which is a representation
		 * of the device microphone, though you are encouraged to provide custom implementations representing
		 * any audio stream source your application needs.
		 *
		 * Internally GnMusicIdStream pulls data from the audio source interface in a loop, so some applications
		 * may wish to start automatic audio processing in a background thread to avoid stalling the main thread.
		 *
		 * Raw audio can also be manually provided to GnMusicIdStream. Audio processing must be started and the
		 * audio format provided, this allows GnMusicIdStream to establish internal buffers and audio
		 * processing modules. Once audio processing is started audio can then be written for processing as
		 * it is received from the stream.
		 *
		 * At any point audio processing can be stopped. When stopped automatic data fetching ceases or
		 * if audio data is being provided manually attempts to write data for processing
		 * manually will fail. Internally GnMusicIdStream clears and releases all buffers and audio
		 * processing modules. Audio processing can be restarted after it is stopped.
		 *
		 * If an error occurs during manual audio processing an exception is thrown during the audio write API
		 * call. If an error occurs during automatic audio processing the internal loop is exited and an exception
		 * thrown from the audio processing start API.
		 *
		 * <b>Identification</b>
		 *
		 * At any point the application can trigger an identification of the audio stream. The identification
		 * process identifies buffered audio. Only up to ~7 seconds of the most recent audio is buffered.
		 * If there isn't enough audio buffered for identification it will wait until enough audio is received.
		 *
		 * The identification process spawns a thread and completes asynchronously. However two identify methods
		 * are provided, one for synchronous and one for asynchronous. Where synchronous identification is invoked the
		 * identification is still performed asynchronously and results delivered via delegate implementing
		 * IGnMusicIdStreamEvents, but the identify method does not return until the identification is complete.
		 * Requests to identify audio while a previous pending identification request is pending will be ignored.
		 *
		 * Audio can be identified against Gracenote's online database or a local database. The default
		 * behavior is to attempt a match against the local database and if a match isn't found try the
		 * online database. Local matches are only possible if GnLookupLocalStream object has been
		 * instantiated and a MusicID-Stream fingerprint bundle ingested. See GnLookupLocalStream for
		 * more information on bundle ingestion.
		 *
		 * An identification process can be canceled. In this case the identification
		 * process stops and, if synchronous identification was invoked, the identify method returns.
		 * The identify error delegate method will be called with an "aborted" error when cancelled.
		 * Note cancelling does not cease audio processing and application can invoke identify again after
		 * cancelling.
		 *
		 * If an error occurs during identification it is reported in one of two ways.
		 * If the error occurs in the asynchronous identifying thread the error information is provided
		 * via identifying error delegate method and the result available delegate method will not be called.
		 * Where this delegate method is invoked no result available delegate method is invoked.
		 * If the error occurs prior to the asynchronous identifying thread being launched an exception
		 * is thrown from the identifying API.
		 *
		 * <b>Configuration</b>
		 *
		 * GnMusicIdStream is configurable via it's options object. The configuration determines, among
		 * other things, if identification is performed against local database, online database or both;
		 * the content returned with results (images, external IDs, etc.)
		 * See GnMusicIdStreamOptions for more information.
		 *
		 *
		 * Note: Customers must be licensed to implement use of a MusicID product in an application.
		 * Contact your Gracenote support representative with questions about product licensing and
		 * entitlement.
		 */
		class GnMusicIdStream : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Establishes an audio stream identification object with locale. The locale is used determine
			 *  the preferred language and script of stream identification results.
			 *  Note: Results are only returned in preferred language and script where available.
			 *  @param user 			[in] Gracenote user
			 *  @param preset 			[in] Gracenote musicID stream preset
			 *  @param locale 			[in] Gracenote locale
			 *  @param pEventDelegate 	[in] Audio processing and identification query events handler
			 */
			GnMusicIdStream(const GnUser& user, GnMusicIdStreamPreset preset, const GnLocale& locale, IGnMusicIdStreamEvents* pEventDelegate) throw (GnError);
			
			/**
			 *  Establishes an audio stream identification object with locale. The locale is used determine
			 *  the preferred language and script of stream identification results.
			 *  Note: Results are only returned in preferred language and script where available.
			 *  @param user 			[in] Gracenote user
			 *  @param preset			[in] Gracenote musicID stream preset
			 *  @param pEventDelegate 	[in] Audio processing and identification query events handler
			 */
			GnMusicIdStream(const GnUser& user, GnMusicIdStreamPreset preset, IGnMusicIdStreamEvents* pEventDelegate) throw (GnError);

			virtual
			~GnMusicIdStream( );


			/**
			 *  Retrieves the MusicID-Stream SDK's version string.
			 *  @return Version string if successful
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after successfully establishing a MusicID-Stream audio channel.
			 *  The returned string is a constant. Do not attempt to modify or delete.
			 *  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build)
			 *  Major: New functionality
			 *  Minor: New or changed features
			 *  Improvement: Improvements and fixes
			 *  Build: Internal build number
			 */
			static gnsdk_cstr_t Version();


			/**
			 *  Retrieves the MusicID-Stream SDK's build date string.
			 *  @return Build date string of the format: YYYY-MM-DD hh:mm UTC
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after successfully establishing a MusicID-Stream audio channel.
			 *  The returned string is a constant. Do not attempt to modify or delete.
			 *  Example build date string: 2008-02-12 00:41 UTC
			 */
			static gnsdk_cstr_t BuildDate();


			/**
			 * Get GnMusicIdStream options object. Use to configure your GnMusicIdStream instance.
			 * @return Options objects
			 */
			GnMusicIdStreamOptions&
			Options() { return options_; }

			/**
			 * Commence retrieving and processing audio from an object implementing the audio source interface.
			 * This is an alternate and often simpler method for providing audio to GnMusicIdStream
			 * instead of calling AudioProcessStart (audio format overload) and AudioProcess.
			 * To use this method the audio source to be identified must be accessible via an IGnAudioSource
			 * implementation. Custom implementations of IGnAudioSource are encouraged.
			 * Note: audio is retrieved from the audio source in a loop so some applications may wish to start
			 * automatic audio processing in a background thread to avoid stalling the main thread.
			 * @param audioSource	[in] Audio source to be identified
			 */
			void
			AudioProcessStart(IGnAudioSource& audioSource) throw (GnError);


			/**
			 * Initialize manual delivery of audio stream audio to GnMusicIdStream. GnMusicIdStream
			 * establishes buffers and audio processing modules, readying itself to receive audio.
			 * @param samplesPerSecond	[in] Number of samples per second
			 * @param bitsPerSample		[in] Number of bits per sample
			 * @param numberOfChannels	[in] Number of channels
			 */
			void
			AudioProcessStart(gnsdk_uint32_t samplesPerSecond, gnsdk_uint32_t bitsPerSample, gnsdk_uint32_t numberOfChannels ) throw (GnError);


			/**
			 * Stops audio processing. If audio processing was started with an object implementing IGnAudioSource
			 * the audio source is closed and data is no longer retrieved from that source. If manual audio processing
			 * was used future attempts to write audio data for processing will fail.
			 */
			void
			AudioProcessStop() throw (GnError);

			/**
			 * Provides audio manually for processing by GnMusicIdStream. This should not be called if
			 * audio processing was started with an object implementing the audio source interface.
			 * @param audioData			[in] Buffer containing sample audio
			 * @param audioDataLength	[in] Number of bytes of audio in pAudioBuffer
			 */
			void
			AudioProcess(const gnsdk_byte_t* audioData, gnsdk_size_t audioDataLength) throw (GnError);

			/**
			 * @deprecated Will be removed next release, use IdentifyAlbumAsync and WaitForIdentify instead.
			 * Identifying the audio in the audio stream and blocks until identification is
			 * complete. Results are delivered asynchronously via IGnMusicIdStreamEvents delegate.
			 */
			void
			IdentifyAlbum() throw (GnError);

			/**
			 * Identifying the audio in the audio stream. Results are delivered
			 * asynchronously via IGnMusicIdStreamEvents delegate.
			 */
			void
			IdentifyAlbumAsync() throw (GnError);

			/**
			 * Wait for currently running identify call to complete (up to timeout_ms milliseconds).
			 * Returns true if identification completed in the timeout period, false if not
			 * @param timeout_ms	[in] Timeout in milliseconds
			 * @return true			True if completed, false if timed out
			 */
			bool
			WaitForIdentify(gnsdk_uint32_t timeout_ms) throw (GnError);

			/**
			 * Cancel the current identify operation blocking until the identification has stopped. 
			 * Cannot be called from within a GnMusicIdStream delegate callback, use the canceller provided 
			 * in the callback instead. This will throw an exception if it is used with the automatic mode 
			 * on.
			 */
			void 
			IdentifyCancel() throw (GnError); 

			/**
			 * Get identify cancel state.
			 * @return Cancel state
			 */
			
			
// Note: hiding for GFM release July 2014 - remove condition after GFM release made
#ifndef PRODUCT_GNSDK_MOBILE
			/**
			 * Specifies automatic recognition should be enable or disabled
			 * @param bEnable 	[in] Option, default is false. True to enable, false to disable
			 *
			 */
			void
			AutomaticIdentifcation(bool bEnable) throw (GnError);
			
			/**
			 * Specifies automatic recognition is enabled or disabled
			 * @return true			True if automatic recognition is enabled
			 *
			 */
			bool
			AutomaticIdentifcation() throw (GnError);
#endif /* !PRODUCT_GNSDK_MOBILE */
			/**
			 * Specifies a change in application for a given GnMusicIdStream
			 * @param event 	[in] One of the GnMusicIdStreamApplicationEventType Enum Values
			 *
			 */	
			void
			Event(GnMusicIdStreamEvent event) throw (GnError);

			/**
			 * Provides broadcast metadata to a query handle for improved match resolution
			 * @param broadcastMetadataKey 		[in] A brodcast metadata input type from the available MusicIDStream Broadcast Metadata Keys  
			 * @param broadcastMetadataValue 	[in] A string value that corresponds to the defined broadcast metadata key
			 *
			 */	
			void
			BroadcastMetadata(gnsdk_cstr_t broadcastMetadataKey, gnsdk_cstr_t broadcastMetadataValue) throw (GnError);
			
			/**
			 * Get the event handler provided on construction
			 * @return Event handler
			 */
			IGnMusicIdStreamEvents* EventHandler() { return eventhandler_; }

		private:

			IGnMusicIdStreamEvents*     eventhandler_;
			GnMusicIdStreamOptions      options_;
			IGnAudioSource*				p_audioSource;

			/* dissallow assignment operator */
			DISALLOW_COPY_AND_ASSIGN(GnMusicIdStream);

		
		};

		/**
		 * Delegate interface for receiving GnMusicIdStream events
		 */
		class IGnMusicIdStreamEvents : public IGnStatusEvents
		{
		public:
			GNWRAPPER_ANNOTATE

			virtual
			~IGnMusicIdStreamEvents() { };



			/**
			 * MusicIdStreamProcessingStatusEvent is currently considered to be experimental.
			 * An application should only use this option if it is advised by Gracenote Global Services and Support representative.
			 * Contact your Gracenote Global Services and Support representative with any questions about this enhanced functionality.
			 * @param status		Status
			 * @param canceller		Cancellable that can be used to cancel this processing operation
			 */
			virtual void
			MusicIdStreamProcessingStatusEvent(GnMusicIdStreamProcessingStatus status, IGnCancellable& canceller) = 0;

			/**
			 * Provides GnMusicIdStream identifying status notification
			 * @param status		Status
			 * @param canceller		Cancellable that can be used to cancel this identification operation
			 */
			virtual void
			MusicIdStreamIdentifyingStatusEvent(GnMusicIdStreamIdentifyingStatus status, IGnCancellable& canceller) = 0;

			/**
			 * A result is available for a GnMusicIdStream identification request
			 * @param result		Result
			 * @param canceller		Cancellable that can be used to cancel this identification operation
			 */
			virtual void
			MusicIdStreamAlbumResult(metadata::GnResponseAlbums& result, IGnCancellable& canceller) = 0;

			/**
			 * Identifying request could not be completed due to the reported error condition
			 * @param completeError	Error condition information
			 */
			virtual void
			MusicIdStreamIdentifyCompletedWithError(GnError& completeError) = 0;
		};

#endif /* GNSDK_MUSICID_STREAM */

	} // namespace musicid_stream

}     // namespace gracenote


#endif // _GNSDK_MUSICID_STREAM_HPP_

