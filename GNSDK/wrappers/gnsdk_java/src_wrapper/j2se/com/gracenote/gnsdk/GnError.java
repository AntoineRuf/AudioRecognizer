
package com.gracenote.gnsdk;

/** 
* GNSDK error condition 
* <p> 
* Provides information about an error condition triggered within GNSDK including 
* error code, API and module. 
* <p> 
* Helper methods are also provided to check if the error condition is a warning or an 
* error, a result of a cancellation request or is equivalent to another error code. 
* <p> 
* {@link GnError} also provides access to GNSDK package identifiers and error codes. There is 
* also a static helper method that compares two error codes allowing your application 
* to correlate returned error codes with known error codes if required. 
* <p> 
* For example if you application wishes to perform specific behavior when an out of 
* memory condition occurs you can, 
* <p> 
* <code><pre> 
* // where error is a {@link GnError} instance received from GNSDK 
* if ( error.isError(GnError.GNSDKERR_NoMemory) ) { 
* 	// perform out of memory processes 
* } 
* </pre></code> 
* <p> 
* Similarly you can compare error codes received from GNSDK via a {@link GnException} as, 
* <p> 
* <code><pre> 
* try { 
* 	// some operation 
* } catch (GnException e) { 
* 	// where error is a {@link GnError} instance received from GNSDK 
* 	if ( GnError.isErrorEqual(e.errorCode(), GnError.GNSDKERR_NoMemory) ) { 
* 		// perform out of memory processes 
* 	} 
* } 
* </pre></code> 
* <p> 
*/ 
 
public class GnError implements  gnsdk_javaConstants  {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnError(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnError obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnError(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

/** 
* Construct {@link GnError} with the last error condition experienced in the underlying SDK 
*/ 
 
  public GnError() {
    this(gnsdk_javaJNI.new_GnError__SWIG_0(), true);
  }

/** 
* Construct {@link GnError} with specific error code and description 
* @param errorCode			[in] Error code 
* @param errorDescription 	[in] Error description 
*/ 
 
  public GnError(long errorCode, String errorDescription) {
    this(gnsdk_javaJNI.new_GnError__SWIG_1(errorCode, errorDescription), true);
  }

/** 
* Construct {@link GnError} from {@link GnError} 
* @param gnError		[in] {@link GnError} class object 
*/ 
 
  public GnError(GnError gnError) {
    this(gnsdk_javaJNI.new_GnError__SWIG_2(GnError.getCPtr(gnError), gnError), true);
  }

/** 
* Error code. 
* @return Code 
*/ 
 
  public long errorCode() {
    return gnsdk_javaJNI.GnError_errorCode(swigCPtr, this);
  }

/** 
* Error description. 
* @return Description 
*/ 
 
  public String errorDescription() {
    return gnsdk_javaJNI.GnError_errorDescription(swigCPtr, this);
  }

/** 
* API where error occurred 
* @return API name 
*/ 
 
  public String errorAPI() {
    return gnsdk_javaJNI.GnError_errorAPI(swigCPtr, this);
  }

/** 
* Module where error occurred 
* @return Module 
*/ 
 
  public String errorModule() {
    return gnsdk_javaJNI.GnError_errorModule(swigCPtr, this);
  }

/** 
* Source error code 
* @return Error code 
*/ 
 
  public long sourceErrorCode() {
    return gnsdk_javaJNI.GnError_sourceErrorCode(swigCPtr, this);
  }

/** 
* Source module where error occurred 
* @return Module 
*/ 
 
  public String sourceErrorModule() {
    return gnsdk_javaJNI.GnError_sourceErrorModule(swigCPtr, this);
  }

/** 
* Get the identifier for the Gracenote package where the error originated 
* @return Package identifier 
*/ 
 
  public long packageId() {
    return gnsdk_javaJNI.GnError_packageId(swigCPtr, this);
  }

/** 
* Determine if the error code severity is a warning 
* @return True if the error has severity of warning 
*/ 
 
  public boolean isWarning() {
    return gnsdk_javaJNI.GnError_isWarning(swigCPtr, this);
  }

  public boolean isError() {
    return gnsdk_javaJNI.GnError_isError(swigCPtr, this);
  }

/** 
* Determine if the error code represents a cancelled operation 
* @return True if the error represents a cancellation 
*/ 
 
  public boolean isCancelled() {
    return gnsdk_javaJNI.GnError_isCancelled(swigCPtr, this);
  }

  public boolean isErrorCode(long error) {
    return gnsdk_javaJNI.GnError_isErrorCode(swigCPtr, this, error);
  }

/** 
* Determine if two error codes are equal. Error code contain information beyond 
* error condition, they also contain severity and package identifier. This method 
* strips that information away and compares just the error condition. This is useful 
* if your application needs to compare a returned error code with a known error code. 
* Known error codes can be accessed via {@link GnError} object. 
* @return True if the error conditions represented by the two error codes is equivalent 
*/ 
 
  public static boolean isErrorEqual(long error1, long error2) {
    return gnsdk_javaJNI.GnError_isErrorEqual(error1, error2);
  }

}
