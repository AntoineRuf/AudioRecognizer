
package com.gracenote.gnsdk;

public enum GnMusicIdStreamEvent {
  kEventInvalid(0),
  kEventBroadcastMetadataChange;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMusicIdStreamEvent swigToEnum(int swigValue) {
    GnMusicIdStreamEvent[] swigValues = GnMusicIdStreamEvent.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMusicIdStreamEvent swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMusicIdStreamEvent.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamEvent() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamEvent(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMusicIdStreamEvent(GnMusicIdStreamEvent swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

