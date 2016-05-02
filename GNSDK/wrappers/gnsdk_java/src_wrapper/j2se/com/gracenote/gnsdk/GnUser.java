
package com.gracenote.gnsdk;

/** 
* Gracenote user 
*/ 
 
public class GnUser extends GnObject {
  private long swigCPtr;

  protected GnUser(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnUser_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnUser obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnUser(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  private IGnUserStore userStore;
  private IGnUserStoreProxyU userStoreProxy;

/** 
* Reconstitutes user from serialized user handle data. 
* Use this constructor to reconstitute a previously serialized {@link GnUser}. Reconstitution does not 
* count towards the user count for your client in Gracenote Service. 
* @param serializedUser		[in] String of serialized user handle data 
* @param clientIdTest			[in_opt] Serialized user's expected Client ID 
*/ 
 
  public GnUser(String serializedUser, String clientIdTest) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( userStore != null ) {
		userStoreProxy = new IGnUserStoreProxyU(userStore);
		this.userStore = userStore;		// <REFERENCE_NAME_CHECK><TYPE>IGnUserStore</TYPE><NAME>userStore</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	}
	
    swigCPtr = gnsdk_javaJNI.new_GnUser__SWIG_0(serializedUser, clientIdTest);
}

  public GnUser(String serializedUser) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( userStore != null ) {
		userStoreProxy = new IGnUserStoreProxyU(userStore);
		this.userStore = userStore;		// <REFERENCE_NAME_CHECK><TYPE>IGnUserStore</TYPE><NAME>userStore</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	}
	
    swigCPtr = gnsdk_javaJNI.new_GnUser__SWIG_1(serializedUser);
}

/** 
* Create a {@link GnUser} with the provided Client ID and Client Tag. Check user storage for an 
* existing user and if found reconstitutes the user. Reconstitution does not 
* count towards the user count for your client in Gracenote Service. If not found in 
* user storage a new user is created. 
* @param userStore				[in] User store delegate 
* @param clientId				[in] Client Identifer 
* @param clientTag				[in] Client Tag 
* @param applicationVersion	[in] Application version 
*/ 
 
  public GnUser(IGnUserStore userStore, String clientId, String clientTag, String applicationVersion) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( userStore != null ) {
		userStoreProxy = new IGnUserStoreProxyU(userStore);
		this.userStore = userStore;		// <REFERENCE_NAME_CHECK><TYPE>IGnUserStore</TYPE><NAME>userStore</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	}
	
    swigCPtr = gnsdk_javaJNI.new_GnUser__SWIG_2((userStoreProxy==null)?0:IGnUserStoreProxyL.getCPtr(userStoreProxy), userStoreProxy, clientId, clientTag, applicationVersion);
}

/** 
* Gets flag indicating if the current user is only registered for local queries 
* @return True if local only user, fals eotherwise 
*/ 
 
  public boolean isLocalOnly() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnUser_isLocalOnly(swigCPtr, this);
  }

/** 
* Receive user options object. Use to set user options. 
* @return User options object 
*/ 
 
  public GnUserOptions options() {
    return new GnUserOptions(gnsdk_javaJNI.GnUser_options(swigCPtr, this), false);
  }

}
