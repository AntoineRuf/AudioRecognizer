
package com.gracenote.gnsdk;

/** 
* list_element_child_iterable 
*//** 
* Element of a Gracenote list. 
*/ 
 
public class GnListElement extends GnObject {
  private long swigCPtr;

  protected GnListElement(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnListElement_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnListElement obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnListElement(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
* Retrieves a display string for a given list element. 
* <p><b>Remarks:</b></p> 
* Use this function to directly retrieve the display string from a list element. 
*/ 
 
  public String displayString() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnListElement_displayString(swigCPtr, this);
  }

/** 
* Retrieves a specified list element ID for a given list element. 
* <p><b>Remarks:</b></p> 
* Use this function to retrieve the ID of a list element. 
*/ 
 
  public long Id() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnListElement_Id(swigCPtr, this);
  }

/** 
* Retrieves a list element ID for use in submitting parcels. 
*/ 
 
  public long IdForSubmit() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnListElement_IdForSubmit(swigCPtr, this);
  }

/** 
* Retrieves the list element's description. 
*/ 
 
  public String description() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnListElement_description(swigCPtr, this);
  }

/** 
* The list element's Rating Type ID (available in content ratings list). 
*/ 
 
  public String ratingTypeId() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnListElement_ratingTypeId(swigCPtr, this);
  }

/** 
* Retrieves the parent element of the given list element. 
* <p><b>Remarks:</b></p> 
* When GNSDK Manager throws an error exception with error code SDKMGRERR_NotFound, 
* then the given element is the top-most parent element. 
*/ 
 
  public GnListElement parent() throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnListElement_parent(swigCPtr, this), true);
  }

/** 
* Retrieves the hierarchy level for a given list element. 
*/ 
 
  public long level() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnListElement_level(swigCPtr, this);
  }

  public GnListElementChildIterable children() {
    return new GnListElementChildIterable(gnsdk_javaJNI.GnListElement_children(swigCPtr, this), true);
  }

}
