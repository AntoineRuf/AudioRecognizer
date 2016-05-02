
package com.gracenote.gnsdk;

/** 
* GNSDK SQLite storage provider 
*/ 
 
public class GnStorageSqlite {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnStorageSqlite(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnStorageSqlite obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnStorageSqlite(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
* Sets the path to an external shared SQLite library to use instead of out internal copy 
* <p><b>Remarks:</b></p> 
* If used, this must be called before <code>Enable()</code> 
*/ 
 
  public static void useExternalLibrary(String sqlite3_filepath) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStorageSqlite_useExternalLibrary(sqlite3_filepath);
  }

/** 
* Enable SQLite storage provider 
* @return Storage provider instance 
*/ 
 
  public static GnStorageSqlite enable() throws com.gracenote.gnsdk.GnException {
    return new GnStorageSqlite(gnsdk_javaJNI.GnStorageSqlite_enable(), false);
  }

/** 
*  Retrieves the version string of the Storage SQLite library. 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnStorageSqlite_version();
  }

/** 
*  Retrieves the build date string of the Storage SQLite library. 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnStorageSqlite_buildDate();
  }

/** 
*  Retrieves the version string of the internal SQLite database engine. 
*/ 
 
  public static String sqliteVersion() {
    return gnsdk_javaJNI.GnStorageSqlite_sqliteVersion();
  }

/** 
*  Sets a folder location for GNSDK SQLite storage 
*  @param folderPath	[in] Relative path name for storage 
* <p><b>Remarks:</b></p> 
*  This API sets the folder location for ALL GNSDK SQLite storage - to set specific cache or database 
*  locations use StorageLocation methods of the appropriate class. 
*/ 
 
  public void storageLocation(String folderPath) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStorageSqlite_storageLocation__SWIG_0(swigCPtr, this, folderPath);
  }

/** 
* Get storage location folder for GNSDK SQLite storage 
*/ 
 
  public String storageLocation() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnStorageSqlite_storageLocation__SWIG_1(swigCPtr, this);
  }

/** 
* Get the temporary storage location folder for GNSDK SQLite storage 
*/ 
 
  public String temporaryStorageLocation() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnStorageSqlite_temporaryStorageLocation__SWIG_0(swigCPtr, this);
  }

/** 
*  Sets a temporary folder location for GNSDK SQLite storage 
*  @param folderPath	[in] Relative path name for storage 
* <p><b>Remarks:</b></p> 
*  This API sets the temporary folder location for ALL GNSDK SQLite storage. 
*/ 
 
  public void temporaryStorageLocation(String folderPath) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStorageSqlite_temporaryStorageLocation__SWIG_1(swigCPtr, this, folderPath);
  }

/** 
* Sets the maximum size the GNSDK cache can grow to; for example '100' for 100 Kb or '1024' for 1 
*  MB. This limit applies to each cache that is created. 
* <p> 
*  The value passed for this option is the maximum number of Kilobytes that the cache files can grow 
*  to. For example, '100' sets the maximum to 100 KB, and '1024' sets the maximum to 1 MB. 
* <p> 
*  If the cache files' current size already exceeds the maximum when this option is set, then the 
*  set maximum is not applied. 
* <p> 
*  When the maximum size is reached, new cache entries are not written to the database. 
*  Additionally, a maintenance thread is run that attempts to clean up expired records from the 
*  database and create space for new records. 
* <p> 
*  If this option is not set the cache files default to having no maximum size. 
* <p> 
*  @param maxCacheSize	[in] Maximum cache file size 
*/ 
 
  public void maximumCacheFileSize(long maxCacheSize) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStorageSqlite_maximumCacheFileSize__SWIG_0(swigCPtr, this, maxCacheSize);
  }

/** 
* Get maximum cache file size 
*/ 
 
  public long maximumCacheFileSize() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnStorageSqlite_maximumCacheFileSize__SWIG_1(swigCPtr, this);
  }

/** 
*  Sets the maximum amount of memory SQLite can use to buffer cache data. 
* <p> 
*  The value passed for this option is the maximum number of Kilobytes of memory that can be used. 
*  For example, '100' sets the maximum to 100 KB, and '1024' sets the maximum to 1 MB. 
* <p> 
*  @param maxMemSize [in]  Maximum cache memory size 
*/ 
 
  public void maximumCacheMemory(long maxMemSize) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStorageSqlite_maximumCacheMemory__SWIG_0(swigCPtr, this, maxMemSize);
  }

/** 
* Get maximum cache memory 
*/ 
 
  public long maximumCacheMemory() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnStorageSqlite_maximumCacheMemory__SWIG_1(swigCPtr, this);
  }

/** 
*  Sets the method that SQLite uses to write to the cache files. 
* <p> 
*  This option is available for SQLite performance tuning. Valid values for this option are: 
*  @param mode [in]: 
*  <ul> 
*  <li>OFF (default setting): No synchronous writing; the quickest but least safe method.</li> 
*  <li>NORMAL: Synchronous writing only at critical times; the generally quick and safe method.</li> 
*  <li>FULL: Always synchronous writing; the slowest and safest method.</li> 
*  </ul> 
* <p> 
*  If the threat of losing a cache file due to hardware failure is high, then set this option in 
*  your application to NORMAL or FULL. 
*/ 
 
  public void synchronousMode(String mode) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStorageSqlite_synchronousMode__SWIG_0(swigCPtr, this, mode);
  }

/** 
* Get synchronous mode setting 
*/ 
 
  public String synchronousMode() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnStorageSqlite_synchronousMode__SWIG_1(swigCPtr, this);
  }

/** 
*  Sets how the SQLite journal file is managed for database transactions. 
* <p> 
*  This option is available for SQLite performance tuning. Valid values for this option are: 
*  @param mode [in]: 
*  <ul> 
*  <li>DELETE: Journal file is deleted after each transaction.</li> 
*  <li>TRUNCATE: Journal file is truncated (but not deleted) after each transaction.</li> 
*  <li>PERSIST: Journal file remains after each transaction.</li> 
*  <li>MEMORY (default setting): Journal file is only stored in memory for each transaction.</li> 
*  <li>OFF: No journaling is performed.</li> 
*  </ul> 
**/ 
 
  public void journalMode(String mode) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnStorageSqlite_journalMode__SWIG_0(swigCPtr, this, mode);
  }

/** 
* Get journalling mode setting 
*/ 
 
  public String journalMode() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnStorageSqlite_journalMode__SWIG_1(swigCPtr, this);
  }

}
