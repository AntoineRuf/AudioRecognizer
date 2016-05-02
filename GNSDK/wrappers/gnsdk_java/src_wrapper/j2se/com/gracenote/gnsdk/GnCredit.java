
package com.gracenote.gnsdk;

/** 
* Lists the contribution of a person (or occasionally a company, such as a record label) 
* to a recording. 
*/ 
 
public class GnCredit extends GnDataObject {
  private long swigCPtr;

  protected GnCredit(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnCredit_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnCredit obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnCredit(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String gnType() {
    return gnsdk_javaJNI.GnCredit_gnType();
  }

  public static GnCredit from(GnDataObject obj) throws com.gracenote.gnsdk.GnException {
    return new GnCredit(gnsdk_javaJNI.GnCredit_from(GnDataObject.getCPtr(obj), obj), true);
  }

/** 
* Credit's name, such as the name of the person or company. 
* @return Name 
*/ 
 
  public GnName name() {
    return new GnName(gnsdk_javaJNI.GnCredit_name(swigCPtr, this), true);
  }

/** 
* Credit's role 
* @return Role 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public GnRole role() {
    return new GnRole(gnsdk_javaJNI.GnCredit_role(swigCPtr, this), true);
  }

/** 
* Credit's contributor. 
* @return Contributor 
*/ 
 
  public GnContributor contributor() {
    return new GnContributor(gnsdk_javaJNI.GnCredit_contributor(swigCPtr, this), true);
  }

}
