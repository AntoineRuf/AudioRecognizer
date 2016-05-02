
package com.gracenote.gnsdk;

/** 
** <b>Experimental</b>: {@link GnMoodgridResult} 
*/ 
 
public class GnMoodgridResult extends GnObject {
  private long swigCPtr;

  protected GnMoodgridResult(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnMoodgridResult_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridResult obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridResult(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Returns the count of the {@link GnMoodgridIdentifier} instances in this result. 
* @return count 
*/ 
 
  public long count() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMoodgridResult_count(swigCPtr, this);
  }

  public GnMoodgridResultIterable identifiers() {
    return new GnMoodgridResultIterable(gnsdk_javaJNI.GnMoodgridResult_identifiers(swigCPtr, this), true);
  }

}
