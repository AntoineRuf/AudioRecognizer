
package com.gracenote.gnsdk;

	import java.util.List;
	import java.util.ArrayList;

/** 
* Provides services for adding audio tracks to {@link GnMusicIdFile} for identification. 
*/ 
 
public class GnMusicIdFileInfoManager {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnMusicIdFileInfoManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMusicIdFileInfoManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMusicIdFileInfoManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

    private List<IGnMusicIdFileInfoEvents> fileInfoEventsReferences = new ArrayList<IGnMusicIdFileInfoEvents>();
    private List<IGnMusicIdFileInfoEventsProxyU> fileInfoEventsProxyUReferences = new ArrayList<IGnMusicIdFileInfoEventsProxyU>();

/** 
* Add an audio file to {@link GnMusicIdFile} for identification 
* @param uniqueIdentifier	[in] Unique identifier for the audio track, such as a filename or library reference 
* @param pEventHandler		[in-opt] Event delegate for processing events specifically for this audio file. Use 
* 							where the generic event handler provided on {@link GnMusicIdFile} construction isn't 
* 							suitable 
* @return Object representing the audio file 
*/ 
 
  public GnMusicIdFileInfo add(String uniqueIdentifier, IGnMusicIdFileInfoEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
IGnMusicIdFileInfoEventsProxyU fileInfoEventHandlerProxy = new IGnMusicIdFileInfoEventsProxyU(pEventHandler);fileInfoEventsReferences.add(pEventHandler);fileInfoEventsProxyUReferences.add(fileInfoEventHandlerProxy);
    {
      return new GnMusicIdFileInfo(gnsdk_javaJNI.GnMusicIdFileInfoManager_add__SWIG_0(swigCPtr, this, uniqueIdentifier, IGnMusicIdFileInfoEventsProxyL.getCPtr(fileInfoEventHandlerProxy), fileInfoEventHandlerProxy), true);
    }
  }

  public GnMusicIdFileInfo add(String uniqueIdentifier) throws com.gracenote.gnsdk.GnException {
    return new GnMusicIdFileInfo(gnsdk_javaJNI.GnMusicIdFileInfoManager_add__SWIG_1(swigCPtr, this, uniqueIdentifier), true);
  }

/** 
* Add audio file(s) represented by an XML string to {@link GnMusicIdFile} for identification 
* @param xmlStr			[in] Audio file(s) XML string, such as one created using RenderToXml() 
* @return Number of audio files added 
*/ 
 
  public long addFromXml(String xmlStr) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMusicIdFileInfoManager_addFromXml(swigCPtr, this, xmlStr);
  }

/** 
* Render all added audio files to an XML string 
* @return XML string 
*/ 
 
  public GnString renderToXml() throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnMusicIdFileInfoManager_renderToXml(swigCPtr, this), true);
  }

/** 
* Remove and audio file from {@link GnMusicIdFile} 
* @param fileInfo			[in] Object representing audio file to remove 
*/ 
 
  public void remove(GnMusicIdFileInfo fileInfo) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMusicIdFileInfoManager_remove(swigCPtr, this, GnMusicIdFileInfo.getCPtr(fileInfo), fileInfo);
  }

  public GnMusicIdFileInfoIterator getIterator() {
    return new GnMusicIdFileInfoIterator(gnsdk_javaJNI.GnMusicIdFileInfoManager_getIterator(swigCPtr, this), true);
  }

/** 
* Get an audio file iterator set at the last audio file. 
* @return audio file iterator 
*/ 
 
  public GnMusicIdFileInfoIterator end() {
    return new GnMusicIdFileInfoIterator(gnsdk_javaJNI.GnMusicIdFileInfoManager_end(swigCPtr, this), true);
  }

/** 
* Get number of audio files added 
* @return Number of audio files 
*/ 
 
  public long count() {
    return gnsdk_javaJNI.GnMusicIdFileInfoManager_count(swigCPtr, this);
  }

/** 
* Get audio file at specified index 
* @param index				[in] Audio file index 
* @return file iterator 
*/ 
 
  public GnMusicIdFileInfo at(long index) {
    return new GnMusicIdFileInfo(gnsdk_javaJNI.GnMusicIdFileInfoManager_at(swigCPtr, this, index), true);
  }

/** 
* Get audio file at specified index 
* @param index		[in] Audio file index 
* @return Object representing audio file 
*/ 
 
  public GnMusicIdFileInfo getByIndex(long index) {
    return new GnMusicIdFileInfo(gnsdk_javaJNI.GnMusicIdFileInfoManager_getByIndex(swigCPtr, this, index), true);
  }

/** 
* Retrieves the {@link GnMusicIdFileInfo} object that matches the given identifier string and is associated with the 
* given MusicID-File handle. 
* @param ident 			[in] String identifier of FileInfo to retrieve 
* <p><b>Remarks:</b></p> 
* The string identifier of each {@link GnMusicIdFileInfo} is set when Add is called. 
* {@link GnMusicIdFile} enforces {@link GnMusicIdFileInfo} identifiers to be unique. 
*/ 
 
  public GnMusicIdFileInfo getByIdentifier(String ident) throws com.gracenote.gnsdk.GnException {
    return new GnMusicIdFileInfo(gnsdk_javaJNI.GnMusicIdFileInfoManager_getByIdentifier(swigCPtr, this, ident), true);
  }

/** 
* Retrieves the {@link GnMusicIdFileInfo} object that matches the given file name. 
* @param filename 			[in] File name or other string identifier of FileInfo to retrieve 
* <p><b>Remarks:</b></p> 
* Only {@link GnMusicIdFileInfo} objects that have file name information set through 
* GnMusicIdFile::FileName can be retrieved with this function. 
* <p><b>Note:</b></p> 
* {@link GnMusicIdFile} does not enforce unique {@link GnMusucIdFileInfo} file names. Consequently, to use this function 
* well, it is important to give unique file names to each {@link GnMusicIdFileInfo} added (such as the full path and 
* file name). 
* {@link GnMusicIdFile} does not check if the given file name given is a valid path or file name, nor is it 
* required to be one. {@link GnMusicIdFile} only performs a match against the existing {@link GnMusicIdFileInfo} path and file 
* names. 
*/ 
 
  public GnMusicIdFileInfo getByFilename(String filename) throws com.gracenote.gnsdk.GnException {
    return new GnMusicIdFileInfo(gnsdk_javaJNI.GnMusicIdFileInfoManager_getByFilename(swigCPtr, this, filename), true);
  }

/** 
* Retrieves the index'th {@link GnMusicIdFileInfo} object matching the given folder. 
* @param folder 			[in] Folder name of {@link GnMusicIdFileInfo} object to retrieve 
* @param index 			[in] Index of {@link GnMusicIdFileInfo} object in folder name to retrieve 
* <p><b>Remarks:</b></p> 
* Only a {@link GnMusicIdFileInfo} that has path information set through GnMusicIdFile::FileName 
* can be retrieved with this function. {@link GnMusicId} does not check if the given folder name is a valid path, 
* nor is it required to be one. {@link GnMusicIdFile} only performs a match against existing {@link GnMusiucIdFileInfo} 
* folder names. 
*/ 
 
  public GnMusicIdFileInfo getByFolder(String folder, long index) throws com.gracenote.gnsdk.GnException {
    return new GnMusicIdFileInfo(gnsdk_javaJNI.GnMusicIdFileInfoManager_getByFolder(swigCPtr, this, folder, index), true);
  }

}
