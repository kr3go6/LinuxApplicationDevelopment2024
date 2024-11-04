AM_CFLAGS = -Wall -Wextra -Werror

bin_PROGRAMS=rhasher
rhasher_SOURCES=src/rhasher.c
TESTS = sha1sum_test.sh md5sum_test.sh

gitclean:
	git clean -fd

sha1sum_test.sh:
	echo 'echo "BIG TESTY" > sha1_test.in' >> $@
	echo 'echo -n "> " > sha1_test.out' >> $@
	echo 'sha1sum sha1_test.in | cut -d " " -f 1 >> sha1_test.out' >> $@
	echo 'echo -n "Sha1 sha1_test.in" | ./rhasher | head -n 1 > rhasher_sha1.out' >> $@
	echo 'cmp sha1_test.out rhasher_sha1.out' >> $@
	chmod +x $@

md5sum_test.sh:
	echo 'echo "BIG TESTY" > md5_test.in' >> $@
	echo 'echo -n "> " > md5_test.out' >> $@
	echo 'md5sum md5_test.in | cut -d " " -f 1 >> md5_test.out' >> $@
	echo 'echo -n "Md5 md5_test.in" | ./rhasher | head -n 1 > rhasher_md5.out' >> $@
	echo 'cmp md5_test.out rhasher_md5.out' >> $@
	chmod +x $@
