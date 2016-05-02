
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/** 
* list_element_iterable
*//**
* Gracenote list.
*/
public class GnList : GnObject {
  private HandleRef swigCPtr;

  internal GnList(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnList_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnList obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnList() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnList(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
* constuctor 
*/
  public GnList(GnListType listType, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnList__SWIG_0((int)listType, (int)language, (int)region, (int)descriptor, GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnList(GnListType listType, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnList__SWIG_1((int)listType, (int)language, (int)region, (int)descriptor, GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* constuctor 
*/
  public GnList(GnListType listType, GnLocale locale, GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnList__SWIG_2((int)listType, GnLocale.getCPtr(locale), GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnList(GnListType listType, GnLocale locale, GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnList__SWIG_3((int)listType, GnLocale.getCPtr(locale), GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  static private IntPtr SwigConstructGnList(string serializedList) {
  System.IntPtr tempserializedList = GnMarshalUTF8.NativeUtf8FromString(serializedList);
    try {
      return gnsdk_csharp_marshalPINVOKE.new_GnList__SWIG_4(tempserializedList);
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempserializedList);
    }
  }

/**
* constuctor 
*/
  public GnList(string serializedList) : this(GnList.SwigConstructGnList(serializedList), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Tests an existing list for updates and downloads a new list, if available. The application must
* ensure the List module can contact the Gracenote Service to test for a new list version, by
* appropriately configuring the user lookup option.
* Note: This function blocks the current thread until the download is complete; set a status callback function to receive progress messages.
* @param user				User making the list update request
* @return True if an update is available, false otherwise.
* <p><b>Remarks:</b></p>
* Use this function to periodically update a list. The list will be updated if an update is available.
* Optionally an application can check if an update is available before calling this method.
*
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public bool Update(GnUser user, GnStatusEventsDelegate pEventHandler) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnList_Update__SWIG_0(swigCPtr, GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool Update(GnUser user) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnList_Update__SWIG_1(swigCPtr, GnUser.getCPtr(user));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Tests an existing list to determine if a newer revision is available. If available, the new revision is not downloaded. To download
* the new revision the application must call GnList.Update().
* The application must ensure the List module can contact the Gracenote Service to test for a new list version, by
* appropriately configuring the user lookup option.
* Note: This function blocks the current thread until the check is complete; set a status callback function to receive progress messages.
* @param user				User making the list update check request
* @return True if an update is available, false otherwise.
* <p><b>Remarks:</b></p>
* Use this function to periodically check Gracenote Service for updates to an existing list handle.
* <p><b>Note:</b></p>
* You should configure application(s) to automatically check for list updates to ensure use of the
* most current data.
* You should immediately check for updates after constructing a list object from a saved serialized list string as it may
* be out of date.
* This function blocks the current thread until the download is complete;
* set a status callback function to receive progress messages.
*
* Long Running Potential: Network I/O
*/
  public bool UpdateCheck(GnUser user, GnStatusEventsDelegate pEventHandler) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnList_UpdateCheck__SWIG_0(swigCPtr, GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool UpdateCheck(GnUser user) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnList_UpdateCheck__SWIG_1(swigCPtr, GnUser.getCPtr(user));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Serializes a list into encrypted text, so the application can store it for later use.
* <p><b>Note:</b></p>
* If you application is using a GNSDK local storage solution, lists are automatically stored
* and retrieved from a local store according to the configuration of user option.
* Applications implementing their own local storage functionality can use this method
* to render a list into a format that can be stored persistently and restored at a later time using
* the appropriate constructor.
*/
  public GnString Serialize() {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnList_Serialize(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Renders list data to XML.
*  @param levels			List level values to render
*  @param renderFlags		Flags configuring rendering output
*/
  public GnString RenderToXml(uint levels, GnListRenderFlags renderFlags) {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnList_RenderToXml(swigCPtr, levels, (int)renderFlags), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnListElementEnumerable ListElements(uint level) {
    GnListElementEnumerable ret = new GnListElementEnumerable(gnsdk_csharp_marshalPINVOKE.GnList_ListElements(swigCPtr, level), true);
    return ret;
  }

/**
* Retrieves a list element from a list using a specific list element ID.
* If no list element with the ID is found a null list element object is returned.
* @param itemId		List element item ID
*/
  public GnListElement ElementById(uint itemId) {
    GnListElement ret = new GnListElement(gnsdk_csharp_marshalPINVOKE.GnList_ElementById(swigCPtr, itemId), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves list element whose range includes the specified value
* If no list element matching the range is found a null list element object is returned.
* @param range		Value for range comparison
*/
  public GnListElement ElementByRange(uint range) {
    GnListElement ret = new GnListElement(gnsdk_csharp_marshalPINVOKE.GnList_ElementByRange(swigCPtr, range), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves list element whose string matches the specified value.	
* If no list element with the string is found a null list element object is returned.
* @param strEquality		Value of string to look up
*/
  public GnListElement ElementByString(string strEquality) {
  System.IntPtr tempstrEquality = GnMarshalUTF8.NativeUtf8FromString(strEquality);
    try {
      GnListElement ret = new GnListElement(gnsdk_csharp_marshalPINVOKE.GnList_ElementByString(swigCPtr, tempstrEquality), true);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempstrEquality);
    }
  }

/**
* Retrieves list element corresponding to the data object.
* If no list element matching the data object is found a null list element object is returned.
* @param dataObject		Gracenote data object
* @param ordinal			Ordinal
* @param level				List level value
*/
  public GnListElement ElementByGnDataObject(GnDataObject dataObject, uint ordinal, uint level) {
    GnListElement ret = new GnListElement(gnsdk_csharp_marshalPINVOKE.GnList_ElementByGnDataObject(swigCPtr, GnDataObject.getCPtr(dataObject), ordinal, level), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves this list's revision string.
*/
  public string Revision {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnList_Revision_get(swigCPtr) );
	} 

  }

/**
* Retrieves this list's type.
*/
  public GnListType Type {
    get {
      GnListType ret = (GnListType)gnsdk_csharp_marshalPINVOKE.GnList_Type_get(swigCPtr);
      return ret;
    } 
  }

/**
* Retrieves this list's descriptor.
*/
  public GnDescriptor Descriptor {
    get {
      GnDescriptor ret = (GnDescriptor)gnsdk_csharp_marshalPINVOKE.GnList_Descriptor_get(swigCPtr);
      return ret;
    } 
  }

/**
* Retrieves this list's language.
*/
  public GnLanguage Language {
    get {
      GnLanguage ret = (GnLanguage)gnsdk_csharp_marshalPINVOKE.GnList_Language_get(swigCPtr);
      return ret;
    } 
  }

/**
* Retrieves this list's region.
*/
  public GnRegion Region {
    get {
      GnRegion ret = (GnRegion)gnsdk_csharp_marshalPINVOKE.GnList_Region_get(swigCPtr);
      return ret;
    } 
  }

/**
* Retrieves a maximum number of levels in a hierarchy for a given list.
* <p><b>Remarks:</b></p>
* When this function succeeds, the returned parameter contains the number of levels in the given
* list's hierarchy. This level count value is needed when determining which level to access when
* retrieving elements or data from a list.
* Lists can be flat or hierarchical. A flat list has only one level. A hierarchical list has a
* parent-child relationship, where the parent's value is broad enough to encompass its child values
* (for example, a level 1 Rock genre is a parent to level 2 Country Rock and Punk Rock genres). You
* can configure an application to use a single level or the entire hierarchy.
* Level 1 indicates the top level of the list, which usually contains the more general data. The
* highest level value for a list contains the most fine-grained data.
*/
  public uint LevelCount {
    get {
      uint ret = gnsdk_csharp_marshalPINVOKE.GnList_LevelCount_get(swigCPtr);
      return ret;
    } 
  }

}

}
