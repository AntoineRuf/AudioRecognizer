
package com.gracenote.gnsdk;

/** 
* Configures options for {@link GnMusicIdStream} 
*/ 
 
public class GnMusicIdStreamOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMusicIdStreamOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdStreamOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdStreamOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
*  Specifies whether identification should be performed against local embedded databases or online. 
*  @param lookupMode  [in] One of the {@link GnLookupMode} values 
*/ 
 
  public void lookupMode(GnLookupMode lookupMode) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_lookupMode(swigCPtr, this, lookupMode.swigValue());
  }

/** 
*  Specifies which data should be included in the response 
*  @param val 		[in] Set One of the {@link GnLookupData} values 
*  @param enable 	[in] True or false to enable or disable 
*/ 
 
  public void lookupData(GnLookupData val, boolean enable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_lookupData(swigCPtr, this, val.swigValue(), enable);
  }

/** 
*  @deprecated To set language provide appropriate {@link GnLocale} object with {@link GnMusicIdStream} constructor 
*  @param preferredLanguage		[in] preferred language for result 
*/ 
 
  public void preferResultLanguage(GnLanguage preferredLanguage) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_preferResultLanguage(swigCPtr, this, preferredLanguage.swigValue());
  }

/** 
* Specifies preference for results that contain the provided external identifier 
* <p><b>Remarks:</b></p> 
* This option is currently only supported when online processing is enabled and single 
* result is specified. 
* @param preferredExternalId 	[in] The name of an external identifier that should be preferred when selecting matches 
*/ 
 
  public void preferResultExternalId(String preferredExternalId) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_preferResultExternalId(swigCPtr, this, preferredExternalId);
  }

/** 
*  Specifies preference for results that have cover art associated 
*  @param bEnable 	[in] Set prefer cover art. 
*/ 
 
  public void preferResultCoverart(boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_preferResultCoverart(swigCPtr, this, bEnable);
  }

/** 
*  Specifies whether a response must return only the single best result. 
*  When enabled a single full result is returned, when disabled multiple partial results may be returned. 
*  @param bEnable 	[in] Option, default is true. True to enable, false to disable. 
*/ 
 
  public void resultSingle(boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_resultSingle(swigCPtr, this, bEnable);
  }

/** 
*  Specifies whether a response must return a range of results that begin at the specified values 
*  @param resultStart  [in] Result range start value 
*  <p><b>Remarks:</b></p> 
*  This Option is useful for paging through results. 
*  <p><b>Note:</b></p> 
*  Gracenote Service enforces that the range start value must be less than or equal to the total 
*  number of results. If you specify a range start value that is greater than the total number of 
*  results, no results are returned. 
*/ 
 
  public void resultRangeStart(long resultStart) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_resultRangeStart(swigCPtr, this, resultStart);
  }

/** 
* Specifies the number of results to return in the response 
* @param resultCount 	[in] Number of results 
* <p> 
*/ 
 
  public void resultCount(long resultCount) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_resultCount(swigCPtr, this, resultCount);
  }

/** 
* This option allows setting of a specific network interface to be used with connections made by   
* this object. Choosing which interface to use can be beneficial for systems with multiple  
* network interfaces. Without setting this option, connections will be made of the default network interface 
* as decided by the operating system. 
*  @param ipAddress [in] local IP address for the desired network interface 
*/ 
 
  public void networkInterface(String ipAddress) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_networkInterface(swigCPtr, this, ipAddress);
  }

/** 
*  General option setting for custom string options 
*  @param optionKey   [in] Option name 
*  @param value	   [in] Option value 
*/ 
 
  public void custom(String optionKey, String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdStreamOptions_custom(swigCPtr, this, optionKey, value);
  }

}
