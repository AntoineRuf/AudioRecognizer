
package com.gracenote.gnsdk;

public enum GnMoodgridCoordinateType {
  kMoodgridCoordinateTopLeft,
  kMoodgridCoordinateBottomLeft;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMoodgridCoordinateType swigToEnum(int swigValue) {
    GnMoodgridCoordinateType[] swigValues = GnMoodgridCoordinateType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMoodgridCoordinateType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMoodgridCoordinateType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMoodgridCoordinateType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMoodgridCoordinateType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMoodgridCoordinateType(GnMoodgridCoordinateType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

