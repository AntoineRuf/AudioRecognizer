
package com.gracenote.gnsdk;

public class list_element_child_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected list_element_child_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(list_element_child_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_list_element_child_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/**  
* Constructor 
*/ 
 
  public list_element_child_provider() {
    this(gnsdk_javaJNI.new_list_element_child_provider(), true);
  }

  public GnListElement getData(long pos) {
    return new GnListElement(gnsdk_javaJNI.list_element_child_provider_getData(swigCPtr, this, pos), true);
  }

/**  
* Get child list element count 
*/ 
 
  public long count() {
    return gnsdk_javaJNI.list_element_child_provider_count(swigCPtr, this);
  }

}
