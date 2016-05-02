
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* <b>Experimental</b>: Playlist "more like this" options.
*/
public class GnPlaylistMoreLikeThisOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnPlaylistMoreLikeThisOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylistMoreLikeThisOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylistMoreLikeThisOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylistMoreLikeThisOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
*  Retrieves an option for Maximum number of Tracks for MoreLikeThis queries on a given collection.
*  Please note that these options are not serialized or stored.
*  Option for querying/specifying the maximum number of tracks in the result to be returned.
*  0 is not a valid value
*  @return Maximum tracks
*
**/
  public uint MaxTracks() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_MaxTracks__SWIG_0(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Sets an option for Maximum number of Tracks for MoreLikeThis queries on a given collection.
* Please note that these options are not serialized or stored.
* @param  value [in] The maximum number of tracks to be returned. 0 is not a valid value.
**/
  public void MaxTracks(uint value) {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_MaxTracks__SWIG_1(swigCPtr, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieves an option for maximum number of tracks Per artist  for MoreLikeThis queries on a given collection.
* Please note that these options are not serialized or stored.
* 0 is not a valid value
* @return Maximum tracks per artist
*
**/
  public uint MaxPerArtist() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_MaxPerArtist__SWIG_0(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Sets an option for maximum number of tracks per artist for MoreLikeThis queries on a given collection.
* Please note that these options are not serialized or stored.
* @param  value [in] The maximum number of tracks per artist to be returned. 0 is not a valid value.
*
**/
  public void MaxPerArtist(uint value) {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_MaxPerArtist__SWIG_1(swigCPtr, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieves an option for maximum number of tracks per album for MoreLikeThis queries on a given collection.
* Please note that these options are not serialized or stored.
* 0 is not a valid value
* @return Maximum tracks per album
*
**/
  public uint MaxPerAlbum() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_MaxPerAlbum__SWIG_0(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Sets an option for maximum number of tracks per album for MoreLikeThis queries on a given collection.
* Please note that these options are not serialized or stored.
* @param  value    [in] The maximum number of tracks per album to be returned. 0 is not a valid value.
**/
  public void MaxPerAlbum(uint value) {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_MaxPerAlbum__SWIG_1(swigCPtr, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieves the RandomSeed option for "More Like This" for a given collection.
* Please note that these options are not serialized or stored.
* Option for querying/specifying the seed value for the random number generator used in calculating a
* "More Like This" playlist.
* @return Seed value
*/
  public uint RandomSeed() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_RandomSeed__SWIG_0(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
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
  public void RandomSeed(uint value) {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistMoreLikeThisOptions_RandomSeed__SWIG_1(swigCPtr, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
