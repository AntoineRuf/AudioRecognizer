
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoSide 
* Both DVDs and Blu-ray discs can be dual side. Double-Sided discs include a single layer on each side of the disc
* that data can be recorded to. Double-Sided recordable DVDs come in two formats: DVD-R and DVD+R, including the rewritable DVD-RW and
* DVD+RW. These discs can hold about 8.75GB of data if you burn to both sides. Dual-side Blu-ray discs can store 50 GB of
* data (25GB on each side).
*/
public class GnVideoSide : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoSide(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoSide_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoSide obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoSide() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoSide(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Ordinal value
* @ingroup GDO_ValueKeys_Misc
*/
  public uint Ordinal {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoSide_Ordinal_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Matched boolean value indicating whether this type
*  is the one that matched the input criteria.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool Matched {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnVideoSide_Matched_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Notes
* @ingroup GDO_ValueKeys_Video
*/
  public string Notes {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoSide_Notes_get(swigCPtr) );
	} 

  }

/**
*  Official title object
* @ingroup GDO_ChildKeys_Title
*/
  public GnTitle OfficialTitle {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSide_OfficialTitle_get(swigCPtr);
      GnTitle ret = (cPtr == IntPtr.Zero) ? null : new GnTitle(cPtr, true);
      return ret;
    } 
  }

  public GnVideoLayerEnumerable Layers {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoSide_Layers_get(swigCPtr);
      GnVideoLayerEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoLayerEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
