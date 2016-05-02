/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_DSP_HPP_
#define _GNSDK_DSP_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"

namespace gracenote
{
	namespace dsp
	{
#if GNSDK_DSP

		enum GnDspFeatureQuality
		{
			kDspFeatureQualityUnknown = 0,

			kDspFeatureQualityStandard,
			kDspFeatureQualityShort,
			kDspFeatureQualitySilent
		};

		// have to keep GnDspFeatureType enum and the fpTypeString lookup table in sync.
		enum GnDspFeatureType
		{
			kDspFeatureTypeInvalid = 0,

			kDspFeatureTypeAFX3,
			kDspFeatureTypeChroma,
			kDspFeatureTypeCantametrixQ,
			kDspFeatureTypeCantametrixR,
			kDspFeatureTypeFEXModule,
			kDspFeatureTypeFraunhofer,
			kDspFeatureTypeFAPIQ3sVLQ,
			kDspFeatureTypeFAPIQ3sLQ,
			kDspFeatureTypeFAPIQ3sMQ,
			kDspFeatureTypeFAPIQ3sHQ,
			kDspFeatureTypeFAPIQ3sVHQ,
			kDspFeatureTypeFAPIR,
			kDspFeatureTypeNanoFAPIQ,
			kDspFeatureTypeMicroFAPIQ
		};


		/**************************************************************************
		** GnDspFeature
		*/
		class GnDspFeature : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnDspFeature();
			GnDspFeature(gnsdk_dsp_feature_handle_t featureHandle);

			gnsdk_cstr_t			FeatureData() const;
			GnDspFeatureQuality		FeatureQuality() const;

		private:
			gnsdk_cstr_t				m_Data;
			GnDspFeatureQuality			m_Quality;
		};


		/**************************************************************************
		** GnDsp
		*/
		class GnDsp : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Initializes the DSP library.
			 * @param user set user
			 * @param featureType The kind of DSP feature, for example a fingerprint.
			 * @param audioSampleRate The source audio sample rate.
			 * @param audioSampleSize The source audio sample size.
			 * @param audioChannels	The source audio channels
			 */
			GnDsp(const GnUser& user, GnDspFeatureType featureType, gnsdk_uint32_t audioSampleRate, gnsdk_uint32_t audioSampleSize, gnsdk_uint32_t audioChannels)  throw (GnError);
			virtual ~GnDsp();

			/**
			 *  Retrieves GnDsp SDK version string.
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 *  string is a constant. Do not attempt to modify or delete.
			 *  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
			 *  Major: New functionality
			 *  Minor: New or changed features
			 *  Improvement: Improvements and fixes
			 *  Build: Internal build number
			 */
			static gnsdk_cstr_t Version();

			/**
			 *  Retrieves the GnDsp SDK's build date string.
			 *  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 * string is a constant. Do not attempt to modify or delete.
			 *  Example build date string: 2008-02-12 00:41 UTC
			 */
			static gnsdk_cstr_t BuildDate();

			/**
			 * Use this method to feed audio in to GnDsp until it returns true
			 * @param audioData The source audio
			 * @param audioDataBytes The source audio size in bytes
			 * @return false : GnDsp needs more audio, true : GnDsp received enough audio to generate required feature
			 */
			bool FeatureAudioWrite(const gnsdk_byte_t* audioData, gnsdk_size_t audioDataBytes) throw (GnError);

			/**
			 * Indicates the the DSP feature has reached the end of the write operation.
			 */
			void FeatureEndOfAudioWrite() throw (GnError);

			/**
			 * Retrieve GnDspFeature
			 * @return GnDspFeature
			 */
			GnDspFeature               FeatureRetrieve() throw (GnError);

		private:

			/* disallow assignment operator */
			DISALLOW_COPY_AND_ASSIGN(GnDsp);
		};

#endif /* GNSDK_DSP */

	} // namespace Dsp

}     // namespace GracenoteSDK

#endif // _GNSDK_DSP_HPP_
