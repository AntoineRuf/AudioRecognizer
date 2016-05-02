
package com.gracenote.gnsdk;

/** 
* Managed immutable string as returned by GNSDK. 
*/ 
 
public class GnString extends GnObject {
  private long swigCPtr;

  protected GnString(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnString_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnString obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnString(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

		public String
		toString( )
		{
			String str = cStr( );
			return str;
		}
	
/** 
* Construct an empty {@link GnString} object 
*/ 
 
  public GnString() {
    this(gnsdk_javaJNI.new_GnString__SWIG_0(), true);
  }

/** 
* Construct a {@link GnString} object from a native constant string 
* @param str [in] Native string 
*/ 
 
  public GnString(String str) {
    this(gnsdk_javaJNI.new_GnString__SWIG_1(str), true);
  }

/** 
* Construct a {@link GnString} object from an existing {@link GnString} object 
* @param str [in] {@link GnString} object 
*/ 
 
  public GnString(GnString str) {
    this(gnsdk_javaJNI.new_GnString__SWIG_2(GnString.getCPtr(str), str), true);
  }

  public GnString set(GnString str) {
    return new GnString(gnsdk_javaJNI.GnString_set__SWIG_0(swigCPtr, this, GnString.getCPtr(str), str), false);
  }

  public GnString set(String str) {
    return new GnString(gnsdk_javaJNI.GnString_set__SWIG_1(swigCPtr, this, str), false);
  }

  public String cStr() {
    return gnsdk_javaJNI.GnString_cStr(swigCPtr, this);
  }

/** 
* Get flag indicating if string object contains no string 
* @return True of empty, false otherwise 
*/ 
 
  public boolean isEmpty() {
    return gnsdk_javaJNI.GnString_isEmpty(swigCPtr, this);
  }

/** 
* Internally used factory for special SDK-managed strings 
* @param str	[in] Native string 
* @return Managed string 
*/ 
 
  public static GnString manage(String str) {
    return new GnString(gnsdk_javaJNI.GnString_manage(str), true);
  }

}
