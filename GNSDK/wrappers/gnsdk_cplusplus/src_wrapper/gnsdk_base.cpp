/*
 * Copyright (c) 2014 Gracenote.
 *
 * This software may not be used in any way or distributed without
 * permission. All rights reserved.
 *
 * Some code herein may be covered by US and international patents.
 */

/* gnsdk.cpp
 *
 * Implementation of C++ wrapper for GNSDK
 *
 */

#include "gnsdk_base.hpp"
#include "gnsdk_list.hpp"
#include "gnsdk_locale.hpp"
#include "gnsdk_manager.hpp"
#include "gnsdk_convert.hpp"

using namespace gracenote;

static void GNSDK_CALLBACK_API
_user_store_callback(gnsdk_void_t* callback_data, gnsdk_cstr_t client_id, gnsdk_cstr_t serialized_user);


/******************************************************************************
** GnUser
*/
GnUser::GnUser(gnsdk_cstr_t serializedUser, gnsdk_cstr_t clientIdTest) throw (GnError)
{
	gnsdk_user_handle_t user = GNSDK_NULL;
	gnsdk_error_t       error;

	error = gnsdk_manager_user_create(serializedUser, clientIdTest, &user);
	if (error) { throw GnError(); }

	options_.weakhandle_ = user;

	this->AcceptOwnership(user);
}

GnUser::GnUser(IGnUserStore& userStore, gnsdk_cstr_t clientId, gnsdk_cstr_t clientTag, gnsdk_cstr_t applicationVersion) throw (GnError)
{
	gnsdk_user_handle_t user           = GNSDK_NULL;
	gnsdk_str_t         serializedUser = GNSDK_NULL;
	gnsdk_error_t       error          = SDKMGRWARN_NotFound;
	GnError             e;

	if ( GNSDK_NULL == clientId )
	{
		throw GnError(GNSDKERR_InvalidArg,"Invalid Client ID provided: null");
	}

	/* try to create from stored user */
	GnString storedUserData = userStore.LoadSerializedUser(clientId);
	if (!storedUserData.IsEmpty())
	{
		error = gnsdk_manager_user_create(storedUserData, clientId, &user);
	}

	/* if did not deserialize user, or existing user is not for current clientId */
	if (error)
	{
		/* create local-only user for now, but set auto-register */
		error = gnsdk_manager_user_register(GNSDK_USER_REGISTER_MODE_LOCALONLY, clientId, clientTag, applicationVersion, &serializedUser);
		if (!error)
		{
			error = gnsdk_manager_user_create(serializedUser, clientId, &user);
			if (error)
			{
				e = GnError();
			}

			gnsdk_manager_string_free(serializedUser);
		}
		else
		{
			e = GnError();
		}
	}

	/* always set autoreg callback on created user */
	if (!error)
	{
		error = gnsdk_manager_user_set_autoregister(user, _user_store_callback, &userStore);
		if (error)
		{
			e = GnError();
		}
	}

	if (error)
	{
		gnsdk_manager_user_release(user);
		throw e;
	}

	options_.weakhandle_ = user;

	this->AcceptOwnership(user);
}


static void GNSDK_CALLBACK_API
_user_store_callback(gnsdk_void_t* callback_data, gnsdk_cstr_t client_id, gnsdk_cstr_t serialized_user)
{
	IGnUserStore* userStore = (IGnUserStore*)callback_data;

	userStore->StoreSerializedUser(client_id, serialized_user);
}


bool
GnUser::IsLocalOnly() const throw (GnError)
{
	gnsdk_bool_t	b_local_only = GNSDK_FALSE;
	gnsdk_error_t	error;

	error = gnsdk_manager_user_is_localonly(native(), &b_local_only);
	if (error) { throw GnError(); }

	if (b_local_only)
		return true;
	return false;
}


/******************************************************************************
** GnUserOptions

GnUserOptions::GnUserOptions(const GnUserOptions& options)
{
	this->weakhandle_ = options.weakhandle_;
}

GnUserOptions&
GnUserOptions::operator=(const GnUserOptions& options)
{
	this->weakhandle_ = options.weakhandle_;
	return *this;
}
*/
/*-----------------------------------------------------------------------------
 *  LookupMode
 */
GnLookupMode
GnUserOptions::LookupMode() throw (GnError)
{
	gnsdk_cstr_t	value;
	gnsdk_error_t	error;

	error = gnsdk_manager_user_option_get(weakhandle_, GNSDK_USER_OPTION_LOOKUP_MODE, &value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	if (gnstd::gn_strcmp(value, GNSDK_LOOKUP_MODE_LOCAL) == 0)
		return kLookupModeLocal;
	if (gnstd::gn_strcmp(value, GNSDK_LOOKUP_MODE_ONLINE) == 0)
		return kLookupModeOnline;
	if (gnstd::gn_strcmp(value, GNSDK_LOOKUP_MODE_ONLINE_NOCACHE) == 0)
		return kLookupModeOnlineNoCache;
	if (gnstd::gn_strcmp(value, GNSDK_LOOKUP_MODE_ONLINE_NOCACHEREAD) == 0)
		return kLookupModeOnlineNoCacheRead;
	if (gnstd::gn_strcmp(value, GNSDK_LOOKUP_MODE_ONLINE_CACHEONLY) == 0)
		return kLookupModeOnlineCacheOnly;

	return kLookupModeInvalid;
}

void
GnUserOptions::LookupMode(GnLookupMode lookupMode) throw (GnError)
{
	gnsdk_error_t error;

	switch (lookupMode)
	{
	case kLookupModeLocal:
		error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_LOCAL);
		break;

	case kLookupModeOnline:
		error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE);
		break;

	case kLookupModeOnlineNoCache:
		error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_NOCACHE);
		break;

	case kLookupModeOnlineNoCacheRead:
		error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_NOCACHEREAD);
		break;

	case kLookupModeOnlineCacheOnly:
		error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_LOOKUP_MODE, GNSDK_LOOKUP_MODE_ONLINE_CACHEONLY);
		break;

	default:
		return;
	}

	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  NetworkProxy
 */
gnsdk_cstr_t
GnUserOptions::NetworkProxy() throw (GnError)
{
	gnsdk_cstr_t	value;
	gnsdk_error_t	error;

	error = gnsdk_manager_user_option_get(weakhandle_, GNSDK_USER_OPTION_PROXY_HOST, &value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return value;
}

void
GnUserOptions::NetworkProxy(gnsdk_cstr_t hostName, gnsdk_cstr_t userName, gnsdk_cstr_t password) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_PROXY_HOST, hostName);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_PROXY_PASS, password);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_PROXY_USER, userName);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  NetworkTimeout
 */
gnsdk_uint32_t
GnUserOptions::NetworkTimeout() throw (GnError)
{
	gnsdk_cstr_t	value;
	gnsdk_error_t	error;
	
	error = gnsdk_manager_user_option_get(weakhandle_, GNSDK_USER_OPTION_NETWORK_TIMEOUT, &value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return gnstd::gn_atoi(value);
}

void
GnUserOptions::NetworkTimeout(gnsdk_uint32_t timeoutMs) throw (GnError)
{
	gnsdk_char_t	buf[32];
	gnsdk_error_t	error;
	
	gnstd::gn_itoa(buf, sizeof(buf), timeoutMs);
	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_NETWORK_TIMEOUT, buf);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  NetworkLoadBalance
 */
bool
GnUserOptions::NetworkLoadBalance() throw (GnError)
{
	gnsdk_cstr_t	value;
	gnsdk_error_t	error;
	
	error = gnsdk_manager_user_option_get(weakhandle_, GNSDK_USER_OPTION_NETWORK_LOADBALANCE, &value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return gnstd::gn_strtobool(value);
}

void
GnUserOptions::NetworkLoadBalance(bool bEnable) throw (GnError)
{
	gnsdk_error_t error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_NETWORK_LOADBALANCE, bEnable ? "Y" : "N");
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  UserInfo
 */
gnsdk_cstr_t
GnUserOptions::NetworkInterface() throw (GnError)
{
	gnsdk_cstr_t	value;
	gnsdk_error_t	error;

	error = gnsdk_manager_user_option_get(weakhandle_, GNSDK_USER_OPTION_NETWORK_INTERFACE, &value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return value;
}

void
GnUserOptions::NetworkInterface(gnsdk_cstr_t nicIpAddress) throw (GnError)
{
	gnsdk_error_t	error;

	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_NETWORK_INTERFACE, nicIpAddress);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  UserInfo
 */
void
GnUserOptions::UserInfo(gnsdk_cstr_t locationId, gnsdk_cstr_t mfg, gnsdk_cstr_t os, gnsdk_cstr_t uId) throw (GnError)
{
	gnsdk_error_t error;

	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_LOCATION_ID, locationId);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_INFO_MFG, mfg);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_INFO_OS, os);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
	
	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_INFO_RAWUID, uId);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}


/*-----------------------------------------------------------------------------
 *  CacheExpiration
 */
gnsdk_uint32_t
GnUserOptions::CacheExpiration() throw (GnError)
{
	gnsdk_cstr_t	value;
	gnsdk_error_t	error;
	
	error = gnsdk_manager_user_option_get(weakhandle_, GNSDK_USER_OPTION_CACHE_EXPIRATION, &value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return gnstd::gn_atoi(value);
}

void
GnUserOptions::CacheExpiration(gnsdk_uint32_t durationSec) throw (GnError)
{
	gnsdk_char_t	buf[32];
	gnsdk_error_t	error;
	
	gnstd::gn_itoa(buf, sizeof(buf), durationSec);
	error = gnsdk_manager_user_option_set(weakhandle_, GNSDK_USER_OPTION_CACHE_EXPIRATION, buf);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}

/*-----------------------------------------------------------------------------
 *  Custom
 */
gnsdk_cstr_t
GnUserOptions::Custom(gnsdk_cstr_t key) throw (GnError)
{
	gnsdk_cstr_t	value;
	gnsdk_error_t	error;
	
	error = gnsdk_manager_user_option_get(weakhandle_, key, &value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }

	return value;
}

void
GnUserOptions::Custom(gnsdk_cstr_t key, gnsdk_cstr_t value) throw (GnError)
{
	gnsdk_error_t error;
	
	error = gnsdk_manager_user_option_set(weakhandle_, key, value);
	if (GNSDKERR_SEVERE(error) ) { throw GnError(); }
}


/******************************************************************************
** GnObject
*/

GnObject::GnObject(gnsdk_handle_t handle) throw (GnError) : handle_(handle)
{
	if (GNSDK_NULL != handle)
	{
		_gnsdk_internal::manager_addref();

		gnsdk_error_t error = gnsdk_handle_addref(handle_);
		if (error)
		{
			handle_ = GNSDK_NULL;
			_gnsdk_internal::manager_release();
			throw GnError();
		}
	}
}

GnObject::GnObject(const GnObject& copy) throw (GnError) : handle_(GNSDK_NULL)
{
	if (GNSDK_NULL != copy.handle_)
	{
		_gnsdk_internal::manager_addref();

		handle_ = copy.handle_;
		gnsdk_error_t error = gnsdk_handle_addref(handle_);
		if (error)
		{
			handle_ = GNSDK_NULL;
			_gnsdk_internal::manager_release();
			throw GnError();
		}
	}
}

/*-----------------------------------------------------------------------------
	*  operator =
	*/
GnObject&
GnObject::operator = (const GnObject& rhs) throw (GnError)
{
	gnsdk_error_t error;

	/* Check for self assignment */
	if (this == &rhs)
	{
		return *this;
	}

	if (GNSDK_NULL != handle_)
	{
		error = gnsdk_handle_release(handle_);
		if (error) { throw GnError(); }

		_gnsdk_internal::manager_release();
	}

	handle_ = rhs.handle_;

	if (GNSDK_NULL != handle_)
	{
		_gnsdk_internal::manager_addref();

		gnsdk_error_t error = gnsdk_handle_addref(handle_);
		if (error) { throw GnError(); }
	}

	return *this;
}

GnObject::~GnObject()
{
	if (GNSDK_NULL != handle_)
	{
		gnsdk_handle_release(handle_);
		_gnsdk_internal::manager_release();
	}
}

/*-----------------------------------------------------------------------------
	*  AcceptOwnership
	*/
void
GnObject::AcceptOwnership(gnsdk_handle_t handle) throw (GnError)
{
	if (GNSDK_NULL != handle)
	{
		_gnsdk_internal::manager_addref();
	}

	if (GNSDK_NULL != handle_)
	{
		gnsdk_error_t error = gnsdk_handle_release(handle_);
		if (error) { throw GnError(); }

		if (GNSDK_NULL == handle)
		{
			_gnsdk_internal::manager_release();
		}
	}

	handle_ = handle;
}


