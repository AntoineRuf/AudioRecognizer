
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Provides core functionality necessary to all Gracenote objects. This class must
* be instantiated prior to any other Gracenote objects.
*/
public class GnManager : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnManager(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnManager obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnManager() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnManager(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public static string GlobalIdMagic() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnManager_GlobalIdMagic();
    return ret;
  }

/**
* Creates a new Serialized User and also increments the user's Client ID user count with Gracenote Service.
* Use this constructor to create a new user; when successful, this call registers a new user for
* a specified client in Gracenote Service. Once the new user is registered and the user count
* incremented in Gracenote Service, the count cannot be reduced, nor can the same user be
* again retrieved.
* Newly registered user handles must be serialized and stored locally for that user to be used
* again for future queries; failing to do this quickly depletes the client's allotted user quota
* within the Gracenote Service.
* @param registerMode  		[in] register as online or local only user
* @param clientId     			[in] client ID that initiates requests with this handle; value provided by
*                      		Gracenote
* @param clientTag    			[in] client ID tag value that matches client ID; value provided by Gracenote
* @param applicationVersion  	[in] client application version; numeric value provided by application, and
*                      		this value is required
*/
  public GnString UserRegister(GnUserRegisterMode registerMode, string clientId, string clientTag, string applicationVersion) {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnManager_UserRegister(swigCPtr, (int)registerMode, clientId, clientTag, applicationVersion), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Get query cache storage operations instance
*/
  public GnStoreOps QueryCacheStore() {
    GnStoreOps ret = new GnStoreOps(gnsdk_csharp_marshalPINVOKE.GnManager_QueryCacheStore(swigCPtr), false);
    return ret;
  }

/**
* Get content cache storage operations instance
*/
  public GnStoreOps ContentCacheStore() {
    GnStoreOps ret = new GnStoreOps(gnsdk_csharp_marshalPINVOKE.GnManager_ContentCacheStore(swigCPtr), false);
    return ret;
  }

/**
* Get locales storage operations instance
*/
  public GnStoreOps LocalesStore() {
    GnStoreOps ret = new GnStoreOps(gnsdk_csharp_marshalPINVOKE.GnManager_LocalesStore(swigCPtr), false);
    return ret;
  }

  public void SystemEventHandler(GnSystemEventsDelegate pEventHandler) {
    gnsdk_csharp_marshalPINVOKE.GnManager_SystemEventHandler(swigCPtr, GnSystemEventsDelegate.getCPtr(pEventHandler));
  }

  public void SystemMemoryEvent(uint memoryWarnSize) {
    gnsdk_csharp_marshalPINVOKE.GnManager_SystemMemoryEvent(swigCPtr, memoryWarnSize);
  }

  public uint SystemMemoryCurrent() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnManager_SystemMemoryCurrent(swigCPtr);
    return ret;
  }

  public uint SystemMemoryHighWater(char bResetHighWater) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnManager_SystemMemoryHighWater(swigCPtr, bResetHighWater);
    return ret;
  }

  public void TestGracenoteConnection(GnUser user) {
    gnsdk_csharp_marshalPINVOKE.GnManager_TestGracenoteConnection(swigCPtr, GnUser.getCPtr(user));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnSystemEventsDelegate EventHandler() {
    IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnManager_EventHandler(swigCPtr);
    GnSystemEventsDelegate ret = (cPtr == IntPtr.Zero) ? null : new GnSystemEventsDelegate(cPtr, false);
    return ret;
  }

  public GnManager(string gnsdkLibraryPath, string license, GnLicenseInputMode licenseInputMode) : this(gnsdk_csharp_marshalPINVOKE.new_GnManager(gnsdkLibraryPath, license, (int)licenseInputMode), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieves the GNSDK version string.
* This API can be called at any time after GnManager instance is constructed successfully. The returned
* string is a constant. Do not attempt to modify or delete.
* Example: 1.2.3.123 (Major.Minor.Improvement.Build)
* Major: New functionality
* Minor: New or changed features
* Improvement: Improvements and fixes
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnManager_Version_get(swigCPtr) );
	} 

  }

/**
* Retrieves the product version string.
* This API can be called at any time after GnManager instance is constructed successfully. The returned
* string is a constant. Do not attempt to modify or delete.
* Example: 1.2.3.123 (Major.Minor.Improvement.Build)
* Major: New functionality
* Minor: New or changed features
* Improvement: Improvements and fixes
* Build: Internal build number
*/
  public string ProductVersion {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnManager_ProductVersion_get(swigCPtr) );
	} 

  }

/**
* Retrieves the GNSDK's build date string.
* This API can be called at any time after GnManager instance is constructed successfully. The returned
* string is a constant. Do not attempt to modify or delete.
* Example: 2008-02-12 00:41 UTC
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnManager_BuildDate_get(swigCPtr) );
	} 

  }

}

}
