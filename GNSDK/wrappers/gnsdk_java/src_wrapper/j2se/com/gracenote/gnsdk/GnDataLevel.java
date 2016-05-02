
package com.gracenote.gnsdk;

/** 
* Metadata level enums 
* Level of granularity of the metadata 
* Eg: Genre 'Rock' (level 1) is less granular than 'Soft Rock' (level 2) 
* Not all 4 levels are supported for all applicable metadata. 
*/ 
 
public enum GnDataLevel {
 
 
  kDataLevelInvalid(0),
 
 
  kDataLevel_1(1),
 
 
  kDataLevel_2,
 
 
  kDataLevel_3,
 
 
  kDataLevel_4;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnDataLevel swigToEnum(int swigValue) {
    GnDataLevel[] swigValues = GnDataLevel.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnDataLevel swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnDataLevel.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnDataLevel() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnDataLevel(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnDataLevel(GnDataLevel swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

