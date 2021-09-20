# st - simple terminal
# See LICENSE file for copyright and license details.

ifeq (${MAKECMDGOALS},rs90)
include config_rs90.mk
else
include config_rs97.mk
endif

SRC = st.c keyboard.c font.c msg_queue.c utf8_utils.c terminfo.c
OBJ = ${SRC:.c=.o}

all: options st libst-preload.so sdl_test

rs90: all

libst-preload.so: st-preload.o msg_queue.o
	${CC} -shared -o $@ $^

sdl_test: sdl_test.o

options:
	@echo st build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

config.h:
	cp config.def.h config.h

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

st: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f st ${OBJ} st-${VERSION}.tar.gz st-preload.o msg_queue.o libst-preload.so sdl_test.o

dist: clean
	@echo creating dist tarball
	@mkdir -p st-${VERSION}
	@cp -R LICENSE Makefile README config.mk config.def.h st.info st.1 ${SRC} st-${VERSION}
	@tar -cf st-${VERSION}.tar st-${VERSION}
	@gzip st-${VERSION}.tar
	@rm -rf st-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f st ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/st
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < st.1 > ${DESTDIR}${MANPREFIX}/man1/st.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/st.1
	@echo If things do not seem to work, be sure that there is no \
		floating st terminfo in the .terminfo directory in your home dir.
	@tic -s st.info

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/st
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/st.1

.PHONY: all options clean dist install uninstall
