#ifndef TA_DEMO_SHA_H
#define TA_DEMO_SHA_H

#include <tee_api.h>

typedef enum{
	SHA_MODE_SHA1,
	SHA_MODE_SHA224,
	SHA_MODE_SHA256,
	SHA_MODE_SHA384,
	SHA_MODE_SHA512,
	SHA_MODE_INVALID
}SHA_MODE;

#define SHA1_DIGEST_SIZE	20
#define SHA224_DIGEST_SIZE	28
#define SHA256_DIGEST_SIZE	32
#define SHA384_DIGEST_SIZE	48
#define SHA512_DIGEST_SIZE	64


#define CHECK(res, name, action) do {			\
		if ((res) != TEE_SUCCESS) {		\
			DMSG(name ": 0x%08x", (res));	\
			action;				\
		}					\
	} while(0)

TEE_Result ta_demo_entry_sha(uint32_t nParamTypes, TEE_Param pParams[4]);
TEE_Result crypto_sha(void* ibuf, uint32_t isize, void* obuf, 
					uint32_t *osize, uint32_t alg);




#endif
