
package com.gracenote.gnsdk;

/************************************************************************** 
** {@link GnDsp} 
*/ 
 
public class GnDsp extends GnObject {
  private long swigCPtr;

  protected GnDsp(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnDsp_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnDsp obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnDsp(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
* Initializes the DSP library. 
* @param user set user 
* @param featureType The kind of DSP feature, for example a fingerprint. 
* @param audioSampleRate The source audio sample rate. 
* @param audioSampleSize The source audio sample size. 
* @param audioChannels	The source audio channels 
*/ 
 
  public GnDsp(GnUser user, GnDspFeatureType featureType, long audioSampleRate, long audioSampleSize, long audioChannels) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnDsp(GnUser.getCPtr(user), user, featureType.swigValue(), audioSampleRate, audioSampleSize, audioChannels), true);
  }

/** 
*  Retrieves {@link GnDsp} SDK version string. 
*  This API can be called at any time, after getting instance of {@link GnManager} successfully. The returned 
*  string is a constant. Do not attempt to modify or delete. 
*  Example: 1.2.3.123 (Major.Minor.Improvement.Build) 
*  Major: New functionality 
*  Minor: New or changed features 
*  Improvement: Improvements and fixes 
*  Build: Internal build number 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnDsp_version();
  }

/** 
*  Retrieves the {@link GnDsp} SDK's build date string. 
*  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC 
*  <p><b>Remarks:</b></p> 
*  This API can be called at any time, after getting instance of {@link GnManager} successfully. The returned 
* string is a constant. Do not attempt to modify or delete. 
*  Example build date string: 2008-02-12 00:41 UTC 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnDsp_buildDate();
  }

/** 
* Use this method to feed audio in to {@link GnDsp} until it returns true 
* @param audioData The source audio 
* @param audioDataBytes The source audio size in bytes 
* @return false : {@link GnDsp} needs more audio, true : {@link GnDsp} received enough audio to generate required feature 
*/ 
 
  public boolean featureAudioWrite(byte[] audioData, long audioDataBytes) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnDsp_featureAudioWrite(swigCPtr, this, audioData, audioDataBytes);
  }

/** 
* Indicates the the DSP feature has reached the end of the write operation. 
*/ 
 
  public void featureEndOfAudioWrite() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnDsp_featureEndOfAudioWrite(swigCPtr, this);
  }

/** 
* Retrieve {@link GnDspFeature} 
* @return {@link GnDspFeature} 
*/ 
 
  public GnDspFeature featureRetrieve() throws com.gracenote.gnsdk.GnException {
    return new GnDspFeature(gnsdk_javaJNI.GnDsp_featureRetrieve(swigCPtr, this), true);
  }

}
