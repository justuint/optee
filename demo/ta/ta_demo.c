#include "ta_demo.h"
#include "ta_demo_sha.h"
#include "ta_demo_rsa.h"

/*
 * Trusted Application Entry Point
 * Called each time a new instance is created.
 */
TEE_Result TA_CreateEntryPoint(void)
{
	DMSG("Create entry point for %s\n", TA_NAME);
	return TEE_SUCCESS;
}


/*
 * Called each time an instance is destroyed.
 */
void TA_DestroyEntryPoint(void)
{
	DMSG("Destroy entry point for %s\n", TA_NAME);
}


/*
 * Called each time a session is opened
 */
TEE_Result TA_OpenSessionEntryPoint(uint32_t nParamTypes,
				    TEE_Param pParams[4], void **ppSessionContext)
{
	//(void)nParamTypes;
	//(void)pParams;
	//(void)ppSessionContext;
	DMSG("Open session entry point for %s\n", TA_NAME);
	return TEE_SUCCESS;
}


/*
 * Called each time a session is closed
 */
void TA_CloseSessionEntryPoint(void *pSessionContext)
{
	//(void)pSessionContext;
	DMSG("Close session entry point for %s\n", TA_NAME);
}


/*
 * Called when a command is invoked
 */
TEE_Result TA_InvokeCommandEntryPoint(void *pSessionContext,uint32_t nCommandID,
										uint32_t nParamTypes, TEE_Param pParams[4])
{
	DMSG("TA Invoke Command Entry Point for %s commandId: %d\n",TA_NAME,nCommandID);
	switch(nCommandID){
		case TA_DEMO_CMD_SHA:
			return ta_demo_entry_sha(nParamTypes, pParams);
		case TA_DEMO_CMD_RSA:
			return ta_demo_entry_rsa(nParamTypes, pParams);
		default:
			return TEE_ERROR_BAD_PARAMETERS;
	}
}



