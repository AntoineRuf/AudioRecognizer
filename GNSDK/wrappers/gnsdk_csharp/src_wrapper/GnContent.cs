
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Provides access to content assets that can be retrieved from Urls.
* Content is only available is content is enabled from the original query's lookup data.
* Use the query object's options to enable content.
* The type of content that is available depends on the parent object. For example
* you can access album cover art from a GnAlbum object, but not an artist image. To
* retrieve an artist image navigate to a GnContributor object and invoke it's GnContent
* instance.
*/
public class GnContent : GnDataObject {
  private HandleRef swigCPtr;

  internal GnContent(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnContent_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnContent obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnContent() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnContent(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
* Asset by image size (if applicable)
* @param imageSize	[in] Image size
* @return Asset object
*/
  public GnAsset Asset(GnImageSize imageSize) {
    GnAsset ret = new GnAsset(gnsdk_csharp_marshalPINVOKE.GnContent_Asset(swigCPtr, (int)imageSize), true);
    return ret;
  }

  public GnAssetEnumerable Assets() {
    GnAssetEnumerable ret = new GnAssetEnumerable(gnsdk_csharp_marshalPINVOKE.GnContent_Assets(swigCPtr), true);
    return ret;
  }

  public string Id {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContent_Id_get(swigCPtr) );
	} 

  }

/**
*  Content's mime type
*  @return Mime type
*/
  public string MimeType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContent_MimeType_get(swigCPtr) );
	} 

  }

/**
*  Content type - cover art, biography, etc.
*  @return Content type
*/
  public GnContentType ContentType {
    get {
      GnContentType ret = (GnContentType)gnsdk_csharp_marshalPINVOKE.GnContent_ContentType_get(swigCPtr);
      return ret;
    } 
  }

}

}
