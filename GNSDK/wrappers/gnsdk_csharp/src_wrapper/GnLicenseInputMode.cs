
namespace GracenoteSDK {

/**
*  License submission options
*  When your app allocates an SDK Manager object (GnManager) it passes the license data you obtained from GSS.
*  Your license determines the content you can access from the Gracenote service
*  License data can be submitted in different ways, as these enums indicate
*/
public enum GnLicenseInputMode {
/**
* Submit license content as string
*/
  kLicenseInputModeInvalid = 0,
/**
* Submit license content in file
*/
  kLicenseInputModeString,
/**
* Submit license content from stdin
*/
  kLicenseInputModeFilename,

  kLicenseInputModeStandardIn
}

}
