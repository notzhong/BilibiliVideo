@echo off
set DestDir=.
set SourceFile1=..\bin\UrlManage_d.lib
set SourceFile2=..\bin\DownloadManage_d.lib
set SourceFile3=..\bin\LoadSettings_d.lib

echo run coping... 
copy %SourceFile1% %DestDir%
copy %SourceFile2% %DestDir%
copy %SourceFile3% %DestDir%

@pause