
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnDataMatch} objects 
*/ 
 
public class GnDataMatchIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnDataMatchIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnDataMatchIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnDataMatchIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnDataMatch __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnDataMatch(gnsdk_javaJNI.GnDataMatchIterator___ref__(swigCPtr, this), false);
  }

  public GnDataMatch next() throws com.gracenote.gnsdk.GnException {
    return new GnDataMatch(gnsdk_javaJNI.GnDataMatchIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnDataMatchIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnDataMatchIterator itr) {
    return gnsdk_javaJNI.GnDataMatchIterator_distance(swigCPtr, this, GnDataMatchIterator.getCPtr(itr), itr);
  }

  public GnDataMatchIterator(GnDataMatchProvider provider, long pos) {
    this(gnsdk_javaJNI.new_GnDataMatchIterator(GnDataMatchProvider.getCPtr(provider), provider, pos), true);
  }

}
