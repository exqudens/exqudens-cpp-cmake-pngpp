### How To Build With CMake

#### Windows

##### example-1:

```
cmake.exe -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - MinGW Makefiles" -S . -B build
cmake.exe --build build --target all -- -j 3
```

### Other

##### all build commands:
```
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - MinGW Makefiles" -S . -B build
cmake --build build --target clean -- -j 3
cmake --build build --target all -- -j 3
```
