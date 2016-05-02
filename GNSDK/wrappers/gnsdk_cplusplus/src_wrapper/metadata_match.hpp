/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

 /**
 * @file metadata_match.hpp
 */
 
#ifndef _GNSDK_METADATA_MATCH_HPP_
#define _GNSDK_METADATA_MATCH_HPP_

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

#if GNSDK_MUSICID_MATCH
		class GnMatch;
		typedef gn_facade_range_iterator<GnMatch, gn_gdo_provider<GnMatch> >            match_iterator;
		typedef gn_iterable_container<GnMatch, gn_gdo_provider<GnMatch> >				match_iterable;

		/**
		 * GnMatch
		 */
		class GnMatch : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Constructs empty GnMatch object
			 */
			GnMatch() { }

			/**
			 * Constructs a GnMatch object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnMatch(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnMatch() { }

			/**
			 * Match's Gracenote Tui (title-unique identifier)
			 * @return Tui
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 * Match's Gracenote Tui Tag.
			 * @return Tui Tag
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 *  Match info type - album or contributor
			 *  @return Match information
			 */
			gnsdk_cstr_t
			MatchInfo() const
			{
				return StringValue(GNSDK_GDO_VALUE_MATCH_INFO_TYPE);
			}

			/**
			 * Iterator for match's external identifiers (e.g., Amazon's).
			 * @return Iterator
			 */
			externalid_iterable ExternalIds() const
			{
				return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}

		};  // GnMatch


        /**
         *  Collection of matches from a Scan & Match query
         */
		class GnResponseMatches : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Constructs empty GnResponseMatches object
			 */
			GnResponseMatches() { }

			/**
			 * Constructs a GnResponseMatches object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			explicit
			GnResponseMatches(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseMatches() { }

			/**
			 * Iterator for accessing response match(es)
			 * @return Iterator
			 */
			match_iterable
			Matches() const
			{
				return match_iterable(gn_gdo_provider<GnMatch> (*this, GNSDK_GDO_CHILD_MATCH_INFO), GN_GDO_START);
			}

		};  // GnResponseMatches

#endif //GNSDK_MUSICID_MATCH

 	} /* namespace metadata */
}     /* namespace gracenote */
#endif /* _GNSDK_METADATA_MATCH_HPP_ */

