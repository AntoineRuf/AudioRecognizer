
package com.gracenote.gnsdk;

public class collection_storage_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected collection_storage_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(collection_storage_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_collection_storage_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public collection_storage_provider() {
    this(gnsdk_javaJNI.new_collection_storage_provider__SWIG_0(), true);
  }

  public collection_storage_provider(collection_storage_provider arg0) {
    this(gnsdk_javaJNI.new_collection_storage_provider__SWIG_1(collection_storage_provider.getCPtr(arg0), arg0), true);
  }

  public String getData(long pos) {
    return gnsdk_javaJNI.collection_storage_provider_getData(swigCPtr, this, pos);
  }

  public long count() {
    return gnsdk_javaJNI.collection_storage_provider_count(swigCPtr, this);
  }

}
