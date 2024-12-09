GENERATES = prog README liboutput_static.a liboutput.so
TRASH = *.o *~ o.* prog prog-a prog-so out*.txt
CFLAGS = -Wall -fPIC
LDFLAGS = -L.

all:    README prog

.SECONDARY:	fun.o const.o
.INTERMEDIATE:	libout_static.a(fun.o const.o)

prog:	prog.o fun.o const.o

prog-a:	prog.o liboutput_static.a
	cc $(CFLAGS) $(LDFLAGS) prog.o liboutput_static.a -o prog-a

prog-so:	prog.o liboutput.so
	cc $(CFLAGS) $(LDFLAGS) prog.o liboutput.so -o prog-so

README: prog
	./$< 2> $@

fun.o prog.o:  outlib.h

clean:
	rm -rf $(TRASH) $(GENERATES)

liboutput_static.a: liboutput_static.a(fun.o const.o)

liboutput.so: fun.o const.o
	cc $(CFLAGS) $(LDFLAGS) fun.o const.o -shared -o liboutput.so

test: prog prog-a prog-so
	./prog > out1_prog.txt 2>&1
	./prog-a > out1_proga.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > out1_progso.txt 2>&1

	./prog workit > out2_prog.txt 2>&1
	./prog-a workit > out2_proga.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so workit > out2_progso.txt 2>&1

	./prog harder makeit better > out3_prog.txt 2>&1
	./prog-a harder makeit better > out3_proga.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so harder makeit better > out3_progso.txt 2>&1

	cmp out1_prog.txt out1_proga.txt && cmp out1_proga.txt out1_progso.txt
	cmp out2_prog.txt out2_proga.txt && cmp out2_proga.txt out2_progso.txt
	cmp out3_prog.txt out3_proga.txt && cmp out3_proga.txt out3_progso.txt
	echo "do it faster makes us stronger (ok)"
