
namespace GracenoteSDK {

/** No event
* @ingroup Music_MusicIDStream_TypesEnums
*/
public enum GnMusicIdStreamApplicationEventType {
/** Metadata change event
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kApplicationEventNone = 0,
/** Broadcast channel change event
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kApplicationEventMetadataChange,
/** Broadcast pause event
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kApplicationEventBroadcastChange,
/** Broadcast resume event
* @ingroup Music_MusicIDStream_TypesEnums
*/
  kApplicationEventPause,

  kApplicationEventResume
}

}
