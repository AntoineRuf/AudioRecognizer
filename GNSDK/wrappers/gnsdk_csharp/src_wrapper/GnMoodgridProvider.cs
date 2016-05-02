
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
** <b>Experimental</b>: GnMoodgridProvider
*/
public class GnMoodgridProvider : GnObject {
  private HandleRef swigCPtr;

  internal GnMoodgridProvider(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMoodgridProvider_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMoodgridProvider obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMoodgridProvider() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMoodgridProvider(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
* Retrieves the name of the moodgrid provider.
* @return string representing the name of the provider.
*/
  public string Name {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMoodgridProvider_Name_get(swigCPtr) );
	} 

  }

/**
* Retrieves the type of Moodgrid provider.e.g. playlist collection
* @return string value denoting type of provider
*/
  public string Type {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnMoodgridProvider_Type_get(swigCPtr) );
	} 

  }

/**
* Retrieves a bool value whether the provider needs access to the network.
* @return requiresnetwork
*/
  public bool RequiresNetwork {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnMoodgridProvider_RequiresNetwork_get(swigCPtr);
      return ret;
    } 
  }

}

}
