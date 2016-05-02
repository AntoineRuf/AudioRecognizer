
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* A person participating Album or Track creation.
* Provides access to artist image when received from a query object
* with content enabled in lookup data.
*/
public class GnContributor : GnDataObject {
  private HandleRef swigCPtr;

  internal GnContributor(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnContributor_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnContributor obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnContributor() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnContributor(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public static string GnType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnContributor_GnType();
    return ret;
  }

  public static GnContributor From(GnDataObject obj) {
    GnContributor ret = new GnContributor(gnsdk_csharp_marshalPINVOKE.GnContributor_From(GnDataObject.getCPtr(obj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Constructs a GnContributor from a Gracenote identifier and identifier tag
* @param id	[in] Identifier
* @param idTag [in] Identifier tag
*/
  public GnContributor(string id, string idTag) : this(gnsdk_csharp_marshalPINVOKE.new_GnContributor(id, idTag), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Content (cover art, review, etc) object
*  @param GnContentType object
*  @return Content object
*/
  public GnContent Content(GnContentType contentType) {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnContributor_Content(swigCPtr, (int)contentType), true);
    return ret;
  }

/**
*  Fetch the contributor's image content object
*  @return Content object
*/
  public GnContent Image() {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnContributor_Image(swigCPtr), true);
    return ret;
  }

/**
* Fetch the contributor's biography content object.
* @return Content object
*/
  public GnContent Biography() {
    GnContent ret = new GnContent(gnsdk_csharp_marshalPINVOKE.GnContributor_Biography(swigCPtr), true);
    return ret;
  }

/**
* Contributor that collaborated with this contributor in the context of the returned result.
* @return Contributor
*/
  public GnContributor Collaborator() {
    GnContributor ret = new GnContributor(gnsdk_csharp_marshalPINVOKE.GnContributor_Collaborator(swigCPtr), true);
    return ret;
  }

/**
* Contributor's genre. List/locale, multi-level field.
* @param level	[in] Data level
* @return Genre
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnContributor_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
* Contributor's origin, e.g., New York City
* @param level 	[in] Data level
* @return Origin
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Origin(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnContributor_Origin(swigCPtr, (int)level);
    return ret;
  }

/**
* Contributor's era. List/locale dependent, multi-level field.
* @param level	[in] Data level
* @return Era
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string Era(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnContributor_Era(swigCPtr, (int)level);
    return ret;
  }

/**
* Contributor's artist type. List/locale dependent, multi-level field.
* @param level	[in] Data level
* @return Artist type
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string ArtistType(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnContributor_ArtistType(swigCPtr, (int)level);
    return ret;
  }

/**
*  Get flag indicating if this is a collaborator result
*  @return True if a collaborator result, false otherwise
*/
  public bool CollaboratorResult() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnContributor_CollaboratorResult(swigCPtr);
    return ret;
  }

/**
*  Flag indicating if data object response contains full (true) or partial metadata.
*  Returns true if full, false if partial.
* <p><b>Note:</b></p>
*   What constitutes a full result varies among the individual response types and results, and also
*  depends on data availability.
* @ingroup GDO_ValueKeys_Misc
*/
  public bool IsFullResult {
    get {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnContributor_IsFullResult_get(swigCPtr);
      return ret;
    } 
  }

/**
* Contributor's Gracenote identifier
* @return Gracenote ID
*/
  public string GnId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_GnId_get(swigCPtr) );
	} 

  }

/**
* Contributor's Gracenote unique identifier.
* @return Gracenote Unique ID
*/
  public string GnUId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_GnUId_get(swigCPtr) );
	} 

  }

/**
* Retrieves the contributor's product identifier.
* @return Gracenote Product ID
* <p><b>Remarks:</b></p>
* Available for most types, this retrieves a value which can be stored or transmitted. This
* value can be used as a static identifier for the current content as it will not change over time.
*/
  public string ProductId {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_ProductId_get(swigCPtr) );
	} 

  }

/**
* Contributor's Gracenote Tui (title-unique identifier)
* @return Tui
*/
  public string Tui {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_Tui_get(swigCPtr) );
	} 

  }

/**
* Contributor's Gracenote Tui Tag
* @return Tui Tag
*/
  public string TuiTag {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_TuiTag_get(swigCPtr) );
	} 

  }

/**
* Contributor's biography when received from a video response.
* When the contributor object was derived from a video response use this
* method to btain the biography.
* @return Biography
*/
  public string BiographyVideo {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_BiographyVideo_get(swigCPtr) );
	} 

  }

/**
* Contributor's birth date.
* @return Date of birth
*/
  public string BirthDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_BirthDate_get(swigCPtr) );
	} 

  }

/**
* Contributor's place of birth.
* @return Place of birth
*/
  public string BirthPlace {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_BirthPlace_get(swigCPtr) );
	} 

  }

/**
* Date contributor died
* @return Date of death
*/
  public string DeathDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_DeathDate_get(swigCPtr) );
	} 

  }

/**
* Contributor's place of death.
* @return Place of death
*/
  public string DeathPlace {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_DeathPlace_get(swigCPtr) );
	} 

  }

/**
* Contributor's media space, e.g., music, film, stage. List/locale dependent field.
* @return Media space
* <p><b>Remarks:</b></p>
* This is a list-based value requiring that a corresponding locale or list be loaded.
*/
  public string MediaSpace {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnContributor_MediaSpace_get(swigCPtr) );
	} 

  }

/**
* Contributor name object
* @return Name
*/
  public GnName Name {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnContributor_Name_get(swigCPtr);
      GnName ret = (cPtr == IntPtr.Zero) ? null : new GnName(cPtr, true);
      return ret;
    } 
  }

  public GnNameEnumerable NamesOfficial {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnContributor_NamesOfficial_get(swigCPtr);
      GnNameEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnNameEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnNameEnumerable NamesRegional {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnContributor_NamesRegional_get(swigCPtr);
      GnNameEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnNameEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnExternalIdEnumerable ExternalIds {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnContributor_ExternalIds_get(swigCPtr);
      GnExternalIdEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnExternalIdEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnContentEnumerable Contents {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnContributor_Contents_get(swigCPtr);
      GnContentEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnContentEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
