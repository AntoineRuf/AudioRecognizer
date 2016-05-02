
namespace GracenoteSDK {

/**
*  The TOC Flag type.
*/
public enum GnVideoTOCFlag {
/**
*  Generally recommended flag to use when setting a video TOC.
*  <p><b>Remarks:</b></p>
*  Use this flag for the TOC flag parameter that is set with the
*  FindProducts() API, for all general cases; this includes when using the Gracenote
*  Video Thin Client component to produce TOC strings.
*  For cases when other VideoID TOC flags seem necessary, contact Gracenote for guidance on setting
*  the correct flag.
*/
  kTOCFlagDefault = 0,
/**
*  Flag to indicate a given simple video TOC is from a PAL (Phase Alternating Line) disc.
*  <p><b>Remarks:</b></p>
*  Use this flag only when directed to by Gracenote. Only special video TOCs that are provided by
*  Gracenote and external to the
*  GNSDK may require this flag.
*/
  kTOCFlagPal,
/**
*  Flag to indicate a given simple video TOC contains angle data.
*  <p><b>Remarks:</b></p>
*  Use this flag only if Gracenote directs you to. Only special video TOCs that Gracenote provides
*  and that are external to the GNSDK may require this flag.
*/
  kTOCFlagAngles
}

}
