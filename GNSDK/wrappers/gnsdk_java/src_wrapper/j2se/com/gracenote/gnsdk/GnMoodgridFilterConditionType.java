
package com.gracenote.gnsdk;

public enum GnMoodgridFilterConditionType {
  kConditionTypeInclude(1),
  kConditionTypeExclude;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMoodgridFilterConditionType swigToEnum(int swigValue) {
    GnMoodgridFilterConditionType[] swigValues = GnMoodgridFilterConditionType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMoodgridFilterConditionType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMoodgridFilterConditionType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMoodgridFilterConditionType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMoodgridFilterConditionType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMoodgridFilterConditionType(GnMoodgridFilterConditionType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

