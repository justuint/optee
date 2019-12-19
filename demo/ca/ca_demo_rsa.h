#ifndef CA_DEMO_RSA_H
#define CA_DEMO_RSA_H
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

#ifndef  TA_DEMO_UUID
#define TA_DEMO_UUID {0xea044d40, 0x01f5, 0x11ea, {0x8d, 0x71, 0x36, 0x2b, 0x9e, 0x15, 0x56, 0x67}}
#endif

#define CA_DEMO_CMD_RSA 2

typedef enum{
	RSA_EN_DEC,
	RSA_EN_ENC,
	RSA_EN_SIGN,
	RSA_EN_VERIFV	
}RSA_MODE;


TEEC_Result ca_demo_rsa_open(void);
TEEC_Result ca_demo_rsa(void* in, unsigned int size, void *out, RSA_MODE mode);
void ca_demo_rsa_close(void);

#endif
