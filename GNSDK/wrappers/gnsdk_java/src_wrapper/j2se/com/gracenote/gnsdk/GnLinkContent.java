
package com.gracenote.gnsdk;

/** 
* {@link GnLinkContent} 
*/ 
 
public class GnLinkContent extends GnObject {
  private long swigCPtr;

  protected GnLinkContent(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnLinkContent_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLinkContent obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLinkContent(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GnLinkContent(byte[] contentData, long dataSize, GnLinkContentType contentType, GnLinkDataType dataType) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnLinkContent(contentData, dataSize, contentType.swigValue(), dataType.swigValue()), true);
  }

/** 
* Retrieves content data buffer size 
*/ 
 
  public long dataSize() {
    return gnsdk_javaJNI.GnLinkContent_dataSize(swigCPtr, this);
  }

/** 
* Retrieves content data type 
*/ 
 
  public GnLinkDataType dataType() {
    return GnLinkDataType.swigToEnum(gnsdk_javaJNI.GnLinkContent_dataType(swigCPtr, this));
  }

  public void dataBuffer(byte[] pre_allocated_byte_buffer) {
    gnsdk_javaJNI.GnLinkContent_dataBuffer(swigCPtr, this, pre_allocated_byte_buffer);
  }

}
