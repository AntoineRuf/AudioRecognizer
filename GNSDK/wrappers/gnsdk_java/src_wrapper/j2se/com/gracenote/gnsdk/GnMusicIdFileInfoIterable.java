
package com.gracenote.gnsdk;

/** 
* Provides access to {@link GnMusicIdFileInfo} iterator object 
*/ 
 
public class GnMusicIdFileInfoIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMusicIdFileInfoIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdFileInfoIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdFileInfoIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnMusicIdFileInfoIterable(musicid_file_info_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnMusicIdFileInfoIterable(musicid_file_info_provider.getCPtr(provider), provider, start), true);
  }

  public GnMusicIdFileInfoIterator getIterator() {
    return new GnMusicIdFileInfoIterator(gnsdk_javaJNI.GnMusicIdFileInfoIterable_getIterator(swigCPtr, this), true);
  }

  public GnMusicIdFileInfoIterator end() {
    return new GnMusicIdFileInfoIterator(gnsdk_javaJNI.GnMusicIdFileInfoIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnMusicIdFileInfoIterable_count(swigCPtr, this);
  }

  public GnMusicIdFileInfoIterator at(long index) {
    return new GnMusicIdFileInfoIterator(gnsdk_javaJNI.GnMusicIdFileInfoIterable_at(swigCPtr, this, index), true);
  }

  public GnMusicIdFileInfoIterator getByIndex(long index) {
    return new GnMusicIdFileInfoIterator(gnsdk_javaJNI.GnMusicIdFileInfoIterable_getByIndex(swigCPtr, this, index), true);
  }

}
