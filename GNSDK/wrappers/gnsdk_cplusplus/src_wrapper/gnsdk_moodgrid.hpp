/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_MOODGRID_HPP_
#define _GNSDK_MOODGRID_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_manager.hpp"
#include "metadata_music.hpp"

namespace gracenote
{
	namespace moodgrid
	{
#if GNSDK_MOODGRID

		/**
		** GnMoodgridDataPoint
		*/
		struct GnMoodgridDataPoint
		{
			GnMoodgridDataPoint() :X(0), Y(0) {}
			GnMoodgridDataPoint(gnsdk_uint32_t x, gnsdk_uint32_t y) :X(x), Y(y) {}
			bool operator == (const GnMoodgridDataPoint& rhs) const { return ( X == rhs.X ) && ( Y == rhs.Y );}
			gnsdk_uint32_t X;
			gnsdk_uint32_t Y;

		};

		/**
		** GnMoodgridPresentationType
		*/
		enum GnMoodgridPresentationType
		{
			kMoodgridPresentationType5x5   = 0x0505,
			kMoodgridPresentationType10x10 = 0x0A0A

		};

		enum GnMoodgridCoordinateType
		{
			kMoodgridCoordinateTopLeft,
			kMoodgridCoordinateBottomLeft

		};

		/**
		** <b>Experimental</b>: GnMoodgridIdentifier
		*/
		class GnMoodgridIdentifier
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Default Constructor
			 */
			GnMoodgridIdentifier() : ident_(GNSDK_NULL), group_(GNSDK_NULL) { }

			/**
			 * Destructor
			 */
			virtual
			~GnMoodgridIdentifier() { }

			/**
			 * Retrieves a read only string that is the media identifier.
			 */
			gnsdk_cstr_t
			MediaIdentifier() const { return ident_; }

			/**
			 * Retrieves a read only string that is the group the MediaIdentifier belongs too.
			 *  E.g. in the case of a Playlist provider , the group represents the name of the collection.
			 */
			gnsdk_cstr_t
			Group() const { return group_; }

			
			bool operator == (const GnMoodgridIdentifier& rhs) const { return ( (ident_ == rhs.ident_) && (group_ == rhs.group_));}

		protected:
			friend class moodgrid_result_provider;
			GnMoodgridIdentifier(gnsdk_cstr_t media_identifier, gnsdk_cstr_t group) : ident_(media_identifier), group_(group) { }


		private:
			gnsdk_cstr_t ident_;
			gnsdk_cstr_t group_;
		};


		/* Internal moodgrid result provider class */
		class moodgrid_result_provider
		{
		public:
			moodgrid_result_provider(gnsdk_moodgrid_result_handle_t results) : resultHandle_(results) { }
			~moodgrid_result_provider() { }

			GnMoodgridIdentifier
			get_data(gnsdk_uint32_t pos);

			/* optional */
			gnsdk_uint32_t
			count() const ;


		private:
			gnsdk_moodgrid_result_handle_t resultHandle_;
		};


		typedef gn_facade_range_iterator<GnMoodgridIdentifier, moodgrid_result_provider>   moodidentifier_iterator;
		typedef gn_iterable_container<GnMoodgridIdentifier, moodgrid_result_provider>      moodidentifier_iterable;


		/**
		** <b>Experimental</b>: GnMoodgridResult
		*/
		class GnMoodgridResult : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnMoodgridResult() { }

			/**
			 *  GnMoodgridResult Constructor.
			 *  @param handle : create a new GnMoodgridResult object that takes ownership of the native handle.
			 */
			explicit
			GnMoodgridResult(gnsdk_moodgrid_result_handle_t handle) : GnObject(handle) { }

			/**
			 *  Returns the count of the GnMoodgridIdentifier instances in this result.
             * @return count
			 */
			gnsdk_uint32_t
			Count() const throw (GnError);

			/**
			 * Retrieves an iterator to access the GnMoodgridIdentifier instances in this result.
             * @return identifiers
			 */
			moodidentifier_iterable Identifiers() const
			{
				return moodidentifier_iterable( moodgrid_result_provider(get<gnsdk_moodgrid_result_handle_t>()), GN_BASE_START);
			}


		protected:
			friend class GnMoodgridPresentation;
		};


		/**
		** <b>Experimental</b>: GnMoodgridProvider
		*/
		class GnMoodgridProvider : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE
            /**
             * Retrieves an iterator to access the GnMoodgridIdentifier instances in this result.
             *
             */
			GnMoodgridProvider()  { }
            /**
             * explicit contructor for the GnMoodgridProvider
             * @param handle [in] : native C handle of moodgrid provider
             */
			explicit
			GnMoodgridProvider(gnsdk_moodgrid_provider_handle_t handle) : GnObject(handle) { }

            /**
             * Retrieves the name of the moodgrid provider.
             * @return string representing the name of the provider.
             */
			gnsdk_cstr_t
			Name() throw (GnError);

            /**
             * Retrieves the type of Moodgrid provider.e.g. playlist collection
             * @return string value denoting type of provider
             */
			gnsdk_cstr_t
			Type() throw (GnError);

            /**
             * Retrieves a bool value whether the provider needs access to the network.
             * @return requiresnetwork
             */
			bool
			RequiresNetwork() throw (GnError);


		private:
			friend class GnMoodgridPresentation;
		};


		/**
		** Internal class  moodgrid_provider
		*/
		class moodgrid_provider
		{
		public:
			/* Required. */
			GnMoodgridProvider
			get_data(gnsdk_uint32_t pos);

			/* optional */
			gnsdk_uint32_t
			count() const;
		};


		/**
		** Internal class  presentation_data_provider
		*/
		class presentation_data_provider
		{
		public:
			presentation_data_provider() : type_(kMoodgridPresentationType5x5) { }
			presentation_data_provider(GnMoodgridPresentationType type) : type_(type) { }

			GnMoodgridDataPoint
			get_data(gnsdk_uint32_t pos);

			/* optional */
			gnsdk_uint32_t
			count() const;


		private:
			GnMoodgridPresentationType type_;
		};


		enum GnMoodgridFilterConditionType
		{
			kConditionTypeInclude = 1,
			kConditionTypeExclude

		};

		enum GnMoodgridFilterListType
		{
			kMoodgridListTypeGenre = 1,
			kMoodgridListTypeOrigins,
			kMoodgridListTypeEras

		};

		typedef gn_facade_range_iterator<GnMoodgridDataPoint, presentation_data_provider>   mooddatapoint_iterator;
		typedef gn_iterable_container<GnMoodgridDataPoint, presentation_data_provider>   mooddatapoint_iterable;

		/**
		** <b>Experimental</b>: GnMoodgridPresentation
		*/
		class GnMoodgridPresentation : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

            /**
             * Constructor for GnMoodgridPresentation
             */
			GnMoodgridPresentation() : GnObject(GNSDK_NULL), coordinate_(kMoodgridCoordinateTopLeft)  { }
			
            /**
             * Constructor for GnMoodgridPresentation for native C handles.
             */
            GnMoodgridPresentation( gnsdk_moodgrid_presentation_handle_t handle, GnMoodgridCoordinateType coordinate) : GnObject(handle), coordinate_(coordinate) { }

            /**
             * Retrieves an iterator to access the Mood data points in this presentation.
             * @return moods
             */
			mooddatapoint_iterable Moods() const throw (GnError);

            /**
             * Retrieves the presentation type the defines the no. of moods available in this presentation..
             * @return moods
             */
			GnMoodgridPresentationType
			LayoutType() throw (GnError);

			/**
             *  Retrieves the coordinate type that defines the layout of the presentation. 
             * @return moodgridcoordinatetype.
             */
			GnMoodgridCoordinateType
			CoordinateType() { return this->coordinate_; }

            /**
             * Adds a filter to the presentation for the inclusion of a list type to include or exclude from the recommendations.
             * @param uniqueIdentifier [in] : unique identifier for the presentation representing this filter.
             * @param elistType [in] : list type 
             * @param strValueId [in] : list value that is to be operated upon.
             * @param eConditionType [in]: filter condition
             */
			void
			AddFilter(gnsdk_cstr_t uniqueIdentifier, GnMoodgridFilterListType elistType, gnsdk_cstr_t strValueId, GnMoodgridFilterConditionType eConditionType) throw (GnError);
			
            /**
             * Removes a filter from the presentation represented by the unique identifier.
             * @param uniqueIdentifier [in] : identifier that represents the filter to be removed.
             */
            void
			RemoveFilter(gnsdk_cstr_t uniqueIdentifier) throw (GnError);
			
            /**
             * Removes all filters from the presentation
             */
            void
			RemoveAllFilters () throw (GnError);

            /**
             * Retrieves a mood name as defined by the locale for a given data point in the presentation.
             * @param position [in] : data position
             * @return moodname
             */
			gnsdk_cstr_t
			MoodName(const GnMoodgridDataPoint& position) throw (GnError);

            /**
             * Retrieves a mood id for the given data point in the presentation.
             * @param position [in] : data position
             * @return moodid.
             */
            
			gnsdk_cstr_t
			MoodId(const GnMoodgridDataPoint& position) throw (GnError);

            /**
             * Generates recommendations for a given mood data point and provider. The reccomentations are represented by a 
             * GnMoodgridResult.
             * @param provider [in] : moodgrid provider that the results must come from.
             * @param position [in] : data point that represents the mood for which reccomendation are requested.
             * @return GnMoodgridResult
             */
			GnMoodgridResult
			FindRecommendations(const GnMoodgridProvider& provider, const GnMoodgridDataPoint& position) throw (GnError);

            /**
             * Generates a recommendations estimate for a given mood data point and provider. The estimate is dependent on the 
             * provider. Use this functionality for creating a heat map of all the moods supported in the presentation.
             * @param provider [in] :moodgrid provider that the estimate must come from.
             * @param position [in] : data point that represents the mood for which the estimate is requested.
             * @return count representing the estimate.
             */
			gnsdk_uint32_t
			FindRecommendationsEstimate(const GnMoodgridProvider& provider, const GnMoodgridDataPoint& position) throw (GnError);


		protected:
			GnMoodgridCoordinateType coordinate_;
			friend class GnMoodgrid;
		};


		typedef gn_facade_range_iterator<GnMoodgridProvider, moodgrid_provider>   moodprovider_iterator;
		typedef gn_iterable_container<GnMoodgridProvider, moodgrid_provider>       moodprovider_iterable;


		/**
		 * <b>Experimental</b>: GnMoodgrid
		 */
		class GnMoodgrid : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnMoodgrid() { _gnsdk_internal::module_initialize(GNSDK_MODULE_MOODGRID); }

			/**
             * Version information for the library
             * @return version
             */
			static gnsdk_cstr_t
			Version() { return gnsdk_moodgrid_get_version(); }

			/** 
             * Build Date for the library
             * @return build date
             */
			static gnsdk_cstr_t
			BuildDate() { return gnsdk_moodgrid_get_build_date(); }

			/**
             * Enumeration of all providers currently available for the moodgrid. 
             * @return iterable container of moodgrid providers.
             */
			moodprovider_iterable Providers() const 
			{
				return moodprovider_iterable(moodgrid_provider(), GN_BASE_START);
			}

            /**
             * Creates a Presentation that represents the type of moodgrid layout to  generate recommendations for. A presentation
             * object is the way to access all Mood names and recommendations supported by its layout.
             * @param user [in] : valid user 
             * @param type [in] : enum value representing the Presentation type . 
             * @param coordinate [in] : enum value representing the coordinate type for the presentation layout.
             * @return presentation.
             */
			GnMoodgridPresentation
			CreatePresentation(const GnUser& user, GnMoodgridPresentationType type, GnMoodgridCoordinateType coordinate) throw (GnError);

			/**
             * Retrieves a data point representing the dimensions of the presentation e.g. 5,5 
             * @return datapoint.
             */
			GnMoodgridDataPoint
			Dimensions(GnMoodgridPresentationType type) throw (GnError);


		private:
			DISALLOW_COPY_AND_ASSIGN(GnMoodgrid);
		};


#endif /* GNSDK_MOODGRID */
	} /* namespace Playlist */

}     /* namespace GracenoteSDK */

#endif /* _GNSDK_MOODGRID_HPP_ */

