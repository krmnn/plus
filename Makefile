# plus, derived from dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = plus.c
OBJ = ${SRC:.c=.o}

all: options plus

options:
	@echo plus build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h: config.def.h
	@echo creating $@ from config.def.h
	@cp config.def.h $@

plus: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f plus ${OBJ} plus-${VERSION}.tar.gz config.h plus.o

dist: clean
	@echo creating dist tarball
	@mkdir -p plus-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk \
		${SRC} plus-${VERSION}
	@tar -cf plus-${VERSION}.tar plus-${VERSION}
	@gzip plus-${VERSION}.tar
	@rm -rf plus-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f plus ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/plus

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/plus

.PHONY: all options clean dist install uninstall
