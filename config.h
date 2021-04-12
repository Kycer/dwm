/* See LICENSE file for copyright and license details. */

#define SCRIPT_PATH "/home/kycer/.dotfiles/scripts"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Source Han Sans CN:size=16" };
static const char dmenufont[]       = "Source Han Sans CN:size=16";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#A162F7";
static char selbgcolor[]            = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

// autostart
static const char *const autostart[] = {
	"sh", "-c", SCRIPT_PATH"/autostart.sh", NULL,
	"sh", "-c", SCRIPT_PATH"/dwm_bar/bar.sh", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      						instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     							NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  							NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Chromium",  							NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Google-chrome",  				NULL,       NULL,       1 << 1,       0,           -1 },
	{ "jetbrains-idea",  				NULL,       NULL,       1 << 4,       0,           -1 },
	{ "dingtalk",  							NULL,       NULL,       1 << 6,       0,           -1 },
	{ "electronic-wechat",  		NULL,       NULL,       1 << 7,       0,           -1 },
	{ "netease-cloud-music",  	NULL,       NULL,       1 << 8,       0,           -1 },
	{ "fcitx5-config-qt",  			NULL,       NULL,       0,						1,           -1 },
	{ "flameshot",  						NULL,       NULL,       0,						1,           -1 },
	{ "Sxiv",  									NULL,       NULL,       0,						1,           -1 },
	{ "Zathura",  							NULL,       NULL,       0,						1,           -1 },
	{ "Display",  							NULL,       NULL,       0,						1,           -1 },
	{ "feh",  									NULL,       NULL,       0,						1,           -1 },
	{ "Pavucontrol",  					NULL,       NULL,       0,						1,           -1 },
	{ "Postman",  							NULL,       NULL,       0,						1,           -1 },
	{ "qv2ray",  								NULL,       NULL,       0,						1,           -1 },
	{ "Pcmanfm",  							NULL,       NULL,       0,						1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

// scratchpad
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_o,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,             					XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("rofi -show drun") },
	{ MODKEY,                       XK_e, 		 spawn,  				 SHCMD("st -e ranger") },
	{ MODKEY|ShiftMask,             XK_u, 		 spawn,  				 SHCMD(SCRIPT_PATH"/vol.sh -u") },
	{ MODKEY|ShiftMask,             XK_d, 		 spawn,  				 SHCMD(SCRIPT_PATH"/vol.sh -d") },
	{ MODKEY|ShiftMask,             XK_m, 		 spawn,  				 SHCMD(SCRIPT_PATH"/vol.sh -m") },
	{ MODKEY|ShiftMask,             XK_t, 		 spawn,  				 SHCMD(SCRIPT_PATH"/traye-tg.sh") },
	{ MODKEY|ShiftMask,             XK_x, 		 spawn,  				 SHCMD("betterlockscreen -l dim") },
	{ MODKEY|ShiftMask,             XK_s, 		 spawn,  				 SHCMD("flameshot gui") },
	{ MODKEY|ShiftMask,             XK_e, 		 spawn,  				 SHCMD("pcmanfm") },
	{ MODKEY|ShiftMask,             XK_q, 		 spawn,  				 SHCMD(SCRIPT_PATH"/rofi/powermenu.sh") },
	{ MODKEY|ShiftMask,             XK_c, 		 spawn,  				 SHCMD(SCRIPT_PATH"/wallpapers.sh c") },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_n,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_v,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_u, 		 zoom,           {0} },

	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,					              XK_w,      killclient,     {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,             					XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_equal,  incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_equal,  incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_minus,  incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_equal,  incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_minus,  incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,  incrovgaps,     {.i = -1 } },


	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },

	{ 0, XF86XK_AudioMute,				spawn,		SHCMD(SCRIPT_PATH"/vol.sh -m") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD(SCRIPT_PATH"/vol.sh -u") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD(SCRIPT_PATH"/vol.sh -d") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_MonBrightnessDown,spawn,		SHCMD("xbacklight -dec 10") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

