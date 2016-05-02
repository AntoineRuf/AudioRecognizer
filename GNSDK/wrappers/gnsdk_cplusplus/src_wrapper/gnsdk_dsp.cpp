/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk_dsp.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */
#include "gnsdk_manager.hpp"

#if GNSDK_DSP

#include "gnsdk_dsp.hpp"

using namespace gracenote;
using namespace gracenote::dsp;

static gnsdk_cstr_t
_getFeatureType(GnDspFeatureType type)
{
	switch( type )
	{
	case kDspFeatureTypeAFX3:			return "AFX3";
	case kDspFeatureTypeChroma:			return "Chroma";
	case kDspFeatureTypeCantametrixQ:	return "Cantametrix-Q";
	case kDspFeatureTypeCantametrixR:	return "Cantametrix-R";
	case kDspFeatureTypeFEXModule:		return "FEXModule";
	case kDspFeatureTypeFraunhofer:		return "Fraunhofer";
	case kDspFeatureTypeFAPIQ3sVLQ:		return "FAPI-Q-3s-VLQ";
	case kDspFeatureTypeFAPIQ3sLQ:		return "FAPI-Q-3s-LQ";
	case kDspFeatureTypeFAPIQ3sMQ:		return "FAPI-Q-3s-MQ";
	case kDspFeatureTypeFAPIQ3sHQ:		return "FAPI-Q-3s-HQ";
	case kDspFeatureTypeFAPIQ3sVHQ:		return "FAPI-Q-3s-VHQ";
	case kDspFeatureTypeFAPIR:			return "FAPI-R";
	case kDspFeatureTypeNanoFAPIQ:		return "NanoFAPI-Q";
	case kDspFeatureTypeMicroFAPIQ:		return "MicroFAPI-Q";
	case kDspFeatureTypeInvalid:		return GNSDK_NULL;
	}
	return GNSDK_NULL;
}

/******************************************************************************
** GnDsp
*/
GnDsp::GnDsp(const GnUser& user, GnDspFeatureType featureType, gnsdk_uint32_t audioSampleRate, gnsdk_uint32_t audioSampleSize, gnsdk_uint32_t audioChannels) throw (GnError)
{
	gnsdk_dsp_feature_handle_t	featureHandle = GNSDK_NULL;
	gnsdk_error_t				error;

	_gnsdk_internal::module_initialize(GNSDK_MODULE_DSP);

	error = gnsdk_dsp_feature_audio_begin(user.native(), _getFeatureType(featureType), audioSampleRate, audioSampleSize, audioChannels, &featureHandle);
	if (error) { throw GnError(); }

	this->AcceptOwnership(featureHandle);
}


GnDsp::~GnDsp()
{
}


/*-----------------------------------------------------------------------------
 *  Version
 */
gnsdk_cstr_t
GnDsp::Version()
{
	return gnsdk_dsp_get_version();
}


/*-----------------------------------------------------------------------------
 *  BuildDate
 */
gnsdk_cstr_t
GnDsp::BuildDate()
{
	return gnsdk_dsp_get_build_date();
}


/*-----------------------------------------------------------------------------
 *  FeatureAudioWrite
 */
bool
GnDsp::FeatureAudioWrite(const gnsdk_byte_t* audioData, gnsdk_size_t audioDataBytes) throw (GnError)
{
	gnsdk_error_t error;
	gnsdk_bool_t  b_complete;

	error = gnsdk_dsp_feature_audio_write(get<gnsdk_dsp_feature_handle_t>(), audioData, audioDataBytes, &b_complete);
	if (error) { throw GnError(); }

	if (b_complete)
		return true;
	return false;
}


/*-----------------------------------------------------------------------------
 *  FeatureEndOfAudioWrite
 */
void
GnDsp::FeatureEndOfAudioWrite()  throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_dsp_feature_end_of_write(get<gnsdk_dsp_feature_handle_t>());
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  FeatureRetrieve
 */
GnDspFeature
GnDsp::FeatureRetrieve() throw (GnError)
{
	return GnDspFeature(get<gnsdk_dsp_feature_handle_t>());
}


/**************************************************************************
** GnDspFeature
*/
GnDspFeature::GnDspFeature() :
	m_Data(GNSDK_NULL), m_Quality(kDspFeatureQualityUnknown)
{
}


GnDspFeature::GnDspFeature(gnsdk_dsp_feature_handle_t featureHandle) : GnObject(featureHandle)
{
	GnDspFeatureQuality           gnFeatureQuality = kDspFeatureQualityUnknown;
	gnsdk_dsp_feature_qualities_t featureQuality   = GNSDK_DSP_FEATURE_QUALITY_DEFAULT;
	gnsdk_cstr_t                  featureData      = GNSDK_NULL;
	gnsdk_error_t                 error;

	/* To retrieve dsp feature data, here passing pointer of GnDspFeature's member i.e dsp_feature->data. */
	if (featureHandle)
	{
		error = gnsdk_dsp_feature_retrieve_data(featureHandle, &featureQuality, &featureData );
		if (error) { throw GnError(); }

		switch (featureQuality)
		{
		case GNSDK_DSP_FEATURE_QUALITY_DEFAULT:
			gnFeatureQuality = kDspFeatureQualityStandard;
			break;

		case GNSDK_DSP_FEATURE_QUALITY_SHORT:
			gnFeatureQuality = kDspFeatureQualityShort;
			break;

		case GNSDK_DSP_FEATURE_QUALITY_SILENT:
			gnFeatureQuality = kDspFeatureQualitySilent;
			break;
		}
	}

	m_Data    = featureData;
	m_Quality = gnFeatureQuality;
}


/*-----------------------------------------------------------------------------
 *  FeatureData
 */
gnsdk_cstr_t
GnDspFeature::FeatureData() const
{
	return m_Data;
}


/*-----------------------------------------------------------------------------
 *  FeatureQuality
 */
GnDspFeatureQuality
GnDspFeature::FeatureQuality() const
{
	return m_Quality;
}


#endif /* GNSDK_DSP */

