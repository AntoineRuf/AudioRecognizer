/*
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_PLAYLIST_HPP_
#define _GNSDK_PLAYLIST_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"
#include "gnsdk_list.hpp"
#include "metadata_music.hpp"


namespace gracenote
{
	namespace playlist
	{
#if GNSDK_PLAYLIST

		class IGnPlaylistCollectionSyncEvents;
		class GnPlaylistCollectionOptions;
		class GnPlaylistCollection;
		class GnPlaylistResult;

		/**
		 * <b>Experimental</b>: GnPlaylistIdentifier
		 */
		class GnPlaylistIdentifier
		{
		public:
			GNWRAPPER_ANNOTATE
			/* Constructors */
			GnPlaylistIdentifier() : ident_(GNSDK_NULL), collection_(GNSDK_NULL) { }


			/*-----------------------------------------------------------------------------
			 *  MediaIdentifier
			 */
			gnsdk_cstr_t
			MediaIdentifier() const
			{
				return ident_;
			}

			/*-----------------------------------------------------------------------------
			 *  CollectionName
			 */
			gnsdk_cstr_t
			CollectionName() const
			{
				return collection_;
			}

			/*-----------------------------------------------------------------------------
			 *  operator ==
			 */
			bool
			operator == (const GnPlaylistIdentifier& rhs) const
			{
				return ( ident_ == rhs.ident_ ) && ( collection_ == rhs.collection_ );
			}

		protected:
			GnPlaylistIdentifier(gnsdk_cstr_t media_identifier, gnsdk_cstr_t collection_name) : ident_(media_identifier), collection_(collection_name) { }
			friend class result_provider;
			friend class collection_ident_provider;
			friend class IGnPlaylistCollectionSyncEvents;


		private:
			gnsdk_cstr_t ident_;
			gnsdk_cstr_t collection_;
		};


		/**
		 * <b>Experimental</b>: GnPlaylistAttributes
		 */
		class GnPlaylistAttributes : public metadata::GnDataObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnPlaylistAttributes() { }
			GnPlaylistAttributes(gnsdk_gdo_handle_t gdo_handle) :     metadata::GnDataObject(gdo_handle) { }
			GnPlaylistAttributes(const GnPlaylistAttributes& other) : metadata::GnDataObject(other) { }

			virtual
			~GnPlaylistAttributes() { }

			/**
			 *  Retrieves the AlbumName value as a string for this attribute .
			 *  @return album name string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			AlbumName() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_ALBUM);
			}

			/**
			 *  Retrieves the ArtistName value as a string for this attribute .
			 *  @return artist name string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			ArtistName() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_ARTIST);
			}

			/**
			 *  Retrieves the ArtistType value as a string for this attribute .
			 *  @return artist type string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			ArtistType() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_ARTTYPE);
			}

			/**
			 *  Retrieves the Era value as a string for this attribute .
			 *  @return era string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			Era() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_ERA);
			}

			/**
			 *  Retrieves the Genre value as a string for this attribute .
			 *  @return genre string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			Genre() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_GENRE);
			}

			/**
			 *  Retrieves the Origin value as a string for this attribute .
			 *  @return origin string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			Origin() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_ORIGIN);
			}

			/**
			 *  Retrieves the Mood value as a string for this attribute .
			 *  @return mood string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			Mood() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_MOOD);
			}

			/**
			 *  Retrieves the Tempo value as a string for this attribute .
			 *  @return tempo string value if it exists else an empty string.
			 *
			 **/
			gnsdk_cstr_t
			Tempo() const
			{
				return StringValue(GNSDK_PLAYLIST_ATTRIBUTE_NAME_TEMPO);
			}

		};


		/*---------------------------------------------------------------------------
		** internal result_provider
		*/
		class result_provider
		{
		public:
			result_provider() : weak_handle_(GNSDK_NULL) { }
			result_provider(gnsdk_playlist_results_handle_t results) : weak_handle_(results) { }
			~result_provider() { }

			/* Required. */
			GnPlaylistIdentifier
			get_data(gnsdk_uint32_t pos) const;

			/* optional */
			gnsdk_uint32_t
			count() const;


		private:
			gnsdk_playlist_results_handle_t weak_handle_;
		};


		/*---------------------------------------------------------------------------
		** internal collection_ident_provider class
		*/
		class collection_ident_provider
		{
		public:
			collection_ident_provider() : weak_handle_(GNSDK_NULL) { }
			collection_ident_provider(gnsdk_playlist_collection_handle_t coll_handle) : weak_handle_(coll_handle) { }

			GnPlaylistIdentifier
			get_data(gnsdk_uint32_t pos) const;

			gnsdk_uint32_t
			count() const;


		private:
			gnsdk_playlist_collection_handle_t weak_handle_;
		};


		/*---------------------------------------------------------------------------
		** internal collection_join_provider
		*/
		class collection_join_provider
		{
		public:
			collection_join_provider() : weak_handle_(GNSDK_NULL) { }
			collection_join_provider(gnsdk_playlist_collection_handle_t coll_handle) : weak_handle_(coll_handle) { }

			GnPlaylistCollection
			get_data(gnsdk_uint32_t pos) const;

			gnsdk_uint32_t
			count() const;


		private:
			gnsdk_playlist_collection_handle_t weak_handle_;
		};


		/*---------------------------------------------------------------------------
		** Internal : collection_storage_provider
		*/
		class collection_storage_provider
		{
		public:
			collection_storage_provider();
			~collection_storage_provider();
			collection_storage_provider(const collection_storage_provider&);

			collection_storage_provider&
			operator = (const collection_storage_provider& copy);

			/* Default method required . */
			gnsdk_cstr_t
			get_data(gnsdk_uint32_t pos);

			gnsdk_uint32_t
			count() const;


		private:
			gnsdk_char_t* buffer_;
		};


		/*---------------------------------------------------------------------------
		** Internal : attribute_provider
		*/
		class attribute_provider
		{
		public:
			attribute_provider() : weak_handle_(GNSDK_NULL) { };
			attribute_provider(gnsdk_playlist_collection_handle_t coll_handle) : weak_handle_(coll_handle) { }

			~attribute_provider() { };

			/* Default method required . */
			gnsdk_cstr_t
			get_data(gnsdk_uint32_t pos) const;

			/*required */
			gnsdk_uint32_t
			count() const;


		private:
			gnsdk_playlist_collection_handle_t weak_handle_;
		};


		typedef gn_facade_range_iterator<GnPlaylistIdentifier, collection_ident_provider>   ident_iterator;
		typedef gn_facade_range_iterator<GnPlaylistCollection, collection_join_provider>    join_iterator;
		typedef gn_facade_range_iterator<gnsdk_cstr_t, collection_storage_provider>         storage_iterator;
		typedef gn_facade_range_iterator<GnPlaylistIdentifier, result_provider>             result_iterator;
		typedef gn_facade_range_iterator<gnsdk_cstr_t, attribute_provider>                  attribute_iterator;

		typedef gn_iterable_container<GnPlaylistIdentifier, collection_ident_provider>   ident_iterable;
		typedef gn_iterable_container<GnPlaylistCollection, collection_join_provider>    join_iterable;
		typedef gn_iterable_container<gnsdk_cstr_t, collection_storage_provider>         storage_iterable;
		typedef gn_iterable_container<GnPlaylistIdentifier, result_provider>             result_iterable;
		typedef gn_iterable_container<gnsdk_cstr_t, attribute_provider>                  attribute_iterable;

		/**
		 * <b>Experimental</b>: GnPlaylistResult
		 */
		class GnPlaylistResult : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnPlaylistResult() { }
			explicit
			GnPlaylistResult(gnsdk_playlist_results_handle_t handle) : GnObject(handle)  { }

			/*-----------------------------------------------------------------------------
			 *  Identifiers
			 */
			result_iterable
			Identifiers() const
			{
				return result_iterable(result_provider(get<gnsdk_playlist_results_handle_t>()), GN_BASE_START);
			}

		};


		/**
		 * <b>Experimental</b>: Playlist "more like this" options.
		 */
		class GnPlaylistMoreLikeThisOptions
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Retrieves an option for Maximum number of Tracks for MoreLikeThis queries on a given collection.
			 *  Please note that these options are not serialized or stored.
			 *  Option for querying/specifying the maximum number of tracks in the result to be returned.
			 *  0 is not a valid value
			 *  @return Maximum tracks
			 *
			 **/
			gnsdk_uint32_t
			MaxTracks() const throw (GnError);

			/**
			 * Sets an option for Maximum number of Tracks for MoreLikeThis queries on a given collection.
			 * Please note that these options are not serialized or stored.
			 * @param  value [in] The maximum number of tracks to be returned. 0 is not a valid value.
			 **/
			void
			MaxTracks(gnsdk_uint32_t value) throw (GnError);
			/**
			 * Retrieves an option for maximum number of tracks Per artist  for MoreLikeThis queries on a given collection.
			 * Please note that these options are not serialized or stored.
			 * 0 is not a valid value
			 * @return Maximum tracks per artist
			 *
			 **/
			gnsdk_uint32_t
			MaxPerArtist() const throw (GnError);

			/**
			 * Sets an option for maximum number of tracks per artist for MoreLikeThis queries on a given collection.
			 * Please note that these options are not serialized or stored.
			 * @param  value [in] The maximum number of tracks per artist to be returned. 0 is not a valid value.
			 *
			 **/
			void
			MaxPerArtist(gnsdk_uint32_t value) throw (GnError);

			/**
			 * Retrieves an option for maximum number of tracks per album for MoreLikeThis queries on a given collection.
			 * Please note that these options are not serialized or stored.
			 * 0 is not a valid value
			 * @return Maximum tracks per album
			 *
			 **/
			gnsdk_uint32_t
			MaxPerAlbum() const throw (GnError);

			/**
			 * Sets an option for maximum number of tracks per album for MoreLikeThis queries on a given collection.
			 * Please note that these options are not serialized or stored.
			 * @param  value    [in] The maximum number of tracks per album to be returned. 0 is not a valid value.
			 **/
			void
			MaxPerAlbum(gnsdk_uint32_t value) throw (GnError);


			/**
			 * Retrieves the RandomSeed option for "More Like This" for a given collection.
			 * Please note that these options are not serialized or stored.
			 * Option for querying/specifying the seed value for the random number generator used in calculating a
			 * "More Like This" playlist.
			 * @return Seed value
			 */
			gnsdk_uint32_t
			RandomSeed() const throw (GnError);

			/**
			 * Sets the RandomSeed option for "More Like This" for a given collection.
			 * Please note that these options are not serialized or stored.
			 * Option for querying/specifying the seed value for the random number generator used in calculating a
			 * "More Like This" playlist. Using the same number for a seed will generate the same 'random' sequence, thus allowing
			 * the same playlist ordering to be recreated. Choosing different numbers will create different playlists. Setting
			 * this value to "0" will disable using a random seed.
			 * @param value		[in] An unsigned int random seed .
			 */
			void
			RandomSeed(gnsdk_uint32_t value) throw (GnError);


		protected:
			GnPlaylistMoreLikeThisOptions() : weakhandle_(GNSDK_NULL) { }


		private:
			DISALLOW_COPY_AND_ASSIGN(GnPlaylistMoreLikeThisOptions);
			friend class GnPlaylistCollection;
			gnsdk_playlist_collection_handle_t weakhandle_;
		};


		/**
		 * <b>Experimental</b>: Playlist Collection Summary that represents
		 * the media in a user's collection and can be used to generate
		 * playlists from that media. A Collection Summary is not intended to be
		 * used as a general database of the user's media collection.
		 *
		 * <b>Creating a Collection Summary</b>
		 *
		 * GNSDK supports multiple user collections and therefore multiple Collection
		 * Summaries. Each Collection Summary is identified by a unique name. To
		 * create a new Collection Summary instantiate a GnPlaylistCollection object
		 * with a unique name.
		 *
		 * <b>Adding User Media</b>
		 *
		 * To generate a playlist from user media your application must first
		 * identify the user's media using Gracenote services (such as MusicID-File)
		 * and then create a Playlist Collection Summary with the recognized media.
		 *
		 * In a simple example your application can use GnMusicIdFile Library ID
		 * functionality to identify audio tracks. The GnMusicIdFile result provides
		 * to GnAlbum objects containg GnTrack objects that map back to the original
		 * audio track; your application can add the GnTrack object <b>and</b> the
		 * GnAlbum object to the Playlist Collection Summary with a unique identifyer
		 * for the audio track.
		 *
		 * Note: When identifying media intended for inclusion in a Playlist Collection
		 * Summary you must specify that the result inlcude lookup data kLookupDataPlaylist
		 * and kLookupDataSonicData.
		 *
		 * In some cases an audio track may not contain enough information to match it
		 * with a single GnTrack object, in such caes you application can use the
		 * available information to add it to the Collection Summary. For example if only
		 * album title or artist name information is available GnMusicId could be used to
		 * match a GnAlbum or GnContributor object which can then be added. Similarly
		 * if only genre information is available the Lists's subsystem could be used to
		 * match a GnListElement object which can then be added.
		 *
		 * <b>Generating Playlists</b>
		 *
		 * Using a GnPlaylistCollection object your application can generate "More Like
		 * This" playlist or where more control is required a playlist specific via
		 * Playlist Definition Langauge (PDL).
		 *
		 * A MTL (More Like This) playlist can be generated from a seed, which can be any
		 * Gracenote data object. For example you may use GnMusicId to perform a text
		 * search for a specific track and receive a GnAlbum object. Your application
		 * can provide the GnAlbum object as the seed. Note: do not use the GnTrack
		 * object as the seed, Playlist will use the "matched" GnTrack object to determine
		 * which track on the album to use.
		 *
		 * For advanced playlist definition your application can define Playlist Definition
		 * Language (PDL) Statements. For more information on creating a PDL Statements consult 
		 * the PDL Specification.
		 *
		 * <b>Synchronizing User's Media Collection</b>
		 *
		 * A user's media collection will change over time. To ensure generated playlists
		 * include new media items and don't include removed media items your application must
		 * synchronize the user's collection with their Collection Summary.
		 *
		 * Synchronization is a two step process. Step one requires your application to use
		 * SyncProcessAdd to add <b>all</b> unique media identifiers that currently exist in the user's
		 * collection. Sep two is to process those identifers by calling SyncProcessExecute.
		 *
		 * During execution GNSDK reconciles the identifiers within the Collection Summary
		 * with those added for sychronization. It can determine which identifiers are new, meaning
		 * they are were added to the user's collection and need to be added to the Collection
		 * Summary; and those that are old, meaning they were removed from the user's collection
		 * and need to be removed from the Collection Summary.
		 *
		 * <b>Joining Collections</b>
		 *
		 * Multiple collection summaries can be joined allowing playlists to be generated that contain
		 * tracks from multiple collections.
		 *
		 * <b>Storing Persistently</b>
		 *
		 * Playlist Collection Summaries are stored entirely in heap memory. To avoid
		 * re-creating them every time your application starts you should store them
		 * persistently.
		 *
		 * Gracenote recommends using managed persistent storage services provided by
		 * GnPlaylistStorage.
		 *
		 * Alternatively a Collection Summary can be serialized into a string that your
		 * application can store persistently and later use to reconstitute a Collection
		 * Summary in memory.
		 *
		 */
		class GnPlaylistCollection : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 * Default Constructor for GnPlaylistCollection
			 */
			 GnPlaylistCollection() {;}

			/**
			 * Constructor for GnPlaylistCollection using a C native playlist collection handle.
			 * Caution For advanced users only: Please note that the native handle will be addref'd when consumed by this class and it is up to
			 * the user to ensure that native handle is properly released ( depending on which C API gave access to the handle).
			 * @param handle   The gnsdk_playlist_collection_handle_t handle
			 */
			explicit
			GnPlaylistCollection(gnsdk_playlist_collection_handle_t handle);

			/**
			 * Constructor for GnPlaylistCollection using char* string name. This creates the collection with the name that is passed in.
			 * @param name   The name to be used to construct the colleciton.
			 */
			explicit
			GnPlaylistCollection(gnsdk_cstr_t name);

			/**
			 * Constructor for GnPlaylistCollection using a buffer to deserialize it from  and the corresponding buffer size .
			 * This created the collection from the buffer that is passed in if it is successfully deserialized.
			 * @param collData  [in] buffer that contains the serialized buffer.
			 * @param dataSize	[in] buffer size .
			 */
			GnPlaylistCollection(gnsdk_byte_t* collData, gnsdk_size_t dataSize);

			/**
			 * Copy Constructor for GnPlaylistCollection.
			 * @param other  [in] reference to GnPlaylistCollection that is to be copied.
			 */
			GnPlaylistCollection(const GnPlaylistCollection& other);

			/**
			 * Assignment operator for GnPlaylistCollection.
			 * @param other  [in] reference to GnPlaylistCollection that is assigned to this GnPlaylistCollection .
			 */
			GnPlaylistCollection&
			operator =(const GnPlaylistCollection& other);

			/**
			 * Get the collection name
			 * @return Name
			 */
			gnsdk_cstr_t
			Name() const throw (GnError);

			/**
			 * Change the collection name
			 * @param updatedName	New collection name
			 */
			void
			Name(gnsdk_cstr_t updatedName) throw (GnError);

			/**
			 * Add a identifier with no metadata to a Collection Summary
			 *
			 * @param mediaIdentifier   [in] Media identifier
			 */
			void
			Add(gnsdk_cstr_t mediaIdentifier) throw (GnError);

			/**
			 * Add a GnAlbum object and its metadata to a Collection Summary.
			 *
			 * @param mediaIdentifier   [in] Media identifier
			 * @param album             [in] GnAlbum object
			 */
			void
			Add(gnsdk_cstr_t mediaIdentifier, const metadata::GnAlbum& album) throw (GnError);

			/**
			 * Add a GnTrack object and its metadata to a Collection Summary
			 *
			 * @param mediaIdentifier   [in] Media identifier
			 * @param track             [in] GnTrack object
			 */
			void
			Add(gnsdk_cstr_t mediaIdentifier, const metadata::GnTrack& track) throw (GnError);

			/**
			 * Add a GnContributor object and its metadata to a Collection Summary
			 *
			 * @param mediaIdentifier   [in] Media identifier
			 * @param contributor       [in] GnContributor object
			 */
			void
			Add(gnsdk_cstr_t mediaIdentifier, const metadata::GnContributor& contributor) throw (GnError);


			/**
			 * Add a GnPlaylistAttributes object to a Collection Summary.
			 *
			 * @param mediaIdentifier       [in] Media identifier
			 * @param playlistAttributes	[in] Playlist attributes
			 */
			void
			Add(gnsdk_cstr_t mediaIdentifier, const GnPlaylistAttributes& playlistAttributes) throw (GnError);

			/**
			 * Add a GnListElement object to a Collection Summary.
			 *
			 * @param mediaIdentifier   [in] Media identifier
			 * @param listElement       [in] GnListElement object
			 */
			void
			Add(gnsdk_cstr_t mediaIdentifier, const GnListElement& listElement) throw (GnError);

			/**
			 * Remove a media element from a Collection Summary.
			 *
			 * @param mediaIdentifier  [in] Media identifier
			 */
			void
			Remove(gnsdk_cstr_t mediaIdentifier) throw (GnError);

			/* TBD */
			/* void Remove(iterator begin, iterator end) {} */

			/**
			 * Test if a media element is in a Collection Summary.
			 *
			 * @param mediaIdentifier  [in] Media identifier
			 */
			bool
			Contains(gnsdk_cstr_t mediaIdentifier) const throw (GnError);

			/**
			 * Find a media element in a Collection Summary.
			 *
			 * @param mediaIdentifier   [in] Media identifier
			 * @param start				[in] Start ordinal
			 */
			ident_iterator
			Find(gnsdk_cstr_t mediaIdentifier, gnsdk_uint32_t start) const throw (GnError);

			/**
			 * Return metadata from a playlist using a playlist identifier
			 *
			 * @param user             [in] Gracenote user
			 * @param mediaIdentifier  [in] Playlist identifier
			 */
			GnPlaylistAttributes
			Attributes(const GnUser& user, const GnPlaylistIdentifier& mediaIdentifier) const throw (GnError);

			/**
			 * Return attributes from a playlist using a Collection Summary name
			 *
			 * @param user             [in] GN User object
			 * @param mediaIdentifier  [in] Playlist identifier
			 */
			GnPlaylistAttributes
			Attributes(const GnUser& user, gnsdk_cstr_t mediaIdentifier, gnsdk_cstr_t joinedCollectionName) const throw (GnError);

			/**
			 * Validate a Playlist Definitioon Statement
			 * @param pdlStatement	Playlist Definition Statment
			 * @return Validation result
			 */
			GnError
			StatementValidate(gnsdk_cstr_t pdlStatement);

			/**
			 * Determine if a Playlist Definition Statement requires a seed
			 * to generate a playlist
			 * @param pdlStatement	Playlist Definition Statment
			 * @return True if a seed is required, false otherwise
			 */
			bool
			StatementRequiresSeed(gnsdk_cstr_t pdlStatement) const throw (GnError);

			/**
			 * <b>Experimental</b>. Analyzes the given PDL Statement as applied to the given media identifier.
			 * Used for debugging and analyzing playlist generation with PDL statements this method
			 * analyzes the given PDL as applied to the given media identifier.
			 * The output is a formatted logical tree of the PDL statement and the outcome applied
			 * for each operation.
			 * For more information on creating PDL Statements consult the PDL Specification.
			 * @param pdlStatment		PDL Statment being debugged
			 * @param mediaIdentifier	Unique identifier of a media item within the collection summary
			 */
			GnString
			StatementAnalyzeIdent(gnsdk_cstr_t pdlStatement, gnsdk_cstr_t mediaIdentifier) const throw (GnError);

			/**
			 * Generate a playlist from a GnDataObject
			 *
			 * @param user             [in] Gracenote user
			 * @param pdlStatement     [in] Playlist Description Language statement
			 * @param playlistSeed     [in] GN data object to use as seed for playlist
			 */
			GnPlaylistResult
			GeneratePlaylist(const GnUser& user, gnsdk_cstr_t pdlStatement, const metadata::GnDataObject& playlistSeed) throw (GnError);

			/**
			 * Generate a playlist using a Playlist Definition Language (PDL) Statement from this object's Collection Summary.
			 * For more information on creating PDL Statements consult the PDL Specification.
			 *
			 * @param user             [in] Gracenote user
			 * @param pdlStatement     [in] Playlist Description Language statement
			 *
			 */
			GnPlaylistResult
			GeneratePlaylist(const GnUser& user, gnsdk_cstr_t pdlStatement) throw (GnError);

			/**
			 * Generate a playlist from a GnDataObject
			 *
			 * @param user             [in] Gracenote user
			 * @param musicDataObj     [in] Gracenote data object
			 *
			 */
			GnPlaylistResult
			GenerateMoreLikeThis(const GnUser& user, const metadata::GnDataObject& musicDataObj) throw (GnError);

			/**
			 *  Returns an iterable container for all the playlist attributes supported by this collection.
			 *
			 */
			attribute_iterable
			AttributesSupported() const
			{
				return attribute_iterable(attribute_provider(), GN_BASE_START);
			}

			/**
			 * Returns an iterable container for all the media identifiers in the collection
			 */
			ident_iterable
			MediaIdentifiers() const
			{
				return ident_iterable(collection_ident_provider(get<gnsdk_playlist_collection_handle_t>()), GN_BASE_START);
			}

			/**
			 *  Returns an iterable container for all the joined collections .
			 *
			 */
			join_iterable
			Joins() const
			{
				return join_iterable(collection_join_provider(get<gnsdk_playlist_collection_handle_t>()), GN_BASE_START);
			}

			/**
			 * Join a playlist collection by collection name
			 *
			 * @param collectionName   [in] Collection Summary name
			 */
			GnPlaylistCollection
			JoinFindByName(gnsdk_cstr_t collectionName) const throw (GnError);

			/**
			 * Join a playlist collection by playlist collection object
			 *
			 * @param toJoin   [in] GnPlaylistCollection object for join
			 */
			void
			Join(const GnPlaylistCollection& toJoin) throw (GnError);

			/**
			 * Remove a join with another playlist
			 *
			 * @param toRemove   [in] GnPlaylistCollection object to remove join
			 */
			void
			JoinRemove(const GnPlaylistCollection& toRemove) throw (GnError);

			/**
			 * Serialize a Collection Summary into buffer
			 *
			 * @param serializedData    [out] Buffer to receive serialized data
			 * @param dataSize          [in] Buffer size
			 * @return buffer size
			 */
			gnsdk_size_t
			Serialize(gnsdk_byte_t* serializedData, gnsdk_size_t dataSize) const throw (GnError);

			/**
			 * Returns the size of a serialized playlist collection object
			 * @return serialized buffer size
			 */
			gnsdk_size_t
			SerializeSize() const throw (GnError);

			/**
			 * Add an identifier as part of synchronizing a user's media collection with the
			 * corresponding Collection Summary.
			 *
			 * Collection sychronization is a two step process, step one is to use this method to
			 * add all unique identifiers that currently exist in the user's collection. Step two
			 * is to execute the synchronization process.
			 * @param mediaIdentifier [in] unique media identifier used in you application e.g. file path
			 */
			void
			SyncProcessAdd(gnsdk_cstr_t mediaIdentifier) throw (GnError);

			/**
			 * Process synchronize identifiers previously added to the Collection Summary to complete
			 * synchronizing a user's media collection with the corresponding Collection Summary.
			 *
			 * As step two of the synchronization process call this method after adding all unique
			 * identifiers using SyncProcessAdd. This call will determine which identifiers added for
			 * synchronization need to be also be added to the Collection Summary; and those that need to be
			 * removed from the Collection Summary because they no longer exist in the user's collection.
			 * This information is delivered via the synchronization delegate.
			 * @param syncEvents [in] Synchronizations events delegate
			 */
			void
			SyncProcessExecute(IGnPlaylistCollectionSyncEvents& syncEvents) throw (GnError);

			/**
			 * Get object for setting "more like this" options
			 * @return	More like this options object
			 */
			GnPlaylistMoreLikeThisOptions&
			MoreLikeThisOptions() { return options_; }


		protected:
			/* friend class definition */
			friend class GnPlaylist;
			friend class GnPlaylistStorage;

			GnPlaylistMoreLikeThisOptions options_;
		};


		/**
		 * Specifies the status of a unique identifier when sychronizing
		 * a Playlist Collection Summary with a user's collection.
		 */
		enum GnPlaylistEventsIdentiferStatus
		{
			/**
			 * The corresponding identifier's status is unknown, the default state
			 */
			kIdentifierStatusUnknown = 0,

			/**
			 * The corresponding identifier is new, meaning it has been added to the
			 * user's media collection and needs to be added to the Collection Summary
			 */
			kIdentifierStatusNew     = 10,

			/**
			 * The corresponding identifier is old, meaning it has been deleted from
			 * the user's media collection and needs to be removed from the
			 * Collection Summary
			 */
			kIdentifierStatusOld     = 20

		};

		/**
		 * <b>Experimental</b>: Delegate interface for receiving playlist synchronization events
		 *
		 * Synchronization events are generated when a synchronization process is
		 * executed.
		 */
		class IGnPlaylistCollectionSyncEvents
		{
		public:
			GNWRAPPER_ANNOTATE

			virtual
			~IGnPlaylistCollectionSyncEvents() { }

			/* Methods to Override. */
			virtual void
			OnUpdate(GnPlaylistCollection collection, GnPlaylistIdentifier identifier, GnPlaylistEventsIdentiferStatus status, IGnCancellable& canceller) = 0;


		protected:
			friend class GnPlaylistCollection;
			static void _collection_sync(gnsdk_void_t*, gnsdk_playlist_collection_handle_t, gnsdk_cstr_t, gnsdk_playlist_status_t, gnsdk_bool_t*);
		};


		/**
		 * <b>Experimental</b>: Playlist Collection Summary storage management
		 *
		 * Provides services for managing the Playlist Collection Summary storage including
		 * adding, loading and removing collection summaries from persistent storage.
		 *
		 * Once a Collection Summary is created your application can store it persistently
		 * by adding it to the Playlist Collection Summary storage. When your application
		 * is initialized it can load the Collection Summary into heap memory from storage.
		 *
		 * Note: Once a Collection Summary is loaded from persistent storage your application
		 * should synchronized the summary with the media available for playlist generation as
		 * the user may have added or removed such media while your appication was not active.
		 *
		 * Collection Summaries can be removed from Playlist Collection Summary storage when
		 * no longer needed. The Playlist Collection Summary storage will retain persistent
		 * storage resources (file space) used by the removed Collection Summary. To return
		 * these resources to the operating system your application should compact the
		 * storage soon after removing a Collection Summary.
		 *
		 * A Gracenote storage provider must be enabled, such as GnStorageSqlite, for
		 * GnPlalistStorage to access persistent storage.
		 *
		 */
		class GnPlaylistStorage : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnPlaylistStorage();
			virtual
			~GnPlaylistStorage() { }


			/**
			 * Performs validation on playlist storage.
			 * @return Error information from storage validation
			 * Long Running Potential: File system I/O, database size affects running time
			 */
			GnError
			IsValid() const;


			/**
			 * Compact Collection Summary storage
			 */
			void
			Compact() throw (GnError);


			/**
			 * Stores a Collection Summary in local storage
			 *
			 * @param collection [in] Playlist collection
			 */
			void
			Store(const GnPlaylistCollection& collection) throw (GnError);


			/**
			 * Loads a Collection Summary from local storage using storage iterator
			 *
			 * @param itr [in] Storage iterator at the position you want to load.
			 * @return Playlist collection
			 */
			GnPlaylistCollection
			Load(storage_iterator itr)  throw (GnError);


			/**
			 * Loads a Collection Summary from local storage using storage name
			 *
			 * @param collectionName [in] explicit name of the collection you want to load.
			 * @return Playlist collection
			 */
			GnPlaylistCollection
			Load(gnsdk_cstr_t collectionName) throw (GnError);


			/**
			 * Removes a Collection Summary from local storage
			 *
			 * @param collection [in] Playlist collection object
			 */
			void
			Remove(const GnPlaylistCollection& collection) throw (GnError);


			/**
			 * Removes a Collection Summary from local storage using storage name
			 *
			 * @param collectionName [in] Playlist collection name
			 */
			void
			Remove(gnsdk_cstr_t collectionName) throw (GnError);


			/**
			 * Sets location for Collection Summary storage
			 *
			 * @param location [in] Location path
			 */
			void
			Location(gnsdk_cstr_t location) throw (GnError);


			/**
			 * Get an iterator for names of all stored Collection Summaries.
			 *
			 * The iterator or the name can be used to explicitly load the
			 * Collection Summary from storage.
			 *
			 * @return Playist Collection Summary Name iterator
			 */
			storage_iterable
			Names() const
			{
				return storage_iterable(collection_storage_provider(), GN_BASE_START);
			}

		};


		/**
		 * <b>Experimental</b>: Provides access to information regarding the underlying
		 * GNSDK playlist library. For working with user collections to create playlists
		 * see GnPlaylistCollection.
		 */
		class GnPlaylist
		{
		public:
			GnPlaylist() throw (GnError);

			GNWRAPPER_ANNOTATE
			/** @internal Version @endinternal
			 *  Retrieves the Playlist SDK version string.
			 *  @return version string if successful
			 *  @return GNSDK_NULL if not successful
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 *   string is a constant. Do not attempt to modify or delete.
			 *  Example version string: 1.2.3.123 (Major.Minor.Improvement.Build)
			 *  Major: New functionality
			 *  Minor: New or changed features
			 *  Improvement: Improvements and fixes
			 *  Build: Internal build number
			 * @ingroup Music_Playlist_InitializationFunctions
			 */
			static gnsdk_cstr_t
			Version();

			/** @internal BuildDate @endinternal
			 *  Retrieves the Playlist SDK's build date string.
			 *  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 *   string is a constant. Do not attempt to modify or delete.
			 *  Example build date string: 2008-02-12 00:41 UTC
			 * @ingroup Music_Playlist_InitializationFunctions
			 */
			static gnsdk_cstr_t
			BuildDate();

			/**
			 *  Media attributes support for playlist generation such as album title,
			 *  artist name and artist type.
			 *  @return Playlist attribute iterator
			 */
			attribute_iterable
			AttributesSupported() const
			{
				return attribute_iterable(attribute_provider(), GN_BASE_START);
			}

		};


#endif /* GNSDK_PLAYLIST */

	} /* namespace Playlist */

}     /* namespace GracenoteSDK */

#endif /* _GNSDK_PLAYLIST_HPP_ */

