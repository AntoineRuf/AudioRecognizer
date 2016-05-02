
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**************************************************************************
** GnDsp
*/
public class GnDsp : GnObject {
  private HandleRef swigCPtr;

  internal GnDsp(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnDsp_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnDsp obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnDsp() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnDsp(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
* Initializes the DSP library.
* @param user set user
* @param featureType The kind of DSP feature, for example a fingerprint.
* @param audioSampleRate The source audio sample rate.
* @param audioSampleSize The source audio sample size.
* @param audioChannels	The source audio channels
*/
  public GnDsp(GnUser user, GnDspFeatureType featureType, uint audioSampleRate, uint audioSampleSize, uint audioChannels) : this(gnsdk_csharp_marshalPINVOKE.new_GnDsp(GnUser.getCPtr(user), (int)featureType, audioSampleRate, audioSampleSize, audioChannels), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool FeatureAudioWrite(byte[] audioData, uint audioDataBytes) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnDsp_FeatureAudioWrite(swigCPtr, audioData, audioDataBytes);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Indicates the the DSP feature has reached the end of the write operation.
*/
  public void FeatureEndOfAudioWrite() {
    gnsdk_csharp_marshalPINVOKE.GnDsp_FeatureEndOfAudioWrite(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieve GnDspFeature
* @return GnDspFeature
*/
  public GnDspFeature FeatureRetrieve() {
    GnDspFeature ret = new GnDspFeature(gnsdk_csharp_marshalPINVOKE.GnDsp_FeatureRetrieve(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Retrieves GnDsp SDK version string.
*  This API can be called at any time, after getting instance of GnManager successfully. The returned
*  string is a constant. Do not attempt to modify or delete.
*  Example: 1.2.3.123 (Major.Minor.Improvement.Build)
*  Major: New functionality
*  Minor: New or changed features
*  Improvement: Improvements and fixes
*  Build: Internal build number
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnDsp_Version_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the GnDsp SDK's build date string.
*  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after getting instance of GnManager successfully. The returned
* string is a constant. Do not attempt to modify or delete.
*  Example build date string: 2008-02-12 00:41 UTC
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnDsp_BuildDate_get(swigCPtr) );
	} 

  }

}

}
