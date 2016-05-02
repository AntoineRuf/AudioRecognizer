
package com.gracenote.gnsdk;

/**  
* list_element_iterable 
*//** 
* Gracenote list. 
*/ 
 
public class GnList extends GnObject {
  private long swigCPtr;

  protected GnList(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnList_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnList obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnList(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

	private IGnStatusEvents pEventHandler;
	private IGnStatusEventsProxyU eventHandlerProxy;
	private GnLocale locale;

/** 
* constuctor  
*/ 
 
  public GnList(GnListType listType, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnList__SWIG_0(listType.swigValue(), language.swigValue(), region.swigValue(), descriptor.swigValue(), GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public GnList(GnListType listType, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnList__SWIG_1(listType.swigValue(), language.swigValue(), region.swigValue(), descriptor.swigValue(), GnUser.getCPtr(user), user);
}

/** 
* constuctor  
*/ 
 
  public GnList(GnListType listType, GnLocale locale, GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnList__SWIG_2(listType.swigValue(), GnLocale.getCPtr(locale), locale, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public GnList(GnListType listType, GnLocale locale, GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnList__SWIG_3(listType.swigValue(), GnLocale.getCPtr(locale), locale, GnUser.getCPtr(user), user);
}

/** 
* constuctor  
*/ 
 
  public GnList(String serializedList) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnList__SWIG_4(serializedList);
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
* <p> 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public boolean update(GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnList_update__SWIG_0(swigCPtr, this, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
  }

  public boolean update(GnUser user) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnList_update__SWIG_1(swigCPtr, this, GnUser.getCPtr(user), user);
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
* <p> 
* Long Running Potential: Network I/O 
*/ 
 
  public boolean updateCheck(GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnList_updateCheck__SWIG_0(swigCPtr, this, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
  }

  public boolean updateCheck(GnUser user) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnList_updateCheck__SWIG_1(swigCPtr, this, GnUser.getCPtr(user), user);
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
 
  public GnString serialize() throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnList_serialize(swigCPtr, this), true);
  }

/** 
*  Renders list data to XML. 
*  @param levels			List level values to render 
*  @param renderFlags		Flags configuring rendering output 
*/ 
 
  public GnString renderToXml(long levels, GnListRenderFlags renderFlags) throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnList_renderToXml(swigCPtr, this, levels, renderFlags.swigValue()), true);
  }

/** 
* Retrieves this list's type. 
*/ 
 
  public GnListType type() throws com.gracenote.gnsdk.GnException {
    return GnListType.swigToEnum(gnsdk_javaJNI.GnList_type(swigCPtr, this));
  }

/** 
* Retrieves this list's descriptor. 
*/ 
 
  public GnDescriptor descriptor() throws com.gracenote.gnsdk.GnException {
    return GnDescriptor.swigToEnum(gnsdk_javaJNI.GnList_descriptor(swigCPtr, this));
  }

/** 
* Retrieves this list's language. 
*/ 
 
  public GnLanguage language() throws com.gracenote.gnsdk.GnException {
    return GnLanguage.swigToEnum(gnsdk_javaJNI.GnList_language(swigCPtr, this));
  }

/** 
* Retrieves this list's region. 
*/ 
 
  public GnRegion region() throws com.gracenote.gnsdk.GnException {
    return GnRegion.swigToEnum(gnsdk_javaJNI.GnList_region(swigCPtr, this));
  }

/** 
* Retrieves this list's revision string. 
*/ 
 
  public String revision() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnList_revision(swigCPtr, this);
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
 
  public long levelCount() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnList_levelCount(swigCPtr, this);
  }

  public GnListElementIterable listElements(long level) {
    return new GnListElementIterable(gnsdk_javaJNI.GnList_listElements(swigCPtr, this, level), true);
  }

/** 
* Retrieves a list element from a list using a specific list element ID. 
* If no list element with the ID is found a null list element object is returned. 
* @param itemId		List element item ID 
*/ 
 
  public GnListElement elementById(long itemId) throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnList_elementById(swigCPtr, this, itemId), true);
  }

/** 
* Retrieves list element whose range includes the specified value 
* If no list element matching the range is found a null list element object is returned. 
* @param range		Value for range comparison 
*/ 
 
  public GnListElement elementByRange(long range) throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnList_elementByRange(swigCPtr, this, range), true);
  }

/** 
* Retrieves list element whose string matches the specified value.	 
* If no list element with the string is found a null list element object is returned. 
* @param strEquality		Value of string to look up 
*/ 
 
  public GnListElement elementByString(String strEquality) throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnList_elementByString(swigCPtr, this, strEquality), true);
  }

/** 
* Retrieves list element corresponding to the data object. 
* If no list element matching the data object is found a null list element object is returned. 
* @param dataObject		Gracenote data object 
* @param ordinal			Ordinal 
* @param level				List level value 
*/ 
 
  public GnListElement elementByGnDataObject(GnDataObject dataObject, long ordinal, long level) throws com.gracenote.gnsdk.GnException {
    return new GnListElement(gnsdk_javaJNI.GnList_elementByGnDataObject(swigCPtr, this, GnDataObject.getCPtr(dataObject), dataObject, ordinal, level), true);
  }

}
