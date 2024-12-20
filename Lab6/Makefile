ifneq ($(KERNELRELEASE),)

obj-m := hello1.o hello2.o

ccflags-y += -g

else

KDIR ?= /lib/modules/`uname -r`/build

default:

	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:

	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif

