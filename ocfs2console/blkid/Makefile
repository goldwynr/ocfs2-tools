TOPDIR = ../..

include $(TOPDIR)/Preamble.make

INCLUDES = -I..

CFLAGS += -fPIC
CPPFLAGS = -DHAVE_UNISTD_H=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 \
	-DHAVE_ERRNO_H=1 -DHAVE_SYS_IOCTL_H=1 -DHAVE_LINUX_FD_H=1 \
	-DHAVE_SYS_QUEUE_H=1 -DHAVE_STDLIB_H=1 -DHAVE_LSEEK64=1 \
	-DHAVE_LSEEK64_PROTOTYPE=1

CFILES =		\
	cache.c		\
	dev.c		\
	devname.c	\
	devno.c		\
	getsize.c	\
	llseek.c	\
	probe.c		\
	read.c		\
	resolve.c	\
	save.c		\
	tag.c		\
	version.c

HFILES = 		\
	blkid.h		\
	blkidP.h	\
	list.h		\
	probe.h

ifndef HAVE_BLKID

UNINST_LIBRARIES = libblkid-internal.a

OBJS = $(subst .c,.o,$(CFILES))

libblkid-internal.a: $(OBJS)
	rm -f $@
	$(AR) r $@ $^
	$(RANLIB) $@

endif

DIST_FILES = $(CFILES) $(HFILES) ChangeLog

include $(TOPDIR)/Postamble.make
