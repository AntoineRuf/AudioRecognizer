
package com.gracenote.gnsdk;

/** 
*  Represents a match to query where any type of match is desired, album or contributor. 
*/ 
 
public class GnDataMatch extends GnDataObject {
  private long swigCPtr;

  protected GnDataMatch(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnDataMatch_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnDataMatch obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnDataMatch(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Flag indicating if match is album 
*  @return True if album is a match, false otherwise 
*/ 
 
  public boolean isAlbum() {
    return gnsdk_javaJNI.GnDataMatch_isAlbum(swigCPtr, this);
  }

/** 
*  Flag indicating if match is contributor 
*  @return True if result is a contributor, false otherwise 
*/ 
 
  public boolean isContributor() {
    return gnsdk_javaJNI.GnDataMatch_isContributor(swigCPtr, this);
  }

/** 
*  If album, get match as album object 
*  @return Album 
*/ 
 
  public GnAlbum getAsAlbum() {
    return new GnAlbum(gnsdk_javaJNI.GnDataMatch_getAsAlbum(swigCPtr, this), true);
  }

/** 
*  If contributor, get match as contributor object 
*  @return Contributor 
*/ 
 
  public GnContributor getAsContributor() {
    return new GnContributor(gnsdk_javaJNI.GnDataMatch_getAsContributor(swigCPtr, this), true);
  }

}
