#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

/** @file bin_search.c
 * Implementation
 *
 * Gussing your number using binary search:
 * every time possible interval reduced in half
 * depending on your answer
 */

/** @brief Macros for gettext function from locale.h
 * 
 * This macros takes string and returns it translated
 *
 * @param STRING The text that should be translated
 * @return Text in target lamguage
 */
#define _(STRING) gettext(STRING)

/** @brief Macros for minimum number that can be guessed
 */
#define MIN 1

/** @brief Macros for maximum number that can be guessed
 */
#define MAX 100

/** @brief Macros for user input buffer size
 */
#define BUF_SIZE 16

/** @brief Roman numerals table
 */
static const char *roman_numerals[100] = {
    "I",    "II",   "III",  "IV",   "V",    "VI",   "VII",  "VIII", "IX",   "X",
    "XI",   "XII",  "XIII", "XIV",  "XV",   "XVI",  "XVII", "XVIII", "XIX", "XX",
    "XXI",  "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI",  "XLII",  "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI",   "LII",   "LIII",  "LIV",  "LV",   "LVI",  "LVII",  "LVIII", "LIX",  "LX",
    "LXI",  "LXII",  "LXIII", "LXIV", "LXV",  "LXVI",  "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI",  "XCII",  "XCIII", "XCIV", "XCV",  "XCVI",  "XCVII", "XCVIII", "XCIX", "C"
};

/** @brief Arabic to roman converter.
 * 
 * This function converts arabic number from 1 to 100 to roman
 *
 * @param arabic int
 * @return NULL if number not in [1, 100], string with roman number otherwise
 */
const char* arabicToRoman(const int arabic) {
    if (MIN <= arabic && arabic <= MAX) {
        return roman_numerals[arabic - 1];
    }

    return NULL;
}

/** @brief main
 * 
 * Possible flags:
 * 
 * -r: roman mode
 * -h (--help): get some help
 * 
 */
int main(int argc, char **argv)
{
    int is_roman = 0, is_help = 0;

    if (argc > 1) {
        is_roman = !strcmp(argv[1], "-r");
        is_help = !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help");
    }

    setlocale(LC_ALL, "");
    bindtextdomain("bin_search", ".");
    textdomain("bin_search");

    if (is_help) {
        printf(_("Gussing your number using binary search: "));
        printf(_("every time possible interval reduced in half"));
        printf(_("depending on your answer.\n\n"));
        printf(_("Usage: ./bin_search [-r] [-h]\n"));
        printf(_("\t-h:\tprint this help\n"));
        printf(_("\t--help\n"));
        printf(_("\t-r:\troman mode\n"));

        return 0;
    }

    int min = MIN, max = MAX, cur = (min + max) / 2;

    char input[BUF_SIZE];
    char num_str[BUF_SIZE];

    while (max - min > 0) {
        if (!is_roman) {
            sprintf(num_str, "%d", cur);
        }

        printf(_("is your number greater than %s? [yes/no]\n"), is_roman ? arabicToRoman(cur) : num_str);

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

    if (!is_roman) {
        sprintf(num_str, "%d", cur);
    }

    printf(_("your number is %s.\n"), is_roman ? arabicToRoman(cur) : num_str);

    return 0;
}
