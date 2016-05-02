# coding=utf-8
# Note: The 'coding' comment is to handle non-Latin-1 text in queries.
#       It must be on the first or second line.

# Copyright (c) 2000-present Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.

"""
Name: musicid_lookup_matches_text
Description:
Recognizes media based on its Text inputs, e.g. from ID3 tags.
Displays some metadata for the matched items.
Supports local and online lookup modes.

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

    print "\n*****MusicID Text Match Query*****"

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

    def do_sample_text_query(album_title, track_title, album_artist, track_artist, composer, user):
        print "  album-%s, track-%s, album artist-%s, track artist-%s, composer-%s" % (
            album_title,
            track_title,
            album_artist,
            track_artist,
            composer
        )

        music_id = gnsdk.GnMusicId(manager.user)
        # Set options here, e.g. to request the single best result uncomment the next line
        # music_id.result_single(True)

        response = music_id.find_matches(album_title,
                                         track_title,
                                         album_artist,
                                         track_artist,
                                         composer
                                         )
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

    # Note: Need the coding comment at the top of the file to handle utf-8 characters below.
    print "\nAlbum + Track match:"
    do_sample_text_query("Supernatural", "Africa Bamba", "Santana", None, None, manager.user)
    print "\nAlbum + Track match with track artist != album artist:"
    do_sample_text_query("Supernatural", "The Calling", "Santana", None, None, manager.user)
    print "\nAlbum match:"
    do_sample_text_query("Supernatural", None, "Santana", None, None, manager.user)
    print "\nAlbum match with non-Latin-1 characters:"
    do_sample_text_query("看我72变", None, None, None, None, manager.user)
    print "\nArtist match:"
    do_sample_text_query(None, None, "Philip Glass", None, None, manager.user);
    print "\nArtist match:"
    do_sample_text_query(None, None, "Bob Marley", None, None, manager.user);
    print "\nAlbum + Track match with no album title input:"
    do_sample_text_query(None, "Purple Stain", "Red Hot Chili Peppers", None, None, manager.user);
    print "\nAlbum + Track match with no album title input:"
    do_sample_text_query(None, "Eyeless", "Slipknot", None, None, manager.user);
