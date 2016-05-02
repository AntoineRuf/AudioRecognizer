
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Playlist Collection Summary storage management 
* <p> 
* Provides services for managing the Playlist Collection Summary storage including 
* adding, loading and removing collection summaries from persistent storage. 
* <p> 
* Once a Collection Summary is created your application can store it persistently 
* by adding it to the Playlist Collection Summary storage. When your application 
* is initialized it can load the Collection Summary into heap memory from storage. 
* <p> 
* Note: Once a Collection Summary is loaded from persistent storage your application 
* should synchronized the summary with the media available for playlist generation as 
* the user may have added or removed such media while your appication was not active. 
* <p> 
* Collection Summaries can be removed from Playlist Collection Summary storage when 
* no longer needed. The Playlist Collection Summary storage will retain persistent 
* storage resources (file space) used by the removed Collection Summary. To return 
* these resources to the operating system your application should compact the 
* storage soon after removing a Collection Summary. 
* <p> 
* A Gracenote storage provider must be enabled, such as {@link GnStorageSqlite}, for 
* {@link GnPlalistStorage} to access persistent storage. 
* <p> 
*/ 
 
public class GnPlaylistStorage extends GnObject {
  private long swigCPtr;

  protected GnPlaylistStorage(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnPlaylistStorage_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistStorage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistStorage(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GnPlaylistStorage() {
    this(gnsdk_javaJNI.new_GnPlaylistStorage(), true);
  }

/** 
* Performs validation on playlist storage. 
* @return Error information from storage validation 
* Long Running Potential: File system I/O, database size affects running time 
*/ 
 
  public GnError isValid() {
    return new GnError(gnsdk_javaJNI.GnPlaylistStorage_isValid(swigCPtr, this), true);
  }

/** 
* Compact Collection Summary storage 
*/ 
 
  public void compact() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistStorage_compact(swigCPtr, this);
  }

/** 
* Stores a Collection Summary in local storage 
* <p> 
* @param collection [in] Playlist collection 
*/ 
 
  public void store(GnPlaylistCollection collection) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistStorage_store(swigCPtr, this, GnPlaylistCollection.getCPtr(collection), collection);
  }

  public GnPlaylistCollection load(GnPlaylistStorageIterator itr) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistCollection(gnsdk_javaJNI.GnPlaylistStorage_load__SWIG_0(swigCPtr, this, GnPlaylistStorageIterator.getCPtr(itr), itr), true);
  }

/** 
* Loads a Collection Summary from local storage using storage name 
* <p> 
* @param collectionName [in] explicit name of the collection you want to load. 
* @return Playlist collection 
*/ 
 
  public GnPlaylistCollection load(String collectionName) throws com.gracenote.gnsdk.GnException {
    return new GnPlaylistCollection(gnsdk_javaJNI.GnPlaylistStorage_load__SWIG_1(swigCPtr, this, collectionName), true);
  }

/** 
* Removes a Collection Summary from local storage 
* <p> 
* @param collection [in] Playlist collection object 
*/ 
 
  public void remove(GnPlaylistCollection collection) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistStorage_remove__SWIG_0(swigCPtr, this, GnPlaylistCollection.getCPtr(collection), collection);
  }

/** 
* Removes a Collection Summary from local storage using storage name 
* <p> 
* @param collectionName [in] Playlist collection name 
*/ 
 
  public void remove(String collectionName) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistStorage_remove__SWIG_1(swigCPtr, this, collectionName);
  }

/** 
* Sets location for Collection Summary storage 
* <p> 
* @param location [in] Location path 
*/ 
 
  public void location(String location) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnPlaylistStorage_location(swigCPtr, this, location);
  }

  public GnPlaylistStorageIterable names() {
    return new GnPlaylistStorageIterable(gnsdk_javaJNI.GnPlaylistStorage_names(swigCPtr, this), true);
  }

}
