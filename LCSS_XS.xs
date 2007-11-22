#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include "lcss.h"

MODULE = String::LCSS_XS		PACKAGE = String::LCSS_XS		

void
_compute_all_lcss(s, t)
	char *	s
	char *	t
PROTOTYPE: $$
ALIAS:
    lcss = 1
    lcss_all = 2
PREINIT:
    LCSS_RES res;
    int i;
    AV * ra;
PPCODE:
    res = _lcss(s,t);
    if (res.n <= 0) {
        _free_res(res);
        return XSRETURN_UNDEF;
    }
    else {
        if (GIMME_V == G_SCALAR) {
            EXTEND(sp, 1);
            PUSHs ( sv_2mortal ( newSVpv ( res.lcss[0].s, 0)));
        }
        else {
            if (ix == 1) {
                EXTEND(sp, 3);
                PUSHs ( sv_2mortal ( newSVpv ( res.lcss[0].s, 0)));
                PUSHs ( sv_2mortal ( newSViv ( res.lcss[0].pos_s)));
                PUSHs ( sv_2mortal ( newSViv ( res.lcss[0].pos_t)));
            }
            if (ix == 2) {
                EXTEND(sp, res.n);
                for (i=0; i< res.n; i++) {
                    ra = (AV *)sv_2mortal((SV *)newAV());
                    av_push( ra, newSVpv ( res.lcss[i].s, 0));
                    av_push( ra, newSViv ( res.lcss[i].pos_s));
                    av_push( ra, newSViv ( res.lcss[i].pos_t));
                    PUSHs ( sv_2mortal( newRV((SV *) ra )) );
                }    
            }
        }
    }
    _free_res(res);
