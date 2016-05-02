/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class GnLogEventsDelegate : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnLogEventsDelegate(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLogEventsDelegate obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLogEventsDelegate() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLogEventsDelegate(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public virtual bool LogMessage(ushort packageId, GnLogMessageType messageType, uint errorCode, string message) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnLogEventsDelegate_LogMessage(swigCPtr, packageId, (int)messageType, errorCode, message);
    return ret;
  }

  public GnLogEventsDelegate() : this(gnsdk_csharp_marshalPINVOKE.new_GnLogEventsDelegate(), true) {
    SwigDirectorConnect();
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("LogMessage", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateGnLogEventsDelegate_0(SwigDirectorLogMessage);
    gnsdk_csharp_marshalPINVOKE.GnLogEventsDelegate_director_connect(swigCPtr, swigDelegate0);
  }

  private bool SwigDerivedClassHasMethod(string methodName, Type[] methodTypes) {
    System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(GnLogEventsDelegate));
    return hasDerivedMethod;
  }

  private bool SwigDirectorLogMessage(ushort packageId, int messageType, uint errorCode, string message) {
    return LogMessage(packageId, (GnLogMessageType)messageType, errorCode, message);
  }

  public delegate bool SwigDelegateGnLogEventsDelegate_0(ushort packageId, int messageType, uint errorCode, string message);

  private SwigDelegateGnLogEventsDelegate_0 swigDelegate0;

  private static Type[] swigMethodTypes0 = new Type[] { typeof(ushort), typeof(GnLogMessageType), typeof(uint), typeof(string) };
}

}
