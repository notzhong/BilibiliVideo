@echo off
set DestDir=.
set SourceFile1=..\bin\UrlManage.lib
set SourceFile2=..\bin\DownloadManage.lib
set SourceFile3=..\bin\LoadSettings.lib

echo run coping... 
copy %SourceFile1% %DestDir%
copy %SourceFile2% %DestDir%
copy %SourceFile3% %DestDir%

@pause