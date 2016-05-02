
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Provides access to {@link GnPlaylistIdentifier} iterator object 
*/ 
 
public class GnPlaylistCollectionIdentIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnPlaylistCollectionIdentIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistCollectionIdentIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistCollectionIdentIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnPlaylistCollectionIdentIterable(collection_ident_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnPlaylistCollectionIdentIterable(collection_ident_provider.getCPtr(provider), provider, start), true);
  }

  public GnPlaylistCollectionIdentIterator getIterator() {
    return new GnPlaylistCollectionIdentIterator(gnsdk_javaJNI.GnPlaylistCollectionIdentIterable_getIterator(swigCPtr, this), true);
  }

  public GnPlaylistCollectionIdentIterator end() {
    return new GnPlaylistCollectionIdentIterator(gnsdk_javaJNI.GnPlaylistCollectionIdentIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnPlaylistCollectionIdentIterable_count(swigCPtr, this);
  }

  public GnPlaylistCollectionIdentIterator at(long index) {
    return new GnPlaylistCollectionIdentIterator(gnsdk_javaJNI.GnPlaylistCollectionIdentIterable_at(swigCPtr, this, index), true);
  }

  public GnPlaylistCollectionIdentIterator getByIndex(long index) {
    return new GnPlaylistCollectionIdentIterator(gnsdk_javaJNI.GnPlaylistCollectionIdentIterable_getByIndex(swigCPtr, this, index), true);
  }

}
