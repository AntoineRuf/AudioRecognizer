
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* GNSDK SQLite storage provider
*/
public class GnStorageSqlite : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnStorageSqlite(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnStorageSqlite obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnStorageSqlite() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnStorageSqlite(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
* Sets the path to an external shared SQLite library to use instead of out internal copy
* <p><b>Remarks:</b></p>
* If used, this must be called before <code>Enable()</code>
*/
  public static void UseExternalLibrary(string sqlite3_filepath) {
    gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_UseExternalLibrary(sqlite3_filepath);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Enable SQLite storage provider
* @return Storage provider instance
*/
  public static GnStorageSqlite Enable() {
    GnStorageSqlite ret = new GnStorageSqlite(gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_Enable(), false);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Get the temporary storage location folder for GNSDK SQLite storage
*/
  public string TemporaryStorageLocation() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_TemporaryStorageLocation__SWIG_0(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Sets a temporary folder location for GNSDK SQLite storage
*  @param folderPath	[in] Relative path name for storage
* <p><b>Remarks:</b></p>
*  This API sets the temporary folder location for ALL GNSDK SQLite storage.
*/
  public void TemporaryStorageLocation(string folderPath) {
    gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_TemporaryStorageLocation__SWIG_1(swigCPtr, folderPath);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Retrieves the version string of the Storage SQLite library.
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_Version_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the build date string of the Storage SQLite library.
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_BuildDate_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the version string of the internal SQLite database engine.
*/
  public string SqliteVersion {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_SqliteVersion_get(swigCPtr) );
	} 

  }

/**
* Get storage location folder for GNSDK SQLite storage
*/
  public string StorageLocation {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_StorageLocation_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_StorageLocation_get(swigCPtr) );
	} 

  }

/**
* Get synchronous mode setting
*/
  public string SynchronousMode {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_SynchronousMode_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_SynchronousMode_get(swigCPtr) );
	} 

  }

/**
* Get journalling mode setting
*/
  public string JournalMode {
	/* csvarin typemap code */
	set 
	{
		IntPtr tempvalue = GnMarshalUTF8.NativeUtf8FromString(value);
		gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_JournalMode_set(swigCPtr, tempvalue);
		GnMarshalUTF8.ReleaseMarshaledUTF8String(tempvalue);
	}
 
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_JournalMode_get(swigCPtr) );
	} 

  }

/**
* Get maximum cache file size
*/
  public uint MaximumCacheFileSize {
    set {
      gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_MaximumCacheFileSize_set(swigCPtr, value);
    } 
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_MaximumCacheFileSize_get(swigCPtr);
      return ret;
    } 
  }

/**
* Get maximum cache memory
*/
  public uint MaximumCacheMemory {
    set {
      gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_MaximumCacheMemory_set(swigCPtr, value);
    } 
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnStorageSqlite_MaximumCacheMemory_get(swigCPtr);
      return ret;
    } 
  }

}

}
