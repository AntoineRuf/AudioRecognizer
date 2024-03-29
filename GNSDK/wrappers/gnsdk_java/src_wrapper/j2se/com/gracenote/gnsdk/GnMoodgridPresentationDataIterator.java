
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Iterate through a collection of {@link GnMoodgridDataPoint} objects 
*/ 
 
public class GnMoodgridPresentationDataIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMoodgridPresentationDataIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridPresentationDataIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridPresentationDataIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridDataPoint __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridDataPoint(gnsdk_javaJNI.GnMoodgridPresentationDataIterator___ref__(swigCPtr, this), false);
  }

  public GnMoodgridDataPoint next() throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridDataPoint(gnsdk_javaJNI.GnMoodgridPresentationDataIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnMoodgridPresentationDataIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnMoodgridPresentationDataIterator itr) {
    return gnsdk_javaJNI.GnMoodgridPresentationDataIterator_distance(swigCPtr, this, GnMoodgridPresentationDataIterator.getCPtr(itr), itr);
  }

  public GnMoodgridPresentationDataIterator(presentation_data_provider provider, long pos) {
    this(gnsdk_javaJNI.new_GnMoodgridPresentationDataIterator(presentation_data_provider.getCPtr(provider), provider, pos), true);
  }

}
