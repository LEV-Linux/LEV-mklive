/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static       int enablegaps         = 1;        /* 1 means gaps are enabled by default */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no standard bar */
static const int topbar             = 1;        /* 0 means standard bar at bottom */
static const int extrabar           = 1;        /* 0 means no extra bar */
static const char statussep         = ';';      /* separator between statuses */
static const char *fonts[]          = { "monospace:size=12", "fontawesome:size=13", "JoyPixels:pixelsize=14" };
#define pywal "/home/salastro/.cache/wal/colors-wal-dwm.h"

#if __has_include(pywal)
#include pywal
#else
static const char norm_fg[] = "#9fb1c4";
static const char norm_bg[] = "#0D070D";
static const char norm_border[] = "#6f7b89";

static const char sel_fg[] = "#9fb1c4";
static const char sel_bg[] = "#495542";
static const char sel_border[] = "#9fb1c4";

static const char urg_fg[] = "#9fb1c4";
static const char urg_bg[] = "#553A48";
static const char urg_border[] = "#553A48";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
#endif

static const char *const autostart[] = {
    /* "sh", "-c", NULL, */
    "clipmenud", NULL,
    "dwmblocks", NULL,
    "numlockx", NULL,
    "picom", NULL,
    "sxhkd", NULL,
    "xss-lock", "slock", NULL,
    NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "💻", "🌐", "📼", "🏢", "📞", "🎮", "7", "8", "9", "10", "11", "12"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class,         instance, title,          tags mask,              isfloating, isterminal, noswallow, monitor */
    { "Firefox",      NULL,     NULL,           1  << 1,                0,          0,          -1,        -1 },
    { "Brave",        NULL,     NULL,           1  << 1,                0,          0,          0,         -1 },
    { "Chromium",     NULL,     NULL,           1  << 1,                0,          0,          0,         -1 },
    { "Tor Browser",  NULL,     NULL,           1                 << 1, 1,          0,          0,         -1 },
    { "chromium",     NULL,     NULL,           1  << 1,                0,          0,          0,         -1 },
    { "mpv",          NULL,     NULL,           1  << 2,                0,          0,          0,         -1 },
    { "vlc",          NULL,     NULL,           1  << 2,                0,          0,          0,         -1 },
    { "Soffice",      NULL,     NULL,           1  << 3,                0,          0,          0,         -1 },
    { "Telegram",     NULL,     NULL,           1  << 4,                0,          0,          0,         -1 },
    { "zoom",         NULL,     NULL,           1  << 4,                1,          0,          0,         -1 },
    { "Steam",        NULL,     NULL,           1  << 5,                1,          0,          0,         -1 },
    { "Virt-manager", NULL,     NULL,           1                 << 6, 0,          0,          0,         -1 },
    { "St",           NULL,     NULL,           0,                      0,          1,          0,         -1 },
    { NULL,           NULL,     "Event Tester", 0,                      0,          0,          1,         -1 },  /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "tabbed", "-r", "2", "st", "-w", "''", "-e", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key             function                argument */
	{ MODKEY|ShiftMask,             XK_Return,      togglescratch,          {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,           togglebar,              {0} },
	{ MODKEY,                       XK_j,           focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_j,           moveresize,             {.v = "0x 25y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_k,           moveresize,             {.v = "0x -25y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_l,           moveresize,             {.v = "25x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_h,           moveresize,             {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_j,           moveresize,             {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_k,           moveresize,             {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,           moveresize,             {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,           moveresize,             {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,          moveresizeedge,         {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,        moveresizeedge,         {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,        moveresizeedge,         {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,       moveresizeedge,         {.v = "r"} },
	{ MODKEY,                       XK_i,           incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,           incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,           setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,           setmfact,               {.f = +0.05} },
	{ MODKEY,                       XK_space,       zoom,                   {0} },
	{ MODKEY|ShiftMask,             XK_k,           setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_j,           setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,           setcfact,               {.f =  0.00} },
	{ MODKEY,                       XK_u,           incrgaps,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,           incrgaps,               {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,           togglegaps,             {0} },
	{ MODKEY,                       XK_o,           defaultgaps,            {0} },
	{ MODKEY|ControlMask,           XK_j,           pushdown,               {0} },
	{ MODKEY|ControlMask,           XK_k,           pushup,                 {0} },
	{ MODKEY,                       XK_Tab,         view,                   {0} },
	{ MODKEY,                       XK_c,           killclient,             {0} },
	{ Mod1Mask,                     XK_Tab,         shiftviewclients,       { .i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_Tab,         shiftviewclients,       { .i = -1 } },
	{ MODKEY,                       XK_t,           setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,           setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,           setlayout,              {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,           setlayout,              {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_m,           setlayout,              {.v = &layouts[13]} },
	{ MODKEY,                       XK_bracketleft, setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_bracketleft, togglefloating,         {0} },
	{ MODKEY|ControlMask,           XK_comma,       cyclelayout,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,      cyclelayout,            {.i = +1 } },
	{ MODKEY|ControlMask,           XK_s,           togglesticky,           {0} },
	{ MODKEY,                       XK_0,           view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,           tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,       focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,                 {.i = +1 } },
	{ MODKEY|ControlMask,           XK_f,           togglecanfocusfloating, {0} },
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	TAGKEYS(                        XK_8,                                   7)
	TAGKEYS(                        XK_9,                                   8)
	TAGKEYS(                        XF86XK_Launch5,                         9)
	TAGKEYS(                        XF86XK_Launch6,                         10)
	TAGKEYS(                        XF86XK_Launch7,                         11)
	{ MODKEY|ShiftMask,             XK_q,           quit,                   {0} },
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      dragmfact,      {0} },
	{ ClkClientWin,         MODKEY|ControlMask, Button1,      dragcfact,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};

