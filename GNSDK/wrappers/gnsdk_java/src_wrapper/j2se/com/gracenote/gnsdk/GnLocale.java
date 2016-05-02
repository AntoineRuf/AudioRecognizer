
package com.gracenote.gnsdk;

/** 
* locale_info_iterable 
*//** 
* Loads Gracenote data for the specified locale 
* <p> 
* Locales are used by GNSDK for various reasons and it's the best practice to have an appropriate 
* locale loaded. Typically an application uses user preferences or device settings to determine the 
* region and language of the loaded locale. To determine what locale group and descriptor to load 
* work with your Gracenote support representative. 
* <p> 
* Locale data is only loaded if it not already loaded. It can be loaded from Gracenote Service or from a 
* local database. To use a local database a storage provider must be enabled, such as {@link GnStorageSqlite}. 
* Where a local database is used GNSDK will attempt to load locale data from it, if not found locale data 
* will be downloaded from Gracenote Service and written to the local database. 
* <p> 
* Locale load can be canceled at any time by setting the "canceller" provided in any {@link IGnStatusEvents} 
* delegate method. No cancel method is provided on {@link GnLocale} object because loading can happen on object 
* construction. 
* <p> 
* Loading a locale can be lengthy, so some applications may wish to perform this operation on a background 
* thread to avoid stalling the main thread. 
* <p> 
* Once a locale is loaded it can be set as the group default. The default locale is automatically 
* associated with appropriate response objects returned by GNSDK, allowing Gracenote descriptive data, 
* such as genres, to be returned according to the locales region and language. 
* <p> 
* Gracenote data is regularly updated; therefore Locale data should also be updated. GNSDK can detect 
* when an application should update a locale and call an {@link IGnSystemEvents} delegate method providing the {@link GnLocale} 
* object. Your application can register for system events via a {@link GnManager} instance. Alternatively your 
* application can keep the {@link GnLocale} object and periodically invoke update. It is Gracenote best practice 
* that your application implement a locale update procedure. 
*/ 
 
public class GnLocale extends GnObject {
  private long swigCPtr;

  protected GnLocale(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnLocale_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLocale obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLocale(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

	private IGnStatusEvents pEventHandler;
	private IGnStatusEventsProxyU eventHandlerProxy;

/** 
* Constructs {@link GnLocale} object 
*/ 
 
  public GnLocale(GnLocaleInfo localeInfo, GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
    swigCPtr = gnsdk_javaJNI.new_GnLocale__SWIG_0(GnLocaleInfo.getCPtr(localeInfo), localeInfo, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public GnLocale(GnLocaleInfo localeInfo, GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
    swigCPtr = gnsdk_javaJNI.new_GnLocale__SWIG_1(GnLocaleInfo.getCPtr(localeInfo), localeInfo, GnUser.getCPtr(user), user);
}

/** 
* Loads the specified locale 
* @param group				Locale group specifies which locale data is loaded 
* @param language			Language of locale data 
* @param region			Region of the locale data where applicable 
* @param descriptor		Descriptor, or verbosity, of the locale data where applicable 
* @param user				User object 
* @param pEventHandler     Status events delegate 
* <p><b>Note</b><p> This method blocks the current thread until the load is complete; 
* set an {@link IGnStatusEvents} delegate to receive progress messages. 
* <p> 
* Long Running Potential: Network I/O, File system I/O 
*/ 
 
  public GnLocale(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
    swigCPtr = gnsdk_javaJNI.new_GnLocale__SWIG_2(group.swigValue(), language.swigValue(), region.swigValue(), descriptor.swigValue(), GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

/** 
* Loads the specified locale 
* @param group				Locale group specifies which locale data is loaded 
* @param language			Language of locale data 
* @param region			Region of the locale data where applicable 
* @param descriptor		Descriptor, or verbosity, of the locale data where applicable 
* @param user				User object 
* <p><b>Note</b><p> This method blocks the current thread until the load is complete. 
* <p> 
* Long Running Potential: Network I/O, File system I/O 
*/ 
 
  public GnLocale(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
    swigCPtr = gnsdk_javaJNI.new_GnLocale__SWIG_3(group.swigValue(), language.swigValue(), region.swigValue(), descriptor.swigValue(), GnUser.getCPtr(user), user);
}

/** 
* Loads the specified locale 
* @param group				Locale group specifies which locale data is loaded 
* @param langIsoCode		Language of locale data as an ISO code 
* @param region			Region of the locale data where applicable 
* @param descriptor		Descriptor, or verbosity, of the locale data where applicable 
* @param user				User object 
* @param pEventHandler     Status events delegate 
* <p><b>Note</b><p> This method blocks the current thread until the load is complete; 
* set an {@link IGnStatusEvents} delegate to receive progress messages. 
* <p> 
* Long Running Potential: Network I/O, File system I/O 
*/ 
 
  public GnLocale(GnLocaleGroup group, String langIsoCode, GnRegion region, GnDescriptor descriptor, GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
    swigCPtr = gnsdk_javaJNI.new_GnLocale__SWIG_4(group.swigValue(), langIsoCode, region.swigValue(), descriptor.swigValue(), GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

/** 
* Loads the specified locale 
* @param group				Locale group specifies which locale data is loaded 
* @param langIsoCode		Language of locale data as an ISO code 
* @param region			Region of the locale data where applicable 
* @param descriptor		Descriptor, or verbosity, of the locale data where applicable 
* @param user				User object 
* <p><b>Note</b><p> This method blocks the current thread until the load is complete. 
* <p> 
* Long Running Potential: Network I/O, File system I/O 
*/ 
 
  public GnLocale(GnLocaleGroup group, String langIsoCode, GnRegion region, GnDescriptor descriptor, GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
    swigCPtr = gnsdk_javaJNI.new_GnLocale__SWIG_5(group.swigValue(), langIsoCode, region.swigValue(), descriptor.swigValue(), GnUser.getCPtr(user), user);
}

/** 
* Reconstitutes locale from serialized locale data. 
* @param serializedLocale	String of serialized locale handle data 
*/ 
 
  public GnLocale(String serializedLocale) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
    swigCPtr = gnsdk_javaJNI.new_GnLocale__SWIG_6(serializedLocale);
}

/** 
* Get Locale information 95 
*/ 
 
  public GnLocaleInfo localeInformation() {
    return new GnLocaleInfo(gnsdk_javaJNI.GnLocale_localeInformation(swigCPtr, this), false);
  }

/** 
* Retrieves this locale's revision string. 
* @return Revision 
*/ 
 
  public String revision() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnLocale_revision(swigCPtr, this);
  }

/** 
* Sets this locale as the default locale for the 'locale group' (see {@link GnLocaleGroup}). 
*/ 
 
  public void setGroupDefault() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnLocale_setGroupDefault(swigCPtr, this);
  }

  public static GnLocaleInfoIterable storedLocales() {
    return new GnLocaleInfoIterable(gnsdk_javaJNI.GnLocale_storedLocales(), true);
  }

/** 
* Updates a locale with new versions of the locale data, if available. 
* The application must ensure Gracenote Service can be contacted to test for a new list version 
* by appropriately configuring the user's lookup mode to allow online access. 
* <p> 
* The application can cancel the update procedure by setting the "canceller" in any method 
* called in the status event delegate. 
* <p> 
* @param user				User requesting the locale update 
* @param pEventHandler		Status events delegate 
* @return True indicates updates were applied, false indicates no updates are available 
* <p> 
* <p><b>Note</b></p> 
* This methods blocks the current thread until the update procedure is complete; 
* set a status events delegate to receive progress messages. 
* <p> 
* Long Running Potential: Network I/O, File system I/O 
*/ 
 
  public boolean update(GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnLocale_update__SWIG_0(swigCPtr, this, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
  }

/** 
* Updates a locale with new versions of the locale data, if available. 
* The application must ensure Gracenote Service can be contacted to test for a new list version 
* by appropriately configuring the user's lookup mode to allow online access. 
* <p> 
* @param user				User requesting the locale update 
* @return True indicates updates were applied, false indicates no updates are available 
* <p> 
* <p><b>Note</b></p> 
* This methods blocks the current thread until the update procedure is complete; 
* set a status events delegate to receive progress messages. 
* <p> 
* Long Running Potential: Network I/O, File system I/O 
*/ 
 
  public boolean update(GnUser user) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnLocale_update__SWIG_1(swigCPtr, this, GnUser.getCPtr(user), user);
  }

/** 
* Tests a locale to determine if a newer revision of any locale data is available. If available the new data 
* is not downloaded. To download the application must invoke update. 
* The application must ensure Gracenote Service can be contacted to test for a new list version 
* by appropriately configuring the user's lookup mode to allow online access. 
* <p> 
* The application can cancel the update check procedure by setting the "canceller" in any method 
* called in the status event delegate. 
* <p> 
* @param user				User requesting the locale update check 
* @param pEventHandler		Status event delegate 
* @return True indicates updates are available, false otherwise. 
* <p> 
* <p><b>Remarks:</b></p> 
* This method can be invoked periodically to check Gracenote Service for updates to locale data. 
* <p> 
* <p><b>Note:</b></p> 
* You should immediately check for updates after constructing a locale object from a saved serialized locale 
* string as it may be out of date. 
* <p> 
* This methods blocks the current thread until the update procedure is complete; 
* set a status events delegate to receive progress messages. 
* <p> 
* Long Running Potential: Network I/O 
*/ 
 
  public boolean updateCheck(GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnLocale_updateCheck__SWIG_0(swigCPtr, this, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
  }

/** 
* Tests a locale to determine if a newer revision of any locale data is available. If available the new data 
* is not downloaded. To download the application must invoke update. 
* The application must ensure Gracenote Service can be contacted to test for a new list version 
* by appropriately configuring the user's lookup mode to allow online access. 
* <p> 
* @param user				User requesting the locale update check 
* @return True indicates updates are available, false otherwise. 
* <p> 
* <p><b>Remarks:</b></p> 
* This method can be invoked periodically to check Gracenote Service for updates to locale data. 
* <p> 
* <p><b>Note:</b></p> 
* You should immediately check for updates after constructing a locale object from a saved serialized locale 
* string as it may be out of date. 
* <p> 
* This methods blocks the current thread until the update procedure is complete; 
* set a status events delegate to receive progress messages. 
* <p> 
* Long Running Potential: Network I/O 
*/ 
 
  public boolean updateCheck(GnUser user) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnLocale_updateCheck__SWIG_1(swigCPtr, this, GnUser.getCPtr(user), user);
  }

/** 
* Serializes locale data into encrypted text string that the application can store locally for later use. 
* <p><b>Note:</b></p> 
* If the application is using a GNSDK local storage solution locale data is automatically stored 
* and retrieved from a local store according to the configuration of user lookup option. 
* Applications implementing their own local storage functionality can use this method to 
* render a locale into a format that can be stored persistently and restored at a later time using 
* the appropriate constructor. 
* @return Serialize locale data 
*/ 
 
  public GnString serialize() throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnLocale_serialize(swigCPtr, this), true);
  }

}
