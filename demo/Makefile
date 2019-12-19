CROSS_COMPILE ?= arm-linux-gnueabihf-
TA_DEV_KIT_DIR  ?= $(shell pwd)/../../out/export-ta_arm32
OPTEE_CLIENT_EXPORT ?=$(shell pwd)/../../optee_client/out/export
ifneq ($O,)
	out-dir := $O
else
	# If no build folder has been specified, then create all build files in
	# the current directory under a folder named out.
	out-dir := $(CURDIR)/out
endif

include $(TA_DEV_KIT_DIR)/host_include/conf.mk

ifneq ($V,1)
	q := @
	echo := @echo
else
	q :=
	echo := @:
endif

.PHONY: all
ifneq ($(wildcard $(TA_DEV_KIT_DIR)/host_include/conf.mk),)
all:  ca ta
else
all:
	$(q)echo "TA_DEV_KIT_DIR is not correctly defined" && false
endif

.PHONY: ca
ca:
	$(q)echo "make ca_demo"
	$(q)$(MAKE) -C ca CROSS_COMPILE="$(CROSS_COMPILE)" TA_DEV_KIT_DIR=$(TA_DEV_KIT_DIR) \
			    OPTEE_CLIENT_EXPORT=$(OPTEE_CLIENT_EXPORT) --no-builtin-variables \
			     q=$(q) \
			     O=$(out-dir)/ca 
			  
			     
.PHONY: ta
ta:
	$(q)echo "make ta_demo"
	$(q)$(MAKE) -C ta CROSS_COMPILE="$(CROSS_COMPILE)" TA_DEV_KIT_DIR=$(TA_DEV_KIT_DIR) \
			  q=$(q) \
			  O=$(out-dir)/ta/demo V=1 \
			  $@

.PHONY: clean
ifneq ($(wildcard $(TA_DEV_KIT_DIR)/host_include/conf.mk),)
clean:
	$(q)$(MAKE) -C ca TA_DEV_KIT_DIR=$(TA_DEV_KIT_DIR) O=$(out-dir)/ca q=$(q) $@
	$(q)$(MAKE) -C ta TA_DEV_KIT_DIR=$(TA_DEV_KIT_DIR) O=$(out-dir)/ta q=$(q) $@
	$(q)rm -rf $(out-dir)
else
clean:
	$(q)echo "TA_DEV_KIT_DIR is not correctly defined"
	$(q)echo "You can remove manually $(out-dir)"
endif

install:
	$(echo) '  INSTALL ${DESTDIR}/lib/optee_armtz'
	$(q)mkdir -p ${DESTDIR}/lib/optee_armtz
	$(q)find $(out-dir) -name \*.ta -exec cp -a {} ${DESTDIR}/lib/optee_armtz \;
	$(echo) '  INSTALL ${DESTDIR}/bin'
	$(q)mkdir -p ${DESTDIR}/bin
	$(q)cp -a $(out-dir)/ca/ca_demo ${DESTDIR}/bin

