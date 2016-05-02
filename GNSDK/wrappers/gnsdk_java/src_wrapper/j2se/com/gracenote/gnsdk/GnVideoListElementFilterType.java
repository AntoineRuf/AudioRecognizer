
package com.gracenote.gnsdk;

/** 
*  The list element filter type. 
*/ 
 
public enum GnVideoListElementFilterType {
/** 
*  List-based filter to include/exclude genres. 
*/ 
 
  kListElementFilterGenre(1),
/** 
*  List-based filter to include/exclude production types. 
*/ 
 
  kListElementFilterProductionType,
/** 
*  List-based filter to include/exclude serial types. 
*/ 
 
  kListElementFilterSerialType,
/** 
*  List-based filter to include/exclude origin. 
*/ 
 
  kListElementFilterOrigin;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnVideoListElementFilterType swigToEnum(int swigValue) {
    GnVideoListElementFilterType[] swigValues = GnVideoListElementFilterType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnVideoListElementFilterType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnVideoListElementFilterType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnVideoListElementFilterType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnVideoListElementFilterType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnVideoListElementFilterType(GnVideoListElementFilterType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

