# Copyright (c) 2000-present Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.

"""
Name: video_product_lookup
Description:
    Looks up a Product based on its TOC and displays some metadata.
    Supports only online lookup modes.

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

        self.display_build_info()

        # Get the user, registering if necessary.
        self.user = self.get_user(client_id, client_id_tag, application_version)

        # Set the locale.
        try:
            locale = gnsdk.GnLocale(
                                    gnsdk.kLocaleGroupVideo,
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

        return user

    def display_build_info(self):
        # Print all of the version information.
        print get_build_info("\nGNSDK Product", self.__manager)

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
    
    def display_product_titles(products):
        for product_index, products in enumerate(products):
            print "%2d: %s" % (product_index+1, products.official_title().display())
    
    def do_match_selection(products):
        print "\nMatch count: %d" % len(products)
        display_product_titles(products)
        # Here you could prompt the user to selection. We just hard-code 1st result.
        return 1
    
    def display_product_metdata(product):
        print "\nTitle: %s" % product.official_title().display()
        print "Aspect ratio: %s" % product.aspect_ratio()
        print "Production Type: %s" % product.video_production_type()
        print "Package language: %s" % product.package_language_display()
        print "Rating: %s" % product.rating().rating()
        
    # Initialize video.
    video = gnsdk.GnVideo(manager.user)
    # Set options here, e.g. to request the single best result uncomment the next line.
    #video.OptionResultSingle(True)
    
    response = video.find_products(
        "1:15;2:198 15;3:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 6914 1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 7630 2564 8910 15;4:830 7241 6099 3596 9790 3605 2905 2060 10890 3026 6600 2214 5825 6741 3126 6914 1090 2490 3492 6515 6740 4006 6435 3690 1891 2244 5881 1435 7975 4020 4522 2179 3370 2111 7630 2564 8910 15;5:8962 15;6:11474 15;7:11538 15;",
        gnsdk.kTOCFlagDefault
    )

    if type(response) is gnsdk.GnResponseVideoProduct:
        if len(response.products()) == 0:
            print "\nNo products found\n"
        else:
            if response.needs_decision() or len(response.products()) > 1:
                choice_ordinal = do_match_selection(response.products())
            else:
                choice_ordinal = 1
                display_product_metdata(response.products()[choice_ordinal - 1])
                
    else:
        print "Error: invalid response\n"
