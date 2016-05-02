
package com.gracenote.gnsdk;

/** 
*  License submission options 
*  When your app allocates an SDK Manager object (GnManager) it passes the license data you obtained from GSS. 
*  Your license determines the content you can access from the Gracenote service 
*  License data can be submitted in different ways, as these enums indicate 
*/ 
 
public enum GnLicenseInputMode {
/** 
* Submit license content as string 
*/ 
 
  kLicenseInputModeInvalid(0),
/** 
* Submit license content in file 
*/ 
 
  kLicenseInputModeString,
/** 
* Submit license content from stdin 
*/ 
 
  kLicenseInputModeFilename,
 
 
  kLicenseInputModeStandardIn;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLicenseInputMode swigToEnum(int swigValue) {
    GnLicenseInputMode[] swigValues = GnLicenseInputMode.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLicenseInputMode swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLicenseInputMode.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLicenseInputMode() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLicenseInputMode(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLicenseInputMode(GnLicenseInputMode swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

