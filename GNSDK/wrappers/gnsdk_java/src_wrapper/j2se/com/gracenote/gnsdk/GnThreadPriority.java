
package com.gracenote.gnsdk;

/** 
* Thread priority values for GNSDK multi-threaded functionality such as  MusicID-File. 
*/ 
 
public enum GnThreadPriority {
/** 
* Use of default thread priority. 
*/ 
 
  kThreadPriorityInvalid(0),
/** 
* Use idle thread priority. 
*/ 
 
  kThreadPriorityDefault,
/** 
* Use low thread priority (default). 
*/ 
 
  kThreadPriorityIdle,
/** 
* Use normal thread priority. 
*/ 
 
  kThreadPriorityLow,
/** 
* Use high thread priority. 
*/ 
 
  kThreadPriorityNormal,
 
 
  kThreadPriorityHigh;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnThreadPriority swigToEnum(int swigValue) {
    GnThreadPriority[] swigValues = GnThreadPriority.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnThreadPriority swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnThreadPriority.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnThreadPriority() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnThreadPriority(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnThreadPriority(GnThreadPriority swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

