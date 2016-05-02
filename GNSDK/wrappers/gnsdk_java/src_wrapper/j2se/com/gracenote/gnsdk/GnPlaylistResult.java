
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: {@link GnPlaylistResult} 
*/ 
 
public class GnPlaylistResult extends GnObject {
  private long swigCPtr;

  protected GnPlaylistResult(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnPlaylistResult_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistResult obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistResult(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GnPlaylistResultIdentIterable identifiers() {
    return new GnPlaylistResultIdentIterable(gnsdk_javaJNI.GnPlaylistResult_identifiers(swigCPtr, this), true);
  }

}
