/**
 * Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

 /**
 * @file metadata_video.hpp
 */
 
#ifndef _GNSDK_METADATA_VIDEO_HPP_
#define _GNSDK_METADATA_VIDEO_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "metadata.hpp"

 /**
 * \namespace gracenote
 */
namespace gracenote
{
	 /**
	 * \namespace metadata
	 */
	namespace metadata
	{
		/* Forward Class Declaration */
		class GnVideoProduct;

		class GnVideoWork;
		class GnVideoSeason;
		class GnVideoSeries;
		class GnVideoDisc;
		class GnVideoSide;
		class GnVideoLayer;
		class GnVideoFeature;
		class GnVideoChapter;
		class GnVideoCredit;
		typedef gn_facade_range_iterator<GnVideoProduct, gn_gdo_provider<GnVideoProduct> >   product_iterator;
		typedef gn_facade_range_iterator<GnVideoWork, gn_gdo_provider<GnVideoWork> >         works_iterator;
		typedef gn_facade_range_iterator<GnVideoSeason, gn_gdo_provider<GnVideoSeason> >     season_iterator;
		typedef gn_facade_range_iterator<GnVideoSeries, gn_gdo_provider<GnVideoSeries> >     series_iterator;
		typedef gn_facade_range_iterator<GnVideoDisc, gn_gdo_provider<GnVideoDisc> >         disc_iterator;
		typedef gn_facade_range_iterator<GnVideoSide, gn_gdo_provider<GnVideoSide> >         side_iterator;
		typedef gn_facade_range_iterator<GnVideoLayer, gn_gdo_provider<GnVideoLayer> >       layer_iterator;
		typedef gn_facade_range_iterator<GnVideoFeature, gn_gdo_provider<GnVideoFeature> >   feature_iterator;
		typedef gn_facade_range_iterator<GnVideoChapter, gn_gdo_provider<GnVideoChapter> >   chapter_iterator;
		typedef gn_facade_range_iterator<GnVideoCredit, gn_gdo_provider<GnVideoCredit> >     video_credit_iterator;
		typedef gn_facade_range_iterator<GnContributor, gn_gdo_provider<GnContributor> >     contributor_iterator;


		typedef gn_iterable_container<GnVideoProduct, gn_gdo_provider<GnVideoProduct> >   product_iterable;
		typedef gn_iterable_container<GnVideoWork, gn_gdo_provider<GnVideoWork> >         works_iterable;
		typedef gn_iterable_container<GnVideoSeason, gn_gdo_provider<GnVideoSeason> >     season_iterable;
		typedef gn_iterable_container<GnVideoSeries, gn_gdo_provider<GnVideoSeries> >     series_iterable;
		typedef gn_iterable_container<GnVideoDisc, gn_gdo_provider<GnVideoDisc> >         disc_iterable;
		typedef gn_iterable_container<GnVideoSide, gn_gdo_provider<GnVideoSide> >         side_iterable;
		typedef gn_iterable_container<GnVideoLayer, gn_gdo_provider<GnVideoLayer> >       layer_iterable;
		typedef gn_iterable_container<GnVideoFeature, gn_gdo_provider<GnVideoFeature> >   feature_iterable;
		typedef gn_iterable_container<GnVideoChapter, gn_gdo_provider<GnVideoChapter> >   chapter_iterable;
		typedef gn_iterable_container<GnVideoCredit, gn_gdo_provider<GnVideoCredit> >     video_credit_iterable;
		typedef gn_iterable_container<GnContributor, gn_gdo_provider<GnContributor> >     contributor_iterable;



		/**
		* \class GnRating
		*/
		class GnRating : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnRating() { }
			GnRating(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnRating() { }

			/**
			 *  Rating value, e.g., PG
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Rating() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING);
			}

			/**
			 *  Rating type value, e.g., MPAA .
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingType() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_TYPE);
			}

			/**
			 *  Rating description .
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingDesc() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_DESC);
			}

			/**
			 *  Rating type Id.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			RatingTypeId() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RATING_TYPE_ID);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Rating reason
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingReason() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_REASON);
			}

			/**
			 *  AMPAA (Motion Picture Assoc. of America) rating.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingMPAA() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_MPAA);
			}

			/**
			 *  A MPAA (Motion Picture Assoc. of America) TV rating type.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingMPAATV() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_MPAA_TV);
			}

			/**
			 *  A FAB (Film Advisory Board) rating.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingFAB() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_FAB);
			}

			/**
			 *  A CHVRS (Canadian Home Video Rating System) rating
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingCHVRS() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_CHVRS);
			}

			/**
			 *  A Canadian TV rating type value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingCanadianTV() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_CANADIAN_TV);
			}

			/**
			 *  A BBFC (British Board of Film Classification) rating type value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingBBFC() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_BBFC);
			}

			/**
			 *  A CBFC (Central Board of Film Certification) rating type value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingCBFC() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_CBFC);
			}

			/**
			 *  A OFLC (Australia) TV rating type value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingOFLC() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_OFLC);
			}

			/**
			 *  A Hong Kong rating type value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingHongKong() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_HONG_KONG);
			}

			/**
			 * A Finnish rating type value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingFinnish() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_FINNISH);
			}

			/**
			 *  A KMRB (Korea Media Rating Board) rating type value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingKMRB() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_KMRB);
			}

			/**
			 * A DVD Parental rating
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingDVDParental() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_DVD_PARENTAL);
			}

			/**
			 * A EIRIN (Japan) rating
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingEIRIN() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_EIRIN);
			}

			/**
			 *  A INCAA (Argentina) rating
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingINCAA() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_INCAA);
			}

			/**
			 *  A DJTCQ (Dept of Justice, Rating, Titles and Qualification) (Brazil) rating
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingDJTCQ() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_DJTCQ);
			}

			/**
			 *  A Quebecois rating.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingQuebec() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_QUEBEC);
			}

			/**
			 *  A French rating.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingFrance() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_FRANCE);
			}

			/**
			 *  A FSK (German) rating.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingFSK() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_FSK);
			}

			/**
			 *  An Italian rating
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingItaly() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_ITALY);
			}

			/**
			 *  A Spanish rating
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RatingSpain() const
			{
				return StringValue(GNSDK_GDO_VALUE_RATING_SPAIN);
			}

		}; // GnRating


	   /**
		* \class GnVideoCredit
		*/
		class GnVideoCredit : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnVideoCredit() { }
			GnVideoCredit(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnVideoCredit()  { }

			/**
			 *  Role, e.g., Actor.
			 * <p><b>Note:</b></p>
			 *  For music credits, the absence of a role for a person indicates that person is the primary
			 *   artist, who may have performed multiple roles.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Role
			 */
			gnsdk_cstr_t
			Role() const
			{
				return StringValue(GNSDK_GDO_VALUE_ROLE);
			}

			/**
			 * Role ID
			 * @ingroup GDO_ValueKeys_Role
			 */
			gnsdk_uint32_t
			RoleId() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ROLE_ID);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  A number identifying the role's listing in the credits.
			 * @ingroup GDO_ValueKeys_Role
			 */
			gnsdk_cstr_t
			RoleBilling() const
			{
				return StringValue(GNSDK_GDO_VALUE_ROLE_BILLING);
			}

			/**
			 *  The character's name on the show.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			CharacterName() const
			{
				return StringValue(GNSDK_GDO_VALUE_CHARACTER_NAME);
			}

			/**
			 *  Role's rank in importance.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			Rank() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RANK);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Genre, e.g., comedy. This is a list/locale dependent, multi-level field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *
			 * @param level :enum value specifying level value
			 * @return gnsdk_cstr_t
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Genre(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Artist type. This is a list/locale dependent, multi-level field
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *
			 * @param level        :enum value specifying level value
			 * @return gnsdk_cstr_t
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			ArtistType(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_ARTISTTYPE_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_ARTISTTYPE_LEVEL2;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *
			 * @param level		[in] enum value specifying level value
			 * @return gnsdk_cstr_t

			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Origin(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL3;
					break;

				case kDataLevel_4:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL4;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 * Artist era. This is a list/locale dependent, multi-level field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *
			 * @param level		[in] enum value specifying level value
			 * @return gnsdk_cstr_t

			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Era(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_ERA_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_ERA_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_ERA_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Official name object .
			 * @ingroup GDO_ChildKeys_Name
			 */
			GnName
			OfficialName() const
			{
				return ChildGet<GnName>(GNSDK_GDO_CHILD_NAME_OFFICIAL);
			}

			/**
			 * Contributor object.
			 * @ingroup GDO_ChildKeys_Contributor
			 */
			GnContributor
			Contributor() const
			{
				return ChildGet<GnContributor>(GNSDK_GDO_CHILD_CONTRIBUTOR);
			}

			/**
			 * Iterable object that allows access to the collection of video work children.
			 * @ingroup GDO_ChildKeys_Video_Work
			 */
			works_iterable Works() const
			{
				return works_iterable(gn_gdo_provider<GnVideoWork>(*this, GNSDK_GDO_CHILD_VIDEO_WORK), GN_GDO_START);
			}

			series_iterable Series() const;

			season_iterable Seasons() const;

		};  // GnVideoCredit


	   /**
		* \class GnVideoChapter
		*/

		class GnVideoChapter : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoChapter, GNSDK_GDO_TYPE_VIDEO_CHAPTER);

			GnVideoChapter() { }
			GnVideoChapter(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnVideoChapter()  { }

			/**
			 * Video chapter's ordinal value.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			Ordinal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ORDINAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Chapter's duration value in seconds such as "3600" for a 60-minute program.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			Duration() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_DURATION);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Chapter's duration units value (seconds, "SEC").
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DurationUnits() const
			{
				return StringValue(GNSDK_GDO_VALUE_DURATION_UNITS);
			}

			/**
			 *  Official Title object.
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *   Iterator for child credits. For music,this includes all credits except the artist credit.
			 * @ingroup GDO_ChildKeys_Credit
			 */
			video_credit_iterable VideoCredits() const
			{
				return video_credit_iterable(gn_gdo_provider<GnVideoCredit>(*this, GNSDK_GDO_CHILD_CREDIT), GN_GDO_START);
			}

		};  // GnVideoChapter


	   /**
		* \class GnVideoSeason
		*/
		class GnVideoSeason : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoSeason,GNSDK_GDO_TYPE_VIDEO_SEASON);

			GnVideoSeason() { }
			GnVideoSeason(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }
			GnVideoSeason(gnsdk_cstr_t id, gnsdk_cstr_t idTag) throw (GnError) : GnDataObject(id, idTag, GNSDK_ID_SOURCE_VIDEO_SEASON) { }

			virtual
			~GnVideoSeason() { }

			/**
			 *  Flag indicating if response result contains full (true) or partial metadata.
			 * <p><b>Note:</b></p>
			 *   What constitutes a full result varies among response results, and also
			 *  depends on data availability.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			bool
			IsFullResult() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FULL_RESULT);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Video season's Gracenote identifier.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 *   Video season's Gracenote unique identifier.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 *  Video season's product ID (aka Tag ID).
			 *  <p><b>Remarks:</b></p>
			 *  Available for most types, this value can be stored or transmitted. Can
			 *  be used as a static identifier for the current content as it will not change over time.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			ProductId() const
			{
				return StringValue(GNSDK_GDO_VALUE_PRODUCTID);
			}

			/**
			 *  Video season's TUI (title-unique identifier).
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 *  Video season's Tui Tag.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 *  Video production type, e.g., Animation. This is a list/locale dependent value.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list or locale be loaded into memory through a successful
			 *  allocation of a GnLocale object
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a GnLocale object.
			 *  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for
			 *  a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoProductionType() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE);
			}

			/**
			 *  Video production type identifier.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			VideoProductionTypeId() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE_ID);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Video season's original release date.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DateOriginalRelease() const
			{
				return StringValue(GNSDK_GDO_VALUE_DATE_ORIGINAL_RELEASE);
			}

			/**
			 *  Duration in seconds such as "3600" for a 60-minute program.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			Duration() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_DURATION);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Duration units value (seconds, "SEC").
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DurationUnits() const
			{
				return StringValue(GNSDK_GDO_VALUE_DURATION_UNITS);
			}

			/**
			 *  Franchise number.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			FranchiseNum() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FRANCHISE_NUM);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Franchise count.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			FranchiseCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FRANCHISE_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Plot sypnosis, e.g., for Friends episode:."Monica's popularity at a karaoke club might have more to do with her revealing dress than her voice"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsis() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS);
			}

			/**
			 *  Plot sypnosis language, e.g., English
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsisLanguage() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS_LANGUAGE);
			}

			/**
			 *  Plot tagline, e.g., "An adventure as big as life itself."
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotTagline() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_TAGLINE);
			}

			/**
			 *  Serial type, e.g., Series or Episode
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SerialType() const
			{
				return StringValue(GNSDK_GDO_VALUE_SERIAL_TYPE);
			}

			/**
			 *  Work type, e.g., Musical
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			WorkType() const
			{
				return StringValue(GNSDK_GDO_VALUE_WORK_TYPE);
			}

			/**
			 *  Target audience, e.g., "Kids and Family"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Audience() const
			{
				return StringValue(GNSDK_GDO_VALUE_AUDIENCE);
			}

			/**
			 *  Video mood, e.g., Playful.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoMood() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_MOOD);
			}

			/**
			 *  Overall story type, e.g., "Love Story".
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			StoryType() const
			{
				return StringValue(GNSDK_GDO_VALUE_STORY_TYPE);
			}

			/**
			 *  Reputation, e.g., "Chick flick".
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Reputation() const
			{
				return StringValue(GNSDK_GDO_VALUE_REPUTATION);
			}

			/**
			 *  Scenario, e.g., Action
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Scenario() const
			{
				return StringValue(GNSDK_GDO_VALUE_SCENARIO);
			}

			/**
			 *  Setting environment, e.g., "High School"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SettingEnvironment() const
			{
				return StringValue(GNSDK_GDO_VALUE_SETTING_ENVIRONMENT);
			}

			/**
			 *  Setting time period, e.g., "Jazz Age 1919-1929".
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SettingTimePeriod() const
			{
				return StringValue(GNSDK_GDO_VALUE_SETTING_TIME_PERIOD);
			}

			/**
			 *  Topic value, e.g., "Teen Angst"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Topic() const
			{
				return StringValue(GNSDK_GDO_VALUE_TOPIC);
			}

			/**
			 *  Season number.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeasonNumber() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_NUMBER);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Season count - total number of seasons.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeasonCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Source, e.g., "Fairy Tales and Nursery Rhymes"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Source() const
			{
				return StringValue(GNSDK_GDO_VALUE_SOURCE);
			}

			/**
			 *  Style, e.g., "Film Noir"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Style() const
			{
				return StringValue(GNSDK_GDO_VALUE_STYLE);
			}

			/**
			 *  Genre. This is a list/locale dependent, multi-level field.
			 *
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list or locale be loaded into memory through a successful
			 *  allocation of a <code>GnLocale</code> object
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a GnLocale object.
			 *  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for
			 *  a list-based value.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Genre(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Origin, e.g., "New York City." List/locale dependent, multi-level field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list or locale be loaded into memory through a successful
			 *  allocation of a <code>GnLocale</code> object
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a GnLocale object.
			 *  The SDK returns a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for
			 *  a list-based value.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Origin(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL3;
					break;

				case kDataLevel_4:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL4;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Rating object.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			GnRating
			Rating() const
			{
				return Reflect<GnRating>();
			}

			/**
			 *   Official title object
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *  Franchise title object.
			 * @ingroup GDO_ChildKeys_Video
			 */
			GnTitle
			FranchiseTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_FRANCHISE);
			}

			/**
			 *  Iterator for extended IDs, which identify a source external to Gracenote (e.g., NetFlix), that also have an identifier for this work.
			 *  Extended ID type supports Link data.
			 * @ingroup GDO_ChildKeys_ExternalId
			 */
			externalid_iterable ExternalIds() const
			{
				return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}

			/**
			 *   Iterator for child works.
			 * @ingroup GDO_ChildKeys_Works
			 */
			works_iterable Works() const 
			{
				return works_iterable(gn_gdo_provider<GnVideoWork>(*this, GNSDK_GDO_CHILD_VIDEO_WORK), GN_GDO_START);
			}

			/**
			 *   Iterator for child products
			 * @ingroup GDO_ChildKeys_Products
			 */
			product_iterable Products() const 
			{
				return product_iterable(gn_gdo_provider<GnVideoProduct>(*this, GNSDK_GDO_CHILD_VIDEO_PRODUCT), GN_GDO_START);
			}

			/**
			 *   Iterable for child credits. For music types, this includes
			 *   all credits except the artist credit.
			 * @ingroup GDO_ChildKeys_Credit
			 */
			video_credit_iterable VideoCredits() const
			{
				return video_credit_iterable(gn_gdo_provider<GnVideoCredit>(*this, GNSDK_GDO_CHILD_CREDIT), GN_GDO_START);
			}

			
			/**
			 * Iterator for the content (cover art, biography, etc.)  associated with this video work.
			 * @return Iterator
			 */
			content_iterable Contents() const
			{
				return content_iterable(gn_gdo_provider<GnContent>(*this, GNSDK_GDO_CHILD_CONTENT),GN_GDO_START);
			}

			/**
			 *   Iterator for child series'
			 * @ingroup GDO_ChildKeys_Series
			 */
			series_iterable Series() const;

		};  // GnVideoSeason


	   /**
		* \class GnVideoSeries
		*/
		class GnVideoSeries : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnVideoSeries() { }
			GnVideoSeries(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }
			GnVideoSeries(gnsdk_cstr_t id, gnsdk_cstr_t idTag) throw (GnError) : GnDataObject(id, idTag, GNSDK_ID_SOURCE_VIDEO_SERIES) { }

			virtual
			~GnVideoSeries()  { }

			/**
			 *  Flag indicating if response result contains full (true) or partial metadata.
			 * <p><b>Note:</b></p>
			 *  What constitutes a full result varies among responses and results and also
			 *  depends on data availability.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			bool
			IsFullResult() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FULL_RESULT);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *   Gracenote ID.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 *   Gracenote unique ID.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 *  Product ID, aka Tag ID
			 *  <p><b>Remarks:</b></p>
			 *  This value can be stored or transmitted - it is a static identifier for the current content and will not change over time.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			ProductId() const
			{
				return StringValue(GNSDK_GDO_VALUE_PRODUCTID);
			}

			/**
			 *  TUI (title unique identifier)
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 *  TUI tag
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 *  Production type, e.g., Animation. This is a list/locale dependent field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. The SDK returns
			 *  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
			 *  information.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoProductionType() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE);
			}

			/**
			 *  Production type identifier
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			VideoProductionTypeId() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE_ID);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Original release date. Available for video Products, Features, and
			 *  Works.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DateOriginalRelease() const
			{
				return StringValue(GNSDK_GDO_VALUE_DATE_ORIGINAL_RELEASE);
			}

			/**
			 *  Duration value such as "3600" (seconds) for a 60-minute
			 *  program. Available for video Chapters, Features, Products, Seasons, Series, and Works.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			Duration() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_DURATION);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Duration units type (seconds, "SEC"). Available for video
			 *  Chapters, Features, Products, Seasons, Series, and Works.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DurationUnits() const
			{
				return StringValue(GNSDK_GDO_VALUE_DURATION_UNITS);
			}

			/**
			 *  Franchise number.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			FranchiseNum() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FRANCHISE_NUM);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Franchise count.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			FranchiseCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FRANCHISE_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Plot synopsis, e.g., "A semi-autobiographical coming-of-age story"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsis() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS);
			}

			/**
			 *  Plot tagline, e.g., "If you forgot what terror was like...its back"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotTagline() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_TAGLINE);
			}

			/**
			 *  Plot synopsis language, e.g., English
			 *  <p><b>Remarks:</b></p>
			 *  The language depends on availability: information in the language set
			 *  for the locale may not be available, and the object's information may be available only in its
			 *  default official language. For example, if a locale's set language is Spanish, but the object's
			 *  information is available only in English, this value returns as English.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsisLanguage() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS_LANGUAGE);
			}

			/**
			 *  Video serial type, e.g., Episode.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> objec. The SDK returns
			 *  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for a list-based value
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SerialType() const
			{
				return StringValue(GNSDK_GDO_VALUE_SERIAL_TYPE);
			}

			/**
			 *  Work type, e.g., Musical
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list be loaded into memory through a successful
			 *  call to gnsdk_manager_locale_load.
			 *
			 *  To render locale-dependent information for list-based values, the application must call
			 *  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
			 *  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
			 *  information.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			WorkType() const
			{
				return StringValue(GNSDK_GDO_VALUE_WORK_TYPE);
			}

			/**
			 *  Audience, e.g., "Young Adult"
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Audience() const
			{
				return StringValue(GNSDK_GDO_VALUE_AUDIENCE);
			}

			/**
			 *  Video mood, e.g., Somber
			 *  <p><b>Remarks:</b></p>
			 *  Mood information for music and video, depending on the respective calling type.
			 * @ingroup GDO_ValueKeys_Music
			 */
			gnsdk_cstr_t
			VideoMood() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_MOOD);
			}

			/**
			 *  Story type, e.g., "Love Story"
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			StoryType() const
			{
				return StringValue(GNSDK_GDO_VALUE_STORY_TYPE);
			}

			/**
			 *  Reputation, e.g., Cult
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Reputation() const
			{
				return StringValue(GNSDK_GDO_VALUE_REPUTATION);
			}

			/**
			 *  Scenario, e.g., Drama
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list be loaded into memory through a successful
			 *  call to gnsdk_manager_locale_load.
			 *
			 *  To render locale-dependent information for list-based values, the application must call
			 *  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
			 *  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
			 *  information.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Scenario() const
			{
				return StringValue(GNSDK_GDO_VALUE_SCENARIO);
			}

			/**
			 *  Setting environment, e.g., Skyscraper.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SettingEnvironment() const
			{
				return StringValue(GNSDK_GDO_VALUE_SETTING_ENVIRONMENT);
			}

			/**
			 *  Historical time period such as "Elizabethan Era, 1558-1603"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SettingTimePeriod() const
			{
				return StringValue(GNSDK_GDO_VALUE_SETTING_TIME_PERIOD);
			}

			/**
			 *  Source, e.g., "Phillip K. Dick short story".
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Source() const
			{
				return StringValue(GNSDK_GDO_VALUE_SOURCE);
			}

			/**
			 *  Style, such as "Film Noir"
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Style() const
			{
				return StringValue(GNSDK_GDO_VALUE_STYLE);
			}

			/**
			 *  Topic, such as Racing
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Topic() const
			{
				return StringValue(GNSDK_GDO_VALUE_TOPIC);
			}

			/**
			 *  Genre, e.g., Comedy. This ia a list/locale dependent, multi-level object.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Genre(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Origin(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL3;
					break;

				case kDataLevel_4:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL4;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Rating object
			 * @ingroup GDO_ValueKeys_Misc
			 */
			GnRating
			Rating() const
			{
				return Reflect<GnRating>();
			}

			/**
			 * Official title object
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *   Franchise title object.
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			FranchiseTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_FRANCHISE);
			}

			/**
			 *  Iterator for external IDs, supports Link data.
			 *  <p><b>Remarks:</b></p>
			 *  External IDs identify a source external to Gracenote (e.g., NetFlix), that also have an identifier for this work.
			 *  The ordinal parameter indicates the n'th child external ID to retrieve.
			 *
			 * @ingroup GDO_ChildKeys_ExternalId
			 */
			externalid_iterable ExternalIds() const
			{
					return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}

			/**
			 * Iterator for child works.
			 * @ingroup GDO_ChildKeys_Works
			 */
			works_iterable Works()
			{
				return works_iterable(gn_gdo_provider<GnVideoWork>(*this, GNSDK_GDO_CHILD_VIDEO_WORK), GN_GDO_START);
			}

			
			/**
			 * Iterator for child video products
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child
			 * @ingroup GDO_ChildKeys_Video
			 */
			product_iterable Products() const
			{
				return product_iterable(gn_gdo_provider<GnVideoProduct>(*this, GNSDK_GDO_CHILD_VIDEO_PRODUCT), GN_GDO_START);
			}

			/**
			 *  Iterator for child seasons
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter indicates the n'th child video season to retrieve.
			 *  Video product types are generally available from video season Gracenote data objects.
			 * @ingroup GDO_ChildKeys_Video
			 */
			season_iterable Seasons() const
			{
				return season_iterable(gn_gdo_provider<GnVideoSeason>(*this, GNSDK_GDO_CHILD_VIDEO_SEASON), GN_GDO_START);
			}

			/**
			 *   Iterable for child video credits.
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter indicates the n'th child video credit to retrieve.
			 * @ingroup GDO_ChildKeys_Credit
			 */
			video_credit_iterable VideoCredits() const
			{
				return video_credit_iterable(gn_gdo_provider<GnVideoCredit>(*this,GNSDK_GDO_CHILD_CREDIT),GN_GDO_START);
			}

			
			/**
			 * Iterator for the content (cover art, biography, etc.)  associated with this video work.
			 * @return Iterator
			 */
			content_iterable Contents() const
			{
				return content_iterable(gn_gdo_provider<GnContent>(*this, GNSDK_GDO_CHILD_CONTENT),GN_GDO_START);
			}

		};


	   /**
		* \class GnVideoWork
		*/
		class GnVideoWork : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoWork, GNSDK_GDO_TYPE_VIDEO_WORK);

			GnVideoWork() { }
			GnVideoWork(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }
			GnVideoWork(gnsdk_cstr_t id, gnsdk_cstr_t idTag) throw (GnError) : GnDataObject(id, idTag, GNSDK_ID_SOURCE_VIDEO_WORK) { }

			virtual
			~GnVideoWork() { }

			/**
			 *  Flag indicating if result contains full (true) or partial metadata.
			 * <p><b>Note:</b></p>
			 *  What constitutes a full result varies among response types and results and also
			 *  depends on data availability.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			bool
			IsFullResult() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FULL_RESULT);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *   Gracenote ID.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 *   Gracenote unique identifier
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 *  Product ID aka Tag ID
			 *  <p><b>Remarks:</b></p>
			 *  This value which can be stored or transmitted - it can be used as a static identifier for the current
			 *  content and will not change over time.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			ProductId() const
			{
				return StringValue(GNSDK_GDO_VALUE_PRODUCTID);
			}

			/**
			 *  TUI (title-unique identifier)
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 *  TUI tag
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 *  Second TUI, if it exists. This TUI is used
			 *   for matching partial Products objects to full Works objects.
			 *  Use this value to ensure correct Tui value matching for cases when a video Product GDO contains
			 *  multiple partial Work GDOs. Each partial Work GDO corresponds
			 *  to a full Works object, and each full Works object contains the GNSDK_GDO_VALUE_TUI value,
			 *  incremented by one digit to maintain data integrity with Gracenote Service.
			 *  The GNSDK_GDO_VALUE_TUI_MATCH_PRODUCT maps the partial Works object Tui value to the full Works
			 *   object.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			TuiMatchProduct() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_MATCH_PRODUCT);
			}

			/**
			 *  Video production type ID
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			VideoProductionTypeId() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE_ID);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Video production type, e.g., Animation. This is a list/locale dependent value.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoProductionType() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE);
			}

			/**
			 *  Video's original release date.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DateOriginalRelease() const
			{
				return StringValue(GNSDK_GDO_VALUE_DATE_ORIGINAL_RELEASE);
			}

			/**
			 *  Duration value in seconds such as "3600" (seconds) for a 60-minute program.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			Duration() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_DURATION);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Duration units value (seconds, "SEC").
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DurationUnits() const
			{
				return StringValue(GNSDK_GDO_VALUE_DURATION_UNITS);
			}

			/**
			 *  Franchise number
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			FranchiseNum() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FRANCHISE_NUM);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Franchise count
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			FranchiseCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FRANCHISE_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Series episode value
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeriesEpisode() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_EPISODE);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Series episode count
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeriesEpisodeCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_EPISODE_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Season episode value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeasonEpisode() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_EPISODE);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Season episode count
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeasonEpisodeCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_EPISODE_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Season count value
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeasonCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Season number value
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			SeasonNumber() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_SEASON_NUMBER);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Plot synopsis e.g., "A semi-autobiographical coming-of-age story"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsis() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS);
			}

			/**
			 *  Plot tagline, e.g., "The Third Dimension is Terror"
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotTagline() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_TAGLINE);
			}

			/**
			 *  Plot synopis language, e.g., English
			 *  <p><b>Remarks:</b></p>
			 *  The language of a returned object depends on availability. Information in the language set
			 *   for the locale may not be available, and the object's information may be available only in its
			 *   default official language. For example, if a locale's set language is Spanish, but the object's
			 *   information is available only in English, this value returns as English.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsisLanguage() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS_LANGUAGE);
			}

			/**
			 *  Supported video serial type such as Series or Episode
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SerialType() const
			{
				return StringValue(GNSDK_GDO_VALUE_SERIAL_TYPE);
			}

			/**
			 *  Work type, e.g., Musical
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list be loaded into memory through a successful
			 *  call to gnsdk_manager_locale_load.
			 *
			 *  To render locale-dependent information for list-based values, the application must call
			 *   <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
			 *   a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
			 *   information.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			WorkType() const
			{
				return StringValue(GNSDK_GDO_VALUE_WORK_TYPE);
			}

			/**
			 *  Audience type, e.g.,"Kids and Family", "African-American", or "Young Adult".
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Audience() const
			{
				return StringValue(GNSDK_GDO_VALUE_AUDIENCE);
			}

			/**
			 *  Mood, e.g., Playful
			 * @ingroup GDO_ValueKeys_Music
			 */
			gnsdk_cstr_t
			VideoMood() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_MOOD);
			}

			/**
			 *  Story type, e.g., "Love Story".
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			StoryType() const
			{
				return StringValue(GNSDK_GDO_VALUE_STORY_TYPE);
			}

			/**
			 *   Scenario, e.g., "Action", "Comedy", and "Drama".
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Scenario() const
			{
				return StringValue(GNSDK_GDO_VALUE_SCENARIO);
			}

			/**
			 *  Physical environment - this is not specific location, but rather a general (or generic)
			 *  location. For example: Prison, High School, Skyscraper, Desert, etc.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SettingEnvironment() const
			{
				return StringValue(GNSDK_GDO_VALUE_SETTING_ENVIRONMENT);
			}

			/**
			 * Historical time setting, e.g., "Elizabethan Era 1558-1603", or "Jazz Age 1919-1929".
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SettingTimePeriod() const
			{
				return StringValue(GNSDK_GDO_VALUE_SETTING_TIME_PERIOD);
			}

			/**
			 *  Story concept source, e.g., "Fairy Tales and Nursery Rhymes".
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Source() const
			{
				return StringValue(GNSDK_GDO_VALUE_SOURCE);
			}

			/**
			 *  Film style, e.g.,  "Film Noir".
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Style() const
			{
				return StringValue(GNSDK_GDO_VALUE_STYLE);
			}

			/**
			 *  Film topic, e.g., "Racing" or "Teen Angst".
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Topic() const
			{
				return StringValue(GNSDK_GDO_VALUE_TOPIC);
			}

			/**
			 *  Film's reputation, e.g., "Classic", "Chick Flick", or "Cult". This is a critical or
			 *  popular "value" that is assigned to a work, usually long after the work was released, though some works may qualify
			 *  shortly after release (e.g., "instant classic" or "blockbuster release").
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list be loaded into memory through a successful
			 *  call to gnsdk_manager_locale_load.
			 *
			 *  To render locale-dependent information for list-based values, the application must call
			 *  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
			 *  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
			 *  information.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Reputation() const
			{
				return StringValue(GNSDK_GDO_VALUE_REPUTATION);
			}

			/**
			 *  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that the list be loaded into memory through a successful
			 *  call to gnsdk_manager_locale_load.
			 *
			 *  To render locale-dependent information for list-based values, the application must call
			 *  <code>gnsdk_manager_locale_load</code> and possibly also <code>gnsdk_sdkmanager_gdo_set_locale</code>. The application returns
			 *  a <code>LocaleNotLoaded</code> message when locale information is not set prior to a request for list-based value
			 *  information.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Origin(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL3;
					break;

				case kDataLevel_4:
					key = GNSDK_GDO_VALUE_ORIGIN_LEVEL4;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 * Genre - e.g., comedy. This is a list/locale dependent, multi-level field.
			 *
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *
			 *  This is a multi-level field requiring a <code>GnDataLevel</code> parameter
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Genre(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Rating object
			 * @ingroup GDO_ValueKeys_Misc
			 */
			GnRating
			Rating() const
			{
				return Reflect<GnRating>();
			}

			/**
			 * Official title object
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *  Franchise title object
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			FranchiseTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_FRANCHISE);
			}

			/**
			 *  Series title object.
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			SeriesTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_SERIES);
			}

			/**
			 *   Iterator for child products
			 * @ingroup GDO_ChildKeys_Products
			 */
			product_iterable Products()
			{
				return product_iterable(gn_gdo_provider<GnVideoProduct>(*this, GNSDK_GDO_CHILD_VIDEO_PRODUCT), GN_GDO_START);
			}

			/**
			 *  Iterator for child credits. For music types, this includes
			 *   all credits except the artist credit.
			 * @ingroup GDO_ChildKeys_Credit
			 */
			video_credit_iterable VideoCredits() const
			{
				return video_credit_iterable(gn_gdo_provider<GnVideoCredit>(*this, GNSDK_GDO_CHILD_CREDIT), GN_GDO_START);
			}

			/**
			 *  Iterator for child seasons.
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child video Season to retrieve.
			 *  Video product types are generally available from GNSDK_GDO_TYPE_RESPONSE_VIDEO_SEASON GDOs.
			 * @ingroup GDO_ChildKeys_Video
			 */
			season_iterable Seasons() const
			{
				return season_iterable(gn_gdo_provider<GnVideoSeason>(*this, GNSDK_GDO_CHILD_VIDEO_SEASON), GN_GDO_START);
			}

			/**
			 * Iterator for child series'
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the the n'th child   video Series to retrieve.
			 *  Video Series types are generally available from GNSDK_GDO_TYPE_RESPONSE_VIDEO_SERIES GDOs.
			 * @ingroup GDO_ChildKeys_Video
			 */
			series_iterable Series() const
			{
				return series_iterable(gn_gdo_provider<GnVideoSeries>(*this, GNSDK_GDO_CHILD_VIDEO_SERIES), GN_GDO_START);
			}

			/**
			 *  Iterator for external IDs.  External IDs are 3rd party IDs used to cross link this metadata to 3rd party services, e.g. Amazon
			 * @ingroup GDO_ChildKeys_ExternalId
			 */

			externalid_iterable ExternalIds() const
			{
				return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}


			/**
			 * Iterator for the content (cover art, biography, etc.)  associated with this video work.
			 * @return Iterator
			 */
			content_iterable Contents() const
			{
				return content_iterable(gn_gdo_provider<GnContent>(*this, GNSDK_GDO_CHILD_CONTENT),GN_GDO_START);
			}

		}; // GnVideoWork


	   /**
		* \class GnVideoFeature 
		* Class containing metadata for a video feature, which has a full-length running time usually between 60 and 120 minutes.
		* A feature is the main component of a DVD or Blu-ray disc which may, in addition, contain extra, or bonus, video clips and features.
		*
		*/
		class GnVideoFeature : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoFeature, GNSDK_GDO_TYPE_VIDEO_FEATURE);

			GnVideoFeature() { }
			GnVideoFeature(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnVideoFeature()  { }

			/**
			 *  Feature's ordinal value
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			Ordinal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ORDINAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Matched boolean value indicating whether this type
			 *  is the one that matched the input criteria. Available from many video types.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			bool
			Matched() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCHED);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Video feature type value.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoFeatureType() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_FEATURE_TYPE);
			}

			/**
			 *  Video production type value.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoProductionType() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE);
			}

			/**
			 *  Video production ID type value
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			VideoProductionTypeId() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE_ID);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Release date in UTC format
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DateRelease() const
			{
				return StringValue(GNSDK_GDO_VALUE_DATE_RELEASE);
			}

			/**
			 *  Original release date in UTC format.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DateOriginalRelease() const
			{
				return StringValue(GNSDK_GDO_VALUE_DATE_ORIGINAL_RELEASE);
			}

			/**
			 *  Notes
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Notes() const
			{
				return StringValue(GNSDK_GDO_VALUE_NOTES);
			}

			/**
			 * Aspect ratio - describes the proportional relationship between the video's width and its height
			 * expressed as two numbers separated by a colon
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			AspectRatio() const
			{
				return StringValue(GNSDK_GDO_VALUE_ASPECT_RATIO);
			}

			/**
			 *  Aspect ratio type, e.g., Standard
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			AspectRatioType() const
			{
				return StringValue(GNSDK_GDO_VALUE_ASPECT_RATIO_TYPE);
			}

			/**
			 *  Duration value in seconds.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			Duration() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_DURATION);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Duration units value (e.g., seconds, "SEC")
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DurationUnits() const
			{
				return StringValue(GNSDK_GDO_VALUE_DURATION_UNITS);
			}

			/**
			 *  Plot summary
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSummary() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SUMMARY);
			}

			/**
			 *  Plot synopsis, e.g., (for Friends episode) "Monica's popularity at a karaoke club might have more to do with her revealing dress than her voice;
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsis() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS);
			}

			/**
			 *  Plot tagline, e.g., "The terrifying motion picture from the terrifying No. 1 best seller."
			 *  GNSDK_GDO_VALUE_PLOT_TAGLINE
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotTagline() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_TAGLINE);
			}

			/**
			 *  Plot synopsis language, e.g., English
			 *  <p><b>Remarks:</b></p>
			 *  The language depends on availability - information in the language set
			 *   for the locale may not be available, and the object's information may be available only in its
			 *   default official language. For example, if a locale's set language is Spanish, but the object's
			 *   information is available only in English, this value returns as English.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			PlotSynopsisLanguage() const
			{
				return StringValue(GNSDK_GDO_VALUE_PLOT_SYNOPSIS_LANGUAGE);
			}

			/**
			 * Genre. e.g., Drama. This is a list/locale dependent,multi-level field
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *
			 *  This is a multi-level field requiring a <code>GnDataLevel</code> parameter
			 *
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Genre(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 *  Official title object
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *  Rating object
			 * @ingroup GDO_ValueKeys_Misc
			 */
			GnRating
			Rating() const
			{
				return Reflect<GnRating>();
			}

			/**
			 *  Iterator for child video works
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child  video Work to retrieve.
			 * @ingroup GDO_ChildKeys_Video
			 */
			works_iterable Works() 
			{
				return works_iterable(gn_gdo_provider<GnVideoWork>(*this, GNSDK_GDO_CHILD_VIDEO_WORK), GN_GDO_START);
			}

			/**
			 *  Iterator for child video chapters
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child  video chapter to retrieve.
			 * @ingroup GDO_ChildKeys_Video
			 */
			chapter_iterable Chapters() const
			{
				return chapter_iterable(gn_gdo_provider<GnVideoChapter>(*this, GNSDK_GDO_CHILD_VIDEO_CHAPTER), GN_GDO_START);
			}

			/**
			 *   Iterable for child credits. For music types, this includes
			 *   all credits except the artist credit.
			 * @ingroup GDO_ChildKeys_Credit
			 */
			video_credit_iterable VideoCredits() const
			{
				return video_credit_iterable(gn_gdo_provider<GnVideoCredit>(*this, GNSDK_GDO_CHILD_CREDIT), GN_GDO_START);
			}

		};


	   /**
		* \class GnVideoLayer
		* Both DVDs and Blu-ray Discs can be dual layer. These discs are only writable on one side of the disc,
		* but contain two layers on that single side for writing data to. Dual-Layer recordable DVDs come in two formats: DVD-R DL and DVD+R DL.
		* They can hold up to 8.5GB on the two layers. Dual-layer Blu-ray discs can store 50 GB of data (25GB on each layer)
		*/
		class GnVideoLayer : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoLayer, GNSDK_GDO_TYPE_VIDEO_LAYER);

			GnVideoLayer() { }
			GnVideoLayer(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnVideoLayer() { }

			/**
			 *  Ordinal value
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			Ordinal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ORDINAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Matched boolean value indicating whether this object
			 *   is the one that matched the input criteria.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			bool
			Matched() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCHED);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Aspect ratio - describes the proportional relationship between the video's width and its height
			 * expressed as two numbers separated by a colon
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			AspectRatio() const
			{
				return StringValue(GNSDK_GDO_VALUE_ASPECT_RATIO);
			}

			/**
			 *  Aspect ratio type, e.g. Standard
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			AspectRatioType() const
			{
				return StringValue(GNSDK_GDO_VALUE_ASPECT_RATIO_TYPE);
			}

			/**
			 *  TV system value, e.g., NTSC.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			TvSystem() const
			{
				return StringValue(GNSDK_GDO_VALUE_TV_SYSTEM);
			}

			/**
			 *  Region code, e.g., FE - France
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			RegionCode() const
			{
				return StringValue(GNSDK_GDO_VALUE_REGION_CODE);
			}

			/**
			 *  Video product region value from the current type, e.g., 1. This is a list/locale dependent value.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoRegion() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_REGION);
			}

			/**
			 *  Video product region, e.g.,  USA, Canada, US Territories, Bermuda, and Cayman Islands.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, the application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoRegionDesc() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_REGION_DESC);
			}

			/**
			 *  Video media type such as Audio-CD, Blu-ray, DVD, or HD DVD.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			MediaType() const
			{
				return StringValue(GNSDK_GDO_VALUE_MEDIA_TYPE);
			}

			/**
			 *  Iterator for child video features.
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child  video feature to retrieve.
			 * @ingroup GDO_ChildKeys_Video
			 */
			feature_iterable Features() const
			{
				return feature_iterable(gn_gdo_provider<GnVideoFeature>(*this, GNSDK_GDO_CHILD_VIDEO_FEATURE),GN_GDO_START);
			}

		};  // GnVideoLayer


	   /**
		* \class GnVideoSide 
		* Both DVDs and Blu-ray discs can be dual side. Double-Sided discs include a single layer on each side of the disc
		* that data can be recorded to. Double-Sided recordable DVDs come in two formats: DVD-R and DVD+R, including the rewritable DVD-RW and
		* DVD+RW. These discs can hold about 8.75GB of data if you burn to both sides. Dual-side Blu-ray discs can store 50 GB of
		* data (25GB on each side).
		*/
		class GnVideoSide : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnVideoSide() { }
			GnVideoSide(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnVideoSide() { }

			/**
			 *  Ordinal value
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			Ordinal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ORDINAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Matched boolean value indicating whether this type
			 *  is the one that matched the input criteria.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			bool
			Matched() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCHED);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Notes
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Notes() const
			{
				return StringValue(GNSDK_GDO_VALUE_NOTES);
			}

			/**
			 *  Official title object
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *  Iterator for video layers
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child video layer to retrieve.

			 * @ingroup GDO_ChildKeys_Video
			 */
			layer_iterable Layers() const
			{
				return layer_iterable(gn_gdo_provider<GnVideoLayer> (*this, GNSDK_GDO_CHILD_VIDEO_LAYER), GN_GDO_START);
			}

		};  // GnVideoSide


	   /**
		* \class GnVideoDisc
		* A video disc can be either DVD (Digital Video Disc) or Blu-ray.
		*/
		class GnVideoDisc : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoDisc, GNSDK_GDO_TYPE_VIDEO_DISC);

			GnVideoDisc() { }
			GnVideoDisc(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }
			GnVideoDisc(gnsdk_cstr_t id, gnsdk_cstr_t idTag) throw (GnError) : GnDataObject(id, idTag, GNSDK_ID_SOURCE_VIDEO_DISC) { }

			virtual
			~GnVideoDisc()  { }

			/**
			 * Gracenote ID
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 * Gracenote unique ID
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 *  Product ID aka Tag ID
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			ProductId() const
			{
				return StringValue(GNSDK_GDO_VALUE_PRODUCTID);
			}

			/**
			 *  TUI - title-unique identifier
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 * Tui Tag value
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 *  Ordinal value
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			Ordinal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ORDINAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Matched boolean value indicating whether this type
			 *   is the one that matched the input criteria.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			bool
			Matched() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCHED);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Notes
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Notes() const
			{
				return StringValue(GNSDK_GDO_VALUE_NOTES);
			}

			/**
			 *  Official title object
			 * @ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *  Iterator for child video sides
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child video side to retrieve.
			 * @ingroup GDO_ChildKeys_Video
			 */
			side_iterable Sides() const
			{
				return side_iterable(gn_gdo_provider<GnVideoSide> (*this, GNSDK_GDO_CHILD_VIDEO_SIDE),GN_GDO_START);
			}

		};  // GnVideoDisc


	   /**
		* \class GnVideoProduct
		* A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a
		* unique commercial code such as a UPC (Univeral Product Code), Hinban, or EAN (European Article Number).
		* Products are for the most part released on a physical format, such as a DVD or Blu-ray.
		*/
		class GnVideoProduct : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnVideoProduct, GNSDK_GDO_TYPE_VIDEO_PRODUCT);

			GnVideoProduct() { }
			GnVideoProduct(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }
			GnVideoProduct(gnsdk_cstr_t id, gnsdk_cstr_t idTag) throw (GnError) : GnDataObject(id, idTag, GNSDK_ID_SOURCE_VIDEO_PRODUCT) { }

			virtual
			~GnVideoProduct()  { }

			/**
			 *  Flag indicating if response result contains full (true) or partial metadata
			 *	<p><b>Remarks:</b></p>
			 *	Available for the following music and video types:
			 *  <ul>
			 *  <li>Album
			 *  <li>Contributor
			 *  <li>Track
			 *  <li>Product
			 *  <li>Season
			 *  <li>Series
			 *  <li>Work
			 *  </ul>
			 *	<p><b>Note:</b></p>
			 *   What constitutes a full result varies among the individual response types and results, and also
			 *	depends on data availability.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			bool
			IsFullResult() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_FULL_RESULT);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *	Gracenote ID
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 *	Gracenote unique ID
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 *	Product ID aka Tag ID
			 *	<p><b>Remarks:</b></p>
			 *	Available for most types, this value which can be stored or transmitted - it can bw used as a static identifier for the current content
			 *  and will not change over time.
			 *	@ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			ProductId() const
			{
				return StringValue(GNSDK_GDO_VALUE_PRODUCTID);
			}

			/**
			 *	Tui (title-unique identifier)
			 *	@ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 *	Tui Tag value
			 *	@ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 *	Package display language, e.g., "English"
			 *  <p><b>Remarks:</b></p>
			 *	The language depends on availability - information in the language set
			 *	for the locale may not be available, and the object's information may be available only in its
			 *	default official language. For example, if a locale's set language is Spanish, but the object's
			 *	information is available only in English, this value returns as English.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			PackageLanguageDisplay() const
			{
				return StringValue(GNSDK_GDO_VALUE_PACKAGE_LANGUAGE_DISPLAY);
			}

			/**
			 *	Package language ISO code, e.g., "eng".
			 *	<p><b>Remarks:</b></p>
			 *	GNSDK supports a subset of the ISO 639-2 Language Code List.
			 *	Specify a locale language's lower-case three-letter code, which is shown in the macro's C/C++
			 *	syntax section.
			 *	<p><b>Note:</b></p>
			 *   The following languages use Gracenote-specific three-letter codes:
			 *  <ul>
			 *  <li>qtb (Simplified Chinese)*
			 *  <li>qtd (Traditional Chinese)*
			 *  </ul>
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			PackageLanguage() const
			{
				return StringValue(GNSDK_GDO_VALUE_PACKAGE_LANGUAGE);
			}

			/**
			 *	Video production type value, e.g., Documentary
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoProductionType() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE);
			}

			/**
			 *	Video production type identifier value
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			VideoProductionTypeId() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_VIDEO_PRODUCTION_TYPE_ID);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Original release date in UTC format.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DateOriginalRelease() const
			{
				return StringValue(GNSDK_GDO_VALUE_DATE_ORIGINAL_RELEASE);
			}

			/**
			 *	Release date in UTC format
			 *	<p><b>Remarks:</b></p>
			 *	Release date values are not always available.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DateRelease() const
			{
				return StringValue(GNSDK_GDO_VALUE_DATE_RELEASE);
			}

			/**
			 *	Duration value in seconds, such as "3600" for a 60-minute program.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_uint32_t
			Duration() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_DURATION);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Duration units value (seconds, "SEC").
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			DurationUnits() const
			{
				return StringValue(GNSDK_GDO_VALUE_DURATION_UNITS);
			}

			/**
			 *	Aspect ratio- describes the proportional relationship between the video's width and its height
			 * expressed as two numbers separated by a colon
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			AspectRatio() const
			{
				return StringValue(GNSDK_GDO_VALUE_ASPECT_RATIO);
			}

			/**
			 *	Aspect ratio type, e.g., Standard
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			AspectRatioType() const
			{
				return StringValue(GNSDK_GDO_VALUE_ASPECT_RATIO_TYPE);
			}

			/**
			 *	Video product region value, e.g, 1
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoRegion() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_REGION);
			}

			/**
			 *	Video product region description, e.g., USA, Canada, US Territories, Bermuda, and Cayman Islands
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			VideoRegionDesc() const
			{
				return StringValue(GNSDK_GDO_VALUE_VIDEO_REGION_DESC);
			}

			/**
			 *	Notes
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			Notes() const
			{
				return StringValue(GNSDK_GDO_VALUE_NOTES);
			}

			/**
			 *	Commerce type value
			 *	<p><b>Remarks:</b></p>
			 *	For information on the specific values this key retrieves, contact your Gracenote Support
			 *	Services representative.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			CommerceType() const
			{
				return StringValue(GNSDK_GDO_VALUE_COMMERCE_TYPE);
			}

			/**
			 *  Genre, e.g., Comedy. This is a list/locale dependent, multi-level field.
			 *  <p><b>Remarks:</b></p>
			 *  This is a list-based value requiring that a list or locale be loaded into memory.
			 *
			 *  To render locale-dependent information for list-based values, your application must allocate a
			 *  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
			 *  is not set prior to a request for a list-based value.
			 *
			 *  This is a multi-level field requiring a <code>GnDataLevel</code> parameter
			 *
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_cstr_t
			Genre(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_GENRE_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 * Rating object.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			GnRating
			Rating() const
			{
				return Reflect<GnRating>();
			}

			/**
			 *	Official child title object
			 *	@ingroup GDO_ChildKeys_Title
			 */
			GnTitle
			OfficialTitle() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 *  Iterator for external IDs.  External IDs are 3rd party IDs used to cross link this metadata to 3rd party services, e.g. Amazon
			 *  The ordinal parameter specifies the n'th child external ID to retrieve.
			 * @ingroup GDO_ChildKeys_ExternalId
			 */
			externalid_iterable ExternalIds() const
			{
					return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}

			/**
			 *	Iterator for child video discs.
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child video disc to retrieve.
			 * @ingroup GDO_ChildKeys_Video
			 */
			disc_iterable Discs() const
			{
				return disc_iterable(gn_gdo_provider<GnVideoDisc>(*this, GNSDK_GDO_CHILD_VIDEO_DISC), GN_GDO_START);
			}

			
			/**
			 * Iterator for the content (cover art, biography, etc.)  associated with this video work.
			 * @return Iterator
			 */
			content_iterable Contents() const
			{
				return content_iterable(gn_gdo_provider<GnContent>(*this, GNSDK_GDO_CHILD_CONTENT),GN_GDO_START);
			}

		};  // GnVideoProduct

   

	   /**
		*  \class GnResponseVideoSuggestions
		*
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseVideoSuggestions : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseVideoSuggestions, GNSDK_GDO_TYPE_RESPONSE_SUGGESTIONS);

			GnResponseVideoSuggestions() { }
			GnResponseVideoSuggestions(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseVideoSuggestions() { }

			/**
			 *  Result count - total number of matches
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the first result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the last result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Estimated total number of results possible.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *	Search suggestion text
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SuggestionText() const
			{
				return StringValue(GNSDK_GDO_VALUE_SUGGESTION_TEXT);
			}

			/**
			 *	Title for the search suggestion type for the current ordinal value.
			 * @ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SuggestionTitle(gnsdk_uint32_t ordinal) const
			{
				return StringValue(GNSDK_GDO_VALUE_SUGGESTION_TITLE, ordinal);
			}

			/**
			 *	Current search suggestion type; this value is only available for a
			 *	video product title search.
			 *	@ingroup GDO_ValueKeys_Video
			 */
			gnsdk_cstr_t
			SuggestionType() const
			{
				return StringValue(GNSDK_GDO_VALUE_SUGGESTION_TYPE);
			}

		}; // GnResponseVideoSuggestions


	   /**
		* \class GnResponseVideoObjects
		*
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseVideoObjects : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseVideoObjects, GNSDK_GDO_TYPE_RESPONSE_VIDEO_OBJECT);

			GnResponseVideoObjects() { }
			GnResponseVideoObjects(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseVideoObjects() { }

			/**
			 *  ResultCount - total number of returned matches
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the first result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the last result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Estimated total number of results possible.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Iterator for child products
			 */
			product_iterable Products() const
			{
				return product_iterable(gn_gdo_provider<GnVideoProduct>(*this, GNSDK_GDO_CHILD_VIDEO_PRODUCT),GN_GDO_START);
			}
			/**
			 *  Iterator for child Works
			 */
			works_iterable Works() 
			{
				return works_iterable(gn_gdo_provider<GnVideoWork>(*this, GNSDK_GDO_CHILD_VIDEO_WORK), GN_GDO_START);
			}

			/**
			 *  Iterator for child Seasons
			 */
			season_iterable Seasons() const
			{
				return season_iterable(gn_gdo_provider<GnVideoSeason>(*this, GNSDK_GDO_CHILD_VIDEO_SEASON), GN_GDO_START);
			}

			/**
			 *  Iterator for child Series
			 */
			series_iterable Series() const
			{
				return series_iterable(gn_gdo_provider<GnVideoSeries> (*this, GNSDK_GDO_CHILD_VIDEO_SERIES), GN_GDO_START);
			}

			/**
			 *  Iterator for child contributors
			 */

			contributor_iterable Contributors() const
			{
				return contributor_iterable(gn_gdo_provider<GnContributor> (*this, GNSDK_GDO_CHILD_CONTRIBUTOR), GN_GDO_START);
			}

		};


	  /**
		*  \class GnResponseContributors
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseContributors : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnResponseContributors() { }
			GnResponseContributors(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseContributors() { }

			/**
			 *  Total number of results
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the first result in the returned range.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the last result in the returned range.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Estimated total number of results possible.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *	Iterator for child contributors.
			 *	@ingroup GDO_ChildKeys_Contributor
			 */
			contributor_iterable Contributors() const
			{
				return contributor_iterable(gn_gdo_provider<GnContributor> (*this, GNSDK_GDO_CHILD_CONTRIBUTOR), GN_GDO_START);
			}

		};


	   /**
		*  \class GnResponseVideoSeries
		*
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseVideoSeries : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseVideoSeries, GNSDK_GDO_TYPE_RESPONSE_VIDEO_SERIES);

			GnResponseVideoSeries() { }
			GnResponseVideoSeries(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseVideoSeries() { }

			/**
			 *  Total number of returned matches
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the first result in the returned range.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the last result in the returned range.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Estimated total number of results possible.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *	Iterator for child series'.
			 *	<p><b>Remarks:</b></p>
			 *	The ordinal parameter specifies the n'th child video Series to retrieve.
			 *	@ingroup GDO_ChildKeys_Video
			 */
			series_iterable Series() const
			{
				return series_iterable(gn_gdo_provider<GnVideoSeries> (*this, GNSDK_GDO_CHILD_VIDEO_SERIES), GN_GDO_START);
			}

		};


	   /**
		* \class GnResponseVideoSeasons
		*
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseVideoSeasons : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseVideoSeasons, GNSDK_GDO_TYPE_RESPONSE_VIDEO_SEASON);

			GnResponseVideoSeasons() { }
			GnResponseVideoSeasons(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseVideoSeasons()  { }

			/**
			 *  Total number of returned matches
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the first result in the returned range.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Ordinal of the last result in the returned range.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *	Estimated total number of results possible.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *	Iterator for child Seasons.
			 *	<p><b>Remarks:</b></p>
			 *	The ordinal parameter specifies the n'th child video Season to retrieve.
			 *	@ingroup GDO_ChildKeys_Video
			 */
			season_iterable Seasons() const
			{
				return season_iterable(gn_gdo_provider<GnVideoSeason>(*this, GNSDK_GDO_CHILD_VIDEO_SEASON), GN_GDO_START);
			}

		};  // GnResponseVideoSeasons


	   /**
		*  \class GnResponseVideoWork
		*
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseVideoWork : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseVideoWork, GNSDK_GDO_TYPE_RESPONSE_VIDEO_WORK);

			GnResponseVideoWork() { }
			GnResponseVideoWork(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseVideoWork() { }

			/**
			 *  Total number of returned results
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Ordinal of the first result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Ordinal of the last result in the returned range.
			 *	@ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Estimated total number of results possible.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Iterator for child video works
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child video Work to retrieve.
			 * @ingroup GDO_ChildKeys_Video
			 */
			works_iterable Works() 
			{
				return works_iterable(gn_gdo_provider<GnVideoWork>(*this, GNSDK_GDO_CHILD_VIDEO_WORK), GN_GDO_START);
			}

		};  // GnResponseVideoWork


	   /**
		* \class GnResponseVideoProduct
		*
		*  <p><b>Remarks about range values:</b></p>
		*  If you do not set a starting value, the default behavior is to return the first set of results.
		*  Range values are available to aid in paging results. Gracenote Service limits the number of
		*  responses returned in any one request, so the range values are available to indicate the total
		*  number of results, and where the current results fit in within that total.
		*  <p><b>Important:</b></p>
		*  The number of results actually returned for a query may not equal the number of results
		*  requested. To accurately iterate through results, always check the range start, end, and total
		*  values and the responses returned by Gracenote Service for the query (or queries). Ensure that you
		*  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
		*  using the initial requested value.
		*/
		class GnResponseVideoProduct : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseVideoProduct, GNSDK_GDO_TYPE_RESPONSE_VIDEO_PRODUCT);

			GnResponseVideoProduct() { }
			GnResponseVideoProduct(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseVideoProduct()  { }

			/**
			 *  Total number of results
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Ordinal of the first result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Ordinal of the last result in the returned range.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Estimated total number of results possible.
			 * @ingroup GDO_ValueKeys_Misc
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response match(es) need a user or app decision - either multiple matches returned or less than perfect single match..
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);

				return gnstd::gn_strtobool(return_value);
			}

			/**
			 *  Iterator for child video products
			 *  <p><b>Remarks:</b></p>
			 *  The ordinal parameter specifies the n'th child
			 * @ingroup GDO_ChildKeys_Video
			 */
			product_iterable Products() const
			{
				return product_iterable(gn_gdo_provider<GnVideoProduct>(*this, GNSDK_GDO_CHILD_VIDEO_PRODUCT), GN_GDO_START);
			}
		};

		inline series_iterable 
		GnVideoCredit::Series() const
		{
			return series_iterable(gn_gdo_provider<GnVideoSeries>(*this, GNSDK_GDO_CHILD_VIDEO_SERIES),GN_GDO_START);
		}

		inline season_iterable 
		GnVideoCredit::Seasons() const 
		{
			return season_iterable(gn_gdo_provider<GnVideoSeason>(*this,GNSDK_GDO_CHILD_VIDEO_SEASON),GN_GDO_START);
		}

		/* late implementation */
		inline series_iterable 
		GnVideoSeason::Series() const
		{
			return series_iterable(gn_gdo_provider<GnVideoSeries>(*this, GNSDK_GDO_CHILD_VIDEO_SERIES),GN_GDO_START);
		}
	} /* namespace metadata_video */
}     /* namespace gracenote */
#endif /* _GNSDK_METADATA_VIDEO_HPP_ */

