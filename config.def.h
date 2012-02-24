/* See LICENSE file for copyright and license details. */

/* font */
static const char font[]            = "-*-helvetica-medium-r-*-*-12-*-*-*-*-*-*-*";

/* colors */
static const char normbordercolor[] = "#2b2b2b";
static const char normbgcolor[]     = "#ffffff";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#295083";
static const char selbgcolor[]      = "#295083";
static const char selfgcolor[]      = "#ffffff";
static const char* colors[NumColors][ColLast] = {
    // border          foreground   background
    { normbordercolor, normfgcolor, normbgcolor },  // normal
    { selbordercolor,  selfgcolor,  selbgcolor  },  // selected
    { normbordercolor, normfgcolor, "#73d216"    },  // warning
    { normbordercolor, selfgcolor,  "#4c4c4c"  },  // error
    { "#dadada",       selfgcolor,  "#000000"  },  // delim
    { normbordercolor, normfgcolor, "#ef2929" },  // hot red
    { normbordercolor, normfgcolor, "#edd400" },  // medium yellow
    { normbordercolor, normfgcolor, "#73d216" },  // cool green
};


static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const int maxbarheight			= 20;

static const Bool systray_enable	= True;
static const int systray_spacing	= 3;


/* tagging */
static const char *tags[] = { "term", "web", "dev", "media", "vm", "rdesktop", "misc"};

static const Rule rules[] = {
    /* class            instance    title       tags mask     isfloating   monitor */
    { "Gimp",           NULL,       NULL,       0,            True,        -1 },
    { "Firefox",        NULL,       NULL,       1 << 1,       False,       -1 },
    { "Google-chrome",  NULL,       NULL,       1 << 1,       False,       -1 },
    { "Eclipse",        NULL,       NULL,       1 << 2,       False,       -1 },
    { NULL,             "urxvt",    "krmnn.de", 1 << 0,       False,       -1 },
    { NULL,             "urxvt",    "chantal",  1 << 0,       False,       -1 },
    { NULL,             "urxvt",    "mephisto", 1 << 0,       False,       -1 },
    { "Virt-manager",   NULL,       NULL,       1 << 4,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[tile]",     tile },    /* first entry is default */
    { "[float]",    NULL },    /* no layout function means floating behavior */
    { "[monocle]",  monocle },
    { "[grid]",     gaplessgrid },
    { "[bstack]",   bstack },
    { "[hstack]",   bstackhoriz },
};



/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,           	XK_k,      cycle,       {.i = -1 } },
    { MODKEY|ShiftMask,           	XK_j,      cycle,       {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        focusonclick,   {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

