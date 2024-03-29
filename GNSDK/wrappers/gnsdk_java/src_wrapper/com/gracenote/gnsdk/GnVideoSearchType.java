/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.gracenote.gnsdk;

public enum GnVideoSearchType {
  kSearchTypeUnknown(0),
  kSearchTypeAnchored,
  kSearchTypeDefault;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnVideoSearchType swigToEnum(int swigValue) {
    GnVideoSearchType[] swigValues = GnVideoSearchType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnVideoSearchType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnVideoSearchType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnVideoSearchType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnVideoSearchType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnVideoSearchType(GnVideoSearchType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

