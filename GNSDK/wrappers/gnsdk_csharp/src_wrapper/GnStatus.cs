
namespace GracenoteSDK {

/** @internal GnStatus @endinternal
*  Indicates messages that can be received in status callbacks.
* @ingroup StatusCallbacks_TypesEnums
*/
public enum GnStatus {
/** @internal kStatusUnknown @endinternal
* Status unknown.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusUnknown = 0,
/** @internal kStatusBegin @endinternal
* Issued once per application function call, at the beginning of the call; percent_complete = 0.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusBegin,
/** @internal kStatusProgress @endinternal
* Issued roughly 10 times per application function call; percent_complete values between 1-100.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusProgress,
/** @internal kStatusComplete @endinternal
* Issued once per application function call, at the end of the call; percent_complete = 100.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusComplete,
/** @internal kStatusErrorInfo @endinternal
* Issued when an error is encountered. If sent, call #gnsdk_manager_error_info().
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusErrorInfo,
/** @internal kStatusConnecting @endinternal
* Issued when connecting to network.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusConnecting,
/** @internal kStatusSending @endinternal
* Issued when uploading.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusSending,
/** @internal kStatusReceiving @endinternal
* Issued when downloading.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusReceiving,
/** @internal kStatusDisconnected @endinternal
* Issued when disconnected from network.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusDisconnected,
/** @internal kStatusReading @endinternal
* Issued when reading from storage.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusReading,
/** @internal kStatusWriting @endinternal
* Issued when writing to storage.
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusWriting,
/** @internal gnsdk_status_cancelled @endinternal
* Issued when transaction/query is cancelled
* @ingroup StatusCallbacks_TypesEnums
*/
  kStatusCancelled
}

}
