
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Iterate through a collection of {@link GnMoodgridProvider} objects 
*/ 
 
public class GnMoodgridProviderIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMoodgridProviderIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridProviderIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridProviderIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridProvider __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridProvider(gnsdk_javaJNI.GnMoodgridProviderIterator___ref__(swigCPtr, this), false);
  }

  public GnMoodgridProvider next() throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridProvider(gnsdk_javaJNI.GnMoodgridProviderIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnMoodgridProviderIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnMoodgridProviderIterator itr) {
    return gnsdk_javaJNI.GnMoodgridProviderIterator_distance(swigCPtr, this, GnMoodgridProviderIterator.getCPtr(itr), itr);
  }

  public GnMoodgridProviderIterator(moodgrid_provider provider, long pos) {
    this(gnsdk_javaJNI.new_GnMoodgridProviderIterator(moodgrid_provider.getCPtr(provider), provider, pos), true);
  }

}
