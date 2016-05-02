
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Configures options for GnMusicIdFile
*/
public class GnMusicIdFileOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnMusicIdFileOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMusicIdFileOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMusicIdFileOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMusicIdFileOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
*  Indicates whether the MusicID-File query should be performed against local embedded databases or online.
*  @param lookupMode		[in] One of the GnLookupMode values
*/
  public void LookupMode(GnLookupMode lookupMode) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_LookupMode(swigCPtr, (int)lookupMode);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Sets the lookup data value for the MusicID-File query.
*  @param val 				[in] Set One of the GnLookupData values
*  @param enable 			[in] True or false to enable or disable
*/
  public void LookupData(GnLookupData val, bool enable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_LookupData(swigCPtr, (int)val, enable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Sets the batch size for the MusicID-File query.
*  @param size				[in] set String value or one of MusicID-File Option Values that corresponds to BATCH_SIZE
*  <p><b>Remarks:</b></p>
*  The option value provided for batch size must be greater than zero (0).
*/
  public void BatchSize(uint size) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_BatchSize(swigCPtr, size);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Indicates whether MusicID-File should Process the responses Online, this may reduce the amount of 
*  resources used by the client. Online processing must be allowed by your license.
*  @param enable			[in] True or false to enable or disable
*/
  public void OnlineProcessing(bool enable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_OnlineProcessing(swigCPtr, enable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Sets the preferred language for the MusicID-File query.
*  @param preferredLangauge	[in] One of the GNSDK language values
*/
  public void PreferResultLanguage(GnLanguage preferredLangauge) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_PreferResultLanguage(swigCPtr, (int)preferredLangauge);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Use this option to specify an external identifier which MusicID-File should try to include in any responses that are returned.
*  <p><b>Remarks:</b></p>
* This option is currently only supported when online processing is enabled.
*  @param preferredExternalId	[in] The name of an external identifier that should be preferred when selecting matches
*/
  public void PreferResultExternalId(string preferredExternalId) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_PreferResultExternalId(swigCPtr, preferredExternalId);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Sets the thread priority for a given MusicID-File query.
*  @param threadPriority 	[in] Set one of GnThreadPriority values that corresponds to thread priority
*  <p><b>Remarks:</b></p>
*  The option value provided for thread priority must be one of the defined
*  #GnThreadPriority values.
*/
  public void ThreadPriority(GnThreadPriority threadPriority) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_ThreadPriority(swigCPtr, (int)threadPriority);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* This option allows setting of a specific network interface to be used with connections made by  
* this object. Choosing which interface to use can be beneficial for systems with multiple 
* network interfaces. Without setting this option, connections will be made of the default network interface
* as decided by the operating system.
*  @param ipAddress		[in] local IP address for the desired network interface
*/
  public void NetworkInterface(string ipAddress) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_NetworkInterface(swigCPtr, ipAddress);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  General option setting for custom options
*  @param optionKey		[in] set One of the MusicID-File Option Keys
*  @param enable			[in] set True or false to enable or disable
*/
  public void Custom(string optionKey, bool enable) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_Custom__SWIG_0(swigCPtr, optionKey, enable);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Set option using option name
*  @param option			[in] Option name
*  @param value			[in] Option value
*/
  public void Custom(string option, string value) {
    gnsdk_csharp_marshalPINVOKE.GnMusicIdFileOptions_Custom__SWIG_1(swigCPtr, option, value);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
