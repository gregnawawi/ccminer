# allow to use Host cuda functions in C/C++
#DEF_INCLUDES = @CUDA_INCLUDES@

if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/compat/jansson
else
JANSSON_INCLUDES=
endif

EXTRA_DIST		= autogen.sh README.md README.txt LICENSE.txt \
			  coco.sln coco.vcxproj coco.vcxproj.filters \
			  compat/gettimeofday.c compat/getopt/getopt_long.c

SUBDIRS = compat

bin_PROGRAMS = coco

coco_SOURCES	= elist.h monir.h compat.h \
			  compat/inttypes.h compat/stdbool.h compat/unistd.h bignum.cpp bignum.hpp \
			  compat/sys/time.h compat/getopt/getopt.h \
			  crc32.c \
			  coco.cpp pools.cpp util.cpp bench.cpp \
			  api.cpp hashlog.cpp stats.cpp sysinfos.cpp \
			  equi/equi-stratum.cpp veros/verosscan.cpp \
			  veros/haraka.c veros/veros_clhash.cpp



if HAVE_WINDOWS
coco_SOURCES += compat/winansi.c
endif

coco_LDFLAGS  = $(PTHREAD_FLAGS)
coco_LDADD    = @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@ @OPENMP_CFLAGS@ @LIBS@ 
coco_CPPFLAGS = @LIBCURL_CPPFLAGS@ @OPENMP_CFLAGS@ $(CPPFLAGS) $(PTHREAD_FLAGS) -march=native -fno-strict-aliasing $(JANSSON_INCLUDES) $(DEF_INCLUDES)

if HAVE_OSX
coco_CPPFLAGS += -I/usr/local/llvm/lib/clang/4.0.0/include
coco_LDFLAGS += -L/usr/local/llvm/lib
coco_LDADD += -lomp
endif




