# Copyright (c) 2000-present Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.

"""
  Name: musicid_image_fetch
  Description:
  This example does a text search and finds images based on gdo type (album or contributor).
  It also finds an image based on genre.

Command line syntax:
> python main.py <client_id> <client_id_tag> <license_filename>

"""

import os
import sys
sys.path.append("..")

# gnsdk_utilities finds gnsdk and sets up sys.path. Import first.
import gnsdk_utilities
import gnsdk

application_version = "1.0.0.0"

def get_build_info(name, gnsdk_lib):
    return name+ \
        " Version    : " + gnsdk_lib.version() + \
        "  (built " + gnsdk_lib.build_date() + ")"

class GNSDK_Manager:

    def __init__(self, client_id, client_id_tag, license_path):
        try:
            self.__manager = gnsdk.GnManager(
                gnsdk_utilities.lib_path,
                license_path,
                gnsdk.kLicenseInputModeFilename
            )
        except gnsdk.GnError as e:
            print "Error creating GnSDK instance: %s" % e.error_description()
            exit(1)

        if configuration.enable_logging:
            sample_log = gnsdk.GnLog("sample.log", None)
            sample_log.filters(gnsdk.GnLogFilters().error())
            sample_log.filters(gnsdk.GnLogFilters().warning())
            sample_log.columns(gnsdk.GnLogColumns().all())
            sample_log.options(gnsdk.GnLogOptions().max_size(0))
            sample_log.options(gnsdk.GnLogOptions().archive(False))
            sample_log.enable(gnsdk.kLogPackageAll)

        try:
            self.__storage = gnsdk.GnStorageSqlite.enable()
        except gnsdk.GnError as e:
            print "Error creating GnStorageSqlite instance: %s" % e.error_description()
            exit(1)

        if configuration.use_local:
            self.__storage.storage_location(configuration.storage_path)
            try:
                self.lookup_local = gnsdk.GnLookupLocal.enable()
            except gnsdk.GnError as e:
                print "Error creating GnLookupLocal instance: %s" % e.error_description()
                exit(1)

        self.display_build_info()

        # Get the user, registering if necessary.
        self.user = self.get_user(client_id, client_id_tag, application_version)

        # Set the locale.
        try:
            locale = gnsdk.GnLocale(
                                    gnsdk.kLocaleGroupMusic,
                                    gnsdk.kLanguageEnglish,
                                    gnsdk.kRegionDefault,
                                    gnsdk.kDescriptorSimplified,
                                    self.user
                                    )
        except gnsdk.GnError as e:
            print "Error setting locale: %s" % e.error_description()
            exit(1)

        try:
            locale.set_group_default()
        except gnsdk.GnError as e:
            print "Error setting locale: %s" % e.error_description()
            exit(1)

    def __create_user(self, serialized_user, client_id):
        # client_id is an optional argument to ensure this user is for this client
        try:
            user = gnsdk.GnUser(serialized_user, client_id)
        except gnsdk.GnError as e:
            print "Error creating user: %s" % e.error_description()
            exit(1)

        return user

    def get_user(self, client_id, client_id_tag, application_version):
        user_filename = "user.txt"

        try:
            user_file = open(user_filename, "r")
        except:
            print "\nInfo: No stored user - this must be the app's first run."
            user_reg_mode = gnsdk.kUserRegisterModeOnline
            if (configuration.use_local):
                user_reg_mode = gnsdk.kUserRegisterModeLocalOnly
            try:
                serialized_user = self.__manager.user_register(
                                                               user_reg_mode,
                                                               client_id,
                                                               client_id_tag,
                                                               application_version
                                                               ).c_str()
            except gnsdk.GnError as e:
                print "Error creating user: %s" % e.error_description()
                exit(1)
            else:
                user = self.__create_user(serialized_user, client_id)
                open(user_filename, "w").write(serialized_user)
        else:
            serialized_user = user_file.read()
            user = self.__create_user(serialized_user, client_id)
            # Recursive call to re-register if user is local and we are online now.
            # You would probably want to save the state here and check at time of doing an online lookup.
            if not configuration.use_local:
                if user.is_local_only():
                    user_file.close()
                    os.remove(user_filename)
                    user = self.get_user(client_id, client_id_tag, application_version)

        if (configuration.use_local):
            user.options().lookup_mode(gnsdk.kLookupModeLocal)

        return user

    def display_build_info(self):
        # Print all of the version information.
        print get_build_info("\nGNSDK Product", self.__manager)
        if configuration.use_local:
            print "gdb version: %s" % self.get_gdb_version()

    def get_gdb_version(self):
        try:
            record_count = self.lookup_local.storage_info_count(gnsdk.kLocalStorageMetadata,
                                                                gnsdk.kLocalStorageInfoVersion)
        except gnsdk.GnError as e:
            print "Error getting storage info: %s" % e.error_description()
            exit(1)

        for i in xrange(record_count):
            version = self.lookup_local.storage_info(gnsdk.kLocalStorageMetadata,
                                                     gnsdk.kLocalStorageInfoVersion,
                                                     i+1
                                                     )
        return version

if __name__ == "__main__":
    def usage(program):
        print "USAGE!!:\n\t%s <client_id> <client_id_tag> <license_path>\n" % program
        exit(1)
    
    if len(sys.argv) != 4:
        usage(sys.argv[0])
    
    # configuration instance
    configuration = gnsdk_utilities.GNSDK_Configuration()
    
    # Create the manager
    manager = GNSDK_Manager(sys.argv[1], sys.argv[2], sys.argv[3])

    print "\n*****MusicID Text Match Query & image fetch*****"

    my_list = gnsdk.GnList(gnsdk.kListTypeGenres,
                           gnsdk.kLanguageEnglish,
                           gnsdk.kRegionDefault,
                           gnsdk.kDescriptorSimplified,
                           manager.user
                           )

    def display_matches(matches):
        for match_idx, match in enumerate(matches):
            if match.is_album():
                album = match.get_as_album()
                print "      %2d: album match (%10s): Title: %s" % (match_idx+1,
                                                                    album.tui(),
                                                                    album.title().display()
                                                                    )
            elif match.is_contributor():
                contributor = match.get_as_contributor()
                print "      %2d: artist match: Name: %s" % (match_idx+1,
                                                             contributor.name().display()
                                                             )
            else:
                print "      %2d: unknown match type" % match_idx+1

    def do_match_selection(matches):
        display_matches(matches)
        # Here you could prompt the user to choose a match. We take the first.
        # The first match is the one that would be returned with option "result_single".
        return 1

    def display_contributor(contributor):
        print "      Artist Name: %s" % contributor.name().display()

    def display_track(track):
        print "      Matched Track: Ordinal %s, Title: %s" % (track.track_number(),
                                                              track.title().display())
        display_contributor(track.artist())

    def display_album(album):
        print "      Album Title: %s" % album.title().display()
        display_contributor(album.artist())
        for track in album.tracks_matched():
            display_track(track)

    def display_result(match):
        if match.is_album():
            display_album(match.get_as_album())
        elif match.is_contributor():
            display_contributor(match.get_as_contributor())

    def do_sample_text_query(album_title, album_artist, genre, user):
        print "  album-%s, artist-%s, genre-%s" % (album_title, album_artist, genre)

        # Create a music_id instance. Set result_single
        music_id = gnsdk.GnMusicId(manager.user)
        music_id.options().result_single(True)
        #print type(gnsdk.kLookupDataContent)
        #music_id.options().custom(gnsdk.kLookupDataContent, True)
        response = music_id.find_matches(album_title, None, album_artist, None, None)
        if type(response) is gnsdk.GnResponseDataMatches:
            if response.result_count() == 0:
                print "    No matches found for this input."
            else:
                matches = response.data_matches()
                # Note, response.result_count() and len(response.data_matches()) should be the same.
                print "    Match count: %d" % len(matches)
                if response.needs_decision() or len(matches) > 1:
                    choice_ordinal = do_match_selection(matches)
                    print "    Chose match %d. Displaying result" % choice_ordinal
                else:
                    choice_ordinal = 1
                    display_result(matches[choice_ordinal - 1])
        else:
            print "Error: invalid response type: %s" % type(response)

    mp3_folder = [["Ask Me No Questions", "Low Commotion Blues Band", "Rock"],
                  ["Supernatural",        "Santana",                  None],
                  [None,                  "Phillip Glass",            None]
                  ]

    for track in mp3_folder:
        do_sample_text_query(track[0], track[1], track[2], manager.user)



    '''
    def find_genre_image(self, user, genre, ilist):
        
        print "Genre String Search\n"
        
        if genre is None:
            print "Must pass a genre\n"
            return -1
        
        print "Genre : " , genre
        
        list_element = ilist.element_by_string(genre)
        print "List element result: " , list_element.display_string(), "level : " , list_element.level()
        link = gnsdk.GnLink(user,list_element)
        
        got_match = 1
        
        MusicIdImageFetch_EventDelegate.fetch_image(link, gnsdk.gnsdk_link_content_genre_art , "genre image")
        
        return got_match

    def perform_image_fetch(self, data_match, user):
        
        link = gnsdk.GnLink(user, data_match)
        
        # Perform the image fetch 
        if(data_match.is_album()):
            
            # If album type get cover art
            if(MusicIdImageFetch_EventDelegate.fetch_image(link, gnsdk.gnsdk_link_content_cover_art , "cover art")):
               
                # if no cover art, try to get the album's artist image
                if(MusicIdImageFetch_EventDelegate.fetch_image(link, gnsdk.gnsdk_link_content_image_artist, "artist image")):
                    
                    # if no artist image, try to get the album's genre image so we have something to display
                    MusicIdImageFetch_EventDelegate.fetch_image(link, gnsdk.gnsdk_link_content_genre_art, "genre image")
                    
        elif (data_match.is_contributor()):
            
            # If contributor type get artist image
            if(MusicIdImageFetch_EventDelegate.fetch_image(link, gnsdk.gnsdk_link_content_image_artist, "artist type")):
                
                # if no artist image, try to get the album's genre image so we have something to display
                MusicIdImageFetch_EventDelegate.fetch_image(link, gnsdk.gnsdk_link_content_genre_art, "genre image")
                
        else:
            print "Unknown gdo Type, must be ALBUM or CONTRIBUTOR\n"


    def do_sample_text_query(self, album_title_tag, artist_name_tag, user):
        
        got_match = 0
        print "MusicID Text Match Query"
        
        if((album_title_tag is None) and (artist_name_tag is None)):
            
            print "Must pass album title or artist name"
            
        if (album_title_tag is None):
            album_title_tag = ""
            
        else:
            print "album title    : " , album_title_tag 
         
        if (artist_name_tag is None):
            artist_name_tag = ""
        else:
            print "artist name    : " , artist_name_tag
            
        musicID = gnsdk.GnMusicId(user)
        
        musicID.option_lookup_data(gnsdk.kLookupDataContent, True)
        
        response = musicID.find_matches(album_title_tag, None, artist_name_tag)
        
        count = len(response.data_matches())
        
        print "Number matches : " , count
        
        #Get the first match type
        
        if(count > 0):
            #OK, we got at least one match.
            got_match = 1
            
            data_match = response.data_matches.at(0).next()
            data_match = gnsdk.GnDataMatch()
            
            print "\nFirst Match GDO type: " , data_match.get_type()
            
            #Get the best image for the match
            MusicIdImageFetch_EventDelegate.perform_image_fetch(self, data_match, user)
            
            
        return got_match
    
    def process_sample_MP3(self, mp3_tags, user, ilist):
        
        #Do a music text query and fetch image from result.
        got_match =0
        
        got_match = MusicIdImageFetch_EventDelegate.do_sample_text_query(self, mp3_tags[0], mp3_tags[1], user)
            
        #If there were no results from the musicid query for this file, try looking up the genre tag to get the genre image.
        if(got_match == 0):
            if (mp3_tags[2] is not None):
                got_match = MusicIdImageFetch_EventDelegate.find_genre_image(self, user, mp3_tags[2], ilist)
                
            
        # Did we successfully find a relevant image?
        if(got_match == 0):
            print "Because there was no match result for any of the input tags, you may want to associate the generic music image \
                   with this track, music_75x75.jpg, music_170x170.jpg or music_300x300.jpg\n"
    '''
