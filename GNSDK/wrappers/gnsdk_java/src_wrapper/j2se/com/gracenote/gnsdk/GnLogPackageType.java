
package com.gracenote.gnsdk;

/** 
* Enum specifying logging packages for the purpose of communicating 
* those packages to the logging sub-system. 
*/ 
 
public enum GnLogPackageType {
 
 
  kLogPackageAll(1),
 
 
  kLogPackageAllGNSDK,
 
 
  kLogPackageManager,
 
 
  kLogPackageMusicID,
 
 
  kLogPackageMusicIDFile,
 
 
  kLogPackageMusicIDStream,
 
 
  kLogPackageMusicIdMatch,
 
 
  kLogPackageVideoID,
 
 
  kLogPackageLink,
 
 
  kLogPackageDsp,
 
 
  kLogPackageAcr,
 
 
  kLogPackageEPG,
 
 
  kLogPackageSubmit,
 
 
  kLogPackageTaste,
 
 
  kLogPackageRhythm,
 
 
  kLogPackagePlaylist,
 
 
  kLogPackageStorageSqlite,
 
 
  kLogPackageStorageQNX,
 
 
  kLogPackageLookupLocal,
 
 
  kLogPackageLookupFPLocal,
 
 
  kLogPackageLookupLocalStream,
 
 
  kLogPackageEDBInstall,
 
 
  kLogPackageMoodGrid,
 
 
  kLogPackageCorrelates,
 
 
  kLogPackageInternal;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLogPackageType swigToEnum(int swigValue) {
    GnLogPackageType[] swigValues = GnLogPackageType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLogPackageType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLogPackageType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLogPackageType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLogPackageType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLogPackageType(GnLogPackageType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

