TARGET    = demo

INC_DIRS += . 
INC_DIRS += ../inc

LIBS	 += -lpthread -lrt
LIBS	 += -L.. -lTask

CFLAGS    = -Wall
LDFLAGS   = $(LIBS)

C_FILES   = 
CPP_FILES = main.cpp

OBJ_DIR   = obj

INCS = $(addprefix -I, ${INC_DIRS})
OBJS += $(patsubst %.c, ${OBJ_DIR}/%.o, ${C_FILES})
OBJS += $(patsubst %.cpp, ${OBJ_DIR}/%.o, ${CPP_FILES})
DEPS = $(patsubst ${OBJ_DIR}/%.o, ${OBJ_DIR}/%.dep, ${OBJS})

BIN_DIR = $(dir ${TARGET})
OBJS_SUBDIRS = $(sort $(foreach OBJ, ${OBJS}, $(dir ${OBJ})))

CC = g++
LD = g++
TYPE = all

.PHONY: all clean

all: ${TARGET}

debug: CFLAGS += -g -DDEBUG
debug: TYPE = debug
debug: ${TARGET}
release: ${TARGET}

pre_make:
	mkdir -p ${BIN_DIR}
	mkdir -p ${OBJS_SUBDIRS}
	make -C ../ ${TYPE}

${TARGET}: pre_make ${OBJS}
	${LD} -o $@ ${OBJS} ${LDFLAGS}
	@echo 
	@echo "<Tips> Build '$(TARGET)' success!"
	@echo 

${OBJ_DIR}/%.o: %.c
	${CC} -o $@ -c $< -MMD -MP -MF $(@:%.o=%.dep) -MT $@ ${CFLAGS} ${INCS}

${OBJ_DIR}/%.o: %.cpp
	${CC} -o $@ -c $< -MMD -MP -MF $(@:%.o=%.dep) -MT $@ ${CFLAGS} ${INCS}

clean:
	make clean -C ../
	rm -rf ${TARGET} ${OBJS} ${DEPS} ${OBJS_SUBDIR} ${OBJ_DIR}
	@echo 
	@echo "<Tips> clean complete!"
	@echo 

-include ${DEPS}
