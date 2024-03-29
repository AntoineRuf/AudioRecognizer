
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnLocaleInfo} objects 
*/ 
 
public class GnLocaleInfoIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnLocaleInfoIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLocaleInfoIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLocaleInfoIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnLocaleInfo next() throws com.gracenote.gnsdk.GnException {
    return new GnLocaleInfo(gnsdk_javaJNI.GnLocaleInfoIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnLocaleInfoIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnLocaleInfoIterator itr) {
    return gnsdk_javaJNI.GnLocaleInfoIterator_distance(swigCPtr, this, GnLocaleInfoIterator.getCPtr(itr), itr);
  }

  public GnLocaleInfoIterator(locale_info_provider provider, long pos) {
    this(gnsdk_javaJNI.new_GnLocaleInfoIterator(locale_info_provider.getCPtr(provider), provider, pos), true);
  }

}
