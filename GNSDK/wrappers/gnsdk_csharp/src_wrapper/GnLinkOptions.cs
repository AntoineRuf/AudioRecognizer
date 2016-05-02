
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

public class GnLinkOptions : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal GnLinkOptions(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnLinkOptions obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnLinkOptions() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnLinkOptions(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/** Set this link query lookup mode.
* @param lookupMode		Lookup mode
*/
  public void LookupMode(GnLookupMode lookupMode) {
    gnsdk_csharp_marshalPINVOKE.GnLinkOptions_LookupMode(swigCPtr, (int)lookupMode);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Explicitly identifies the track of interest by its ordinal number. This option takes precedence
*   over any provided by track indicator.
* @ingroup Link_OptionKeys
*/
  public void TrackOrdinal(uint number) {
    gnsdk_csharp_marshalPINVOKE.GnLinkOptions_TrackOrdinal(swigCPtr, number);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  This option sets the source provider of the content (for example, "Acme").
* @ingroup Link_OptionKeys
*/
  public void DataSource(string datasource) {
    gnsdk_csharp_marshalPINVOKE.GnLinkOptions_DataSource(swigCPtr, datasource);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  This option sets the type of the provider content (for example, "cover").
* @ingroup Link_OptionKeys
*/
  public void DataType(string datatype) {
    gnsdk_csharp_marshalPINVOKE.GnLinkOptions_DataType(swigCPtr, datatype);
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
    gnsdk_csharp_marshalPINVOKE.GnLinkOptions_NetworkInterface(swigCPtr, ipAddress);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Clears all options currently set for a given Link query.
*  <p><b>Remarks:</b></p>
*  As Link query handles can be used to retrieve multiple enhanced data items, it may be appropriate
*   to specify different options between data retrievals. You can use this function to clear all options
*   before setting new ones.
* @ingroup Link_QueryFunctions
*/
  public void Clear() {
    gnsdk_csharp_marshalPINVOKE.GnLinkOptions_Clear(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
