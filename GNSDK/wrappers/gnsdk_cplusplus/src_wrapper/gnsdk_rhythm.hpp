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
*  @file gnsdk_rhythm.hpp
*/

#ifndef _GNSDK_RHYTHM_HPP_
#define _GNSDK_RHYTHM_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"
#include "metadata_music.hpp"

/** 
* \namespace gracenote
*/
namespace gracenote
{
	/** 
	* \namespace rhythm
	*/
	namespace rhythm
	{
#if GNSDK_RHYTHM
		/**
		* 
		* Used with the GnRhythmStation::Event method to influence to contents of Rhythm Playlists
		*/
		enum GnRhythmEvent
		{
			/** @internal GNSDK_RHYTHM_EVENT_TRACK_PLAYED @endinternal
			*
			*  Indicate that the track should be marked as played. 
			*  Moves the play queue (drops track being played and adds additional track to end of queue)
			* @ingroup Music_Rhythm_TypesEnums
			*/
			kRhythmEventTrackPlayed = 1,

			/** @internal GNSDK_RHYTHM_EVENT_TRACK_SKIPPED @endinternal
			*
			*  Indicate that the track should be marked as skipped. 
			*  Moves the play queue (drops track being played and adds additional track to end of queue)
			* @ingroup Music_Rhythm_TypesEnums
			*/
			kRhythmEventTrackSkipped,

			/** @internal GNSDK_RHYTHM_EVENT_TRACK_LIKE @endinternal
			*
			*  Indicate that the track should be marked as liked
			*  Does not move the playlist queue.
			* @ingroup Music_Rhythm_TypesEnums
			*/
			kRhythmEventTrackLike,

			/** @internal GNSDK_RHYTHM_EVENT_TRACK_DISLIKE @endinternal
			*
			*  Indicate that the track should be marked as disliked
			*  Refreshes the playlist queue.
			* @ingroup Music_Rhythm_TypesEnums
			*/
			kRhythmEventTrackDislike,

			/** @internal GNSDK_RHYTHM_EVENT_ARTIST_LIKE @endinternal
			*
			*  Indicate that the artist should be marked as like
			*  Does not move the playlist queue.
			* @ingroup Music_Rhythm_TypesEnums
			*/
			kRhythmEventArtistLike,

			/** @internal GNSDK_RHYTHM_EVENT_ARTIST_DISLIKE @endinternal
			*
			*  Indicate that the artist should be marked as disliked
			*  Refreshes the playlist queue.
			* @ingroup Music_Rhythm_TypesEnums
			*/
			kRhythmEventArtistDislike
		};

		/**
		 * \class GnRhythm
		 * Gracenote Rhythm provide a suite of Adaptive Radio and Recommendation features.
		 *
		 * Key features of Gracenote Rhythm:
		 *    - Creates highly-relevant and personalized adaptive radio experiences and recommendations for end-users
		 *    - Delivers radio stations or playlists from seed artist(s) and track(s)
		 *    - Radio stations respond to user's likes and dislikes and includes support for DMCA (Digital Millennium Copyright Act) sequencing rulesPerforms bulk audio track recognition
		 */

		class GnRhythm : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Retrieves the Rhythm library's version string.
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting instance of GnManager successfully.
			 *  The returned string is a constant. Do not attempt to modify or delete.
			 *
			 *  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build)
			 *
			 *  Major: New functionality
			 *  Minor: New or changed features
			 *  Improvement: Improvements and fixes
			 *  Build: Internal build number
			 */
			static gnsdk_cstr_t
			Version();

			/**
			 *  Retrieves the Rhythm library's build date string.
			 *  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting instance of GnManager successfully.
			 *  The returned string is a constant. Do not attempt to modify or delete.
			 *
			 *  Example build date string: 2008-02-12 00:41 UTC
			 */
			static gnsdk_cstr_t
			BuildDate();
		};

		class GnRhythmQuery;
		class GnRhythmStation;

		/**
		 * \class GnRhythmQueryOptions
		 * Configures options for GnRhythmQuery
		 */
		class GnRhythmQueryOptions
		{
		friend class GnRhythmQuery;
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Sets the lookup data value for the MusicID-File query.
			 *  @param lookupData   [in] Set One of the GnLookupData values
			 *  @param bEnable      [in] True or false to enable or disable
			 */
			void
			LookupData(GnLookupData lookupData, bool bEnable) throw (GnError);

			/**
			 *  Specifies how many tracks to return in the playlist response to this query.
			 *  @param count        [in] The number of tracks to return. 
			 *  <p><b>Remarks:</b></p>
			 *  The range for this option is 1..25, The default value is 5.
			 */
			void
			ReturnCount(gnsdk_uint32_t count) throw (GnError);

			/**
			 *  Tuning Parameter to influence how Rhythm uses popularity to affect how the radio station playlist is generated.
			 *  @param amount	[in] new popularity focus setting.
			 *  <p><b>Remarks:</b></p>
			 *  The range for this option is 0..1000, The default value is 1000.
			 */
			void
			FocusPopularity(gnsdk_uint32_t amount) throw (GnError);

			/**
			 *  Tuning Parameter to influence how Rhythm uses similarity to affect how the radio station playlist is generated.
			 *  @param amount	[in] new similarity focus setting.
			 *  <p><b>Remarks:</b></p>
			 *  The range for this option is 0..1000, The default value is 1000.
			 */
			void
			FocusSimilarity(gnsdk_uint32_t amount) throw (GnError);

			/** 
			 *  Specifies a maximum number of tracks per artist for recommended playlist results. 
			 *  @param count 	[in] Maximum number of tracks per artist. 
			 *  <p><b>Remarks:</b></p>
			 *  This option is only applicable to Recommendations generated by GnRhythmQuery
			 *  The range for this option is 1..1000.
			 * @ingroup Music_Rhythm_TypesEnums
			 */
			void
			RecommendationMaxTracksPerArtist(gnsdk_uint32_t count) throw (GnError);

			/** 
			 *  Enabling this option will cause results to be sequenced in a radio-like fashion, otherwise results will be without sequencing. 
			 *  @param bEnable 	[in] True or false to enable or disable
			 *  <p><b>Remarks:</b></p>
			 *  This option is only applicable to Recommendations generated by GnRhythmQuery
			 *  To enable Radio sequencing, define this option key with a True value.
			 *  Without this option Rhythm might return you 5 Britney Spears tracks.
			 *  With this option enabled Rhtyhm would never do that, it would mix it up more, like a radio station.
			 * @ingroup Music_Rhythm_TypesEnums
			 */
			void
			RecommendationRotationRadio(bool bEnable) throw (GnError);

			/** 
			 *  When creating a radio station, you have the option to enable DMCA rules, which reduce the repetition of songs and albums in conformance with DMCA guidelines. By default, DMCA is not enabled.  
			 *  @param bEnable 	[in] True or false to enable or disable
			 *  <p><b>Remarks:</b></p>
			 *  This option cannot be changed after the radio station has been created
			 * @ingroup Music_Rhythm_TypesEnums
			 */
			void
			StationDMCA(bool bEnable) throw (GnError);

			/**
			 * This option allows setting of a specific network interface to be used with connections made by  
			 * this object. Choosing which interface to use can be beneficial for systems with multiple 
			 * network interfaces. Without setting this option, connections will be made of the default network interface
			 * as decided by the operating system.
			 *  @param ipAddress [in] local IP address for the desired network interface
			 */
			void
			NetworkInterface(gnsdk_cstr_t ipAddress) throw (GnError);

			/**
			 *  Set option using option name
			 *  @param option   [in] Option name
			 *  @param bEnable	[in] True or false to enable or disable
			 */
			void
			Custom(gnsdk_cstr_t option, bool bEnable) throw (GnError);

			/**
			 *  Set option using option name
			 *  @param option   [in] Option name
			 *  @param value	[in] Option value, as unsigned integer
			 */
			void
			Custom(gnsdk_cstr_t option, gnsdk_uint32_t value) throw (GnError);

			/**
			 *  Set option using option name
			 *  @param option   [in] Option name
			 *  @param value	[in] Option value
			 */
			virtual void
			Custom(gnsdk_cstr_t option, gnsdk_cstr_t value) throw (GnError);

		protected:
			GnRhythmQueryOptions() : weakhandle_(GNSDK_NULL) {}
			virtual ~GnRhythmQueryOptions() {}

		private:
			DISALLOW_COPY_AND_ASSIGN(GnRhythmQueryOptions);

			gnsdk_rhythm_query_handle_t weakhandle_;
		};

		/**
		 * \class GnRhythmQuery
		 * Provides services for generating Rhythm Recommendations
		 */
		class GnRhythmQuery : public GnRhythm
		{
		friend class GnRhythmStation;

		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Constructs a Rhythm query object with a Gracenote user and event delegate
			 *  @param user          [in] Set GnUser object representing the user making the GnMusicId request
			 *  @param pEventHandler [in-opt] Set Optional status event handler to get bytes sent, received, or completed.
			 */
			GnRhythmQuery(GnUser const& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

			/**
			 *  Adds a Seed to the GnRhythmQuery object.
			 *  @param seed			[in] GnDataObject to be used as seed, can be a GnTrack, GnAlbum, or GnArtist object
			 */
			void
			AddSeed(metadata::GnDataObject const& seed) throw (GnError);

			/** 
			 *  Generates a set of recommendations based on seeds set into the query handle.
			 *  @return An instance of GnResponseAlbums, response contains one Album per Recommended Track. 
			 *  <p><b>Remarks:</b></p>
			 *  The Matched Track on each Album in the GnResponseAlbums is the Recommended Track
			 */
			metadata::GnResponseAlbums
			GenerateRecommendations() throw (GnError);

			/**
			 * Get the event handler provided on construction
			 * @return Event handler
			 */
			IGnStatusEvents*
			EventHandler() 
			{ 
				return eventhandler_;
			}

			/**
			 * Get GnRhythmQuery options object. Use to configure your GnRhythmQuery instance.
			 * @return Options object
			 */
			GnRhythmQueryOptions&
			Options() 
			{ 
				return options_; 
			}

			/**
			 * Set cancel state
			 * @param bCancel 	[in] Cancel state
			 */
			virtual void
			SetCancel(bool bCancel)
			{
				cancelled_ = bCancel;
			}

			/**
			 * Get cancel state.
			 * @return Cancel state
			 */
			virtual bool
			IsCancelled()
			{
				return cancelled_;
			}

		private:
			gnsdk_rhythm_station_handle_t
			GenerateStation(GnRhythmStation* p_rhythmStation);

			bool					cancelled_;
			IGnStatusEvents*		eventhandler_;
			GnRhythmQueryOptions 	options_;

			DISALLOW_COPY_AND_ASSIGN(GnRhythmQuery);
		};


		/**
		 * Configures options for GnRhythmStation
		 */
		class GnRhythmStationOptions : public GnRhythmQueryOptions
		{
		friend class GnRhythmStation;
		public:
			GNWRAPPER_ANNOTATE

			virtual void
			Custom(gnsdk_cstr_t option, gnsdk_cstr_t value) throw (GnError);

		protected:
			GnRhythmStationOptions() : weakhandle_(GNSDK_NULL) {}

		private:
			gnsdk_rhythm_station_handle_t weakhandle_;

			/**
			 * Not applicable to GnRhythmStation
			 */
			void
			RecommendationMaxTracksPerArtist(gnsdk_uint32_t count) throw (GnError);

			/**
			 * Not applicable to GnRhythmStation
			 */
			void
			RecommendationRotationRadio(bool bEnable) throw (GnError);

			/**
			 * Can't be changed after station creation.
			 * Must be set on the GnRhythmQuery object which is used to create the GnRhythmStation
			 */
			void
			StationDMCA(bool bEnable) throw (GnError);

			DISALLOW_COPY_AND_ASSIGN(GnRhythmStationOptions);
		};

		/**
		 * \class GnRhythmStation
		 * Provides services for interacting with Rhythm Stations
		 */
		class GnRhythmStation : public GnRhythm
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Constructs a Rhythm Station object from a GnRhythmQuery object and event delegate
			 *  @param rhythmQuery   [in] GnRhythmQuery object containing the seeds and options to generate a new Rhythm Station.
			 *  @param pEventHandler [in-opt] Set Optional status event handler to get bytes sent, received, or completed.
			 */
			GnRhythmStation(GnRhythmQuery& rhythmQuery, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

			/**
			 *  Constructs a Rhythm Station object from an existing Rhythm Station ID, with a Gracenote user and event delegate
			 *  @param station_id    [in] An Rhythm Station ID which will be used to retrieve a pre-existing Rhythm Station.
			 *  @param user          [in] Set GnUser object representing the user making the GnMusicId request.
			 *  @param pEventHandler [in-opt] Set Optional status event handler to get bytes sent, received, or completed.
			 */
			GnRhythmStation(gnsdk_cstr_t station_id, GnUser const& user, IGnStatusEvents* pEventHandler = GNSDK_NULL) throw (GnError);

			/**
			 *  Retrieves the station ID
			 *   @return A C String contaning the Rhythm Station's ID.
			 *  <p><b>Remarks:</b></p>
			 *  The returned string is a constant. Do not attempt to modify or delete.
			 */
			gnsdk_cstr_t
			StationId() throw (GnError);

			/**
			 *  Generate a Rhythm Station Playlist.
			 *  @return An instance of GnResponseAlbums, response contains one Album per Recommended Track. 
			 *  <p><b>Remarks:</b></p>
			 *  The Matched Track on each Album in the GnResponseAlbums is the Recommended Track
			 */
			metadata::GnResponseAlbums
			GeneratePlaylist() throw (GnError);

			/**
			 *  Adds an event to a Rhythm station.
			 *   @param event        [in] One of the predefined Rhythm event types
			 *   @param gnObj        [in] A GnDataObject representing the context of the event
			 */
			void
			Event(GnRhythmEvent event, metadata::GnDataObject const& gnObj) throw (GnError);

			/**
			 * Get the event handler provided on construction
			 * @return Event handler
			 */
			IGnStatusEvents*
			EventHandler() 
			{ 
				return eventhandler_;
			}

			/**
			 * Get GnRhythmQuery options object. Use to configure your GnRhythmQuery instance.
			 * @return Options object
			 */
			GnRhythmQueryOptions&
			Options() 
			{ 
				return options_; 
			}

			/**
			 * Set cancel state
			 * @param bCancel 	[in] Cancel state
			 */
			virtual void
			SetCancel(bool bCancel)
			{
				cancelled_ = bCancel;
			}

			/**
			 * Get cancel state.
			 * @return Cancel state
			 */
			virtual bool
			IsCancelled()
			{
				return cancelled_;
			}

		private:
			bool					cancelled_;
			IGnStatusEvents*		eventhandler_;
			GnRhythmStationOptions 	options_;

			DISALLOW_COPY_AND_ASSIGN(GnRhythmStation);
		};

#endif /* GNSDK_RHYTHM */

	} /* namespace rhythm */

}     /* namespace gracenote */

#endif /* _GNSDK_RHYTHM_HPP_ */

