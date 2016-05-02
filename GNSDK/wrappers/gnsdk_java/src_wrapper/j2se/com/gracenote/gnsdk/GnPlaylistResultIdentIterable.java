
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Provides access to {@link GnPlaylistIdentifier} iterator object 
*/ 
 
public class GnPlaylistResultIdentIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnPlaylistResultIdentIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistResultIdentIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistResultIdentIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnPlaylistResultIdentIterable(result_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnPlaylistResultIdentIterable(result_provider.getCPtr(provider), provider, start), true);
  }

  public GnPlaylistResultIdentIterator getIterator() {
    return new GnPlaylistResultIdentIterator(gnsdk_javaJNI.GnPlaylistResultIdentIterable_getIterator(swigCPtr, this), true);
  }

  public GnPlaylistResultIdentIterator end() {
    return new GnPlaylistResultIdentIterator(gnsdk_javaJNI.GnPlaylistResultIdentIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnPlaylistResultIdentIterable_count(swigCPtr, this);
  }

  public GnPlaylistResultIdentIterator at(long index) {
    return new GnPlaylistResultIdentIterator(gnsdk_javaJNI.GnPlaylistResultIdentIterable_at(swigCPtr, this, index), true);
  }

  public GnPlaylistResultIdentIterator getByIndex(long index) {
    return new GnPlaylistResultIdentIterator(gnsdk_javaJNI.GnPlaylistResultIdentIterable_getByIndex(swigCPtr, this, index), true);
  }

}
