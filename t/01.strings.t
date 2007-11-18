use Test::More qw(no_plan);
use strict;

use String::LCSS_XS;


my $longest = lcss ( "xyzzx", "abcxyzefg" );
is ( $longest, "xyz", "xyzzx vs abcxyzefg" );

$longest = lcss ( "abcxyzzx", "abcxyzefg" );
is ( $longest, "abcxyz", "abcxyzzx vs abcxyzefg" );

$longest = lcss ( "foobar", "abcxyzefg" );
is ( $longest, 'a', "foobar vs abcxyzefg" );

my $needle = "i pushed the lazy dog into a creek, the quick brown fox told me to";
my $haystack = "the quick brown fox jumps over the lazy dog";

$longest = lcss ( $needle, $haystack );
is ( $longest, "the quick brown fox ", "the quick brown fox" );

$longest = lcss ( $haystack, $needle );
is ( $longest, "the quick brown fox ", "the quick brown fox (reverse args)" );

$haystack = "why did the quick brown fox jumps over the lazy dog";
$longest = lcss ( $needle, $haystack );
is ( $longest, " the quick brown fox ", "why did the quick brown fox" );

