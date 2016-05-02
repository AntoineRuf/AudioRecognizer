
namespace GracenoteSDK {

/**
* Metadata level enums
* Level of granularity of the metadata
* Eg: Genre 'Rock' (level 1) is less granular than 'Soft Rock' (level 2)
* Not all 4 levels are supported for all applicable metadata.
*/
public enum GnDataLevel {

  kDataLevelInvalid = 0,

  kDataLevel_1 = 1,

  kDataLevel_2,

  kDataLevel_3,

  kDataLevel_4
}

}
