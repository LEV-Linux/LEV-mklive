/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int instant = 0;
static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int fuzzy = 1;                      /* -F  option; if 0, dmenu doesn't use fuzzy matching     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"monospace:size=12"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
#define pywal "/home/salastro/.cache/wal/colors-wal-dmenu.h"

#if __has_include(pywal)
#include pywal
#else
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] =		{ "#fbf1c7", "#32302f" },
	[SchemeSel] =		{ "#fbf1c7", "#fb4934" },
	[SchemeSelHighlight] = 	{ "#8ec07c", "#fb4934" },
	[SchemeNormHighlight] =	{ "#8ec07c", "#32302f" },
	[SchemeOut] = 		{ "#fbf1c7", "#8ec07c" },
};
#endif
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
