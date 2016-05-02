
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnAlbum} iterator object 
*/ 
 
public class GnAlbumIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnAlbumIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnAlbumIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnAlbumIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnAlbumIterable(GnAlbumProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnAlbumIterable(GnAlbumProvider.getCPtr(provider), provider, start), true);
  }

  public GnAlbumIterator getIterator() {
    return new GnAlbumIterator(gnsdk_javaJNI.GnAlbumIterable_getIterator(swigCPtr, this), true);
  }

  public GnAlbumIterator end() {
    return new GnAlbumIterator(gnsdk_javaJNI.GnAlbumIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnAlbumIterable_count(swigCPtr, this);
  }

  public GnAlbumIterator at(long index) {
    return new GnAlbumIterator(gnsdk_javaJNI.GnAlbumIterable_at(swigCPtr, this, index), true);
  }

  public GnAlbumIterator getByIndex(long index) {
    return new GnAlbumIterator(gnsdk_javaJNI.GnAlbumIterable_getByIndex(swigCPtr, this, index), true);
  }

}
