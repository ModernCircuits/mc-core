@echo on
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
@echo on

cd ..
cmake -S . -B cmake-build-release -G "Ninja Multi-Config" -D CMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17 -DMC_BUILD_WERROR=ON || goto :error
cmake --build cmake-build-release --config Release || goto :error

goto :EOF
:error
exit /b 1
