NAME=game
VERSION_MAJOR=0
VERSION_MINOR=0

CXX=g++
CONFIG = -D CORE_CONFIG \
	-D PROJECT_NAME=\"${NAME}\"\
	-D VERSION_MAJOR=${VERSION_MAJOR} \
	-D VERSION_MINOR=${VERSION_MINOR} \
	-D WINDOW_WIDTH=800 \
	-D WINDOW_HEIGHT=600 \
	-D VERBOSE_UNHANDLED_EVENTS \
	-D USE_SDL2_IMAGE \
	#-D USE_SDL2_NET \
	#-D USE_SDL2_TTF

__CXXFLAGS=-Og -g -std=c++17 \
	-Wall -Wextra -pedantic \
	-pthread \
	-lSDL2 \
	-lSDL2_image \
	#-lSDL2_ttf \
	#-lSDL2_mixer \
	#-lSDL2_net

LDXX=ldd


IDIR=src
SDIR=src
BDIR=bin
ODIR=obj
DDIR=dep
ASSETS_DIR=assets

_CXXFLAGS = ${__CXXFLAGS} ${CONFIG} -I${IDIR} -I${ODIR}/${IDIR} ${CXXFLAGS}
SRC = $(shell find ${SDIR} -type f -name '*.cpp' -o -name ".backup" -prune -type f)
OBJ = $(patsubst ${SDIR}/%.cpp,${ODIR}/%.o,${SRC})
DEP = $(patsubst ${SDIR}/%.cpp,${DDIR}/%.dep,${SRC})
ASSETS = $(shell find ${ASSETS_DIR} -type f -o -name ".backup" -prune -type f)
#NEW_ASSETS = $(patsubst %,${BDIR}/%, ${ASSETS})

ifndef VERBOSE
.SILENT:
endif

build: depend ${SRC} ${BDIR}/${NAME} assets # ctags

${DEP}: ${DDIR}/%.dep: ${SDIR}/%.cpp
	mkdir -p ${DDIR}
	echo "Calculating dependencies for $<"
	mkdir -p $$(dirname $@)
	${CXX} ${_CXXFLAGS} $< -MM -MP -MT $(patsubst ${SDIR}/%.cpp,${ODIR}/%.o,$<) > $@

depend: ${DEP}
include ${DEP}

${OBJ}: ${ODIR}/%.o: ${SDIR}/%.cpp makefile
	# mkdir -p ${ODIR}
	echo "Compiling $@"
	mkdir -p $$(dirname $@)
	${CXX} -c -o $@ $< ${_CXXFLAGS}

${BDIR}/${NAME}: ${OBJ}
	mkdir -p ${BDIR}
	echo "Linking ${NAME}"
	$(CXX) -o $@ ${OBJ} ${_CXXFLAGS}

clean:
	echo "Cleaning build files"
	rm -r ${ODIR} ${DDIR}
	# rm tags

run: build
	echo "Running ${NAME}"
	cd ${BDIR} && ./${NAME} $(ARGS)

ctags: ${SRC}
	echo "Generating ctags"
	ctags -R ${IDIR} ${SDIR}

assets: ${BDIR}/${ASSETS_DIR}/STAMP

${BDIR}/${ASSETS_DIR}/STAMP: ${ASSETS}
	if [ -d "${BDIR}/${ASSETS_DIR}" ]; then \
		rm -r "${BDIR}/${ASSETS_DIR}"; \
	fi
	cp -r "${ASSETS_DIR}" "${BDIR}/${ASSETS_DIR}"
	echo "Preparing assets"
	cd ${BDIR}/${ASSETS_DIR}
	if [ -f "./prepare.sh" ]; then \
		./prepare.sh; \
	fi
	touch $@


CFG_FILES = $(shell find ${IDIR} -type f -name '*.hpp.in' -o -name ".backup" -prune -type f)
CFG_PARSED = $(patsubst ${IDIR}/%.hpp.in,${ODIR}/${IDIR}/%.hpp,${CFG_FILES})

config: ${CFG_PARSED}

${CFG_PARSED}: ${ODIR}/${IDIR}/%.hpp : ${IDIR}/%.hpp.in
	mkdir -p ${ODIR}/${IDIR}
	mkdir -p $$(dirname $@)
	echo "Creating empty $@"
	touch $@ -d "$$(stat -c %y $<)"

