
package com.gracenote.gnsdk;

/** 
* The status of the channel or current identification query. 
*  As a channel processes audio or as an identification query progresses 
*  status notifications are provided via the events delegate. 
* 
*/ 
 
public enum GnMusicIdStreamIdentifyingStatus {
/** Invalid status 
* 
*/ 
 
  kStatusIdentifyingInvalid(0),
/** Identification query started 
* 
*/ 
 
  kStatusIdentifyingStarted,
/** Fingerprint generated for sample audio 
* 
*/ 
 
  kStatusIdentifyingFpGenerated,
/** Local query started for identification 
* 
*/ 
 
  kStatusIdentifyingLocalQueryStarted,
/** Local query ended for identification 
* 
*/ 
 
  kStatusIdentifyingLocalQueryEnded,
/** Online query started for identification 
* 
*/ 
 
  kStatusIdentifyingOnlineQueryStarted,
/** Online query ended for identification 
* 
*/ 
 
  kStatusIdentifyingOnlineQueryEnded,
/** Identification query ended 
* 
*/ 
 
  kStatusIdentifyingEnded;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMusicIdStreamIdentifyingStatus swigToEnum(int swigValue) {
    GnMusicIdStreamIdentifyingStatus[] swigValues = GnMusicIdStreamIdentifyingStatus.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMusicIdStreamIdentifyingStatus swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMusicIdStreamIdentifyingStatus.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamIdentifyingStatus() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamIdentifyingStatus(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamIdentifyingStatus(GnMusicIdStreamIdentifyingStatus swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

