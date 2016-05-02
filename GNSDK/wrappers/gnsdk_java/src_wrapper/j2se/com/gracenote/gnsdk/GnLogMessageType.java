
package com.gracenote.gnsdk;

/** 
* Logging message type. Specifies the message type when writing your own messages to the GNSDK log. 
*/ 
 
public enum GnLogMessageType {
 
 
  kLoggingMessageTypeInvalid(0),
 
 
  kLoggingMessageTypeError,
 
 
  kLoggingMessageTypeWarning,
 
 
  kLoggingMessageTypeInfo,
 
 
  kLoggingMessageTypeDebug;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLogMessageType swigToEnum(int swigValue) {
    GnLogMessageType[] swigValues = GnLogMessageType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLogMessageType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLogMessageType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLogMessageType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLogMessageType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLogMessageType(GnLogMessageType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

