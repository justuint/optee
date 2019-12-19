SHELL = /bin/bash

BINARY = ea044d40-01f5-11ea-8d71362b9e155667
CFG_TEE_TA_LOG_LEVEL	?= 4

# Make these default for now
CROSS_COMPILE ?= arm-none-linux-gnueabi-
TA_DEV_KIT_DIR  ?= $(shell pwd)/../../out/export-ta_arm32
ifneq ($O,)
	out-dir := $O
else
	# If no build folder has been specified, then create all build files in
	# the current directory under a folder named out.
	out-dir := $(CURDIR)/out
endif

include $(TA_DEV_KIT_DIR)/host_include/conf.mk
include $(TA_DEV_KIT_DIR)/mk/ta_dev_kit.mk

ifneq ($V,1)
	q := @
	echo := @echo
else
	q :=
	echo := @:
endif

.PHONY: ta
ta: 
	$(q)$(MAKE) O=$(O)