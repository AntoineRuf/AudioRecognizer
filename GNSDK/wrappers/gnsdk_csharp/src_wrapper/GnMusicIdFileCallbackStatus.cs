
namespace GracenoteSDK {

/**
*  Status codes passed to the gnsdk_musicidfile_callback_status_fn() callback.
* @ingroup Music_MusicIDFile_TypesEnums
*/
public enum GnMusicIdFileCallbackStatus {
  kMusicIdFileCallbackStatusProcessingBegin = 0x100,
  kMusicIdFileCallbackStatusFileInfoQuery = 0x150,
  kMusicIdFileCallbackStatusProcessingComplete = 0x199,
  kMusicIdFileCallbackStatusProcessingError = 0x299,
  kMusicIdFileCallbackStatusError = 0x999
}

}
