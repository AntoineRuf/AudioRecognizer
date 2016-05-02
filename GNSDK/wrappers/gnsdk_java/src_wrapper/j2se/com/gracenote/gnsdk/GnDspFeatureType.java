
package com.gracenote.gnsdk;

public enum GnDspFeatureType {
  kDspFeatureTypeInvalid(0),
  kDspFeatureTypeAFX3,
  kDspFeatureTypeChroma,
  kDspFeatureTypeCantametrixQ,
  kDspFeatureTypeCantametrixR,
  kDspFeatureTypeFEXModule,
  kDspFeatureTypeFraunhofer,
  kDspFeatureTypeFAPIQ3sVLQ,
  kDspFeatureTypeFAPIQ3sLQ,
  kDspFeatureTypeFAPIQ3sMQ,
  kDspFeatureTypeFAPIQ3sHQ,
  kDspFeatureTypeFAPIQ3sVHQ,
  kDspFeatureTypeFAPIR,
  kDspFeatureTypeNanoFAPIQ,
  kDspFeatureTypeMicroFAPIQ;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnDspFeatureType swigToEnum(int swigValue) {
    GnDspFeatureType[] swigValues = GnDspFeatureType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnDspFeatureType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnDspFeatureType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnDspFeatureType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnDspFeatureType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnDspFeatureType(GnDspFeatureType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

