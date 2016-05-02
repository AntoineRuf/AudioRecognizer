
package com.gracenote.gnsdk;

/** 
** Both DVDs and Blu-ray discs can be dual side. Double-Sided discs include a single layer on each side of the disc 
* that data can be recorded to. Double-Sided recordable DVDs come in two formats: DVD-R and DVD+R, including the rewritable DVD-RW and 
* DVD+RW. These discs can hold about 8.75GB of data if you burn to both sides. Dual-side Blu-ray discs can store 50 GB of 
* data (25GB on each side). 
*/ 
 
public class GnVideoSide extends GnDataObject {
  private long swigCPtr;

  protected GnVideoSide(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoSide_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoSide obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoSide(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Ordinal value 
* 
*/ 
 
  public long ordinal() {
    return gnsdk_javaJNI.GnVideoSide_ordinal(swigCPtr, this);
  }

/** 
*  Matched boolean value indicating whether this type 
*  is the one that matched the input criteria. 
* 
*/ 
 
  public boolean matched() {
    return gnsdk_javaJNI.GnVideoSide_matched(swigCPtr, this);
  }

/** 
*  Notes 
* 
*/ 
 
  public String notes() {
    return gnsdk_javaJNI.GnVideoSide_notes(swigCPtr, this);
  }

/** 
*  Official title object 
* 
*/ 
 
  public GnTitle officialTitle() {
    return new GnTitle(gnsdk_javaJNI.GnVideoSide_officialTitle(swigCPtr, this), true);
  }

  public GnVideoLayerIterable layers() {
    return new GnVideoLayerIterable(gnsdk_javaJNI.GnVideoSide_layers(swigCPtr, this), true);
  }

}
