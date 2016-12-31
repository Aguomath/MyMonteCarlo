#****************************************************************************
# 需要采用多线程技术达到精度
#
# Makefile for Otf_doppler 
# Liu Xiongguo 
# 2015年 10月 14日 星期三 22:31:53 CST
#
# This is a GNU make (gmake) makefile
#****************************************************************************

# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG          := NO

# PROFILE can be set to YES to include profiling info, or NO otherwise
PROFILE        := NO

#****************************************************************************

CC               := gcc -g -lmath
CXX              := gcc
LD               := g++
AR               := ar rc
RANLIB           := ranlib

DEBUG_CFLAGS     :=   -g 
RELEASE_CFLAGS   :=    

LIBS		 :=

DEBUG_CXXFLAGS   := ${DEBUG_CFLAGS} 
RELEASE_CXXFLAGS := ${RELEASE_CFLAGS}

DEBUG_LDFLAGS    := -g
RELEASE_LDFLAGS  :=

ifeq (YES, ${DEBUG})
   CFLAGS        := ${DEBUG_CFLAGS}
   CXXFLAGS      := ${DEBUG_CXXFLAGS}
   LDFLAGS       := ${DEBUG_LDFLAGS}
else
   CFLAGS        := ${RELEASE_CFLAGS}
   CXXFLAGS      := ${RELEASE_CXXFLAGS}
   LDFLAGS       := ${RELEASE_LDFLAGS}
endif

ifeq (YES, ${PROFILE})
   CFLAGS   := ${CFLAGS} -pg -O3
   CXXFLAGS := ${CXXFLAGS} -pg -O3
   LDFLAGS  := ${LDFLAGS} -pg
endif

#****************************************************************************
# Include Paths
#****************************************************************************
INCS := 

#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

OUTPUT      := montecarlo

all: ${OUTPUT}

#****************************************************************************
# Source files
#****************************************************************************
#  fgetdata.c fgettoken.c finit.c fnewcell.c foutput.c  freadace.c freadgeometry.c fsimulate.c main.c

SRCS := fgetdata.c fgettoken.c finit.c fnewcell.c foutput.c freadace.c freadface.c freadgeometry.c freadmaterial.c fsimulate.c main.c
# Add on the sources for libraries
SRCS := ${SRCS}

OBJS := $(addsuffix .o,$(basename ${SRCS}))


#****************************************************************************
# Output
#****************************************************************************

${OUTPUT}: ${OBJS}
	${LD} -o $@ ${LDFLAGS} ${OBJS} ${LIBS} 

#****************************************************************************
# common rules
#****************************************************************************
# Rules for compiling source files to object files
#%.o : %.cpp
#	${CXX} -c ${DEBUG_CFLAGS} ${CXXFLAGS} ${INCS} $< -o $@
%.o : %.c
	${CC} -c ${DEBUG_CFLAGS} ${CFLAGS} ${INCS} $< -o $@   

dist:
	bash make distlinux

clean:
	rm -f  ${OUTPUT} ${OBJS}

#main.o : doppler_broaden.h
#ace.o : doppler_broaden.h
#c_bsigma.o : doppler_broaden.h 
#otf.o : doppler_broaden.h
#svdminfit.o : doppler_broaden.h
#ugrid_create.o : doppler_broaden.h
#utils.o : doppler_broaden.h

#fgetdata.o: header.h
#foutput.o: header.h
#freadgeometry.o: header.h
#main.o: header.h
#finit.o:header.h
#freadace.o:header.h
#fsimulate.o:header.h
#fgettoken.o: header.h
