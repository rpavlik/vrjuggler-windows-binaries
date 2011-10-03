set VJ_BASE_DIR=%~dp0
set VJ_DEPS_DIR=%VJ_BASE_DIR%
set PATH=%VJ_BASE_DIR%bin;%VJ_BASE_DIR%lib
%comspec% /k ""c:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"" x86