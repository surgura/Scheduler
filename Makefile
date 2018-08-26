CC := gcc
all: build test

.PHONY: test
test:
	${MAKE} -C test

build: libdir lib

libdir:
	mkdir -p lib

lib: obj/scheduler.o
	ar rcs lib/libscheduler.a obj/scheduler.o

objdir:
	mkdir -p obj

obj/scheduler.o: objdir
	${CC} -c src/scheduler.c -o obj/scheduler.o -Iinclude/scheduler

clean:
	rm -r obj
	rm -r lib