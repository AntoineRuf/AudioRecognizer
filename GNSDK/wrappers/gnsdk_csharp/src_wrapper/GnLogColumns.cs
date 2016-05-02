
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Logging columns specifies what columns are written for each entry in the GNSDK log
*/
public class GnLogColumns : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnLogColumns(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLogColumns obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLogColumns() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLogColumns(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnLogColumns() : this(gnsdk_csharp_marshalPINVOKE.new_GnLogColumns(), true) {
  }

/**
* Clear options currently set
*/
  public void None() {
    gnsdk_csharp_marshalPINVOKE.GnLogColumns_None(swigCPtr);
  }

/**
* Specify to include a time stamp for each entry of the format: Wed Jan 30 18:56:37 2008
*/
  public GnLogColumns TimeStamp() {
    GnLogColumns ret = new GnLogColumns(gnsdk_csharp_marshalPINVOKE.GnLogColumns_TimeStamp(swigCPtr), false);
    return ret;
  }

/**
* Specify to categorizes the log entries by headings such as ERROR, INFO, and so on.
*/
  public GnLogColumns Category() {
    GnLogColumns ret = new GnLogColumns(gnsdk_csharp_marshalPINVOKE.GnLogColumns_Category(swigCPtr), false);
    return ret;
  }

/**
* Specify to include the Package Name, or the Package ID if the name is unavailable.
*/
  public GnLogColumns PackageName() {
    GnLogColumns ret = new GnLogColumns(gnsdk_csharp_marshalPINVOKE.GnLogColumns_PackageName(swigCPtr), false);
    return ret;
  }

/**
* Specify to include the Thread ID.
*/
  public GnLogColumns Thread() {
    GnLogColumns ret = new GnLogColumns(gnsdk_csharp_marshalPINVOKE.GnLogColumns_Thread(swigCPtr), false);
    return ret;
  }

/**
* Specify to include the source information
*/
  public GnLogColumns SourceInfo() {
    GnLogColumns ret = new GnLogColumns(gnsdk_csharp_marshalPINVOKE.GnLogColumns_SourceInfo(swigCPtr), false);
    return ret;
  }

/**
* Specify to include a trailing newline in the format: "\r\n"
*/
  public GnLogColumns NewLine() {
    GnLogColumns ret = new GnLogColumns(gnsdk_csharp_marshalPINVOKE.GnLogColumns_NewLine(swigCPtr), false);
    return ret;
  }

/**
* Specify to include all log formatting options.
*/
  public GnLogColumns All() {
    GnLogColumns ret = new GnLogColumns(gnsdk_csharp_marshalPINVOKE.GnLogColumns_All(swigCPtr), false);
    return ret;
  }

}

}
