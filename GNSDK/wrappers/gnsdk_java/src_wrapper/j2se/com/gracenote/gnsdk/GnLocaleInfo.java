
package com.gracenote.gnsdk;

/** 
* Encapsulates information about a {@link GnLocale} instance. Used where GNSDK delivers a locale description such as 
* iterating the available locales or when querying a {@link GnLocale} instance for information. 
*/ 
 
public class GnLocaleInfo extends GnObject {
  private long swigCPtr;

  protected GnLocaleInfo(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnLocaleInfo_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLocaleInfo obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLocaleInfo(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
* Construct {@link GnLocaleInfo} object with default values. 
* @param {@link GnLocaleGroup} group - locale group 
* @param {@link GnLanguage} language - locale language 
* @param {@link GnRegion} region - locale region 
* @param {@link GnDescriptor} descriptor - locale descriptor 
*/ 
 
  public GnLocaleInfo(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor) {
    this(gnsdk_javaJNI.new_GnLocaleInfo(group.swigValue(), language.swigValue(), region.swigValue(), descriptor.swigValue()), true);
  }

  public GnLocaleGroup group() {
    return GnLocaleGroup.swigToEnum(gnsdk_javaJNI.GnLocaleInfo_group(swigCPtr, this));
  }

  public GnLanguage language() {
    return GnLanguage.swigToEnum(gnsdk_javaJNI.GnLocaleInfo_language(swigCPtr, this));
  }

  public GnRegion region() {
    return GnRegion.swigToEnum(gnsdk_javaJNI.GnLocaleInfo_region(swigCPtr, this));
  }

  public GnDescriptor descriptor() {
    return GnDescriptor.swigToEnum(gnsdk_javaJNI.GnLocaleInfo_descriptor(swigCPtr, this));
  }

}
