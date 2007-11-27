use 5.006_001;
use ExtUtils::MakeMaker;

WriteMakefile(
    NAME              => 'String::LCSS_XS',
    VERSION_FROM      => 'lib/String/LCSS_XS.pm', 
    PREREQ_PM         => {
        'XSLoader'   => 0,
        'Exporter'   => 0,
        'Test::More' => 0,
    }, 
    ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM  => 'lib/String/LCSS_XS.pm', # retrieve abstract from module
       AUTHOR         => 'Markus Riester <mriester@gmx.de>') : ()),
    ((ExtUtils::MakeMaker->VERSION() gt '6.30') ?
            ('LICENSE'  => 'perl')         : ()),
    LIBS              => [''], 
    DEFINE            => '-I ../..', 
    INC               => '-I.', 
    OBJECT            => '$(O_FILES)', 
    clean             =>  { FILES => 'String-LCSS_XS-*' },
);
