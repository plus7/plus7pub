obj-m := example.o hello.o

# Modify this if you put the kernel source tree in a different location.
KERNELDIR := /lib/modules/`uname -r`/build

all::
	$(MAKE) -C ${KERNELDIR} M=`pwd` modules

install::
	$(MAKE) -C ${KERNELDIR} V=1 M=`pwd` modules_install

clean:
	$(MAKE) -C ${KERNELDIR} M=`pwd` clean
	rm -f *~ *.ko *.o .*.o.d *.mod.[co] .*.cmd Module.symvers
	rm -rf .tmp_versions
