/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_musicidstream.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk_manager.hpp"

#if GNSDK_MUSICID_STREAM

#include "gnsdk_musicidstream.hpp"
#include "metadata_music.hpp"


using namespace gracenote;
using namespace gracenote::metadata;
using namespace gracenote::musicid_stream;




static gnsdk_void_t GNSDK_CALLBACK_API 
			callback_mids_processing_status(
				gnsdk_void_t*                				callback_data,
				gnsdk_musicidstream_processing_status_t 	status,
				gnsdk_bool_t*                				p_abort
				);

static gnsdk_void_t GNSDK_CALLBACK_API
			callback_mids_identifying_status(
				gnsdk_void_t*                				callback_data,
				gnsdk_musicidstream_identifying_status_t 	status,
				gnsdk_bool_t*                				p_abort
				);

			static void GNSDK_CALLBACK_API
			callback_status(
				void*          								callback_data,
				gnsdk_status_t 								status,
				gnsdk_uint32_t 								percent_complete,
				gnsdk_size_t   								bytes_total_sent,
				gnsdk_size_t   								bytes_total_received,
				gnsdk_bool_t*  								p_abort
			 	);

			static gnsdk_void_t GNSDK_CALLBACK_API
			callback_result_available(
				gnsdk_void_t*                        		callback_data,
				gnsdk_musicidstream_channel_handle_t 		p_musicidstream_channel_handle,
				gnsdk_gdo_handle_t                   		response_gdo,
				gnsdk_bool_t*                        		p_abort
				);

			static gnsdk_void_t GNSDK_CALLBACK_API
			callback_completed_with_error(
				gnsdk_void_t* 								callback_data,
				gnsdk_musicidstream_channel_handle_t		p_musicidstream_channel_handle,
				const gnsdk_error_info_t* 					p_error_info
				);

static gnsdk_musicidstream_callbacks_t  callbacks = 
{
	callback_status,
	callback_mids_processing_status,
	callback_mids_identifying_status,
	callback_result_available,
	callback_completed_with_error
};

/******************************************************************************
** GnMusicIdStreamOptions
*/

/*-----------------------------------------------------------------------------
 *  LookupMode
 */
void
GnMusicIdStreamOptions::LookupMode(GnLookupMode lookupMode) throw (GnError)
{
	gnsdk_error_t error;

	switch (lookupMode)
	{
	case kLookupModeLocal:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_LOCAL);
		break;

	case kLookupModeOnline:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE);
		break;

	case kLookupModeOnlineNoCache:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_NOCACHE);
		break;

	case kLookupModeOnlineNoCacheRead:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_NOCACHEREAD);
		break;

	case kLookupModeOnlineCacheOnly:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_CACHEONLY);
		break;

	default:
		return;
	}

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  LookupData
 */
void
GnMusicIdStreamOptions::LookupData(GnLookupData lookupData, bool bEnable) throw (GnError)
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
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_ENABLE_CONTENT_DATA, sz_enable);
		break;

	case kLookupDataClassical:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_ENABLE_CLASSICAL_DATA, sz_enable);
		break;

	case kLookupDataSonicData:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_ENABLE_SONIC_DATA, sz_enable);
		break;

	case kLookupDataPlaylist:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_ENABLE_PLAYLIST, sz_enable);
		break;

	case kLookupDataExternalIds:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_ENABLE_EXTERNAL_IDS, sz_enable);
		break;

	case kLookupDataGlobalIds:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_ENABLE_GLOBALIDS, sz_enable);
		break;

	case kLookupDataAdditionalCredits:
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_ADDITIONAL_CREDITS, sz_enable);
		break;

	default:
		return;
	}

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  PreferResultLanguage
 */
void
GnMusicIdStreamOptions::PreferResultLanguage(GnLanguage preferredLanguage) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_PREFERRED_LANG, gnconvert::_convertLangCppC(preferredLanguage));
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  PreferResultExternalId
 */
void
GnMusicIdStreamOptions::PreferResultExternalId(gnsdk_cstr_t preferredExternalId) throw (GnError)
{
	gnsdk_error_t error;


	error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_RESULT_PREFER_XID, preferredExternalId);
	if ( error ) { throw GnError( ); }
}


/*-----------------------------------------------------------------------------
 *  ResultSingle
 */
void
GnMusicIdStreamOptions::ResultSingle(bool bEnable) throw (GnError)
{
	gnsdk_error_t error;

	if (bEnable)
	{
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_RESULT_SINGLE, GNSDK_VALUE_TRUE);
	}
	else
	{
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_RESULT_SINGLE, GNSDK_VALUE_FALSE);
	}

	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  ResultRangeStart
 */
void
GnMusicIdStreamOptions::ResultRangeStart(gnsdk_uint32_t resultStart) throw (GnError)
{
	char          buffer[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buffer, sizeof(buffer), resultStart);
	error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_RESULT_RANGE_START, buffer);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  ResultCount
 */
void
GnMusicIdStreamOptions::ResultCount(gnsdk_uint32_t resultCount) throw (GnError)
{
	char          buffer[16];
	gnsdk_error_t error;

	gnstd::gn_itoa(buffer, sizeof(buffer), resultCount);
	error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_RESULT_RANGE_SIZE, buffer);
	if (error) { throw GnError(); }
}


/* RevisionCheck has not been implemented in C core yet */
/*-----------------------------------------------------------------------------
 *  RevisionCheck
 */
/*
void
GnMusicIdStreamOptions::RevisionCheck(bool bEnable) throw (GnError)
{
	gnsdk_error_t error;

	if (bEnable)
	{
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_REVISION_CHECK, GNSDK_VALUE_TRUE);
	}
	else
	{
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_REVISION_CHECK, GNSDK_VALUE_FALSE);
	}

	if (error) { throw GnError(); }
}
*/

/*-----------------------------------------------------------------------------
 *  PreferResultCoverart
 */
void
GnMusicIdStreamOptions::PreferResultCoverart(bool bEnable) throw (GnError)
{
	gnsdk_error_t error;

	if (bEnable)
	{
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_RESULT_PREFER_COVERART, GNSDK_VALUE_TRUE);
	}
	else
	{
		error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_MUSICIDSTREAM_OPTION_RESULT_PREFER_COVERART, GNSDK_VALUE_FALSE);
	}

	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  NetworkInterface
 */
void
GnMusicIdStreamOptions::NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_musicidstream_channel_option_set(weakhandle_, GNSDK_QUERY_OPTION_NETWORK_INTERFACE, ipAddress);
	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  Custom
 */
void
GnMusicIdStreamOptions::Custom(gnsdk_cstr_t optionKey, gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidstream_channel_option_set(weakhandle_, optionKey, value);
	if (error) { throw GnError(); }
}


/******************************************************************************
** GnMusicIdStream
*/

GnMusicIdStream::GnMusicIdStream(const GnUser& user, GnMusicIdStreamPreset preset, const GnLocale& locale, IGnMusicIdStreamEvents* pEventHandler)  throw (GnError) :
	eventhandler_(pEventHandler),
	p_audioSource(GNSDK_NULL)
{
	gnsdk_musicidstream_channel_handle_t	channel_handle = GNSDK_NULL;
	gnsdk_error_t							error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_MUSICIDSTREAM);

	error = gnsdk_musicidstream_channel_create(user.native(), (gnsdk_musicidstream_preset_t)preset, &callbacks, this, &channel_handle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(channel_handle);

	error = gnsdk_musicidstream_channel_set_locale(channel_handle, locale.native());
	if (error) { throw GnError(); }

	options_.weakhandle_ = channel_handle;
}

GnMusicIdStream::GnMusicIdStream(const GnUser& user, GnMusicIdStreamPreset preset, IGnMusicIdStreamEvents* pEventHandler)  throw (GnError) :
	eventhandler_(pEventHandler),
	p_audioSource(GNSDK_NULL)
{
	gnsdk_musicidstream_channel_handle_t	channel_handle	= GNSDK_NULL;
	gnsdk_error_t							error			= GNSDK_SUCCESS;
	
	_gnsdk_internal::module_initialize(GNSDK_MODULE_MUSICIDSTREAM);
	
	error = gnsdk_musicidstream_channel_create(user.native(), (gnsdk_musicidstream_preset_t)preset, &callbacks, this, &channel_handle);
		
	if (error) { throw GnError(); }
	
	this->AcceptOwnership(channel_handle);
	
	options_.weakhandle_ = channel_handle;
}


GnMusicIdStream::~GnMusicIdStream()
{
	/*
	** Nothing to do here, cleanup was done when releasing channel handle
	*/
}


/*-----------------------------------------------------------------------------
 *  Version
 */
gnsdk_cstr_t
GnMusicIdStream::Version()
{
	return gnsdk_musicidstream_get_version();
}


/*-----------------------------------------------------------------------------
 *  BuildDate
 */
gnsdk_cstr_t
GnMusicIdStream::BuildDate()
{
	return gnsdk_musicidstream_get_build_date();
}

/*-----------------------------------------------------------------------------
 *  AudioProcessStart
 */
void
GnMusicIdStream::AudioProcessStart(IGnAudioSource& audioSource) throw (GnError)
{
#define AUDIO_BUFFER_DURATION_MS 100
	gnsdk_byte_t   *audioBuffer;
	gnsdk_size_t audioBufferSize = 0;
	gnsdk_error_t  error     = GNSDK_SUCCESS;
	gnsdk_size_t bytesRead = 0;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_DSP);

	error = audioSource.SourceInit();
	if (error)
	{
		gnsdk_error_info_t error_info;
		error_info.error_api = "GnMusicIdStream::AudioProcessStart";
		error_info.error_code = error;
		error_info.error_description = "Failed to initialize audio source";
		error_info.error_module = "GnMusicIdStream";
		error_info.source_error_code = error_info.error_code;
		error_info.source_error_module = error_info.error_module;
		throw GnError(&error_info);
	}

	error = gnsdk_musicidstream_channel_audio_begin(
		get<gnsdk_musicidstream_channel_handle_t>(),
		audioSource.SamplesPerSecond(),
		audioSource.SampleSizeInBits(),
		audioSource.NumberOfChannels() );
	if (error) { throw GnError(); }

	audioBufferSize = (AUDIO_BUFFER_DURATION_MS * audioSource.SamplesPerSecond() * audioSource.SampleSizeInBits()/8 * audioSource.NumberOfChannels())/1000;

	audioBuffer = new gnsdk_byte_t[audioBufferSize];

	// grab audio source which works as flag to tell rest of this class an
	// audio pull loop is active and an audio source must be closed if audio is stopped
	p_audioSource = &audioSource;
	while (!error)
	{
		bytesRead = audioSource.GetData(audioBuffer, audioBufferSize);
		if (bytesRead == 0)
		{
			break;
		}

		error = gnsdk_musicidstream_channel_audio_write(get<gnsdk_musicidstream_channel_handle_t>(), audioBuffer, bytesRead);

	}
	// only call end if no error and our audio source flag is still set, this indicates end was not called elsewhere
	if (!error && p_audioSource)
	{
		error = gnsdk_musicidstream_channel_audio_end(get<gnsdk_musicidstream_channel_handle_t>());
	}
	// if audio source not closed elsewhere close here and reset our audio source flag
	if ( p_audioSource )
	{
		p_audioSource = GNSDK_NULL;
		audioSource.SourceClose();
	}

	delete [] audioBuffer;

	/* Lets not throw from here unless its a serious issue. */
	if ((MIDSWARN_NotReady!= error) && GNSDKERR_SEVERE(error)) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  AudioProcessStart
 */
void
GnMusicIdStream::AudioProcessStart(
	gnsdk_uint32_t samples_per_second,
	gnsdk_uint32_t bits_per_sample,
	gnsdk_uint32_t number_of_channels
	) throw (GnError)
{
	gnsdk_error_t error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_DSP);

	error = gnsdk_musicidstream_channel_audio_begin(
				get<gnsdk_musicidstream_channel_handle_t>(),
				samples_per_second,
				bits_per_sample,
				number_of_channels);
	if (error) { throw GnError(); }

}


/*-----------------------------------------------------------------------------
 *  AudioProcessStop
 */
void
GnMusicIdStream::AudioProcessStop() throw (GnError)
{
	// p_audioSource acts as a flag indicating an IGnAudioSource is in use and must
	// be closed immediately when audio is stopped.
	// So if we have an audio source close it and reset the flag.
	if ( p_audioSource )
	{
		p_audioSource->SourceClose();
		p_audioSource = GNSDK_NULL;
	}
	
	gnsdk_error_t error = gnsdk_musicidstream_channel_audio_end(get<gnsdk_musicidstream_channel_handle_t>());
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  AudioProcess
 */
void
GnMusicIdStream::AudioProcess(
	const gnsdk_byte_t*  	pAudioData,
	gnsdk_size_t 			audioDataLength
	) throw (GnError)
{
	gnsdk_error_t error = GNSDK_SUCCESS;
	error = gnsdk_musicidstream_channel_audio_write(get<gnsdk_musicidstream_channel_handle_t>(), pAudioData, audioDataLength);
			
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  IdentifyAlbum
 */
void
GnMusicIdStream::IdentifyAlbum() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidstream_channel_identify(get<gnsdk_musicidstream_channel_handle_t>());
	if (error) { throw GnError(); }
	
	error = gnsdk_musicidstream_channel_wait_for_identify(get<gnsdk_musicidstream_channel_handle_t>(), GNSDK_MUSICIDSTREAM_TIMEOUT_INFINITE);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  IdentifyAlbumAsync
 */
void
GnMusicIdStream::IdentifyAlbumAsync() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidstream_channel_identify(get<gnsdk_musicidstream_channel_handle_t>());
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  WaitForIdentify
 */
bool
GnMusicIdStream::WaitForIdentify(gnsdk_uint32_t timeout_ms) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_musicidstream_channel_wait_for_identify(get<gnsdk_musicidstream_channel_handle_t>(), timeout_ms);
	if (error)
	{ 
		if (GNSDKERR_ERROR_CODE(error) == GNSDKERR_Timeout)
			return false;
		else
			throw GnError();
	}

	return true;
}

void 
GnMusicIdStream::IdentifyCancel() throw (GnError)
{
	gnsdk_error_t error = gnsdk_musicidstream_channel_identify_cancel(get<gnsdk_musicidstream_channel_handle_t>());
	if (error) { throw GnError();}
}


// Note: hiding for GFM release July 2014 - remove condition after GFM release made
#ifndef PRODUCT_GNSDK_MOBILE
/*-----------------------------------------------------------------------------
 *  AutomaticIdentification
 */
void
GnMusicIdStream::AutomaticIdentifcation(bool bEnable) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_musicidstream_channel_automatic_set(get<gnsdk_musicidstream_channel_handle_t>(), bEnable);
			
	if (error) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  AutomaticIdentification
 */
bool
GnMusicIdStream::AutomaticIdentifcation() throw (GnError)
{
	gnsdk_bool_t	returnValue = GNSDK_NULL;
	gnsdk_error_t	error;
	
	error = gnsdk_musicidstream_channel_automatic_get(get<gnsdk_musicidstream_channel_handle_t>(), &returnValue);
	if (error) { throw GnError(); }
	
	if (returnValue)
		return true;
	return false;

}
#endif /* PRODUCT_GNSDK_MOBILE */

/*-----------------------------------------------------------------------------
 *  Event
 */
void
GnMusicIdStream::Event(GnMusicIdStreamEvent event) throw (GnError)
{
	gnsdk_error_t	error;
	
	error = gnsdk_musicidstream_channel_event(get<gnsdk_musicidstream_channel_handle_t>(), (gnsdk_musicidstream_event_t)event);
	if (error) { throw GnError(); }

}


void
GnMusicIdStream::BroadcastMetadata(gnsdk_cstr_t broadcastMetadataKey, gnsdk_cstr_t broadcastMetadataValue) throw (GnError)
{
	gnsdk_error_t	error;
	
	error = gnsdk_musicidstream_channel_broadcast_metadata_write(get<gnsdk_musicidstream_channel_handle_t>(), broadcastMetadataKey, broadcastMetadataValue);
	if (error) { throw GnError(); }
	
}

/*-----------------------------------------------------------------------------
 *  _callback_status
 */
void GNSDK_CALLBACK_API
callback_status(void* callback_data, gnsdk_status_t mid_status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t* p_abort)
{
	GnMusicIdStream* p_musicid_stream = (GnMusicIdStream*)callback_data;

	if (p_musicid_stream->EventHandler())
	{
		gn_canceller	canceller;

		p_musicid_stream->EventHandler()->StatusEvent((GnStatus)mid_status, percent_complete, bytes_total_sent, bytes_total_received, canceller);
		if (canceller.IsCancelled())
		{
			*p_abort = GNSDK_TRUE;
		}
	}
}



/*-----------------------------------------------------------------------------
 *  _callback_mids_processing_status
 */
gnsdk_void_t GNSDK_CALLBACK_API
callback_mids_processing_status(
	gnsdk_void_t*                				callback_data,
	gnsdk_musicidstream_processing_status_t 	status,
	gnsdk_bool_t*                				p_abort
	)
{
	GnMusicIdStream* 					p_musicid_stream = (GnMusicIdStream*)callback_data;
	GnMusicIdStreamProcessingStatus		cppStatus = kStatusProcessingInvalid;

	if (p_musicid_stream->EventHandler())
	{
		gn_canceller	canceller;

		switch ( status )
		{
		case gnsdk_musicidstream_processing_status_invalid:							cppStatus = kStatusProcessingInvalid;break;
		case gnsdk_musicidstream_processing_status_audio_none:						cppStatus = kStatusProcessingAudioNone;break;
		case gnsdk_musicidstream_processing_status_audio_silence:					cppStatus = kStatusProcessingAudioSilence;break;
		case gnsdk_musicidstream_processing_status_audio_noise:						cppStatus = kStatusProcessingAudioNoise;break;
		case gnsdk_musicidstream_processing_status_audio_speech:					cppStatus = kStatusProcessingAudioSpeech;break;
		case gnsdk_musicidstream_processing_status_audio_music:						cppStatus = kStatusProcessingAudioMusic;break;
		case gnsdk_musicidstream_processing_status_transition_channel_change:		cppStatus = kStatusProcessingTransitionChannelChange;break;
		case gnsdk_musicidstream_processing_status_transition_content_to_content:	cppStatus = kStatusProcessingTransitionContentToContent;break;
		case gnsdk_musicidstream_processing_status_error_noclassifier:				cppStatus = kStatusProcessingErrorNoClassifier;break;
		case gnsdk_musicidstream_processing_status_audio_started:					cppStatus = kStatusProcessingAudioStarted;break;
		case gnsdk_musicidstream_processing_status_audio_ended:						cppStatus = kStatusProcessingAudioEnded;break;
		}

		p_musicid_stream->EventHandler()->MusicIdStreamProcessingStatusEvent(cppStatus, canceller);
		if (canceller.IsCancelled())
		{
			*p_abort = GNSDK_TRUE;
		}
	}
}

/*-----------------------------------------------------------------------------
 *  callback_mids_identifying_status
 */
gnsdk_void_t GNSDK_CALLBACK_API
callback_mids_identifying_status(
	gnsdk_void_t*                				callback_data,
	gnsdk_musicidstream_identifying_status_t 	status,
	gnsdk_bool_t*                				p_abort
	)
{
	GnMusicIdStream* 					p_musicid_stream = (GnMusicIdStream*)callback_data;
	GnMusicIdStreamIdentifyingStatus	cppStatus = kStatusIdentifyingInvalid;

	if (p_musicid_stream->EventHandler())
	{
		gn_canceller	canceller;

		switch ( status )
		{
		case gnsdk_musicidstream_identifying_status_invalid:			cppStatus = kStatusIdentifyingInvalid;break;
		case gnsdk_musicidstream_identifying_started:					cppStatus = kStatusIdentifyingStarted;break;
		case gnsdk_musicidstream_identifying_fp_generated:				cppStatus = kStatusIdentifyingFpGenerated;break;
		case gnsdk_musicidstream_identifying_local_query_started:		cppStatus = kStatusIdentifyingLocalQueryStarted;break;
		case gnsdk_musicidstream_identifying_local_query_ended:			cppStatus = kStatusIdentifyingLocalQueryEnded;break;
		case gnsdk_musicidstream_identifying_online_query_started:		cppStatus = kStatusIdentifyingOnlineQueryStarted;break;
		case gnsdk_musicidstream_identifying_online_query_ended:		cppStatus = kStatusIdentifyingOnlineQueryEnded;break;
		case gnsdk_musicidstream_identifying_ended:						cppStatus = kStatusIdentifyingEnded;break;
		}

		p_musicid_stream->EventHandler()->MusicIdStreamIdentifyingStatusEvent(cppStatus, canceller);
		

		if (canceller.IsCancelled())
		{
			*p_abort = GNSDK_TRUE;
		}
	}
}


/*-----------------------------------------------------------------------------
 *  _callback_result_available
 */
gnsdk_void_t GNSDK_CALLBACK_API
callback_result_available(
	gnsdk_void_t*                        callback_data,
	gnsdk_musicidstream_channel_handle_t p_musicidstream_channel_handle,
	gnsdk_gdo_handle_t                   response_gdo,
	gnsdk_bool_t*                        p_abort
	)
{
	GnMusicIdStream* p_musicid_stream = (GnMusicIdStream*)callback_data;

	GNSDK_UNUSED(p_musicidstream_channel_handle);

	if (p_musicid_stream->EventHandler())
	{
		gn_canceller		canceller;
		GnResponseAlbums	tmp = GnResponseAlbums(response_gdo);

		p_musicid_stream->EventHandler()->MusicIdStreamAlbumResult(tmp, canceller);

		if (canceller.IsCancelled())
		{
			*p_abort = GNSDK_TRUE;
		}
	}
}

/*-----------------------------------------------------------------------------
 *  _callback_completed_with_error
 */
gnsdk_void_t GNSDK_CALLBACK_API
callback_completed_with_error(
	gnsdk_void_t* 								callback_data,
	gnsdk_musicidstream_channel_handle_t		p_musicidstream_channel_handle,
	const gnsdk_error_info_t* 					p_error_info
	)
{
	GnMusicIdStream* 					p_musicid_stream = (GnMusicIdStream*)callback_data;

	(void)p_musicidstream_channel_handle;

	if (p_musicid_stream->EventHandler())
	{
		GnError errorObj(p_error_info);

		p_musicid_stream->EventHandler()->MusicIdStreamIdentifyCompletedWithError(errorObj);
	}
}


#endif /* GNSDK_MUSICID_STREAM */

