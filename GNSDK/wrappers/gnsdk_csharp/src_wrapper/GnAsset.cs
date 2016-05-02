
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Assets for content (cover art, biography etc)
*/
public class GnAsset : GnDataObject {
  private HandleRef swigCPtr;

  internal GnAsset(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnAsset_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnAsset obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnAsset() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnAsset(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Pixel image size of asset as defined with a GnImageSize enum, e.g., kImageSize110 (110x110)
*  @return Image size
*/
  public GnImageSize Size {
    get {
      GnImageSize ret = (GnImageSize)gnsdk_csharp_marshalPINVOKE.GnAsset_Size_get(swigCPtr);
      return ret;
    } 
  }

  public uint Bytes {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnAsset_Bytes_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Asset dimension
*  @return Dimention string
*/
  public string Dimension {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAsset_Dimension_get(swigCPtr) );
	} 

  }

/**
*  Url for retrieval of asset from Gracenote
*  @return URL
*/
  public string Url {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnAsset_Url_get(swigCPtr) );
	} 

  }

}

}
