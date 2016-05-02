
package com.gracenote.gnsdk;

/** 
*  The type of text search field that is used to find results. 
*/ 
 
public enum GnVideoSearchField {
/** 
*  Contributor name search field. 
*/ 
 
  kSearchFieldContributorName(1),
/** 
*  Character name search field. 
*/ 
 
  kSearchFieldCharacterName,
/** 
*  Work franchise search field. 
*/ 
 
  kSearchFieldWorkFranchise,
/** 
*  Work series search field. 
*/ 
 
  kSearchFieldWorkSeries,
/** 
*  Work title search field. 
*/ 
 
  kSearchFieldWorkTitle,
/** 
* <p> 
*  Product title search field. 
*/ 
 
  kSearchFieldProductTitle,
/** 
* <p> 
*  Series title search field. 
*/ 
 
  kSearchFieldSeriesTitle,
/** 
*  Comprehensive search field. 
*  <p><b>Remarks:</b></p> 
*  This option searches all relevant search fields and returns any 
*  data found. Note, however, that you cannot use this search field for 
*  suggestion search queries. 
*/ 
 
  kSearchFieldAll;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnVideoSearchField swigToEnum(int swigValue) {
    GnVideoSearchField[] swigValues = GnVideoSearchField.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnVideoSearchField swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnVideoSearchField.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnVideoSearchField() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnVideoSearchField(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnVideoSearchField(GnVideoSearchField swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

