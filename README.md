### ReadMe
#### Windows 编译
> Debug版本
- `mkdir build` 
- `cd build` 
- `mkdir debug` 
- `cd debug`
- `cmake -G "Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=E:/develop/cpp/package/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_INSTALL_PREFIX=../../install/debug ../..`

> Release版本
- `mkdir build` 
- `cd build` 
- `mkdir release` 
- `cd release`
- `cmake -G "Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=E:/develop/cpp/package/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x86-windows-static -DCMAKE_INSTALL_PREFIX=../../install/debug ../..`


### Linux编译
> Debug版本
- `mkdir build` 
- `cd build` 
- `mkdir debug` 
- `cd debug`
- `cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux -DCMAKE_INSTALL_PREFIX=../../install/debug ../..`

> Release版本
- `mkdir build` 
- `cd build` 
- `mkdir release` 
- `cd release`
- `cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux -DCMAKE_INSTALL_PREFIX=../../install/release ../..`
- 