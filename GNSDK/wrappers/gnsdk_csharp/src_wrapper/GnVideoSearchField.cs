
namespace GracenoteSDK {

/**
*  The type of text search field that is used to find results.
*/
public enum GnVideoSearchField {
/**
*  Contributor name search field.
*/
  kSearchFieldContributorName = 1,
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
*
*  Product title search field.
*/
  kSearchFieldProductTitle,
/**
*
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
  kSearchFieldAll
}

}
