
package com.gracenote.gnsdk;

/** 
* Fingerprint algorithm type. 
*/ 
 
public enum GnFingerprintType {
/** 
* Invalid fingerprint type 
*/ 
 
  kFingerprintTypeInvalid(0),
/** 
* Specifies a fingerprint data type for generating fingerprints used with MusicID-File. 
* <p><b>Remarks:</b></p> 
* A MusicID-File fingerprint is a fingerprint of the beginning 16 seconds of the file. 
* <p><b>Note:</b></p> 
* Do not design your application to submit only 16 seconds of a file; the 
* application must submit data until GNSDK indicates it has received enough input. 
* Use this fingerprint type when identifying audio from a file source (MusicID-File). 
*/ 
 
  kFingerprintTypeFile,
/** 
*  Specifies a fingerprint used for identifying an ~3-second excerpt from an audio stream. 
*  Use this fingerprint type when identifying a continuous stream of audio data and when retrieving 
*  Track Match Position values. The fingerprint represents a 
*  specific point in time of the audio stream as denoted by the audio provided when the fingerprint 
*  is generated. 
*  <p><b>Note:</b></p> 
*  Do not design your application to submit only 3 seconds of audio data; the 
*  application must submit audio data until GNSDK indicates it has received enough input. 
*  You must use this fingerprint or its 6-second counterpart when generating results where match 
*  position is required. 
*  The usage of this type of fingerprint must be configured to your specific User ID, otherwise queries 
*  of this type will not succeed. 
*/ 
 
  kFingerprintTypeStream3,
/** 
*  Specifies a fingerprint used for identifying an ~6-second excerpt from and audio stream. 
*  This is the same as kFingerprintTypeStream3 but requires more audio data to generate 
*  but could be more accurate. 
*  For additional notes see kFingerprintTypeStream3. 
*/ 
 
  kFingerprintTypeStream6,
/** 
* @deprecated NB: This key has been marked as deprecated and will be removed from the next major release. 
*      Use kFingerprintTypeFile instead. 
*/ 
 
  kFingerprintTypeCMX,
/** 
* @deprecated NB: This key has been marked as deprecated and will be removed from the next major release. 
*      Use kFingerprintTypeStream3 or kFingerprintTypeStream6 instead. 
*/ 
 
  kFingerprintTypeGNFPX;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnFingerprintType swigToEnum(int swigValue) {
    GnFingerprintType[] swigValues = GnFingerprintType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnFingerprintType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnFingerprintType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnFingerprintType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnFingerprintType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnFingerprintType(GnFingerprintType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

