
package com.gracenote.gnsdk;

/** 
** Configures options for {@link GnMusicId} 
*/ 
 
public class GnMusicIdOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMusicIdOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
*  Indicates whether the MusicID query should be performed against local embedded databases or online. 
*  @param lookupMode  [in] One of the {@link GnLookupMode} values 
*/ 
 
  public void lookupMode(GnLookupMode lookupMode) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_lookupMode(swigCPtr, this, lookupMode.swigValue());
  }

/** 
*  Indicates the lookup data value for the MusicID query. 
*  @param lookupData [in] One of the {@link GnLookupData} values 
*  @param bEnable    [in] Set lookup data 
*/ 
 
  public void lookupData(GnLookupData lookupData, boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_lookupData(swigCPtr, this, lookupData.swigValue(), bEnable);
  }

/** 
*  Indicates the preferred language of the returned results. 
*  @param preferredLanguage [in] One of the GNSDK language values 
*/ 
 
  public void preferResultLanguage(GnLanguage preferredLanguage) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_preferResultLanguage(swigCPtr, this, preferredLanguage.swigValue());
  }

/** 
*  Indicates the preferred external ID of the returned results. 
*  Only available where single result is also requested. 
*  @param strExternalId [in] Gracenote external ID source name 
*/ 
 
  public void preferResultExternalId(String strExternalId) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_preferResultExternalId(swigCPtr, this, strExternalId);
  }

/** 
*  Indicates using cover art to prefer the returned results. 
*  @param bEnable [in] Set prefer cover art 
*/ 
 
  public void preferResultCoverart(boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_preferResultCoverart(swigCPtr, this, bEnable);
  }

/** 
*  Indicates whether a response must return only the single best result. 
*  When enabled a single full result is returned, when disabled multiple partial results may be returned. 
*  @param bEnable [in] Set single result 
*  <p><b>Remarks:</b></p> 
*  If enabled, the MusicID library selects the single best result based on the query type and input. 
*/ 
 
  public void resultSingle(boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_resultSingle(swigCPtr, this, bEnable);
  }

/** 
*  Enables or disables revision check option. 
*  @param bEnable [in] Set revision check 
* <p> 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public void revisionCheck(boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_revisionCheck(swigCPtr, this, bEnable);
  }

/** 
*  Specfies whether a response must return a range of results that begin and count at a specified values. 
*  @param resultStart  [in] Result range start value 
*  <p><b>Remarks:</b></p> 
*  This Option is useful for paging through results. 
*  <p><b>Note:</b></p> 
*  Gracenote Service enforces that the range start value must be less than or equal to the total 
*  number of results. If you specify a range start value that is greater than the total number of 
*  results, no results are returned. 
*/ 
 
  public void resultRangeStart(long resultStart) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_resultRangeStart(swigCPtr, this, resultStart);
  }

  public void resultCount(long resultCount) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_resultCount(swigCPtr, this, resultCount);
  }

/** 
* This option allows setting of a specific network interface to be used with connections made by   
* this object. Choosing which interface to use can be beneficial for systems with multiple  
* network interfaces. Without setting this option, connections will be made of the default network interface 
* as decided by the operating system. 
*  @param ipAddress [in] local IP address for the desired network interface 
*/ 
 
  public void networkInterface(String ipAddress) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_networkInterface(swigCPtr, this, ipAddress);
  }

/** 
*  Set option using option name 
*  @param option   [in] Option name 
*  @param value	[in] Option value 
*/ 
 
  public void custom(String option, String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_custom__SWIG_0(swigCPtr, this, option, value);
  }

/** 
*  Set option using option name 
*  @param option   [in] Option name 
*  @param bEnable	[in] Option enable true/false 
*/ 
 
  public void custom(String option, boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdOptions_custom__SWIG_1(swigCPtr, this, option, bEnable);
  }

}
