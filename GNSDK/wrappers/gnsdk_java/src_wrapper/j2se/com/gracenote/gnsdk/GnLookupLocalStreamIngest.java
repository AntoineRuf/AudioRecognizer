
package com.gracenote.gnsdk;

public class GnLookupLocalStreamIngest extends GnObject {
  private long swigCPtr;

  protected GnLookupLocalStreamIngest(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnLookupLocalStreamIngest_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLookupLocalStreamIngest obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLookupLocalStreamIngest(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  private IGnLookupLocalStreamIngestEvents 			pEventDelegate;
  private IGnLookupLocalStreamIngestEventsProxyU 	eventHandlerProxy;

/** 
*  Constructor for creating a {@link GnLookupLocalStreamIngest} Object 
*  @param pEventDelegate           [in] Delegate to receive events . 
*  @param callbackData             [in] Optional user data that will be sent to the Delegate 
*/ 
 
  public GnLookupLocalStreamIngest(IGnLookupLocalStreamIngestEvents pEventDelegate) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnLookupLocalStreamIngestEventsProxyU(pEventDelegate);
	this.pEventDelegate = pEventDelegate; // <REFERENCE_NAME_CHECK><TYPE>IGnLookupLocalStreamIngestEvents</TYPE><NAME>pEventDelegate</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLookupLocalStreamIngest((eventHandlerProxy==null)?0:IGnLookupLocalStreamIngestEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public void write(byte[] bundleData, long dataSize) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnLookupLocalStreamIngest_write(swigCPtr, this, bundleData, dataSize);
  }

/** 
* Flushes the memory cache to the file storage and commits the changes. This call will result in IO . 
* Use this method to ensure that everything written is commited to the file system. 
* Note: This is an optional call as internally data is flushed when it exceed the cache size and when the object goes out of scope.. 
*/ 
 
  public void flush() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnLookupLocalStreamIngest_flush(swigCPtr, this);
  }

  public IGnLookupLocalStreamIngestEvents eventHandler() {
	return pEventDelegate;
}

}
