
package com.gracenote.gnsdk;

/** 
* Iterate through a collection of {@link GnAlbum} objects 
*/ 
 
public class GnAlbumIterator {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnAlbumIterator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnAlbumIterator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnAlbumIterator(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnAlbum __ref__() throws com.gracenote.gnsdk.GnException {
    return new GnAlbum(gnsdk_javaJNI.GnAlbumIterator___ref__(swigCPtr, this), false);
  }

  public GnAlbum next() throws com.gracenote.gnsdk.GnException {
    return new GnAlbum(gnsdk_javaJNI.GnAlbumIterator_next(swigCPtr, this), true);
  }

  public boolean hasNext() {
    return gnsdk_javaJNI.GnAlbumIterator_hasNext(swigCPtr, this);
  }

  public long distance(GnAlbumIterator itr) {
    return gnsdk_javaJNI.GnAlbumIterator_distance(swigCPtr, this, GnAlbumIterator.getCPtr(itr), itr);
  }

  public GnAlbumIterator(GnAlbumProvider provider, long pos) {
    this(gnsdk_javaJNI.new_GnAlbumIterator(GnAlbumProvider.getCPtr(provider), provider, pos), true);
  }

}
