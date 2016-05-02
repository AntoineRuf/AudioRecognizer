
namespace GracenoteSDK {

/**
* Thread priority values for GNSDK multi-threaded functionality such as  MusicID-File.
*/
public enum GnThreadPriority {
/**
* Use of default thread priority.
*/
  kThreadPriorityInvalid = 0,
/**
* Use idle thread priority.
*/
  kThreadPriorityDefault,
/**
* Use low thread priority (default).
*/
  kThreadPriorityIdle,
/**
* Use normal thread priority.
*/
  kThreadPriorityLow,
/**
* Use high thread priority.
*/
  kThreadPriorityNormal,

  kThreadPriorityHigh
}

}
