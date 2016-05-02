/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */
#include "gnsdk_base.hpp"

#if GNSDK_MOODGRID

#include "gnsdk_moodgrid.hpp"

using namespace gracenote;
using namespace gracenote::moodgrid;

/*-----------------------------------------------------------------------------
 *  _convert
 */
static void
_convert( GnMoodgridCoordinateType coordinate, GnMoodgridPresentationType type, const GnMoodgridDataPoint& in, GnMoodgridDataPoint& out)
{
	out.X = in.X;
	if (coordinate == kMoodgridCoordinateBottomLeft)
	{
		int offset = type == kMoodgridPresentationType5x5 ? 5 : 10;
		out.Y = offset - in.Y  + 1;
	}
	else
	{
		out.Y = in.Y;
	}
}


/* ********************************************************** */
/* / moodgrid_result_provider */
/* ********************************************************** */

GnMoodgridIdentifier
moodgrid_result_provider::get_data(gnsdk_uint32_t pos)
{
	gnsdk_cstr_t  media_ident = GNSDK_NULL;
	gnsdk_cstr_t  group       = GNSDK_NULL;
	gnsdk_error_t error;

	if ( pos < GN_UINT32_MAX)
	{
		error = gnsdk_moodgrid_results_enum(this->resultHandle_, pos, &media_ident, &group);
		if (!error) 
		{
			return GnMoodgridIdentifier(media_ident, group);
		}
	}
	return GnMoodgridIdentifier();

	
}


/*-----------------------------------------------------------------------------
 *  count
 */
gnsdk_uint32_t
moodgrid_result_provider::count() const 
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	error = gnsdk_moodgrid_results_count(resultHandle_, &count);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	return count;
}


/* ********************************************************** */
/* GnMoodgridResult */
/* ********************************************************** */
gnsdk_uint32_t
GnMoodgridResult::Count() const throw (GnError)
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	error = gnsdk_moodgrid_results_count(get<gnsdk_moodgrid_result_handle_t>(), &count);
	if (error) { throw GnError(); }

	return count;
}



/* ********************************************************** */
/* GnMoodgridProvider */
/* ********************************************************** */
gnsdk_cstr_t
GnMoodgridProvider::Name() throw (GnError)
{
	gnsdk_cstr_t  value = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_moodgrid_provider_get_data(this->get<gnsdk_moodgrid_provider_handle_t>(), GNSDK_MOODGRID_PROVIDER_NAME, &value);
	if (error) { throw GnError(); }

	return value;
}


/*-----------------------------------------------------------------------------
 *  Type
 */
gnsdk_cstr_t
GnMoodgridProvider::Type() throw (GnError)
{
	gnsdk_cstr_t  value = GNSDK_NULL;
	gnsdk_error_t error;
	
	error = gnsdk_moodgrid_provider_get_data(this->get<gnsdk_moodgrid_provider_handle_t>(), GNSDK_MOODGRID_PROVIDER_TYPE, &value);
	if (error) { throw GnError(); }

	return value;
}


/*-----------------------------------------------------------------------------
 *  RequiresNetwork
 */
bool
GnMoodgridProvider::RequiresNetwork() throw (GnError)
{
	gnsdk_cstr_t  value = GNSDK_NULL;
	gnsdk_error_t error;

	error = gnsdk_moodgrid_provider_get_data(this->get<gnsdk_moodgrid_provider_handle_t>(), GNSDK_MOODGRID_PROVIDER_TYPE, &value);
	if (error) { throw GnError(); }

	return gnstd::gn_strtobool(value);
}


/* ********************************************************** */
/* presentation_data_provider */
/* ********************************************************** */
GnMoodgridDataPoint
presentation_data_provider::get_data(gnsdk_uint32_t pos)
{
	gnsdk_uint32_t x, y, max_x, max_y;
	
	max_x = max_y = x = y  = 0;
	gnsdk_error_t  error = gnsdk_moodgrid_presentation_type_dimension( (gnsdk_moodgrid_presentation_type_t)type_, &max_x, &max_y);
	if (GNSDKERR_SEVERE(error)) { throw GnError(); }

	gnsdk_uint32_t max = max_x* max_y;
	/* Note: It is important to test in the case forward only iterators.*/
	if (pos < max)
	{
		x = ( pos + max_y ) / max_y;
		y = ( pos % max_y ) + 1;
	}

	return GnMoodgridDataPoint(x,y);
}


/* optional */
gnsdk_uint32_t
presentation_data_provider::count() const
{
	gnsdk_uint32_t max_x, max_y;
	gnsdk_error_t  error;

	error = gnsdk_moodgrid_presentation_type_dimension( (gnsdk_moodgrid_presentation_type_t)type_, &max_x, &max_y);
	if (error) { throw GnError(); }

	return max_x * max_y;
}


/* ********************************************************** */
/* GnMoodgridPresentation */
/* ********************************************************** */
mooddatapoint_iterable
GnMoodgridPresentation::Moods() const throw (GnError)
{
	gnsdk_moodgrid_presentation_type_t 	type;
	GnMoodgridPresentationType			cppType = kMoodgridPresentationType5x5;

	gnsdk_error_t error = gnsdk_moodgrid_presentation_get_type(this->get<gnsdk_moodgrid_presentation_handle_t>(), &type);
	if (error) { throw GnError(); }

	switch ( type )
	{
	case gnsdk_moodgrid_presentation_type_5x5:	cppType = kMoodgridPresentationType5x5; break;
	case gnsdk_moodgrid_presentation_type_10x10:cppType = kMoodgridPresentationType10x10; break;
	}
	return mooddatapoint_iterable( presentation_data_provider(cppType), GN_BASE_START);
}


/*-----------------------------------------------------------------------------
 *  AddFilter
 */
void
GnMoodgridPresentation::AddFilter(gnsdk_cstr_t uniqueIndentfier, GnMoodgridFilterListType elistType, gnsdk_cstr_t strValueId, GnMoodgridFilterConditionType eConditionType) throw (GnError)
{
	gnsdk_cstr_t cstrList      = GNSDK_NULL;
	gnsdk_cstr_t cstrCondition = GNSDK_MOODGRID_FILTER_CONDITION_INCLUDE;

	switch (elistType)
	{
	case kMoodgridListTypeGenre:
		cstrList = GNSDK_MOODGRID_FILTER_LIST_TYPE_GENRE;
		break;

	case kMoodgridListTypeEras:
		cstrList = GNSDK_MOODGRID_FILTER_LIST_TYPE_ORIGINS;
		break;

	case kMoodgridListTypeOrigins:
		cstrList = GNSDK_MOODGRID_FILTER_LIST_TYPE_ERAS;
		break;
	}

	/* Only need to handle the exclude case. */
	if (kConditionTypeExclude == eConditionType)
	{
		cstrCondition = GNSDK_MOODGRID_FILTER_CONDITION_EXCLUDE;
	}

	gnsdk_error_t error = gnsdk_moodgrid_presentation_filter_set(get<gnsdk_moodgrid_presentation_handle_t>(),
	                                                             uniqueIndentfier,
	                                                             cstrList,
	                                                             strValueId,
	                                                             cstrCondition);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  RemoveFilter
 */
void
GnMoodgridPresentation::RemoveFilter(gnsdk_cstr_t uniqueIndentfier) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_moodgrid_presentation_filter_remove(get<gnsdk_moodgrid_presentation_handle_t>(), uniqueIndentfier);
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  RemoveAllFilters
 */
void
GnMoodgridPresentation::RemoveAllFilters() throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_moodgrid_presentation_filter_remove_all(get<gnsdk_moodgrid_presentation_handle_t>() );
	if (error) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  LayoutType
 */
GnMoodgridPresentationType
GnMoodgridPresentation::LayoutType() throw (GnError)
{
	gnsdk_moodgrid_presentation_type_t eReturnType;
	gnsdk_error_t                      error;

	error = gnsdk_moodgrid_presentation_get_type(this->get<gnsdk_moodgrid_presentation_handle_t>(), &eReturnType);
	if (error) { throw GnError(); }

	return static_cast<GnMoodgridPresentationType>( eReturnType );
}


/*-----------------------------------------------------------------------------
 *  MoodName
 */
gnsdk_cstr_t
GnMoodgridPresentation::MoodName(const GnMoodgridDataPoint& position) throw (GnError)
{
	gnsdk_cstr_t        name       = GNSDK_NULL;
	GnMoodgridDataPoint calculated;

	_convert(coordinate_, this->LayoutType(), position, calculated);

	gnsdk_error_t error = gnsdk_moodgrid_presentation_get_mood_name(get<gnsdk_moodgrid_presentation_handle_t>(), calculated.X, calculated.Y, &name);
	if (error) { throw GnError(); }

	return name;
}


/*-----------------------------------------------------------------------------
 *  MoodId
 */
gnsdk_cstr_t
GnMoodgridPresentation::MoodId(const GnMoodgridDataPoint& position) throw (GnError)
{
	gnsdk_cstr_t        id         = GNSDK_NULL;

	GnMoodgridDataPoint calculated;
	_convert(coordinate_, this->LayoutType(), position, calculated);

	gnsdk_error_t error = gnsdk_moodgrid_presentation_get_mood_id(get<gnsdk_moodgrid_presentation_handle_t>(), calculated.X, calculated.Y, &id);
	if (error) { throw GnError(); }

	return id;
}


/*-----------------------------------------------------------------------------
 *  FindRecommendations
 */
GnMoodgridResult
GnMoodgridPresentation::FindRecommendations(const GnMoodgridProvider& provider, const GnMoodgridDataPoint& position) throw (GnError)
{
	gnsdk_moodgrid_result_handle_t handle     = GNSDK_NULL;

	GnMoodgridDataPoint  calculated;
	_convert(coordinate_, this->LayoutType(), position, calculated);

	gnsdk_error_t error = gnsdk_moodgrid_presentation_find_recommendations(get<gnsdk_moodgrid_presentation_handle_t>(), provider.get<gnsdk_moodgrid_provider_handle_t>(), calculated.X, calculated.Y, &handle);
	if (error) { throw GnError(); }

	GnMoodgridResult retVal;
	retVal.AcceptOwnership(handle);
	return retVal;
}


/*-----------------------------------------------------------------------------
 *  FindRecommendationsEstimate
 */
gnsdk_uint32_t
GnMoodgridPresentation::FindRecommendationsEstimate(const GnMoodgridProvider& provider, const GnMoodgridDataPoint& position) throw (GnError)
{
	gnsdk_uint32_t estimate = GNSDK_NULL;
	gnsdk_error_t  error;

	GnMoodgridDataPoint calculated;
	_convert(coordinate_, this->LayoutType(), position, calculated);

	error = gnsdk_moodgrid_presentation_find_recommendations_estimate(get<gnsdk_moodgrid_presentation_handle_t>(), provider.get<gnsdk_moodgrid_provider_handle_t>(), calculated.X, calculated.Y, &estimate);
	if (error) { throw GnError(); }

	return estimate;
}


/* ********************************************************** */
/* moodgrid_provider */
/* ********************************************************** */
GnMoodgridProvider
moodgrid_provider::get_data(gnsdk_uint32_t pos)
{
	gnsdk_moodgrid_provider_handle_t provider = GNSDK_NULL;
	gnsdk_error_t                    error;

	error = gnsdk_moodgrid_provider_enum(pos, &provider);

	if (GNSDKERR_SEVERE(error)) {throw GnError();}

	GnMoodgridProvider result(provider);
	gnsdk_handle_release(provider);
	return result;
}


/* optional */
gnsdk_uint32_t
moodgrid_provider::count() const
{
	gnsdk_uint32_t count = 0;
	gnsdk_error_t  error;

	error = gnsdk_moodgrid_provider_count(&count);
	if (error) { throw GnError(); }

	return count;
}



/*-----------------------------------------------------------------------------
 *  CreatePresentation
 */
GnMoodgridPresentation
GnMoodgrid::CreatePresentation(const GnUser& user, GnMoodgridPresentationType type, GnMoodgridCoordinateType coordinate) throw (GnError)
{
	gnsdk_moodgrid_presentation_handle_t handle = GNSDK_NULL;
	gnsdk_error_t                        error;

	error = gnsdk_moodgrid_presentation_create(user.native(), (gnsdk_moodgrid_presentation_type_t)type, GNSDK_NULL, GNSDK_NULL, &handle);
	if (error) { throw GnError(); }

	GnMoodgridPresentation result(GNSDK_NULL, coordinate);

	result.AcceptOwnership(handle);

	return result;
}


/*-----------------------------------------------------------------------------
 *  Dimensions
 */
GnMoodgridDataPoint
GnMoodgrid::Dimensions(GnMoodgridPresentationType type) throw (GnError)
{
	GnMoodgridDataPoint result;
	gnsdk_error_t       error;

	error = gnsdk_moodgrid_presentation_type_dimension((gnsdk_moodgrid_presentation_type_t)type, &result.X, &result.Y);
	if (error) { throw GnError(); }

	return result;
}


#endif /*GNSDK_MOODGRID*/

