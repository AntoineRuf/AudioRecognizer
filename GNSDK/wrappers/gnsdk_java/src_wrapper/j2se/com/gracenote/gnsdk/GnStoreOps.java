
package com.gracenote.gnsdk;

/** 
* GNSDK persistent store configuration and maintenance operations 
*/ 
 
public class GnStoreOps {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnStoreOps(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnStoreOps obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnStoreOps(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
*  Specify the location of the persistent store. 
* <p> 
*  If location is not specified using this method the location set for the initialized storage SDK will be used. 
*  For example, if the SQLite Storage SDK has been initialized, any path set using 
*  <code>GnStorageSqlite.StorageLocation(..)</code> will be used. 
* <p> 
*  The storage location must be a valid relative or absolute path to an existing folder that 
*  has the necessary write permissions. 
* <p> 
*  <p><b>Important:</b></p> 
*  For Windows CE an absolute path must be used. 
*  @param location [in] response cache location 
*/ 
 
  public void location(String location) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStoreOps_location(swigCPtr, this, location);
  }

/** 
*  Clears all records from the persistent store. 
* <p> 
*  When the <code>bAsync</code> is set to true the function immediately 
*  returns and the flush is performed in the background and on a separate thread. 
* <p> 
*  Performance 
* <p> 
*  If <code>bAsync</code> is true this API spawns a thread to perform the operation. This thread runs at the 
*  lowest priority to minimize the impact on other running queries or operations of the SDK. 
* <p> 
*  This function can cause performance issues due to creating a large amount of disk I/O. 
* <p> 
*  This operation can be performed on different storages at the same time, but note that performing 
*  multiple simultaneous calls will potentially further degrade performance. 
* <p> 
*  @param bAsync [in] if true perform an asynchronous cache flush in the background on a separate thread 
*/ 
 
  public void flush(boolean bAsync) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStoreOps_flush(swigCPtr, this, bAsync);
  }

/** 
*  Attempts to compact the persistent store and minimize the amount of space required. 
* <p> 
*  When the <code>bAsync</code> is set to true the function immediately 
*  returns and the compact is performed in the background and on a separate thread. 
* <p> 
*  Performance 
* <p> 
*  If <code>bAsync</code> is true this API spawns a thread to perform the operation. This thread runs at the 
*  lowest priority to minimize the impact on other running queries or operations of the SDK. 
* <p> 
*  This method can cause performance issues due to creating a large amount of disk I/O. 
* <p> 
*  This operation can be performed on different storages at the same time, but note that performing 
*  multiple simultaneous calls will potentially further degrade performance. 
* <p> 
*  @param bAsync [in] if true perform an asynchronous cache compact in the background on a separate thread 
*/ 
 
  public void compact(boolean bAsync) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStoreOps_compact(swigCPtr, this, bAsync);
  }

/** 
*  Searches the existing local store and removes any records that are expired or unneeded. 
* <p> 
*  Operation 
* <p> 
*  This API first decides if maintenance is required; this is determined by tracking when the next 
*  record expiration is needed. 
* <p> 
*  Maintenance is always run the first time this API is called; any subsequent calls only perform 
*  maintenance if this is required. Consequently, calling this API multiple times does not result in 
*  excessive maintenance. 
* <p> 
*  Performance 
* <p> 
*  If <code>bAsync</code> is true and if maintenance is necessary, this API spawns a thread to perform the clean-up. 
*  This thread runs at the lowest priority to minimize the impact on other running queries or operations of the SDK. 
* <p> 
*  This function can cause performance issues due to creating a large amount of disk I/O. 
* <p> 
*  This operation can be performed on different storages at the same time, but note that performing 
*  multiple simultaneous calls will potentially further degrade performance. 
* <p> 
*  Expired Records 
* <p> 
*  Expired records are those older than the maximum allowable, even if the record has been recently 
*  read. Old but actively read records are removed because Gracenote Service may have an updated 
*  matching record. 
* <p> 
*  The maximum allowable age of a record varies by query type and is managed internally by 
*  Gracenote. Applications can use {@link GnUser} option to adjust the age at which 
*  records are expired. 
* <p> 
*  @param bAsync [in] if true perform an asynchronous cache clean-up maintenance in the background on a separate thread 
* <p> 
*/ 
 
  public void cleanup(boolean bAsync) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStoreOps_cleanup(swigCPtr, this, bAsync);
  }

}
