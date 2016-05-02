
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Playlist Collection Summary that represents 
* the media in a user's collection and can be used to generate 
* playlists from that media. A Collection Summary is not intended to be 
* used as a general database of the user's media collection. 
* <p> 
* <b>Creating a Collection Summary</b> 
* <p> 
* GNSDK supports multiple user collections and therefore multiple Collection 
* Summaries. Each Collection Summary is identified by a unique name. To 
* create a new Collection Summary instantiate a {@link GnPlaylistCollection} object 
* with a unique name. 
* <p> 
* <b>Adding User Media</b> 
* <p> 
* To generate a playlist from user media your application must first 
* identify the user's media using Gracenote services (such as MusicID-File) 
* and then create a Playlist Collection Summary with the recognized media. 
* <p> 
* In a simple example your application can use {@link GnMusicIdFile} Library ID 
* functionality to identify audio tracks. The {@link GnMusicIdFile} result provides 
* to {@link GnAlbum} objects containg {@link GnTrack} objects that map back to the original 
* audio track; your application can add the {@link GnTrack} object <b>and</b> the 
* {@link GnAlbum} object to the Playlist Collection Summary with a unique identifyer 
* for the audio track. 
* <p> 
* Note: When identifying media intended for inclusion in a Playlist Collection 
* Summary you must specify that the result inlcude lookup data kLookupDataPlaylist 
* and kLookupDataSonicData. 
* <p> 
* In some cases an audio track may not contain enough information to match it 
* with a single {@link GnTrack} object, in such caes you application can use the 
* available information to add it to the Collection Summary. For example if only 
* album title or artist name information is available {@link GnMusicId} could be used to 
* match a {@link GnAlbum} or {@link GnContributor} object which can then be added. Similarly 
* if only genre information is available the Lists's subsystem could be used to 
* match a {@link GnListElement} object which can then be added. 
* <p> 
* <b>Generating Playlists</b> 
* <p> 
* Using a {@link GnPlaylistCollection} object your application can generate "More Like 
* This" playlist or where more control is required a playlist specific via 
* Playlist Definition Langauge (PDL). 
* <p> 
* A MTL (More Like This) playlist can be generated from a seed, which can be any 
* Gracenote data object. For example you may use {@link GnMusicId} to perform a text 
* search for a specific track and receive a {@link GnAlbum} object. Your application 
* can provide the {@link GnAlbum} object as the seed. Note: do not use the {@link GnTrack} 
* object as the seed, Playlist will use the "matched" {@link GnTrack} object to determine 
* which track on the album to use. 
* <p> 
* For advanced playlist definition your application can define Playlist Definition 
* Language (PDL) Statements. For more information on creating a PDL Statements consult  
* the PDL Specification. 
* <p> 
* <b>Synchronizing User's Media Collection</b> 
* <p> 
* A user's media collection will change over time. To ensure generated playlists 
* include new media items and don't include removed media items your application must 
* synchronize the user's collection with their Collection Summary. 
* <p> 
* Synchronization is a two step process. Step one requires your application to use 
* SyncProcessAdd to add <b>all</b> unique media identifiers that currently exist in the user's 
* collection. Sep two is to process those identifers by calling SyncProcessExecute. 
* <p> 
* During execution GNSDK reconciles the identifiers within the Collection Summary 
* with those added for sychronization. It can determine which identifiers are new, meaning 
* they are were added to the user's collection and need to be added to the Collection 
* Summary; and those that are old, meaning they were removed from the user's collection 
* and need to be removed from the Collection Summary. 
* <p> 
* <b>Joining Collections</b> 
* <p> 
* Multiple collection summaries can be joined allowing playlists to be generated that contain 
* tracks from multiple collections. 
* <p> 
* <b>Storing Persistently</b> 
* <p> 
* Playlist Collection Summaries are stored entirely in heap memory. To avoid 
* re-creating them every time your application starts you should store them 
* persistently. 
* <p> 
* Gracenote recommends using managed persistent storage services provided by 
* {@link GnPlaylistStorage}. 
* <p> 
* Alternatively a Collection Summary can be serialized into a string that your 
* application can store persistently and later use to reconstitute a Collection 
* Summary in memory. 
* <p> 
*/ 
 
public class GnPlaylistCollection extends GnObject {
  private long swigCPtr;

  protected GnPlaylistCollection(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnPlaylistCollection_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistCollection obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistCollection(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  private IGnPlaylistCollectionSyncEvents elementReference;
  private IGnPlaylistCollectionSyncEventsProxyU syncEventsProxy;
  private long getNewSyncEventsCPtr(IGnPlaylistCollectionSyncEvents element) {
    elementReference = element;
    syncEventsProxy = new IGnPlaylistCollectionSyncEventsProxyU(element);
    return IGnPlaylistCollectionSyncEventsProxyL.getCPtr(syncEventsProxy);
  }

/** 
* Constructor for {@link GnPlaylistCollection} using char* string name. This creates the collection with the name that is passed in. 
* @param name   The name to be used to construct the colleciton. 
*/ 
 
  public GnPlaylistCollection(String name) {
    this(gnsdk_javaJNI.new_GnPlaylistCollection__SWIG_0(name), true);
  }

  public GnPlaylistCollection(byte[] collData, long dataSize) {
    this(gnsdk_javaJNI.new_GnPlaylistCollection__SWIG_1(collData, dataSize), true);
  }

/** 
* Copy Constructor for {@link GnPlaylistCollection}. 
* @param other  [in] reference to {@link GnPlaylistCollection} that is to be copied. 
*/ 
 
  public GnPlaylistCollection(GnPlaylistCollection other) {
    this(gnsdk_javaJNI.new_GnPlaylistCollection__SWIG_2(GnPlaylistCollection.getCPtr(other), other), true);
  }

/** 
* Get the collection name 
* @return Name 
*/ 
 
  public String name() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistCollection_name__SWIG_0(swigCPtr, this);
  }

/** 
* Change the collection name 
* @param updatedName	New collection name 
*/ 
 
  public void name(String updatedName) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_name__SWIG_1(swigCPtr, this, updatedName);
  }

/** 
* Add a identifier with no metadata to a Collection Summary 
* <p> 
* @param mediaIdentifier   [in] Media identifier 
*/ 
 
  public void add(String mediaIdentifier) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_add__SWIG_0(swigCPtr, this, mediaIdentifier);
  }

/** 
* Add a {@link GnAlbum} object and its metadata to a Collection Summary. 
* <p> 
* @param mediaIdentifier   [in] Media identifier 
* @param album             [in] {@link GnAlbum} object 
*/ 
 
  public void add(String mediaIdentifier, GnAlbum album) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_add__SWIG_1(swigCPtr, this, mediaIdentifier, GnAlbum.getCPtr(album), album);
  }

/** 
* Add a {@link GnTrack} object and its metadata to a Collection Summary 
* <p> 
* @param mediaIdentifier   [in] Media identifier 
* @param track             [in] {@link GnTrack} object 
*/ 
 
  public void add(String mediaIdentifier, GnTrack track) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_add__SWIG_2(swigCPtr, this, mediaIdentifier, GnTrack.getCPtr(track), track);
  }

/** 
* Add a {@link GnContributor} object and its metadata to a Collection Summary 
* <p> 
* @param mediaIdentifier   [in] Media identifier 
* @param contributor       [in] {@link GnContributor} object 
*/ 
 
  public void add(String mediaIdentifier, GnContributor contributor) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_add__SWIG_3(swigCPtr, this, mediaIdentifier, GnContributor.getCPtr(contributor), contributor);
  }

/** 
* Add a {@link GnPlaylistAttributes} object to a Collection Summary. 
* <p> 
* @param mediaIdentifier       [in] Media identifier 
* @param playlistAttributes	[in] Playlist attributes 
*/ 
 
  public void add(String mediaIdentifier, GnPlaylistAttributes playlistAttributes) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_add__SWIG_4(swigCPtr, this, mediaIdentifier, GnPlaylistAttributes.getCPtr(playlistAttributes), playlistAttributes);
  }

/** 
* Add a {@link GnListElement} object to a Collection Summary. 
* <p> 
* @param mediaIdentifier   [in] Media identifier 
* @param listElement       [in] {@link GnListElement} object 
*/ 
 
  public void add(String mediaIdentifier, GnListElement listElement) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_add__SWIG_5(swigCPtr, this, mediaIdentifier, GnListElement.getCPtr(listElement), listElement);
  }

/** 
* Remove a media element from a Collection Summary. 
* <p> 
* @param mediaIdentifier  [in] Media identifier 
*/ 
 
  public void remove(String mediaIdentifier) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_remove(swigCPtr, this, mediaIdentifier);
  }

/** 
* Test if a media element is in a Collection Summary. 
* <p> 
* @param mediaIdentifier  [in] Media identifier 
*/ 
 
  public boolean contains(String mediaIdentifier) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistCollection_contains(swigCPtr, this, mediaIdentifier);
  }

/** 
* Find a media element in a Collection Summary. 
* <p> 
* @param mediaIdentifier   [in] Media identifier 
* @param start				[in] Start ordinal 
*/ 
 
  public GnPlaylistCollectionIdentIterator find(String mediaIdentifier, long start) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistCollectionIdentIterator(gnsdk_javaJNI.GnPlaylistCollection_find(swigCPtr, this, mediaIdentifier, start), true);
  }

/** 
* Return metadata from a playlist using a playlist identifier 
* <p> 
* @param user             [in] Gracenote user 
* @param mediaIdentifier  [in] Playlist identifier 
*/ 
 
  public GnPlaylistAttributes attributes(GnUser user, GnPlaylistIdentifier mediaIdentifier) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistAttributes(gnsdk_javaJNI.GnPlaylistCollection_attributes__SWIG_0(swigCPtr, this, GnUser.getCPtr(user), user, GnPlaylistIdentifier.getCPtr(mediaIdentifier), mediaIdentifier), true);
  }

/** 
* Return attributes from a playlist using a Collection Summary name 
* <p> 
* @param user             [in] GN User object 
* @param mediaIdentifier  [in] Playlist identifier 
*/ 
 
  public GnPlaylistAttributes attributes(GnUser user, String mediaIdentifier, String joinedCollectionName) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistAttributes(gnsdk_javaJNI.GnPlaylistCollection_attributes__SWIG_1(swigCPtr, this, GnUser.getCPtr(user), user, mediaIdentifier, joinedCollectionName), true);
  }

/** 
* Validate a Playlist Definitioon Statement 
* @param pdlStatement	Playlist Definition Statment 
* @return Validation result 
*/ 
 
  public GnError statementValidate(String pdlStatement) {
    return new GnError(gnsdk_javaJNI.GnPlaylistCollection_statementValidate(swigCPtr, this, pdlStatement), true);
  }

/** 
* Determine if a Playlist Definition Statement requires a seed 
* to generate a playlist 
* @param pdlStatement	Playlist Definition Statment 
* @return True if a seed is required, false otherwise 
*/ 
 
  public boolean statementRequiresSeed(String pdlStatement) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistCollection_statementRequiresSeed(swigCPtr, this, pdlStatement);
  }

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
 
  public GnString statementAnalyzeIdent(String pdlStatement, String mediaIdentifier) throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnPlaylistCollection_statementAnalyzeIdent(swigCPtr, this, pdlStatement, mediaIdentifier), true);
  }

/** 
* Generate a playlist from a {@link GnDataObject} 
* <p> 
* @param user             [in] Gracenote user 
* @param pdlStatement     [in] Playlist Description Language statement 
* @param playlistSeed     [in] GN data object to use as seed for playlist 
*/ 
 
  public GnPlaylistResult generatePlaylist(GnUser user, String pdlStatement, GnDataObject playlistSeed) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistResult(gnsdk_javaJNI.GnPlaylistCollection_generatePlaylist__SWIG_0(swigCPtr, this, GnUser.getCPtr(user), user, pdlStatement, GnDataObject.getCPtr(playlistSeed), playlistSeed), true);
  }

/** 
* Generate a playlist using a Playlist Definition Language (PDL) Statement from this object's Collection Summary. 
* For more information on creating PDL Statements consult the PDL Specification. 
* <p> 
* @param user             [in] Gracenote user 
* @param pdlStatement     [in] Playlist Description Language statement 
* <p> 
*/ 
 
  public GnPlaylistResult generatePlaylist(GnUser user, String pdlStatement) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistResult(gnsdk_javaJNI.GnPlaylistCollection_generatePlaylist__SWIG_1(swigCPtr, this, GnUser.getCPtr(user), user, pdlStatement), true);
  }

/** 
* Generate a playlist from a {@link GnDataObject} 
* <p> 
* @param user             [in] Gracenote user 
* @param musicDataObj     [in] Gracenote data object 
* <p> 
*/ 
 
  public GnPlaylistResult generateMoreLikeThis(GnUser user, GnDataObject musicDataObj) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistResult(gnsdk_javaJNI.GnPlaylistCollection_generateMoreLikeThis(swigCPtr, this, GnUser.getCPtr(user), user, GnDataObject.getCPtr(musicDataObj), musicDataObj), true);
  }

  public GnPlaylistAttributeIterable attributesSupported() {
    return new GnPlaylistAttributeIterable(gnsdk_javaJNI.GnPlaylistCollection_attributesSupported(swigCPtr, this), true);
  }

  public GnPlaylistCollectionIdentIterable mediaIdentifiers() {
    return new GnPlaylistCollectionIdentIterable(gnsdk_javaJNI.GnPlaylistCollection_mediaIdentifiers(swigCPtr, this), true);
  }

  public GnPlaylistJoinIterable joins() {
    return new GnPlaylistJoinIterable(gnsdk_javaJNI.GnPlaylistCollection_joins(swigCPtr, this), true);
  }

/** 
* Join a playlist collection by collection name 
* <p> 
* @param collectionName   [in] Collection Summary name 
*/ 
 
  public GnPlaylistCollection joinFindByName(String collectionName) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistCollection(gnsdk_javaJNI.GnPlaylistCollection_joinFindByName(swigCPtr, this, collectionName), true);
  }

/** 
* Join a playlist collection by playlist collection object 
* <p> 
* @param toJoin   [in] {@link GnPlaylistCollection} object for join 
*/ 
 
  public void join(GnPlaylistCollection toJoin) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_join(swigCPtr, this, GnPlaylistCollection.getCPtr(toJoin), toJoin);
  }

/** 
* Remove a join with another playlist 
* <p> 
* @param toRemove   [in] {@link GnPlaylistCollection} object to remove join 
*/ 
 
  public void joinRemove(GnPlaylistCollection toRemove) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_joinRemove(swigCPtr, this, GnPlaylistCollection.getCPtr(toRemove), toRemove);
  }

  public long serialize(byte[] serializedData, long dataSize) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistCollection_serialize(swigCPtr, this, serializedData, dataSize);
  }

/** 
* Returns the size of a serialized playlist collection object 
* @return serialized buffer size 
*/ 
 
  public long serializeSize() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistCollection_serializeSize(swigCPtr, this);
  }

/** 
* Add an identifier as part of synchronizing a user's media collection with the 
* corresponding Collection Summary. 
* <p> 
* Collection sychronization is a two step process, step one is to use this method to 
* add all unique identifiers that currently exist in the user's collection. Step two 
* is to execute the synchronization process. 
* @param mediaIdentifier [in] unique media identifier used in you application e.g. file path 
*/ 
 
  public void syncProcessAdd(String mediaIdentifier) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_syncProcessAdd(swigCPtr, this, mediaIdentifier);
  }

/** 
* Process synchronize identifiers previously added to the Collection Summary to complete 
* synchronizing a user's media collection with the corresponding Collection Summary. 
* <p> 
* As step two of the synchronization process call this method after adding all unique 
* identifiers using SyncProcessAdd. This call will determine which identifiers added for 
* synchronization need to be also be added to the Collection Summary; and those that need to be 
* removed from the Collection Summary because they no longer exist in the user's collection. 
* This information is delivered via the synchronization delegate. 
* @param syncEvents [in] Synchronizations events delegate 
*/ 
 
  public void syncProcessExecute(IGnPlaylistCollectionSyncEvents syncEvents) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistCollection_syncProcessExecute(swigCPtr, this, getNewSyncEventsCPtr(syncEvents), syncEventsProxy);
  }

/** 
* Get object for setting "more like this" options 
* @return	More like this options object 
*/ 
 
  public GnPlaylistMoreLikeThisOptions moreLikeThisOptions() {
    return new GnPlaylistMoreLikeThisOptions(gnsdk_javaJNI.GnPlaylistCollection_moreLikeThisOptions(swigCPtr, this), false);
  }

}
