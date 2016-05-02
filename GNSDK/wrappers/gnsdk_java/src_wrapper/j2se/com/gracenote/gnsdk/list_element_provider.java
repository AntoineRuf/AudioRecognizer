
package com.gracenote.gnsdk;

public class list_element_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected list_element_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(list_element_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_list_element_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/**  
* Constructor 
*/ 
 
  public list_element_provider() {
    this(gnsdk_javaJNI.new_list_element_provider(), true);
  }

  public GnListElement getData(long pos) throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.list_element_provider_getData(swigCPtr, this, pos), true);
  }

/** 
* Get count  
*/ 
 
  public long count() {
    return gnsdk_javaJNI.list_element_provider_count(swigCPtr, this);
  }

}
