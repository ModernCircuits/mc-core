@echo on
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
@echo on

cd "%~dp0\.."
conan install -if cmake-build-release --build=missing -pr:b=default -pr:h=default -s compiler.cppstd=20 -s build_type=Release || goto :error
conan build -bf cmake-build-release || goto :error

goto :EOF
:error
exit /b 1
