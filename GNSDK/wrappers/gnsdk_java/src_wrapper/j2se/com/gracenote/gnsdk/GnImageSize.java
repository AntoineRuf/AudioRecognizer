
package com.gracenote.gnsdk;

/** 
* Image size 
*/ 
 
public enum GnImageSize {
 
 
  kImageSizeUnknown(0),
 
 
  kImageSize75,
 
 
  kImageSize110,
 
 
  kImageSize170,
 
 
  kImageSize220,
 
 
  kImageSize300,
 
 
  kImageSize450,
 
 
  kImageSize720,
 
 
  kImageSize1080,
 
 
  kImageSizeThumbnail(kImageSize75),
 
 
  kImageSizeSmall(kImageSize170),
 
 
  kImageSizeMedium(kImageSize450),
 
 
  kImageSizeLarge(kImageSize720),
 
 
  kImageSizeXLarge(kImageSize1080);

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnImageSize swigToEnum(int swigValue) {
    GnImageSize[] swigValues = GnImageSize.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnImageSize swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnImageSize.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnImageSize() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnImageSize(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnImageSize(GnImageSize swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

