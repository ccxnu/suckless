/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#000000",     /* after initialization */
	[INPUT] =  "#090012",   /* during input */
	[FAILED] = "#290A08",   /* wrong password */
};

/* lock screen opacity */
static const float alpha = 0.85;

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* default message */
//static const char * message = " It's okay to live hard.";

static const char * message =
    "      |\\      _,,,---,,_\n"
    "ZZZzz /,`.-'`'    -.  ;-;;,_\n"
    "     |,4-  ) )-,_. ,\\ (  `'-'\n"
    "    '---''(_/--'  `-'\\_)  ccxnu\n"
    "\n"
    "     It's okay to live hard";

/* text color */
static const char * text_color = "#ffffff";

/* text size (must be a valid size) */
static const char * font_name = "JetBrainsMono Nerd Font Mono:pixelsize=24:antialias=true:autohint=true";
