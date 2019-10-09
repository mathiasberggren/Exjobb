# FIXME: before you push into master...
RUNTIMEDIR=/usr/include/omc/c/
OMC_MINIMAL_RUNTIME=1
OMC_FMI_RUNTIME=1
include $(RUNTIMEDIR)/Makefile.objs
#COPY_RUNTIMEFILES=$(FMI_ME_OBJS:%= && (OMCFILE=% && cp $(RUNTIMEDIR)/$$OMCFILE.c $$OMCFILE.c))

fmu:
	rm -f InvertedPendulum.fmutmp/sources/InvertedPendulum_init.xml
	cp -a /usr/include/omc/c/* InvertedPendulum.fmutmp/sources/include/
	cp -a /usr/share/omc/runtime/c/fmi/buildproject/* InvertedPendulum.fmutmp/sources
	cp -a InvertedPendulum_FMU.libs InvertedPendulum.fmutmp/sources/

