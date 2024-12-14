# SPDX-License-Identifier: GPL-2.0
obj-m += hello.o

KDIR ?= /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

