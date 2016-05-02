
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Playlist "more like this" options. 
*/ 
 
public class GnPlaylistMoreLikeThisOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnPlaylistMoreLikeThisOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistMoreLikeThisOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistMoreLikeThisOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
*  Retrieves an option for Maximum number of Tracks for MoreLikeThis queries on a given collection. 
*  Please note that these options are not serialized or stored. 
*  Option for querying/specifying the maximum number of tracks in the result to be returned. 
*  0 is not a valid value 
*  @return Maximum tracks 
* <p> 
**/ 
 
  public long maxTracks() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_maxTracks__SWIG_0(swigCPtr, this);
  }

/** 
* Sets an option for Maximum number of Tracks for MoreLikeThis queries on a given collection. 
* Please note that these options are not serialized or stored. 
* @param  value [in] The maximum number of tracks to be returned. 0 is not a valid value. 
**/ 
 
  public void maxTracks(long value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_maxTracks__SWIG_1(swigCPtr, this, value);
  }

/** 
* Retrieves an option for maximum number of tracks Per artist  for MoreLikeThis queries on a given collection. 
* Please note that these options are not serialized or stored. 
* 0 is not a valid value 
* @return Maximum tracks per artist 
* <p> 
**/ 
 
  public long maxPerArtist() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_maxPerArtist__SWIG_0(swigCPtr, this);
  }

/** 
* Sets an option for maximum number of tracks per artist for MoreLikeThis queries on a given collection. 
* Please note that these options are not serialized or stored. 
* @param  value [in] The maximum number of tracks per artist to be returned. 0 is not a valid value. 
* <p> 
**/ 
 
  public void maxPerArtist(long value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_maxPerArtist__SWIG_1(swigCPtr, this, value);
  }

/** 
* Retrieves an option for maximum number of tracks per album for MoreLikeThis queries on a given collection. 
* Please note that these options are not serialized or stored. 
* 0 is not a valid value 
* @return Maximum tracks per album 
* <p> 
**/ 
 
  public long maxPerAlbum() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_maxPerAlbum__SWIG_0(swigCPtr, this);
  }

/** 
* Sets an option for maximum number of tracks per album for MoreLikeThis queries on a given collection. 
* Please note that these options are not serialized or stored. 
* @param  value    [in] The maximum number of tracks per album to be returned. 0 is not a valid value. 
**/ 
 
  public void maxPerAlbum(long value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_maxPerAlbum__SWIG_1(swigCPtr, this, value);
  }

/** 
* Retrieves the RandomSeed option for "More Like This" for a given collection. 
* Please note that these options are not serialized or stored. 
* Option for querying/specifying the seed value for the random number generator used in calculating a 
* "More Like This" playlist. 
* @return Seed value 
*/ 
 
  public long randomSeed() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_randomSeed__SWIG_0(swigCPtr, this);
  }

/** 
* Sets the RandomSeed option for "More Like This" for a given collection. 
* Please note that these options are not serialized or stored. 
* Option for querying/specifying the seed value for the random number generator used in calculating a 
* "More Like This" playlist. Using the same number for a seed will generate the same 'random' sequence, thus allowing 
* the same playlist ordering to be recreated. Choosing different numbers will create different playlists. Setting 
* this value to "0" will disable using a random seed. 
* @param value		[in] An unsigned int random seed . 
*/ 
 
  public void randomSeed(long value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistMoreLikeThisOptions_randomSeed__SWIG_1(swigCPtr, this, value);
  }

}
