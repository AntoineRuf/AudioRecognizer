
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Gracenote user
*/
public class GnUser : GnObject {
  private HandleRef swigCPtr;

  internal GnUser(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnUser_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnUser obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnUser() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnUser(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
* Reconstitutes user from serialized user handle data.
* Use this constructor to reconstitute a previously serialized GnUser. Reconstitution does not
* count towards the user count for your client in Gracenote Service.
* @param serializedUser		[in] String of serialized user handle data
* @param clientIdTest			[in_opt] Serialized user's expected Client ID
*/
  public GnUser(string serializedUser, string clientIdTest) : this(gnsdk_csharp_marshalPINVOKE.new_GnUser__SWIG_0(serializedUser, clientIdTest), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnUser(string serializedUser) : this(gnsdk_csharp_marshalPINVOKE.new_GnUser__SWIG_1(serializedUser), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Create a GnUser with the provided Client ID and Client Tag. Check user storage for an
* existing user and if found reconstitutes the user. Reconstitution does not
* count towards the user count for your client in Gracenote Service. If not found in
* user storage a new user is created.
* @param userStore				[in] User store delegate
* @param clientId				[in] Client Identifer
* @param clientTag				[in] Client Tag
* @param applicationVersion	[in] Application version
*/
  public GnUser(IGnUserStore userStore, string clientId, string clientTag, string applicationVersion) : this(gnsdk_csharp_marshalPINVOKE.new_GnUser__SWIG_2(IGnUserStore.getCPtr(userStore), clientId, clientTag, applicationVersion), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Gets flag indicating if the current user is only registered for local queries
* @return True if local only user, fals eotherwise
*/
  public bool IsLocalOnly() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnUser_IsLocalOnly(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Receive user options object. Use to set user options.
* @return User options object
*/
  public GnUserOptions Options() {
    GnUserOptions ret = new GnUserOptions(gnsdk_csharp_marshalPINVOKE.GnUser_Options(swigCPtr), false);
    return ret;
  }

}

}
