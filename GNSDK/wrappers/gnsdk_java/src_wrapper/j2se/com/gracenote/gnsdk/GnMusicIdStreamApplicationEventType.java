
package com.gracenote.gnsdk;

/** No event 
* 
*/ 
 
public enum GnMusicIdStreamApplicationEventType {
/** Metadata change event 
* 
*/ 
 
  kApplicationEventNone(0),
/** Broadcast channel change event 
* 
*/ 
 
  kApplicationEventMetadataChange,
/** Broadcast pause event 
* 
*/ 
 
  kApplicationEventBroadcastChange,
/** Broadcast resume event 
* 
*/ 
 
  kApplicationEventPause,
 
 
  kApplicationEventResume;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMusicIdStreamApplicationEventType swigToEnum(int swigValue) {
    GnMusicIdStreamApplicationEventType[] swigValues = GnMusicIdStreamApplicationEventType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMusicIdStreamApplicationEventType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMusicIdStreamApplicationEventType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamApplicationEventType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamApplicationEventType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamApplicationEventType(GnMusicIdStreamApplicationEventType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

