
package com.gracenote.gnsdk;

/** 
*  Indicates possible data formats for the retrieved content. 
* 
*/ 
 
public enum GnLinkDataType {
/** 
* <p> 
*   Indicates an invalid data type. 
* 
*/ 
 
  kLinkDataUnknown(0),
/** 
* <p> 
*   Indicates the content buffer contains plain text data (null terminated). 
* 
*/ 
 
  kLinkDataTextPlain(1),
/** 
* <p> 
*   Indicates the content buffer contains XML data (null terminated). 
* 
*/ 
 
  kLinkDataTextXML(2),
/** 
* <p> 
*   Indicates the content buffer contains a numerical value 
*   (gnsdk_uint32_t). Unused. 
* 
*/ 
 
  kLinkDataNumber(10),
/** 
* <p> 
*   Indicates the content buffer contains jpeg image data. 
* 
*/ 
 
  kLinkDataImageJpeg(20),
/** 
* <p> 
*   Indicates the content buffer contains png image data. 
* 
*/ 
 
  kLinkDataImagePng(30),
/** 
* <p> 
*   Indicates the content buffer contains externally defined binary data. 
* 
*/ 
 
  kLinkDataImageBinary(100);

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLinkDataType swigToEnum(int swigValue) {
    GnLinkDataType[] swigValues = GnLinkDataType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLinkDataType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLinkDataType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLinkDataType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLinkDataType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLinkDataType(GnLinkDataType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

