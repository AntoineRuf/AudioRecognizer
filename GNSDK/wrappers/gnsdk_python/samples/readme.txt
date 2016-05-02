Cookbook for executing a python sample, assuming you have python 2.6 or greater installed.

# Build and install the python wrapper. Note, the "cleanall" option below causes a
# "make clean" on gcsl and common and so can take some time. Use "clean" instead of
# "cleanall" to just clean the wrapper.

prompt$ cd gn-sdks/devel/main/source/wrappers
prompt$ python make_wrapper.py python cleanall

# Now execute.

prompt$ cd gnsdk_python/samples

# Verify that gnsdk_config.py is set up the way you want.

prompt$ cd <sample_name>
prompt$ python main.py <client_id> <client_id_tag> <license_file>


# The configuration of the samples can be modified by editing samples/gnsdk_config.py.
# To run in local mode, for example, you would change this line
use_local = False
# to this
use_local = True

# When you run in local mode, you need to make sure you have a gdb installed at the
# location indicated by the configuration setting
storage_path

# Not all samples support local mode. The following samples only support online queries.
acr_fp_lookup
musicid_match
musicid_stream
vacr_fp_lookup
vacr_wrapper
video_*

# In addition the following sample is not impacted by the "use_local" setting.
musicid_lookup_album_local_online
# This sample attempts local and online lookups so does require a gdb.

