
package com.gracenote.gnsdk;

/************************************************************************** 
** {@link GnDspFeature} 
*/ 
 
public class GnDspFeature extends GnObject {
  private long swigCPtr;

  protected GnDspFeature(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnDspFeature_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnDspFeature obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnDspFeature(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public String featureData() {
    return gnsdk_javaJNI.GnDspFeature_featureData(swigCPtr, this);
  }

  public GnDspFeatureQuality featureQuality() {
    return GnDspFeatureQuality.swigToEnum(gnsdk_javaJNI.GnDspFeature_featureQuality(swigCPtr, this));
  }

}
