#include "ta_demo_sha.h"

TEE_Result ta_demo_entry_sha(uint32_t nParamTypes, TEE_Param pParams[4])
{
	TEE_Result ret;
	SHA_MODE mode;
	void* ibuf;
	void* obuf;
	uint32_t isize,alg,osize;
	if(nParamTypes != TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INPUT, TEE_PARAM_TYPE_MEMREF_INPUT,
										TEE_PARAM_TYPE_MEMREF_OUTPUT, TEE_PARAM_TYPE_NONE))
		return TEE_ERROR_BAD_PARAMETERS;
	mode = pParams[0].value.a;
	ibuf = pParams[1].memref.buffer;
	isize = pParams[1].memref.size;
	obuf = pParams[2].memref.buffer;
	osize = pParams[2].memref.size;
	switch (mode){
		case SHA_MODE_SHA1:
			if(&osize>SHA1_DIGEST_SIZE)
				alg=TEE_ALG_SHA1;
			else
				return TEE_ERROR_SHORT_BUFFER;
			break;
		case SHA_MODE_SHA224:
			if(&osize>SHA224_DIGEST_SIZE)
				alg=TEE_ALG_SHA224;
			else
				return TEE_ERROR_SHORT_BUFFER;
			break;
		case SHA_MODE_SHA256:
			if(&osize>SHA256_DIGEST_SIZE)
				alg=TEE_ALG_SHA256;
			else
				return TEE_ERROR_SHORT_BUFFER;
			break;
		case SHA_MODE_SHA384:
			if(&osize>SHA384_DIGEST_SIZE)
				alg=TEE_ALG_SHA384;
			else
				return TEE_ERROR_SHORT_BUFFER;
			break;
		case SHA_MODE_SHA512:
			if(&osize>SHA512_DIGEST_SIZE)
				alg=TEE_ALG_SHA512;
			else
				return TEE_ERROR_SHORT_BUFFER;
			break;
		default:
			DMSG("ta_demo_entry_sha: Invalid mode:%d\n",mode);
			return TEE_ERROR_BAD_PARAMETERS;
	}
	
	ret = crypto_sha(ibuf, isize, obuf, &pParams[2].memref.size, alg);

	if(ret != TEE_SUCCESS)
		DMSG("sha_call error %x\n",ret);
	return ret;
}

TEE_Result crypto_sha(void* ibuf, uint32_t isize, void* obuf, 
								uint32_t *osize, uint32_t alg)
{
	TEE_OperationHandle op;
	TEE_Result ret;
	
	ret = TEE_AllocateOperation(&op, alg, TEE_MODE_DIGEST, 0);
	if(ret != TEE_SUCCESS){
		DMSG("crypto_sha: TEE_AllocateOperation failed: %x\n",ret);
		goto exit_1;
	}
	
	TEE_DigestUpdate(op, ibuf, isize);
	ret = TEE_DigestDoFinal(op, ibuf, isize, obuf, osize);
	if(ret != TEE_SUCCESS){
		DMSG("crypto_sha: TEE_DigestDoFinal failed: %x\n",ret);
		goto exit_2;
	}
exit_2:
	TEE_FreeOperation(op);
exit_1:
	return ret;
}
