
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Provides services for adding audio tracks to GnMusicIdFile for identification.
*/
public class GnMusicIdFileInfoManager : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnMusicIdFileInfoManager(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicIdFileInfoManager obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicIdFileInfoManager() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicIdFileInfoManager(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public GnMusicIdFileInfo Add(string uniqueIdentifier, GnMusicIdFileInfoEventsDelegate pEventHandler) {
  System.IntPtr tempuniqueIdentifier = GnMarshalUTF8.NativeUtf8FromString(uniqueIdentifier);
    try {
      GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_Add__SWIG_0(swigCPtr, tempuniqueIdentifier, GnMusicIdFileInfoEventsDelegate.getCPtr(pEventHandler)), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempuniqueIdentifier);
    }
  }

  public GnMusicIdFileInfo Add(string uniqueIdentifier) {
  System.IntPtr tempuniqueIdentifier = GnMarshalUTF8.NativeUtf8FromString(uniqueIdentifier);
    try {
      GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_Add__SWIG_1(swigCPtr, tempuniqueIdentifier), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempuniqueIdentifier);
    }
  }

/**
* Add audio file(s) represented by an XML string to GnMusicIdFile for identification
* @param xmlStr			[in] Audio file(s) XML string, such as one created using RenderToXml()
* @return Number of audio files added
*/
  public uint AddFromXml(string xmlStr) {
  System.IntPtr tempxmlStr = GnMarshalUTF8.NativeUtf8FromString(xmlStr);
    try {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_AddFromXml(swigCPtr, tempxmlStr);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempxmlStr);
    }
  }

/**
* Render all added audio files to an XML string
* @return XML string
*/
  public GnString RenderToXml() {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_RenderToXml(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Remove and audio file from GnMusicIdFile
* @param fileInfo			[in] Object representing audio file to remove
*/
  public void Remove(GnMusicIdFileInfo fileInfo) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_Remove(swigCPtr, GnMusicIdFileInfo.getCPtr(fileInfo));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnMusicIdFileInfoEnumerator GetEnumerator() {
    GnMusicIdFileInfoEnumerator ret = new GnMusicIdFileInfoEnumerator(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_GetEnumerator(swigCPtr), true);
    return ret;
  }

  public GnMusicIdFileInfoEnumerator end() {
    GnMusicIdFileInfoEnumerator ret = new GnMusicIdFileInfoEnumerator(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_end(swigCPtr), true);
    return ret;
  }

/**
* Get number of audio files added
* @return Number of audio files
*/
  public uint count() {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_count(swigCPtr);
    return ret;
  }

/**
* Get audio file at specified index
* @param index				[in] Audio file index
* @return file iterator
*/
  public GnMusicIdFileInfo at(uint index) {
    GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_at(swigCPtr, index), true);
    return ret;
  }

  public GnMusicIdFileInfo getByIndex(uint index) {
    GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_getByIndex(swigCPtr, index), true);
    return ret;
  }

/**
* Retrieves the GnMusicIdFileInfo object that matches the given identifier string and is associated with the
* given MusicID-File handle.
* @param ident 			[in] String identifier of FileInfo to retrieve
* <p><b>Remarks:</b></p>
* The string identifier of each GnMusicIdFileInfo is set when Add is called.
* GnMusicIdFile enforces GnMusicIdFileInfo identifiers to be unique.
*/
  public GnMusicIdFileInfo GetByIdentifier(string ident) {
  System.IntPtr tempident = GnMarshalUTF8.NativeUtf8FromString(ident);
    try {
      GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_GetByIdentifier(swigCPtr, tempident), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempident);
    }
  }

/**
* Retrieves the GnMusicIdFileInfo object that matches the given file name.
* @param filename 			[in] File name or other string identifier of FileInfo to retrieve
* <p><b>Remarks:</b></p>
* Only GnMusicIdFileInfo objects that have file name information set through
* GnMusicIdFile::FileName can be retrieved with this function.
* <p><b>Note:</b></p>
* GnMusicIdFile does not enforce unique GnMusucIdFileInfo file names. Consequently, to use this function
* well, it is important to give unique file names to each GnMusicIdFileInfo added (such as the full path and
* file name).
* GnMusicIdFile does not check if the given file name given is a valid path or file name, nor is it
* required to be one. GnMusicIdFile only performs a match against the existing GnMusicIdFileInfo path and file
* names.
*/
  public GnMusicIdFileInfo GetByFilename(string filename) {
  System.IntPtr tempfilename = GnMarshalUTF8.NativeUtf8FromString(filename);
    try {
      GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_GetByFilename(swigCPtr, tempfilename), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempfilename);
    }
  }

/**
* Retrieves the index'th GnMusicIdFileInfo object matching the given folder.
* @param folder 			[in] Folder name of GnMusicIdFileInfo object to retrieve
* @param index 			[in] Index of GnMusicIdFileInfo object in folder name to retrieve
* <p><b>Remarks:</b></p>
* Only a GnMusicIdFileInfo that has path information set through GnMusicIdFile::FileName
* can be retrieved with this function. GnMusicId does not check if the given folder name is a valid path,
* nor is it required to be one. GnMusicIdFile only performs a match against existing GnMusiucIdFileInfo
* folder names.
*/
  public GnMusicIdFileInfo GetByFolder(string folder, uint index) {
  System.IntPtr tempfolder = GnMarshalUTF8.NativeUtf8FromString(folder);
    try {
      GnMusicIdFileInfo ret = new GnMusicIdFileInfo(gnsdk_csharp_marshalPINVOKE.GnMusicIdFileInfoManager_GetByFolder(swigCPtr, tempfolder, index), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempfolder);
    }
  }

}

}
