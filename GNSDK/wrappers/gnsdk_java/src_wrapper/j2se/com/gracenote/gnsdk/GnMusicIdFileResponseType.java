
package com.gracenote.gnsdk;

/** 
* Type of response requested from DoTrackId, DoAlbumId and DoLibraryId 
*/ 
 
public enum GnMusicIdFileResponseType {
 
 
  kResponseAlbums(1),
 
 
  kResponseMatches;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnMusicIdFileResponseType swigToEnum(int swigValue) {
    GnMusicIdFileResponseType[] swigValues = GnMusicIdFileResponseType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnMusicIdFileResponseType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnMusicIdFileResponseType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileResponseType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileResponseType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnMusicIdFileResponseType(GnMusicIdFileResponseType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

