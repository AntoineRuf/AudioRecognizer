/** Public header file for Gracenote SDK C++ Wrapper
 * Author:
 *   Copyright (c) 2014 Gracenote, Inc.
 *
 *   This software may not be used in any way or distributed without
 *   permission. All rights reserved.
 *
 *   Some code herein may be covered by US and international patents.
 */

#ifndef __cplusplus
#error "C++ compiler required"
#endif

#include "gnsdk_std.hpp"

using namespace gracenote;

const char* gnstd::kEmptyString = "";

bool
gnstd::gn_strtobool(gnsdk_cstr_t value)
{
	if (value)
	{
		if (value[0] != '0')
		{
			return true;
		}
	}
	return false;
}

gnsdk_int32_t
gnstd::gn_atoi(gnsdk_cstr_t value)
{
	gnsdk_int32_t val   = 0;
	bool          b_neg = false;

	if (value)
	{
		while( ( *value == ' ' ) || ( *value == '\t' ) )
		{
			value++;
		}

		if (*value == '-')
		{
			b_neg = true;
			++value;
		}
		else if (*value == '+')
		{
			++value;
		}

		while( ( *value >= '0' ) && ( *value <= '9' ) )
		{
			val = val * 10 + ( *value - '0' );
			++value;
		}

		if (b_neg)
		{
			val = -val;
		}
	}
	return val;
}

bool
gnstd::gn_itoa(char* buffer, gnsdk_size_t buffer_sz, int value)
{
	gnsdk_size_t  used    = 1;
	gnsdk_size_t  current = 0;

	// minimum is a signed char
	bool retval = false;
	char base   = '0';

	buffer[current] = '\0';

	// special case
	if ( ( value == 0 ) && ( ( used ) < buffer_sz ) )
	{
		buffer[current++] = base;
	}
	if ( ( value < 0 ) && ( ( ++used ) < buffer_sz ) )
	{
		buffer[current++] = '-';
		value            *= -1;
	}
	gnsdk_size_t start_pos = current;

	for(char next_val = 0; value > 0 && used < buffer_sz; ++used, value /= 10)
	{
		next_val          = (char)( value % 10 );
		buffer[current++] = base + next_val;
	}

	// swap string around

	for(gnsdk_size_t end_pos = current - 1; start_pos < end_pos; start_pos++, end_pos--)
	{
		char temp = buffer[end_pos];
		buffer[end_pos]   = buffer[start_pos];
		buffer[start_pos] = temp;
	}

	retval          = ( 0 == value );
	buffer[current] = '\0';
	return retval;
}

gnsdk_int32_t
gnstd::gn_strcmp(gnsdk_cstr_t lhs, gnsdk_cstr_t rhs)
{
	if (lhs == rhs)
		return 0;

	if ( (lhs == 0) || (rhs == 0) )
		return 1;

	while(*lhs == *rhs)
	{
		if (*lhs == '\0')
		{
			return 0;
		}
		++lhs;
		++rhs;
	}

	return *lhs - *rhs;
}

gnsdk_size_t
gnstd::gn_strlen(gnsdk_cstr_t s)
{
	gnsdk_size_t i = 0;

	if ( GNSDK_NULL == s )
		return 0;

	while (s[i])
	{
		i++;
	}

	return i;
}

gnsdk_size_t
gnstd::gn_strcpy(char* dest, gnsdk_size_t dest_size, gnsdk_cstr_t src)
{
	gnsdk_size_t count = 0;

	if (dest && src)
	{
		while( ( count < dest_size ) && ( *dest++ = *src++ ) )
		{
			count++;
		}
	}

	return count;
}
