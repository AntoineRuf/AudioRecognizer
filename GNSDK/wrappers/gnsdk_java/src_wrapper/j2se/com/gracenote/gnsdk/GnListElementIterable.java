
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnListElement} iterator object 
*/ 
 
public class GnListElementIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnListElementIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnListElementIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnListElementIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnListElementIterable(list_element_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnListElementIterable(list_element_provider.getCPtr(provider), provider, start), true);
  }

  public GnListElementIterator getIterator() {
    return new GnListElementIterator(gnsdk_javaJNI.GnListElementIterable_getIterator(swigCPtr, this), true);
  }

  public GnListElementIterator end() {
    return new GnListElementIterator(gnsdk_javaJNI.GnListElementIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnListElementIterable_count(swigCPtr, this);
  }

  public GnListElementIterator at(long index) {
    return new GnListElementIterator(gnsdk_javaJNI.GnListElementIterable_at(swigCPtr, this, index), true);
  }

  public GnListElementIterator getByIndex(long index) {
    return new GnListElementIterator(gnsdk_javaJNI.GnListElementIterable_getByIndex(swigCPtr, this, index), true);
  }

}
