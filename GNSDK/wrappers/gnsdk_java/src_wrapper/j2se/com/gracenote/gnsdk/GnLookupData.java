
package com.gracenote.gnsdk;

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
 
  kLookupDataInvalid(0),
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
 
 
  kLookupDataAdditionalCredits;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLookupData swigToEnum(int swigValue) {
    GnLookupData[] swigValues = GnLookupData.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLookupData swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLookupData.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLookupData() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLookupData(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLookupData(GnLookupData swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

