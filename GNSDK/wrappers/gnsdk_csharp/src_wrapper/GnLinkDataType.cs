
namespace GracenoteSDK {

/** @internal GnLinkDataType @endinternal
*  Indicates possible data formats for the retrieved content.
* @ingroup Link_TypesEnums
*/
public enum GnLinkDataType {
/** @internal kLinkDataUnknown @endinternal
*
*   Indicates an invalid data type.
* @ingroup Link_TypesEnums
*/
  kLinkDataUnknown = 0,
/** @internal kLinkDataTextPlain @endinternal
*
*   Indicates the content buffer contains plain text data (null terminated).
* @ingroup Link_TypesEnums
*/
  kLinkDataTextPlain = 1,
/** @internal kLinkDataTextXML @endinternal
*
*   Indicates the content buffer contains XML data (null terminated).
* @ingroup Link_TypesEnums
*/
  kLinkDataTextXML = 2,
/** @internal kLinkDataNumber @endinternal
*
*   Indicates the content buffer contains a numerical value
*   (gnsdk_uint32_t). Unused.
* @ingroup Link_TypesEnums
*/
  kLinkDataNumber = 10,
/** @internal kLinkDataImageJpeg @endinternal
*
*   Indicates the content buffer contains jpeg image data.
* @ingroup Link_TypesEnums
*/
  kLinkDataImageJpeg = 20,
/** @internal kLinkDataImagePng @endinternal
*
*   Indicates the content buffer contains png image data.
* @ingroup Link_TypesEnums
*/
  kLinkDataImagePng = 30,
/** @internal kLinkDataImageBinary @endinternal
*
*   Indicates the content buffer contains externally defined binary data.
* @ingroup Link_TypesEnums
*/
  kLinkDataImageBinary = 100
}

}
