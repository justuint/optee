#ifndef TA_DEMO_RSA_H
#define TA_DEMO_RSA_H

#include <tee_api.h>

TEE_Result ta_demo_entry_rsa(uint32_t nParamTypes, TEE_Param pParams[4]);

typedef enum{
	RSA_EN_DEC,
	RSA_EN_ENC,
	RSA_EN_SIGN,
	RSA_EN_VERIFV	
}RSA_MODE;

typedef struct _RsaKey{
	char *nData;
	char *dData;
	char *eData;
	uint32_t nLen;
	uint32_t dLen;
	uint32_t eLen;
	uint32_t padding;
}RsaKey;

TEE_Result ta_demo_entry_rsa(uint32_t nParamTypes, TEE_Param pParams [ 4 ]);
TEE_Result ta_demo_rsa_enc(RsaKey key, char *ibuf, uint32_t isize, char *obuf, uint32_t *osize);
TEE_Result ta_demo_rsa_dec(RsaKey key, char *ibuf, uint32_t isize, char *obuf, uint32_t *osize);


#endif
