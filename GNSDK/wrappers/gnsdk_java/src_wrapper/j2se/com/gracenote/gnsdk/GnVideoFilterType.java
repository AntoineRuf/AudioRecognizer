
package com.gracenote.gnsdk;

/** 
*  The video filter type. 
*/ 
 
public enum GnVideoFilterType {
/** 
*  Filter for Season numbers; not list-based. 
*/ 
 
  kFilterSeasonNumber(1),
/** 
*  Filter for season episode numbers; not list-based. 
*/ 
 
  kFilterSeasonEpisodeNumber,
/** 
*  Filter for series episode numbers; not list-based. 
*/ 
 
  kFilterSeriesEpisodeNumber;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnVideoFilterType swigToEnum(int swigValue) {
    GnVideoFilterType[] swigValues = GnVideoFilterType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnVideoFilterType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnVideoFilterType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnVideoFilterType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnVideoFilterType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnVideoFilterType(GnVideoFilterType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

