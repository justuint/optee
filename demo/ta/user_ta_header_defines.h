#ifndef USER_TA_HEADER_DEFINES_H
#define USER_TA_HEADER_DEFINES_H

#include <stdint.h>
#include <user_ta_header.h>

#define TA_LOG_PREFIX	"ta_demo.ta"
#define TA_UUID {0xea044d40, 0x01f5, 0x11ea, {0x8d, 0x71, 0x36, 0x2b, 0x9e, 0x15, 0x56, 0x67}}

#define TA_FLAGS (TA_FLAG_USER_MODE | TA_FLAG_EXEC_DDR | \
		  TA_FLAG_UNSAFE_NW_PARAMS | \
		  TA_FLAG_MULTI_SESSION)
#define TA_STACK_SIZE (8 * 1024)
#define TA_DATA_SIZE (900 * 1024)

#endif


