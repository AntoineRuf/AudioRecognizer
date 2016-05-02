
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnAsset} objects 
*/ 
 
public class GnAssetIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnAssetIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnAssetIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnAssetIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnAsset __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnAsset(gnsdk_javaJNI.GnAssetIterator___ref__(swigCPtr, this), false);
  }

  public GnAsset next() throws com.gracenote.gnsdk.GnException {
    return new GnAsset(gnsdk_javaJNI.GnAssetIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnAssetIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnAssetIterator itr) {
    return gnsdk_javaJNI.GnAssetIterator_distance(swigCPtr, this, GnAssetIterator.getCPtr(itr), itr);
  }

  public GnAssetIterator(GnAssetProvider provider, long pos) {
    this(gnsdk_javaJNI.new_GnAssetIterator(GnAssetProvider.getCPtr(provider), provider, pos), true);
  }

}
