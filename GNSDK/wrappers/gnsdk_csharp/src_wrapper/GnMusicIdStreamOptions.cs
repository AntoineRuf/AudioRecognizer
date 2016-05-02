
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Configures options for GnMusicIdStream
*/
public class GnMusicIdStreamOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnMusicIdStreamOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicIdStreamOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicIdStreamOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicIdStreamOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
*  Specifies whether identification should be performed against local embedded databases or online.
*  @param lookupMode  [in] One of the GnLookupMode values
*/
  public void LookupMode(GnLookupMode lookupMode) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_LookupMode(swigCPtr, (int)lookupMode);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Specifies which data should be included in the response
*  @param val 		[in] Set One of the #GnLookupData values
*  @param enable 	[in] True or false to enable or disable
*/
  public void LookupData(GnLookupData val, bool enable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_LookupData(swigCPtr, (int)val, enable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  @deprecated To set language provide appropriate GnLocale object with GnMusicIdStream constructor
*  @param preferredLanguage		[in] preferred language for result
*/
  public void PreferResultLanguage(GnLanguage preferredLanguage) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_PreferResultLanguage(swigCPtr, (int)preferredLanguage);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Specifies preference for results that contain the provided external identifier
* <p><b>Remarks:</b></p>
* This option is currently only supported when online processing is enabled and single
* result is specified.
* @param preferredExternalId 	[in] The name of an external identifier that should be preferred when selecting matches
*/
  public void PreferResultExternalId(string preferredExternalId) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_PreferResultExternalId(swigCPtr, preferredExternalId);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Specifies preference for results that have cover art associated
*  @param bEnable 	[in] Set prefer cover art.
*/
  public void PreferResultCoverart(bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_PreferResultCoverart(swigCPtr, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Specifies whether a response must return only the single best result.
*  When enabled a single full result is returned, when disabled multiple partial results may be returned.
*  @param bEnable 	[in] Option, default is true. True to enable, false to disable.
*/
  public void ResultSingle(bool bEnable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_ResultSingle(swigCPtr, bEnable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Specifies whether a response must return a range of results that begin at the specified values
*  @param resultStart  [in] Result range start value
*  <p><b>Remarks:</b></p>
*  This Option is useful for paging through results.
*  <p><b>Note:</b></p>
*  Gracenote Service enforces that the range start value must be less than or equal to the total
*  number of results. If you specify a range start value that is greater than the total number of
*  results, no results are returned.
*/
  public void ResultRangeStart(uint resultStart) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_ResultRangeStart(swigCPtr, resultStart);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Specifies the number of results to return in the response
* @param resultCount 	[in] Number of results
*
*/
  public void ResultCount(uint resultCount) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_ResultCount(swigCPtr, resultCount);
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
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_NetworkInterface(swigCPtr, ipAddress);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  General option setting for custom string options
*  @param optionKey   [in] Option name
*  @param value	   [in] Option value
*/
  public void Custom(string optionKey, string value) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdStreamOptions_Custom(swigCPtr, optionKey, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
