
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnVideoCredit
*/
public class GnVideoCredit : GnDataObject {
  private HandleRef swigCPtr;

  internal GnVideoCredit(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideoCredit_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideoCredit obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideoCredit() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideoCredit(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Genre, e.g., comedy. This is a list/locale dependent, multi-level field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*
* @param level :enum value specifying level value
* @return gnsdk_cstr_t
* @ingroup GDO_ValueKeys_Misc
*/
  public string Genre(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Genre(swigCPtr, (int)level);
    return ret;
  }

/**
*  Artist type. This is a list/locale dependent, multi-level field
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*
* @param level        :enum value specifying level value
* @return gnsdk_cstr_t
* @ingroup GDO_ValueKeys_Misc
*/
  public string ArtistType(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_ArtistType(swigCPtr, (int)level);
    return ret;
  }

/**
*  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*
* @param level		[in] enum value specifying level value
* @return gnsdk_cstr_t
* @ingroup GDO_ValueKeys_Misc
*/
  public string Origin(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Origin(swigCPtr, (int)level);
    return ret;
  }

/**
* Artist era. This is a list/locale dependent, multi-level field.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
*
* @param level		[in] enum value specifying level value
* @return gnsdk_cstr_t
* @ingroup GDO_ValueKeys_Misc
*/
  public string Era(GnDataLevel level) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Era(swigCPtr, (int)level);
    return ret;
  }

/**
*  Role, e.g., Actor.
* <p><b>Note:</b></p>
*  For music credits, the absence of a role for a person indicates that person is the primary
*   artist, who may have performed multiple roles.
*  <p><b>Remarks:</b></p>
*  This is a list-based value requiring that a list or locale be loaded into memory.
*
*  To render locale-dependent information for list-based values, your application must allocate a
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information
*  is not set prior to a request for a list-based value.
* @ingroup GDO_ValueKeys_Role
*/
  public string Role {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Role_get(swigCPtr) );
	} 

  }

/**
* Role ID
* @ingroup GDO_ValueKeys_Role
*/
  public uint RoleId {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_RoleId_get(swigCPtr);
      return ret;
    } 
  }

/**
*  A number identifying the role's listing in the credits.
* @ingroup GDO_ValueKeys_Role
*/
  public string RoleBilling {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoCredit_RoleBilling_get(swigCPtr) );
	} 

  }

/**
*  The character's name on the show.
* @ingroup GDO_ValueKeys_Video
*/
  public string CharacterName {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideoCredit_CharacterName_get(swigCPtr) );
	} 

  }

/**
*  Role's rank in importance.
* @ingroup GDO_ValueKeys_Misc
*/
  public uint Rank {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Rank_get(swigCPtr);
      return ret;
    } 
  }

/**
*  Official name object .
* @ingroup GDO_ChildKeys_Name
*/
  public GnName OfficialName {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_OfficialName_get(swigCPtr);
      GnName ret = (cPtr == IntPtr.Zero) ? null : new GnName(cPtr, true);
      return ret;
    } 
  }

/**
* Contributor object.
* @ingroup GDO_ChildKeys_Contributor
*/
  public GnContributor Contributor {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Contributor_get(swigCPtr);
      GnContributor ret = (cPtr == IntPtr.Zero) ? null : new GnContributor(cPtr, true);
      return ret;
    } 
  }

  public GnVideoSeasonEnumerable Seasons {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Seasons_get(swigCPtr);
      GnVideoSeasonEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoSeasonEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoSeriesEnumerable Series {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Series_get(swigCPtr);
      GnVideoSeriesEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoSeriesEnumerable(cPtr, true);
      return ret;
    } 
  }

  public GnVideoWorkEnumerable Works {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideoCredit_Works_get(swigCPtr);
      GnVideoWorkEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnVideoWorkEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
