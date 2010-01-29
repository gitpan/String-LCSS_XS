use Test::More tests => 4;
use strict;

use String::LCSS_XS qw(lcss);

my $s = "\x{263a}xyzz";
my $t = "abcxyzefg";

ok(utf8::is_utf8($s), "we are working with a utf8 strings");

my ($longest,$p1,$p2) = lcss ( $s, $t );
is ( $longest, "xyz", "xyzzx vs abcxyzefg" );
TODO: {
    local $TODO = "Fix this bug";
    is( $p1, 1, "position unicode string correct");
}
is( $p1, 3, "position non-unicode string correct");

