#include "ca_demo.h"
#include "ca_demo_sha.h"
#include "ca_demo_rsa.h"

int main(int argc, char ** argv)
{
	char str[2048];
	TEEC_Result ret;
	if(argc < 3){
		printf("Please enter the string to be summarized\n");
		return -1;
	}

	if(strcmp(argv[1],"sha") == 0){
		ret = ca_demo_sha_open();
		if(ret != TEEC_SUCCESS){
			printf("ca_demo_sha_open failed:%x\n",ret);
			return -1;
		}
		SHA_MODE mode;
		mode = SHA_MODE_SHA1;
		ret = ca_demo_sha(argv[2], strlen(argv[2]), str, mode);
		if(ret != TEEC_SUCCESS)
			printf("ca_demo_sha failed :%x\n",ret);
		
		ca_demo_sha_close();
	}else if(strcmp(argv[1],"rsa") == 0){
		ret = ca_demo_rsa_open();
		if(ret != TEEC_SUCCESS){
			printf("ca_demo_rsa_open failed:%x\n",ret);
			return -1;
		}
		RSA_MODE mode1;
		//mode1 = argv[3][0]-'0';
		ret = ca_demo_rsa(argv[2], strlen(argv[2]), str, RSA_EN_ENC);
		ret = ca_demo_rsa(str, 128, str, RSA_EN_DEC);
		if(ret != TEEC_SUCCESS)
			printf("ca_demo_sha failed :%x\n",ret);
		ca_demo_rsa_close();
		
	}

	return 0;
}
