
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
** <b>Experimental</b>: GnMoodgridPresentation
*/
public class GnMoodgridPresentation : GnObject {
  private HandleRef swigCPtr;

  internal GnMoodgridPresentation(IntPtr cPtr, bool cMemoryOwn) : base(gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(GnMoodgridPresentation obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~GnMoodgridPresentation() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_GnMoodgridPresentation(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

/**
*  Retrieves the coordinate type that defines the layout of the presentation. 
* @return moodgridcoordinatetype.
*/
  public GnMoodgridCoordinateType CoordinateType() {
    GnMoodgridCoordinateType ret = (GnMoodgridCoordinateType)gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_CoordinateType(swigCPtr);
    return ret;
  }

/**
* Adds a filter to the presentation for the inclusion of a list type to include or exclude from the recommendations.
* @param uniqueIdentifier [in] : unique identifier for the presentation representing this filter.
* @param elistType [in] : list type 
* @param strValueId [in] : list value that is to be operated upon.
* @param eConditionType [in]: filter condition
*/
  public void AddFilter(string uniqueIdentifier, GnMoodgridFilterListType elistType, string strValueId, GnMoodgridFilterConditionType eConditionType) {
  System.IntPtr tempuniqueIdentifier = GnMarshalUTF8.NativeUtf8FromString(uniqueIdentifier);
  System.IntPtr tempstrValueId = GnMarshalUTF8.NativeUtf8FromString(strValueId);
    try {
      gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_AddFilter(swigCPtr, tempuniqueIdentifier, (int)elistType, tempstrValueId, (int)eConditionType);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempuniqueIdentifier);
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempstrValueId);
    }
  }

/**
* Removes a filter from the presentation represented by the unique identifier.
* @param uniqueIdentifier [in] : identifier that represents the filter to be removed.
*/
  public void RemoveFilter(string uniqueIdentifier) {
  System.IntPtr tempuniqueIdentifier = GnMarshalUTF8.NativeUtf8FromString(uniqueIdentifier);
    try {
      gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_RemoveFilter(swigCPtr, tempuniqueIdentifier);
      if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    } finally {
 GnMarshalUTF8.ReleaseMarshaledUTF8String(tempuniqueIdentifier);
    }
  }

/**
* Removes all filters from the presentation
*/
  public void RemoveAllFilters() {
    gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_RemoveAllFilters(swigCPtr);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
  }

/**
* Retrieves a mood name as defined by the locale for a given data point in the presentation.
* @param position [in] : data position
* @return moodname
*/
  public string MoodName(GnMoodgridDataPoint position) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_MoodName(swigCPtr, GnMoodgridDataPoint.getCPtr(position));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves a mood id for the given data point in the presentation.
* @param position [in] : data position
* @return moodid.
*/
  public string MoodId(GnMoodgridDataPoint position) {
    string ret = gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_MoodId(swigCPtr, GnMoodgridDataPoint.getCPtr(position));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Generates recommendations for a given mood data point and provider. The reccomentations are represented by a 
* GnMoodgridResult.
* @param provider [in] : moodgrid provider that the results must come from.
* @param position [in] : data point that represents the mood for which reccomendation are requested.
* @return GnMoodgridResult
*/
  public GnMoodgridResult FindRecommendations(GnMoodgridProvider provider, GnMoodgridDataPoint position) {
    GnMoodgridResult ret = new GnMoodgridResult(gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_FindRecommendations(swigCPtr, GnMoodgridProvider.getCPtr(provider), GnMoodgridDataPoint.getCPtr(position)), true);
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Generates a recommendations estimate for a given mood data point and provider. The estimate is dependent on the 
* provider. Use this functionality for creating a heat map of all the moods supported in the presentation.
* @param provider [in] :moodgrid provider that the estimate must come from.
* @param position [in] : data point that represents the mood for which the estimate is requested.
* @return count representing the estimate.
*/
  public uint FindRecommendationsEstimate(GnMoodgridProvider provider, GnMoodgridDataPoint position) {
    uint ret = gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_FindRecommendationsEstimate(swigCPtr, GnMoodgridProvider.getCPtr(provider), GnMoodgridDataPoint.getCPtr(position));
    if (gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Pending) throw gnsdk_csharp_marshalPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

/**
* Retrieves the presentation type the defines the no. of moods available in this presentation..
* @return moods
*/
  public GnMoodgridPresentationType LayoutType {
    get {
      GnMoodgridPresentationType ret = (GnMoodgridPresentationType)gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_LayoutType_get(swigCPtr);
      return ret;
    } 
  }

  public GnMoodgridPresentationDataEnumerable Moods {
    get {
      IntPtr cPtr = gnsdk_csharp_marshalPINVOKE.GnMoodgridPresentation_Moods_get(swigCPtr);
      GnMoodgridPresentationDataEnumerable ret = (cPtr == IntPtr.Zero) ? null : new GnMoodgridPresentationDataEnumerable(cPtr, true);
      return ret;
    } 
  }

}

}
