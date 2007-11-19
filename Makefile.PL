#use 5.008006;
use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
    NAME              => 'String::LCSS_XS',
    VERSION_FROM      => 'lib/String/LCSS_XS.pm', # finds $VERSION
    PREREQ_PM         => {}, # e.g., Module::Name => 1.1
    ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM  => 'lib/String/LCSS_XS.pm', # retrieve abstract from module
       AUTHOR         => 'Markus Riester <mriester@gmx.de>') : ()),
    LIBS              => [''], # e.g., '-lm'
    DEFINE            => '-I ../..', # e.g., '-DHAVE_SOMETHING'
    INC               => '-I.', # e.g., '-I. -I/usr/include/other'
	# Un-comment this if you add C files to link with later:
    OBJECT            => '$(O_FILES)', # link all the C files too
);
