
package com.gracenote.gnsdk;

/** 
** <b>Experimental</b>: {@link GnMoodgridPresentation} 
*/ 
 
public class GnMoodgridPresentation extends GnObject {
  private long swigCPtr;

  protected GnMoodgridPresentation(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnMoodgridPresentation_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnMoodgridPresentation obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnMoodgridPresentation(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GnMoodgridPresentationDataIterable moods() throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridPresentationDataIterable(gnsdk_javaJNI.GnMoodgridPresentation_moods(swigCPtr, this), true);
  }

/** 
* Retrieves the presentation type the defines the no. of moods available in this presentation.. 
* @return moods 
*/ 
 
  public GnMoodgridPresentationType layoutType() throws com.gracenote.gnsdk.GnException {
    return GnMoodgridPresentationType.swigToEnum(gnsdk_javaJNI.GnMoodgridPresentation_layoutType(swigCPtr, this));
  }

/** 
*  Retrieves the coordinate type that defines the layout of the presentation.  
* @return moodgridcoordinatetype. 
*/ 
 
  public GnMoodgridCoordinateType coordinateType() {
    return GnMoodgridCoordinateType.swigToEnum(gnsdk_javaJNI.GnMoodgridPresentation_coordinateType(swigCPtr, this));
  }

/** 
* Adds a filter to the presentation for the inclusion of a list type to include or exclude from the recommendations. 
* @param uniqueIdentifier [in] : unique identifier for the presentation representing this filter. 
* @param elistType [in] : list type  
* @param strValueId [in] : list value that is to be operated upon. 
* @param eConditionType [in]: filter condition 
*/ 
 
  public void addFilter(String uniqueIdentifier, GnMoodgridFilterListType elistType, String strValueId, GnMoodgridFilterConditionType eConditionType) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMoodgridPresentation_addFilter(swigCPtr, this, uniqueIdentifier, elistType.swigValue(), strValueId, eConditionType.swigValue());
  }

/** 
* Removes a filter from the presentation represented by the unique identifier. 
* @param uniqueIdentifier [in] : identifier that represents the filter to be removed. 
*/ 
 
  public void removeFilter(String uniqueIdentifier) throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMoodgridPresentation_removeFilter(swigCPtr, this, uniqueIdentifier);
  }

/** 
* Removes all filters from the presentation 
*/ 
 
  public void removeAllFilters() throws com.gracenote.gnsdk.GnException {
    gnsdk_javaJNI.GnMoodgridPresentation_removeAllFilters(swigCPtr, this);
  }

/** 
* Retrieves a mood name as defined by the locale for a given data point in the presentation. 
* @param position [in] : data position 
* @return moodname 
*/ 
 
  public String moodName(GnMoodgridDataPoint position) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMoodgridPresentation_moodName(swigCPtr, this, GnMoodgridDataPoint.getCPtr(position), position);
  }

/** 
* Retrieves a mood id for the given data point in the presentation. 
* @param position [in] : data position 
* @return moodid. 
*/ 
 
  public String moodId(GnMoodgridDataPoint position) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMoodgridPresentation_moodId(swigCPtr, this, GnMoodgridDataPoint.getCPtr(position), position);
  }

/** 
* Generates recommendations for a given mood data point and provider. The reccomentations are represented by a  
* {@link GnMoodgridResult}. 
* @param provider [in] : moodgrid provider that the results must come from. 
* @param position [in] : data point that represents the mood for which reccomendation are requested. 
* @return {@link GnMoodgridResult} 
*/ 
 
  public GnMoodgridResult findRecommendations(GnMoodgridProvider provider, GnMoodgridDataPoint position) throws com.gracenote.gnsdk.GnException {
    return new GnMoodgridResult(gnsdk_javaJNI.GnMoodgridPresentation_findRecommendations(swigCPtr, this, GnMoodgridProvider.getCPtr(provider), provider, GnMoodgridDataPoint.getCPtr(position), position), true);
  }

/** 
* Generates a recommendations estimate for a given mood data point and provider. The estimate is dependent on the  
* provider. Use this functionality for creating a heat map of all the moods supported in the presentation. 
* @param provider [in] :moodgrid provider that the estimate must come from. 
* @param position [in] : data point that represents the mood for which the estimate is requested. 
* @return count representing the estimate. 
*/ 
 
  public long findRecommendationsEstimate(GnMoodgridProvider provider, GnMoodgridDataPoint position) throws com.gracenote.gnsdk.GnException {
    return gnsdk_javaJNI.GnMoodgridPresentation_findRecommendationsEstimate(swigCPtr, this, GnMoodgridProvider.getCPtr(provider), provider, GnMoodgridDataPoint.getCPtr(position), position);
  }

}
