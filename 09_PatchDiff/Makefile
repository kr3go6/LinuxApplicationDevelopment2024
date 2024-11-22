CFLAGS = -Wall -Werror -Wextra

GENERATES = labirintus_v1.c labirintus_v1 labirintus_v2.c labirintus_v2 labirintus_v3.c labirintus_v3

labirintus_v1.c:
	@patch labirintus.c < v1.patch -o labirintus_v1.c

labirintus_v2.c:
	@patch labirintus.c < v2.patch -o labirintus_v2.c

labirintus_v3.c:
	@patch labirintus.c < v3.patch -o labirintus_v3.c

labirintus_v1: labirintus_v1.c

labirintus_v2: labirintus_v2.c

labirintus_v3: labirintus_v3.c


gen: labirintus_v1 labirintus_v2 labirintus_v3

run: gen
	./labirintus_v1 8
	@echo
	./labirintus_v2 " #" 5
	@echo
	./labirintus_v3 42 "#." 6
	@echo

gitclean:
	git clean -xdf

clean:
	rm -f $(GENERATES)
