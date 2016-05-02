
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Provides access to {@link GnMoodgridProvider} iterator object 
*/ 
 
public class GnMoodgridProviderIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMoodgridProviderIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridProviderIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridProviderIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridProviderIterable(moodgrid_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnMoodgridProviderIterable(moodgrid_provider.getCPtr(provider), provider, start), true);
  }

  public GnMoodgridProviderIterator getIterator() {
    return new GnMoodgridProviderIterator(gnsdk_javaJNI.GnMoodgridProviderIterable_getIterator(swigCPtr, this), true);
  }

  public GnMoodgridProviderIterator end() {
    return new GnMoodgridProviderIterator(gnsdk_javaJNI.GnMoodgridProviderIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnMoodgridProviderIterable_count(swigCPtr, this);
  }

  public GnMoodgridProviderIterator at(long index) {
    return new GnMoodgridProviderIterator(gnsdk_javaJNI.GnMoodgridProviderIterable_at(swigCPtr, this, index), true);
  }

  public GnMoodgridProviderIterator getByIndex(long index) {
    return new GnMoodgridProviderIterator(gnsdk_javaJNI.GnMoodgridProviderIterable_getByIndex(swigCPtr, this, index), true);
  }

}
