
package com.gracenote.gnsdk;

/** 
* Provides core functionality necessary to all Gracenote objects. This class must 
* be instantiated prior to any other Gracenote objects. 
*/ 
 
public class GnManager {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

	private IGnSystemEvents systemEvents;
	private IGnSystemEventsProxyU systemEventsProxy;
    private long getNewSystemEventsCPtr(IGnSystemEvents systemEvents) {
    	this.systemEvents = systemEvents;
    	systemEventsProxy = new IGnSystemEventsProxyU(systemEvents);
    	return IGnSystemEventsProxyL.getCPtr(systemEventsProxy);
    }

/** 
* Retrieves the GNSDK version string. 
* This API can be called at any time after {@link GnManager} instance is constructed successfully. The returned 
* string is a constant. Do not attempt to modify or delete. 
* Example: 1.2.3.123 (Major.Minor.Improvement.Build) 
* Major: New functionality 
* Minor: New or changed features 
* Improvement: Improvements and fixes 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnManager_version();
  }

/** 
* Retrieves the product version string. 
* This API can be called at any time after {@link GnManager} instance is constructed successfully. The returned 
* string is a constant. Do not attempt to modify or delete. 
* Example: 1.2.3.123 (Major.Minor.Improvement.Build) 
* Major: New functionality 
* Minor: New or changed features 
* Improvement: Improvements and fixes 
* Build: Internal build number 
*/ 
 
  public static String productVersion() {
    return gnsdk_javaJNI.GnManager_productVersion();
  }

/** 
* Retrieves the GNSDK's build date string. 
* This API can be called at any time after {@link GnManager} instance is constructed successfully. The returned 
* string is a constant. Do not attempt to modify or delete. 
* Example: 2008-02-12 00:41 UTC 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnManager_buildDate();
  }

  public static String globalIdMagic() {
    return gnsdk_javaJNI.GnManager_globalIdMagic();
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
 
  public GnString userRegister(GnUserRegisterMode registerMode, String clientId, String clientTag, String applicationVersion) throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnManager_userRegister(swigCPtr, this, registerMode.swigValue(), clientId, clientTag, applicationVersion), true);
  }

/** 
* Get query cache storage operations instance 
*/ 
 
  public GnStoreOps queryCacheStore() {
    return new GnStoreOps(gnsdk_javaJNI.GnManager_queryCacheStore(swigCPtr, this), false);
  }

/** 
* Get content cache storage operations instance 
*/ 
 
  public GnStoreOps contentCacheStore() {
    return new GnStoreOps(gnsdk_javaJNI.GnManager_contentCacheStore(swigCPtr, this), false);
  }

/** 
* Get locales storage operations instance 
*/ 
 
  public GnStoreOps localesStore() {
    return new GnStoreOps(gnsdk_javaJNI.GnManager_localesStore(swigCPtr, this), false);
  }

/** 
* Provide a delegate to receive system events 
* @param pEventHandler		[in] event handler delegate 
*/ 
 
  public void systemEventHandler(IGnSystemEvents pEventHandler) {
    gnsdk_javaJNI.GnManager_systemEventHandler(swigCPtr, this, getNewSystemEventsCPtr(pEventHandler), systemEventsProxy);
  }

  public void systemMemoryEvent(long memoryWarnSize) {
    gnsdk_javaJNI.GnManager_systemMemoryEvent(swigCPtr, this, memoryWarnSize);
  }

  public long systemMemoryCurrent() {
    return gnsdk_javaJNI.GnManager_systemMemoryCurrent(swigCPtr, this);
  }

  public long systemMemoryHighWater(char bResetHighWater) {
    return gnsdk_javaJNI.GnManager_systemMemoryHighWater(swigCPtr, this, bResetHighWater);
  }

  public void testGracenoteConnection(GnUser user) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnManager_testGracenoteConnection(swigCPtr, this, GnUser.getCPtr(user), user);
  }

/** 
* Get the system event handler if previously provided 
* @return Event handler 
*/ 
 
  public IGnSystemEvents eventHandler() {
	return systemEvents;
}

  public GnManager(String gnsdkLibraryPath, String license, GnLicenseInputMode licenseInputMode) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnManager(gnsdkLibraryPath, license, licenseInputMode.swigValue()), true);
  }

}
