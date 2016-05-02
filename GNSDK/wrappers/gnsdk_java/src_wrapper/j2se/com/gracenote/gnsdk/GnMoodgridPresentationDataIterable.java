
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Provides access to {@link GnMoodgridDataPoint} iterator object 
*/ 
 
public class GnMoodgridPresentationDataIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMoodgridPresentationDataIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridPresentationDataIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridPresentationDataIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridPresentationDataIterable(presentation_data_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnMoodgridPresentationDataIterable(presentation_data_provider.getCPtr(provider), provider, start), true);
  }

  public GnMoodgridPresentationDataIterator getIterator() {
    return new GnMoodgridPresentationDataIterator(gnsdk_javaJNI.GnMoodgridPresentationDataIterable_getIterator(swigCPtr, this), true);
  }

  public GnMoodgridPresentationDataIterator end() {
    return new GnMoodgridPresentationDataIterator(gnsdk_javaJNI.GnMoodgridPresentationDataIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnMoodgridPresentationDataIterable_count(swigCPtr, this);
  }

  public GnMoodgridPresentationDataIterator at(long index) {
    return new GnMoodgridPresentationDataIterator(gnsdk_javaJNI.GnMoodgridPresentationDataIterable_at(swigCPtr, this, index), true);
  }

  public GnMoodgridPresentationDataIterator getByIndex(long index) {
    return new GnMoodgridPresentationDataIterator(gnsdk_javaJNI.GnMoodgridPresentationDataIterable_getByIndex(swigCPtr, this, index), true);
  }

}
