
package com.gracenote.gnsdk;

public enum GnMoodgridFilterListType {
  kMoodgridListTypeGenre(1),
  kMoodgridListTypeOrigins,
  kMoodgridListTypeEras;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMoodgridFilterListType swigToEnum(int swigValue) {
    GnMoodgridFilterListType[] swigValues = GnMoodgridFilterListType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMoodgridFilterListType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMoodgridFilterListType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMoodgridFilterListType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMoodgridFilterListType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMoodgridFilterListType(GnMoodgridFilterListType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

