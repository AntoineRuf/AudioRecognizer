
package com.gracenote.gnsdk;

/** 
* Provides services for local lookup of MusicID-Stream queries 
* <p> 
* {@link GnLookupLocalStream} is a MusicID-Stream local lookup provider, providing a local 
* database of MusicID-Stream tracks suitable for lookup via {@link GnMusicIdStream} or {@link GnMusicId}. 
* <p> 
* The local database is a Gracenote storage; therefore a storage provider, such as {@link GnStorageSqlite}, 
* must be enabled as a pre-requisite to successfully using this class. 
* <p> 
* <b>Bundle Ingestion</b> 
* <p> 
* The MusicID-Stream local database is constructed from "bundles" provided periodically by Gracenote. 
* Your application must ingest the bundle, a process that adds the tracks from the bundle to the local 
* database making them available for local recognition. 
* <p> 
* To ingest a bundle create an instance of {@link GnLookupLocalStreamIngest} and write the bundle bytes 
* as received when streaming the bundle from your online service. 
* <p> 
* Multiple bundles can be ingested by the same application. If the same track exists in multiple 
* ingested bundles it is added to the local database only once and only the most recent/up-to-date track 
* information is written to the database. 
* <p> 
* The process of ingestion can be lengthy. Some applications may wish to perform ingestion on a 
* background thread to avoid stalling the main application thread. 
* <p> 
* <b>Bundle Management</b> 
* <p> 
* Bundles are regularly generated for multiple global regions and in multiple flavors being 
* incremental (only differences from previous bundle for that region) or full (all records for the 
* region). 
* <p> 
* Incremental bundles are intended for applications that have installed the previous bundles in the 
* sequence. If your application skips a bundle it should clear it's MusicID-Stream local database 
* and install the full bundle. 
* <p> 
* Your bundle management system must provide the means to regularly distribute the correct bundle to 
* your application, ensuring it provides the bundle for the correct region and, as appropriate, the 
* full or incremental bundle. 
* <p> 
* A typical bundle management system is:<br> 
* - retrieve bundles as produced by Gracenote (manual step)<br> 
* - place bundle in online location where application can fetch it<br> 
* - application downloads and ingests the bundle 
* <p> 
* Note: Bundles should be retrieved from an online source. Gracenote recommends when your application 
* is installed/initialized it download and ingest the latest bundle rather than ship with a bundle as 
* part of the application binaries. 
*/ 
 
public class GnLookupLocalStream {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnLookupLocalStream(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLookupLocalStream obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLookupLocalStream(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
* Enable Lookup local Stream provider. 
* @return Storage provider instance 
*/ 
 
  public static GnLookupLocalStream enable() throws com.gracenote.gnsdk.GnException {
    return new GnLookupLocalStream(gnsdk_javaJNI.GnLookupLocalStream_enable(), false);
  }

/** 
*  Retrieves {@link GnLookupLocalStream} SDK version string. 
*  This API can be called at any time, after getting instance of {@link GnManager} successfully. The returned 
*  string is a constant. Do not attempt to modify or delete. 
*  Example: 1.2.3.123 (Major.Minor.Improvement.Build) 
*  Major: New functionality 
*  Minor: New or changed features 
*  Improvement: Improvements and fixes 
*  Build: Internal build number 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnLookupLocalStream_version();
  }

/** 
*  Retrieves the {@link GnLookupLocalStream} SDK's build date string. 
*  @return gnsdk_cstr_t Build date string of the format: YYYY-MM-DD hh:mm UTC 
*  <p><b>Remarks:</b></p> 
*  This API can be called at any time, after getting instance of {@link GnManager} successfully. The returned 
* string is a constant. Do not attempt to modify or delete. 
*  Example build date string: 2008-02-12 00:41 UTC 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnLookupLocalStream_buildDate();
  }

/** 
*  Sets a folder location for GNSDK LookupLocalStream 
*  @param folderPath	[in] Relative path name for storage 
* <p><b>Remarks:</b></p> 
*  This API overrides the (default or explicit) folder location of GNSDK SQLite storage - for this database. 
*/ 
 
  public void storageLocation(String location) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnLookupLocalStream_storageLocation(swigCPtr, this, location);
  }

  public void engineType(GnLocalStreamEngineType engineType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnLookupLocalStream_engineType__SWIG_0(swigCPtr, this, engineType.swigValue());
  }

  public GnLocalStreamEngineType engineType() throws com.gracenote.gnsdk.GnException {
    return GnLocalStreamEngineType.swigToEnum(gnsdk_javaJNI.GnLookupLocalStream_engineType__SWIG_1(swigCPtr, this));
  }

/** 
* Clear all tracks from the MusicID-Stream local database storage file 
*/ 
 
  public void storageClear() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnLookupLocalStream_storageClear(swigCPtr, this);
  }

/** 
* Remove an item from the MusicID-Stream local database identified by 
* Bundle Item ID. 
* @param	bundleItemId	[in] Bundle Item ID 
*/ 
 
  public void storageRemove(String bundleItemId) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnLookupLocalStream_storageRemove(swigCPtr, this, bundleItemId);
  }

}
