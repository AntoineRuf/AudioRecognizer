
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* <b>Experimental</b>: GnPlaylistAttributes
*/
public class GnPlaylistAttributes : GnDataObject {
  private HandleRef swigCPtr;

  internal GnPlaylistAttributes(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnPlaylistAttributes obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnPlaylistAttributes() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnPlaylistAttributes(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnPlaylistAttributes(GnPlaylistAttributes other) : this(gnsdk_csharp_marshalPINVOKE.new_GnPlaylistAttributes(GnPlaylistAttributes.getCPtr(other)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Retrieves the AlbumName value as a string for this attribute .
*  @return album name string value if it exists else an empty string.
*
**/
  public string AlbumName {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_AlbumName_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the ArtistName value as a string for this attribute .
*  @return artist name string value if it exists else an empty string.
*
**/
  public string ArtistName {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_ArtistName_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the ArtistType value as a string for this attribute .
*  @return artist type string value if it exists else an empty string.
*
**/
  public string ArtistType {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_ArtistType_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the Era value as a string for this attribute .
*  @return era string value if it exists else an empty string.
*
**/
  public string Era {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_Era_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the Genre value as a string for this attribute .
*  @return genre string value if it exists else an empty string.
*
**/
  public string Genre {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_Genre_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the Origin value as a string for this attribute .
*  @return origin string value if it exists else an empty string.
*
**/
  public string Origin {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_Origin_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the Mood value as a string for this attribute .
*  @return mood string value if it exists else an empty string.
*
**/
  public string Mood {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_Mood_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the Tempo value as a string for this attribute .
*  @return tempo string value if it exists else an empty string.
*
**/
  public string Tempo {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnPlaylistAttributes_Tempo_get(swigCPtr) );
	} 

  }

}

}
