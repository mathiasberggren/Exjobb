# FIXME: before you push into master...
RUNTIMEDIR=/usr/bin/../include/omc/c/
#COPY_RUNTIMEFILES=$(FMI_ME_OBJS:%= && (OMCFILE=% && cp $(RUNTIMEDIR)/$$OMCFILE.c $$OMCFILE.c))

fmu:
	rm -f InvertedPendulum.fmutmp/sources/InvertedPendulum_init.xml
	cp -a "/usr/bin/../share/omc/runtime/c/fmi/buildproject/"* InvertedPendulum.fmutmp/sources
	cp -a InvertedPendulum_FMU.libs InvertedPendulum.fmutmp/sources/

