CC = gcc
CFLAGS = -Wall -Werror -Wextra -O2

INFILE = _test_infile.txt
PROTECT_INFILE = _test_PROTECT_infile.txt
OUTFILE = _test_outfile.txt

all: move protect.so

move: move.c

protect.so:
	$(CC) $(CFLAGS) protect.c -shared -o protect.so

clean:
	@rm -f move protect.so
	$(call clean-test-files)

define clean-test-files =
	@rm -f ${INFILE} ${PROTECT_INFILE} ${OUTFILE}
endef

test-ok: move
	$(call clean-test-files)
	@echo "Big testy" > ${INFILE}
	@./move ${INFILE} ${OUTFILE} || test $$? -eq 0
	@test -f ${INFILE} ; test $$? -eq 1
	@test -f ${OUTFILE} ; test $$? -eq 0
	$(call clean-test-files)
	@echo "[OK] test-ok"

test-wrong-argc: move
	$(call clean-test-files)
	@echo "Big testy" > ${INFILE}
	@./move ${INFILE} 2> /dev/null || test $$? -eq 1
	$(call clean-test-files)
	@echo "[OK] test-wrong-argc"

test-open-readfile: move
	$(call clean-test-files)
	@echo "Big testy" > ${INFILE}
	@strace -e fault=openat:error=EPERM:when=1 -P ${INFILE} ./move ${INFILE} ${OUTFILE} 2> /dev/null || test $$? -eq 2
	@test -f ${INFILE} ; test $$? -eq 0
	@test -f ${OUTFILE} ; test $$? -eq 1
	$(call clean-test-files)
	@echo "[OK] test-infile-open"

test-open-new-writefile: move
	$(call clean-test-files)
	@echo "Big testy" > ${INFILE}
	@strace -e fault=openat:error=EPERM:when=1 -P ${OUTFILE} ./move ${INFILE} ${OUTFILE} 2> /dev/null || test $$? -eq 2
	@test -f ${INFILE} ; test $$? -eq 0
	@test -f ${OUTFILE} ; test $$? -eq 1
	$(call clean-test-files)
	@echo "[OK] test-open-new-writefile"

test-open-existing-writefile: move
	$(call clean-test-files)
	@echo "Big testy" > ${INFILE}
	@echo "stub" > ${OUTFILE}
	@strace -e fault=openat:error=EPERM:when=1 -P ${OUTFILE} ./move ${INFILE} ${OUTFILE} 2> /dev/null || test $$? -eq 2
	@test -f ${INFILE} ; test $$? -eq 0
	@test -f ${OUTFILE} ; test $$? -eq 0
	$(call clean-test-files)
	@echo "[OK] test-open-existing-writefile"

test-read: move
	$(call clean-test-files)
	@echo "Big testy" > ${INFILE}
	@strace -e fault=read:error=EPERM:when=1 -P ${INFILE} ./move ${INFILE} ${OUTFILE} 2> /dev/null || test $$? -eq 4
	@test -f ${INFILE} ; test $$? -eq 0
	@test -f ${OUTFILE} ; test $$? -eq 1
	$(call clean-test-files)
	@echo "[OK] test-read"

test-write: move
	$(call clean-test-files)
	@echo "Big testy" > ${INFILE}
	@strace -e fault=write:error=EPERM:when=1 ./move ${INFILE} ${OUTFILE} 2> /dev/null || test $$? -eq 3
	@test -f ${INFILE} ; test $$? -eq 0
	@test -f ${OUTFILE} ; test $$? -eq 1
	$(call clean-test-files)
	@echo "[OK] test-write"

test-protect: move protect.so
	$(call clean-test-files)
	@echo "Big testy" > ${PROTECT_INFILE}
	@LD_PRELOAD=./protect.so ./move ${PROTECT_INFILE} ${OUTFILE}
	@test $$? -eq 0
	@test -f ${PROTECT_INFILE} ; test $$? -eq 0
	@test -f ${OUTFILE} ; test $$? -eq 0
	$(call clean-test-files)
	@echo "[OK] test-write"

test: test-ok test-wrong-argc test-open-readfile test-open-new-writefile test-open-existing-writefile test-read test-write test-protect
