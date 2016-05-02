
package com.gracenote.gnsdk;

/** 
**/ 
 
public class GnVideoCredit extends GnDataObject {
  private long swigCPtr;

  protected GnVideoCredit(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideoCredit_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoCredit obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoCredit(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
*  Role, e.g., Actor. 
* <p><b>Note:</b></p> 
*  For music credits, the absence of a role for a person indicates that person is the primary 
*   artist, who may have performed multiple roles. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* 
*/ 
 
  public String role() {
    return gnsdk_javaJNI.GnVideoCredit_role(swigCPtr, this);
  }

/** 
* Role ID 
* 
*/ 
 
  public long roleId() {
    return gnsdk_javaJNI.GnVideoCredit_roleId(swigCPtr, this);
  }

/** 
*  A number identifying the role's listing in the credits. 
* 
*/ 
 
  public String roleBilling() {
    return gnsdk_javaJNI.GnVideoCredit_roleBilling(swigCPtr, this);
  }

/** 
*  The character's name on the show. 
* 
*/ 
 
  public String characterName() {
    return gnsdk_javaJNI.GnVideoCredit_characterName(swigCPtr, this);
  }

/** 
*  Role's rank in importance. 
* 
*/ 
 
  public long rank() {
    return gnsdk_javaJNI.GnVideoCredit_rank(swigCPtr, this);
  }

/** 
*  Genre, e.g., comedy. This is a list/locale dependent, multi-level field. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* <p> 
* @param level :enum value specifying level value 
* @return gnsdk_cstr_t 
* 
*/ 
 
  public String genre(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoCredit_genre(swigCPtr, this, level.swigValue());
  }

/** 
*  Artist type. This is a list/locale dependent, multi-level field 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* <p> 
* @param level        :enum value specifying level value 
* @return gnsdk_cstr_t 
* 
*/ 
 
  public String artistType(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoCredit_artistType(swigCPtr, this, level.swigValue());
  }

/** 
*  Geographic location, e.g., "New York City". This is a list/locale dependent, multi-level field. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* <p> 
* @param level		[in] enum value specifying level value 
* @return gnsdk_cstr_t 
* 
*/ 
 
  public String origin(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoCredit_origin(swigCPtr, this, level.swigValue());
  }

/** 
* Artist era. This is a list/locale dependent, multi-level field. 
*  <p><b>Remarks:</b></p> 
*  This is a list-based value requiring that a list or locale be loaded into memory. 
* <p> 
*  To render locale-dependent information for list-based values, your application must allocate a 
*  <code>GnLocale</code> object. A <code>LocaleNotLoaded</code> message is returned when locale information 
*  is not set prior to a request for a list-based value. 
* <p> 
* @param level		[in] enum value specifying level value 
* @return gnsdk_cstr_t 
* 
*/ 
 
  public String era(GnDataLevel level) {
    return gnsdk_javaJNI.GnVideoCredit_era(swigCPtr, this, level.swigValue());
  }

/** 
*  Official name object . 
* 
*/ 
 
  public GnName officialName() {
    return new GnName(gnsdk_javaJNI.GnVideoCredit_officialName(swigCPtr, this), true);
  }

/** 
* Contributor object. 
* 
*/ 
 
  public GnContributor contributor() {
    return new GnContributor(gnsdk_javaJNI.GnVideoCredit_contributor(swigCPtr, this), true);
  }

  public GnVideoWorkIterable works() {
    return new GnVideoWorkIterable(gnsdk_javaJNI.GnVideoCredit_works(swigCPtr, this), true);
  }

  public GnVideoSeriesIterable series() {
    return new GnVideoSeriesIterable(gnsdk_javaJNI.GnVideoCredit_series(swigCPtr, this), true);
  }

  public GnVideoSeasonIterable seasons() {
    return new GnVideoSeasonIterable(gnsdk_javaJNI.GnVideoCredit_seasons(swigCPtr, this), true);
  }

}
