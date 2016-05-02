
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnContent} objects 
*/ 
 
public class GnContentIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnContentIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnContentIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnContentIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnContent __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnContent(gnsdk_javaJNI.GnContentIterator___ref__(swigCPtr, this), false);
  }

  public GnContent next() throws com.gracenote.gnsdk.GnException {
    return new GnContent(gnsdk_javaJNI.GnContentIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnContentIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnContentIterator itr) {
    return gnsdk_javaJNI.GnContentIterator_distance(swigCPtr, this, GnContentIterator.getCPtr(itr), itr);
  }

  public GnContentIterator(GnContentProvider provider, long pos) {
    this(gnsdk_javaJNI.new_GnContentIterator(GnContentProvider.getCPtr(provider), provider, pos), true);
  }

}
