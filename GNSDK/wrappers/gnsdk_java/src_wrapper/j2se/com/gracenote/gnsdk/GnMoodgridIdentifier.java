
package com.gracenote.gnsdk;

/** 
** <b>Experimental</b>: {@link GnMoodgridIdentifier} 
*/ 
 
public class GnMoodgridIdentifier {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMoodgridIdentifier(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridIdentifier obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridIdentifier(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
* Retrieves a read only string that is the media identifier. 
*/ 
 
  public String mediaIdentifier() {
    return gnsdk_javaJNI.GnMoodgridIdentifier_mediaIdentifier(swigCPtr, this);
  }

/** 
* Retrieves a read only string that is the group the MediaIdentifier belongs too. 
*  E.g. in the case of a Playlist provider , the group represents the name of the collection. 
*/ 
 
  public String group() {
    return gnsdk_javaJNI.GnMoodgridIdentifier_group(swigCPtr, this);
  }

}
