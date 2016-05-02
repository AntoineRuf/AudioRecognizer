
package com.gracenote.gnsdk;

/** 
* Represents the role that a contributor played in a music or video production; 
* for example, singing, playing an instrument, acting, directing, and so on. 
* <p><b>Note:</b></p> 
* For music credits, the absence of a role for a person indicates that person is the primary 
* artist, who may have performed multiple roles. 
*/ 
 
public class GnRole extends GnDataObject {
  private long swigCPtr;

  protected GnRole(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnRole_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnRole obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnRole(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
* Role category, such as string instruments or brass instruments. 
* @return Category 
* <p><b>Remarks:</b></p> 
* This is a list-based value requiring that a corresponding locale or list be loaded. 
*/ 
 
  public String category() {
    return gnsdk_javaJNI.GnRole_category(swigCPtr, this);
  }

/** 
* Role's display string. 
* @return Role 
*/ 
 
  public String role() {
    return gnsdk_javaJNI.GnRole_role(swigCPtr, this);
  }

}
