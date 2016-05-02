
package com.gracenote.gnsdk;

/** 
* Gracenote user registration mode 
*/ 
 
public enum GnUserRegisterMode {
/** 
* Register a user via a netowrk connection with Gracenote Service. A user 
* must be registered online before any online queries can be made against 
* Gracenote Service. 
*/ 
 
  kUserRegisterModeOnline(1),
/** 
* Register a user for local use only. User's registered locally can only 
* perform queries against local databases and not against Gracenote 
* Service. 
*/ 
 
  kUserRegisterModeLocalOnly;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnUserRegisterMode swigToEnum(int swigValue) {
    GnUserRegisterMode[] swigValues = GnUserRegisterMode.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnUserRegisterMode swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnUserRegisterMode.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnUserRegisterMode() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnUserRegisterMode(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnUserRegisterMode(GnUserRegisterMode swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

