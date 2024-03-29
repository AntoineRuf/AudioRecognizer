/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.gracenote.gnsdk;

public class GnVideoChapterIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnVideoChapterIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoChapterIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoChapterIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnVideoChapterIterable(GnVideoChapterProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnVideoChapterIterable(GnVideoChapterProvider.getCPtr(provider), provider, start), true);
  }

  public GnVideoChapterIterator getIterator() {
    return new GnVideoChapterIterator(gnsdk_javaJNI.GnVideoChapterIterable_getIterator(swigCPtr, this), true);
  }

  public GnVideoChapterIterator end() {
    return new GnVideoChapterIterator(gnsdk_javaJNI.GnVideoChapterIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnVideoChapterIterable_count(swigCPtr, this);
  }

  public GnVideoChapterIterator at(long index) {
    return new GnVideoChapterIterator(gnsdk_javaJNI.GnVideoChapterIterable_at(swigCPtr, this, index), true);
  }

  public GnVideoChapterIterator getByIndex(long index) {
    return new GnVideoChapterIterator(gnsdk_javaJNI.GnVideoChapterIterable_getByIndex(swigCPtr, this, index), true);
  }

}
