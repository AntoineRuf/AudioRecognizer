
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnListElement} objects 
*/ 
 
public class GnListElementIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnListElementIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnListElementIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnListElementIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnListElement __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnListElementIterator___ref__(swigCPtr, this), false);
  }

  public GnListElement next() throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnListElementIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnListElementIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnListElementIterator itr) {
    return gnsdk_javaJNI.GnListElementIterator_distance(swigCPtr, this, GnListElementIterator.getCPtr(itr), itr);
  }

  public GnListElementIterator(list_element_provider provider, long pos) {
    this(gnsdk_javaJNI.new_GnListElementIterator(list_element_provider.getCPtr(provider), provider, pos), true);
  }

}
