
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
*  Logging options specifies what options are applied to the GNSDK log
*/
public class GnLogOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnLogOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLogOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLogOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLogOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnLogOptions() : this(gnsdk_csharp_marshalPINVOKE.new_GnLogOptions(), true) {
  }

/**
* Specify true for the log to be written synchronously (no background thread).
* By default logs are written to asynchronously. No internal logging
* thread is created if all GnLog instances are specified for synchronous
* writing.
* @param bSyncWrite  Set true to enable synchronized writing, false for asynchrounous (default)
*/
  public GnLogOptions Synchronous(bool bSyncWrite) {
    GnLogOptions ret = new GnLogOptions(gnsdk_csharp_marshalPINVOKE.GnLogOptions_Synchronous(swigCPtr, bSyncWrite), false);
    return ret;
  }

/**
* Specify true to retain and rename old logs. 
* Default behavior is to delete old logs.
* @param bArchive  Set true to keep rolled log files, false to delete rolled logs (default)
*/
  public GnLogOptions Archive(bool bArchive) {
    GnLogOptions ret = new GnLogOptions(gnsdk_csharp_marshalPINVOKE.GnLogOptions_Archive(swigCPtr, bArchive), false);
    return ret;
  }

/**
* Specify that when archive is also specified the logs to archive (roll)
* at the start of each day (12:00 midnight). Archiving by the given size
* parameter will still occur normally as well.
*/
  public GnLogOptions ArchiveDaily() {
    GnLogOptions ret = new GnLogOptions(gnsdk_csharp_marshalPINVOKE.GnLogOptions_ArchiveDaily(swigCPtr), false);
    return ret;
  }

  public GnLogOptions MaxSize(ulong maxSize) {
    GnLogOptions ret = new GnLogOptions(gnsdk_csharp_marshalPINVOKE.GnLogOptions_MaxSize(swigCPtr, maxSize), false);
    return ret;
  }

}

}
