
package com.gracenote.gnsdk;

/** 
* Flags indicating rendering level for a list object, used when rendering a list to XML. 
*/ 
 
public enum GnListRenderFlags {
/** 
* Minimal information included. 
*/ 
 
  kRenderDefault,
/** 
* All information included. 
*/ 
 
  kRenderMinimal,
 
 
  kRenderFull;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnListRenderFlags swigToEnum(int swigValue) {
    GnListRenderFlags[] swigValues = GnListRenderFlags.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnListRenderFlags swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnListRenderFlags.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnListRenderFlags() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnListRenderFlags(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnListRenderFlags(GnListRenderFlags swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

