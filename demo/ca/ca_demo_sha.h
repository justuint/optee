#ifndef CA_DEMO_SHA1_H
#define CAD_EMO_SHA1_H

#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "tee_client_api.h"

#define TA_DEMO_UUID {0xea044d40, 0x01f5, 0x11ea, {0x8d, 0x71, 0x36, 0x2b, 0x9e, 0x15, 0x56, 0x67}}

typedef enum{
	SHA_MODE_SHA1,
	SHA_MODE_SHA224,
	SHA_MODE_SHA256,
	SHA_MODE_SHA384,
	SHA_MODE_SHA512,
	SHA_MODE_INVALID
}SHA_MODE;
	
TEEC_Result ca_demo_sha_open(void);
TEEC_Result ca_demo_sha(void* in, unsigned int size, void *out, SHA_MODE mode);
void ca_demo_sha_close(void);




/*
 *CommandID
 */
#define CA_DEMO_CMD_SHA 1

#endif