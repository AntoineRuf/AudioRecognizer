
package com.gracenote.gnsdk;

/** 
* Provides access to content assets that can be retrieved from Urls. 
* Content is only available is content is enabled from the original query's lookup data. 
* Use the query object's options to enable content. 
* The type of content that is available depends on the parent object. For example 
* you can access album cover art from a {@link GnAlbum} object, but not an artist image. To 
* retrieve an artist image navigate to a {@link GnContributor} object and invoke it's {@link GnContent} 
* instance. 
*/ 
 
public class GnContent extends GnDataObject {
  private long swigCPtr;

  protected GnContent(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnContent_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnContent obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnContent(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public String Id() {
    return gnsdk_javaJNI.GnContent_Id(swigCPtr, this);
  }

/** 
*  Content type - cover art, biography, etc. 
*  @return Content type 
*/ 
 
  public GnContentType contentType() {
    return GnContentType.swigToEnum(gnsdk_javaJNI.GnContent_contentType(swigCPtr, this));
  }

/** 
*  Content's mime type 
*  @return Mime type 
*/ 
 
  public String mimeType() {
    return gnsdk_javaJNI.GnContent_mimeType(swigCPtr, this);
  }

/** 
* Asset by image size (if applicable) 
* @param imageSize	[in] Image size 
* @return Asset object 
*/ 
 
  public GnAsset asset(GnImageSize imageSize) {
    return new GnAsset(gnsdk_javaJNI.GnContent_asset(swigCPtr, this, imageSize.swigValue()), true);
  }

  public GnAssetIterable assets() {
    return new GnAssetIterable(gnsdk_javaJNI.GnContent_assets(swigCPtr, this), true);
  }

}
