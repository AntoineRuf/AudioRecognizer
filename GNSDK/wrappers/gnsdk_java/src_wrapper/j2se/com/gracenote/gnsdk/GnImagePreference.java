
package com.gracenote.gnsdk;

/** 
* {@link GnImagePreference} 
*/ 
 
public enum GnImagePreference {
/** 
* Retrieve exact size as specified by {@link GnImageSize} 
*/ 
 
  exact(1),
/** 
* Retrieve exact or smaller size as specified by {@link GnImageSize} 
*/ 
 
  largest,
/** 
* Retrieve exact or larger size as specified by {@link GnImageSize} 
*/ 
 
  smallest;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnImagePreference swigToEnum(int swigValue) {
    GnImagePreference[] swigValues = GnImagePreference.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnImagePreference swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnImagePreference.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnImagePreference() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnImagePreference(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnImagePreference(GnImagePreference swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

