
namespace GracenoteSDK {

/**
* Gracenote user registration mode
*/
public enum GnUserRegisterMode {
/**
* Register a user via a netowrk connection with Gracenote Service. A user
* must be registered online before any online queries can be made against
* Gracenote Service.
*/
  kUserRegisterModeOnline = 1,
/**
* Register a user for local use only. User's registered locally can only
* perform queries against local databases and not against Gracenote
* Service.
*/
  kUserRegisterModeLocalOnly
}

}
