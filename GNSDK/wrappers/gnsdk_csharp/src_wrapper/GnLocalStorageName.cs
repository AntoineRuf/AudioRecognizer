
namespace GracenoteSDK {

/**
* Gracenote local database names
* Gracenote supports local lookup for various types of identification
* and content, each is provided in it's own Gracenote database. Each name
* herein represents a specific local Gracenote database.
* @ingroup Setup_StorageIDs
*/
public enum GnLocalStorageName {
/**
* Name of the local storage the SDK uses to query Gracenote Content.
* @ingroup Setup_StorageIDs
*/
  kLocalStorageInvalid = 0,
/**
* Name of the local storage the SDK uses to query Gracenote Metadata.
* @ingroup Setup_StorageIDs
*/
  kLocalStorageContent,
/**
* Name of the local storage the SDK uses for CD TOC searching.
* @ingroup Setup_StorageIDs
*/
  kLocalStorageMetadata,
/**
* Name of the local storage the SDK uses for text searching.
* @ingroup Setup_StorageIDs
*/
  kLocalStorageTOCIndex,
/**
* For referencing all the above storages that make up the local storage.
* @ingroup Setup_StorageIDs
*/
  kLocalStorageTextIndex,

  kLocalStorageAll
}

}
