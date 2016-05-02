
package com.gracenote.gnsdk;

/** 
* Gracenote Data Object - encapsulation of GNSDK delivered media elements and metadata. 
*/ 
 
public class GnDataObject extends GnObject {
  private long swigCPtr;

  protected GnDataObject(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnDataObject_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnDataObject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnDataObject(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

	private GnLocale locale;
	
	private long getLocaleCppPtrAndSaveReference( GnLocale newLocale ) {
		locale = newLocale;
		return GnLocale.getCPtr(newLocale);
	}

  public GnDataObject(GnDataObject obj) {
    this(gnsdk_javaJNI.new_GnDataObject__SWIG_0(GnDataObject.getCPtr(obj), obj), true);
  }

  public GnDataObject(String id, String idTag, String idSrc) throws com.gracenote.gnsdk.GnException {
    this(gnsdk_javaJNI.new_GnDataObject__SWIG_1(id, idTag, idSrc), true);
  }

/** 
*  Deserialize GNSDK data object 
*  @param serializedGdo	[in] Serialized Gracenote data object string 
*  @return Gracenote data object 
*/ 
 
  public static GnDataObject deserialize(String serializedGdo) throws com.gracenote.gnsdk.GnException {
    return new GnDataObject(gnsdk_javaJNI.GnDataObject_deserialize(serializedGdo), true);
  }

/** 
*  Create Gracenote Data Object from XML 
*  @param xml	[in] XML string 
*  @return Gracenote data object 
*/ 
 
  public static GnDataObject createFromXml(String xml) throws com.gracenote.gnsdk.GnException {
    return new GnDataObject(gnsdk_javaJNI.GnDataObject_createFromXml(xml), true);
  }

/** 
*  Serialize this object 
*  @return Serialize Gracenote data object string 
*/ 
 
  public GnString serialize() throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnDataObject_serialize(swigCPtr, this), true);
  }

/** 
* Returns count of the metadata values available for the key. 
* @param valueKey      [in] Key of the value count to return 
* @return count 
*/ 
 
  public long stringValueCount(String valueKey) {
    return gnsdk_javaJNI.GnDataObject_stringValueCount(swigCPtr, this, valueKey);
  }

/** 
* Returns media or metadata value as a string based on the provided key and ordinal. 
* @param valueKey      [in] Key of the value to return 
* @param ordinal		[in] 1-based specifier of a value where multiple values for a key exist 
* @return Value 
*/ 
 
  public String stringValue(String valueKey, long ordinal) {
    return gnsdk_javaJNI.GnDataObject_stringValue__SWIG_0(swigCPtr, this, valueKey, ordinal);
  }

  public String stringValue(String valueKey) {
    return gnsdk_javaJNI.GnDataObject_stringValue__SWIG_1(swigCPtr, this, valueKey);
  }

/** 
* Number of children available for a given key. 
* @param childKey [in] Child key to count 
* @return Count 
* <p> 
* <p><b>Remarks:</b></p> 
* Use this function to count children of a specific data instance; note that only those children 
* accessible in the current type are considered. 
* <p> 
* When this function successfully counts zero (0) occurrences of the child key with no errors, the 
* method returns successfully. 
*/ 
 
  public long childCount(String childKey) {
    return gnsdk_javaJNI.GnDataObject_childCount(swigCPtr, this, childKey);
  }

/** 
* Child data object specified by the key and ordinal 
* @param childKey     	[in] Child key to return 
* @param childOrdinal	[in] 1-based specifier of a child where multiple values for a key exist 
* <p> 
* <p><b>Remarks:</b></p> 
* Use this function to count children of a specific data instance; note that only those children 
* accessible in the current type are considered. 
*/ 
 
  public GnDataObject child(String childKey, long childOrdinal) {
    return new GnDataObject(gnsdk_javaJNI.GnDataObject_child__SWIG_0(swigCPtr, this, childKey, childOrdinal), true);
  }

  public GnDataObject child(String childKey) {
    return new GnDataObject(gnsdk_javaJNI.GnDataObject_child__SWIG_1(swigCPtr, this, childKey), true);
  }

/** 
* Renders contents of the data object as an XML string. 
* @param options	[in] Render options object 
* @return Rendered output string 
*/ 
 
  public GnString render(GnRenderOptions options) throws com.gracenote.gnsdk.GnException {
    return new GnString(gnsdk_javaJNI.GnDataObject_render(swigCPtr, this, GnRenderOptions.getCPtr(options), options), true);
  }

/** 
* Applies lists to use for retrieving and rendering locale-related values. 
* @param	locale Locale to apply to this data object 
* <p><b>Remarks:</b></p> 
* Use this function to set the locale of retrieved and rendered locale-dependent data for this 
* data object. This function overrides any applicable global locale defaults set elsewhere. 
* <p><b>Locale Language Support</b></p> 
* This function supports all locale languages and successfully assigns a locale for this data object. 
* The locale is used for future calls to get data values when locale-dependent values are requested. 
* <p> 
* When list-based locale-specific values are requested from this data object they are returned 
* only if an applicable locale has been successfully set by this method or a default locale has been 
* successfully set elsehwere. 
* <p> 
* When a non-list-based locale-specific values are requested from this data object they are returned 
* only if these values are available from Gracenote Service or the locale database (where online queries 
* are not accessible or permitted). If not, the application uses the default (or "official") locale data for 
* these values. For example, plot values are non-list-based. If a plot summary value is available only in the 
* English language, and the specific locale is defined for the Spanish language, the application 
* displays the plot summary in the English language. 
*/ 
 
  public void locale(GnLocale locale) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnDataObject_locale(swigCPtr, this, getLocaleCppPtrAndSaveReference(locale), locale);
  }

/** 
* Data object's type. 
* @return Type string 
* <p><b>Remarks:</b></p> 
* The data object's contents are not clearly defined. Use this API to retrieve a data object's type, 
* as this enables the application to more accurately determine what data the specific data it contains. 
* Typically an application will use data objects subclassed from the data object, which do specifically 
* define a type. 
*/ 
 
  public String getType() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnDataObject_getType(swigCPtr, this);
  }

/** 
*  Flag indicating if object is specified type 
*  @param strType	[in] Type string 
*  @return True if object is if provided type, false otherwise 
*/ 
 
  public boolean isType(String strType) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnDataObject_isType(swigCPtr, this, strType);
  }

}
