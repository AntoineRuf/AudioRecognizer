
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnCredit} objects 
*/ 
 
public class GnCreditIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnCreditIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnCreditIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnCreditIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnCredit __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnCredit(gnsdk_javaJNI.GnCreditIterator___ref__(swigCPtr, this), false);
  }

  public GnCredit next() throws com.gracenote.gnsdk.GnException {
    return new GnCredit(gnsdk_javaJNI.GnCreditIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnCreditIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnCreditIterator itr) {
    return gnsdk_javaJNI.GnCreditIterator_distance(swigCPtr, this, GnCreditIterator.getCPtr(itr), itr);
  }

  public GnCreditIterator(GnCreditProvider provider, long pos) {
    this(gnsdk_javaJNI.new_GnCreditIterator(GnCreditProvider.getCPtr(provider), provider, pos), true);
  }

}
