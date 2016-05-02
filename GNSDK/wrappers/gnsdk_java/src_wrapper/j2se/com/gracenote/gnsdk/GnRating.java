
package com.gracenote.gnsdk;

/** 
**/ 
 
public class GnRating extends GnDataObject {
  private long swigCPtr;

  protected GnRating(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnRating_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnRating obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnRating(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Rating value, e.g., PG 
* 
*/ 
 
  public String rating() {
    return gnsdk_javaJNI.GnRating_rating(swigCPtr, this);
  }

/** 
*  Rating type value, e.g., MPAA . 
* 
*/ 
 
  public String ratingType() {
    return gnsdk_javaJNI.GnRating_ratingType(swigCPtr, this);
  }

/** 
*  Rating description . 
* 
*/ 
 
  public String ratingDesc() {
    return gnsdk_javaJNI.GnRating_ratingDesc(swigCPtr, this);
  }

/** 
*  Rating type Id. 
* 
*/ 
 
  public long ratingTypeId() {
    return gnsdk_javaJNI.GnRating_ratingTypeId(swigCPtr, this);
  }

/** 
*  Rating reason 
* 
*/ 
 
  public String ratingReason() {
    return gnsdk_javaJNI.GnRating_ratingReason(swigCPtr, this);
  }

/** 
*  AMPAA (Motion Picture Assoc. of America) rating. 
* 
*/ 
 
  public String ratingMPAA() {
    return gnsdk_javaJNI.GnRating_ratingMPAA(swigCPtr, this);
  }

/** 
*  A MPAA (Motion Picture Assoc. of America) TV rating type. 
* 
*/ 
 
  public String ratingMPAATV() {
    return gnsdk_javaJNI.GnRating_ratingMPAATV(swigCPtr, this);
  }

/** 
*  A FAB (Film Advisory Board) rating. 
* 
*/ 
 
  public String ratingFAB() {
    return gnsdk_javaJNI.GnRating_ratingFAB(swigCPtr, this);
  }

/** 
*  A CHVRS (Canadian Home Video Rating System) rating 
* 
*/ 
 
  public String ratingCHVRS() {
    return gnsdk_javaJNI.GnRating_ratingCHVRS(swigCPtr, this);
  }

/** 
*  A Canadian TV rating type value. 
* 
*/ 
 
  public String ratingCanadianTV() {
    return gnsdk_javaJNI.GnRating_ratingCanadianTV(swigCPtr, this);
  }

/** 
*  A BBFC (British Board of Film Classification) rating type value. 
* 
*/ 
 
  public String ratingBBFC() {
    return gnsdk_javaJNI.GnRating_ratingBBFC(swigCPtr, this);
  }

/** 
*  A CBFC (Central Board of Film Certification) rating type value. 
* 
*/ 
 
  public String ratingCBFC() {
    return gnsdk_javaJNI.GnRating_ratingCBFC(swigCPtr, this);
  }

/** 
*  A OFLC (Australia) TV rating type value. 
* 
*/ 
 
  public String ratingOFLC() {
    return gnsdk_javaJNI.GnRating_ratingOFLC(swigCPtr, this);
  }

/** 
*  A Hong Kong rating type value. 
* 
*/ 
 
  public String ratingHongKong() {
    return gnsdk_javaJNI.GnRating_ratingHongKong(swigCPtr, this);
  }

/** 
* A Finnish rating type value. 
* 
*/ 
 
  public String ratingFinnish() {
    return gnsdk_javaJNI.GnRating_ratingFinnish(swigCPtr, this);
  }

/** 
*  A KMRB (Korea Media Rating Board) rating type value. 
* 
*/ 
 
  public String ratingKMRB() {
    return gnsdk_javaJNI.GnRating_ratingKMRB(swigCPtr, this);
  }

/** 
* A DVD Parental rating 
* 
*/ 
 
  public String ratingDVDParental() {
    return gnsdk_javaJNI.GnRating_ratingDVDParental(swigCPtr, this);
  }

/** 
* A EIRIN (Japan) rating 
* 
*/ 
 
  public String ratingEIRIN() {
    return gnsdk_javaJNI.GnRating_ratingEIRIN(swigCPtr, this);
  }

/** 
*  A INCAA (Argentina) rating 
* 
*/ 
 
  public String ratingINCAA() {
    return gnsdk_javaJNI.GnRating_ratingINCAA(swigCPtr, this);
  }

/** 
*  A DJTCQ (Dept of Justice, Rating, Titles and Qualification) (Brazil) rating 
* 
*/ 
 
  public String ratingDJTCQ() {
    return gnsdk_javaJNI.GnRating_ratingDJTCQ(swigCPtr, this);
  }

/** 
*  A Quebecois rating. 
* 
*/ 
 
  public String ratingQuebec() {
    return gnsdk_javaJNI.GnRating_ratingQuebec(swigCPtr, this);
  }

/** 
*  A French rating. 
* 
*/ 
 
  public String ratingFrance() {
    return gnsdk_javaJNI.GnRating_ratingFrance(swigCPtr, this);
  }

/** 
*  A FSK (German) rating. 
* 
*/ 
 
  public String ratingFSK() {
    return gnsdk_javaJNI.GnRating_ratingFSK(swigCPtr, this);
  }

/** 
*  An Italian rating 
* 
*/ 
 
  public String ratingItaly() {
    return gnsdk_javaJNI.GnRating_ratingItaly(swigCPtr, this);
  }

/** 
*  A Spanish rating 
* 
*/ 
 
  public String ratingSpain() {
    return gnsdk_javaJNI.GnRating_ratingSpain(swigCPtr, this);
  }

}
