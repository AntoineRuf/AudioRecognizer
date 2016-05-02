
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

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
public class GnPlaylistStorage : GnObject {
  private HandleRef swigCPtr;

  internal GnPlaylistStorage(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylistStorage obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylistStorage() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylistStorage(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnPlaylistStorage() : this(gnsdk_csharp_marshalPINVOKE.new_GnPlaylistStorage(), true) {
  }

/**
* Performs validation on playlist storage.
* @return Error information from storage validation
* Long Running Potential: File system I/O, database size affects running time
*/
  public GnError IsValid() {
    GnError ret = new GnError(gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_IsValid(swigCPtr), true);
    return ret;
  }

/**
* Compact Collection Summary storage
*/
  public void Compact() {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Compact(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Stores a Collection Summary in local storage
*
* @param collection [in] Playlist collection
*/
  public void Store(GnPlaylistCollection collection) {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Store(swigCPtr, GnPlaylistCollection.getCPtr(collection));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnPlaylistCollection Load(GnPlaylistStorageEnumerator itr) {
    GnPlaylistCollection ret = new GnPlaylistCollection(gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Load__SWIG_0(swigCPtr, GnPlaylistStorageEnumerator.getCPtr(itr)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Loads a Collection Summary from local storage using storage name
*
* @param collectionName [in] explicit name of the collection you want to load.
* @return Playlist collection
*/
  public GnPlaylistCollection Load(string collectionName) {
    GnPlaylistCollection ret = new GnPlaylistCollection(gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Load__SWIG_1(swigCPtr, collectionName), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Removes a Collection Summary from local storage
*
* @param collection [in] Playlist collection object
*/
  public void Remove(GnPlaylistCollection collection) {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Remove__SWIG_0(swigCPtr, GnPlaylistCollection.getCPtr(collection));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Removes a Collection Summary from local storage using storage name
*
* @param collectionName [in] Playlist collection name
*/
  public void Remove(string collectionName) {
    gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Remove__SWIG_1(swigCPtr, collectionName);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Sets location for Collection Summary storage
*
* @param location [in] Location path
*/
  public void Location(string location) {
  System.IntPtr templocation = GnMarshalUTF8.NativeUtf8FromString(location);
    try {
      gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Location(swigCPtr, templocation);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(templocation);
    }
  }

  public GnPlaylistStorageEnumerable Names {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnPlaylistStorage_Names_get(swigCPtr);
      GnPlaylistStorageEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnPlaylistStorageEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
