
package com.gracenote.gnsdk;

/** 
* {@link GnVideo} 
*/ 
 
public class GnVideo extends GnObject {
  private long swigCPtr;

  protected GnVideo(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnVideo_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnVideo obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnVideo(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

	private IGnStatusEvents pEventHandler;
	private IGnStatusEventsProxyU eventHandlerProxy;
	private GnLocale locale;

    private long getCancellerCPtrFromCancellable(IGnCancellable cancellable) {
    	if ( cancellable instanceof IGnCancellableProxy ){
    		IGnCancellableProxy canceller = (IGnCancellableProxy)cancellable;
    		return IGnCancellableProxy.getCPtr(canceller);
    	}
    	return 0;
    }

/** 
*  Initializes Gracenote's VideoID and Video Explore libraries. 
*  @param user 
*  @param pEventHandler 
*/ 
 
  public GnVideo(GnUser user, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnVideo__SWIG_0(GnUser.getCPtr(user), user, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public GnVideo(GnUser user) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnVideo__SWIG_1(GnUser.getCPtr(user), user);
}

/** 
* Initializes Gracenote's VideoID and Video Explore libraries. 
* @param user 
* @param locale 
* @param pEventHandler 
*/ 
 
  public GnVideo(GnUser user, GnLocale locale, IGnStatusEvents pEventHandler) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnVideo__SWIG_2(GnUser.getCPtr(user), user, GnLocale.getCPtr(locale), locale, (eventHandlerProxy==null)?0:IGnStatusEventsProxyL.getCPtr(eventHandlerProxy), eventHandlerProxy);
}

  public GnVideo(GnUser user, GnLocale locale) throws com.gracenote.gnsdk.GnException {
	this(0, true);
	
	if ( pEventHandler != null )
	{
		eventHandlerProxy = new IGnStatusEventsProxyU(pEventHandler);
	}
	this.pEventHandler=pEventHandler;	// <REFERENCE_NAME_CHECK><TYPE>IGnStatusEvents</TYPE><NAME>pEventHandler</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	this.locale = locale; 				// <REFERENCE_NAME_CHECK><TYPE>GnLocale</TYPE><NAME>locale</NAME></REFERENCE_NAME_CHECK> leave for scripted verification of names
	
	swigCPtr = gnsdk_javaJNI.new_GnVideo__SWIG_3(GnUser.getCPtr(user), user, GnLocale.getCPtr(locale), locale);
}

/** 
*  Retrieves the VideoID and Video Explore library's version string. 
* <p> 
*  This API can be called at any time, even before initialization and after shutdown. The returned 
*  string is a constant. Do not attempt to modify or delete. 
* <p> 
*  Example: <code>1.2.3.123</code> (Major.Minor.Improvement.Build)<br> 
*  Major: New functionality<br> 
*  Minor: New or changed features<br> 
*  Improvement: Improvements and fixes<br> 
*  Build: Internal build number<br> 
*/ 
 
  public static String version() {
    return gnsdk_javaJNI.GnVideo_version();
  }

/** 
*  Retrieves the VideoID and Video Explore library's build date as a string. 
*  This API can be called at any time, even before initialization and after shutdown. The returned 
*  string is a constant. Do not attempt to modify or delete. 
*  @return String with format: YYYY-MM-DD hh:mm UTC 
* <p> 
*  Example:<code>"2008-02-12 00:41 UTC"</code> 
*/ 
 
  public static String buildDate() {
    return gnsdk_javaJNI.GnVideo_buildDate();
  }

/** 
*  Options 
*/ 
 
  public GnVideoOptions options() {
    return new GnVideoOptions(gnsdk_javaJNI.GnVideo_options(swigCPtr, this), false);
  }

/** 
*  Find video products using a TOC (Table of Contents) string. 
*  @param videoTOC [in] TOC string; must be an XML string constructed by the Gracenote Video Thin Client component. 
*  @param TOCFlag [in] TOC string flag; for flags types, see {@link GnVideoTOCFlag} 
*  @return {@link GnResponseVideoProduct} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial 
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray. 
*  Use this API to find a video product by its TOC. 
*/ 
 
  public GnResponseVideoProduct findProducts(String videoTOC, GnVideoTOCFlag TOCFlag) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoProduct(gnsdk_javaJNI.GnVideo_findProducts__SWIG_0(swigCPtr, this, videoTOC, TOCFlag.swigValue()), true);
  }

/** 
*  Find video products using a partial {@link GnVideoProduct} object. 
*  @param videoProduct 
*  @return {@link GnResponseVideoProduct} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A partial {@link GnVideoProduct} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial 
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray. 
*/ 
 
  public GnResponseVideoProduct findProducts(GnVideoProduct videoProduct) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoProduct(gnsdk_javaJNI.GnVideo_findProducts__SWIG_1(swigCPtr, this, GnVideoProduct.getCPtr(videoProduct), videoProduct), true);
  }

/** 
*  Find video products using a partial {@link GnVideoWork} object. 
*  @param videoWork 
*  @return {@link GnResponseVideoProduct} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A partial {@link GnVideoWork} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial 
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray. 
*/ 
 
  public GnResponseVideoProduct findProducts(GnVideoWork videoWork) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoProduct(gnsdk_javaJNI.GnVideo_findProducts__SWIG_2(swigCPtr, this, GnVideoWork.getCPtr(videoWork), videoWork), true);
  }

/** 
*  Find video products using supported {@link GnDataObject} types. 
*  @param gnObj 
*  @return {@link GnResponseVideoProduct} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial 
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray. 
*/ 
 
  public GnResponseVideoProduct findProducts(GnDataObject gnObj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoProduct(gnsdk_javaJNI.GnVideo_findProducts__SWIG_3(swigCPtr, this, GnDataObject.getCPtr(gnObj), gnObj), true);
  }

/** 
*  Find video products using a text search 
*  @param textInput [in] Text string. 
*  @param searchField [in] Can be GnVideoSearchField.kSearchFieldProductTitle or GnVideoSearchField.kSearchFieldAll 
*  @param searchType [in] Video search type; see {@link GnVideoSearchType} 
*  @return {@link GnResponseVideoProduct} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial 
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray. 
*/ 
 
  public GnResponseVideoProduct findProducts(String textInput, GnVideoSearchField searchField, GnVideoSearchType searchType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoProduct(gnsdk_javaJNI.GnVideo_findProducts__SWIG_4(swigCPtr, this, textInput, searchField.swigValue(), searchType.swigValue()), true);
  }

/** 
*  Find video products using an external ID 
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services. 
*  @param externalIdType [in] External ID type; see {@link GnVideoExternalIdType} for available external ID types 
*  @return {@link GnResponseVideoProduct} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial 
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray. 
*/ 
 
  public GnResponseVideoProduct findProducts(String externalId, GnVideoExternalIdType externalIdType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoProduct(gnsdk_javaJNI.GnVideo_findProducts__SWIG_5(swigCPtr, this, externalId, externalIdType.swigValue()), true);
  }

/** 
*  Find video works using a partial {@link GnVideoProduct} object. 
*  @param videoProduct [in] 
*  @return {@link GnResponseVideoWork} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A partial {@link GnVideoProduct} can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(GnVideoProduct videoProduct) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_0(swigCPtr, this, GnVideoProduct.getCPtr(videoProduct), videoProduct), true);
  }

/** 
*  Find video works using a partial {@link GnVideoWork} object. 
*  @param videoWork [in] 
*  @return {@link GnResponseVideoWork} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A partial {@link GnVideoWork} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(GnVideoWork videoWork) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_1(swigCPtr, this, GnVideoWork.getCPtr(videoWork), videoWork), true);
  }

/** 
*  Find video works using a partial {@link GnContributor} object. 
*  @param contributor [in] 
*  @return {@link GnResponseVideoWork} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A partial {@link GnContributor} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(GnContributor contributor) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_2(swigCPtr, this, GnContributor.getCPtr(contributor), contributor), true);
  }

/** 
*  Find video works using a partial {@link GnVideoSeason} object. 
*  @param videoSeason [in] 
*  @return {@link GnResponseVideoWork} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami 
*  (Season Two), CSI: Miami (Season Three). 
*  A partial {@link GnVideoSeason} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(GnVideoSeason videoSeason) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_3(swigCPtr, this, GnVideoSeason.getCPtr(videoSeason), videoSeason), true);
  }

/** 
*  Find video works using a  partial {@link GnVideoSeries} object. 
*  @param videoSeries [in] 
*  @return {@link GnResponseVideoWork} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation. 
*  A partial {@link GnVideoSeries} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(GnVideoSeries videoSeries) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_4(swigCPtr, this, GnVideoSeries.getCPtr(videoSeries), videoSeries), true);
  }

/** 
*  Find video works using supported {@link GnDataObject} types. 
*  @param gnObj [in] 
*  @return {@link GnResponseVideoWork} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(GnDataObject gnObj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_5(swigCPtr, this, GnDataObject.getCPtr(gnObj), gnObj), true);
  }

/** 
*  Find video works using a text search. 
*  @param textInput [in] text string. 
*  @param searchField [in] Can be any {@link GnVideoSearchField} option except GnVideoSearchField.kSearchFieldProductTitle 
*  @param searchType [in] Video search type, see {@link GnVideoSearchType} 
* <p> 
*  @return {@link GnResponseVideoWork} 
*  <p><b>Remarks:</b></p> 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(String textInput, GnVideoSearchField searchField, GnVideoSearchType searchType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_6(swigCPtr, this, textInput, searchField.swigValue(), searchType.swigValue()), true);
  }

/** 
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services. 
*  @param externalIdType [in] External ID type; see {@link GnVideoExternalIdType} for available external ID types 
* <p> 
*  @return {@link GnResponseVideoWork} 
*  <p><b>Remarks:</b></p> 
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a 
*  body of work, or, more specifically, to indicate a particular movie or television show. 
*/ 
 
  public GnResponseVideoWork findWorks(String externalId, GnVideoExternalIdType externalIdType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoWork(gnsdk_javaJNI.GnVideo_findWorks__SWIG_7(swigCPtr, this, externalId, externalIdType.swigValue()), true);
  }

/** 
*  Find video seasons using a partial {@link GnVideoWork} object. 
*  @param videoWork [in] 
*  @return {@link GnResponseVideoSeasons} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami 
*  (Season Two), CSI: Miami (Season Three). 
*  A partial {@link GnVideoWork} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeasons findSeasons(GnVideoWork videoWork) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeasons(gnsdk_javaJNI.GnVideo_findSeasons__SWIG_0(swigCPtr, this, GnVideoWork.getCPtr(videoWork), videoWork), true);
  }

/** 
*  Find video seasons using a partial {@link GnContributor} object. 
*  @param contributor [in] 
*  @return {@link GnResponseVideoSeasons} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami 
*  (Season Two), CSI: Miami (Season Three). 
*  A partial {@link GnContributor} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeasons findSeasons(GnContributor contributor) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeasons(gnsdk_javaJNI.GnVideo_findSeasons__SWIG_1(swigCPtr, this, GnContributor.getCPtr(contributor), contributor), true);
  }

/** 
*  Find video seasons using a partial {@link GnVideoSeason} object. 
*  @param videoSeason [in] 
*  @return {@link GnResponseVideoSeasons} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami 
*  (Season Two), CSI: Miami (Season Three). 
*  A partial {@link GnVideoSeason} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeasons findSeasons(GnVideoSeason videoSeason) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeasons(gnsdk_javaJNI.GnVideo_findSeasons__SWIG_2(swigCPtr, this, GnVideoSeason.getCPtr(videoSeason), videoSeason), true);
  }

/** 
*  Find video seasons using a partial {@link GnVideoSeries} object. 
*  @param videoSeries [in] 
*  @return {@link GnResponseVideoSeasons} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami 
*  (Season Two), CSI: Miami (Season Three). 
*  A partial {@link GnVideoSeries} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeasons findSeasons(GnVideoSeries videoSeries) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeasons(gnsdk_javaJNI.GnVideo_findSeasons__SWIG_3(swigCPtr, this, GnVideoSeries.getCPtr(videoSeries), videoSeries), true);
  }

/** 
*  Find video seasons using supported {@link GnDataObject} types. 
*  @param gnObj [in] 
*  @return {@link GnResponseVideoSeasons} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami 
*  (Season Two), CSI: Miami (Season Three). 
*/ 
 
  public GnResponseVideoSeasons findSeasons(GnDataObject gnObj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeasons(gnsdk_javaJNI.GnVideo_findSeasons__SWIG_4(swigCPtr, this, GnDataObject.getCPtr(gnObj), gnObj), true);
  }

/** 
*  Find video seasons using an external ID. 
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services. 
*  @param externalIdType [in] External ID type; see {@link GnVideoExternalIdType} for available external ID types 
*  @return {@link GnResponseVideoSeasons} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami 
*  (Season Two), CSI: Miami (Season Three). 
*/ 
 
  public GnResponseVideoSeasons findSeasons(String externalId, GnVideoExternalIdType externalIdType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeasons(gnsdk_javaJNI.GnVideo_findSeasons__SWIG_5(swigCPtr, this, externalId, externalIdType.swigValue()), true);
  }

/** 
*  Find video series using a partial {@link GnVideoWork} object. 
*  @param videoWork [in] 
*  @return {@link GnResponseVideoSeries} 
* <p> 
*   <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation. 
*  A partial {@link GnVideoWork} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeries findSeries(GnVideoWork videoWork) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnVideo_findSeries__SWIG_0(swigCPtr, this, GnVideoWork.getCPtr(videoWork), videoWork), true);
  }

/** 
*  Find video series using a contributor Tui and TuiTag or partial {@link GnContributor} object. 
*  @param contributor [in] 
*  @return {@link GnResponseVideoSeries} 
* <p> 
*   <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation. 
*  A partial {@link GnContributor} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeries findSeries(GnContributor contributor) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnVideo_findSeries__SWIG_1(swigCPtr, this, GnContributor.getCPtr(contributor), contributor), true);
  }

/** 
*  Find video series using a video season Tui and TuiTag or partial {@link GnVideoSeason}. 
*  @param videoSeason [in] 
*  @return {@link GnResponseVideoSeries} 
* <p> 
*   <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation. 
*  A partial {@link GnVideoSeason} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeries findSeries(GnVideoSeason videoSeason) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnVideo_findSeries__SWIG_2(swigCPtr, this, GnVideoSeason.getCPtr(videoSeason), videoSeason), true);
  }

/** 
*  Find video series using a partial {@link GnVideoSeries} object. 
*  @param videoSeries [in] 
*  @return {@link GnResponseVideoSeries} 
* <p> 
*   <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation. 
*  A partial {@link GnVideoSeries} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseVideoSeries findSeries(GnVideoSeries videoSeries) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnVideo_findSeries__SWIG_3(swigCPtr, this, GnVideoSeries.getCPtr(videoSeries), videoSeries), true);
  }

/** 
*  Find video series using supported {@link GnDataObject} types. 
*  @param gnObj [in] 
*  @return {@link GnResponseVideoSeries} 
* <p> 
*   <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation. 
*/ 
 
  public GnResponseVideoSeries findSeries(GnDataObject gnObj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnVideo_findSeries__SWIG_4(swigCPtr, this, GnDataObject.getCPtr(gnObj), gnObj), true);
  }

/** 
*  Find video series using a text search. 
*  @param textInput [in]  Video series title 
*  @param searchType [in] Can only be GnVideoSearchType.kSearchFieldSeriesTitle - you cannot search for a Series 
*  using GnVideoSearchType.kSearchFieldAll 
*  @return {@link GnResponseVideoSeries} 
* <p> 
*   <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation. 
*/ 
 
  public GnResponseVideoSeries findSeries(String textInput, GnVideoSearchType searchType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnVideo_findSeries__SWIG_5(swigCPtr, this, textInput, searchType.swigValue()), true);
  }

/** 
*  Find video series using an external ID. 
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services. 
*  @param externalIdType [in] External ID type; see {@link GnVideoExternalIdType} for available external ID types 
*  @return {@link GnResponseVideoSeries} 
* <p> 
*   <p><b>Remarks:</b></p> 
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series), 
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigati 
*/ 
 
  public GnResponseVideoSeries findSeries(String externalId, GnVideoExternalIdType externalIdType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSeries(gnsdk_javaJNI.GnVideo_findSeries__SWIG_6(swigCPtr, this, externalId, externalIdType.swigValue()), true);
  }

/** 
*  Find contributors associated with a partial {@link GnVideoWork} object. 
*  @param videoWork [in] 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person involved in the creation of a work (such as an actor or a director) or 
*  an entity (such as a production company). 
*  A partial {@link GnVideoWork} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseContributors findContributors(GnVideoWork videoWork) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_0(swigCPtr, this, GnVideoWork.getCPtr(videoWork), videoWork), true);
  }

/** 
*  Find contributors using a partial {@link GnContributor} objet. 
*  @param contributor [in] 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company) 
*  A partial {@link GnContributor} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseContributors findContributors(GnContributor contributor) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_1(swigCPtr, this, GnContributor.getCPtr(contributor), contributor), true);
  }

/** 
*  Find contributors associated with a video season using a partial {@link GnVideoSeason}. 
*  @param videoSeason [in] 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company) 
*  A partial {@link GnVideoSeason} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseContributors findContributors(GnVideoSeason videoSeason) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_2(swigCPtr, this, GnVideoSeason.getCPtr(videoSeason), videoSeason), true);
  }

/** 
*  Find contributors associated with a partial {@link GnVideoSeries} object. 
*  @param videoSeries [in] 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company) 
*  A partial {@link GnVideoSeason} object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized. 
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service. 
*/ 
 
  public GnResponseContributors findContributors(GnVideoSeries videoSeries) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_3(swigCPtr, this, GnVideoSeries.getCPtr(videoSeries), videoSeries), true);
  }

/** 
*  Find contributors using supported {@link GnDataObject} types. 
*  @param gnObj [in] 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company) 
*/ 
 
  public GnResponseContributors findContributors(GnDataObject gnObj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_4(swigCPtr, this, GnDataObject.getCPtr(gnObj), gnObj), true);
  }

/** 
*  @deprecated This method has been deprecated. 
*  Find contributors using a text search. 
*  @param textInput [in] 
*  @param searchType [in] 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company) 
*/ 
 
  public GnResponseContributors findContributors(String textInput, GnVideoSearchType searchType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_5(swigCPtr, this, textInput, searchType.swigValue()), true);
  }

/** 
*  Find contributors using a text search. 
*  @param searchText [in] 
*  @param searchField [in] Can be GnVideoSearchField.kSearchFieldContributorName or GnVideoSearchField.kSearchFieldAll 
*  @param searchType [in] Video search type, see {@link GnVideoSearchType} 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company) 
*/ 
 
  public GnResponseContributors findContributors(String searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_6(swigCPtr, this, searchText, searchField.swigValue(), searchType.swigValue()), true);
  }

/** 
*  Find contributors using an external ID. 
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services. 
*  @param externalIdType [in] External ID type; see {@link GnVideoExternalIdType} for available external ID types 
*  @return {@link GnResponseContributors} 
* <p> 
*  <p><b>Remarks:</b></p> 
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company) 
*/ 
 
  public GnResponseContributors findContributors(String externalId, GnVideoExternalIdType externalIdType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseContributors(gnsdk_javaJNI.GnVideo_findContributors__SWIG_7(swigCPtr, this, externalId, externalIdType.swigValue()), true);
  }

/** 
*  Performs a Video Explore query for any type of video object. Use this function to retrieve a specific 
*  Video Explore object referenced by a {@link GnDataObject}. 
*  @param gnObj [in] 
*  @return {@link GnResponseVideoObjects} 
* <p> 
*/ 
 
  public GnResponseVideoObjects findObjects(GnDataObject gnObj) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoObjects(gnsdk_javaJNI.GnVideo_findObjects__SWIG_0(swigCPtr, this, GnDataObject.getCPtr(gnObj), gnObj), true);
  }

/** 
*  Performs a Video Explore query for any type of video object. Use this function to retrieve 
*  all the Video Explore objects (Contributors, Products, Seasons, Series, and Works) associated with a 
*  particular external ID. 
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services. 
*  @param externalIdType [in] External ID type; see {@link GnVideoExternalIdType} for available external ID types 
*  @return {@link GnResponseVideoObjects} 
*/ 
 
  public GnResponseVideoObjects findObjects(String externalId, GnVideoExternalIdType externalIdType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoObjects(gnsdk_javaJNI.GnVideo_findObjects__SWIG_1(swigCPtr, this, externalId, externalIdType.swigValue()), true);
  }

/** 
*  Performs a VideoID or Video Explore query for search suggestion text. Use this function to suggest potential matching titles, 
*  names, and series as a user enters text in a search query. A suggestion search cannot be performed using GnVideoSearchField.kSearchFieldAll. 
*  @param searchText [in] Text string. 
*  @param searchField [in] Can be any {@link GnVideoSearchField} option except GnVideoSearchType.kSearchFieldAll 
*  @param searchType [in] Video search type, see {@link GnVideoSearchType} 
*  @return {@link GnResponseVideoSuggestions} 
*/ 
 
  public GnResponseVideoSuggestions findSuggestions(String searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) throws com.gracenote.gnsdk.GnException {
    return new GnResponseVideoSuggestions(gnsdk_javaJNI.GnVideo_findSuggestions(swigCPtr, this, searchText, searchField.swigValue(), searchType.swigValue()), true);
  }

  public IGnStatusEvents eventHandler() {
	return pEventHandler;
}

  public void setCancel(boolean bCancel) {
    gnsdk_javaJNI.GnVideo_setCancel(swigCPtr, this, bCancel);
  }

  public boolean isCancelled() {
    return gnsdk_javaJNI.GnVideo_isCancelled(swigCPtr, this);
  }

}
