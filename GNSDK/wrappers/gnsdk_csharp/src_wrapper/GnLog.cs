
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Configures and enables GNSDK logging including registering custom logging packages
* and writing your own logging message to the GNSDK log
*/
public class GnLog : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnLog(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLog obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLog() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLog(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnLog(string logFilePath, GnLogEventsDelegate pLoggingDelegate) : this(gnsdk_csharp_marshalPINVOKE.new_GnLog__SWIG_0(logFilePath, GnLogEventsDelegate.getCPtr(pLoggingDelegate)), true) {
  }

  public GnLog(string logFilePath) : this(gnsdk_csharp_marshalPINVOKE.new_GnLog__SWIG_1(logFilePath), true) {
  }

  public GnLog(string logFilePath, GnLogFilters filters, GnLogColumns columns, GnLogOptions options, GnLogEventsDelegate pLoggingDelegate) : this(gnsdk_csharp_marshalPINVOKE.new_GnLog__SWIG_2(logFilePath, GnLogFilters.getCPtr(filters), GnLogColumns.getCPtr(columns), GnLogOptions.getCPtr(options), GnLogEventsDelegate.getCPtr(pLoggingDelegate)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnLog(string logFilePath, GnLogFilters filters, GnLogColumns columns, GnLogOptions options) : this(gnsdk_csharp_marshalPINVOKE.new_GnLog__SWIG_3(logFilePath, GnLogFilters.getCPtr(filters), GnLogColumns.getCPtr(columns), GnLogOptions.getCPtr(options)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Set logger instance options
* @param options  Selection of logging options via GnLogOptions
*/
  public void Options(GnLogOptions options) {
    gnsdk_csharp_marshalPINVOKE.GnLog_Options(swigCPtr, GnLogOptions.getCPtr(options));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Set logger instance filters
* @param filters  Selection of log message filters via GnLogFilters
*/
  public void Filters(GnLogFilters filters) {
    gnsdk_csharp_marshalPINVOKE.GnLog_Filters(swigCPtr, GnLogFilters.getCPtr(filters));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Set logger instance columns
* @param columns  Selection of log column format via GnLogColumns
*/
  public void Columns(GnLogColumns columns) {
    gnsdk_csharp_marshalPINVOKE.GnLog_Columns(swigCPtr, GnLogColumns.getCPtr(columns));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Enable logging for the given package with the current logging options and filters.
* Enable can be called multiple times to enable logging of multiple packages to the same log.
* <p><b>Remarks:</b></p>
* Changes to logging options and filters do not take affect until the logger is next enabled.
* @param package [in] GnLogPackage to enable for this log.
* @return This GnLog object to allow method chaining.
*/
  public GnLog Enable(GnLogPackageType package) {
    GnLog ret = new GnLog(gnsdk_csharp_marshalPINVOKE.GnLog_Enable__SWIG_0(swigCPtr, (int)package), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLog Enable(ushort customPackageId) {
    GnLog ret = new GnLog(gnsdk_csharp_marshalPINVOKE.GnLog_Enable__SWIG_1(swigCPtr, customPackageId), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Disable logging for the given package for the current log.
* If no other packages are enabled for the log, the log will be closed
* @param package [in] GnLogPackage to disable for this log.
* @return This GnLog object to allow method chaining.
*/
  public GnLog Disable(GnLogPackageType package) {
    GnLog ret = new GnLog(gnsdk_csharp_marshalPINVOKE.GnLog_Disable__SWIG_0(swigCPtr, (int)package), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLog Disable(ushort customPackageId) {
    GnLog ret = new GnLog(gnsdk_csharp_marshalPINVOKE.GnLog_Disable__SWIG_1(swigCPtr, customPackageId), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnLog Register(ushort customPackageId, string customPackageName) {
    GnLog ret = new GnLog(gnsdk_csharp_marshalPINVOKE.GnLog_Register(swigCPtr, customPackageId, customPackageName), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static void Write(int line, string fileName, ushort customPackageId, GnLogMessageType messageType, string format) {
    gnsdk_csharp_marshalPINVOKE.GnLog_Write(line, fileName, customPackageId, (int)messageType, format);
  }

  public static readonly ushort kMinimumCustomPackageIdValue = gnsdk_csharp_marshalPINVOKE.GnLog_kMinimumCustomPackageIdValue_get();
  public static readonly ushort kMaximumCustomPackageIdValue = gnsdk_csharp_marshalPINVOKE.GnLog_kMaximumCustomPackageIdValue_get();
}

}
