/* =====================================
  @author: Pablo Cuenca
  @url: https://github.com/cuencapablo
===================================== */

/*  Constants */

#define TERMINAL "st"
#define TERMCLASS "St"
/* #define BROWSER "qutebrowser" */

/*  Appearance */

static unsigned int borderpx = 1; /* border pixel of windows and border or screen */
static unsigned int snap = 0; /* snap pixel */
static unsigned int gappih = 0; /* horiz inner gap between windows */
static unsigned int gappiv = 0; /* vert inner gap between windows */
static unsigned int gappoh = 0; /* horiz outer gap between windows and screen edge */
static unsigned int gappov = 0; /* vert outer gap between windows and screen edge */
static int swallowfloating = 0; /* 1 means swallow floating windows by default */
static int smartgaps = 1; /* 1 means no outer gap when there is only one window */
static int showbar = 0; /* 0 means no bar */
static int topbar = 1;  /* 0 means bottom bar */

/*  Fonts  */

static char *fonts[] = {
    "JetBrainsMono Nerd Font:size=10:antialias=true:autohint=true",
    "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true",
};

static char normbgcolor[] = "#000000";
static char normbordercolor[] = "#1D1D1D";
static char normfgcolor[] = "#bdc3af"; // white

static char selfgcolor[] = "#a38a5b";
static char selbordercolor[] = "#841a5c"; // Red
static char selbgcolor[] = "#000000";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

/* Tagging */

static const char *tags[] = {" ", " ", " "};

/*  Terminal cmd rule */

typedef struct {
  const char *name;
  const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL};
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "FiraCode Nerd Font:size=20", "-g", "35x12", "-e", "bc", "-lq", NULL};
const char *spcmd3[] = {TERMINAL, "-n", "spclok", "-g", "37x09", "-e", "tty-clock", "-C", "7", NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm", spcmd1},
    {"spcalc", spcmd2},
    {"spclok", spcmd3},
};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* Class-Instance-Title-Tags-Mask-Isfloating-Isterminal-Noswallow-Monitor */
    {"Google-chrome", NULL,         NULL,   1 << 1, 0, 0, 0, -1},
    {"Inkscape",      NULL,         NULL,   1 << 2, 0, 0, 0, -1},
    {"thunar",        NULL,         NULL,   1 << 2, 0, 0, 0, -1},
    {TERMCLASS,       NULL,         NULL,        0, 0, 1, 0, -1},
    {TERMCLASS,       "floatterm",  NULL,        0, 1, 1, 0, -1},
    {TERMCLASS,       "bg",         NULL,   1 << 7, 0, 1, 0, -1},
    {TERMCLASS,       "spterm",     NULL, SPTAG(0), 1, 1, 0, -1},
    {TERMCLASS,       "spcalc",     NULL, SPTAG(1), 1, 1, 0, -1},
    {TERMCLASS,       "spclok",     NULL, SPTAG(2), 1, 1, 0, -1},
};

/* Layout(s) */

static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1 /* force two clients to always split vertically */
#include "options/vanitygaps.c"

static const Layout layouts[] = {
    /* symbol arrange function */
    {"[]=", tile},                   /* Default: Master on left, slaves on right */
    {"TTT", bstack},                 /* Master on top, slaves on bottom */
    {"[M]", monocle},                /* All windows on top of eachother */
    {"H[]", deck},                   /* Master on left, slaves in monocle-like mode on right */
    {"|M|", centeredmaster},         /* Master in middle, slaves on sides */
    {">M>", centeredfloatingmaster}, /* Same but master floats */
    {"><>", NULL},                   /* no layout function means floating behavior */
};

/* Key definitions */
#define MODALT Mod1Mask               /* Alt Key */
#define ALTSHIFT Mod1Mask | ShiftMask /* Alt + Shift */
#define MODKEY Mod4Mask               /* Super Key*/
#define TAGKEYS(KEY, TAG)                                                  \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                   \
  {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
  {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
  {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define STACKKEYS(MOD, ACTION)                                             \
  {MOD, XK_l, ACTION##stack, {.i = INC(+1)}},                              \
  {MOD, XK_h, ACTION##stack, {.i = INC(-1)}},                              \
  {MOD, XK_v, ACTION##stack, {.i = 0}},                                    \
  /* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
  /* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
  /* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
  /* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd){ .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }

/* Dmenu */

static char dmenufont[] = "JetBrainsMono Nerd Font:size=10:antialias=true:autohint=true";
static char dmenumon[2] = "0";
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,        "-fn",
                                 dmenufont,   "-nb", normbgcolor,     "-nf",
                                 selfgcolor,  "-sb", normbordercolor, "-sf",
                                 normfgcolor, NULL};
static const char *termcmd[] = {TERMINAL, NULL};

/* Xresources (on login) */

ResourcePref resources[] = {
    {"color0", STRING, &normbordercolor},
    {"color8", STRING, &selbordercolor},
    {"color0", STRING, &normbgcolor},
    {"color4", STRING, &normfgcolor},
    {"color0", STRING, &selfgcolor},
    {"color4", STRING, &selbgcolor},
    {"borderpx", INTEGER, &borderpx},
    {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},
    {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},
    {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},
    {"gappih", INTEGER, &gappih},
    {"gappiv", INTEGER, &gappiv},
    {"gappoh", INTEGER, &gappoh},
    {"gappov", INTEGER, &gappov},
    {"swallowfloating", INTEGER, &swallowfloating},
    {"smartgaps", INTEGER, &smartgaps},
};

/* Preferences */

#include "options/shiftview.c"
#include <X11/XF86keysym.h>

static const char *lf[] = {TERMINAL, "-n", "lf", "-e", "lf", NULL};
static const char *lock[] = {"/usr/bin/betterlockscreen", "-l", "dimblur", NULL};
static const char *btop[] = {TERMINAL, "-n", "btop", "-e", "btop", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)

  /* ALT KEYMAPS */

	/* { ALTSHIFT,    XK_f,	          	spawn,		{.v = (const char*[]){ BROWSER, NULL } } }, // Firefox */
	{ ALTSHIFT,     XK_c,	          	spawn,		{.v = (const char*[]){ "google-chrome-stable", NULL } } }, // Chrome
	{ ALTSHIFT,     XK_t,	          	spawn,		{.v = (const char*[]){ "thunar", NULL } } }, // Thunar
	{ ALTSHIFT,     XK_i,	          	spawn,		{.v = (const char*[]){ "inkscape", NULL } } }, // Inkscape

  /* TAGS */

	TAGKEYS(  XK_ampersand,    0)
	TAGKEYS(  XK_bracketleft,  1)
	TAGKEYS(  XK_braceleft,    2)

  /* PERSONAL APPS KEYMAPS */

	{ MODKEY,	   	XK_r,       spawn,    {.v = lf } }, // lf
	{ MODKEY,     XK_d,       spawn,    {.v = dmenucmd } }, // dmenu
	{ MODKEY,	   XK_F5,       spawn,    {.v = lock } }, // betterlockscreen
	{ MODKEY,    XK_F7,       spawn,    {.v = btop } }, // btop
	{ MODKEY,    XK_F4,       spawn,    {.v = (const char*[]){ "pavucontrol" , NULL } } }, // Pavucontrol

  /* PERSONAL SCRIPTS KEYMAPS */

	{ MODKEY|ShiftMask,  XK_BackSpace,  spawn,  {.v = (const char*[]){ "sysact", NULL } } }, // Systemt control
	{ MODKEY|ShiftMask,  XK_s,          spawn,  {.v = (const char*[]){ "capture", NULL } } }, // Screenshot

  // FLOATING WINDOWS

	{ MODKEY|ShiftMask,		  XK_Return,	    togglescratch,	{.ui = 0} },
	{ MODKEY,			          XK_apostrophe,	togglescratch,  {.ui = 1} },
	{ MODKEY,			          XK_semicolon,	  togglescratch,  {.ui = 2} },
	{ MODKEY,			          XK_Return,	    spawn,		      {.v = termcmd } },

  /* LAYOUTS KEYMAPS */

	{ MODKEY,		        	XK_t,		setlayout,	{.v = &layouts[0]} },	/* tile si */
	{ MODKEY|ShiftMask,		XK_t,		setlayout,	{.v = &layouts[1]} },	/* bstack */
	{ MODKEY,		        	XK_m,		setlayout,	{.v = &layouts[2]} },	/* monocle si */
	{ MODKEY|ShiftMask,	 	XK_m,		setlayout,	{.v = &layouts[3]} },	/* deck si*/
	{ MODKEY,			        XK_c,		setlayout,	{.v = &layouts[4]} },	/* centeredmaster */
	{ MODKEY|ShiftMask,		XK_c,	 	setlayout,  {.v = &layouts[5]} }, /* centeredfloatingmaster */
	{ MODKEY|ShiftMask,	  XK_v, 	setlayout,	{0} },

  /* GENERAL SYSTEM KEYMAPS */

	{ MODKEY,			        XK_Tab,		        view,		        {0} },
	{ MODKEY|ShiftMask,		XK_w,	        	  killclient,     {0} },
	{ MODKEY,			        XK_f,	        	  togglefullscr,  {0} },
	{ MODKEY,		        	XK_space,	        zoom,		        {0} },
	{ MODKEY,			        XK_plus,    	    shiftview,      { .i = -1 } },
	{ MODKEY,			        XK_bracketright,	shiftview,	    { .i = +1 } },
	{ MODKEY,		        	XK_j,	          	setmfact,	      { .f = -0.05 } },
	{ MODKEY,			        XK_k,		          setmfact,       { .f = +0.05 } },

  /* WINDOW GAPS */

	{ MODKEY|ShiftMask,		XK_a,		        defaultgaps,	  {0} },
	{ MODKEY,			        XK_s,		        togglesticky,	  {0} },
	{ MODKEY,			        XK_z,		        incrgaps,	      {.i = +2 } },
	{ MODKEY,			        XK_x,	        	incrgaps,	      {.i = -2 } },
	{ MODKEY,			        XK_b,		        togglebar,    	{0} },

  /* EXTERNAL MONITOR */
	{ MODKEY|ShiftMask,   XK_plus,	         focusmon,    {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_bracketright,   focusmon,    {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_Left,	           tagmon,    {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_Right,	           tagmon,    {.i = +1 } },

  /* AUDIO OUTPUT SPEAKER/HEADPHONE */
	{ MODKEY,  XK_F2,  spawn,  SHCMD("pacmd set-sink-port alsa_output.pci-0000_00_1b.0.analog-stereo analog-output-speaker") },
	{ MODKEY,  XK_F3,  spawn,  SHCMD("pacmd set-sink-port alsa_output.pci-0000_00_1b.0.analog-stereo analog-output-headphones") },

  /* Fn Keymaps */

	{ 0, XF86XK_AudioMute,		       spawn,		      SHCMD("amixer -q -D pulse sset Master toggle; pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioRaiseVolume,	   spawn,		      SHCMD("amixer -q -D pulse sset Master 5%+; pkill -RTMIN+10 dwmblocks")},
	{ 0, XF86XK_AudioLowerVolume,	   spawn,		      SHCMD("amixer -q -D pulse sset Master 5%-; pkill -RTMIN+10 dwmblocks")},

	{ 0, XF86XK_MonBrightnessUp,	   spawn,		      SHCMD("light -A 5; pkill -RTMIN+5 dwmblocks") },
	{ 0, XF86XK_MonBrightnessDown,	 spawn,		      SHCMD("light -U 5; pkill -RTMIN+5 dwmblocks") },

	{ 0, XF86XK_AudioPrev,		       spawn,		      SHCMD("playerctl previous; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_AudioNext,		       spawn,		      SHCMD("playerctl next; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_AudioPause,		       spawn,		      SHCMD("playerctl play-pause; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_AudioPlay,		       spawn,		      SHCMD("playerctl play-pause; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_AudioStop,		       spawn,		      SHCMD("playerctl stop; pkill -RTMIN+12 dwmblocks") },

	{ 0, XF86XK_AudioRewind,	       spawn,		      {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	{ 0, XF86XK_AudioForward,	       spawn,		      {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	{ 0, XF86XK_AudioMedia,		       spawn,		      {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ 0, XF86XK_AudioMicMute,	       spawn,		      SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,	           spawn,		      {.v = (const char*[]){ "sysact", NULL } } },
	{ 0, XF86XK_Calculator,		       spawn,		      {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,	             spawn,		      {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	{ 0, XF86XK_DOS,	               spawn,		      {.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,	       spawn,		      SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,		         spawn,		      {.v = (const char*[]){ TERMINAL, "-e", "btop", NULL } } },
	{ 0, XF86XK_Mail,		             spawn,		      SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_Launch1,	           spawn,		      {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,	     spawn,		      SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	       spawn,		      {.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0, XF86XK_TouchpadOn,	         spawn,		      {.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },

};

static const Button buttons[] = {
#ifndef __OpenBSD__
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, sigdwmblocks, {.i = 1}},
    {ClkStatusText, 0, Button2, sigdwmblocks, {.i = 2}},
    {ClkStatusText, 0, Button3, sigdwmblocks, {.i = 3}},
    {ClkStatusText, 0, Button4, sigdwmblocks, {.i = 4}},
    {ClkStatusText, 0, Button5, sigdwmblocks, {.i = 5}},
    {ClkStatusText, ShiftMask, Button1, sigdwmblocks, {.i = 6}},
#endif
    {ClkStatusText, ShiftMask, Button3, spawn,
     SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h")},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, defaultgaps, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, incrgaps, {.i = +1}},
    {ClkClientWin, MODKEY, Button5, incrgaps, {.i = -1}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    // { ClkTagBar,		0,		Button4,	shiftview,
    // {.i = -1}
    // }, { ClkTagBar,		0,		Button5,	shiftview,
    // {.i = 1} },
    {ClkRootWin, 0, Button2, togglebar, {0}},
};
