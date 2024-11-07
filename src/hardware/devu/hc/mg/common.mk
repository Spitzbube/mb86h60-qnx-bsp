ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

NAME=devu-mb86h60-mg

define PINFO
PINFO DESCRIPTION=Mentor USB controller driver
endef

include $(MKFILES_ROOT)/qtargets.mk

