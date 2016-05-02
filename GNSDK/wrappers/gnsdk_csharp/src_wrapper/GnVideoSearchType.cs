
namespace GracenoteSDK {

/**
*  The type of text search that is used to find results.
*/
public enum GnVideoSearchType {
/**
*   Unknown search type; the default state.
*/
  kSearchTypeUnknown = 0,
/**
*   Anchored text search, used for product title and suggestion searches.
*   Retrieves results that begin with the same characters as exactly
*   specified; for example, entering <i>dar</i>, <i>dark</i>, <i>dark k</i>,
*   or <i>dark kni</i> retrieves the title <i>Dark Knight,</i> but entering<i>
*   knight</i> will not retrieve<i> Dark Knight</i>. Note that this search
*   type recognizes both partial and full words.
*/
  kSearchTypeAnchored,
/**
*   Normal keyword filter search for contributor, product, and work title
*   searches; for example, a search using a keyword of <i>dark</i>, <i>knight</i>,
*   or <i>dark knight </i>retrieves the title <i>Dark Knight</i>. Note that
*   this search type recognizes only full words, not partial words; this
*   means that entering only <i>dar</i> for <i>dark</i> is not recognized.
*/
  kSearchTypeDefault
}

}
