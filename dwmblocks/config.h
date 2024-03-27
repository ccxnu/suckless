//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
  // {"⌨ ",   "kbselect",            0,                30},
	/* {"",	   "music",	              1,               	12}, */
	{"",	   "volume",	            0,               	10},
	{"",	   "battery",	            3,               	 3},
	/* {"",	   "clock",	             30,               	 1}, */
	/* {"",	   "tgredshift",	        0,               	15}, */
	{"",	   "brightness",	      0,               	 5},
	{"",	   "internet",	          5,               	 4},
};

//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = "  ";
