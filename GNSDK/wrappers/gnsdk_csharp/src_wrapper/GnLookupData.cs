
namespace GracenoteSDK {

/**
* Types of data that can be delivered in a search response
*/
public enum GnLookupData {
/**
* Indicates whether a response should include data for use in fetching content (like images).
* <p><b>Remarks:</b></p>
* An application's client ID must be entitled to retrieve this specialized data. Contact your
*	Gracenote Global Services and Support representative with any questions about this enhanced
*	functionality.
*/
  kLookupDataInvalid = 0,
/**
* Indicates whether a response should include any associated classical music data.
* <p><b>Remarks:</b></p>
* An application's license must be entitled to retrieve this specialized data. Contact your
* Gracenote Global Services and Support representative with any questions about this enhanced functionality.
*/
  kLookupDataContent,
/**
* Indicates whether a response should include any associated sonic attribute data.
* <p><b>Remarks:</b></p>
* An application's license must be entitled to retrieve this specialized data. Contact your
* Gracenote Global Services and Support representative with any questions about this enhanced functionality.
*/
  kLookupDataClassical,
/**
* Indicates whether a response should include associated attribute data for GNSDK Playlist.
* <p><b>Remarks:</b></p>
* An application's license must be entitled to retrieve this specialized data. Contact your
* Gracenote Global Services and Support representative with any questions about this enhanced functionality.
*/
  kLookupDataSonicData,
/**
* Indicates whether a response should include external IDs (third-party IDs).
* <p><b>Remarks:</b></p>
* External IDs are third-party IDs associated with the results (such as an Amazon ID),
*	configured specifically for your application.
* An application's client ID must be entitled to retrieve this specialized data. Contact your
* Gracenote Global Services and Support representative with any questions about this enhanced functionality.
* External IDs can be retrieved from applicable query response objects.
*/
  kLookupDataPlaylist,
/**
* Indicates whether a response should include global IDs.
*/
  kLookupDataExternalIds,
/**
* Indicates whether a response should include additional credits.
*/
  kLookupDataGlobalIds,

  kLookupDataAdditionalCredits
}

}
