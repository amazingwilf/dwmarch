/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx		= 2;
static const unsigned int snap			= 32;
static int floatposgrid_x				= 5;
static int floatposgrid_y				= 5;
static const int swallowfloating		= 0;
static const int swterminheritfs		= 1;
static const char *toggle_float_pos		= "50% 50% 80% 80%"; 

static const int showbar				= 1;
static const int topbar					= 1;
static const char buttonbar[]			= "󰤆 ";

#define ICONSIZE (bh - 12)
#define ICONSPACING 12


static const unsigned int gappih		= 10;
static const unsigned int gappiv		= 10;
static const unsigned int gappoh		= 10;
static const unsigned int gappov		= 10;
static int smartgaps					= 0;

static const char *fonts[]				= { "Noto Sans:style=Condensed Medium:size=13",
											"JetBrainsMono Nerd Font:size=17",
											"Noto Sans:size=12",
											"JetBrainsMono Nerd Font:style=ExtraBold:size=11" };

static char normfgcolor[]				= "#bbbbbb";
static char normbgcolor[]				= "#222222";
static char normbordercolor[]			= "#444444";

static char selfgcolor[]				= "#eeeeee";
static char selbgcolor[]				= "#005577";
static char selbordercolor[]			= "#005577";

static char floatfgcolor[]				= "#eeeeee";
static char floatbgcolor[]				= "#005577";
static char floatbordercolor[]			= "#005577";

static char scratchfgcolor[]			= "#bbbbbb";
static char scratchbgcolor[]			= "#222222";
static char scratchbordercolor[]		= "#007799";

static char stickyfgcolor[]				= "#bbbbbb";
static char stickybgcolor[]				= "#222222";
static char stickybordercolor[]			= "#007799";

static char emptyfgcolor[]				= "#444444";
static char emptybgcolor[]				= "#222222";
static char emptybordercolor[]			= "#007799";

static char occfgcolor[]				= "#bbbbbb";
static char occbgcolor[]				= "#222222";
static char occbordercolor[]			= "#007799";

static char stbuttonfgcolor[]			= "#eeeeee";
static char stbuttonbgcolor[]			= "#222222";
static char ltsymbolfgcolor[]			= "#0088aa";
static char ltsymbolbgcolor[]			= "#222222";

static char *colors[][3]	= {
	[SchemeNorm]		= { normfgcolor,		normbgcolor,		normbordercolor },
	[SchemeSel]			= { selfgcolor,			selbgcolor,			selbordercolor },
	[SchemeFloat]		= { floatfgcolor,		floatbgcolor,		floatbordercolor },
	[SchemeScratch]		= { scratchfgcolor,		scratchbgcolor,		scratchbordercolor },
	[SchemeSticky]		= { stickyfgcolor,		stickybgcolor,		stickybordercolor },
	[SchemeEmpty]		= { emptyfgcolor,		emptybgcolor,		emptybordercolor },
	[SchemeOcc]			= { occfgcolor,			occbgcolor,			occbordercolor },
	[SchemeStButton]	= { stbuttonfgcolor,	stbuttonbgcolor,	"#000000" },
	[SchemeLtSymbol]	= { ltsymbolfgcolor,	ltsymbolbgcolor,	"#000000" },
};
static const char *const autostart[] = {
	"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"nitrogen", "--restore", NULL,
	"picom", "-b", NULL,
	"slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const unsigned int ulinepad		= 5;	
static const unsigned int ulinestroke	= 2;
static const unsigned int ulinevoffset	= 0;
static const int ulineall 				= 0;

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Lxappearance", .isfloating = 1, .floatpos = "50% 50% -1h -1w" },
	{ .class = "Archlinux-logout.py", .isfloating = 1 },
	{ .class = "firefox", .tags = 1 << 1 },
	{ .class = "spterm", .scratchkey = 't', .isfloating = 1, .floatpos = "50% 50% 80% 80%" },
	{ .class = "Alacritty", .isterminal = 1 },
	{ .title = "Event Tester", .noswallow = 1 },
};

/* layout(s) */
static const float mfact		= 0.50; 
static const int nmaster		= 1;
static const int resizehints 	= 0;
static const int lockfullscreen	= 1;

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol	arrange function */
	{ "[]=",	tile },
	{ "><>",	NULL },
	{ "[M]",	monocle },
	{ "[@]",	spiral },
	{ "[\\]",	dwindle },
	{ "D[]",	deck },
	{ "TTT",	bstack },
	{ "===",	bstackhoriz },
	{ "HHH",	grid },
	{ "###",	nrowgrid },
	{ "---",	horizgrid },
	{ ":::",	gaplessgrid },
	{ "|M|",	centeredmaster },
	{ ">M>",	centeredfloatingmaster },
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,						KEY,	view,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,			KEY,	toggleview,	{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,				KEY,	tag,		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,	KEY,	toggletag,	{.ui = 1 << TAG} },

#define STATUSBAR "dwmblocks"

/* commands */
static const char *termcmd[]	= { "alacritty", "-T", "Terminal", NULL };
static const char *roficmd[]	= { "rofi", "-show", "drun", NULL };
static const char *ffcmd[]		= { "firefox", NULL };
static const char *logoutcmd[]	= { "archlinux-logout", NULL };
static const char *lockcmd[]	= { "betterlockscreen", "-l", NULL };

static const char *sptermcmd[]	= { "t", "alacritty", "--class", "spterm,spterm", NULL };

#include <X11/XF86keysym.h>
static const char *mutevol[]	= { "volume", "--toggle", NULL };
static const char *mutemic[]	= { "volume", "--toggle-mic", NULL };
static const char *upvol[]		= { "volume", "--inc", NULL };
static const char *downvol[]	= { "volume", "--dec", NULL };
static const char *upbl[]		= { "brightness", "--inc", NULL };
static const char *downbl[]		= { "brightness", "--dec", NULL };



static const Key keys[] = {
	/* modifier	key		function	argument */
	{ MODKEY,				XK_Return, 					spawn,				{.v = termcmd } },
	{ MODKEY,				XK_space,					spawn,				{.v = roficmd } },
	{ MODKEY,				XK_w,						spawn,				{.v = ffcmd } },
	{ MODKEY,				XK_x,						spawn,				{.v = logoutcmd } },
	{ MODKEY,				XK_l,						spawn,				{.v = lockcmd } },

	{ MODKEY,				XK_grave,					togglescratch,		{.v = sptermcmd } },

	{ 0, 					XF86XK_AudioMute, 			spawn, 				{.v = mutevol } },
	{ 0, 					XF86XK_AudioMicMute, 		spawn, 				{.v = mutemic } },
	{ 0, 					XF86XK_AudioLowerVolume, 	spawn, 				{.v = downvol } },
	{ 0, 					XF86XK_AudioRaiseVolume, 	spawn, 				{.v = upvol } },
	{ 0, 					XF86XK_MonBrightnessUp, 	spawn, 				{.v = upbl } },
	{ 0, 					XF86XK_MonBrightnessDown, 	spawn, 				{.v = downbl } },

	{ MODKEY,				XK_j,						focusstack,			{.i = +1 } },
	{ MODKEY,				XK_k,						focusstack,			{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_j,						rotatestack,		{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_k,						rotatestack,		{.i = -1 } },
	{ MODKEY,				XK_i,						incnmaster,			{.i = +1 } },
	{ MODKEY,				XK_d,						incnmaster,			{.i = -1 } },
	{ MODKEY,				XK_h,						setmfact,			{.f = -0.05} },
	{ MODKEY,				XK_l,						setmfact,			{.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_h,						setcfact,			{.f = +0.25} },
	{ MODKEY|ShiftMask,		XK_l,						setcfact,			{.f = -0.25} },
	{ MODKEY|ShiftMask,		XK_o,						setcfact,			{.f =	0.00} },
	{ MODKEY,				XK_bracketright,			incrgaps,			{.i = +1 } },
	{ MODKEY,				XK_bracketleft,				incrgaps,			{.i = -1 } },
	{ MODKEY|ShiftMask,		XK_g,						togglegaps,			{0} },
	{ MODKEY|ControlMask,	XK_g,						defaultgaps,		{0} },
	{ MODKEY,				XK_q,						killclient,			{0} },
	{ MODKEY|ShiftMask,		XK_q,						quit,				{0} },
	{ MODKEY|ShiftMask, 	XK_r,						quit,				{1} }, 
	{ MODKEY,				XK_t,						setlayout,			{.v = &layouts[0]} },
	{ MODKEY,				XK_f,						setlayout,			{.v = &layouts[1]} },
	{ MODKEY,				XK_m,						setlayout,			{.v = &layouts[2]} },
	{ MODKEY,				XK_b,						setlayout,			{.v = &layouts[6]} },
	{ MODKEY,				XK_comma,					cyclelayout,		{.i = -1 } },
	{ MODKEY,				XK_period,					cyclelayout,		{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_space,					togglefloating,		{0} },
	{ MODKEY|ShiftMask,		XK_f,						togglefullscr,		{0} },
	{ MODKEY|ShiftMask,		XK_b,						togglebar,			{0} },
	{ MODKEY|ShiftMask,		XK_s,						togglesticky,		{0} },
	{ MODKEY|ShiftMask,		XK_x,						xrdb,				{.v = NULL } },
	{ MODKEY,				XK_0,						view,				{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,						tag,				{.ui = ~0 } },
	{ MODKEY,				XK_Right,					viewnext,			{0} },
	{ MODKEY,				XK_Left,					viewprev,			{0} },
	{ MODKEY|ShiftMask,		XK_Right,					tagtonext,			{0} },
	{ MODKEY|ShiftMask,		XK_Left,					tagtoprev,			{0} },
	TAGKEYS(				XK_1,											0)
	TAGKEYS(				XK_2,											1)
	TAGKEYS(				XK_3,											2)
	TAGKEYS(				XK_4,											3)
	TAGKEYS(				XK_5,											4)
	TAGKEYS(				XK_6,											5)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click	event mask	button	function	argument */
	{ ClkButton,		0,			Button1,	spawn,			{.v = logoutcmd } },
	{ ClkLtSymbol,		0,			Button1,	setlayout,		{0} },
	{ ClkLtSymbol,		0,			Button3,	setlayout,		{.v = &layouts[2]} },
	{ ClkWinTitle,		0,			Button2,	zoom,			{0} },
	{ ClkStatusText,	0,			Button1,	sigstatusbar,	{.i = 1} },
	{ ClkStatusText,	0,			Button2,	sigstatusbar,	{.i = 2} },
	{ ClkStatusText,	0,			Button3,	sigstatusbar,	{.i = 3} },
	{ ClkStatusText,	0,			Button4,	sigstatusbar,	{.i = 4} },
	{ ClkStatusText,	0,			Button5,	sigstatusbar,	{.i = 5} },
	{ ClkClientWin,		MODKEY,		Button1,	movemouse,		{0} },
	{ ClkClientWin,		MODKEY,		Button2,	togglefloating, {0} },
	{ ClkClientWin,		MODKEY,		Button3,	resizemouse,	{0} },
	{ ClkTagBar,		0,			Button1,	view,			{0} },
	{ ClkTagBar,		0,			Button3,	toggleview,		{0} },
	{ ClkTagBar,		MODKEY,		Button1,	tag,			{0} },
	{ ClkTagBar,		MODKEY,		Button3,	toggletag,		{0} },
};

