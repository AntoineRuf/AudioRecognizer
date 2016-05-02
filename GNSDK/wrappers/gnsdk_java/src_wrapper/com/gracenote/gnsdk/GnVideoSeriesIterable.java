/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.gracenote.gnsdk;

public class GnVideoSeriesIterable {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnVideoSeriesIterable(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideoSeriesIterable obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideoSeriesIterable(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnVideoSeriesIterable(GnVideoSeriesProvider provider, long start) {
    this(gnsdk_javaJNI.new_GnVideoSeriesIterable(GnVideoSeriesProvider.getCPtr(provider), provider, start), true);
  }

  public GnVideoSeriesIterator getIterator() {
    return new GnVideoSeriesIterator(gnsdk_javaJNI.GnVideoSeriesIterable_getIterator(swigCPtr, this), true);
  }

  public GnVideoSeriesIterator end() {
    return new GnVideoSeriesIterator(gnsdk_javaJNI.GnVideoSeriesIterable_end(swigCPtr, this), true);
  }

  public long count() {
    return gnsdk_javaJNI.GnVideoSeriesIterable_count(swigCPtr, this);
  }

  public GnVideoSeriesIterator at(long index) {
    return new GnVideoSeriesIterator(gnsdk_javaJNI.GnVideoSeriesIterable_at(swigCPtr, this, index), true);
  }

  public GnVideoSeriesIterator getByIndex(long index) {
    return new GnVideoSeriesIterator(gnsdk_javaJNI.GnVideoSeriesIterable_getByIndex(swigCPtr, this, index), true);
  }

}
