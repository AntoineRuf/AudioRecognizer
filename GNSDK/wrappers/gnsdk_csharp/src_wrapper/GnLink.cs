
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* GnLink
*/
public class GnLink : GnObject {
  private HandleRef swigCPtr;

  internal GnLink(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnLink_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLink obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLink() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLink(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnLink(GnDataObject gnDataObject, GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnLink__SWIG_0(GnDataObject.getCPtr(gnDataObject), GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnLink(GnDataObject gnDataObject, GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnLink__SWIG_1(GnDataObject.getCPtr(gnDataObject), GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnLink(GnListElement listElement, GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnLink__SWIG_2(GnListElement.getCPtr(listElement), GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnLink(GnListElement listElement, GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnLink__SWIG_3(GnListElement.getCPtr(listElement), GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieves count for the specified content
* @param contentType Type of content to count
* @return Count
* <p><b>Remarks:</b></p>
* <code>Count()</code> can be called repeatedly on the same GnLink object with
* different content type requests to
* retrieve the count for differing values of content type.
*/
  public uint Count(GnLinkContentType contentType) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnLink_Count(swigCPtr, (int)contentType);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkOptions Options() {
    GnLinkOptions ret = new GnLinkOptions(gnsdk_csharp_marshalPINVOKE.GnLink_Options(swigCPtr), false);
    return ret;
  }

/**
* Retrieves CoverArt data.
* @param imageSize size of the image to retrieve
* @param imagePreference image retrieval preference
* @param item_ord Nth CoverArt
* @return GnLinkContent
*  <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different size and ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent CoverArt(GnImageSize imageSize, GnImagePreference imagePreference, uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_CoverArt__SWIG_0(swigCPtr, (int)imageSize, (int)imagePreference, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent CoverArt(GnImageSize imageSize, GnImagePreference imagePreference) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_CoverArt__SWIG_1(swigCPtr, (int)imageSize, (int)imagePreference), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves GenreArt data.
* @param imageSize size of the image to retrieve
* @param imagePreference image retrieval preference
* @param item_ord Nth GenreArt
* @return GnLinkContent
*  <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different size and ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent GenreArt(GnImageSize imageSize, GnImagePreference imagePreference, uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_GenreArt__SWIG_0(swigCPtr, (int)imageSize, (int)imagePreference, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent GenreArt(GnImageSize imageSize, GnImagePreference imagePreference) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_GenreArt__SWIG_1(swigCPtr, (int)imageSize, (int)imagePreference), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves Image data.
* @param imageSize size of the image to retrieve
* @param imagePreference image retrieval preference
* @param item_ord  Nth Image
* @return GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different size and ordinal parameters
* @ingroup Link_QueryFunctions
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent Image(GnImageSize imageSize, GnImagePreference imagePreference, uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_Image__SWIG_0(swigCPtr, (int)imageSize, (int)imagePreference, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent Image(GnImageSize imageSize, GnImagePreference imagePreference) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_Image__SWIG_1(swigCPtr, (int)imageSize, (int)imagePreference), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves ArtistImage data.
* @param  imageSize size of the image to retrieve
* @param imagePreference image retrieval preference
* @param item_ord Nth ArtistImage
* @return  GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different size and ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent ArtistImage(GnImageSize imageSize, GnImagePreference imagePreference, uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_ArtistImage__SWIG_0(swigCPtr, (int)imageSize, (int)imagePreference, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent ArtistImage(GnImageSize imageSize, GnImagePreference imagePreference) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_ArtistImage__SWIG_1(swigCPtr, (int)imageSize, (int)imagePreference), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves Review data.
* @param item_ord Nth Review
* @return  GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent Review(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_Review__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent Review() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_Review__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves Biography data.
* @param item_ord [in] Nth Biography
* @return GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent Biography(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_Biography__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent Biography() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_Biography__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves AristNews data.
* @param item_ord Nth AristNews
* @return GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent ArtistNews(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_ArtistNews__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent ArtistNews() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_ArtistNews__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves LyricXML data.
* @param item_ord Nth LyricXML
* @return  GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent LyricXML(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_LyricXML__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent LyricXML() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_LyricXML__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves LyricText data.
* @param item_ord Nth LyricText
* @return  GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent LyricText(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_LyricText__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent LyricText() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_LyricText__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves CommentsListener data.
* @param item_ord [in] Nth CommentsListener
* @return GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent CommentsListener(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_CommentsListener__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent CommentsListener() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_CommentsListener__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves CommentsRelease data.
* @param item_ord [in] Nth CommentsRelease
* @return GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent CommentsRelease(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_CommentsRelease__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent CommentsRelease() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_CommentsRelease__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves News data.
* @param item_ord Nth News
* @return GnLinkContent
* <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent News(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_News__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent News() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_News__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves DspData data.
* @param item_ord Nth DspData
* @return GnLinkContent
*  <p><b>Remarks:</b></p>
* This API can be called repeatedly on the same link query handle with
* different ordinal parameters
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public GnLinkContent DspData(uint item_ord) {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_DspData__SWIG_0(swigCPtr, item_ord), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLinkContent DspData() {
    GnLinkContent ret = new GnLinkContent(gnsdk_csharp_marshalPINVOKE.GnLink_DspData__SWIG_1(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnStatusEventsDelegate EventHandler() {
    IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnLink_EventHandler(swigCPtr);
    GnStatusEventsDelegate ret = (cPtr == IntPtr.Zero) ? null : new GnStatusEventsDelegate(cPtr, false);
    return ret;
  }

  public virtual void SetCancel(bool bCancel) {
    gnsdk_csharp_marshalPINVOKE.GnLink_SetCancel(swigCPtr, bCancel);
  }

  public virtual bool IsCancelled() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnLink_IsCancelled(swigCPtr);
    return ret;
  }

/**
* Retrieves the Link library version string.
* This API can be called at any time, after getting GnManager instance successfully. The returned
* string is a constant. Do not attempt to modify or delete.
*
* Example: <code>1.2.3.123</code> (Major.Minor.Improvement.Build)<br>
* Major: New functionality<br>
* Minor: New or changed features<br>
* Improvement: Improvements and fixes<br>
* Build: Internal build number<br>
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnLink_Version_get(swigCPtr) );
	} 

  }

/**
*  Retrieves Link library build date string.
*  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC
*  <p><b>Remarks:</b></p>
*  This API can be called at any time, after getting GnManager instance successfully. The returned
*  string is a constant. Do not attempt to modify or delete.
*  Example build date string: 2008-02-12 00:41 UTC
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnLink_BuildDate_get(swigCPtr) );
	} 

  }

}

}
