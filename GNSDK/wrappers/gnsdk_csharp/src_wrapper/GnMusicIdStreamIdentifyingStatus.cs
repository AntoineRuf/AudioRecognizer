
namespace GracenoteSDK {

/**
* The status of the channel or current identification query.
*  As a channel processes audio or as an identification query progresses
*  status notifications are provided via the events delegate.
* @ingroup Music_MusicIDStream_TypesEnums
*/
public enum GnMusicIdStreamIdentifyingStatus {
/** Invalid status
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingInvalid = 0,
/** Identification query started
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingStarted,
/** Fingerprint generated for sample audio
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingFpGenerated,
/** Local query started for identification
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingLocalQueryStarted,
/** Local query ended for identification
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingLocalQueryEnded,
/** Online query started for identification
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingOnlineQueryStarted,
/** Online query ended for identification
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingOnlineQueryEnded,
/** Identification query ended
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kStatusIdentifyingEnded
}

}
