
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Represents the role that a contributor played in a music or video production;
* for example, singing, playing an instrument, acting, directing, and so on.
* <p><b>Note:</b></p>
* For music credits, the absence of a role for a person indicates that person is the primary
* artist, who may have performed multiple roles.
*/
public class GnRole : GnDataObject {
  private HandleRef swigCPtr;

  internal GnRole(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnRole_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnRole obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnRole() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnRole(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
* Role category, such as string instruments or brass instruments.
* @return Category
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Category {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRole_Category_get(swigCPtr) );
	} 

  }

/**
* Role's display string.
* @return Role
*/
  public string Role {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnRole_Role_get(swigCPtr) );
	} 

  }

}

}
