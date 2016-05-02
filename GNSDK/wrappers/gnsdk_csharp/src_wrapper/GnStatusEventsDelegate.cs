
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Delegate interface for receiving status updates as GNSDK operations are performed.
*/
public class GnStatusEventsDelegate : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnStatusEventsDelegate(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnStatusEventsDelegate obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnStatusEventsDelegate() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnStatusEventsDelegate(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
* Status change notification method. Override to receive notification.
* @param status				[in] Status type
* @param percentComplete		[in] Operation progress
* @param bytesTotalSent		[in] Total number of bytes sent
* @param bytesTotalReceived	[in] Total number of bytes received
* @param canceller				[in] Object that can be used to canel the operation
*/
  public virtual void StatusEvent(GnStatus status, uint percentComplete, uint bytesTotalSent, uint bytesTotalReceived, IGnCancellable canceller) {
    gnsdk_csharp_marshalPINVOKE.GnStatusEventsDelegate_StatusEvent(swigCPtr, (int)status, percentComplete, bytesTotalSent, bytesTotalReceived, IGnCancellable.getCPtr(canceller));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnStatusEventsDelegate() : this(gnsdk_csharp_marshalPINVOKE.new_GnStatusEventsDelegate(), true) {
    SwigDirectorConnect();
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("StatusEvent", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateGnStatusEventsDelegate_0(SwigDirectorStatusEvent);
    gnsdk_csharp_marshalPINVOKE.GnStatusEventsDelegate_director_connect(swigCPtr, swigDelegate0);
  }

  private bool SwigDerivedClassHasMethod(string methodName, Type[] methodTypes) {
    System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(GnStatusEventsDelegate));
    return hasDerivedMethod;
  }

  private void SwigDirectorStatusEvent(int status, uint percentComplete, uint bytesTotalSent, uint bytesTotalReceived, IntPtr canceller) {
    StatusEvent((GnStatus)status, percentComplete, bytesTotalSent, bytesTotalReceived, new IGnCancellable(canceller, false));
  }

  public delegate void SwigDelegateGnStatusEventsDelegate_0(int status, uint percentComplete, uint bytesTotalSent, uint bytesTotalReceived, IntPtr canceller);

  private SwigDelegateGnStatusEventsDelegate_0 swigDelegate0;

  private static Type[] swigMethodTypes0 = new Type[] { typeof(GnStatus), typeof(uint), typeof(uint), typeof(uint), typeof(IGnCancellable) };
}

}
