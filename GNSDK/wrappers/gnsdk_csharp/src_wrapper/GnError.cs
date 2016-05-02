
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* GNSDK error condition
*/
public class GnError : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnError(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnError obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnError() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnError(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
* Construct GnError with the last error condition experienced in the underlying SDK
*/
  public GnError() : this(gnsdk_csharp_marshalPINVOKE.new_GnError__SWIG_0(), true) {
  }

/**
* Construct GnError with specific error code and description
* @param errorCode			[in] Error code
* @param errorDescription 	[in] Error description
*/
  public GnError(uint errorCode, string errorDescription) : this(gnsdk_csharp_marshalPINVOKE.new_GnError__SWIG_1(errorCode, errorDescription), true) {
  }

/**
* Construct GnError from GnError
* @param gnError		[in] GnError class object
*/
  public GnError(GnError gnError) : this(gnsdk_csharp_marshalPINVOKE.new_GnError__SWIG_2(GnError.getCPtr(gnError)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Error code.
* @return Code
*/
  public uint ErrorCode() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnError_ErrorCode(swigCPtr);
    return ret;
  }

/**
* Error description.
* @return Description
*/
  public string ErrorDescription() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnError_ErrorDescription(swigCPtr);
    return ret;
  }

/**
* API where error occurred
* @return API name
*/
  public string ErrorAPI() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnError_ErrorAPI(swigCPtr);
    return ret;
  }

/**
* Module where error occurred
* @return Module
*/
  public string ErrorModule() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnError_ErrorModule(swigCPtr);
    return ret;
  }

/**
* Source error code
* @return Error code
*/
  public uint SourceErrorCode() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnError_SourceErrorCode(swigCPtr);
    return ret;
  }

/**
* Source module where error occurred
* @return Module
*/
  public string SourceErrorModule() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnError_SourceErrorModule(swigCPtr);
    return ret;
  }

}

}
