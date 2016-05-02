# Copyright (c) 2000-present Gracenote.
#
# This software may not be used in any way or distributed without
# permission. All rights reserved.
#
# Some code herein may be covered by US and international patents.

"""
Common utilities for GNSDK python sample applications.

"""

import sys
import os
import platform

class GNSDK_Configuration:
    
    def __init__(self):
        # Set configuration defaults then load any overrides from config module.
        self.use_local = False
        self.enable_logging = True
        self.storage_path = os.path.join(sample_data, "sample_db")
        
        # Now try to open the config script and read any overrides.
        try:
            import gnsdk_config
        except:
            print "\n\t******************************************************"
            print   "\t********* Configuration script not provided **********"
            print   "\t*********     Proceeding with defaults      **********"
            print   "\t******************************************************\n"
        else:
            try:
                self.use_local = gnsdk_config.use_local
            except:
                pass
            try:
                self.enable_logging = gnsdk_config.enable_logging
            except:
                pass
            try:
                self.storage_path = gnsdk_config.storage_path
            except:
                pass

    def __str__(self):
        return "\tuse_local = %s\n\tenable_logging = %s\n\tstorage_path = %s" % (
            self.use_local,
            self.enable_logging,
            self.storage_path
        )

# Construct the GNSDK platform folder name.
def get_platform_dir():
    machine = platform.machine()
    try:
        hyphIdx = machine.index('_')
    except:
        if machine == 'AMD64':
            machine = 'x86-32'
        elif machine == 'i686':
            machine = 'x86-32'
        elif machine == 'i386':
            machine = 'x86-64'
    else:
        machine = machine[:hyphIdx] + '-' + machine[hyphIdx+1:]

    system = platform.system()
    if system == 'Darwin':
        system = 'mac'
    elif system == 'Windows':
        system = 'win'
    elif system == 'Linux':
        system = 'linux'
    elif system[:6] == 'CYGWIN':
        system = 'win'

    return system + '_' + machine

# Are we in perforce or in a release package?
def get_environment():
    if os.path.exists(os.path.join("..", "..", "..", "..", "..", "..", "..", "..", "gn-sdks")):
        environment = "depot"
    elif os.path.exists(os.path.join("..", "..", "..", "..", "lib")):
        environment = "release"
    else:
        raise RuntimeError("Can't determine path to libraries. Where am I?")
    return environment

# Determine platform and whether we are in perfoce or a release package.
shared_root = os.path.join("..", "..", "..", "..")
sample_data = os.path.join(shared_root, "sample_data")

platform_dir = get_platform_dir()
environment = get_environment()
if environment == "depot":
    install_root = os.path.join(shared_root, "..", "install")
    lib_path = os.path.join(install_root, 'common', 'release', 'lib', platform_dir)
    module_dirs = [
        os.path.join(install_root, 'wrappers', 'gnsdk_python', 'src_wrapper'),
        os.path.join(install_root, 'wrappers', 'gnsdk_python', 'lib', 'release', platform_dir)
    ]
elif environment == "release":
    lib_path = os.path.join(shared_root, "lib", platform_dir)
    module_dirs = [
        os.path.join(shared_root, "wrappers", "gnsdk_python", "src_wrapper"),
        os.path.join(shared_root, "wrappers", "gnsdk_python", "lib", platform_dir)
    ]

# Check that the extension module directory and the gnsdk library directory exist
for dir in module_dirs + [lib_path, sample_data]:
    if not os.path.exists(dir):
        raise RuntimeError("Path %s does not exist" % dir)

if __name__ != "__main__":
    # Add directories with the python wrapper and extension module to sys.path.
    for moduleDir in module_dirs:
        sys.path.append(moduleDir)

if __name__ == "__main__":
    print
    print "platform_dir = %s" % platform_dir
    print "install_root =   %s" % install_root
    print "lib_path =      %s" % lib_path
    for item in module_dirs:
        print "append to path: %s" % item
    print
