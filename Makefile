# From https://github.com/danielpinto8zz6/c-cpp-project-generator#readme

CC = gcc
CFLAGS := -Wall -Wextra -std=gnu89 -g
LFLAGS =
OUTPUT := output
SRC := src
INCLUDE := include
LIB := lib

ifeq ($(OS),Windows_NT)
MAIN := main.exe
SOURCEDIRS := $(SRC)
INCLUDEDIRS := $(INCLUDE)
LIBDIRS := $(LIB)
FIXPATH = $(subst /,\,$1)
RM := del /q /f
MD := mkdir
else
MAIN := main
SOURCEDIRS := $(shell find $(SRC) -type d)
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
LIBDIRS := $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD := mkdir -p
endif

INCLUDES := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
LIBS := $(patsubst %,-L%, $(LIBDIRS:%/=%))
SOURCES := $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS := $(SOURCES:.c=.o)
OUTPUTMAIN := $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing "all" complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	@echo Cleanup complete!


progress_bar_test:
	$(CC) $(CFLAGS) -c src/probar.c -o src/probar.o $(INCLUDES) $(LFLAGS) $(LIBS)
	$(CC) $(CFLAGS) src/progress_bar_test.c $(INCLUDES) -o $(OUTPUT)/progress_bar_test src/probar.o $(LFLAGS) $(LIBS)
	./$(OUTPUT)/progress_bar_test
	@echo progress_bar_test is done

progress_indicator_test:
	$(CC) $(CFLAGS) -c src/probar.c -o src/probar.o $(INCLUDES) $(LFLAGS) $(LIBS)
	$(CC) $(CFLAGS) src/progress_indicator_test.c $(INCLUDES) -o $(OUTPUT)/progress_indicator_test src/probar.o $(LFLAGS) $(LIBS)
	./$(OUTPUT)/progress_indicator_test
	@echo progress_indicator_test is done
