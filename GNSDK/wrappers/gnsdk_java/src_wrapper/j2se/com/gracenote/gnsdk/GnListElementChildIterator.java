
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnListElement} objects 
*/ 
 
public class GnListElementChildIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnListElementChildIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnListElementChildIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnListElementChildIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnListElement __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnListElementChildIterator___ref__(swigCPtr, this), false);
  }

  public GnListElement next() throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnListElementChildIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnListElementChildIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnListElementChildIterator itr) {
    return gnsdk_javaJNI.GnListElementChildIterator_distance(swigCPtr, this, GnListElementChildIterator.getCPtr(itr), itr);
  }

  public GnListElementChildIterator(list_element_child_provider provider, long pos) {
    this(gnsdk_javaJNI.new_GnListElementChildIterator(list_element_child_provider.getCPtr(provider), provider, pos), true);
  }

}
