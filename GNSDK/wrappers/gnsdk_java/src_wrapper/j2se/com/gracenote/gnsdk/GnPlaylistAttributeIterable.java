
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: Provides access to attribute iterator object 
*/ 
 
public class GnPlaylistAttributeIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnPlaylistAttributeIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistAttributeIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistAttributeIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnPlaylistAttributeIterable(attribute_provider provider, long start) {
    this(gnsdk_javaJNI.new_GnPlaylistAttributeIterable(attribute_provider.getCPtr(provider), provider, start), true);
  }

  public GnPlaylistAttributeIterator getIterator() {
    return new GnPlaylistAttributeIterator(gnsdk_javaJNI.GnPlaylistAttributeIterable_getIterator(swigCPtr, this), true);
  }

  public GnPlaylistAttributeIterator end() {
    return new GnPlaylistAttributeIterator(gnsdk_javaJNI.GnPlaylistAttributeIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnPlaylistAttributeIterable_count(swigCPtr, this);
  }

  public GnPlaylistAttributeIterator at(long index) {
    return new GnPlaylistAttributeIterator(gnsdk_javaJNI.GnPlaylistAttributeIterable_at(swigCPtr, this, index), true);
  }

  public GnPlaylistAttributeIterator getByIndex(long index) {
    return new GnPlaylistAttributeIterator(gnsdk_javaJNI.GnPlaylistAttributeIterable_getByIndex(swigCPtr, this, index), true);
  }

}
