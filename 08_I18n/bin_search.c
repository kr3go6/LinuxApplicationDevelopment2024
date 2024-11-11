#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

#define MIN 1
#define MAX 100
#define BUF_SIZE 16

int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain("bin_search", ".");
    textdomain("bin_search");

    int min = MIN, max = MAX, cur = (min + max) / 2;

    char input[BUF_SIZE];

    while (max - min > 0) {
        printf(_("is your number greater than %d? [yes/no]\n"), cur);

        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (input[strlen(input) - 1] != '\n') {
                for (int ch = getchar(); ch != '\n' && ch != EOF; ch = getchar());
            } else {
                input[strlen(input) - 1] = '\0';
            }
        }

        if (strncmp(input, _("yes"), BUF_SIZE) == 0) {
            min = cur + 1;
            cur = (min + max) / 2;
        } else if (strncmp(input, _("no"), BUF_SIZE) == 0) {
            max = cur;
            cur = (min + max) / 2;
        } else {
            printf(_("invalid input; please enter one word [yes] or [no].\n"));
        }
    }

    printf(_("your number is %d.\n"), cur);

    return 0;
}
