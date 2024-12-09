AM_CFLAGS = -Wall -Wextra

CFLAGS = -Wall -Wextra
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

@DX_RULES@
doxygen-doc/man/man1/bin_search.c.1: doxygen-doc

man1_MANS = doxygen-doc/man/man1/bin_search.c.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http: doxygen-doc
	python3 -m http.server --directory $</html

bin_PROGRAMS=bin_search

all: /usr/local/share/locale/ru/LC_MESSAGES/bin_search.mo doxygen-doc

gitclean:
	git clean -xdf

ru.po: bin_search.c
	xgettext --keyword=_ --language=C --add-comments -o bin_search.pot bin_search.c
	msgmerge -U $@ bin_search.pot

/usr/local/share/locale/ru/LC_MESSAGES/bin_search.mo: ru.po
	mkdir -p /usr/local/share/locale/ru/LC_MESSAGES
	msgfmt ru.po -o $@

SUBDIRS = tests

checklog: check
	cat tests/*.log

gcov: check
	gcov -o .libs libbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
