#include "ca_demo_rsa.h"


static  int valid_session = 0;
static  TEEC_Context context;
static  TEEC_Session session;
static  TEEC_SharedMemory sharedMem;

TEEC_Result ca_demo_rsa_open(void)
{
	TEEC_Result ret;
	TEEC_UUID id = TA_DEMO_UUID;
	//printf("ca_demo_sha_open\n",ret);
	ret = TEEC_InitializeContext(NULL, &context);
	if(ret != TEEC_SUCCESS){
		printf("ca_demo_sha_open:TEEC_InitializeContext failed %x\n",ret);
		goto exit_1;
	}

	ret = TEEC_OpenSession(&context, &session, &id, TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
	if(ret != TEEC_SUCCESS){
		printf("ca_demo_sha_open:TEEC_OpenSession failed %x\n",ret);
		goto finalizeContext;
	}

	sharedMem.size = 1024 * 4;
	sharedMem.flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT;

	ret = TEEC_AllocateSharedMemory(&context, &sharedMem);
	if(ret != TEEC_SUCCESS){
		printf("ca_demo_sha_open:TEEC_AllocateSharedMemory failed %x\n",ret);
		goto closeSession;
	}
	
	valid_session = 1;
	return ret;

closeSession:
	TEEC_CloseSession(&session);

finalizeContext:
	TEEC_FinalizeContext(&context);

exit_1:
	return ret;
}

TEEC_Result ca_demo_rsa(void* in, unsigned int size, void *out, RSA_MODE mode)
{
	TEEC_Result ret;
	TEEC_Operation op;
	uint32_t err_origin;
	
	//printf("ca_demo_rsa\n");
	if(!valid_session)
		return TEEC_ERROR_BAD_STATE;
	if(size > 1024)
		return TEEC_ERROR_BAD_PARAMETERS;

	memcpy(sharedMem.buffer, in, size);
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_MEMREF_PARTIAL_INPUT,
										TEEC_MEMREF_PARTIAL_OUTPUT, TEEC_NONE);
	op.started = 1;
	op.params[0].value.a = mode;
	op.params[1].memref.parent = &sharedMem;
	op.params[1].memref.offset = 0;
	op.params[1].memref.size = size;

	op.params[2].memref.parent = &sharedMem;
	op.params[2].memref.offset = 2048;
	op.params[2].memref.size = 2048;
	
	ret = TEEC_InvokeCommand(&session, CA_DEMO_CMD_RSA, &op, &err_origin);
	if(ret != TEEC_SUCCESS){
		printf("invoke faild %x\n",ret);
		return ret;
	}
	
	memcpy(out, (void*)((char *)sharedMem.buffer + 2048), op.params[2].memref.size);
	uint32_t len = op.params[2].memref.size;
	printf("RSA: len:%d\n", len);
	int i;
	char* p = out;
	for(i= 0; i<len; i++)
		printf("%02x",p[i]);
	printf("\n");

	//printf("ENC_RESULT:%s\n",(char*)out);
	return ret;
}

void ca_demo_rsa_close(void)
{
	if(!valid_session)
		return;
	TEEC_ReleaseSharedMemory(&sharedMem);
	TEEC_CloseSession(&session);
	TEEC_FinalizeContext(&context);
	valid_session = 0;
	return;
}
