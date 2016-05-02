
namespace GracenoteSDK {

/**
*  The status value of the current query.
* @ingroup Music_MusicIDFile_TypesEnums
*/
public enum GnMusicIdFileInfoStatus {
/**
* FileInfo has not been processed.
* @ingroup Music_MusicIDFile_TypesEnums
*/
  kMusicIdFileInfoStatusUnprocessed = 0,
/**
* FileInfo is currently being processed.
* @ingroup Music_MusicIDFile_TypesEnums
*/
  kMusicIdFileInfoStatusProcessing = 1,
/**
* An error occurred while processing the FileInfo.
* @ingroup Music_MusicIDFile_TypesEnums
*/
  kMusicIdFileInfoStatusError = 2,
/**
* No results were found for FileInfo.
* @ingroup Music_MusicIDFile_TypesEnums
*/
  kMusicIdFileInfoStatusResultNone = 3,
/**
* Single preferred response available for FileInfo.
* @ingroup Music_MusicIDFile_TypesEnums
*/
  kMusicIdFileInfoStatusResultSingle = 4,
/**
* All retrieved results available for FileInfo.
* @ingroup Music_MusicIDFile_TypesEnums
*/
  kMusicIdFileInfoStatusResultAll = 5
}

}
