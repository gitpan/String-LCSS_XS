package String::LCSS_XS;

#use 5.008006;
use strict;
use warnings;

require Exporter;

our @ISA = qw(Exporter);

our @EXPORT = qw(
	lcss	
);

our $VERSION = '0.02';

require XSLoader;
XSLoader::load('String::LCSS_XS', $VERSION);

1;
__END__

=head1 NAME

String::LCSS_XS - Find The Longest Common Substring of Two Strings.

=head1 SYNOPSIS

  use String::LCSS_XS;
  
  my $longest = lcss ( "zyzxx", "abczyzefg" );
  print $longest, "\n";

=head1 DESCRIPTION


String::LCSS_XS computes the Longest Common Substring shared by two strings.
It is a C implementation of L<String::LCSS> and uses a dynamic programming 
algorithm with both runtime and memory usage of O(mn). 

=head1 EXPORT

 char* lcss(char* s, char* t)

=head1 PERFORMANCE

  my $s = 'i pushed the lazy dog into a creek, the quick brown fox told me to';
  my $t = 'the quick brown fox jumps over the lazy dog';

                    Rate    String::LCSS String::LCSS_XS
 String::LCSS     42.5/s              --           -100%
 String::LCSS_XS 32609/s          76628%              --
  
=head1 BUGS AND LIMITATIONS

Probably many. 

If there are multiple lcss (with the same length), then this implementation
returns only the first
found.

String::LCSS_XS currently does not support L<String::LCSS> feature in list
context where it returns the lcss positions. 

L<String::LCSS> returns undef when the lcss has size 1. String::LCSS_XS
returns this single character.

=head1 CREDITS

Daniel Yacob has written L<String::LCSS>. I stole his API, test suite and
SYNOPSIS.

=head1 SEE ALSO

L<String::LCSS> - A pure perl implementation (but O(n^3) runtime)

Gusfield, Dan. I<Algorithms on Strings, Trees and Sequences: Computer Science
and Computational Biology>. USA: Cambridge University Press. 
ISBN 0-521-58519-8. 


=head1 AUTHOR

Markus Riester, E<lt>mriester@gmx.deE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2007 by Markus Riester

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.8.6 or,
at your option, any later version of Perl 5 you may have available.


=cut
