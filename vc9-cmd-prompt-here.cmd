set VJ_BASE_DIR=%~dp0
set VJ_DEPS_DIR=%VJ_BASE_DIR%
set PATH=%VJ_BASE_DIR%bin;%VJ_BASE_DIR%lib
%comspec% /k ""%VS90COMNTOOLS%vsvars32.bat""