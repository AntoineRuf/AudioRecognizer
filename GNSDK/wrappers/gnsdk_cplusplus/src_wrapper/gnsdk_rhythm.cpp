/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_rhythmrhythm.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk_manager.hpp"
#include "gnsdk_convert.hpp"

#if GNSDK_RHYTHM

#include "gnsdk_rhythm.hpp"
#include "metadata_music.hpp"


using namespace gracenote;
using namespace gracenote::rhythm;

/*-----------------------------------------------------------------------------
 *  _callback_status
 */
 static void GNSDK_CALLBACK_API
_callback_status(void* callback_data, gnsdk_status_t status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t* p_abort)
{
	GnRhythmQuery* p_rhythm = static_cast<GnRhythmQuery*>(callback_data);

	if (p_rhythm->EventHandler())
	{
		if (!p_rhythm->IsCancelled())
		{
			gn_canceller	canceller;

			p_rhythm->EventHandler()->StatusEvent((GnStatus)status, percent_complete, bytes_total_sent, bytes_total_received, canceller);
			if (canceller.IsCancelled() || p_rhythm->IsCancelled())
			{
				*p_abort = GNSDK_TRUE;
			}
		}
	}
}

 /*-----------------------------------------------------------------------------
 *  _callback_status_station
 */
 static void GNSDK_CALLBACK_API
_callback_status_station(void* callback_data, gnsdk_status_t status, gnsdk_uint32_t percent_complete, gnsdk_size_t bytes_total_sent, gnsdk_size_t bytes_total_received, gnsdk_bool_t* p_abort)
{
	GnRhythmStation* p_rhythm = static_cast<GnRhythmStation*>(callback_data);

	if (p_rhythm->EventHandler())
	{
		if (!p_rhythm->IsCancelled())
		{
			gn_canceller	canceller;

			p_rhythm->EventHandler()->StatusEvent((GnStatus)status, percent_complete, bytes_total_sent, bytes_total_received, canceller);
			if (canceller.IsCancelled() || p_rhythm->IsCancelled())
			{
				*p_abort = GNSDK_TRUE;
			}
		}
	}
}

/* ****************************************************************************	*/
/* GnRhythm - Functions															*/
/* ****************************************************************************	*/
gnsdk_cstr_t
GnRhythm::Version()
{
	return gnsdk_rhythm_get_version();
}

gnsdk_cstr_t
GnRhythm::BuildDate()
{
	return gnsdk_rhythm_get_build_date();
}

/* ****************************************************************************	*/
/* GnRhythmOptions                                                              */
/* ****************************************************************************	*/
void
GnRhythmQueryOptions::LookupData(GnLookupData lookupData, bool bEnable) throw (GnError)
{
	switch (lookupData)
	{
	case kLookupDataContent:
		Custom(GNSDK_RHYTHM_OPTION_ENABLE_CONTENT_DATA, bEnable);
		break;
	case kLookupDataSonicData:
		Custom(GNSDK_RHYTHM_OPTION_ENABLE_SONIC_DATA, bEnable);
		break;
	case kLookupDataExternalIds:
		Custom(GNSDK_RHYTHM_OPTION_ENABLE_EXTERNAL_IDS, bEnable);
		break;

	default:
		throw GnError(RHYTHMERR_InvalidArg, "Unsupported lookupData");
	}
}

void
GnRhythmQueryOptions::ReturnCount(gnsdk_uint32_t count) throw (GnError)
{
	Custom(GNSDK_RHYTHM_OPTION_ENABLE_SONIC_DATA, count);
}

void
GnRhythmQueryOptions::FocusPopularity(gnsdk_uint32_t amount) throw (GnError)
{
	Custom(GNSDK_RHYTHM_OPTION_FOCUS_POPULARITY, amount);
}

void
GnRhythmQueryOptions::FocusSimilarity(gnsdk_uint32_t amount) throw (GnError)
{
	Custom(GNSDK_RHYTHM_OPTION_FOCUS_SIMILARITY, amount);
}

void
GnRhythmQueryOptions::RecommendationMaxTracksPerArtist(gnsdk_uint32_t count) throw (GnError)
{
	Custom(GNSDK_RHYTHM_OPTION_RECOMMENDATION_MAX_TRACKS_PER_ARTIST, count);
}

void
GnRhythmQueryOptions::RecommendationRotationRadio(bool bEnable) throw (GnError)
{
	Custom(GNSDK_RHYTHM_OPTION_RECOMMENDATION_ROTATION_RADIO, bEnable);
}

void
GnRhythmQueryOptions::StationDMCA(bool bEnable) throw (GnError)
{
	Custom(GNSDK_RHYTHM_OPTION_STATION_DMCA, bEnable);
}

/*-----------------------------------------------------------------------------
 *  NetworkInterface
 */
void
GnRhythmQueryOptions::NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError)
{
	Custom(GNSDK_QUERY_OPTION_NETWORK_INTERFACE, ipAddress);
}

void
GnRhythmQueryOptions::Custom(gnsdk_cstr_t option, bool bEnable) throw (GnError)
{
	Custom(option, bEnable ? GNSDK_VALUE_TRUE : GNSDK_VALUE_FALSE);
}

void
GnRhythmQueryOptions::Custom(gnsdk_cstr_t option, gnsdk_uint32_t value) throw (GnError)
{
	char buffer[16];
	gnstd::gn_itoa(buffer, sizeof(buffer), value);
	Custom(option, buffer);
}

void
GnRhythmQueryOptions::Custom(gnsdk_cstr_t option, gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;
	error = gnsdk_rhythm_query_option_set(weakhandle_, option, value);
	if (error) { throw GnError(); }
}

/* ****************************************************************************	*/
/* GnRhythmQuery                                                                */
/* ****************************************************************************	*/
GnRhythmQuery::GnRhythmQuery(GnUser const& user, IGnStatusEvents* pEventHandler) throw (GnError):
	cancelled_(false), eventhandler_(pEventHandler)
{
	gnsdk_error_t error;
	gnsdk_rhythm_query_handle_t query_handle = GNSDK_NULL;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_RHYTHM);

	error = gnsdk_rhythm_query_create(user.native(), _callback_status, this, &query_handle);
	if (error) { throw GnError(); }

	AcceptOwnership(query_handle);
	options_.weakhandle_ = query_handle;
}

void
GnRhythmQuery::AddSeed(metadata::GnDataObject const& seed) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_rhythm_query_set_gdo(get<gnsdk_rhythm_query_handle_t>(), seed.native());
	if (error) { throw GnError(); }
}

metadata::GnResponseAlbums
GnRhythmQuery::GenerateRecommendations() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;

	cancelled_ = false;
	error = gnsdk_rhythm_query_generate_recommendations(get<gnsdk_rhythm_query_handle_t>(), &response_gdo);
	if (error) { throw GnError(); }

	metadata::GnResponseAlbums tmp = metadata::GnResponseAlbums(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}
gnsdk_rhythm_station_handle_t
GnRhythmQuery::GenerateStation(GnRhythmStation* p_rhythmStation)
{
	gnsdk_error_t error;
	gnsdk_rhythm_station_handle_t station_handle = GNSDK_NULL;

	cancelled_ = false;
	error = gnsdk_rhythm_query_generate_station(get<gnsdk_rhythm_query_handle_t>(), _callback_status_station, p_rhythmStation, &station_handle);
	if (error) { throw GnError(); }

	return station_handle;
}


/* ****************************************************************************	*/
/* GnRhythmStationOptions                                                       */
/* ****************************************************************************	*/

void
GnRhythmStationOptions::Custom(gnsdk_cstr_t option, gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;
	error = gnsdk_rhythm_station_option_set(weakhandle_, option, value);
	if (error) { throw GnError(); }
}

/* ****************************************************************************	*/
/* GnRhythmStation          													*/
/* ****************************************************************************	*/
GnRhythmStation::GnRhythmStation(GnRhythmQuery& rhythm, IGnStatusEvents* pEventHandler) throw (GnError):
	cancelled_(false), eventhandler_(pEventHandler)
{
	gnsdk_rhythm_station_handle_t station_handle = rhythm.GenerateStation(this);

	AcceptOwnership(station_handle);
	options_.weakhandle_ = station_handle;
}

GnRhythmStation::GnRhythmStation(gnsdk_cstr_t serializedStation, GnUser const& user, IGnStatusEvents* pEventHandler) throw (GnError):
	cancelled_(false), eventhandler_(pEventHandler)
{
	gnsdk_error_t error;
	gnsdk_rhythm_station_handle_t station_handle = GNSDK_NULL;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_RHYTHM);

	error = gnsdk_rhythm_station_lookup(serializedStation, user.native(), _callback_status_station, this, &station_handle);
	if (error) { throw GnError(); }

	AcceptOwnership(station_handle);
	options_.weakhandle_ = station_handle;
}

gnsdk_cstr_t
GnRhythmStation::StationId() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_cstr_t station_id = GNSDK_NULL;

	error = gnsdk_rhythm_station_id(get<gnsdk_rhythm_station_handle_t>(), &station_id);
	if (error) { throw GnError(); }

	return station_id;
}

metadata::GnResponseAlbums
GnRhythmStation::GeneratePlaylist() throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_gdo_handle_t response_gdo = GNSDK_NULL;

	cancelled_ = false;
	error = gnsdk_rhythm_station_generate_playlist(get<gnsdk_rhythm_station_handle_t>(), &response_gdo);
	if (error) { throw GnError(); }

	metadata::GnResponseAlbums tmp = metadata::GnResponseAlbums(response_gdo);

	error = gnsdk_manager_gdo_release(response_gdo);
	if (error) { throw GnError(); }

	return tmp;
}

void
GnRhythmStation::Event(GnRhythmEvent event, metadata::GnDataObject const& gnObj) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_rhythm_station_event(get<gnsdk_rhythm_station_handle_t>(), static_cast<gnsdk_rhythm_event_t>(event), gnObj.native());
	if (error) { throw GnError(); }
}

#endif /* GNSDK_RHYTHM */

