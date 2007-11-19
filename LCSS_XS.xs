#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

/* shut up a compiler warning: ppport.h redefines
 *  * PERL_UNUSED_DECL already defined in perl.h */
#ifdef PERL_UNUSED_DECL
#   undef PERL_UNUSED_DECL
#endif

#include "ppport.h"

#include "lcss.h"

MODULE = String::LCSS_XS		PACKAGE = String::LCSS_XS		


char *
lcss(s, t)
	char *	s
	char *	t
