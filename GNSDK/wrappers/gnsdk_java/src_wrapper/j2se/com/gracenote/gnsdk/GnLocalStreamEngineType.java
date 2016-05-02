
package com.gracenote.gnsdk;

public enum GnLocalStreamEngineType {
  kLocalStreamEngineInvalid(0),
  kLocalStreamEngineMMap,
  kLocalStreamEngineInMemory;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLocalStreamEngineType swigToEnum(int swigValue) {
    GnLocalStreamEngineType[] swigValues = GnLocalStreamEngineType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLocalStreamEngineType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLocalStreamEngineType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLocalStreamEngineType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLocalStreamEngineType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLocalStreamEngineType(GnLocalStreamEngineType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

