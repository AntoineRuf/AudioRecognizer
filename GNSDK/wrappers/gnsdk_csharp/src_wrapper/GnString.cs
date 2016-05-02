
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Managed immutable string as returned by GNSDK.
*/
public class GnString : GnObject {
  private HandleRef swigCPtr;

  internal GnString(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnString_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnString obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnString() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnString(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

		public override string
		ToString( )
		{
			string str = c_str( );
			return str;
		}
	
/**
* Construct an empty GnString object
*/
  public GnString() : this(gnsdk_csharp_marshalPINVOKE.new_GnString__SWIG_0(), true) {
  }

/**
* Construct a GnString object from a native constant string
* @param str [in] Native string
*/
  public GnString(string str) : this(gnsdk_csharp_marshalPINVOKE.new_GnString__SWIG_1(str), true) {
  }

/**
* Construct a GnString object from an existing GnString object
* @param str [in] GnString object
*/
  public GnString(GnString str) : this(gnsdk_csharp_marshalPINVOKE.new_GnString__SWIG_2(GnString.getCPtr(str)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public string c_str() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnString_c_str(swigCPtr);
    return ret;
  }

/**
* Get flag indicating if string object contains no string
* @return True of empty, false otherwise
*/
  public bool IsEmpty() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnString_IsEmpty(swigCPtr);
    return ret;
  }

/**
* Internally used factory for special SDK-managed strings
* @param str	[in] Native string
* @return Managed string
*/
  public static GnString manage(string str) {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnString_manage(str), true);
    return ret;
  }

}

}
