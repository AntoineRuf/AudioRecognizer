
package com.gracenote.gnsdk;

public class attribute_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected attribute_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(attribute_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_attribute_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public attribute_provider() {
    this(gnsdk_javaJNI.new_attribute_provider(), true);
  }

  public String getData(long pos) {
    return gnsdk_javaJNI.attribute_provider_getData(swigCPtr, this, pos);
  }

  public long count() {
    return gnsdk_javaJNI.attribute_provider_count(swigCPtr, this);
  }

}
