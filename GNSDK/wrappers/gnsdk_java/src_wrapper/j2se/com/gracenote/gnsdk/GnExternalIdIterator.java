
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnExternalId} objects 
*/ 
 
public class GnExternalIdIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnExternalIdIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnExternalIdIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnExternalIdIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnExternalId __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnExternalId(gnsdk_javaJNI.GnExternalIdIterator___ref__(swigCPtr, this), false);
  }

  public GnExternalId next() throws com.gracenote.gnsdk.GnException {
    return new GnExternalId(gnsdk_javaJNI.GnExternalIdIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnExternalIdIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnExternalIdIterator itr) {
    return gnsdk_javaJNI.GnExternalIdIterator_distance(swigCPtr, this, GnExternalIdIterator.getCPtr(itr), itr);
  }

  public GnExternalIdIterator(GnExternalIdProvider provider, long pos) {
    this(gnsdk_javaJNI.new_GnExternalIdIterator(GnExternalIdProvider.getCPtr(provider), provider, pos), true);
  }

}
