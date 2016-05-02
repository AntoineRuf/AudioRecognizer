
package com.gracenote.gnsdk;

/** 
*  The video external ID type. 
*/ 
 
public enum GnVideoExternalIdType {
/** 
*  Sets a Universal Product Code (UPC) value as an external ID for a Products query. 
*  <p><b>Remarks:</b></p> 
*  Use as the external ID type parameter set with the ExternalIdTypeSet() API when 
*  providing a video UPC value for identification. 
*/ 
 
  kExternalIdTypeUPC(1),
/** 
* <p> 
*  Sets a International Standard Audiovisual Number (ISAN) code as an external ID for a Works 
*  query. 
*  <p><b>Remarks:</b></p> 
*  Use as the external ID Type parameter set with the ExternalIdTypeSet() API when 
*   providing a video ISAN value for identification. 
*/ 
 
  kExternalIdTypeISAN;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnVideoExternalIdType swigToEnum(int swigValue) {
    GnVideoExternalIdType[] swigValues = GnVideoExternalIdType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnVideoExternalIdType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnVideoExternalIdType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnVideoExternalIdType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnVideoExternalIdType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnVideoExternalIdType(GnVideoExternalIdType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

