
package com.gracenote.gnsdk;

/** 
* Logging columns specifies what columns are written for each entry in the GNSDK log 
*/ 
 
public class GnLogColumns {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected GnLogColumns(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLogColumns obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLogColumns(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public GnLogColumns() {
    this(gnsdk_javaJNI.new_GnLogColumns(), true);
  }

/** 
* Clear options currently set 
*/ 
 
  public void none() {
    gnsdk_javaJNI.GnLogColumns_none(swigCPtr, this);
  }

/** 
* Specify to include a time stamp for each entry of the format: Wed Jan 30 18:56:37 2008 
*/ 
 
  public GnLogColumns timeStamp() {
    return new GnLogColumns(gnsdk_javaJNI.GnLogColumns_timeStamp(swigCPtr, this), false);
  }

/** 
* Specify to categorizes the log entries by headings such as ERROR, INFO, and so on. 
*/ 
 
  public GnLogColumns category() {
    return new GnLogColumns(gnsdk_javaJNI.GnLogColumns_category(swigCPtr, this), false);
  }

/** 
* Specify to include the Package Name, or the Package ID if the name is unavailable. 
*/ 
 
  public GnLogColumns packageName() {
    return new GnLogColumns(gnsdk_javaJNI.GnLogColumns_packageName(swigCPtr, this), false);
  }

/** 
* Specify to include the Thread ID. 
*/ 
 
  public GnLogColumns thread() {
    return new GnLogColumns(gnsdk_javaJNI.GnLogColumns_thread(swigCPtr, this), false);
  }

/** 
* Specify to include the source information 
*/ 
 
  public GnLogColumns sourceInfo() {
    return new GnLogColumns(gnsdk_javaJNI.GnLogColumns_sourceInfo(swigCPtr, this), false);
  }

/** 
* Specify to include a trailing newline in the format: "\r\n" 
*/ 
 
  public GnLogColumns newLine() {
    return new GnLogColumns(gnsdk_javaJNI.GnLogColumns_newLine(swigCPtr, this), false);
  }

/** 
* Specify to include all log formatting options. 
*/ 
 
  public GnLogColumns all() {
    return new GnLogColumns(gnsdk_javaJNI.GnLogColumns_all(swigCPtr, this), false);
  }

}
