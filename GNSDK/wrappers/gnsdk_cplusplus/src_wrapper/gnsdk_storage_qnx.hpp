/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef _GNSDK_STORAGE_QNX_HPP_
#define _GNSDK_STORAGE_QNX_HPP_

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_base.hpp"

#if GNSDK_STORAGE_QNX

namespace gracenote
{
	namespace storage_qnx
	{
		/**************************************************************************
		** GnStorageQnx
		*/
		class GnStorageQnx : public GnObject
		{
		public:
			GNWRAPPER_ANNOTATE

			GnStorageQnx()  throw (GnError)
			{
				module_initialize(GNSDK_MODULE_STORAGE_QNX);
			}

			virtual ~GnStorageQnx() { }

			/**
			 *  Retrieves the version string of the Storage SQLite library.
			 **/
			static gnsdk_cstr_t Version()
			{
				return gnsdk_storage_qnx_get_version();
			}

			static gnsdk_cstr_t BuildDate()
			{
				return gnsdk_storage_qnx_get_build_date();
			}

			void OptionStorageFolderSet(gnsdk_cstr_t folderPath) throw (GnError)
			{
				gnsdk_error_t error;

				error = gnsdk_storage_qnx_option_set(GNSDK_STORAGE_QNX_OPTION_STORAGE_FOLDER, folderPath);
				if (error) { throw GnError(); }
			}

			gnsdk_cstr_t OptionStorageFolderGet() throw (GnError)
			{
				gnsdk_error_t error;
				gnsdk_cstr_t  storageFolder = GNSDK_NULL;

				error = gnsdk_storage_qnx_option_get(GNSDK_STORAGE_QNX_OPTION_STORAGE_FOLDER, &storageFolder);
				if (error) { throw GnError(); }

				return storageFolder;
			}
			
			/** 
			*  Sets option to use pps - default is false
			*/
			void OptionUsePPSSet(gnsdk_bool_t bUsePPS) throw (GnError)
			{
				gnsdk_error_t error;
				
				if(true == bUsePPS)
				{
					error = gnsdk_storage_qnx_option_set(GNSDK_STORAGE_QNX_OPTION_USE_PPS, GNSDK_VALUE_TRUE);
				}				
				else
				{
					error = gnsdk_storage_qnx_option_set(GNSDK_STORAGE_QNX_OPTION_USE_PPS, GNSDK_VALUE_FALSE);
				}
				if (error) { throw GnError(); }
				
				return;
			}
			
			/** 
			*  Gets option value for use pps - default is false
			*/	
			bool OptionUsePPSGet(gnsdk_bool_t bUsePPS) throw (GnError)
			{
				gnsdk_error_t error;
				gnsdk_cstr_t value; 
				
				if(true == bUsePPS)
				{
					error = gnsdk_storage_qnx_option_get(GNSDK_STORAGE_QNX_OPTION_USE_PPS, &value);
				}				
				else
				{
					error = gnsdk_storage_qnx_option_get(GNSDK_STORAGE_QNX_OPTION_USE_PPS, &value);
				}
				if (error) { throw GnError(); }
				
				return gnstd::gn_strtobool(value);;
			}

		private:
			/* dissallow assignment operator */
			DISALLOW_COPY_AND_ASSIGN(GnStorageQnx);
		};
	} // namespace storage_qnx
}     // namespace gracenote
#endif /* GNSDK_STORAGE_QNX */
#endif // _GNSDK_STORAGE_QNX_HPP_
