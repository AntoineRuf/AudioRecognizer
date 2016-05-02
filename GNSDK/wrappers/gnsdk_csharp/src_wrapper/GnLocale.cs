
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* locale_info_iterable
*//**
* Loads Gracenote data for the specified locale
*
* Locales are used by GNSDK for various reasons and it's the best practice to have an appropriate
* locale loaded. Typically an application uses user preferences or device settings to determine the
* region and language of the loaded locale. To determine what locale group and descriptor to load
* work with your Gracenote support representative.
*
* Locale data is only loaded if it not already loaded. It can be loaded from Gracenote Service or from a
* local database. To use a local database a storage provider must be enabled, such as GnStorageSqlite.
* Where a local database is used GNSDK will attempt to load locale data from it, if not found locale data
* will be downloaded from Gracenote Service and written to the local database.
*
* Locale load can be canceled at any time by setting the "canceller" provided in any IGnStatusEvents
* delegate method. No cancel method is provided on GnLocale object because loading can happen on object
* construction.
*
* Loading a locale can be lengthy, so some applications may wish to perform this operation on a background
* thread to avoid stalling the main thread.
*
* Once a locale is loaded it can be set as the group default. The default locale is automatically
* associated with appropriate response objects returned by GNSDK, allowing Gracenote descriptive data,
* such as genres, to be returned according to the locales region and language.
*
* Gracenote data is regularly updated; therefore Locale data should also be updated. GNSDK can detect
* when an application should update a locale and call an IGnSystemEvents delegate method providing the GnLocale
* object. Your application can register for system events via a GnManager instance. Alternatively your
* application can keep the GnLocale object and periodically invoke update. It is Gracenote best practice
* that your application implement a locale update procedure.
*/
public class GnLocale : GnObject {
  private HandleRef swigCPtr;

  internal GnLocale(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnLocale_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLocale obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLocale() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLocale(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
* Constructs GnLocale object
*/
  public GnLocale(GnLocaleInfo localeInfo, GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnLocale__SWIG_0(GnLocaleInfo.getCPtr(localeInfo), GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnLocale(GnLocaleInfo localeInfo, GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnLocale__SWIG_1(GnLocaleInfo.getCPtr(localeInfo), GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
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
* set an IGnStatusEvents delegate to receive progress messages.
*
* Long Running Potential: Network I/O, File system I/O
*/
  public GnLocale(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnLocale__SWIG_2((int)group, (int)language, (int)region, (int)descriptor, GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Loads the specified locale
* @param group			Locale group specifies which locale data is loaded
* @param language		Language of locale data
* @param region			Region of the locale data where applicable
* @param descriptor		Descriptor, or verbosity, of the locale data where applicable
* @param user			User object
* <p><b>Note</b><p> This method blocks the current thread until the load is complete;
* set an IGnStatusEvents delegate to receive progress messages.
*
* Long Running Potential: Network I/O, File system I/O
*/
  public GnLocale(GnLocaleGroup group, GnLanguage language, GnRegion region, GnDescriptor descriptor, GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnLocale__SWIG_3((int)group, (int)language, (int)region, (int)descriptor, GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  static private IntPtr SwigConstructGnLocale(GnLocaleGroup group, string langIsoCode, GnRegion region, GnDescriptor descriptor, GnUser user, GnStatusEventsDelegate pEventHandler) {
  System.IntPtr templangIsoCode = GnMarshalUTF8.NativeUtf8FromString(langIsoCode);
    try {
      return gnsdk_csharp_marshalPINVOKE.new_GnLocale__SWIG_4((int)group, templangIsoCode, (int)region, (int)descriptor, GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler));
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(templangIsoCode);
    }
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
* set an IGnStatusEvents delegate to receive progress messages.
*
* Long Running Potential: Network I/O, File system I/O
*/
  public GnLocale(GnLocaleGroup group, string langIsoCode, GnRegion region, GnDescriptor descriptor, GnUser user, GnStatusEventsDelegate pEventHandler) : this(GnLocale.SwigConstructGnLocale(group, langIsoCode, region, descriptor, user, pEventHandler), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  static private IntPtr SwigConstructGnLocale(GnLocaleGroup group, string langIsoCode, GnRegion region, GnDescriptor descriptor, GnUser user) {
  System.IntPtr templangIsoCode = GnMarshalUTF8.NativeUtf8FromString(langIsoCode);
    try {
      return gnsdk_csharp_marshalPINVOKE.new_GnLocale__SWIG_5((int)group, templangIsoCode, (int)region, (int)descriptor, GnUser.getCPtr(user));
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(templangIsoCode);
    }
  }

/**
* Loads the specified locale
* @param group				Locale group specifies which locale data is loaded
* @param langIsoCode		Language of locale data as an ISO code
* @param region				Region of the locale data where applicable
* @param descriptor			Descriptor, or verbosity, of the locale data where applicable
* @param user				User object
* <p><b>Note</b><p> This method blocks the current thread until the load is complete;
* set an IGnStatusEvents delegate to receive progress messages.
*
* Long Running Potential: Network I/O, File system I/O
*/
  public GnLocale(GnLocaleGroup group, string langIsoCode, GnRegion region, GnDescriptor descriptor, GnUser user) : this(GnLocale.SwigConstructGnLocale(group, langIsoCode, region, descriptor, user), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  static private IntPtr SwigConstructGnLocale(string serializedLocale) {
  System.IntPtr tempserializedLocale = GnMarshalUTF8.NativeUtf8FromString(serializedLocale);
    try {
      return gnsdk_csharp_marshalPINVOKE.new_GnLocale__SWIG_6(tempserializedLocale);
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempserializedLocale);
    }
  }

/**
* Reconstitutes locale from serialized locale data.
* @param serializedLocale	String of serialized locale handle data
*/
  public GnLocale(string serializedLocale) : this(GnLocale.SwigConstructGnLocale(serializedLocale), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Sets this locale as the default locale for the 'locale group' (see GnLocaleGroup).
*/
  public void SetGroupDefault() {
    gnsdk_csharp_marshalPINVOKE.GnLocale_SetGroupDefault(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Updates a locale with new versions of the locale data, if available.
* The application must ensure Gracenote Service can be contacted to test for a new list version
* by appropriately configuring the user's lookup mode to allow online access.
*
* The application can cancel the update procedure by setting the "canceller" in any method
* called in the status event delegate.
*
* @param user				User requesting the locale update
* @param pEventHandler		Status events delegate
* @return True indicates updates were applied, false indicates no updates are available
*
* <p><b>Note</b></p>
* This methods blocks the current thread until the update procedure is complete;
* set a status events delegate to receive progress messages.
*
* Long Running Potential: Network I/O, File system I/O
*/
  public bool Update(GnUser user, GnStatusEventsDelegate pEventHandler) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnLocale_Update__SWIG_0(swigCPtr, GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Updates a locale with new versions of the locale data, if available.
* The application must ensure Gracenote Service can be contacted to test for a new list version
* by appropriately configuring the user's lookup mode to allow online access.
*
* The application can cancel the update procedure by setting the "canceller" in any method
* called in the status event delegate.
*
* @param user				User requesting the locale update
* @return True indicates updates were applied, false indicates no updates are available
*
* <p><b>Note</b></p>
* This methods blocks the current thread until the update procedure is complete;
* set a status events delegate to receive progress messages.
*
* Long Running Potential: Network I/O, File system I/O
*/
  public bool Update(GnUser user) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnLocale_Update__SWIG_1(swigCPtr, GnUser.getCPtr(user));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Tests a locale to determine if a newer revision of any locale data is available. If available the new data
* is not downloaded. To download the application must invoke update.
* The application must ensure Gracenote Service can be contacted to test for a new list version
* by appropriately configuring the user's lookup mode to allow online access.
*
* The application can cancel the update check procedure by setting the "canceller" in any method
* called in the status event delegate.
*
* @param user				User requesting the locale update check
* @param pEventHandler		Status event delegate
* @return True indicates updates are available, false otherwise.
*
* <p><b>Remarks:</b></p>
* This method can be invoked periodically to check Gracenote Service for updates to locale data.
*
* <p><b>Note:</b></p>
* You should immediately check for updates after constructing a locale object from a saved serialized locale
* string as it may be out of date.
*
* This methods blocks the current thread until the update procedure is complete;
* set a status events delegate to receive progress messages.
*
* Long Running Potential: Network I/O
*/
  public bool UpdateCheck(GnUser user, GnStatusEventsDelegate pEventHandler) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnLocale_UpdateCheck__SWIG_0(swigCPtr, GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Tests a locale to determine if a newer revision of any locale data is available. If available the new data
* is not downloaded. To download the application must invoke update.
* The application must ensure Gracenote Service can be contacted to test for a new list version
* by appropriately configuring the user's lookup mode to allow online access.
*
* The application can cancel the update check procedure by setting the "canceller" in any method
* called in the status event delegate.
*
* @param user				User requesting the locale update check
* @return True indicates updates are available, false otherwise.
*
* <p><b>Remarks:</b></p>
* This method can be invoked periodically to check Gracenote Service for updates to locale data.
*
* <p><b>Note:</b></p>
* You should immediately check for updates after constructing a locale object from a saved serialized locale
* string as it may be out of date.
*
* This methods blocks the current thread until the update procedure is complete;
* set a status events delegate to receive progress messages.
*
* Long Running Potential: Network I/O
*/
  public bool UpdateCheck(GnUser user) {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnLocale_UpdateCheck__SWIG_1(swigCPtr, GnUser.getCPtr(user));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
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
  public GnString Serialize() {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnLocale_Serialize(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves this locale's revision string.
* @return Revision
*/
  public string Revision {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnLocale_Revision_get(swigCPtr) );
	} 

  }

/**
* Get Locale information 95
*/
  public GnLocaleInfo LocaleInformation {
    get {
      GnLocaleInfo ret = new GnLocaleInfo(gnsdk_csharp_marshalPINVOKE.GnLocale_LocaleInformation_get(swigCPtr), false);
      return ret;
    } 
  }

  public GnLocaleInfoEnumerable StoredLocales {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnLocale_StoredLocales_get(swigCPtr);
      GnLocaleInfoEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnLocaleInfoEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
