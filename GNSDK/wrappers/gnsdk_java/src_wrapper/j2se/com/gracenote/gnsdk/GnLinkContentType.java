
package com.gracenote.gnsdk;

/** 
*  Indicates available content types that can be retrieved for Albums, Lyrics, Tracks, Video 
*  Products, Contributors, Works, Seasons, or Series (or some combination of these object types). Not 
*  all content types are available for all objects. 
*/ 
 
public enum GnLinkContentType {
/** 
* <p> 
*   Indicates an invalid content type. 
* 
*/ 
 
  kLinkContentUnknown(0),
/** 
* <p> 
*   Retrieves cover artwork; this is Album-level and Video Product-level 
*   content. 
* <p> 
*   Use with #GNSDK_GDO_TYPE_ALBUM and #GNSDK_GDO_TYPE_VIDEO_PRODUCT. 
* <p> 
*   Do not use with #GNSDK_GDO_TYPE_VIDEO_WORK, 
*   #GNSDK_GDO_TYPE_VIDEO_SERIES, #GNSDK_GDO_TYPE_VIDEO_SEASON, or 
*   #GNSDK_GDO_TYPE_CONTRIBUTOR. 
* 
*/ 
 
  kLinkContentCoverArt,
/** 
* <p> 
*   Retrieves artwork for the object's primary genre; this is Album-level 
*   and Track-level content. 
* 
*/ 
 
  kLinkContentGenreArt,
/** 
* <p> 
*   Retrieves a review for the object; this is Album-level content. 
* 
*/ 
 
  kLinkContentReview,
/** 
* <p> 
*   Retrieves a biography for the object; this is Album-level content. 
* 
*/ 
 
  kLinkContentBiography,
/** 
* <p> 
*   Retrieves news for the artist; this is Album-level content. 
* 
*/ 
 
  kLinkContentArtistNews,
/** 
* <p> 
*   Retrieves lyrics in XML form; this is Lyric-level and Track-level 
*   data. 
* 
*/ 
 
  kLinkContentLyricXML,
/** 
* <p> 
*   Retrieves lyrics in plain text form; this is Lyric-level and 
*   Track-level content. 
* 
*/ 
 
  kLinkContentLyricText,
/** 
* <p> 
*   Retrieves DSP content; this is Track-level content. 
* 
*/ 
 
  kLinkContentDspData,
/** 
* <p> 
*   Retrieves listener comments; this is Album-level content. 
* 
*/ 
 
  kLinkContentCommentsListener,
/** 
* <p> 
*   Retrieves new release comments; this is Album-level content. 
* 
*/ 
 
  kLinkContentCommentsRelease,
/** 
* <p> 
*   Retrieves news for the object; this is Album-level content. 
* 
*/ 
 
  kLinkContentNews,
/** 
* <p> 
*   Retrieves an image for specific Video types. 
* <p> 
*   Use with #GNSDK_GDO_TYPE_VIDEO_WORK, #GNSDK_GDO_TYPE_VIDEO_SERIES, 
*   #GNSDK_GDO_TYPE_VIDEO_SEASON, and video #GNSDK_GDO_TYPE_CONTRIBUTOR. 
* <p> 
*   Do not use with #GNSDK_GDO_TYPE_VIDEO_PRODUCT. 
* <p> 
*   Note: At the time of this guide's publication, support for Video 
*   Explore Seasons and Series image retrieval through Seasons, Series, and 
*   Works queries is limited. Contact your Gracenote Professional Services 
*   representative for updates on the latest supported images. 
* 
*/ 
 
  kLinkContentImage,
/** 
* Retrieves an artist image for the object; this can be album-level or contributor-level content. 
* Use with #GNSDK_GDO_TYPE_ALBUM or #GNSDK_GDO_TYPE_CONTRIBUTOR. 
* There are three ways to retrieve an artist image: 
* <ul><li>If the GDO is the result of an album match, you can retrieve the artist image from the album GDO.</li> 
* <li>If the GDO is the result of an album match, you can retrieve a contributor GDO from the album GDO, 
* and then retrieve the artist image from the contributor GDO.</li> 
* <li>If the GDO is the result of a contributor match, which can only come from a local text query, 
* you can use the GDO to retrieve the artist image from the local image database. 
* However, you cannot retrieve the artist image from the online database using this GDO.</li></ul> 
* <p> 
* The GDO used to retrieve an artist image can be the full object or a recently deserialized object. 
* <p> 
*   Note: At the time of this guide's publication, the available Album 
*   artist images are limited. Contact your Gracenote Professional Services 
*   representative for updates on the latest supported images. 
* 
*/ 
 
  kLinkContentImageArtist;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLinkContentType swigToEnum(int swigValue) {
    GnLinkContentType[] swigValues = GnLinkContentType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLinkContentType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLinkContentType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLinkContentType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLinkContentType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLinkContentType(GnLinkContentType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

