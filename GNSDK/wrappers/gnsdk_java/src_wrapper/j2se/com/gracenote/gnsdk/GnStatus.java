
package com.gracenote.gnsdk;

/** 
*  Indicates messages that can be received in status callbacks. 
* 
*/ 
 
public enum GnStatus {
/** 
* Status unknown. 
* 
*/ 
 
  kStatusUnknown(0),
/** 
* Issued once per application function call, at the beginning of the call; percent_complete = 0. 
* 
*/ 
 
  kStatusBegin,
/** 
* Issued roughly 10 times per application function call; percent_complete values between 1-100. 
* 
*/ 
 
  kStatusProgress,
/** 
* Issued once per application function call, at the end of the call; percent_complete = 100. 
* 
*/ 
 
  kStatusComplete,
/** 
* Issued when an error is encountered. If sent, call #gnsdk_manager_error_info(). 
* 
*/ 
 
  kStatusErrorInfo,
/** 
* Issued when connecting to network. 
* 
*/ 
 
  kStatusConnecting,
/** 
* Issued when uploading. 
* 
*/ 
 
  kStatusSending,
/** 
* Issued when downloading. 
* 
*/ 
 
  kStatusReceiving,
/** 
* Issued when disconnected from network. 
* 
*/ 
 
  kStatusDisconnected,
/** 
* Issued when reading from storage. 
* 
*/ 
 
  kStatusReading,
/** 
* Issued when writing to storage. 
* 
*/ 
 
  kStatusWriting,
/** 
* Issued when transaction/query is cancelled 
* 
*/ 
 
  kStatusCancelled;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnStatus swigToEnum(int swigValue) {
    GnStatus[] swigValues = GnStatus.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnStatus swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnStatus.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnStatus() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnStatus(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnStatus(GnStatus swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

