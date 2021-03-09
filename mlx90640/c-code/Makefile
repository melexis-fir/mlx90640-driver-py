.PHONY: clean all

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

CC=gcc
AR=ar

DEP_LIBS:=
# DEP_LIBS+=-lm
DEP_LIB_PATH:=
SHARED_LIB_NAME:=mlx90640_driver
STATIC_LIB_NAME:=mlx90640_driver_static

STATIC_LIB_FILE:=lib$(STATIC_LIB_NAME).a
SHARED_LIB_FILE:=lib$(SHARED_LIB_NAME).so

LIB_RESULT_DIR:=../libs

ifeq ($(detected_OS),Windows)
SHARED_LIB_FILE:=$(SHARED_LIB_NAME).dll
MACHINE:=windows
else
MACHINE:=$(shell uname -m)
endif

CFLAGS:=-Wall -Wextra -Wstrict-prototypes -Wunused-result -O3 -std=c99 -fmessage-length=0 -fPIC -Iinc
CFLAGS+=$(CFLAGS_EXTRA)


all: $(SHARED_LIB_FILE) $(STATIC_LIB_FILE)

clean:
	rm -f main *.o
	rm -f src/*.o
	rm -f $(SHARED_LIB_FILE) $(STATIC_LIB_FILE)

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^

src/MLX90640_API.o: src/MLX90640_API.c
	$(CC) -c -o $@ $(CFLAGS) $^

src/mlx90640_driver_register.o: src/mlx90640_driver_register.c
	$(CC) -c -o $@ $(CFLAGS) $^


main: main.o src/MLX90640_API.o src/mlx90640_driver_register.o
	$(CC) -o $@ $^ -lm -Wl,-rpath=$(LIB_RESULT_DIR)/$(MACHINE) -L$(LIB_RESULT_DIR)/$(MACHINE) $(DEP_LIBS)


$(SHARED_LIB_FILE): src/MLX90640_API.o src/mlx90640_driver_register.o
	$(CC) -shared -o $@ $^ -L../libs/$(MACHINE) $(DEP_LIBS) -Wl,-rpath=../libs/$(MACHINE)
	@mkdir -p $(LIB_RESULT_DIR)/$(MACHINE)
	@cp -fv $@ $(LIB_RESULT_DIR)/$(MACHINE)

$(STATIC_LIB_FILE): src/MLX90640_API.o src/mlx90640_driver_register.o
	$(AR) rcu $@ $<
	@mkdir -p $(LIB_RESULT_DIR)/$(MACHINE)
	@cp -fv $@ $(LIB_RESULT_DIR)/$(MACHINE)
