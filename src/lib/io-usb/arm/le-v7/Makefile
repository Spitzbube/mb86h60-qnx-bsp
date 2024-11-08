include ../../../common.mk

class.o : override CCFLAGS+=-O0

my_io-usb.dump: my-io-usb
	arm-unknown-nto-qnx6.5.0-objdump -hds  my-io-usb > my-io-usb.dump

