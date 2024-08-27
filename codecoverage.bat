opencppcoverage ^
--verbose ^
--working_dir %~dp0build\Win64-Debug\ ^
--sources %~dp0\* ^
--modules %~dp0build\Win64-Debug* ^
-- %~dp0build\Win64-Debug\tst_viwebserver.exe