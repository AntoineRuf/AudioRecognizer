
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* GnVideo
*/
public class GnVideo : GnObject {
  private HandleRef swigCPtr;

  internal GnVideo(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnVideo_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnVideo obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnVideo() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnVideo(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Initializes Gracenote's VideoID and Video Explore libraries.
*  @param user
*  @param pEventHandler
*/
  public GnVideo(GnUser user, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideo__SWIG_0(GnUser.getCPtr(user), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnVideo(GnUser user) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideo__SWIG_1(GnUser.getCPtr(user)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Initializes Gracenote's VideoID and Video Explore libraries.
* @param user
* @param locale
* @param pEventHandler
*/
  public GnVideo(GnUser user, GnLocale locale, GnStatusEventsDelegate pEventHandler) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideo__SWIG_2(GnUser.getCPtr(user), GnLocale.getCPtr(locale), GnStatusEventsDelegate.getCPtr(pEventHandler)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

  public GnVideo(GnUser user, GnLocale locale) : this(gnsdk_csharp_marshalPINVOKE.new_GnVideo__SWIG_3(GnUser.getCPtr(user), GnLocale.getCPtr(locale)), true) {
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
*  Options
*/
  public GnVideoOptions Options() {
    GnVideoOptions ret = new GnVideoOptions(gnsdk_csharp_marshalPINVOKE.GnVideo_Options(swigCPtr), false);
    return ret;
  }

/**
*  Find video products using a TOC (Table of Contents) string.
*  @param videoTOC [in] TOC string; must be an XML string constructed by the Gracenote Video Thin Client component.
*  @param TOCFlag [in] TOC string flag; for flags types, see #GnVideoTOCFlag
*  @return GnResponseVideoProduct
*
*  <p><b>Remarks:</b></p>
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
*  Use this API to find a video product by its TOC.
*/
  public GnResponseVideoProduct FindProducts(string videoTOC, GnVideoTOCFlag TOCFlag) {
    GnResponseVideoProduct ret = new GnResponseVideoProduct(gnsdk_csharp_marshalPINVOKE.GnVideo_FindProducts__SWIG_0(swigCPtr, videoTOC, (int)TOCFlag), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video products using a partial GnVideoProduct object.
*  @param videoProduct
*  @return GnResponseVideoProduct
*
*  <p><b>Remarks:</b></p>
*  A partial GnVideoProduct object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
*/
  public GnResponseVideoProduct FindProducts(GnVideoProduct videoProduct) {
    GnResponseVideoProduct ret = new GnResponseVideoProduct(gnsdk_csharp_marshalPINVOKE.GnVideo_FindProducts__SWIG_1(swigCPtr, GnVideoProduct.getCPtr(videoProduct)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video products using a partial GnVideoWork object.
*  @param videoWork
*  @return GnResponseVideoProduct
*
*  <p><b>Remarks:</b></p>
*  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
*/
  public GnResponseVideoProduct FindProducts(GnVideoWork videoWork) {
    GnResponseVideoProduct ret = new GnResponseVideoProduct(gnsdk_csharp_marshalPINVOKE.GnVideo_FindProducts__SWIG_2(swigCPtr, GnVideoWork.getCPtr(videoWork)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video products using supported GnDataObject types.
*  @param gnObj
*  @return GnResponseVideoProduct
*
*  <p><b>Remarks:</b></p>
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
*/
  public GnResponseVideoProduct FindProducts(GnDataObject gnObj) {
    GnResponseVideoProduct ret = new GnResponseVideoProduct(gnsdk_csharp_marshalPINVOKE.GnVideo_FindProducts__SWIG_3(swigCPtr, GnDataObject.getCPtr(gnObj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video products using a text search
*  @param textInput [in] Text string.
*  @param searchField [in] Can be #GnVideoSearchField.kSearchFieldProductTitle or #GnVideoSearchField.kSearchFieldAll
*  @param searchType [in] Video search type; see #GnVideoSearchType
*  @return GnResponseVideoProduct
*
*  <p><b>Remarks:</b></p>
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
*/
  public GnResponseVideoProduct FindProducts(string textInput, GnVideoSearchField searchField, GnVideoSearchType searchType) {
    GnResponseVideoProduct ret = new GnResponseVideoProduct(gnsdk_csharp_marshalPINVOKE.GnVideo_FindProducts__SWIG_4(swigCPtr, textInput, (int)searchField, (int)searchType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video products using an external ID
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
*  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
*  @return GnResponseVideoProduct
*
*  <p><b>Remarks:</b></p>
*  A Product refers to the commercial release of a Film, TV Series, or video content. Products contain a unique commercial
*  code such as a UPC, Hinban, or EAN. Products are for the most part released on a physical format, such as a DVD or Blu-ray.
*/
  public GnResponseVideoProduct FindProducts(string externalId, GnVideoExternalIdType externalIdType) {
    GnResponseVideoProduct ret = new GnResponseVideoProduct(gnsdk_csharp_marshalPINVOKE.GnVideo_FindProducts__SWIG_5(swigCPtr, externalId, (int)externalIdType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video works using a partial GnVideoProduct object.
*  @param videoProduct [in]
*  @return GnResponseVideoWork
*
*  <p><b>Remarks:</b></p>
*  A partial GnVideoProduct can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(GnVideoProduct videoProduct) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_0(swigCPtr, GnVideoProduct.getCPtr(videoProduct)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video works using a partial GnVideoWork object.
*  @param videoWork [in]
*  @return GnResponseVideoWork
*
*  <p><b>Remarks:</b></p>
*  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(GnVideoWork videoWork) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_1(swigCPtr, GnVideoWork.getCPtr(videoWork)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video works using a partial GnContributor object.
*  @param contributor [in]
*  @return GnResponseVideoWork
*
*  <p><b>Remarks:</b></p>
*  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(GnContributor contributor) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_2(swigCPtr, GnContributor.getCPtr(contributor)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video works using a partial GnVideoSeason object.
*  @param videoSeason [in]
*  @return GnResponseVideoWork
*
*  <p><b>Remarks:</b></p>
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
*  (Season Two), CSI: Miami (Season Three).
*  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(GnVideoSeason videoSeason) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_3(swigCPtr, GnVideoSeason.getCPtr(videoSeason)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video works using a  partial GnVideoSeries object.
*  @param videoSeries [in]
*  @return GnResponseVideoWork
*
*  <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
*  A partial GnVideoSeries object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(GnVideoSeries videoSeries) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_4(swigCPtr, GnVideoSeries.getCPtr(videoSeries)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video works using supported GnDataObject types.
*  @param gnObj [in]
*  @return GnResponseVideoWork
*
*  <p><b>Remarks:</b></p>
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(GnDataObject gnObj) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_5(swigCPtr, GnDataObject.getCPtr(gnObj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video works using a text search.
*  @param textInput [in] text string.
*  @param searchField [in] Can be any #GnVideoSearchField option except #GnVideoSearchField.kSearchFieldProductTitle
*  @param searchType [in] Video search type, see #GnVideoSearchType
*
*  @return GnResponseVideoWork
*  <p><b>Remarks:</b></p>
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(string textInput, GnVideoSearchField searchField, GnVideoSearchType searchType) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_6(swigCPtr, textInput, (int)searchField, (int)searchType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
*  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
*
*  @return GnResponseVideoWork
*  <p><b>Remarks:</b></p>
*  The term 'work' has both generic and specific meanings. It can be used generically to indicate a
*  body of work, or, more specifically, to indicate a particular movie or television show.
*/
  public GnResponseVideoWork FindWorks(string externalId, GnVideoExternalIdType externalIdType) {
    GnResponseVideoWork ret = new GnResponseVideoWork(gnsdk_csharp_marshalPINVOKE.GnVideo_FindWorks__SWIG_7(swigCPtr, externalId, (int)externalIdType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video seasons using a partial GnVideoWork object.
*  @param videoWork [in]
*  @return GnResponseVideoSeasons
*
*  <p><b>Remarks:</b></p>
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
*  (Season Two), CSI: Miami (Season Three).
*  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeasons FindSeasons(GnVideoWork videoWork) {
    GnResponseVideoSeasons ret = new GnResponseVideoSeasons(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeasons__SWIG_0(swigCPtr, GnVideoWork.getCPtr(videoWork)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video seasons using a partial GnContributor object.
*  @param contributor [in]
*  @return GnResponseVideoSeasons
*
*  <p><b>Remarks:</b></p>
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
*  (Season Two), CSI: Miami (Season Three).
*  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeasons FindSeasons(GnContributor contributor) {
    GnResponseVideoSeasons ret = new GnResponseVideoSeasons(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeasons__SWIG_1(swigCPtr, GnContributor.getCPtr(contributor)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video seasons using a partial GnVideoSeason object.
*  @param videoSeason [in]
*  @return GnResponseVideoSeasons
*
*  <p><b>Remarks:</b></p>
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
*  (Season Two), CSI: Miami (Season Three).
*  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeasons FindSeasons(GnVideoSeason videoSeason) {
    GnResponseVideoSeasons ret = new GnResponseVideoSeasons(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeasons__SWIG_2(swigCPtr, GnVideoSeason.getCPtr(videoSeason)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video seasons using a partial GnVideoSeries object.
*  @param videoSeries [in]
*  @return GnResponseVideoSeasons
*
*  <p><b>Remarks:</b></p>
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
*  (Season Two), CSI: Miami (Season Three).
*  A partial GnVideoSeries object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeasons FindSeasons(GnVideoSeries videoSeries) {
    GnResponseVideoSeasons ret = new GnResponseVideoSeasons(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeasons__SWIG_3(swigCPtr, GnVideoSeries.getCPtr(videoSeries)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video seasons using supported GnDataObject types.
*  @param gnObj [in]
*  @return GnResponseVideoSeasons
*
*  <p><b>Remarks:</b></p>
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
*  (Season Two), CSI: Miami (Season Three).
*/
  public GnResponseVideoSeasons FindSeasons(GnDataObject gnObj) {
    GnResponseVideoSeasons ret = new GnResponseVideoSeasons(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeasons__SWIG_4(swigCPtr, GnDataObject.getCPtr(gnObj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video seasons using an external ID.
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
*  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
*  @return GnResponseVideoSeasons
*
*  <p><b>Remarks:</b></p>
*  A Season is an ordered collection of Works, typically representing a season of a TV series. For example: CSI: Miami (Season One), CSI: Miami
*  (Season Two), CSI: Miami (Season Three).
*/
  public GnResponseVideoSeasons FindSeasons(string externalId, GnVideoExternalIdType externalIdType) {
    GnResponseVideoSeasons ret = new GnResponseVideoSeasons(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeasons__SWIG_5(swigCPtr, externalId, (int)externalIdType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video series using a partial GnVideoWork object.
*  @param videoWork [in]
*  @return GnResponseVideoSeries
*
*   <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
*  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeries FindSeries(GnVideoWork videoWork) {
    GnResponseVideoSeries ret = new GnResponseVideoSeries(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeries__SWIG_0(swigCPtr, GnVideoWork.getCPtr(videoWork)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video series using a contributor Tui and TuiTag or partial GnContributor object.
*  @param contributor [in]
*  @return GnResponseVideoSeries
*
*   <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
*  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeries FindSeries(GnContributor contributor) {
    GnResponseVideoSeries ret = new GnResponseVideoSeries(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeries__SWIG_1(swigCPtr, GnContributor.getCPtr(contributor)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video series using a video season Tui and TuiTag or partial GnVideoSeason.
*  @param videoSeason [in]
*  @return GnResponseVideoSeries
*
*   <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
*  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeries FindSeries(GnVideoSeason videoSeason) {
    GnResponseVideoSeries ret = new GnResponseVideoSeries(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeries__SWIG_2(swigCPtr, GnVideoSeason.getCPtr(videoSeason)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video series using a partial GnVideoSeries object.
*  @param videoSeries [in]
*  @return GnResponseVideoSeries
*
*   <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
*  A partial GnVideoSeries object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseVideoSeries FindSeries(GnVideoSeries videoSeries) {
    GnResponseVideoSeries ret = new GnResponseVideoSeries(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeries__SWIG_3(swigCPtr, GnVideoSeries.getCPtr(videoSeries)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video series using supported GnDataObject types.
*  @param gnObj [in]
*  @return GnResponseVideoSeries
*
*   <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
*/
  public GnResponseVideoSeries FindSeries(GnDataObject gnObj) {
    GnResponseVideoSeries ret = new GnResponseVideoSeries(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeries__SWIG_4(swigCPtr, GnDataObject.getCPtr(gnObj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video series using a text search.
*  @param textInput [in]  Video series title
*  @param searchType [in] Can only be #GnVideoSearchType.kSearchFieldSeriesTitle - you cannot search for a Series
*  using #GnVideoSearchType.kSearchFieldAll
*  @return GnResponseVideoSeries
*
*   <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigation.
*/
  public GnResponseVideoSeries FindSeries(string textInput, GnVideoSearchType searchType) {
    GnResponseVideoSeries ret = new GnResponseVideoSeries(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeries__SWIG_5(swigCPtr, textInput, (int)searchType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find video series using an external ID.
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
*  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
*  @return GnResponseVideoSeries
*
*   <p><b>Remarks:</b></p>
*  A Series is a collection of related Works, typically in sequence, and often comprised of Seasons (generally for TV series),
*  for example: CSI: Miami, CSI: Vegas, CSI: Crime Scene Investigati
*/
  public GnResponseVideoSeries FindSeries(string externalId, GnVideoExternalIdType externalIdType) {
    GnResponseVideoSeries ret = new GnResponseVideoSeries(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSeries__SWIG_6(swigCPtr, externalId, (int)externalIdType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find contributors associated with a partial GnVideoWork object.
*  @param videoWork [in]
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person involved in the creation of a work (such as an actor or a director) or
*  an entity (such as a production company).
*  A partial GnVideoWork object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseContributors FindContributors(GnVideoWork videoWork) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_0(swigCPtr, GnVideoWork.getCPtr(videoWork)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find contributors using a partial GnContributor objet.
*  @param contributor [in]
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
*  A partial GnContributor object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseContributors FindContributors(GnContributor contributor) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_1(swigCPtr, GnContributor.getCPtr(contributor)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find contributors associated with a video season using a partial GnVideoSeason.
*  @param videoSeason [in]
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
*  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseContributors FindContributors(GnVideoSeason videoSeason) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_2(swigCPtr, GnVideoSeason.getCPtr(videoSeason)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find contributors associated with a partial GnVideoSeries object.
*  @param videoSeries [in]
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
*  A partial GnVideoSeason object can be constructed in a number of different ways, typically with a Tui or Tui Tag, or one that has been deserialized.
*  Tui is a Gracenote acronym for "title unique identifier". For example: "267348592". This and tuiTag are used for unique identification within the Gracenote service.
*/
  public GnResponseContributors FindContributors(GnVideoSeries videoSeries) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_3(swigCPtr, GnVideoSeries.getCPtr(videoSeries)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find contributors using supported GnDataObject types.
*  @param gnObj [in]
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
*/
  public GnResponseContributors FindContributors(GnDataObject gnObj) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_4(swigCPtr, GnDataObject.getCPtr(gnObj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  @deprecated This method has been deprecated.
*  Find contributors using a text search.
*  @param textInput [in]
*  @param searchType [in]
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
*/
  public GnResponseContributors FindContributors(string textInput, GnVideoSearchType searchType) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_5(swigCPtr, textInput, (int)searchType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find contributors using a text search.
*  @param searchText [in]
*  @param searchField [in] Can be #GnVideoSearchField.kSearchFieldContributorName or #GnVideoSearchField.kSearchFieldAll
*  @param searchType [in] Video search type, see #GnVideoSearchType
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
*/
  public GnResponseContributors FindContributors(string searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_6(swigCPtr, searchText, (int)searchField, (int)searchType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Find contributors using an external ID.
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
*  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
*  @return GnResponseContributors
*
*  <p><b>Remarks:</b></p>
*  A contributor is a person or entity involved in creating a work (e.g., actor, director, production company)
*/
  public GnResponseContributors FindContributors(string externalId, GnVideoExternalIdType externalIdType) {
    GnResponseContributors ret = new GnResponseContributors(gnsdk_csharp_marshalPINVOKE.GnVideo_FindContributors__SWIG_7(swigCPtr, externalId, (int)externalIdType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Performs a Video Explore query for any type of video object. Use this function to retrieve a specific
*  Video Explore object referenced by a GnDataObject.
*  @param gnObj [in]
*  @return GnResponseVideoObjects
*
*/
  public GnResponseVideoObjects FindObjects(GnDataObject gnObj) {
    GnResponseVideoObjects ret = new GnResponseVideoObjects(gnsdk_csharp_marshalPINVOKE.GnVideo_FindObjects__SWIG_0(swigCPtr, GnDataObject.getCPtr(gnObj)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Performs a Video Explore query for any type of video object. Use this function to retrieve
*  all the Video Explore objects (Contributors, Products, Seasons, Series, and Works) associated with a
*  particular external ID.
*  @param externalId [in] External ID. External IDs are 3rd-party IDs used to cross link Gracenote metadata to 3rd-party services.
*  @param externalIdType [in] External ID type; see #GnVideoExternalIdType for available external ID types
*  @return GnResponseVideoObjects
*/
  public GnResponseVideoObjects FindObjects(string externalId, GnVideoExternalIdType externalIdType) {
    GnResponseVideoObjects ret = new GnResponseVideoObjects(gnsdk_csharp_marshalPINVOKE.GnVideo_FindObjects__SWIG_1(swigCPtr, externalId, (int)externalIdType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
*  Performs a VideoID or Video Explore query for search suggestion text. Use this function to suggest potential matching titles,
*  names, and series as a user enters text in a search query. A suggestion search cannot be performed using #GnVideoSearchField.kSearchFieldAll.
*  @param searchText [in] Text string.
*  @param searchField [in] Can be any #GnVideoSearchField option except #GnVideoSearchType.kSearchFieldAll
*  @param searchType [in] Video search type, see #GnVideoSearchType
*  @return GnResponseVideoSuggestions
*/
  public GnResponseVideoSuggestions FindSuggestions(string searchText, GnVideoSearchField searchField, GnVideoSearchType searchType) {
    GnResponseVideoSuggestions ret = new GnResponseVideoSuggestions(gnsdk_csharp_marshalPINVOKE.GnVideo_FindSuggestions(swigCPtr, searchText, (int)searchField, (int)searchType), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public GnStatusEventsDelegate EventHandler() {
    IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnVideo_EventHandler(swigCPtr);
    GnStatusEventsDelegate ret = (cPtr == IntPtr.Zero) ? null : new GnStatusEventsDelegate(cPtr, false);
    return ret;
  }

  public virtual void SetCancel(bool bCancel) {
    gnsdk_csharp_marshalPINVOKE.GnVideo_SetCancel(swigCPtr, bCancel);
  }

  public virtual bool IsCancelled() {
    bool ret = gnsdk_csharp_marshalPINVOKE.GnVideo_IsCancelled(swigCPtr);
    return ret;
  }

/**
*  Retrieves the VideoID and Video Explore library's version string.
*
*  This API can be called at any time, even before initialization and after shutdown. The returned
*  string is a constant. Do not attempt to modify or delete.
*
*  Example: <code>1.2.3.123</code> (Major.Minor.Improvement.Build)<br>
*  Major: New functionality<br>
*  Minor: New or changed features<br>
*  Improvement: Improvements and fixes<br>
*  Build: Internal build number<br>
*/
  public string Version {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideo_Version_get(swigCPtr) );
	} 

  }

/**
*  Retrieves the VideoID and Video Explore library's build date as a string.
*  This API can be called at any time, even before initialization and after shutdown. The returned
*  string is a constant. Do not attempt to modify or delete.
*  @return String with format: YYYY-MM-DD hh:mm UTC
*
*  Example:<code>"2008-02-12 00:41 UTC"</code>
*/
  public string BuildDate {
	get
	{   
		/* csvarout typemap code */
		return GnMarshalUTF8.StringFromNativeUtf8(gnsdk_csharp_marshalPINVOKE.GnVideo_BuildDate_get(swigCPtr) );
	} 

  }

}

}
