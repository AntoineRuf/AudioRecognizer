package com.gracenote.gnsdk;

/** 
* Delegate interface for receiving system events 
*/ 
 
public interface IGnSystemEvents {

/** 
* Notification event that the give Locale should be updated. 
* @param locale	[in] Locale detected as out of date 
*/ 
 
 	public void localeUpdateNeeded(GnLocale locale);

/** 
* Notification event that the given List should be updated. 
* @param list		[in] List detected as out of date 
*/ 
 
  	public void listUpdateNeeded(GnList list);

/** 
* Notifcation that GNSDK memory usage has gone over the set warning limit 
* @param curMemSize		[in] Current memory size 
* @param memoryWarnSize	[in] Memory warning size 
*/ 
 
  	public void systemMemoryWarning(long curMemSize, long memoryWarnSize);

}
