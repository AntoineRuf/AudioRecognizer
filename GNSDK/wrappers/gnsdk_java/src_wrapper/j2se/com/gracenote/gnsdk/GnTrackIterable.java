
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnTrack} iterator object 
*/ 
 
public class GnTrackIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnTrackIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnTrackIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnTrackIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnTrackIterable(GnTrackProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnTrackIterable(GnTrackProvider.getCPtr(provider), provider, start), true);
  }

  public GnTrackIterator getIterator() {
    return new GnTrackIterator(gnsdk_javaJNI.GnTrackIterable_getIterator(swigCPtr, this), true);
  }

  public GnTrackIterator end() {
    return new GnTrackIterator(gnsdk_javaJNI.GnTrackIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnTrackIterable_count(swigCPtr, this);
  }

  public GnTrackIterator at(long index) {
    return new GnTrackIterator(gnsdk_javaJNI.GnTrackIterable_at(swigCPtr, this, index), true);
  }

  public GnTrackIterator getByIndex(long index) {
    return new GnTrackIterator(gnsdk_javaJNI.GnTrackIterable_getByIndex(swigCPtr, this, index), true);
  }

}
