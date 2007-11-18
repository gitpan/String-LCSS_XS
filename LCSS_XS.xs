#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include "lcss.h"


MODULE = String::LCSS_XS		PACKAGE = String::LCSS_XS		


char *
lcss(s, t)
	char *	s
	char *	t
