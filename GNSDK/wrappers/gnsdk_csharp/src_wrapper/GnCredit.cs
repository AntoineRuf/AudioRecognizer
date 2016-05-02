
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Lists the contribution of a person (or occasionally a company, such as a record label)
* to a recording.
*/
public class GnCredit : GnDataObject {
  private HandleRef swigCPtr;

  internal GnCredit(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnCredit_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnCredit obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnCredit() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnCredit(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnCredit_GnType();
    return ret;
  }

  public static GnCredit From(GnDataObject obj) {
    GnCredit ret = new GnCredit(gnsdk_csharp_marshalPINVOKE.GnCredit_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Credit's name, such as the name of the person or company.
* @return Name
*/
  public GnName Name {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnCredit_Name_get(swigCPtr);
      GnName ret = (cPtr == IntPtr.Zero) ? null : new GnName(cPtr, true);
      return ret;
    } 
  }

/**
* Credit's contributor.
* @return Contributor
*/
  public GnContributor Contributor {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnCredit_Contributor_get(swigCPtr);
      GnContributor ret = (cPtr == IntPtr.Zero) ? null : new GnContributor(cPtr, true);
      return ret;
    } 
  }

/**
* Credit's role
* @return Role
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public GnRole Role {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnCredit_Role_get(swigCPtr);
      GnRole ret = (cPtr == IntPtr.Zero) ? null : new GnRole(cPtr, true);
      return ret;
    } 
  }

}

}
