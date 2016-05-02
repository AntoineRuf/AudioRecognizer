
package com.gracenote.gnsdk;

/** 
** Internal class  presentation_data_provider 
*/ 
 
public class presentation_data_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected presentation_data_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(presentation_data_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_presentation_data_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public presentation_data_provider() {
    this(gnsdk_javaJNI.new_presentation_data_provider__SWIG_0(), true);
  }

  public presentation_data_provider(GnMoodgridPresentationType type) {
    this(gnsdk_javaJNI.new_presentation_data_provider__SWIG_1(type.swigValue()), true);
  }

  public GnMoodgridDataPoint getData(long pos) {
    return new GnMoodgridDataPoint(gnsdk_javaJNI.presentation_data_provider_getData(swigCPtr, this, pos), true);
  }

  public long count() {
    return gnsdk_javaJNI.presentation_data_provider_count(swigCPtr, this);
  }

}
