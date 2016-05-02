
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnRenderOptions
* Rendering options (e.g., JSON, XML)
*/
public class GnRenderOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnRenderOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnRenderOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnRenderOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnRenderOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
* Construct GnRenderOptions object
*/
  public GnRenderOptions() : this(gnsdk_csharp_marshalPINVOKE.new_GnRenderOptions(), true) {
  }

/**
* Specify render format of XML
* @return Render options object
*/
  public GnRenderOptions Xml() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Xml(swigCPtr), false);
    return ret;
  }

/**
* Specify render format of JSON
* @return Render options object
*/
  public GnRenderOptions Json() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Json(swigCPtr), false);
    return ret;
  }

  public GnRenderOptions Standard() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Standard(swigCPtr), false);
    return ret;
  }

/**
* Specify rendered output include Credits
* @return Render options object
*/
  public GnRenderOptions Credits() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Credits(swigCPtr), false);
    return ret;
  }

/**
* Specify rendered output include Sortable information
* @return Render options object
*/
  public GnRenderOptions Sortable() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Sortable(swigCPtr), false);
    return ret;
  }

  public GnRenderOptions SerialGdos() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_SerialGdos(swigCPtr), false);
    return ret;
  }

/**
* Specify rendered output include Product IDs
* @return Render options object
*/
  public GnRenderOptions ProductIds() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_ProductIds(swigCPtr), false);
    return ret;
  }

/**
* Specify rendered output include raw TUIs
* @return Render options object
*/
  public GnRenderOptions RawTuis() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_RawTuis(swigCPtr), false);
    return ret;
  }

/**
* Specify rendered output include Gracenote IDs
* @return Render options object
*/
  public GnRenderOptions GnIds() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_GnIds(swigCPtr), false);
    return ret;
  }

  public GnRenderOptions GnUIds() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_GnUIds(swigCPtr), false);
    return ret;
  }

/**
* Specify rendered output include Genre descriptors for specified level
* @param level	[in] Data level
* @return Render options object
*/
  public GnRenderOptions Genres(GnDataLevel level) {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Genres(swigCPtr, (int)level), false);
    return ret;
  }

  public GnRenderOptions Default() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Default(swigCPtr), false);
    return ret;
  }

  public GnRenderOptions Full() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Full(swigCPtr), false);
    return ret;
  }

/**
* Clear render options
* @return Render options object
*/
  public GnRenderOptions Clear() {
    GnRenderOptions ret = new GnRenderOptions(gnsdk_csharp_marshalPINVOKE.GnRenderOptions_Clear(swigCPtr), false);
    return ret;
  }

}

}
