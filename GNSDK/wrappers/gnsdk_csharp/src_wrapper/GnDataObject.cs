
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Gracenote Data Object - encapsulation of GNSDK delivered media elements and metadata.
*/
public class GnDataObject : GnObject {
  private HandleRef swigCPtr;

  internal GnDataObject(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnDataObject_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnDataObject obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnDataObject() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnDataObject(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public GnDataObject(GnDataObject obj) : this(gnsdk_csharp_marshalPINVOKE.new_GnDataObject__SWIG_0(GnDataObject.getCPtr(obj)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnDataObject(string id, string idTag, string idSrc) : this(gnsdk_csharp_marshalPINVOKE.new_GnDataObject__SWIG_1(id, idTag, idSrc), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Deserialize GNSDK data object
*  @param serializedGdo	[in] Serialized Gracenote data object string
*  @return Gracenote data object
*/
  public static GnDataObject Deserialize(string serializedGdo) {
    GnDataObject ret = new GnDataObject(gnsdk_csharp_marshalPINVOKE.GnDataObject_Deserialize(serializedGdo), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Create Gracenote Data Object from XML
*  @param xml	[in] XML string
*  @return Gracenote data object
*/
  public static GnDataObject CreateFromXml(string xml) {
    GnDataObject ret = new GnDataObject(gnsdk_csharp_marshalPINVOKE.GnDataObject_CreateFromXml(xml), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Serialize this object
*  @return Serialize Gracenote data object string
*/
  public GnString Serialize() {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnDataObject_Serialize(swigCPtr), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Returns count of the metadata values available for the key.
* @param valueKey      [in] Key of the value count to return
* @return count
*/
  public uint StringValueCount(string valueKey) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnDataObject_StringValueCount(swigCPtr, valueKey);
    return ret;
  }

/**
* Returns media or metadata value as a string based on the provided key and ordinal.
* @param valueKey      [in] Key of the value to return
* @param ordinal		[in] 1-based specifier of a value where multiple values for a key exist
* @return Value
*/
  public string StringValue(string valueKey, uint ordinal) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnDataObject_StringValue__SWIG_0(swigCPtr, valueKey, ordinal);
    return ret;
  }

  public string StringValue(string valueKey) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnDataObject_StringValue__SWIG_1(swigCPtr, valueKey);
    return ret;
  }

/**
* Number of children available for a given key.
* @param childKey [in] Child key to count
* @return Count
*
* <p><b>Remarks:</b></p>
* Use this function to count children of a specific data instance; note that only those children
* accessible in the current type are considered.
*
* When this function successfully counts zero (0) occurrences of the child key with no errors, the
* method returns successfully.
*/
  public uint ChildCount(string childKey) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnDataObject_ChildCount(swigCPtr, childKey);
    return ret;
  }

/**
* Child data object specified by the key and ordinal
* @param childKey     	[in] Child key to return
* @param childOrdinal	[in] 1-based specifier of a child where multiple values for a key exist
*
* <p><b>Remarks:</b></p>
* Use this function to count children of a specific data instance; note that only those children
* accessible in the current type are considered.
*/
  public GnDataObject Child(string childKey, uint childOrdinal) {
    GnDataObject ret = new GnDataObject(gnsdk_csharp_marshalPINVOKE.GnDataObject_Child__SWIG_0(swigCPtr, childKey, childOrdinal), true);
    return ret;
  }

  public GnDataObject Child(string childKey) {
    GnDataObject ret = new GnDataObject(gnsdk_csharp_marshalPINVOKE.GnDataObject_Child__SWIG_1(swigCPtr, childKey), true);
    return ret;
  }

/**
* Renders contents of the data object as an XML string.
* @param options	[in] Render options object
* @return Rendered output string
*/
  public GnString Render(GnRenderOptions options) {
    GnString ret = new GnString(gnsdk_csharp_marshalPINVOKE.GnDataObject_Render(swigCPtr, GnRenderOptions.getCPtr(options)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
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
*
* When list-based locale-specific values are requested from this data object they are returned
* only if an applicable locale has been successfully set by this method or a default locale has been
* successfully set elsehwere.
*
* When a non-list-based locale-specific values are requested from this data object they are returned
* only if these values are available from Gracenote Service or the locale database (where online queries
* are not accessible or permitted). If not, the application uses the default (or "official") locale data for
* these values. For example, plot values are non-list-based. If a plot summary value is available only in the
* English language, and the specific locale is defined for the Spanish language, the application
* displays the plot summary in the English language.
*/
  public void Locale(GnLocale locale) {
    gnsdk_csharp_marshalPINVOKE.GnDataObject_Locale(swigCPtr, GnLocale.getCPtr(locale));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
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
  public string GetType() {
    string ret = gnsdk_csharp_marshalPINVOKE.GnDataObject_GetType(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Flag indicating if object is specified type
*  @param strType	[in] Type string
*  @return True if object is if provided type, false otherwise
*/
  public bool IsType(string strType) {
  System.IntPtr tempstrType = GnMarshalUTF8.NativeUtf8FromString(strType);
    try {
      bool ret = gnsdk_csharp_marshalPINVOKE.GnDataObject_IsType(swigCPtr, tempstrType);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempstrType);
    }
  }

}

}
