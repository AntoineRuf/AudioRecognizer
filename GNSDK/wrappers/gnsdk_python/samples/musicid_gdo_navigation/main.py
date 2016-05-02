# Copyright (c) 2000-present Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.

"""
   Name: musicid_gdo_navigation
   Description:
   This application uses MusicID to look up Album GDO content,    
   including Album artist, credits, title, year, and genre.
   It demonstrates how to navigate the album GDO that returns basic
   track information, including artist, credits, title, track number,
   and genre.
   Notes:
   For clarity  and  simplicity error handling in not shown here.
   Refer "logging" sample to learn about GNSDK error handling.

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

def display_contributors(gn_contributor, tab):
    for name in gn_contributor.names_official():
        print tab,"Credit:"
        print tab,"\tContributor:"
        print tab,"\t\tName Official:"
        print tab,"\t\t\tDisplay:" , name.display()

    if gn_contributor.origin(gnsdk.kDataLevel_1):
        print tab,"\t\tOrigin Level 1:" , gn_contributor.origin(gnsdk.kDataLevel_1)
    if gn_contributor.origin(gnsdk.kDataLevel_2):
        print tab,"\t\tOrigin Level 2:" , gn_contributor.origin(gnsdk.kDataLevel_2)
    if gn_contributor.origin(gnsdk.kDataLevel_3):
        print tab,"\t\tOrigin Level 3:" , gn_contributor.origin(gnsdk.kDataLevel_3)
    if gn_contributor.origin(gnsdk.kDataLevel_4):
        print tab,"\t\tOrigin Level 4:" , gn_contributor.origin(gnsdk.kDataLevel_4)

    if gn_contributor.era(gnsdk.kDataLevel_1):
        print tab,"\t\tEra Level 1:" , gn_contributor.era(gnsdk.kDataLevel_1)
    if gn_contributor.era(gnsdk.kDataLevel_2):
        print tab,"\t\tEra Level 2:" , gn_contributor.era(gnsdk.kDataLevel_2)
    if gn_contributor.era(gnsdk.kDataLevel_3):
        print tab,"\t\tEra Level 3:" , gn_contributor.era(gnsdk.kDataLevel_3)

    if gn_contributor.artist_type(gnsdk.kDataLevel_1):
        print tab,"\t\tArtist Type Level 1:" , gn_contributor.artist_type(gnsdk.kDataLevel_1)
    if gn_contributor.artist_type(gnsdk.kDataLevel_2):
        print tab,"\t\tArtist Type Level 2:" , gn_contributor.artist_type(gnsdk.kDataLevel_2)

def display_track(track):
    print "\tTrack:"
    print "\t\tTrack TUI:" , track.tui()
    print "\t\tTrack Number:", track.track_number()

    contributor = track.artist().contributor()
    if contributor:
        display_contributors(contributor, "\t\t")

    title = track.title()
    print "\t\tTitle Official:"
    print "\t\t\tDisplay:" , title.display()
    if title.sortable():
        print "\t\t\tSortable2 : " , title.sortable()

    if track.genre(gnsdk.kDataLevel_1):
        print "\t\tGenre Level 1:", track.genre(gnsdk.kDataLevel_1)
    if track.genre(gnsdk.kDataLevel_2):
        print "\t\tGenre Level 2:", track.genre(gnsdk.kDataLevel_2)
    if track.genre(gnsdk.kDataLevel_3):
        print "\t\tGenre Level 3:", track.genre(gnsdk.kDataLevel_3)

    if track.year():
        print"\t\tYear:" , track.year()

def display_result(gn_result):
    print "Match.\n"
    print "***Navigating Result GDO***"

    for album in gn_result.albums():
        print "Album:"
        print "\tPackage Language:", album.language()
        contributor = album.artist().contributor()
        if contributor:
            display_contributors(contributor, "\t")

        title = album.title()
        print "\tTitle Official:"
        print "\t\tDisplay:" , title.display()
        if title.sortable():
            print "\t\tSortable2 : " , title.sortable()

        if album.year():
            print "\tYear:" , album.year()

        if album.genre(gnsdk.kDataLevel_1):
            print "\tGenre Level 1:", album.genre(gnsdk.kDataLevel_1)
        if album.genre(gnsdk.kDataLevel_2):
            print "\tGenre Level 2:", album.genre(gnsdk.kDataLevel_2)
        if album.genre(gnsdk.kDataLevel_3):
            print "\tGenre Level 3:", album.genre(gnsdk.kDataLevel_3)

        if album.label():
            print "\tAlbum Label: " + album.label()

        if album.total_in_set():
            print "\tTotal In Set:" , album.total_in_set()
        if album.disc_in_set():
            print "\tDisc In Set:" , album.disc_in_set()

        print "\tTrack Count:" , album.track_count()
        for track in album.tracks():
            display_track(track)

        print ""    

def music_id_lookup_album(input_tui_id, input_tui_tag, user):
    print "*****Sample MusicID Query*****"
    music_id = gnsdk.GnMusicId(user)
    gn_id = gnsdk.GnAlbum(input_tui_id, input_tui_tag)
    gn_result = music_id.find_albums(gn_id)
    display_result(gn_result)

def do_sample_tui_lookups(user):
    # Lookup album: Nelly - Nellyville to demostrate collaborative artist navigation in track level (track #12)
    input_tui_id = "30716057"
    input_tui_tag = "BB402408B507485074CC8B3C6D313616";
    music_id_lookup_album(input_tui_id, input_tui_tag, user)

    # Lookup album: Dido - Life for Rent 
    input_tui_id = "46508189";
    input_tui_tag = "951407B37F9D8EAE68F74B0B5C5E1224";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);

    # Lookup album: Jean-Pierre Rampal - Portrait Of Rampal
    input_tui_id = "3020551";
    input_tui_tag = "CAA37D27FD12337073B54F8E597A11D3";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);

    # Lookup album: Various Artists - Grieg: Piano Concerto, Peer Gynth Suites #1
    input_tui_id = "2971440";
    input_tui_tag = "7F6C280498E077330B1732086C3AAD8F";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);

    # Lookup album: Stephen Kovacevich - Brahms: Rhapsodies, Waltzes & Piano Pieces
    input_tui_id = "2972852";
    input_tui_tag = "EC246BB5B359D88BEBDC1EF55873311E";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);    

    # Lookup album: Nirvana - Nevermind
    input_tui_id = "2897699";
    input_tui_tag = "2FAE8F59CCECBA288810EC27DCD56A0A";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);

    # Lookup album: Eminem - Encore
    input_tui_id = "68056434";
    input_tui_tag = "C6E3634DF05EF343E3D22CE3A28A901A";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);

    # Lookup Japanese album: NOTE: In order to correctly see the Japanese
    # metadata results for this lookup, this program will need to write out
    # to UTF-8
    input_tui_id = "16391605";
    input_tui_tag = "F272BD764FDEB344A54F53D0756DC3FD";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);

    #Lookup Chinese album: NOTE: In order to correctly see the Chinese
    #metadata results for this lookup, this program will need to write out
    #to UTF-8
    input_tui_id = "3798282";
    input_tui_tag = "6BF6849840A77C987E8D3AF675129F33";
    music_id_lookup_album(input_tui_id, input_tui_tag, user);

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

    do_sample_tui_lookups(manager.user)
