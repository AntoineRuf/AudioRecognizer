
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Iterate through a collection of {@link GnMoodgridResult} objects 
*/ 
 
public class GnMoodgridResultIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMoodgridResultIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridResultIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridResultIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridIdentifier __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridIdentifier(gnsdk_javaJNI.GnMoodgridResultIterator___ref__(swigCPtr, this), false);
  }

  public GnMoodgridIdentifier next() throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridIdentifier(gnsdk_javaJNI.GnMoodgridResultIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnMoodgridResultIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnMoodgridResultIterator itr) {
    return gnsdk_javaJNI.GnMoodgridResultIterator_distance(swigCPtr, this, GnMoodgridResultIterator.getCPtr(itr), itr);
  }

  public GnMoodgridResultIterator(moodgrid_result_provider provider, long pos) {
    this(gnsdk_javaJNI.new_GnMoodgridResultIterator(moodgrid_result_provider.getCPtr(provider), provider, pos), true);
  }

}
