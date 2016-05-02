
package com.gracenote.gnsdk;

/** 
*  Status codes passed to the gnsdk_musicidfile_callback_status_fn() callback. 
* 
*/ 
 
public enum GnMusicIdFileCallbackStatus {
  kMusicIdFileCallbackStatusProcessingBegin(0x100),
  kMusicIdFileCallbackStatusFileInfoQuery(0x150),
  kMusicIdFileCallbackStatusProcessingComplete(0x199),
  kMusicIdFileCallbackStatusProcessingError(0x299),
  kMusicIdFileCallbackStatusError(0x999);

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMusicIdFileCallbackStatus swigToEnum(int swigValue) {
    GnMusicIdFileCallbackStatus[] swigValues = GnMusicIdFileCallbackStatus.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMusicIdFileCallbackStatus swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMusicIdFileCallbackStatus.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileCallbackStatus() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileCallbackStatus(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileCallbackStatus(GnMusicIdFileCallbackStatus swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

