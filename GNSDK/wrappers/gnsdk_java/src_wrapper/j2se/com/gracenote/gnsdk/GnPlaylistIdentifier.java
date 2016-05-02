
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: {@link GnPlaylistIdentifier} 
*/ 
 
public class GnPlaylistIdentifier {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnPlaylistIdentifier(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistIdentifier obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistIdentifier(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public String mediaIdentifier() {
    return gnsdk_javaJNI.GnPlaylistIdentifier_mediaIdentifier(swigCPtr, this);
  }

  public String collectionName() {
    return gnsdk_javaJNI.GnPlaylistIdentifier_collectionName(swigCPtr, this);
  }

}
