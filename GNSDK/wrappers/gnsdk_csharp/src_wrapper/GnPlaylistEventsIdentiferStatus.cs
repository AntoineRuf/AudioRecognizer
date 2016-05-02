
namespace GracenoteSDK {

/**
* Specifies the status of a unique identifier when sychronizing
* a Playlist Collection Summary with a user's collection.
*/
public enum GnPlaylistEventsIdentiferStatus {
/**
* The corresponding identifier's status is unknown, the default state
*/
  kIdentifierStatusUnknown = 0,
/**
* The corresponding identifier is new, meaning it has been added to the
* user's media collection and needs to be added to the Collection Summary
*/
  kIdentifierStatusNew = 10,
/**
* The corresponding identifier is old, meaning it has been deleted from
* the user's media collection and needs to be removed from the
* Collection Summary
*/
  kIdentifierStatusOld = 20
}

}
