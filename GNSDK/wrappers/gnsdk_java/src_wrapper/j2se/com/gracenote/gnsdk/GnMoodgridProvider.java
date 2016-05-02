
package com.gracenote.gnsdk;

/** 
** <b>Experimental</b>: {@link GnMoodgridProvider} 
*/ 
 
public class GnMoodgridProvider extends GnObject {
  private long swigCPtr;

  protected GnMoodgridProvider(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnMoodgridProvider_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridProvider obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridProvider(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

/** 
* Retrieves the name of the moodgrid provider. 
* @return string representing the name of the provider. 
*/ 
 
  public String name() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMoodgridProvider_name(swigCPtr, this);
  }

/** 
* Retrieves the type of Moodgrid provider.e.g. playlist collection 
* @return string value denoting type of provider 
*/ 
 
  public String type() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMoodgridProvider_type(swigCPtr, this);
  }

/** 
* Retrieves a bool value whether the provider needs access to the network. 
* @return requiresnetwork 
*/ 
 
  public boolean requiresNetwork() throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMoodgridProvider_requiresNetwork(swigCPtr, this);
  }

}
