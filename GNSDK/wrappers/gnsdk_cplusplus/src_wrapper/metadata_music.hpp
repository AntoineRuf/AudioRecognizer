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
 * @file metadata_music.hpp
 */
 
#ifndef _GNSDK_METADATA_MUSIC_HPP_
#define _GNSDK_METADATA_MUSIC_HPP_

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
		class GnTrack;
		class GnAlbum;
		class GnDataMatch;

		typedef gn_facade_range_iterator<GnTrack, gn_gdo_provider<GnTrack> >           track_iterator;
		typedef gn_facade_range_iterator<GnCredit, gn_gdo_provider<GnCredit> >         credit_iterator;
		typedef gn_facade_range_iterator<GnAlbum, gn_gdo_provider<GnAlbum> >           album_iterator;
		typedef gn_facade_range_iterator<GnDataMatch, gn_gdo_provider<GnDataMatch> >   datamatch_iterator;
		typedef gn_facade_range_iterator<gnsdk_cstr_t, gn_gdo_string_provider>		   string_iterator;

		typedef gn_iterable_container<GnTrack, gn_gdo_provider<GnTrack> >           track_iterable;
		typedef gn_iterable_container<GnCredit, gn_gdo_provider<GnCredit> >         credit_iterable;
		typedef gn_iterable_container<GnAlbum, gn_gdo_provider<GnAlbum> >           album_iterable;
		typedef gn_iterable_container<GnDataMatch, gn_gdo_provider<GnDataMatch> >   datamatch_iterable;
		typedef gn_iterable_container<gnsdk_cstr_t, gn_gdo_string_provider>			string_iterable;

		/**
		 * \class GnAudioWork
		 * A collection of classical music recordings.
		 */
		class GnAudioWork : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnAudioWork, GNSDK_GDO_TYPE_AUDIO_WORK);

			/**
			 * Constructs empty GnAudioWork object
			 */
			GnAudioWork() { }

			/**
			 * Constructs a GnAudioWork object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnAudioWork(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnAudioWork() { }

			/**
			 * Audio work's official title.
			 * @return Title
			 */
			GnTitle
			Title() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 * Credit object for this audio work.
			 * @return Credit
			 */
			GnCredit
			Credit() const
			{
				return ChildGet<GnCredit>(GNSDK_GDO_CHILD_CREDIT);
			}

			/**
			 * Gracenote Tui (title unique identifier) for this audio work.
			 * @return Tui
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 * Gracenote Tui Tag for this audio work.
			 * @return Tui Tag
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 * Gracenote Tag identifier for this audio work (Tag ID is same as Product ID)
			 * @return Tag identifier
			 * <p><b>Remarks:</b></p>
			 * This method exists primarily to support legacy implementations. We recommend using
			 * the Product ID method to retrieve product related identifiers
			 */
			gnsdk_cstr_t
			TagId() const
			{
				return StringValue(GNSDK_GDO_VALUE_TAGID);
			}

			/**
			 * Audio work's Gracenote identifier
			 * @return Gracenote identifier
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 * Audio work's Gracenote unique identifier.
			 * @return Gracenote unique identifier
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 * Audio work's product ID (aka Tag ID).
			 * <p><b>Remarks:</b></p>
			 * Available for most types, this value can be stored or transmitted. Can
			 * be used as a static identifier for the current content as it will not change over time.
			 * @ingroup GDO_ValueKeys_GracenoteIDs
			 */
			gnsdk_cstr_t
			ProductId() const
			{
				return StringValue(GNSDK_GDO_VALUE_PRODUCTID);
			}

			/**
			 * Audio work's geographic location, e.g., New York City. List/locale dependent multi-leveled field.
			 * @param level	[in] Data level
			 * @return Origin
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
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
			 * Audio work's era. List/locale dependent, multi-leveled field.
			 * @param level	[in] Data level
			 * @return Era
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
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
			 * Audio work's genre, e.g. punk rock, rock opera, etc. List/locale dependent, multi-level field.
			 * @param level	[in] Data level
			 * @return Genre
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
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
			 * Audio work's classical music composition form value (e.g., Symphony).
			 * @return Compsition form
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
			 */
			gnsdk_cstr_t
			CompositionForm() const
			{
				return StringValue(GNSDK_GDO_VALUE_COMPOSITION_FORM);
			}

		};  // GnAudioWork


		/**
		 * Person or group primarily responsible for creating the Album or Track.
		 */
		class GnArtist : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnArtist, GNSDK_GDO_TYPE_ARTIST);

			/**
			 * Constructs empty GnArtist object
			 */
			GnArtist() { }

			/**
			 * Constructs a GnArtist object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnArtist(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnArtist() { }

			/**
			 * Artist's official name.
			 * @return Name
			 */
			GnName
			Name() const
			{
				return ChildGet<GnName>(GNSDK_GDO_CHILD_NAME_OFFICIAL);
			}

			/**
			 * Contributor object - contributor associated with the work
			 * @return Contributor
			 */
			GnContributor
			Contributor() const
			{
				return ChildGet<GnContributor>(GNSDK_GDO_CHILD_CONTRIBUTOR);
			}

		};  // GnArtist


		/**
		 * A song or instrumental recording.
		 */
		class GnTrack : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnTrack, GNSDK_GDO_TYPE_TRACK);

			/**
			 * Constructs empty GnTrack object
			 */
			GnTrack() { }

			/**
			 * Constructs a GnTrack object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnTrack(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			/** Constructs a GnTrack object from identifier and identifie tag
			 * @param id	[in] Identifier
			 * @param idTag	[in] Identifier tag
			 */
			GnTrack(gnsdk_cstr_t id, gnsdk_cstr_t idTag) throw (GnError) : GnDataObject(id, idTag, GNSDK_ID_SOURCE_TRACK) { }

			virtual
			~GnTrack() { }

			/**
			 *  Flag indicating if response contains full (true) or partial (false) metadata.
			 *  @return True if full result, false otherwise
			 * <p><b>Note:</b></p>
			 *   What constitutes a full result varies among the individual response types and results, and also
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
			 * Track's official title.
			 * @return Title
			 */
			GnTitle
			Title() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 * Track's artist.
			 * @return Artist
			 */
			GnArtist
			Artist() const
			{
				return ChildGet<GnArtist>(GNSDK_GDO_CHILD_ARTIST);
			}

			/**
			 * Track's audio work.
			 * @return Work
			 */
			GnAudioWork
			Work() const
			{
				return ChildGet<GnAudioWork>(GNSDK_GDO_CHILD_AUDIO_WORK);
			}

			/**
			 * Track's mood, e.g., Playful. List/locale dependent, multi-level field.
			 * @param level	[in] Data level
			 * @return Mood
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
			 */
			gnsdk_cstr_t
			Mood(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_MOOD_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_MOOD_LEVEL2;
					break;

				default:
					break;
				}
				return StringValue(key);
			}


			/**
			 * Track's tempo, e.g., Fast. List/locale dependent, multi-leveled field.
			 * @param level	[in] Data level
			 * @return Tempo
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
			 */
			gnsdk_cstr_t
			Tempo(GnDataLevel level) const
			{
				gnsdk_cstr_t key = GNSDK_NULL;
				switch (level)
				{
				case kDataLevel_1:
					key = GNSDK_GDO_VALUE_TEMPO_LEVEL1;
					break;

				case kDataLevel_2:
					key = GNSDK_GDO_VALUE_TEMPO_LEVEL2;
					break;

				case kDataLevel_3:
					key = GNSDK_GDO_VALUE_TEMPO_LEVEL3;
					break;

				default:
					break;
				}
				return StringValue(key);
			}

			/**
			 * Track's genre, e.g., Heavy Metal. List/locale dependent, multi-level field
			 * @param level	[in] Data level
			 * @return Genre
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
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
			 *  Track's content, e.g., cover image, artist image, biography etc.
			 *  @param GnContentType object
			 *  @return Content object
			 */
			GnContent
			Content(GnContentType contentType) const
			{
				gnsdk_cstr_t key = gnconvert::_convertContentTypeCppC(contentType);
				return ChildGet<GnContent>(key);
			}

			/**
			 *  Fetch the album's review content object
			 *  @return Content object
			 */
			GnContent
			Review() const
			{
				return ChildGet<GnContent>(GNSDK_GDO_CHILD_CONTENT_REVIEW);
			}

			/* this is supported for GnTrack, should it be?
			GnContent
			Biography() const
			{
				return ChildGet<GnContent>(GNSDK_GDO_CHILD_CONTENT_BIOGRAPHY);
			}*/

			/**
			 * Flag indicating if this is the matched track (true)
			 * @return True if matched track, false otherwise
			 */
			bool
			Matched() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCHED);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 * Position in milliseconds of where we matched in the track
			 * @return Match position in milliseconds
			 */
			gnsdk_uint32_t
			MatchPosition() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCH_POSITION_MS);
				return gnstd::gn_atoi(return_value);
			}
			
			
			/**
			 * For MusicID-Stream fingerprint matches, this is the length of matched reference audio in
			 * milliseconds.
			 */
			gnsdk_uint32_t
			MatchDuration() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_MATCH_DURATION_MS);
				return gnstd::gn_atoi(return_value);
			}


		   /**
			 * Current position in milliseconds of the matched track.
			 * The current position tracks the approximate real time position of the
			 * playing audio track assuming it is not paused. Only available from
			 * GnMusicIdStream responses.
			 * @return Current position in milliseconds
			 */
			gnsdk_uint32_t
			CurrentPosition() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_CURRENT_POSITION_MS);
				return gnstd::gn_atoi(return_value);
			}
			

			/**
			 * Duration in milliseconds of the track (only available if this is the matched track)
			 * @return Duration in milliseconds
			 */
			gnsdk_uint32_t
			Duration () const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_DURATION);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Iterator for accessing credits for this album, except artist credit.
			 * The Artist Credit is accessed via a dedicated method.
			 * @return Iterator
			 */
			credit_iterable Credits() const
			{
				return credit_iterable(gn_gdo_provider<GnCredit>(*this, GNSDK_GDO_CHILD_CREDIT), GN_GDO_START);
			}

			/**
			 * Iterator for the content (cover art, biography, etc.)  associated with this track.
			 * @return Iterator
			 */
			content_iterable Contents() const
			{
				return content_iterable(gn_gdo_provider<GnContent>(*this, GNSDK_GDO_CHILD_CONTENT), GN_GDO_START);
			}

			/**
			 * Iterator for the track's external identifiers (ids from sources external to Gracenote, e.g., Amazon)
			 * @return Iterator
			 */
			externalid_iterable ExternalIds() const
			{
				return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID), GN_GDO_START);
			}

			/**
			 * Track's Gracenote Tui (title-unique identifier).
			 * @return Tui
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 * Track's Gracenote Tui Tag.
			 * @return Tui Tag
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 * Track's Gracenote Tag identifier (same as Product ID)
			 * @return Gracenote Tag identifier
			 * <p><b>Remarks:</b></p>
			 * This method exists primarily to support legacy implementations. We recommend using
			 * the Product ID method to retrieve product related identifiers
			 */
			gnsdk_cstr_t
			TagId() const
			{
				return StringValue(GNSDK_GDO_VALUE_TAGID);
			}

			/**
			 * Track's Gracenote identifier
			 * @return Gracenote identifier
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 * Track's Gracenote unique identifier.
			 * @return Gracenote unique identifier
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 * Track's ordinal number on album.
			 * @return Track number
			 */
			gnsdk_cstr_t
			TrackNumber() const
			{
				return StringValue(GNSDK_GDO_VALUE_TRACK_NUMBER);
			}

			/**
			 * Track's year.
			 * @return Year
			 */
			gnsdk_cstr_t
			Year() const
			{
				return StringValue(GNSDK_GDO_VALUE_YEAR);
			}


			/**
			 * Track identifiers . Each identifier is associated with a file information object presented to Music-ID.
			 * @return Matched identifier
			 */
			string_iterable MatchedIdents() const 
			{
				return string_iterable( gn_gdo_string_provider(*this,GNSDK_GDO_VALUE_IDENT),GN_GDO_START); 
			}


			/**
			 * Track's match type - the most authoritative matching type for a given file info object.
			 * @return Match lookup type
			 *  <p><b>Remarks:</b></p>
			 * The match type indicates which query type was the most authoritative matching type for a given file
			 * information object.
			 * MusicID-File does a query for each type of input data, and each type of input data has an authoritative rank.
			 * The match type indicates the highest authoritative matched type for this file information object.
			 * The match type is only useful in comparison to other match types. By itself it does not indicate
			 * a strong or poor match. The higher the match type, the more authoritative the identification process
			 * used.
			 * The following table lists the possible match type values:
			 * <table>
			 * <tr><th>Match Type</th><th>Value</th></tr>
			 * <tr><td>MIDF_MATCH_TYPE_TUI</td><td>11</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_MUI</td><td>10</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_TOC</td><td>9</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_ASSOCIATED_ID</td><td>8</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_WF</td><td>7</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_TEXT_ON_WF</td><td>6</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_ASSOCIATED_TEXT</td><td>5</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_TEXT_TRACK</td><td>4</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_TEXT_ALBUM</td><td>3</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_TEXT_CONTRIBUTOR</td><td>2</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_NONE</td><td>1</td></tr>
			 * <tr><td>MIDF_MATCH_TYPE_INVALID</td><td>0</td></tr>
			 * </table>
			 */
			gnsdk_cstr_t
			MatchLookupType() const
			{
				// Using macro GNSDK_GDO_VALUE_TRACK_MATCH_TYPE instead of macro GNSDK_MUSICIDFILE_GDO_VALUE_MATCH_TYPE,
				// as macro GNSDK_MUSICIDFILE_GDO_VALUE_MATCH_TYPE may not be defined 
				// based on - product includes gnsdk_musicidfile.hpp or not 
				return StringValue(GNSDK_GDO_VALUE_TRACK_MATCH_TYPE);
			}

			/**
			 *  Confidence score (0-100) for match
			 *  @return Confidence score
			 */
			gnsdk_cstr_t
			MatchConfidence() const
			{
				// Using direct string key instead of macro GNSDK_MUSICIDFILE_GDO_VALUE_MATCH_CONFIDENCE, 
				// as macro GNSDK_MUSICIDFILE_GDO_VALUE_MATCH_CONFIDENCE may not be defined 
				// based on - product includes gnsdk_musicidfile.hpp or not  
				return StringValue("gnsdk_midf_val_matchconf");
			}


			/**
			 * Track's match score - correlation between input text and matched track
			 * @return Match score
			 * <p><b>Remarks:</b></p>
			 * The match score gives a correlation between the input text and the matched track,
			 * indicating how well the input text matched the track. However, any result that is returned
			 * is considered to be a good match. The match score is only useful in comparison to other match
			 * scores. By itself it does not indicate a strong or poor match.
			 */
			gnsdk_uint32_t
			MatchScore() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_TEXT_MATCH_SCORE);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Title presented using Gracenote's Three Line Solution for classical track (composer/work title/movement title)
			 *  @return Title
			 */
			GnTitle
			TitleClassical() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_TLS);
			}

			/**
			 *  Regional title. Locale/list dependent field.
			 *  @return Title
			 */
			GnTitle
			TitleRegional() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_REGIONAL);
			}

		};  // GnTrack


		/**
		 * Collection of track results received in response to a track query
		 */
		class GnResponseTracks : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseTracks, GNSDK_GDO_TYPE_RESPONSE_TRACK);

			/**
			 * Constructs empty GnResponseTracks object
			 */
			GnResponseTracks() { }

			/**
			 * Constructs a GnResponseTracks object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnResponseTracks(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseTracks() { }

			/**
			 *  Result count - number of matches returned
			 *  @return Count
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Range start - ordinal value of first match in range total
			 *  @return Range start ordinal
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Range end - ordinal value of last match in range total
			 *  @return Range end ordinal
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Range total - total number of matches that could be returned
			 *  @return Range total
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Flag indicating if response needs user decision - either multiple matches returned or less than perfect single match
			 *  @return True if user decision required, false otherwise
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 * Iterable for accessing response tracks
			 * @return Iterator
			 */
			track_iterable
			Tracks() const
			{
				return track_iterable(gn_gdo_provider<GnTrack>(*this, GNSDK_GDO_CHILD_TRACK),GN_GDO_START);
			}

		};


		/**
		 * Collection of audio recordings.
		 * Provides access to album cover art when received from a query object
		 * with content enabled in lookup data.
		 */
		class GnAlbum : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnAlbum, GNSDK_GDO_TYPE_ALBUM);

			/**
			 * Constructs empty GnAlbum object
			 */
			GnAlbum() { }

			/**
			 * Constructs a GnAlbum object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnAlbum(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			/**
			 * Constructs a GnAlbum object from identifier and identifier tag
			 * @param id	[in] Identifier
			 * @param idTag	[in] Identifier tag
			 */
			GnAlbum(gnsdk_cstr_t id, gnsdk_cstr_t idTag) throw (GnError) : GnDataObject(id, idTag, GNSDK_ID_SOURCE_ALBUM) { }


			virtual
			~GnAlbum() { }

			/**
			 *  Flag indicating if response contains full (true) or partial (false) metadata.
			 *  @return True if full result, false if partial result
			 * <p><b>Note:</b></p>
			 *   What constitutes a full result varies among the individual response types and results, and also
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
			 * Album's official title.
			 * @return Title
			 */
			GnTitle
			Title() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_OFFICIAL);
			}

			/**
			 * Album's artist.
			 * @return Artist
			 */
			GnArtist
			Artist() const
			{
				return ChildGet<GnArtist>(GNSDK_GDO_CHILD_ARTIST);
			}

			/**
			 * Album's genre, e.g., punk rock. List/locale dependent, multi-level field.
			 * @param level	[in] Data level
			 * @return Genre
			 * <p><b>Remarks:</b></p>
			 * This is a list-based value requiring that a corresponding locale or list be loaded.
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
			 * Album's label - record company that released the album, e.g., Atlantic.
			 * Album label values are not always available.
			 * @return Label
			 */
			gnsdk_cstr_t
			Label() const
			{
				return StringValue(GNSDK_GDO_VALUE_ALBUM_LABEL);
			}


			/**
			 *  Display language
			 *  @return Language string
			 */
			gnsdk_cstr_t
			Language() const
			{
				return StringValue(GNSDK_GDO_VALUE_DISPLAY_LANGUAGE_DISPLAY);
			}

			/**
			 *  Display langauge's 3-letter ISO code
			 *  @return Language code
			 */
			gnsdk_cstr_t
			LanguageCode() const
			{
				return StringValue(GNSDK_GDO_VALUE_PACKAGE_LANGUAGE);
			}

			/**
			 * Album's Gracenote Tui (title-unique identifier)
			 * @return Tui
			 */
			gnsdk_cstr_t
			Tui() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI);
			}

			/**
			 * Album's Gracenote Tui Tag
			 * @return Tui Tag
			 */
			gnsdk_cstr_t
			TuiTag() const
			{
				return StringValue(GNSDK_GDO_VALUE_TUI_TAG);
			}

			/**
			 * Album's Gracenote Tag identifier (Tag ID is same as Product ID)
			 * @return Gracenote Tag identifier
			 * <p><b>Remarks:</b></p>
			 * This method exists primarily to support legacy implementations. We recommend using
			 * the Product ID method to retrieve product related identifiers
			 */
			gnsdk_cstr_t
			TagId() const
			{
				return StringValue(GNSDK_GDO_VALUE_TAGID);
			}

			/**
			 * Album's Gracenote identifier.
			 * @return Gracenote identifier
			 */
			gnsdk_cstr_t
			GnId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNID);
			}

			/**
			 * Album's Gracenote unique identifier.
			 * @return Gracenote unique identifier
			 */
			gnsdk_cstr_t
			GnUId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GNUID);
			}

			/**
			 * Album's global identifier (used for transcriptions).
			 * @return Gracenote Global identifier
			 */
			gnsdk_cstr_t
			GlobalId() const
			{
				return StringValue(GNSDK_GDO_VALUE_GLOBALID);
			}

			/**
			 * Album's volume number in a multi-volume set.
			 * This value is not always available.
			 * @return Disc in set
			 */
			gnsdk_uint32_t
			DiscInSet() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ALBUM_DISC_IN_SET);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Total number of volumes in album's multi-volume set.
			 * This value is not always available.
			 * @return Total in set
			 */
			gnsdk_uint32_t
			TotalInSet() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ALBUM_TOTAL_IN_SET);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Year the album was released.
			 * @return year
			 */
			gnsdk_cstr_t
			Year() const
			{
				return StringValue(GNSDK_GDO_VALUE_YEAR);
			}

			/**
			 * Flag indicating if enhanced classical music data exists
			 * for this album.
			 * @return True is this is a classical album, false otherwise
			 */
			bool
			IsClassical() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_CLASSICAL_DATA);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 * Total number of tracks on this album.
			 * @return Count
			 */
			gnsdk_uint32_t
			TrackCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_ALBUM_TRACK_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Album's compilation value
			 * @return Compilation
			 */
			gnsdk_cstr_t
			Compilation() const
			{
				return StringValue(GNSDK_GDO_VALUE_ALBUM_COMPILATION);
			}

			/**
			 * Match confidence score for top-level match
			 * @return Match score
			 */
			gnsdk_uint32_t
			MatchScore() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_TEXT_MATCH_SCORE);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Album track using the track number.
			 * @param trackNumber	Ordinal of the desired track (1-based)
			 * @return Track
			 */
			GnTrack
			Track(gnsdk_uint32_t trackNumber) const
			{
				return ChildGet<GnTrack>(GNSDK_GDO_CHILD_TRACK_BY_NUMBER, trackNumber);
			}

			/**
			 * Ordinal value on album for matching track
			 * @param ordinal	Ordinal of the desired track (1-based)
			 * @return Track
			 */
			GnTrack
			TrackMatched(gnsdk_uint32_t ordinal = 1) const
			{
				return ChildGet<GnTrack>(GNSDK_GDO_CHILD_TRACK_MATCHED, ordinal);
			}

			/**
			 * Track number on album for matching track
			 * @param ordinal	Ordinal of the desired track (1-based)
			 * @return Matched number
			 */
			gnsdk_uint32_t
			TrackMatchNumber(gnsdk_uint32_t ordinal = 1) const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_TRACK_MATCHED_NUM, ordinal);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Content (cover art, biography, review, etc.) object
			 *  @param GnContentType object
			 *  @return Content object
			 */
			GnContent
			Content(GnContentType contentType) const
			{
				gnsdk_cstr_t key = gnconvert::_convertContentTypeCppC(contentType);
				return ChildGet<GnContent>(key);
			}

			/**
			 *  Fetch the album's cover art content object
			 *  @return Content object
			 */
			GnContent
			CoverArt() const
			{
				return ChildGet<GnContent>(GNSDK_GDO_CHILD_CONTENT_IMAGECOVER);
			}

			/**
			 *  Fetch the album's review content object
			 *  @return Content object
			 */
			GnContent
			Review() const
			{
				return ChildGet<GnContent>(GNSDK_GDO_CHILD_CONTENT_REVIEW);
			}

			/* this is supported for GnAlbum, should it be?
			GnContent
			Biography() const
			{
				return ChildGet<GnContent>(GNSDK_GDO_CHILD_CONTENT_BIOGRAPHY);
			}*/

			/**
			 * Iterator for accessing album tracks
			 * @return Iterator
			 */
			track_iterable
			Tracks() const
			{
				return track_iterable(gn_gdo_provider<GnTrack>(*this, GNSDK_GDO_CHILD_TRACK),GN_GDO_START);
			}

			/**
			 * Iterator for accessing album's matched track(s).
			 * @return Iterator
			 */
			track_iterable
			TracksMatched() const
			{
				return track_iterable(gn_gdo_provider<GnTrack>(*this, GNSDK_GDO_CHILD_TRACK_MATCHED),GN_GDO_START);
			}

			/**
			 * Iterator for accessing album credits, except artist credit, which is accessed with another dedicated method
			 * The Artist Credit is accessed via a dedicated method.
			 * @return Iterator
			 */
			credit_iterable Credits() const
			{
				return credit_iterable(gn_gdo_provider<GnCredit>(*this, GNSDK_GDO_CHILD_CREDIT),GN_GDO_START);
			}

			/**
			 * Iterator for the content associated with this contributor.
			 * @return Iterator
			 */
			content_iterable Contents() const
			{
				return content_iterable(gn_gdo_provider<GnContent>(*this, GNSDK_GDO_CHILD_CONTENT),GN_GDO_START);
			}

			/**
			 * Iterator for album's external identifiers, e.g., Amazon's identifier.
			 * @return Iterator
			 */
			externalid_iterable ExternalIds() const
			{
				return externalid_iterable(gn_gdo_provider<GnExternalId>(*this, GNSDK_GDO_CHILD_EXTERNAL_ID),GN_GDO_START);
			}

			/**
			 *  Title presented using Gracenote's Three Line Solution for classical track (composer/work title/movement title)
			 *  @return Title
			 */
			GnTitle
			TitleClassical() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_TLS);
			}

			/**
			 *  Regional title - list/locale dependent field
			 *  @return Title
			 */
			GnTitle
			TitleRegional() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_REGIONAL);
			}

			/**
			 *  Regional locale title - list/locale dependent field
			 *  @return Title
			 */
			GnTitle
			TitleRegionalLocale() const
			{
				return ChildGet<GnTitle>(GNSDK_GDO_CHILD_TITLE_REGIONAL_LOCALE);
			}
			/**
			 *  Script used by the display values as ISO 15924 code
			 *  @return Script value.
			 */
			gnsdk_cstr_t Script() const 
			{
				return StringValue(GNSDK_GDO_VALUE_DISPLAY_SCRIPT);
			}
		};  // GnAlbum


		/**
		 * Collection of album results received in response to an album query.
		 */
		class GnResponseAlbums : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GNSDK_CHECKED_CAST(GnResponseAlbums, GNSDK_GDO_TYPE_RESPONSE_ALBUM);

			/**
			 * Constructs empty GnResponseAlbums object
			 */
			GnResponseAlbums() { }

			/**
			 * Constructs a GnResponseAlbums object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnResponseAlbums(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseAlbums() { }

			/**
			 *  Number of matches returned
			 *  @return Count
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Ordinal of the first result in the returned range.
			 *  @return Range start
			 *  <p><b>Remarks:</b></p>
			 *  If you do not set a starting value, the default behavior is to return the first set of results.
			 *  Range values are available to aid in paging results. Gracenote limits the number of
			 *  responses returned in any one request, so the range values are available to indicate the total
			 *  number of results, and where the current results fit in within that total.
			 *
			 *  <p><b>Important:</b></p>
			 *  The number of results actually returned for a query may not equal the number of results initially
			 *  requested. To accurately iterate through results, always check the range start, end, and total
			 *  values and the responses returned for the query (or queries). Ensure that you
			 *  are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
			 *  using the initial requested value.
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Ordinal of the last result in the returned range.
			 * @return Range end
			 * <p><b>Remarks:</b></p>
			 * Range values are available to aid in paging results. Gracenote limits the number of
			 * responses returned in any one request, so the range values are available to indicate the total
			 * number of results, and where the current results fit in within that total.
			 *
			 * <p><b>Important:</b></p>
			 * The number of results actually returned for a query may not equal the number of results initially
			 * requested. To accurately iterate through results, always check the range start, end, and total
			 * values and the responses returned for the query (or queries). Ensure that you
			 * are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
			 * using the initial requested value.
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Estimated total number of results possible.
			 * @return Range total
			 * <p><b>Remarks:</b></p>
			 * Range values are available to aid in paging results. Gracenote limits the number of
			 * responses returned in any one request, so the range values are available to indicate the total
			 * number of results, and where the current results fit in within that total.
			 * The total value may be estimated.
			 *
			 * <p><b>Important:</b></p>
			 * The number of results actually returned for a query may not equal the number of results initially
			 * requested. To accurately iterate through results, always check the range start, end, and total
			 * values and the responses returned for the query (or queries). Ensure that you
			 * are incrementing by using the actual last range end value plus one (range_end+1), and not by simply
			 * using the initial requested value.
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);
				return gnstd::gn_atoi(return_value);
			}

			/**
			 * Flag indicating if response need a user or app decision - either multiple matches returned or less than perfect single match.
			 * @return True if user decision needed, false otherwise
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 * Iterator for accessing matched albums.
			 * @return Iterator
			 */
			album_iterable
			Albums() const
			{
				return album_iterable(gn_gdo_provider<GnAlbum> (*this, GNSDK_GDO_CHILD_ALBUM), GN_GDO_START);
			}

		};  // GnResponseAlbums


		/**
		 *  Represents a match to query where any type of match is desired, album or contributor.
		 */
		class GnDataMatch : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Constructs empty GnDataMatch object
			 */
			GnDataMatch() { }

			/**
			 * Constructs a GnDataMatch object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			explicit
			GnDataMatch(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnDataMatch() { }

			/**
			 *  Flag indicating if match is album
			 *  @return True if album is a match, false otherwise
			 */
			bool
			IsAlbum() const
			{
				return 0 == gnstd::gn_strcmp(GNSDK_GDO_TYPE_ALBUM, this->GetType() );
			}

			/**
			 *  Flag indicating if match is contributor
			 *  @return True if result is a contributor, false otherwise
			 */
			bool
			IsContributor() const
			{
				return 0 == gnstd::gn_strcmp(GNSDK_GDO_TYPE_CONTRIBUTOR, this->GetType() );
			}

			/**
			 *  If album, get match as album object
			 *  @return Album
			 */
			GnAlbum
			GetAsAlbum() const
			{
				if (IsAlbum() )
				{
					return Reflect<GnAlbum>();
				}
				else
				{
					return GnAlbum();
				}
			}

			/**
			 *  If contributor, get match as contributor object
			 *  @return Contributor
			 */
			GnContributor
			GetAsContributor() const
			{
				if (IsContributor() )
				{
					return Reflect<GnContributor>();
				}
				else
				{
					return GnContributor();
				}
			}

		};  // GnDataMatch

		/**
		 * Collection of data match results received in response to a data match query.
		 */
		class GnResponseDataMatches : public GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Constructs empty GnResponseDataMatches object
			 */
			GnResponseDataMatches() { }

			/**
			 * Constructs a GnResponseDataMatches object from a native handle
			 * @param gdoHandle		[in] Native handle
			 */
			GnResponseDataMatches(gnsdk_gdo_handle_t gdoHandle) : GnDataObject(gdoHandle) { }

			virtual
			~GnResponseDataMatches() { }


			/**
			 *  Result count - number of matches returned
			 *  @return Count
			 */
			gnsdk_uint32_t
			ResultCount() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RESULT_COUNT);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Range start - ordinal value of first match in range total
			 *  @return Range start
			 */
			gnsdk_uint32_t
			RangeStart() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_START);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Range end - ordinal value of last match in range total
			 *  @return Range end
			 */
			gnsdk_uint32_t
			RangeEnd() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_END);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Range total - total number of matches that could be returned
			 *  @return Range total
			 */
			gnsdk_uint32_t
			RangeTotal() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_RANGE_TOTAL);

				return gnstd::gn_atoi(return_value);
			}

			/**
			 *  Flag indicating if response needs user or app decision - either multiple matches returned or less than perfect single match
			 *  @return True is user decision needed, false otherwise
			 */
			bool
			NeedsDecision() const
			{
				gnsdk_cstr_t return_value = StringValue(GNSDK_GDO_VALUE_RESPONSE_NEEDS_DECISION);
				return gnstd::gn_strtobool(return_value);
			}

			/**
			 * Iterator for accessing response match(es).
			 * @return Iterator
			 */
			datamatch_iterable
			DataMatches() const
			{
				return datamatch_iterable(gn_gdo_provider<GnDataMatch> (*this, GNSDK_GDO_CHILD_MATCH), GN_GDO_START);
			}

		};  // GnResponseDataMatches


	} /* namespace metadata */
}     /* namespace gracenote */
#endif /* _GNSDK_METADATA_MUSIC_HPP_ */

