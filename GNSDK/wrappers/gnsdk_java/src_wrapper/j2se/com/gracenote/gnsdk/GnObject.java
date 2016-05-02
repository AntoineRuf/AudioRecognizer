
package com.gracenote.gnsdk;

/** 
* Base object for managing objects in natively running GNSDK. 
*/ 
 
public class GnObject {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnObject(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnObject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        throw new UnsupportedOperationException("C++ destructor does not have public access");
      }
      swigCPtr = 0;
    }
  }

/** 
*  Get flag indicating if {@link GnObject} contains no native object handle 
*  @return True if null, false otherwise 
*/ 
 
  public boolean isNull() {
    return gnsdk_javaJNI.GnObject_isNull(swigCPtr, this);
  }

}
