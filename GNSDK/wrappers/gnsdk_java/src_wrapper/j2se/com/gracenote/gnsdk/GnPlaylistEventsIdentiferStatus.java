
package com.gracenote.gnsdk;

/** 
* Specifies the status of a unique identifier when sychronizing 
* a Playlist Collection Summary with a user's collection. 
*/ 
 
public enum GnPlaylistEventsIdentiferStatus {
/** 
* The corresponding identifier's status is unknown, the default state 
*/ 
 
  kIdentifierStatusUnknown(0),
/** 
* The corresponding identifier is new, meaning it has been added to the 
* user's media collection and needs to be added to the Collection Summary 
*/ 
 
  kIdentifierStatusNew(10),
/** 
* The corresponding identifier is old, meaning it has been deleted from 
* the user's media collection and needs to be removed from the 
* Collection Summary 
*/ 
 
  kIdentifierStatusOld(20);

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnPlaylistEventsIdentiferStatus swigToEnum(int swigValue) {
    GnPlaylistEventsIdentiferStatus[] swigValues = GnPlaylistEventsIdentiferStatus.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnPlaylistEventsIdentiferStatus swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnPlaylistEventsIdentiferStatus.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnPlaylistEventsIdentiferStatus() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnPlaylistEventsIdentiferStatus(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnPlaylistEventsIdentiferStatus(GnPlaylistEventsIdentiferStatus swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

