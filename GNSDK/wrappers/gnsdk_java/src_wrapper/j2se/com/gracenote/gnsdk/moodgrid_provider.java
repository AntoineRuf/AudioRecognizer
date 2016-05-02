
package com.gracenote.gnsdk;

/** 
** Internal class  moodgrid_provider 
*/ 
 
public class moodgrid_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected moodgrid_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(moodgrid_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_moodgrid_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMoodgridProvider getData(long pos) {
    return new GnMoodgridProvider(gnsdk_javaJNI.moodgrid_provider_getData(swigCPtr, this, pos), true);
  }

  public long count() {
    return gnsdk_javaJNI.moodgrid_provider_count(swigCPtr, this);
  }

  public moodgrid_provider() {
    this(gnsdk_javaJNI.new_moodgrid_provider(), true);
  }

}
