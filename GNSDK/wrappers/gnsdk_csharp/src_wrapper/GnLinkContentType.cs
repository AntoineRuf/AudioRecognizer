
namespace GracenoteSDK {

/**
*  Indicates available content types that can be retrieved for Albums, Lyrics, Tracks, Video
*  Products, Contributors, Works, Seasons, or Series (or some combination of these object types). Not
*  all content types are available for all objects.
*/
public enum GnLinkContentType {
/** @internal kLinkContentUnknown @endinternal
*
*   Indicates an invalid content type.
* @ingroup Link_TypesEnums
*/
  kLinkContentUnknown = 0,
/** @internal kLinkContentCoverArt @endinternal
*
*   Retrieves cover artwork; this is Album-level and Video Product-level
*   content.
*
*   Use with #GNSDK_GDO_TYPE_ALBUM and #GNSDK_GDO_TYPE_VIDEO_PRODUCT.
*
*   Do not use with #GNSDK_GDO_TYPE_VIDEO_WORK,
*   #GNSDK_GDO_TYPE_VIDEO_SERIES, #GNSDK_GDO_TYPE_VIDEO_SEASON, or
*   #GNSDK_GDO_TYPE_CONTRIBUTOR.
* @ingroup Link_TypesEnums
*/
  kLinkContentCoverArt,
/** @internal kLinkContentGenreArt @endinternal
*
*   Retrieves artwork for the object's primary genre; this is Album-level
*   and Track-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentGenreArt,
/** @internal kLinkContentReview @endinternal
*
*   Retrieves a review for the object; this is Album-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentReview,
/** @internal kLinkContentBiography @endinternal
*
*   Retrieves a biography for the object; this is Album-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentBiography,
/** @internal kLinkContentArtistNews @endinternal
*
*   Retrieves news for the artist; this is Album-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentArtistNews,
/** @internal kLinkContentLyricXML @endinternal
*
*   Retrieves lyrics in XML form; this is Lyric-level and Track-level
*   data.
* @ingroup Link_TypesEnums
*/
  kLinkContentLyricXML,
/** @internal kLinkContentLyricText @endinternal
*
*   Retrieves lyrics in plain text form; this is Lyric-level and
*   Track-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentLyricText,
/** @internal kLinkContentDspData @endinternal
*
*   Retrieves DSP content; this is Track-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentDspData,
/** @internal kLinkContentCommentsListener @endinternal
*
*   Retrieves listener comments; this is Album-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentCommentsListener,
/** @internal kLinkContentCommentsRelease @endinternal
*
*   Retrieves new release comments; this is Album-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentCommentsRelease,
/** @internal kLinkContentNews @endinternal
*
*   Retrieves news for the object; this is Album-level content.
* @ingroup Link_TypesEnums
*/
  kLinkContentNews,
/** @internal kLinkContentImage @endinternal
*
*   Retrieves an image for specific Video types.
*
*   Use with #GNSDK_GDO_TYPE_VIDEO_WORK, #GNSDK_GDO_TYPE_VIDEO_SERIES,
*   #GNSDK_GDO_TYPE_VIDEO_SEASON, and video #GNSDK_GDO_TYPE_CONTRIBUTOR.
*
*   Do not use with #GNSDK_GDO_TYPE_VIDEO_PRODUCT.
*
*   Note: At the time of this guide's publication, support for Video
*   Explore Seasons and Series image retrieval through Seasons, Series, and
*   Works queries is limited. Contact your Gracenote Professional Services
*   representative for updates on the latest supported images.
* @ingroup Link_TypesEnums
*/
  kLinkContentImage,
/** @internal kLinkContentImageArtist @endinternal
* Retrieves an artist image for the object; this can be album-level or contributor-level content.
* Use with #GNSDK_GDO_TYPE_ALBUM or #GNSDK_GDO_TYPE_CONTRIBUTOR.
* There are three ways to retrieve an artist image:
* <ul><li>If the GDO is the result of an album match, you can retrieve the artist image from the album GDO.</li>
* <li>If the GDO is the result of an album match, you can retrieve a contributor GDO from the album GDO,
* and then retrieve the artist image from the contributor GDO.</li>
* <li>If the GDO is the result of a contributor match, which can only come from a local text query,
* you can use the GDO to retrieve the artist image from the local image database.
* However, you cannot retrieve the artist image from the online database using this GDO.</li></ul>
*
* The GDO used to retrieve an artist image can be the full object or a recently deserialized object.
*
*   Note: At the time of this guide's publication, the available Album
*   artist images are limited. Contact your Gracenote Professional Services
*   representative for updates on the latest supported images.
* @ingroup Link_TypesEnums
*/
  kLinkContentImageArtist
}

}
