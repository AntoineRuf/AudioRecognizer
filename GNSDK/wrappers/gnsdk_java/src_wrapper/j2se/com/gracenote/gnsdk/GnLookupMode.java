
package com.gracenote.gnsdk;

/** 
* Modes for accessing Gracenote data and performing searches. 
* GNSDK can, where available, access data and search from both local and online 
* sources. 
*/ 
 
public enum GnLookupMode {
/** 
* Invalid lookup mode 
*/ 
 
  kLookupModeInvalid(0),
/** 
* This mode forces the lookup to be done against the local database only. Local caches created from (online) query 
* results are not queried in this mode. 
* If no local database exists, the query will fail. 
*/ 
 
  kLookupModeLocal,
/** 
* This is the default lookup mode. If a cache exists, the query checks it first for a match. 
* If a no match is found in the cache, then an online query is performed against Gracenote Service. 
* If a result is found there, it is stored in the local cache.  If no online provider exists, the query will fail. 
* The length of time before cache lookup query expires can be set via the user object. 
*/ 
 
  kLookupModeOnline,
/** 
* This mode forces the query to be done online only and will not perform a local cache lookup first. 
* If no online provider exists, the query will fail. In this mode online queries and lists are not 
* written to local storage, even if a storage provider has been initialize. 
*/ 
 
  kLookupModeOnlineNoCache,
/** 
* This mode forces the query to be done online only and will not perform a local cache lookup first. 
* If no online provider exists, the query will fail. If a storage provider has been initialized, 
* queries and lists are immediately written to local storage, but are never read unless the lookup mode is changed. 
*/ 
 
  kLookupModeOnlineNoCacheRead,
/** 
* This mode forces the query to be done against the online cache only and will not perform a network lookup. 
* If no online provider exists, the query will fail. 
*/ 
 
  kLookupModeOnlineCacheOnly;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLookupMode swigToEnum(int swigValue) {
    GnLookupMode[] swigValues = GnLookupMode.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLookupMode swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLookupMode.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLookupMode() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLookupMode(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLookupMode(GnLookupMode swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

