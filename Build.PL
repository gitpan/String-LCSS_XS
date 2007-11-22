use 5.006_001;
use strict;
use warnings;

use Module::Build;

my $build = Module::Build->new(
    module_name       => 'String::LCSS_XS',
    dist_version_from => 'lib/String/LCSS_XS.pm',
    requires          => { 'Test::More' => 0, },
    dist_author       => 'Markus Riester <mriester@gmx.de>',
    license           => 'perl',
    c_source          => './',
    xs_files          => { 'LCSS_XS.xs' => 'lib/String/LCSS_XS.xs', },
);

$build->create_build_script;
