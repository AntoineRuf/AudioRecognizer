/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_CONVERT_HPP_
#define _GNSDK_CONVERT_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"

namespace gracenote
{
	/**
	 * Various methods for converting to and from native values
	 * For internal use.
	 */
	class gnconvert
	{
	public:

		/**
		 * Convert native language to enumerated language
		 * @param c_region 	[in] Native language
		 * @return Enumerated language
		 */
		static GnLanguage
		_convertLanguageCCpp( gnsdk_cstr_t c_language )
		{
			GnLanguage language = kLanguageEnglish;

			if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_ENGLISH ) == 0 )
			{
				language = kLanguageEnglish;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_CHINESE_SIMP ) == 0 )
			{
				language = kLanguageChineseSimplified;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_CHINESE_TRAD ) == 0 )
			{
				language = kLanguageChineseTraditional;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_DUTCH ) == 0 )
			{
				language = kLanguageDutch;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_FRENCH ) == 0 )
			{
				language = kLanguageFrench;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_GERMAN ) == 0 )
			{
				language = kLanguageGerman;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_ITALIAN ) == 0 )
			{
				language = kLanguageItalian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_JAPANESE ) == 0 )
			{
				language = kLanguageJapanese;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_KOREAN ) == 0 )
			{
				language = kLanguageKorean;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_PORTUGUESE ) == 0 )
			{
				language = kLanguagePortuguese;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_RUSSIAN ) == 0 )
			{
				language = kLanguageRussian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_SPANISH ) == 0 )
			{
				language = kLanguageSpanish;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_SWEDISH ) == 0 )
			{
				language = kLanguageSwedish;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_THAI ) == 0 )
			{
				language = kLanguageThai;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_TURKISH ) == 0 )
			{
				language = kLanguageTurkish;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_POLISH ) == 0 )
			{
				language = kLanguagePolish;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_FARSI ) == 0 )
			{
				language = kLanguageFarsi;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_VIETNAMESE ) == 0 )
			{
				language = kLanguageVietnamese;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_HUNGARIAN ) == 0 )
			{
				language = kLanguageHungarian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_CZECH ) == 0 )
			{
				language = kLanguageCzech;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_SLOVAK ) == 0 )
			{
				language = kLanguageSlovak;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_ROMANIAN ) == 0 )
			{
				language = kLanguageRomanian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_GREEK ) == 0 )
			{
				language = kLanguageGreek;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_ARABIC ) == 0 )
			{
				language = kLanguageArabic;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_INDONESIAN ) == 0 )
			{
				language = kLanguageIndonesian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_FINNISH ) == 0 )
			{
				language = kLanguageFinnish;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_NORWEGIAN ) == 0 )
			{
				language = kLanguageNorwegian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_CROATIAN ) == 0 )
			{
				language = kLanguageCroatian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_BULGARIAN ) == 0 )
			{
				language = kLanguageBulgarian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_SERBIAN ) == 0 )
			{
				language = kLanguageSerbian;
			}
			else if ( gnstd::gn_strcmp( c_language, GNSDK_LANG_DANISH ) == 0 )
			{
				language = kLanguageDanish;
			}

			return language;
		}

		/**
		 * Convert enumerated language to native language
		 * @param lanaguage	[in] Enumerated langauge
		 * @return Native language value
		 */
		static gnsdk_cstr_t
		_convertLangCppC( GnLanguage language )
		{
			switch ( language )
			{
			case kLanguageArabic:             return GNSDK_LANG_ARABIC;
			case kLanguageBulgarian:          return GNSDK_LANG_BULGARIAN;
			case kLanguageChineseSimplified:  return GNSDK_LANG_CHINESE_SIMP;
			case kLanguageChineseTraditional: return GNSDK_LANG_CHINESE_TRAD;
			case kLanguageCroatian:           return GNSDK_LANG_CROATIAN;
			case kLanguageCzech:              return GNSDK_LANG_CZECH;
			case kLanguageDanish:             return GNSDK_LANG_DANISH;
			case kLanguageDutch:              return GNSDK_LANG_DUTCH;
			case kLanguageEnglish:            return GNSDK_LANG_ENGLISH;
			case kLanguageFarsi:              return GNSDK_LANG_FARSI;
			case kLanguageFinnish:            return GNSDK_LANG_FINNISH;
			case kLanguageFrench:             return GNSDK_LANG_FRENCH;
			case kLanguageGerman:             return GNSDK_LANG_GERMAN;
			case kLanguageGreek:              return GNSDK_LANG_GREEK;
			case kLanguageHungarian:          return GNSDK_LANG_HUNGARIAN;
			case kLanguageIndonesian:         return GNSDK_LANG_INDONESIAN;
			case kLanguageItalian:            return GNSDK_LANG_ITALIAN;
			case kLanguageJapanese:           return GNSDK_LANG_JAPANESE;
			case kLanguageKorean:             return GNSDK_LANG_KOREAN;
			case kLanguageNorwegian:          return GNSDK_LANG_NORWEGIAN;
			case kLanguagePolish:             return GNSDK_LANG_POLISH;
			case kLanguagePortuguese:         return GNSDK_LANG_PORTUGUESE;
			case kLanguageRomanian:           return GNSDK_LANG_ROMANIAN;
			case kLanguageRussian:            return GNSDK_LANG_RUSSIAN;
			case kLanguageSerbian:    		  return GNSDK_LANG_SERBIAN;
			case kLanguageSlovak:             return GNSDK_LANG_SLOVAK;
			case kLanguageSpanish:            return GNSDK_LANG_SPANISH;
			case kLanguageSwedish:            return GNSDK_LANG_SWEDISH;
			case kLanguageThai:               return GNSDK_LANG_THAI;
			case kLanguageTurkish:            return GNSDK_LANG_TURKISH;
			case kLanguageVietnamese:         return GNSDK_LANG_VIETNAMESE;
			case kLanguageInvalid:
				break;
			}

			return GNSDK_NULL;
		}

		/**
		 * Convert native region to enumerated region
		 * @param c_region 	[in] Native region
		 * @return Enumerated region
		 */
		static GnRegion
		_convertRegionCCpp( gnsdk_cstr_t c_region )
		{
			GnRegion region = kRegionDefault;

			if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_DEFAULT ) == 0 )
			{
				region = kRegionDefault;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_GLOBAL ) == 0 )
			{
				region = kRegionGlobal;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_US ) == 0 )
			{
				region = kRegionUS;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_JAPAN ) == 0 )
			{
				region = kRegionJapan;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_CHINA ) == 0 )
			{
				region = kRegionChina;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_TAIWAN ) == 0 )
			{
				region = kRegionTaiwan;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_KOREA ) == 0 )
			{
				region = kRegionKorea;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_EUROPE ) == 0 )
			{
				region = kRegionEurope;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_NORTH_AMERICA ) == 0 )
			{
				region = kRegionNorthAmerica;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_LATIN_AMERICA ) == 0 )
			{
				region = kRegionLatinAmerica;
			}
			else if ( gnstd::gn_strcmp( c_region, GNSDK_REGION_INDIA ) == 0 )
			{
				region = kRegionIndia;
			}

			return region;
		}

		/**
		 * Convert enumerated region to native region
		 * @param lanaguage	[in] Enumerated region
		 * @return Native region value
		 */
		static gnsdk_cstr_t
		_convertRegionCppC( GnRegion region )
		{
			switch ( region )
			{
			case kRegionDefault:      return GNSDK_REGION_DEFAULT;
			case kRegionGlobal:       return GNSDK_REGION_GLOBAL;
			case kRegionNorthAmerica:
			case kRegionUS:           return GNSDK_REGION_US;
			case kRegionJapan:        return GNSDK_REGION_JAPAN;
			case kRegionChina:        return GNSDK_REGION_CHINA;
			case kRegionTaiwan:       return GNSDK_REGION_TAIWAN;
			case kRegionKorea:        return GNSDK_REGION_KOREA;
			case kRegionEurope:       return GNSDK_REGION_EUROPE;
			case kRegionLatinAmerica: return GNSDK_REGION_LATIN_AMERICA;
			case kRegionIndia: 		  return GNSDK_REGION_INDIA;
			}

			return GNSDK_REGION_DEFAULT;
		}

		/**
		 * Convert native descriptor to enumerated descriptor
		 * @param c_region 	[in] Native descriptor
		 * @return Enumerated descriptor
		 */
		static GnDescriptor
		_convertDescriptorCCpp( gnsdk_cstr_t c_descriptor )
		{
			GnDescriptor desc = kDescriptorDefault;

			if ( gnstd::gn_strcmp( c_descriptor, GNSDK_DESCRIPTOR_DEFAULT ) == 0 )
			{
				desc = kDescriptorDefault;
			}
			else if ( gnstd::gn_strcmp( c_descriptor, GNSDK_DESCRIPTOR_SIMPLIFIED ) == 0 )
			{
				desc = kDescriptorSimplified;
			}
			else if ( gnstd::gn_strcmp( c_descriptor, GNSDK_DESCRIPTOR_DETAILED ) == 0 )
			{
				desc = kDescriptorDetailed;
			}

			return desc;
		}

		/**
		 * Convert enumerated descriptor to native descriptor
		 * @param lanaguage	[in] Enumerated descriptor
		 * @return Native descriptor value
		 */
		static gnsdk_cstr_t
		_convertDescCppC( GnDescriptor descriptor )
		{
			switch ( descriptor )
			{
			case kDescriptorDefault:    return GNSDK_DESCRIPTOR_DEFAULT;
			case kDescriptorSimplified: return GNSDK_DESCRIPTOR_SIMPLIFIED;
			case kDescriptorDetailed:   return GNSDK_DESCRIPTOR_DETAILED;
			}
			return GNSDK_DESCRIPTOR_DEFAULT;
		}

		/**
		 * Convert enumerated content type to native content type
		 * @param lanaguage	[in] Enumerated content type
		 * @return Native content type value
		 */
		static gnsdk_cstr_t
		_convertContentTypeCppC( GnContentType contentType )
		{
			gnsdk_cstr_t key = GNSDK_NULL;

			switch (contentType)
			{
			case kContentTypeImageCover:
				key = GNSDK_GDO_CHILD_CONTENT_IMAGECOVER;
				break;

			case kContentTypeImageArtist:
				key = GNSDK_GDO_CHILD_CONTENT_IMAGEARTIST;
				break;

			case kContentTypeImageVideo:
				key = GNSDK_GDO_CHILD_CONTENT_IMAGEVIDEO;
				break;

			case kContentTypeBiography:
				key = GNSDK_GDO_CHILD_CONTENT_BIOGRAPHY;
				break;

			case kContentTypeReview:
				key = GNSDK_GDO_CHILD_CONTENT_REVIEW;
				break;

			case kContentTypeNews:
				key = GNSDK_CONTENT_TYPE_TEXT_NEWS;
				break;

			case kContentTypeArtistNews:
				key = GNSDK_CONTENT_TYPE_TEXT_ARTISTNEWS;
				break;

			case kContentTypeListenerComments:
				key = GNSDK_CONTENT_TYPE_TEXT_LISTENERCOMMENTS;
				break;

			case kContentTypeReleaseComments:
				key = GNSDK_CONTENT_TYPE_TEXT_RELEASECOMMENTS;
				break;

			default:
				break;
			}

			return key;
		}
	};

}

#endif // _GNSDK_CONVERT_HPP_
