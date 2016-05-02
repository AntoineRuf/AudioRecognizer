
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* \class GnMusicIdOptions
* Configures options for GnMusicId
*/
public class GnMusicIdOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnMusicIdOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicIdOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicIdOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicIdOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
*  Indicates whether the MusicID query should be performed against local embedded databases or online.
*  @param lookupMode  [in] One of the #GnLookupMode values
*/
  public void LookupMode(GnLookupMode lookupMode) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_LookupMode(swigCPtr, (int)lookupMode);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Indicates the lookup data value for the MusicID query.
*  @param lookupData [in] One of the #GnLookupData values
*  @param bEnable    [in] Set lookup data
*/
  public void LookupData(GnLookupData lookupData, bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_LookupData(swigCPtr, (int)lookupData, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Indicates the preferred language of the returned results.
*  @param preferredLanguage [in] One of the GNSDK language values
*/
  public void PreferResultLanguage(GnLanguage preferredLanguage) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_PreferResultLanguage(swigCPtr, (int)preferredLanguage);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Indicates the preferred external ID of the returned results.
*  Only available where single result is also requested.
*  @param strExternalId [in] Gracenote external ID source name
*/
  public void PreferResultExternalId(string strExternalId) {
  System.IntPtr tempstrExternalId = GnMarshalUTF8.NativeUtf8FromString(strExternalId);
    try {
      gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_PreferResultExternalId(swigCPtr, tempstrExternalId);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempstrExternalId);
    }
  }

/**
*  Indicates using cover art to prefer the returned results.
*  @param bEnable [in] Set prefer cover art
*/
  public void PreferResultCoverart(bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_PreferResultCoverart(swigCPtr, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Indicates whether a response must return only the single best result.
*  When enabled a single full result is returned, when disabled multiple partial results may be returned.
*  @param bEnable [in] Set single result
*  <p><b>Remarks:</b></p>
*  If enabled, the MusicID library selects the single best result based on the query type and input.
*/
  public void ResultSingle(bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_ResultSingle(swigCPtr, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Enables or disables revision check option.
*  @param bEnable [in] Set revision check
*
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup)
*/
  public void RevisionCheck(bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_RevisionCheck(swigCPtr, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Specfies whether a response must return a range of results that begin and count at a specified values.
*  @param resultStart  [in] Result range start value
*  <p><b>Remarks:</b></p>
*  This Option is useful for paging through results.
*  <p><b>Note:</b></p>
*  Gracenote Service enforces that the range start value must be less than or equal to the total
*  number of results. If you specify a range start value that is greater than the total number of
*  results, no results are returned.
*/
  public void ResultRangeStart(uint resultStart) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_ResultRangeStart(swigCPtr, resultStart);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public void ResultCount(uint resultCount) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_ResultCount(swigCPtr, resultCount);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* This option allows setting of a specific network interface to be used with connections made by  
* this object. Choosing which interface to use can be beneficial for systems with multiple 
* network interfaces. Without setting this option, connections will be made of the default network interface
* as decided by the operating system.
*  @param ipAddress [in] local IP address for the desired network interface
*/
  public void NetworkInterface(string ipAddress) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_NetworkInterface(swigCPtr, ipAddress);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Set option using option name
*  @param option   [in] Option name
*  @param value	[in] Option value
*/
  public void Custom(string option, string value) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_Custom__SWIG_0(swigCPtr, option, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Set option using option name
*  @param option   [in] Option name
*  @param bEnable	[in] Option enable true/false
*/
  public void Custom(string option, bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdOptions_Custom__SWIG_1(swigCPtr, option, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
