
package com.gracenote.gnsdk;

public class moodgrid_result_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected moodgrid_result_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(moodgrid_result_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_moodgrid_result_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridIdentifier getData(long pos) {
    return new GnMoodgridIdentifier(gnsdk_javaJNI.moodgrid_result_provider_getData(swigCPtr, this, pos), true);
  }

  public long count() {
    return gnsdk_javaJNI.moodgrid_result_provider_count(swigCPtr, this);
  }

}
