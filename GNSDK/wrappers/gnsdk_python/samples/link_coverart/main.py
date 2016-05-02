# Copyright (c) 2000-present Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.

"""
Name: link_coverart
Description:
  Fetches a cover art and an artist image using a serialized GDO as input.
  Supports local and online lookup modes.
  A common use case would get the GDO from a query. See 'lookup' samples for that.
  For a more thourough example of performing an image fetch after a media
  recognition, including fallback from cover art to artist image to genre image,
  refer to the sample musicid_image_fetch.

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

    print "\n*****Sample Link Album Query*****\n"

    image_sizes = {
        "gnsdk_content_sz_75":gnsdk.kImageSize75,
        "gnsdk_content_sz_170":gnsdk.kImageSize170,
        "gnsdk_content_sz_300":gnsdk.kImageSize300,
        "gnsdk_content_sz_450":gnsdk.kImageSize450,
        "gnsdk_content_sz_720":gnsdk.kImageSize720,
        "gnsdk_content_sz_1080":gnsdk.kImageSize1080,
        "gnsdk_content_sz_110":gnsdk.kImageSize110,
        "gnsdk_content_sz_220":gnsdk.kImageSize220
    }

    # Select the size of fetched images.
    # In local mode, we need to take a size that is in our local database. If the
    # preferred size is there, we use that, otherwise, we arbitrarily take the last
    # size listed in the database header.
    def get_image_size():
        preferred_image_size = "gnsdk_content_sz_170"
        if configuration.use_local:
            try:
                size_count = manager.lookup_local.storage_info_count(gnsdk.kLocalStorageContent,
                                                                     gnsdk.kLocalStorageInfoImageSize)
            except gnsdk.GnError as e:
                print "Error getting storage info: %s" % e.error_description()
                exit(1)

            for i in xrange(size_count):
                size = manager.lookup_local.storage_info(
                    gnsdk.kLocalStorageContent,
                    gnsdk.kLocalStorageInfoImageSize,
                    i+1
                )
                if size == preferred_image_size:
                    break
            preferred_image_size = size

        return image_sizes[preferred_image_size]

    def fetch_image(query_method, size, image_type):
        try:
            content_obj = query_method(size, gnsdk.exact)
        except gnsdk.GnError as e:
            print "Error fetching image: " + e.ErrorDescription()
            exit(1)
        else:
            if content_obj.data_type() == gnsdk.kLinkDataImageJpeg:
                image_bfr_wrap = gnsdk.byte_buffer(content_obj.data_size())
                content_obj.data_buffer(image_bfr_wrap)
                image_bfr = gnsdk.cdata(image_bfr_wrap,content_obj.data_size())
                image_hash = str(abs(hash(image_bfr)))
                image_filename = image_hash + ".jpg"
                jpg = open(image_filename, "w")
                jpg.write(image_bfr)
                jpg.close()
                if content_obj.data_size()  > 0:
                    print '\nRETRIEVED: ',image_type,' image: ' ,content_obj.data_size() , ' byte JPEG'
                else:
                    print '\n NOT FOUND:',image_type,' image' 
    # Get the size of images to fetch. Local db will have restricted choices.
    image_size = get_image_size()

    # Set the input GDO.
    serialized_gdo = "WEcxAbwX1+DYDXSI3nZZ/L9ntBr8EhRjYAYzNEwlFNYCWkbGGLvyitwgmBccgJtgIM/dkcbDgrOqBMIQJZMmvysjCkx10ppXc68ZcgU0SgLelyjfo1Tt7Ix/cn32BvcbeuPkAk0WwwReVdcSLuO8cYxAGcGQrEE+4s2H75HwxFG28r/yb2QX71pR";

    try:
        gdo = gnsdk.GnDataObject_deserialize(serialized_gdo)
    except gnsdk.GnError as e:
        print "Error creating GDO: " + e.ErrorDescription()
        exit(1)

    link = gnsdk.GnLink(gdo, manager.user)

    fetch_image(link.cover_art, image_size, 'cover art')
    fetch_image(link.artist_image, image_size, 'artist')
