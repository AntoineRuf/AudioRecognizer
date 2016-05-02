
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnTrack} objects 
*/ 
 
public class GnTrackIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnTrackIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnTrackIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnTrackIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnTrack __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnTrack(gnsdk_javaJNI.GnTrackIterator___ref__(swigCPtr, this), false);
  }

  public GnTrack next() throws com.gracenote.gnsdk.GnException {
    return new GnTrack(gnsdk_javaJNI.GnTrackIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnTrackIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnTrackIterator itr) {
    return gnsdk_javaJNI.GnTrackIterator_distance(swigCPtr, this, GnTrackIterator.getCPtr(itr), itr);
  }

  public GnTrackIterator(GnTrackProvider provider, long pos) {
    this(gnsdk_javaJNI.new_GnTrackIterator(GnTrackProvider.getCPtr(provider), provider, pos), true);
  }

}
