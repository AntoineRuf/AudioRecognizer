
package com.gracenote.gnsdk;

/** 
* Languages used when specifying which locale or list to load and preferring a language for metadata returned in 
* responses. 
*/ 
 
public enum GnLanguage {
 
 
  kLanguageInvalid(0),
 
 
  kLanguageArabic,
 
 
  kLanguageBulgarian,
 
 
  kLanguageChineseSimplified,
 
 
  kLanguageChineseTraditional,
 
 
  kLanguageCroatian,
 
 
  kLanguageCzech,
 
 
  kLanguageDanish,
 
 
  kLanguageDutch,
 
 
  kLanguageEnglish,
 
 
  kLanguageFarsi,
 
 
  kLanguageFinnish,
 
 
  kLanguageFrench,
 
 
  kLanguageGerman,
 
 
  kLanguageGreek,
 
 
  kLanguageHungarian,
 
 
  kLanguageIndonesian,
 
 
  kLanguageItalian,
 
 
  kLanguageJapanese,
 
 
  kLanguageKorean,
 
 
  kLanguageNorwegian,
 
 
  kLanguagePolish,
 
 
  kLanguagePortuguese,
 
 
  kLanguageRomanian,
 
 
  kLanguageRussian,
 
 
  kLanguageSerbian,
 
 
  kLanguageSlovak,
 
 
  kLanguageSpanish,
 
 
  kLanguageSwedish,
 
 
  kLanguageThai,
 
 
  kLanguageTurkish,
 
 
  kLanguageVietnamese;

  protected final int swigValue() {
    return swigValue;
  }

  protected static GnLanguage swigToEnum(int swigValue) {
    GnLanguage[] swigValues = GnLanguage.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (GnLanguage swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + GnLanguage.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private GnLanguage() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private GnLanguage(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private GnLanguage(GnLanguage swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

