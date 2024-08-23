opencppcoverage ^
--verbose ^
--sources %~dp0core\* ^
--sources %~dp0tests\* ^
--modules %~dp0build\Win64-Debug* ^
--working_dir %~dp0 ^
--cover_children ^
-- %~dp0build\Win64-Debug\tst_viwebserver.exe