
package com.gracenote.gnsdk;

/** 
* Configures and enables GNSDK logging including registering custom logging packages 
* and writing your own logging message to the GNSDK log 
*/ 
 
public class GnLog {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnLog(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLog obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLog(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

	private IGnLogEvents pLoggingDelegate;
	private IGnLogEventsProxyU logProxyDelegate;

/** 
* Instantiate a GNSDK logging instance 
* @param logFilePath		[in] File path of the logging file 
* @param pLoggingDelegate	[in] Optional delegate to receive logging messages 
*/ 
 
  public GnLog(String logFilePath, IGnLogEvents pLoggingDelegate) {
	this(0, true);
	
	if ( pLoggingDelegate != null )
	{
		logProxyDelegate = new IGnLogEventsProxyU(pLoggingDelegate);
	}
	this.pLoggingDelegate=pLoggingDelegate;		// <REFERENCE_NAME_CHECK><TYPE>IGnLogEvents</TYPE><NAME>pLoggingDelegate</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLog__SWIG_0(logFilePath, (logProxyDelegate==null)?0:IGnLogEventsProxyL.getCPtr(logProxyDelegate), logProxyDelegate);	
}

  public GnLog(String logFilePath) {
	this(0, true);
	
	if ( pLoggingDelegate != null )
	{
		logProxyDelegate = new IGnLogEventsProxyU(pLoggingDelegate);
	}
	this.pLoggingDelegate=pLoggingDelegate;		// <REFERENCE_NAME_CHECK><TYPE>IGnLogEvents</TYPE><NAME>pLoggingDelegate</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLog__SWIG_1(logFilePath);	
}

/** 
* Instantiate a GNSDK logging instance 
* <p><b>Remarks:</b></p> 
* {@link GnLog} instances setup individual logs. Any number of logs can be 
* started with any configurations. Messages that filter to multiple logs will 
* be written to all applicable logs.  
* Logging instances are distinguished by the logFilePath. Creating {@link GnLog} instances 
* with the same logFilePath as one already started will modify the configuration for  
* the existing log. 
* Logging is not started until GnLog::Enable() is called. 
* Logging continues until GnLog::Disable() is called. Destruction of {@link GnLog} instance 
* does not terminate logging setup by that instance. 
* @param logFilePath		[in] Path and name of the logging file 
* @param filters			[in] Logging filters 
* @param columns			[in] Logging columns 
* @param options			[in] Logging options 
* @param pLoggingDelegate	[in] Optional Delegate to receive logging messages 
*/ 
 
  public GnLog(String logFilePath, GnLogFilters filters, GnLogColumns columns, GnLogOptions options, IGnLogEvents pLoggingDelegate) {
	this(0, true);
	
	if ( pLoggingDelegate != null )
	{
		logProxyDelegate = new IGnLogEventsProxyU(pLoggingDelegate);
	}
	this.pLoggingDelegate=pLoggingDelegate;		// <REFERENCE_NAME_CHECK><TYPE>IGnLogEvents</TYPE><NAME>pLoggingDelegate</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLog__SWIG_2(logFilePath, GnLogFilters.getCPtr(filters), filters, GnLogColumns.getCPtr(columns), columns, GnLogOptions.getCPtr(options), options, (logProxyDelegate==null)?0:IGnLogEventsProxyL.getCPtr(logProxyDelegate), logProxyDelegate);	
}

  public GnLog(String logFilePath, GnLogFilters filters, GnLogColumns columns, GnLogOptions options) {
	this(0, true);
	
	if ( pLoggingDelegate != null )
	{
		logProxyDelegate = new IGnLogEventsProxyU(pLoggingDelegate);
	}
	this.pLoggingDelegate=pLoggingDelegate;		// <REFERENCE_NAME_CHECK><TYPE>IGnLogEvents</TYPE><NAME>pLoggingDelegate</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLog__SWIG_3(logFilePath, GnLogFilters.getCPtr(filters), filters, GnLogColumns.getCPtr(columns), columns, GnLogOptions.getCPtr(options), options);	
}

/** 
* Set logger instance options 
* @param options  Selection of logging options via {@link GnLogOptions} 
*/ 
 
  public void options(GnLogOptions options) {
    gnsdk_javaJNI.GnLog_options(swigCPtr, this, GnLogOptions.getCPtr(options), options);
  }

/** 
* Set logger instance filters 
* @param filters  Selection of log message filters via {@link GnLogFilters} 
*/ 
 
  public void filters(GnLogFilters filters) {
    gnsdk_javaJNI.GnLog_filters(swigCPtr, this, GnLogFilters.getCPtr(filters), filters);
  }

/** 
* Set logger instance columns 
* @param columns  Selection of log column format via {@link GnLogColumns} 
*/ 
 
  public void columns(GnLogColumns columns) {
    gnsdk_javaJNI.GnLog_columns(swigCPtr, this, GnLogColumns.getCPtr(columns), columns);
  }

/** 
* Enable logging for the given package with the current logging options and filters. 
* Enable can be called multiple times to enable logging of multiple packages to the same log. 
* <p><b>Remarks:</b></p> 
* Changes to logging options and filters do not take affect until the logger is next enabled. 
* @param package [in] {@link GnLogPackage} to enable for this log. 
* @return This {@link GnLog} object to allow method chaining. 
*/ 
 
  public GnLog enable(GnLogPackageType arg0) throws com.gracenote.gnsdk.GnException {
    return new GnLog(gnsdk_javaJNI.GnLog_enable__SWIG_0(swigCPtr, this, arg0.swigValue()), false);
  }

  public GnLog enable(int customPackageId) throws com.gracenote.gnsdk.GnException {
    return new GnLog(gnsdk_javaJNI.GnLog_enable__SWIG_1(swigCPtr, this, customPackageId), false);
  }

/** 
* Disable logging for the given package for the current log. 
* If no other packages are enabled for the log, the log will be closed 
* @param package [in] {@link GnLogPackage} to disable for this log. 
* @return This {@link GnLog} object to allow method chaining. 
*/ 
 
  public GnLog disable(GnLogPackageType arg0) throws com.gracenote.gnsdk.GnException {
    return new GnLog(gnsdk_javaJNI.GnLog_disable__SWIG_0(swigCPtr, this, arg0.swigValue()), false);
  }

  public GnLog disable(int customPackageId) throws com.gracenote.gnsdk.GnException {
    return new GnLog(gnsdk_javaJNI.GnLog_disable__SWIG_1(swigCPtr, this, customPackageId), false);
  }

  public GnLog register(int customPackageId, String customPackageName) throws com.gracenote.gnsdk.GnException {
    return new GnLog(gnsdk_javaJNI.GnLog_register(swigCPtr, this, customPackageId, customPackageName), false);
  }

  public static void write(int line, String fileName, int customPackageId, GnLogMessageType messageType, String format) {
    gnsdk_javaJNI.GnLog_write(line, fileName, customPackageId, messageType.swigValue(), format);
  }

  public final static int kMinimumCustomPackageIdValue = (((0x80) +0x5f) +0x01);
  public final static int kMaximumCustomPackageIdValue = (((0x80) +0x7D));
}
