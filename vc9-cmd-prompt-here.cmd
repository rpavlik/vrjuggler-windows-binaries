rem Set VJ_BASE_DIR to the drive and path of this command script
set VJ_BASE_DIR=%~dp0

rem Set VJ_DEPS_DIR to be the same as VJ_BASE_DIR
set VJ_DEPS_DIR=%VJ_BASE_DIR%

rem Set the PATH to include both the bin and lib directories, so DLLs may be found.
set PATH=%VJ_BASE_DIR%bin;%VJ_BASE_DIR%lib

rem Run a command prompt that includes the Visual Studio 2008 settings.
%comspec% /k ""%VS90COMNTOOLS%vsvars32.bat""