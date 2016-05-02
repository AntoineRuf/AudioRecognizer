
package com.gracenote.gnsdk;

/** 
* Configuration options for {@link GnUser} 
*/ 
 
public class GnUserOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnUserOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnUserOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnUserOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
* Constructs empty {@link GnUserOptions} object. It is not associated with any {@link GnUser} object. 
*/ 
 
  public GnUserOptions() {
    this(gnsdk_javaJNI.new_GnUserOptions(), true);
  }

/** 
* Get lookup mode. 
* @return Lookup mode 
*/ 
 
  public GnLookupMode lookupMode() throws com.gracenote.gnsdk.GnException {
    return GnLookupMode.swigToEnum(gnsdk_javaJNI.GnUserOptions_lookupMode__SWIG_0(swigCPtr, this));
  }

/** 
* Set lookup mode. 
* @param lookupMode	[in] Lookup mode 
*/ 
 
  public void lookupMode(GnLookupMode lookupMode) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_lookupMode__SWIG_1(swigCPtr, this, lookupMode.swigValue());
  }

/** 
* Get network proxy hostname 
* @return Network proxy hostname 
*/ 
 
  public String networkProxy() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnUserOptions_networkProxy__SWIG_0(swigCPtr, this);
  }

/** 
* Sets host name, username and password for proxy to route GNSDK queries through 
* @param hostname	[in] Fully qualified host name with optional port number. If no port number 
*                  is given the default port number is assumed to be 80. 
*                  Example values are "http://proxy.mycompany.com:8080/", "proxy.mycompany.com:8080" and 
*                  "proxy.mycompany.com" 
* @param username  [in] Valid user name for the proxy server. Do not set this option if a username is not required. 
* @param password  [in] Valid password for the proxy server. Do not set this option if a password is not required. 
*/ 
 
  public void networkProxy(String hostname, String username, String password) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_networkProxy__SWIG_1(swigCPtr, this, hostname, username, password);
  }

/** 
* Gets the network time-out for all GNSDK queries 
* @return Netwrk timeout 
*/ 
 
  public long networkTimeout() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnUserOptions_networkTimeout__SWIG_0(swigCPtr, this);
  }

/** 
* Sets the network time-out for all GNSDK queries in milliseconds. 
* Value for this option is a string with a numeric value that indicates the number of milliseconds 
* to set for network time-outs. For example for a 30-second time-out set option value as 30000 
* @param timeout_ms	[in] Time-out in milliseconds 
*/ 
 
  public void networkTimeout(long timeout_ms) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_networkTimeout__SWIG_1(swigCPtr, this, timeout_ms);
  }

/** 
* Get network local balance state 
* @return Network load balance state 
*/ 
 
  public boolean networkLoadBalance() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnUserOptions_networkLoadBalance__SWIG_0(swigCPtr, this);
  }

/** 
* Enables/Disable distributing queries across multiple Gracenote co-location facilities 
* When not enabled, queries will generally resolve to a single co-location. 
* To implement load balancing, enable this option. 
* Value to enable this option must be a boolean value that indicates true. 
* @param bEnable  [in] True to enable load balancing, false otherwise. 
* <p><b>Note:</b></p> 
* Ensure that any security settings (such as a firewall) in your network infrastructure do not 
* affect outbound access and prevent GNSDK from transmitting queries to various hosts with unique IP 
* addresses. 
*/ 
 
  public void networkLoadBalance(boolean bEnable) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_networkLoadBalance__SWIG_1(swigCPtr, this, bEnable);
  }

/** 
* Get the IP address of the network interface as configured for this User object 
* @return IP address 
*/ 
 
  public String networkInterface() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnUserOptions_networkInterface__SWIG_0(swigCPtr, this);
  }

/** 
* Set a specific network interface to be used with connections made by GNSDK utilizing this {@link GnUser} object. 
* Choosing which interface to use can be beneficial for systems with multiple network interfaces. Without 
* setting this option, connections will be made of the default network interface as decided by the 
* operating system. To enable this option a valid local IP address of the desired network interface must be 
* provided. 
* @param nicIpAddress	IP address of a local network interface 
*/ 
 
  public void networkInterface(String nicIpAddress) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_networkInterface__SWIG_1(swigCPtr, this, nicIpAddress);
  }

/** 
* Set information about this user 
* @param location_id	[in] Set an IP address or country code to represent the location of user performing requests. 
*                      Value for this parameter is a string with the IP address, or a 3-character country code 
*                      for the client making the request. This is generally required when setting a proxy for 
*                      GNSDK queries. Example values are "192.168.1.1", "usa" and "jpn". 
* @param mfg			[in] The manufacturer of the device running the SDK. Used mostly by Gracenote Service to collect 
*                      runtime statistics. 
* @param os			[in] The OS version of the device running the SDK. Used mostly by Gracenote Service to collect 
*                      runtime statistics. 
* @param uid			[in] Unique ID of the device running the SDK, such as ESN. Used mostly by Gracenote Service to 
*                      collect runtime statistics. 
*/ 
 
  public void userInfo(String location_id, String mfg, String os, String uid) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_userInfo(swigCPtr, this, location_id, mfg, os, uid);
  }

/** 
* Gets cache expiration time in seconds 
* @return Cache expiration time 
*/ 
 
  public long cacheExpiration() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnUserOptions_cacheExpiration__SWIG_0(swigCPtr, this);
  }

/** 
* Sets the maximum duration for which an item in the GNSDK query cache is valid. This duration is in 
* seconds, and must exceed one day. 
* The value set for this option is a string with a numeric value that indicates the number of 
* seconds to set for the expiration of cached queries. The maximum duration is set by Gracenote and 
* varies by requirements. 
* @param durationSec		[in] Expiration duration in seconds. For example, for a one day expiration 
* 							set an option value of "86400" (60 seconds * 60 minutes * 24 hours); for a 
* 							seven day expiration set an option value of "604800" 
* 							(60 seconds * 60 minutes * 24 hours * 7 days). 
* <p><b>Note:</b></p> 
* Setting this option to a zero value (0) causes the cache to start deleting records upon cache 
* hit, and not write new or updated records to the cache; in short, the cache effectively flushes 
* itself. The cache will start caching records again once this option is set to a value greater than 
* 0. Setting this option to a value less than 0 (for example: -1) causes the cache to use default 
* expiration values. 
* <p> 
* For mobile platforms Android, iOS and Windows Mobile the default cache expiration is zero. 
* <p> 
* Cache expiration only has an effect if the application initializes a GNSDK storage provider such as 
* {@link GnStorageSqlite}. Without a storage provider no cache can be created. 
* <p> 
*/ 
 
  public void cacheExpiration(long durationSec) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_cacheExpiration__SWIG_1(swigCPtr, this, durationSec);
  }

/** 
* Gets user option 
* @param key	[in] Option key 
* @return Option value 
*/ 
 
  public String custom(String key) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnUserOptions_custom__SWIG_0(swigCPtr, this, key);
  }

/** 
* Sets User option 
* @param key	[in] Option key 
* @param value	[in] Option value 
*/ 
 
  public void custom(String key, String value) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnUserOptions_custom__SWIG_1(swigCPtr, this, key, value);
  }

}
