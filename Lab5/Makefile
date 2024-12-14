# SPDX-License-Identifier: GPL-2.0
obj-m += hello1.o
obj-m += hello2.o

ccflags-y := -I$(PWD)/inc

KDIR ?= /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

