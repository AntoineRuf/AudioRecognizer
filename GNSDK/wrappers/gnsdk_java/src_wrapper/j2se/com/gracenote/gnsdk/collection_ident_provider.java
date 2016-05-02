
package com.gracenote.gnsdk;

public class collection_ident_provider {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected collection_ident_provider(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(collection_ident_provider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_collection_ident_provider(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public collection_ident_provider() {
    this(gnsdk_javaJNI.new_collection_ident_provider(), true);
  }

  public GnPlaylistIdentifier getData(long pos) {
    return new GnPlaylistIdentifier(gnsdk_javaJNI.collection_ident_provider_getData(swigCPtr, this, pos), true);
  }

  public long count() {
    return gnsdk_javaJNI.collection_ident_provider_count(swigCPtr, this);
  }

}
