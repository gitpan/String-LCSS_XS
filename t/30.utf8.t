use Test::More tests => 9;
use strict;

use String::LCSS_XS qw(lcss);

my $s = "\x{263a}xyzz";
my $t = "abcxyzefg";

ok(utf8::is_utf8($s), "we are working with a utf8 strings");

my ($longest,$p1,$p2) = lcss ( $s, $t );
is ( $longest, "xyz", "xyzzx vs abcxyzefg" );
is( $p1, 1, "position unicode string correct");
is ( index($s, 'xyz'), 1, "index function returns correct position");
is( $p2, 3, "position non-unicode string correct");

$t = "abc\x{263a}xyzefg";
($longest,$p1,$p2) = lcss ( $s, $t );
TODO: {
    local $TODO = "Why is this not working";
    ok(utf8::is_utf8($longest), "we got an utf8 string");
    is( $longest , "\x{263a}xyz", "xyzzx vs abcxyzefg" );
}
is( $p1, 0, "position unicode string correct");
is( $p2, 3, "position non-unicode string correct");
