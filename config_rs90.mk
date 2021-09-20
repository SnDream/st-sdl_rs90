# st version
VERSION = 0.3

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS = -I. 
LIBS = -lc -lutil

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS += -g -Wall ${INCS} ${CPPFLAGS} -DRS90 -fPIC
LDFLAGS += -g ${LIBS} -lSDL

# compiler and linker
CC = /opt/rs90-toolchain/usr/bin/mipsel-rs90-linux-musl-gcc
