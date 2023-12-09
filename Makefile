ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m   := hello1.o hello2.o
ccflags-y += -g -I$(src)/inc	# added debugging info
else
# normal makefile
KDIR ?= /lib/modules/4.19.295/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
	cp hello1.ko hello1.ko.unstripped
	$(CROSS_COMPILE)strip -g hello1.ko # strip only debugging info
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
