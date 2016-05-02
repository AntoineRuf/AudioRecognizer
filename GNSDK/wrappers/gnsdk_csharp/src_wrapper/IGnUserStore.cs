
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Delegate interface for providing persistent serialized Gracenote user object storage and retrieval
*/
public class IGnUserStore : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IGnUserStore(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(IGnUserStore obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~IGnUserStore() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_IGnUserStore(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public virtual GnString LoadSerializedUser(string clientId) {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.IGnUserStore_LoadSerializedUser(swigCPtr, clientId), true);
    return ret;
  }

  public virtual bool StoreSerializedUser(string clientId, string userData) {
    bool ret = gnsdk_csharp_marshalPINVOKE.IGnUserStore_StoreSerializedUser(swigCPtr, clientId, userData);
    return ret;
  }

  public IGnUserStore() : this(gnsdk_csharp_marshalPINVOKE.new_IGnUserStore(), true) {
    SwigDirectorConnect();
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("LoadSerializedUser", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateIGnUserStore_0(SwigDirectorLoadSerializedUser);
    if (SwigDerivedClassHasMethod("StoreSerializedUser", swigMethodTypes1))
      swigDelegate1 = new SwigDelegateIGnUserStore_1(SwigDirectorStoreSerializedUser);
    gnsdk_csharp_marshalPINVOKE.IGnUserStore_director_connect(swigCPtr, swigDelegate0, swigDelegate1);
  }

  private bool SwigDerivedClassHasMethod(string methodName, Type[] methodTypes) {
    System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(IGnUserStore));
    return hasDerivedMethod;
  }

  private IntPtr SwigDirectorLoadSerializedUser(string clientId) {
    return GnString.getCPtr(LoadSerializedUser(clientId)).Handle;
  }

  private bool SwigDirectorStoreSerializedUser(string clientId, string userData) {
    return StoreSerializedUser(clientId, userData);
  }

  public delegate IntPtr SwigDelegateIGnUserStore_0(string clientId);
  public delegate bool SwigDelegateIGnUserStore_1(string clientId, string userData);

  private SwigDelegateIGnUserStore_0 swigDelegate0;
  private SwigDelegateIGnUserStore_1 swigDelegate1;

  private static Type[] swigMethodTypes0 = new Type[] { typeof(string) };
  private static Type[] swigMethodTypes1 = new Type[] { typeof(string), typeof(string) };
}

}
