# Copyright (c) 2000-present Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.

"""
Name: playlist
Description:
  Playlist is the GNSDK library that generates playlists when integrated with the
  MusicID or MusicID-File library (or both). Playlist APIs enable an application to:
    01. Create, administer, populate, and synchronize a collection summary.
    02. Store a collection summary within a local storage solution.
    03. Validate PDL statements.
    04. Generate Playlists using either the More Like This function or the general
        playlist generation function.
    05. Manage results.
  Streamline your Playlist implementation by using the provided More Like This
  function, gnsdk_playlist_generate_morelikethis, which generates optimal playlists
  and eliminates the need to create and validate Playlist Definition Language
  statements.

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
                                    gnsdk.kLocaleGroupPlaylist,
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

    print "\n*****Playlist Collection creation and Playlist Generation*****\n"

    def populate_playlist_collection(playlist_collection):
        input_query_tocs = [
            "150 13224 54343 71791 91348 103567 116709 132142 141174 157219 175674 197098 238987 257905",
            "182 23637 47507 63692 79615 98742 117937 133712 151660 170112 189281",
            "182 14035 25710 40955 55975 71650 85445 99680 115902 129747 144332 156122 170507",
            "150 10705 19417 30005 40877 50745 62252 72627 84955 99245 109657 119062 131692 141827 152207 164085 173597 187090 204152 219687 229957 261790 276195 289657 303247 322635 339947 356272",
            "150 14112 25007 41402 54705 69572 87335 98945 112902 131902 144055 157985 176900 189260 203342",
            "150 1307 15551 31744 45022 57486 72947 85253 100214 115073 128384 141948 152951 167014",
            "183 69633 96258 149208 174783 213408 317508",
            "150 19831 36808 56383 70533 87138 105157 121415 135112 151619 169903 189073",
            "182 10970 29265 38470 59517 74487 83422 100987 113777 137640 150052 162445 173390 196295 221582",
            "150 52977 87922 128260 167245 187902 215777 248265",
            "183 40758 66708 69893 75408 78598 82983 87633 91608 98690 103233 108950 111640 117633 124343 126883 132298 138783 144708 152358 175233 189408 201408 214758 239808",
            "150 92100 135622 183410 251160 293700 334140",
            "150 17710 33797 65680 86977 116362 150932 166355 183640 193035",
            "150 26235 51960 73111 93906 115911 142086 161361 185586 205986 227820 249300 277275 333000",
            "150 1032 27551 53742 75281 96399 118691 145295 165029 189661 210477 232501 254342 282525",
            "150 26650 52737 74200 95325 117675 144287 163975 188650 209350 231300 253137 281525 337875",
            "150 19335 35855 59943 78183 96553 111115 125647 145635 163062 188810 214233 223010 241800 271197",
            "150 17942 32115 47037 63500 79055 96837 117772 131940 148382 163417 181167 201745",
            "150 17820 29895 41775 52915 69407 93767 105292 137857 161617 171547 182482 204637 239630 250692 282942 299695 311092 319080",
            "182 21995 45882 53607 71945 80495 94445 119270 141845 166445 174432 187295 210395 230270 240057 255770 277745 305382 318020 335795 356120",
            "187 34360 64007 81050 122800 157925 195707 230030 255537 279212 291562 301852 310601",
            "150 72403 124298 165585 226668 260273 291185"
        ]

        # Create a musicID instance to lookup the TOCs
        music_id = gnsdk.GnMusicId(manager.user)
        music_id.options().result_single(True)
        music_id.options().lookup_data(gnsdk.kLookupDataSonicData, True)
        music_id.options().lookup_data(gnsdk.kLookupDataPlaylist, True)

        print "Creating a new collection"
        for toc_idx, toc in enumerate(input_query_tocs):
            response = music_id.find_albums(toc)
            for album in response.albums():
                for trk_idx, track in enumerate(album.tracks()):
                    playlist_collection.add("%d_%d"%(toc_idx, trk_idx), album)
                    playlist_collection.add("%d_%d"%(toc_idx, trk_idx), track)

        print "Finished populating collection summary"

    def get_existing_collection(playlist_storage, collection_summary_name):
        collection_count = playlist_storage.names().count()
        if collection_count:
            print "Currently stored collections: %d" % collection_count
            try:
                playlist_collection = playlist_storage.load(collection_summary_name)
            except gnsdk.GnError as e:
                print "Error %s loading collection %s" % (e.error_description(), collection_summary_name)
            else:
                print "Loaded Collection '%s' from storage" % collection_summary_name
                return playlist_collection

        return None

    def get_seed(playlist_collection):
        ident = playlist_collection.media_identifiers()[4]
        return playlist_collection.attributes(manager.user, ident)

    def enumerate_playlist_result(result):
        print "    Generated playlist: %d tracks" % len(result.identifiers())
        for identifier in result.identifiers():
            data = playlist_collection.attributes(manager.user, identifier)
            print "      %s : %s: %s, %s, %s, %s, %s, %s, %s, %s" % (
                identifier.collection_name(),
                identifier.media_identifier(),
                data.album_name(),
                data.artist_name(),
                data.artist_type(),
                data.era(),
                data.genre(),
                data.origin(),
                data.mood(),
                data.tempo()
            )

    def do_playlist_pdl(playlist_collection):
        print "\nGenerating PDL playlists"
        pdl_statements = [
            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 0",
            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2929) > 300",
            "GENERATE PLAYLIST WHERE GN_Genre = 2929",
            "GENERATE PLAYLIST WHERE GN_Genre = 2821",
            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 0",
            "GENERATE PLAYLIST WHERE (GN_Genre LIKE 2821) > 300",
            "GENERATE PLAYLIST WHERE (GN_Genre LIKE SEED) > 300 LIMIT 20 RESULTS",
            "GENERATE PLAYLIST WHERE (GN_ArtistName LIKE 'Green Day') > 300 LIMIT 20 RESULTS, 2 PER GN_ArtistName;"
        ]
        for idx, pdl_statement in enumerate(pdl_statements):
            print "\n  PDL statement %d: %s" % (idx, pdl_statement)
            seed = get_seed(playlist_collection)
            playlist_result = playlist_collection.generate_playlist(
                manager.user,
                pdl_statement,
                seed
            )
            enumerate_playlist_result(playlist_result)

    def set_mlt_options(mlt_options):
        for mlt_option in mlt_options:
            mlt_option[1](mlt_option[2])

    def display_mlt_options(mlt_options):
        for mlt_option in mlt_options:
            print "   %s = %s" % (mlt_option[0], mlt_option[1]())

    def gen_mlt(playlist_collection, seed):
        playlist_result = playlist_collection.generate_more_like_this(manager.user, seed)
        enumerate_playlist_result(playlist_result)
        
    def do_playlist_mlt(playlist_collection):

        seed = get_seed(playlist_collection)
        print "\nGenerating MoreLikeThis playlist"

        print "\n  MoreLikeThis with Default Options"
        gen_mlt(playlist_collection, seed)

        print "\n  MoreLikeThis with Custom Options"
        options = playlist_collection.more_like_this_options()
        mlt_options = [("max tracks",     options.max_tracks,     30),
                       ("max per artist", options.max_per_artist, 10),
                       ("max per album",  options.max_per_album,   5)
                       ]
        set_mlt_options(mlt_options)
        display_mlt_options(mlt_options)

        gen_mlt(playlist_collection, seed)

    # Create the playlist collection.
    collection_summary_name = "sample_collection"

    playlist_storage = gnsdk.GnPlaylistStorage()
    playlist_storage.location(os.getcwd())

    # Get the collection summary, create if necessary
    playlist_collection = get_existing_collection(playlist_storage, collection_summary_name)
    if not playlist_collection:
        playlist_collection = gnsdk.GnPlaylistCollection(collection_summary_name)
        populate_playlist_collection(playlist_collection)
        playlist_storage.store(playlist_collection)

    # Do a PDL based playlist
    do_playlist_pdl(playlist_collection)

    # Do a MLT playlist
    do_playlist_mlt(playlist_collection)
