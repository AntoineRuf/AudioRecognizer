
package com.gracenote.gnsdk;

/** 
* Configures options for {@link GnMusicIdFile} 
*/ 
 
public class GnMusicIdFileOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMusicIdFileOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdFileOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdFileOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
*  Indicates whether the MusicID-File query should be performed against local embedded databases or online. 
*  @param lookupMode		[in] One of the {@link GnLookupMode} values 
*/ 
 
  public void lookupMode(GnLookupMode lookupMode) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_lookupMode(swigCPtr, this, lookupMode.swigValue());
  }

/** 
*  Sets the lookup data value for the MusicID-File query. 
*  @param val 				[in] Set One of the {@link GnLookupData} values 
*  @param enable 			[in] True or false to enable or disable 
*/ 
 
  public void lookupData(GnLookupData val, boolean enable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_lookupData(swigCPtr, this, val.swigValue(), enable);
  }

/** 
*  Sets the batch size for the MusicID-File query. 
*  @param size				[in] set String value or one of MusicID-File Option Values that corresponds to BATCH_SIZE 
*  <p><b>Remarks:</b></p> 
*  The option value provided for batch size must be greater than zero (0). 
*/ 
 
  public void batchSize(long size) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_batchSize(swigCPtr, this, size);
  }

/** 
*  Indicates whether MusicID-File should Process the responses Online, this may reduce the amount of  
*  resources used by the client. Online processing must be allowed by your license. 
*  @param enable			[in] True or false to enable or disable 
*/ 
 
  public void onlineProcessing(boolean enable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_onlineProcessing(swigCPtr, this, enable);
  }

/** 
*  Sets the preferred language for the MusicID-File query. 
*  @param preferredLangauge	[in] One of the GNSDK language values 
*/ 
 
  public void preferResultLanguage(GnLanguage preferredLangauge) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_preferResultLanguage(swigCPtr, this, preferredLangauge.swigValue());
  }

/** 
* Use this option to specify an external identifier which MusicID-File should try to include in any responses that are returned. 
*  <p><b>Remarks:</b></p> 
* This option is currently only supported when online processing is enabled. 
*  @param preferredExternalId	[in] The name of an external identifier that should be preferred when selecting matches 
*/ 
 
  public void preferResultExternalId(String preferredExternalId) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_preferResultExternalId(swigCPtr, this, preferredExternalId);
  }

/** 
*  Sets the thread priority for a given MusicID-File query. 
*  @param threadPriority 	[in] Set one of {@link GnThreadPriority} values that corresponds to thread priority 
*  <p><b>Remarks:</b></p> 
*  The option value provided for thread priority must be one of the defined 
*  {@link GnThreadPriority} values. 
*/ 
 
  public void threadPriority(GnThreadPriority threadPriority) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_threadPriority(swigCPtr, this, threadPriority.swigValue());
  }

/** 
* This option allows setting of a specific network interface to be used with connections made by   
* this object. Choosing which interface to use can be beneficial for systems with multiple  
* network interfaces. Without setting this option, connections will be made of the default network interface 
* as decided by the operating system. 
*  @param ipAddress		[in] local IP address for the desired network interface 
*/ 
 
  public void networkInterface(String ipAddress) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_networkInterface(swigCPtr, this, ipAddress);
  }

/** 
*  General option setting for custom options 
*  @param optionKey		[in] set One of the MusicID-File Option Keys 
*  @param enable			[in] set True or false to enable or disable 
*/ 
 
  public void custom(String optionKey, boolean enable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_custom__SWIG_0(swigCPtr, this, optionKey, enable);
  }

/** 
*  Set option using option name 
*  @param option			[in] Option name 
*  @param value			[in] Option value 
*/ 
 
  public void custom(String option, String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileOptions_custom__SWIG_1(swigCPtr, this, option, value);
  }

}
