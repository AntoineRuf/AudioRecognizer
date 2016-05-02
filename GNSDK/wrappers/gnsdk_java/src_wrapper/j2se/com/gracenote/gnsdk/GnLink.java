
package com.gracenote.gnsdk;

/** 
* {@link GnLink} 
*/ 
 
public class GnLink extends GnObject {
  private long swigCPtr;

  protected GnLink(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnLink_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnLink obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnLink(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

	private IGnStatusEvents pEventHandler;
	private IGnStatusEventsProxyU eventHandlerProxy;

  public GnLink(GnDataObject gnDataObject, GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLink__SWIG_0(GnDataObject.getCPtr(gnDataObject), gnDataObject, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public GnLink(GnDataObject gnDataObject, GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLink__SWIG_1(GnDataObject.getCPtr(gnDataObject), gnDataObject, GnUser.getCPtr(user), user);
}

  public GnLink(GnListElement listElement, GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLink__SWIG_2(GnListElement.getCPtr(listElement), listElement, GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public GnLink(GnListElement listElement, GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnLink__SWIG_3(GnListElement.getCPtr(listElement), listElement, GnUser.getCPtr(user), user);
}

/** 
* Retrieves the Link library version string. 
* This API can be called at any time, after getting {@link GnManager} instance successfully. The returned 
* string is a constant. Do not attempt to modify or delete. 
* <p> 
* Example: <code>1.2.3.123</code> (Major.Minor.Improvement.Build)<br> 
* Major: New functionality<br> 
* Minor: New or changed features<br> 
* Improvement: Improvements and fixes<br> 
* Build: Internal build number<br> 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnLink_version();
  }

/** 
*  Retrieves Link library build date string. 
*  @return Note Build date string of the format: YYYY-MM-DD hh:mm UTC 
*  <p><b>Remarks:</b></p> 
*  This API can be called at any time, after getting {@link GnManager} instance successfully. The returned 
*  string is a constant. Do not attempt to modify or delete. 
*  Example build date string: 2008-02-12 00:41 UTC 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnLink_buildDate();
  }

/** 
* Retrieves count for the specified content 
* @param contentType Type of content to count 
* @return Count 
* <p><b>Remarks:</b></p> 
* <code>Count()</code> can be called repeatedly on the same {@link GnLink} object with 
* different content type requests to 
* retrieve the count for differing values of content type. 
*/ 
 
  public long count(GnLinkContentType contentType) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnLink_count(swigCPtr, this, contentType.swigValue());
  }

  public GnLinkOptions options() {
    return new GnLinkOptions(gnsdk_javaJNI.GnLink_options(swigCPtr, this), false);
  }

/** 
* Retrieves CoverArt data. 
* @param imageSize size of the image to retrieve 
* @param imagePreference image retrieval preference 
* @param item_ord Nth CoverArt 
* @return {@link GnLinkContent} 
*  <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different size and ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent coverArt(GnImageSize imageSize, GnImagePreference imagePreference, long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_coverArt__SWIG_0(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue(), item_ord), true);
  }

  public GnLinkContent coverArt(GnImageSize imageSize, GnImagePreference imagePreference) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_coverArt__SWIG_1(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue()), true);
  }

/** 
* Retrieves GenreArt data. 
* @param imageSize size of the image to retrieve 
* @param imagePreference image retrieval preference 
* @param item_ord Nth GenreArt 
* @return {@link GnLinkContent} 
*  <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different size and ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent genreArt(GnImageSize imageSize, GnImagePreference imagePreference, long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_genreArt__SWIG_0(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue(), item_ord), true);
  }

  public GnLinkContent genreArt(GnImageSize imageSize, GnImagePreference imagePreference) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_genreArt__SWIG_1(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue()), true);
  }

/** 
* Retrieves Image data. 
* @param imageSize size of the image to retrieve 
* @param imagePreference image retrieval preference 
* @param item_ord  Nth Image 
* @return {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different size and ordinal parameters 
* 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent image(GnImageSize imageSize, GnImagePreference imagePreference, long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_image__SWIG_0(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue(), item_ord), true);
  }

  public GnLinkContent image(GnImageSize imageSize, GnImagePreference imagePreference) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_image__SWIG_1(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue()), true);
  }

/** 
* Retrieves ArtistImage data. 
* @param  imageSize size of the image to retrieve 
* @param imagePreference image retrieval preference 
* @param item_ord Nth ArtistImage 
* @return  {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different size and ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent artistImage(GnImageSize imageSize, GnImagePreference imagePreference, long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_artistImage__SWIG_0(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue(), item_ord), true);
  }

  public GnLinkContent artistImage(GnImageSize imageSize, GnImagePreference imagePreference) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_artistImage__SWIG_1(swigCPtr, this, imageSize.swigValue(), imagePreference.swigValue()), true);
  }

/** 
* Retrieves Review data. 
* @param item_ord Nth Review 
* @return  {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent review(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_review__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent review() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_review__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves Biography data. 
* @param item_ord [in] Nth Biography 
* @return {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent biography(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_biography__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent biography() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_biography__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves AristNews data. 
* @param item_ord Nth AristNews 
* @return {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent artistNews(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_artistNews__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent artistNews() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_artistNews__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves LyricXML data. 
* @param item_ord Nth LyricXML 
* @return  {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent lyricXML(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_lyricXML__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent lyricXML() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_lyricXML__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves LyricText data. 
* @param item_ord Nth LyricText 
* @return  {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent lyricText(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_lyricText__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent lyricText() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_lyricText__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves CommentsListener data. 
* @param item_ord [in] Nth CommentsListener 
* @return {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent commentsListener(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_commentsListener__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent commentsListener() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_commentsListener__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves CommentsRelease data. 
* @param item_ord [in] Nth CommentsRelease 
* @return {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent commentsRelease(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_commentsRelease__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent commentsRelease() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_commentsRelease__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves News data. 
* @param item_ord Nth News 
* @return {@link GnLinkContent} 
* <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent news(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_news__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent news() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_news__SWIG_1(swigCPtr, this), true);
  }

/** 
* Retrieves DspData data. 
* @param item_ord Nth DspData 
* @return {@link GnLinkContent} 
*  <p><b>Remarks:</b></p> 
* This API can be called repeatedly on the same link query handle with 
* different ordinal parameters 
* Long Running Potential: Network I/O, File system I/O (for online query cache or local lookup) 
*/ 
 
  public GnLinkContent dspData(long item_ord) throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_dspData__SWIG_0(swigCPtr, this, item_ord), true);
  }

  public GnLinkContent dspData() throws com.gracenote.gnsdk.GnException {
    return new GnLinkContent(gnsdk_javaJNI.GnLink_dspData__SWIG_1(swigCPtr, this), true);
  }

  public IGnStatusEvents eventHandler() {
	return pEventHandler;
}

  public void setCancel(boolean bCancel) {
    gnsdk_javaJNI.GnLink_setCancel(swigCPtr, this, bCancel);
  }

  public boolean isCancelled() {
    return gnsdk_javaJNI.GnLink_isCancelled(swigCPtr, this);
  }

}
