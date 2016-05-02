
package com.gracenote.gnsdk;

/** 
*  The TOC Flag type. 
*/ 
 
public enum GnVideoTOCFlag {
/** 
*  Generally recommended flag to use when setting a video TOC. 
*  <p><b>Remarks:</b></p> 
*  Use this flag for the TOC flag parameter that is set with the 
*  FindProducts() API, for all general cases; this includes when using the Gracenote 
*  Video Thin Client component to produce TOC strings. 
*  For cases when other VideoID TOC flags seem necessary, contact Gracenote for guidance on setting 
*  the correct flag. 
*/ 
 
  kTOCFlagDefault(0),
/** 
*  Flag to indicate a given simple video TOC is from a PAL (Phase Alternating Line) disc. 
*  <p><b>Remarks:</b></p> 
*  Use this flag only when directed to by Gracenote. Only special video TOCs that are provided by 
*  Gracenote and external to the 
*  GNSDK may require this flag. 
*/ 
 
  kTOCFlagPal,
/** 
*  Flag to indicate a given simple video TOC contains angle data. 
*  <p><b>Remarks:</b></p> 
*  Use this flag only if Gracenote directs you to. Only special video TOCs that Gracenote provides 
*  and that are external to the GNSDK may require this flag. 
*/ 
 
  kTOCFlagAngles;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnVideoTOCFlag swigToEnum(int swigValue) {
    GnVideoTOCFlag[] swigValues = GnVideoTOCFlag.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnVideoTOCFlag swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnVideoTOCFlag.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnVideoTOCFlag() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnVideoTOCFlag(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnVideoTOCFlag(GnVideoTOCFlag swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

