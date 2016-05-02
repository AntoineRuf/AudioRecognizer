
package com.gracenote.gnsdk;

/** 
* <b>Experimental</b>: {@link GnPlaylistAttributes} 
*/ 
 
public class GnPlaylistAttributes extends GnDataObject {
  private long swigCPtr;

  protected GnPlaylistAttributes(long cPtr, boolean cMemoryOwn) {
    super(gnsdk_javaJNI.GnPlaylistAttributes_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(GnPlaylistAttributes obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        gnsdk_javaJNI.delete_GnPlaylistAttributes(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GnPlaylistAttributes(GnPlaylistAttributes other) {
    this(gnsdk_javaJNI.new_GnPlaylistAttributes(GnPlaylistAttributes.getCPtr(other), other), true);
  }

/** 
*  Retrieves the AlbumName value as a string for this attribute . 
*  @return album name string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String albumName() {
    return gnsdk_javaJNI.GnPlaylistAttributes_albumName(swigCPtr, this);
  }

/** 
*  Retrieves the ArtistName value as a string for this attribute . 
*  @return artist name string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String artistName() {
    return gnsdk_javaJNI.GnPlaylistAttributes_artistName(swigCPtr, this);
  }

/** 
*  Retrieves the ArtistType value as a string for this attribute . 
*  @return artist type string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String artistType() {
    return gnsdk_javaJNI.GnPlaylistAttributes_artistType(swigCPtr, this);
  }

/** 
*  Retrieves the Era value as a string for this attribute . 
*  @return era string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String era() {
    return gnsdk_javaJNI.GnPlaylistAttributes_era(swigCPtr, this);
  }

/** 
*  Retrieves the Genre value as a string for this attribute . 
*  @return genre string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String genre() {
    return gnsdk_javaJNI.GnPlaylistAttributes_genre(swigCPtr, this);
  }

/** 
*  Retrieves the Origin value as a string for this attribute . 
*  @return origin string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String origin() {
    return gnsdk_javaJNI.GnPlaylistAttributes_origin(swigCPtr, this);
  }

/** 
*  Retrieves the Mood value as a string for this attribute . 
*  @return mood string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String mood() {
    return gnsdk_javaJNI.GnPlaylistAttributes_mood(swigCPtr, this);
  }

/** 
*  Retrieves the Tempo value as a string for this attribute . 
*  @return tempo string value if it exists else an empty string. 
* <p> 
**/ 
 
  public String tempo() {
    return gnsdk_javaJNI.GnPlaylistAttributes_tempo(swigCPtr, this);
  }

}
