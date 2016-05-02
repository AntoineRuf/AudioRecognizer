
package com.gracenote.gnsdk;

/** 
* List types. GNSDK uses lists to provide media metadata via response objects. Response metadata depending 
* on lists is known as list-based metadata. Lists are localized meaning, where applicable, the data they 
* contain is specific to a region and/or translated into languages supported by Gracenote. 
* Where a list is not available in the requested language the default language, English, is returned. 
*/ 
 
public enum GnListType {
/** 
* This list contains languages that are supported by Gracenote, and are typically used to indicate 
* the original language of an item. 
*/ 
 
  kListTypeInvalid(0),
/** 
* This list contains scripts that are supported by Gracenote 
*/ 
 
  kListTypeLanguages,
/** 
* The list of supported music genres. 
* <p><b>Remarks:</b></p> 
* The genre list contains a hierarchy of genres available from Gracenote strictly for music data. 
*/ 
 
  kListTypeScripts,
/** 
* The list of supported geographic origins for artists. 
*/ 
 
  kListTypeGenres,
/** 
* The list of supported music era categories. 
*/ 
 
  kListTypeOrigins,
/** 
* The list of supported artist type categories. 
*/ 
 
  kListTypeEras,
/** 
* This list contains role list elements supported Gracenote for album data, such as Vocalist and Bass Guitar. 
*/ 
 
  kListTypeArtistTypes,
/** 
*  This list contains a hierarchy of genre list elements available from Gracenote, strictly for 
* video data. 
*/ 
 
  kListTypeRoles,
/** 
* This list contains movie rating list elements supported by Gracenote. 
*/ 
 
  kListTypeGenreVideos,
/** 
* This list contains film content rating list elements supported by Gracenote. 
*/ 
 
  kListTypeRatings,
/** 
* This list contains contributor role list elements available from Gracenote, such as Actor or 
* Costume Design. These apply to video data. 
*/ 
 
  kListTypeRatingTypes,
/** 
* The list of supported feature types for video data. 
*/ 
 
  kListTypeContributors,
/** 
*  The list of supported video regions. 
*/ 
 
  kListTypeFeatureTypes,
/** 
* The list of supported video types, such as Documentary, Sporting Event, or Motion Picture. 
*/ 
 
  kListTypeVideoRegions,
/** 
* The list of supported media types for music and video, such as Audio CD, Blu-ray, DVD, or HD DVD. 
*/ 
 
  kListTypeVideoTypes,
/** 
* The list of supported video serial types, such as Series or Episode. 
*/ 
 
  kListTypeMediaTypes,
/** 
* The list of supported work types for video data, such as Musical or Image. 
*/ 
 
  kListTypeVideoSerialTypes,
/** 
* The list of supported media spaces for video data, such as Music, Film, or Stage. 
*/ 
 
  kListTypeWorkTypes,
/** 
* The list of supported moods for music data. Moods are categorized into levels, from more general 
* (Level 1, such as Blue) to more specific (Level 2, such as Gritty/Earthy/Soulful). 
*/ 
 
  kListTypeMediaSpaces,
/** 
* The list of supported tempos for music data, has three levels of granularity. 
* The tempos are categorized in levels in increasing order of granularity. 
* Level 1: The meta level, such as Fast Tempo. 
* Level 2: The sub tempo level, such as Very Fast. 
* Level 3: The micro level, which may be displayed as a numeric tempo range, such as 240-249, or a 
* descriptive phrase. 
*/ 
 
  kListTypeMoods,
/** 
* The list of supported composition forms for classical music. 
*/ 
 
  kListTypeTempos,
/** 
* The list of supported instrumentation for classical music. 
*/ 
 
  kListTypeCompostionForm,
/** 
* The list of supported overall story types for video data, such as Love Story. 
* It includes general theme classifications such as such as Love Story, Family Saga, Road Trip, 
* and Rags to Riches. 
*/ 
 
  kListTypeInstrumentation,
/** 
* The list of supported audience types for video data. 
* It includes general audience classifications by age, ethnicity, gender, and spiritual beliefs, 
* such as Kids & Family, African-American, Female, Gay & Lesbian, and Buddhist. 
*/ 
 
  kListTypeVideoStoryType,
/** 
* The list of supported moods for video data, such as Offbeat. 
* It includes general classifications such as such as Offbeat, Uplifting, Mystical, and Sarcastic. 
*/ 
 
  kListTypeVideoAudience,
/** 
* The list of supported film reputation types for video data, such as Classic. 
* It includes general classifications such as such as Classic, Chick Flick, and Cult. 
*/ 
 
  kListTypeVideoMood,
/** 
* The list of supported scenarios for video data. It 
* includes general classifications such as such as Action, Comedy, and Drama. 
*/ 
 
  kListTypeVideoReputation,
/** 
* The language of the list is determined by the language value given to 
*/ 
 
  kListTypeVideoScenario,
/** 
* The list of supported historical time settings for video data, such as Elizabethan Era, 
* 1558-1603, or Jazz Age, 1919-1929. 
*/ 
 
  kListTypeVideoSettingEnv,
/** 
* The list of supported story concept sources for video data, such as Fairy Tales & Nursery Rhymes. 
* It includes story source classifications such as Novel, Video Game, and True Story. 
*/ 
 
  kListTypeVideoSettingPeriod,
/** 
* The list of supported film style types for video data, such as Film Noir.It 
* includes general style classifications such as Art House, Film Noir, and Silent. 
*/ 
 
  kListTypeVideoSource,
/** 
* The list of supported film topics for video data, such as Racing or Teen Angst. It includes a diverse 
* range of film topics, such as Politics, Floods, Mercenaries, Surfing, and Adventure. It also includes 
* some list elements that can be considered sub-topics of a broader topic. For example, the list element Aliens (the broad topic), 
* and Nice Aliens and Bad Aliens (the more defined topics). 
*/ 
 
  kListTypeVideoStyle,
/** 
* The list of supported viewing types for EPG data, such as live and rerun. 
*/ 
 
  kListTypeVideoTopic,
/** 
* The list of supported audio types for EPG data, such as stereo and dolby. 
*/ 
 
  kListTypeEpgViewingTypes,
/** 
* The list of supported video types for EPG data, such as HDTV and PAL30. 
*/ 
 
  kListTypeEpgAudioTypes,
/** 
* The list of supported video types for EPG data, such as closed caption. 
*/ 
 
  kListTypeEpgVideoTypes,
/** 
* The list of supported categories for IPG data, such as movie and TV series. 
*/ 
 
  kListTypeEpgCaptionTypes,
/** 
* The list of supported categories for IPG data, such as action and adventure. 
*/ 
 
  kListTypeIpgCategoriesL1,
/** 
* The list of supported production types for EPG data, such as news and documentary. 
*/ 
 
  kListTypeIpgCategoriesL2,
/** 
* The list of supported device types for EPG data. 
*/ 
 
  kListTypeEpgProductionTypes,
 
 
  kListTypeEpgDeviceTypes;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnListType swigToEnum(int swigValue) {
    GnListType[] swigValues = GnListType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnListType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnListType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnListType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnListType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnListType(GnListType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

