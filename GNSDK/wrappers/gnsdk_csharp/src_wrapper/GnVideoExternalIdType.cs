
namespace GracenoteSDK {

/**
*  The video external ID type.
*/
public enum GnVideoExternalIdType {
/**
*  Sets a Universal Product Code (UPC) value as an external ID for a Products query.
*  <p><b>Remarks:</b></p>
*  Use as the external ID type parameter set with the ExternalIdTypeSet() API when
*  providing a video UPC value for identification.
*/
  kExternalIdTypeUPC = 1,
/**
*
*  Sets a International Standard Audiovisual Number (ISAN) code as an external ID for a Works
*  query.
*  <p><b>Remarks:</b></p>
*  Use as the external ID Type parameter set with the ExternalIdTypeSet() API when
*   providing a video ISAN value for identification.
*/
  kExternalIdTypeISAN
}

}
