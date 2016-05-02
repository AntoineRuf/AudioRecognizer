
package com.gracenote.gnsdk;

/** 
** Rendering options (e.g., JSON, XML) 
*/ 
 
public class GnRenderOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnRenderOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnRenderOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnRenderOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
* Construct {@link GnRenderOptions} object 
*/ 
 
  public GnRenderOptions() {
    this(gnsdk_javaJNI.new_GnRenderOptions(), true);
  }

/** 
* Specify render format of XML 
* @return Render options object 
*/ 
 
  public GnRenderOptions xml() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_xml(swigCPtr, this), false);
  }

/** 
* Specify render format of JSON 
* @return Render options object 
*/ 
 
  public GnRenderOptions json() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_json(swigCPtr, this), false);
  }

  public GnRenderOptions standard() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_standard(swigCPtr, this), false);
  }

/** 
* Specify rendered output include Credits 
* @return Render options object 
*/ 
 
  public GnRenderOptions credits() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_credits(swigCPtr, this), false);
  }

/** 
* Specify rendered output include Sortable information 
* @return Render options object 
*/ 
 
  public GnRenderOptions sortable() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_sortable(swigCPtr, this), false);
  }

  public GnRenderOptions serialGdos() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_serialGdos(swigCPtr, this), false);
  }

/** 
* Specify rendered output include Product IDs 
* @return Render options object 
*/ 
 
  public GnRenderOptions productIds() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_productIds(swigCPtr, this), false);
  }

/** 
* Specify rendered output include raw TUIs 
* @return Render options object 
*/ 
 
  public GnRenderOptions rawTuis() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_rawTuis(swigCPtr, this), false);
  }

/** 
* Specify rendered output include Gracenote IDs 
* @return Render options object 
*/ 
 
  public GnRenderOptions gnIds() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_gnIds(swigCPtr, this), false);
  }

  public GnRenderOptions gnUIds() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_gnUIds(swigCPtr, this), false);
  }

/** 
* Specify rendered output include Genre descriptors for specified level 
* @param level	[in] Data level 
* @return Render options object 
*/ 
 
  public GnRenderOptions genres(GnDataLevel level) {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_genres(swigCPtr, this, level.swigValue()), false);
  }

  public GnRenderOptions DefaultOptions() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_DefaultOptions(swigCPtr, this), false);
  }

  public GnRenderOptions full() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_full(swigCPtr, this), false);
  }

/** 
* Clear render options 
* @return Render options object 
*/ 
 
  public GnRenderOptions clear() {
    return new GnRenderOptions(gnsdk_javaJNI.GnRenderOptions_clear(swigCPtr, this), false);
  }

}
