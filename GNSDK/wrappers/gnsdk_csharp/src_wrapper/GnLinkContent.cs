
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* GnLinkContent
*/
public class GnLinkContent : GnObject {
  private HandleRef swigCPtr;

  internal GnLinkContent(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnLinkContent_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLinkContent obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLinkContent() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLinkContent(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

      public byte[] DataBuffer
      {
        get
        {
          byte[] dataBytes = new byte[DataSize];
          Marshal.Copy((IntPtr)ContentData, dataBytes, 0, (int)DataSize);
          return dataBytes;
        }
      }
    
  public GnLinkContent(SWIGTYPE_p_unsigned_char contentData, uint dataSize, GnLinkContentType contentType, GnLinkDataType dataType) : this(gnsdk_csharp_marshalPINVOKE.new_GnLinkContent(SWIGTYPE_p_unsigned_char.getCPtr(contentData), dataSize, (int)contentType, (int)dataType), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieves content data buffer size
*/
  public uint DataSize {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnLinkContent_DataSize_get(swigCPtr);
      return ret;
    } 
  }

/**
* Retrieves content data type
*/
  public GnLinkDataType DataType {
    get {
      GnLinkDataType ret = (GnLinkDataType)gnsdk_csharp_marshalPINVOKE.GnLinkContent_DataType_get(swigCPtr);
      return ret;
    } 
  }

  public IntPtr ContentData {get{IntPtr res = gnsdk_csharp_marshalPINVOKE.GnLinkContent_ContentData_get(swigCPtr); ; return res;}
  }

}

}
