TOPDIR = ..

include $(TOPDIR)/Preamble.make

sbindir = $(root_sbindir)
SBIN_PROGRAMS = o2cb_ctl o2cb

INCLUDES = -I$(TOPDIR)/include

LIBTOOLS_INTERNAL_LIBS = -L$(TOPDIR)/libtools-internal -ltools-internal
LIBTOOLS_INTERNAL_DEPS = $(TOPDIR)/libtools-internal/libtools-internal.a

LIBOCFS2_LIBS = -L$(TOPDIR)/libocfs2 -locfs2
LIBOCFS2_DEPS = $(TOPDIR)/libocfs2/libocfs2.a

LIBO2CB_LIBS  = -L$(TOPDIR)/libo2cb -lo2cb
LIBO2CB_DEPS = $(TOPDIR)/libo2cb/libo2cb.a

LIBO2DLM_LIBS = -L$(TOPDIR)/libo2dlm -lo2dlm $(DL_LIBS)
LIBO2DLM_DEPS = $(TOPDIR)/libo2dlm/libo2dlm.a

ifndef OCFS2_DYNAMIC_CTL
LDFLAGS += -static
endif

DEFINES = -DVERSION=\"$(VERSION)\"

O2CB_CONFIG_CFILES = o2cb_config.c jconfig.c jiterator.c
O2CB_CTL_CFILES = ${O2CB_CONFIG_CFILES} o2cb_ctl.c
O2CB_CFILES = ${O2CB_CONFIG_CFILES} o2cbtool.c op_cluster.c op_node.c op_heartbeat.c \
		op_lists.c op_register.c op_start.c o2cb_scandisk.c op_status.c o2cbutils.c

O2CB_CTL_OBJS = $(subst .c,.o,$(O2CB_CTL_CFILES))
O2CB_OBJS = $(subst .c,.o,$(O2CB_CFILES))

HFILES = o2cb_config.h jconfig.h jiterator.h o2cbtool.h o2cb_scandisk.h

CFILES = $(O2CB_CTL_CFILES) $(O2CB_CFILES)

MANS = o2cb_ctl.8 o2cb.8 ocfs2.cluster.conf.5

DIST_FILES = $(CFILES) $(HFILES) o2cb_ctl.8.in o2cb.8.in ocfs2.cluster.conf.5.in

DIST_RULES = dist-subdircreate

jconfig_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
jiterator_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
o2cb_config_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
o2cb_ctl_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
o2cbtool_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
op_cluster_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
op_node_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
op_heartbeat_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
op_lists_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
op_register_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
op_start_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
o2cb_scandisk_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
op_status_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED
o2cbutils_CPPFLAGS = $(GLIB_CFLAGS) -DG_DISABLE_DEPRECATED

o2cb_ctl: $(O2CB_CTL_OBJS) $(LIBOCFS2_DEPS) $(LIBO2CB_DEPS)
	$(LINK) $(LIBO2CB_LIBS) $(GLIB_LIBS) $(LIBOCFS2_LIBS) $(COM_ERR_LIBS) $(AIO_LIBS)

o2cb: $(O2CB_OBJS) $(LIBOCFS2_DEPS) $(LIBO2CB_DEPS) ${LIBO2DLM_DEPS} ${LIBTOOLS_INTERNAL_DEPS}
	$(LINK) $(LIBO2CB_LIBS) $(GLIB_LIBS) $(LIBOCFS2_LIBS) ${LIBO2DLM_LIBS} ${LIBTOOLS_INTERNAL_LIBS} $(COM_ERR_LIBS) $(AIO_LIBS)

include $(TOPDIR)/Postamble.make
