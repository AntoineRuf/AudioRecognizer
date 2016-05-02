
package com.gracenote.gnsdk;

/** 
* Logging Filters 
*/ 
 
public class GnLogFilters {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnLogFilters(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLogFilters obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLogFilters(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnLogFilters() {
    this(gnsdk_javaJNI.new_GnLogFilters(), true);
  }

/** Include error logging messages */ 
 
  public GnLogFilters clear() {
    return new GnLogFilters(gnsdk_javaJNI.GnLogFilters_clear(swigCPtr, this), false);
  }

/** Include error logging messages */ 
 
  public GnLogFilters error() {
    return new GnLogFilters(gnsdk_javaJNI.GnLogFilters_error(swigCPtr, this), false);
  }

/** Include warning logging messages */ 
 
  public GnLogFilters warning() {
    return new GnLogFilters(gnsdk_javaJNI.GnLogFilters_warning(swigCPtr, this), false);
  }

/** Include informative logging messages */ 
 
  public GnLogFilters info() {
    return new GnLogFilters(gnsdk_javaJNI.GnLogFilters_info(swigCPtr, this), false);
  }

/** Include debugging logging messages */ 
 
  public GnLogFilters debug() {
    return new GnLogFilters(gnsdk_javaJNI.GnLogFilters_debug(swigCPtr, this), false);
  }

/** Include all logging messages */ 
 
  public GnLogFilters all() {
    return new GnLogFilters(gnsdk_javaJNI.GnLogFilters_all(swigCPtr, this), false);
  }

}
