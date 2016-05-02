
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* <b>Experimental</b>: GnMoodgrid
*/
public class GnMoodgrid : GnObject {
  private HandleRef swigCPtr;

  internal GnMoodgrid(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMoodgrid_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMoodgrid obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMoodgrid() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMoodgrid(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnMoodgrid() : this(gnsdk_csharp_marshalPINVOKE.new_GnMoodgrid(), true) {
  }

/**
* Creates a Presentation that represents the type of moodgrid layout to  generate recommendations for. A presentation
* object is the way to access all Mood names and recommendations supported by its layout.
* @param user [in] : valid user 
* @param type [in] : enum value representing the Presentation type . 
* @param coordinate [in] : enum value representing the coordinate type for the presentation layout.
* @return presentation.
*/
  public GnMoodgridPresentation CreatePresentation(GnUser user, GnMoodgridPresentationType type, GnMoodgridCoordinateType coordinate) {
    GnMoodgridPresentation ret = new GnMoodgridPresentation(gnsdk_csharp_marshalPINVOKE.GnMoodgrid_CreatePresentation(swigCPtr, GnUser.getCPtr(user), (int)type, (int)coordinate), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves a data point representing the dimensions of the presentation e.g. 5,5 
* @return datapoint.
*/
  public GnMoodgridDataPoint Dimensions(GnMoodgridPresentationType type) {
    GnMoodgridDataPoint ret = new GnMoodgridDataPoint(gnsdk_csharp_marshalPINVOKE.GnMoodgrid_Dimensions(swigCPtr, (int)type), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Version information for the library
* @return version
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMoodgrid_Version_get(swigCPtr) );
	} 

  }

/** 
* Build Date for the library
* @return build date
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMoodgrid_BuildDate_get(swigCPtr) );
	} 

  }

  public GnMoodgridProviderEnumerable Providers {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMoodgrid_Providers_get(swigCPtr);
      GnMoodgridProviderEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnMoodgridProviderEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
