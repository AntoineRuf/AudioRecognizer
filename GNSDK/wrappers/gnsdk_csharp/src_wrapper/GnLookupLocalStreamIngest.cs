
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class GnLookupLocalStreamIngest : GnObject {
  private HandleRef swigCPtr;

  internal GnLookupLocalStreamIngest(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnLookupLocalStreamIngest_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLookupLocalStreamIngest obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLookupLocalStreamIngest() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLookupLocalStreamIngest(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnLookupLocalStreamIngest(GnLookupLocalStreamIngestEventsDelegate pEventDelegate) : this(gnsdk_csharp_marshalPINVOKE.new_GnLookupLocalStreamIngest(GnLookupLocalStreamIngestEventsDelegate.getCPtr(pEventDelegate)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Write to the ingestion process . This can be called multiple times to ensure that data is written as and when it is available.
*  @param data             [in] data to ingest
*  @param dataLength       [in] size of data being written
*/
  public void Write(byte[] bundleData, uint dataSize) {
    gnsdk_csharp_marshalPINVOKE.GnLookupLocalStreamIngest_Write(swigCPtr, bundleData, dataSize);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Flushes the memory cache to the file storage and commits the changes. This call will result in IO .
* Use this method to ensure that everything written is commited to the file system.
* Note: This is an optional call as internally data is flushed when it exceed the cache size and when the object goes out of scope..
*/
  public void Flush() {
    gnsdk_csharp_marshalPINVOKE.GnLookupLocalStreamIngest_Flush(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnLookupLocalStreamIngestEventsDelegate EventHandler() {
    IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnLookupLocalStreamIngest_EventHandler(swigCPtr);
    GnLookupLocalStreamIngestEventsDelegate ret = (cPtr == IntPtr.Zero) ? null : new GnLookupLocalStreamIngestEventsDelegate(cPtr, false);
    return ret;
  }

}

}
