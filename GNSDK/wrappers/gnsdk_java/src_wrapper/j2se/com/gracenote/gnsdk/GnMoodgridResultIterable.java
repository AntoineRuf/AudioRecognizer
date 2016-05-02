
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Provides access to {@link GnMoodgridResult} iterator object 
*/ 
 
public class GnMoodgridResultIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMoodgridResultIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridResultIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridResultIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridResultIterable(moodgrid_result_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnMoodgridResultIterable(moodgrid_result_provider.getCPtr(provider), provider, start), true);
  }

  public GnMoodgridResultIterator getIterator() {
    return new GnMoodgridResultIterator(gnsdk_javaJNI.GnMoodgridResultIterable_getIterator(swigCPtr, this), true);
  }

  public GnMoodgridResultIterator end() {
    return new GnMoodgridResultIterator(gnsdk_javaJNI.GnMoodgridResultIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnMoodgridResultIterable_count(swigCPtr, this);
  }

  public GnMoodgridResultIterator at(long index) {
    return new GnMoodgridResultIterator(gnsdk_javaJNI.GnMoodgridResultIterable_at(swigCPtr, this, index), true);
  }

  public GnMoodgridResultIterator getByIndex(long index) {
    return new GnMoodgridResultIterator(gnsdk_javaJNI.GnMoodgridResultIterable_getByIndex(swigCPtr, this, index), true);
  }

}
