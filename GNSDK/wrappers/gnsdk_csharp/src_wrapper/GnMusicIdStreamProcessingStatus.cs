
namespace GracenoteSDK {

/**
* GnMusicIdStreamProcessingStatus is currently considered to be experimental.
* An application should only use this option if it is advised by Gracenote Global Services and Support representative.
* Contact your Gracenote Global Services and Support representative with any questions about this enhanced functionality.
* @ingroup Music_MusicIDStream_TypesEnums
*/
public enum GnMusicIdStreamProcessingStatus {

  kStatusProcessingInvalid = 0,

  kStatusProcessingAudioNone,

  kStatusProcessingAudioSilence,

  kStatusProcessingAudioNoise,

  kStatusProcessingAudioSpeech,

  kStatusProcessingAudioMusic,

  kStatusProcessingTransitionNone,

  kStatusProcessingTransitionChannelChange,

  kStatusProcessingTransitionContentToContent,

  kStatusProcessingErrorNoClassifier,

  kStatusProcessingAudioStarted,

  kStatusProcessingAudioEnded
}

}
