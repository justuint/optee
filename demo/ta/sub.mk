cppflags$(sm) += -I. 
cppflags$(sm) += -DCFG_TEE_TA_LOG_LEVEL=$(CFG_TEE_TA_LOG_LEVEL)
srcs-y += ta_demo.c
srcs-y += ta_demo_sha.c
srcs-y += ta_demo_rsa.c
