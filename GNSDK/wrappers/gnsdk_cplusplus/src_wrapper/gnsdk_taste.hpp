/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_TASTE_HPP_
#define _GNSDK_TASTE_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk.hpp"
#include "gnsdk_playlist.hpp"
#include "metadata.hpp"
#include "gnsdk_taste.h"

namespace gracenote
{
	    namespace taste
	{
#if GNSDK_TASTE

		class GnPersona;
		/**
		 * Indicates the preferred action with GnPersona::Add.
		 * @ingroup Taste_TypesEnums
		 */
		enum GnPersonaAction
		{
			/**
			 *   Unknown Persona Action.
			 * @ingroup Taste_TypesEnums
			 */
			kPersonaActionUnknown = 0,

			kPersonaActionAdded,
			kPersonaActionPlayed,
			kPersonaActionSkipped,
			kPersonaActionLiked,
			kPersonaActionDisliked

		};

		/**
		 *   GnPersona Options.
		 */
		class GnPersonaOptions
		{
		public:
			GNWRAPPER_ANNOTATE

			/**
			 *  Set option using option name
			 *  @param option   [in] Option name
			 *  @param value	[in] Option value
			 */
			void
			Custom(gnsdk_cstr_t option, gnsdk_cstr_t value) throw (GnError);


			/**
			 *  Set option using option name
			 *  @param option   [in] Option name
			 *  @param bEnable	[in] Option enable true/false
			 */
			void
			Custom(gnsdk_cstr_t option, bool bEnable) throw (GnError);


		protected:
			GnPersonaOptions() : weakhandle_(GNSDK_NULL) {}


		private:
			friend class GnPersona;
			gnsdk_taste_persona_handle_t weakhandle_;
		};


		/**
		 *   GnTasteChannelComponent. The generated object is returned from iterating a taste channel music attribute set .
		 *   Each channel component allows for accessing the precise GnListElement and its corresponding weight that went
		 *   into composing that particular taste channel.
		 */
		class GnTasteChannelComponent
		{
		public:
			GnTasteChannelComponent() : listelement_(GNSDK_NULL), weight_(0.0f) { }

			/**
			 *  Retrieves the weight that is attributed to this specific component that went into calculating the channel.
			 *  @return gnsdk_flt32_t value . ( 32 bit float)
			 */
			gnsdk_flt32_t
			Weight() { return weight_; }
			/**
			 *  Retrieves the list element that is attributed to this specific component . The list element can be queries for
			 *  for values ,descriptors , parents etc. for further data in this specific GnTasteChannelComponent.
			 *  @return GnListElement  object .
			 */
			GnListElement&
			ListElement() { return listelement_; }

			bool operator == (const GnTasteChannelComponent& rhs) const { return  (weight_ == rhs.weight_) && (listelement_ == rhs.listelement_); }
		private:
			friend class channel_component_provider;
			GnTasteChannelComponent(GnListElement element, gnsdk_flt32_t weight ) : listelement_(element), weight_(weight) { }
			GnListElement listelement_;
			gnsdk_flt32_t weight_;
		};


		/**
		 *   channel_component_provider. Internal class to support iteration of GnTasteChannelComponents.
		 */
		class channel_component_provider
		{
		public:
			channel_component_provider() : weakhandle_(GNSDK_NULL), component_(GNSDK_NULL){; }
			channel_component_provider(gnsdk_taste_channel_handle_t channel, gnsdk_cstr_t component) : weakhandle_(channel), component_(component){; }

			GnTasteChannelComponent
			get_data(gnsdk_uint32_t pos) throw (GnError);

			gnsdk_uint32_t
			count() const;


		private:
			gnsdk_taste_channel_handle_t weakhandle_;
			gnsdk_cstr_t                 component_;
		};


		/**
		 *   GnTasteChannel.  The generated object returned from a GnTasteChannelSet for a specific
		 *   taste persona (GnPersona). Each taste channel has a unique PDL statement that can be used to query any gracenote playlist collection
		 *   for a result set that matches the taste for that channelset.
		 *   Each channel also  supports iterating  the list of (Genre / Origin /Era/ Tempo / Mood) music attributes that
		 *   went into calculating the PDL statement.
		 */
		typedef gn_facade_range_iterator<GnTasteChannelComponent, channel_component_provider> component_iterator;
		typedef gn_iterable_container<GnTasteChannelComponent, channel_component_provider>  component_iterable;

		class GnTasteChannel : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnTasteChannel() throw (GnError) { };

			explicit
			GnTasteChannel(gnsdk_taste_channel_handle_t handle) throw (GnError);

			/**
			 * Retrieves PDL-Statement for channel
			 */
			gnsdk_cstr_t
			PdlStatement(bool b_friendly) throw (GnError);

			/**
			 * Retrieves Observation count for channel
			 */
			gnsdk_uint32_t
			ObservationCount() throw (GnError);

			/**
			 * Retrieves the Iterable container for all Genre elements that went into calculating the taste channel
			 */
			component_iterable Genre() const 
			{
				return component_iterable(channel_component_provider(get<gnsdk_taste_channel_handle_t>(), GNSDK_TASTE_COMPONENT_GENRE), GN_BASE_START);
			}
			/**
			 * Retrieves the Iterable container for all Orgin elements that went into calculating the taste channel
			 */
			component_iterable Origin() const 
			{
				return component_iterable(channel_component_provider(get<gnsdk_taste_channel_handle_t>(), GNSDK_TASTE_COMPONENT_ORIGIN), GN_BASE_START);
			}
			/**
			 * Retrieves the Iterable container for all Era elements that went into calculating the taste channel
			 */
			component_iterable Era() const
			{
			  return component_iterable(channel_component_provider(get<gnsdk_taste_channel_handle_t>(), GNSDK_TASTE_COMPONENT_ERA), GN_BASE_START);
			}
			/**
			 * Retrieves the Iterable container for all Type elements that went into calculating the taste channel
			 */
			component_iterable Type() const 
			{
			   return component_iterable(channel_component_provider(get<gnsdk_taste_channel_handle_t>(), GNSDK_TASTE_COMPONENT_TYPE), GN_BASE_START);
			}
			/**
			 * Retrieves the Iterable container for all Mood elements that went into calculating the taste channel
			 */
			component_iterable Mood() const
			{
			   return component_iterable(channel_component_provider(get<gnsdk_taste_channel_handle_t>(), GNSDK_TASTE_COMPONENT_MOOD), GN_BASE_START);
			}
			/**
			 * Retrieves the Iterable container for all Tempo elements that went into calculating the taste channel
			 */
			component_iterable Tempo() const 
			{
				return component_iterable(channel_component_provider(get<gnsdk_taste_channel_handle_t>(), GNSDK_TASTE_COMPONENT_TEMPO), GN_BASE_START);

			}
		};


		/*---------------------------------------------------------------------------
		 * Tnternal: taste_channel_provider
		 */
		class taste_channel_provider
		{
		public:
			taste_channel_provider() : weakhandle_(GNSDK_NULL) { }
			taste_channel_provider(gnsdk_taste_channelset_handle_t channelset) : weakhandle_(channelset) { }

			GnTasteChannel
			get_data(gnsdk_uint32_t pos);

			gnsdk_uint32_t
			count() const;


		private:
			gnsdk_taste_channelset_handle_t weakhandle_;
		};


		/*---------------------------------------------------------------------------
		** Internal : persona_storage_provider
		*/
		class persona_storage_provider
		{
		public:
			persona_storage_provider();

			/* Default method required . */
			gnsdk_cstr_t
			get_data(gnsdk_uint32_t pos);

			gnsdk_uint32_t count() const;
		};


		typedef gn_facade_range_iterator<GnTasteChannel, taste_channel_provider>    channel_iterator;
		typedef gn_facade_range_iterator<gnsdk_cstr_t, persona_storage_provider>    persona_storage_iterator;

		typedef gn_iterable_container<GnTasteChannel, taste_channel_provider>    channel_iterable;
		typedef gn_iterable_container<gnsdk_cstr_t, persona_storage_provider>    persona_storage_iterable;

		/**
		 *   GnTasteChannelSet.  The generated object for a specific taste persona (GnPersona).
		 *   This object represents an iterable collection  of GnTasteChannels .
		 */
		class GnTasteChannelSet : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE
			GnTasteChannelSet() throw (GnError) { };

			/**
			 * Retrieves the iterable container for all the generated GnTasteChannels
			 */
			channel_iterable Channels() const 
			{
				return channel_iterable( taste_channel_provider (get<gnsdk_taste_channelset_handle_t>()), GN_BASE_START);
			}


		private:
			friend class GnPersona;
			GnTasteChannelSet(gnsdk_taste_channelset_handle_t handle) throw (GnError);

		};


		/**************************************************************************
		** GnPersonaStorage
		*/
		class GnPersonaStorage : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnPersonaStorage();
			virtual
			~GnPersonaStorage() { }


			/**
			 * Compact collection storage
			 *
			 * @return GnError
			 */
			GnError
			IsValid() const;


			/**
			 * Compact collection storage
			 */
			void
			Compact() throw (GnError);


			/**
			 * Stores a Collection Summary in local storage
			 *
			 * @param collection [in] Playlist collection object
			 */
			void
			Store(const GnPersona& persona) throw (GnError);

			/**
			 * Loads a Collection Summary from local storage
			 *
			 * @param itr [in] Storage iterator at the position you want to load.
			 * @return collection
			 */
			GnPersona
			Load(persona_storage_iterator itr)  throw (GnError);


			/**
			 * Loads a Collection Summary from local storage
			 *
			 * @param collectionName [in] explicit name of the collection you want to load.
			 * @return collection
			 */
			GnPersona
			Load(gnsdk_cstr_t personaName) throw (GnError);


			/**
			 * Removes a Collection Summary from local storage
			 *
			 * @param collection [in] Playlist collection object
			 */
			void
			Remove(const GnPersona& persona) throw (GnError);

			/**
			 * Removes a Collection Summary from local storage
			 *
			 * @param collectionName [in] Playlist collection name
			 */
			void
			Remove(gnsdk_cstr_t personaName) throw (GnError);

			/**
			 * Sets location for Collection storage
			 *
			 * @param location [in] Location path
			 */
			void
			Location(gnsdk_cstr_t location) throw (GnError);

			/**
			 * Access to an iteration of all the stored collection names , the iterator or the name
			 * can be used to explicitly load the collection.
			 *
			 * @return gn_iterable_container<storage_iterator>
			 */
			persona_storage_iterable PersonaNames() const 
			{
				return persona_storage_iterable(persona_storage_provider(), GN_BASE_START);
			}
		};


		/**************************************************************************
		** GnPersona class
		*/
		class GnPersona : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnPersona() { };
			GnPersona(const GnUser& user, gnsdk_cstr_t name) throw (GnError);
			GnPersona(const GnUser& user, gnsdk_byte_t* buffer, gnsdk_size_t size) throw (GnError);

			/**
			 * Constructor for GnPersona using a C native taste persona handle.
			 * Caution For advanced users only: Please note that the native handle will be addref'd when consumed by this class and it is up to
			 * the user to ensure that native handle is properly released ( depending on which C API gave access to the handle).
			 * @param handle   The gnsdk_taste_persona_handle_t handle
			 */
			explicit
			GnPersona(gnsdk_taste_persona_handle_t handle);


			/**
			 * Add()
			 * Add a GnAlbum object and its metadata to a Collection Summary.
			 * @param metadata  [in] GnAlbum object
			 */
			void
			Add(const metadata::GnAlbum& album, GnPersonaAction action) throw (GnError);

#if GNSDK_PLAYLIST
			/**
			 * Add()
			 * Add a GnPlaylistAttributes object to a Collection Summary.
			 * @param metadata  [in] GnPlaylistAttributes object
			 */
			void
			Add(const playlist::GnPlaylistAttributes& playlistAttributes, GnPersonaAction action) throw (GnError);
#endif /* GNSDK_PLAYLIST */

			/**
			 * Retrieves GnTast name
			 */
			gnsdk_cstr_t
			Name() const throw (GnError);

			/**
			 * Sets a new GnTaste name
			 */
			void
			SetName(gnsdk_cstr_t name) throw (GnError);

			/**
			 * Retrieves current observation count
			 */
			gnsdk_uint32_t
			ObservationCount() const throw (GnError);

			/**
			 * Retrieves GnPersonaOptions
			 */
			GnPersonaOptions&
			Options() { return options_; }

			/**
			 * Serialize GnPersona into buffer.
			 * @param p_buffer		[in] Buffer
			 * @param size			[in] Buffer size
			 */
			gnsdk_size_t
			Serialize(gnsdk_byte_t* p_buffer, gnsdk_size_t size) throw (GnError);

			/**
			 * Retrieves Serialize size
			 */
			gnsdk_size_t
			SerializeSize() throw (GnError);

			/**
			 * Create ChannelSet.
			 * @param channels		[in] number of channels
			 */
			GnTasteChannelSet
			CreateChannelSet(GnLocale locale,  gnsdk_uint32_t channels) throw (GnError);


		protected:
			GnPersonaOptions options_;

			friend class GnPersonaStorage;
		};


		class GnTaste
		{
		public:
			/**
			 *  Retrieves GnTaste SDK version string.
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 *  string is a constant. Do not attempt to modify or delete.
			 *  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
			 *  Major: New functionality
			 *  Minor: New or changed features
			 *  Improvement: Improvements and fixes
			 *  Build: Internal build number
			 */
			static gnsdk_cstr_t
			Version();

			/**
			 *  Retrieves the GnTaste SDK's build date string.
			 *  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC
			 *  <p><b>Remarks:</b></p>
			 *  This API can be called at any time, after getting instance of GnManager successfully. The returned
			 * string is a constant. Do not attempt to modify or delete.
			 *  Example build date string: 2008-02-12 00:41 UTC
			 */
			static gnsdk_cstr_t
			BuildDate();
		};


#endif /* GNSDK_TASTE */

	} /* namespace taste */

}     /* namespace gracenote */

#endif /* _GNSDK_TASTE_HPP_ */

