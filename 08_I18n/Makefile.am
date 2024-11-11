AM_CFLAGS = -Wall -Wextra

bin_PROGRAMS=bin_search

all: ru/LC_MESSAGES/bin_search.mo

gitclean:
	git clean -xdf

ru.po: bin_search.c
	xgettext --keyword=_ --language=C --add-comments -o bin_search.pot bin_search.c
	msgmerge -U $@ bin_search.pot

ru/LC_MESSAGES/bin_search.mo: ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt ru.po -o $@
