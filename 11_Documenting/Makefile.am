AM_CFLAGS = -Wall -Wextra

@DX_RULES@
doxygen-doc/man/man1/bin_search.c.1: doxygen-doc

man1_MANS = doxygen-doc/man/man1/bin_search.c.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http: doxygen-doc
	python3 -m http.server --directory $</html

bin_PROGRAMS=bin_search

all: ru/LC_MESSAGES/bin_search.mo doxygen-doc

gitclean:
	git clean -xdf

ru.po: bin_search.c
	xgettext --keyword=_ --language=C --add-comments -o bin_search.pot bin_search.c
	msgmerge -U $@ bin_search.pot

ru/LC_MESSAGES/bin_search.mo: ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt ru.po -o $@
