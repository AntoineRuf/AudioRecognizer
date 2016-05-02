
package com.gracenote.gnsdk;

/** 
*  Logging options specifies what options are applied to the GNSDK log 
*/ 
 
public class GnLogOptions {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnLogOptions(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLogOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLogOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnLogOptions() {
    this(gnsdk_javaJNI.new_GnLogOptions(), true);
  }

/** 
* Specify true for the log to be written synchronously (no background thread). 
* By default logs are written to asynchronously. No internal logging 
* thread is created if all {@link GnLog} instances are specified for synchronous 
* writing. 
* @param bSyncWrite  Set true to enable synchronized writing, false for asynchrounous (default) 
*/ 
 
  public GnLogOptions synchronous(boolean bSyncWrite) {
    return new GnLogOptions(gnsdk_javaJNI.GnLogOptions_synchronous(swigCPtr, this, bSyncWrite), false);
  }

/** 
* Specify true to retain and rename old logs.  
* Default behavior is to delete old logs. 
* @param bArchive  Set true to keep rolled log files, false to delete rolled logs (default) 
*/ 
 
  public GnLogOptions archive(boolean bArchive) {
    return new GnLogOptions(gnsdk_javaJNI.GnLogOptions_archive(swigCPtr, this, bArchive), false);
  }

/** 
* Specify that when archive is also specified the logs to archive (roll) 
* at the start of each day (12:00 midnight). Archiving by the given size 
* parameter will still occur normally as well. 
*/ 
 
  public GnLogOptions archiveDaily() {
    return new GnLogOptions(gnsdk_javaJNI.GnLogOptions_archiveDaily(swigCPtr, this), false);
  }

/** 
* Specify the maximum size of log before new log is created. Enter a value of zero (0) to 
* always create new log on open 
* @param maxSize  Set to maximum size log file should reach to be rolled.  
* Set to zero to always roll log on creation (default) 
*/ 
 
  public GnLogOptions maxSize(java.math.BigInteger maxSize) {
    return new GnLogOptions(gnsdk_javaJNI.GnLogOptions_maxSize(swigCPtr, this, maxSize), false);
  }

}
