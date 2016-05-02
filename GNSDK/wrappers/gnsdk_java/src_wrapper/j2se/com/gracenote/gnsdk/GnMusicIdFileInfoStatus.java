
package com.gracenote.gnsdk;

/** 
*  The status value of the current query. 
* 
*/ 
 
public enum GnMusicIdFileInfoStatus {
/** 
* FileInfo has not been processed. 
* 
*/ 
 
  kMusicIdFileInfoStatusUnprocessed(0),
/** 
* FileInfo is currently being processed. 
* 
*/ 
 
  kMusicIdFileInfoStatusProcessing(1),
/** 
* An error occurred while processing the FileInfo. 
* 
*/ 
 
  kMusicIdFileInfoStatusError(2),
/** 
* No results were found for FileInfo. 
* 
*/ 
 
  kMusicIdFileInfoStatusResultNone(3),
/** 
* Single preferred response available for FileInfo. 
* 
*/ 
 
  kMusicIdFileInfoStatusResultSingle(4),
/** 
* All retrieved results available for FileInfo. 
* 
*/ 
 
  kMusicIdFileInfoStatusResultAll(5);

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMusicIdFileInfoStatus swigToEnum(int swigValue) {
    GnMusicIdFileInfoStatus[] swigValues = GnMusicIdFileInfoStatus.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMusicIdFileInfoStatus swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMusicIdFileInfoStatus.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileInfoStatus() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileInfoStatus(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileInfoStatus(GnMusicIdFileInfoStatus swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

