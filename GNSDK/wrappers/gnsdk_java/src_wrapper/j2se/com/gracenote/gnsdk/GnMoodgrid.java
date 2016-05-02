
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: {@link GnMoodgrid} 
*/ 
 
public class GnMoodgrid extends GnObject {
  private long swigCPtr;

  protected GnMoodgrid(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnMoodgrid_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgrid obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgrid(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GnMoodgrid() {
    this(gnsdk_javaJNI.new_GnMoodgrid(), true);
  }

/** 
* Version information for the library 
* @return version 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnMoodgrid_version();
  }

/**  
* Build Date for the library 
* @return build date 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnMoodgrid_buildDate();
  }

  public GnMoodgridProviderIterable providers() {
    return new GnMoodgridProviderIterable(gnsdk_javaJNI.GnMoodgrid_providers(swigCPtr, this), true);
  }

/** 
* Creates a Presentation that represents the type of moodgrid layout to  generate recommendations for. A presentation 
* object is the way to access all Mood names and recommendations supported by its layout. 
* @param user [in] : valid user  
* @param type [in] : enum value representing the Presentation type .  
* @param coordinate [in] : enum value representing the coordinate type for the presentation layout. 
* @return presentation. 
*/ 
 
  public GnMoodgridPresentation createPresentation(GnUser user, GnMoodgridPresentationType type, GnMoodgridCoordinateType coordinate) throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridPresentation(gnsdk_javaJNI.GnMoodgrid_createPresentation(swigCPtr, this, GnUser.getCPtr(user), user, type.swigValue(), coordinate.swigValue()), true);
  }

/** 
* Retrieves a data point representing the dimensions of the presentation e.g. 5,5  
* @return datapoint. 
*/ 
 
  public GnMoodgridDataPoint dimensions(GnMoodgridPresentationType type) throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridDataPoint(gnsdk_javaJNI.GnMoodgrid_dimensions(swigCPtr, this, type.swigValue()), true);
  }

}
