![SML Logo](logo.png)

| **Platform** | **32 Bit** | **64 Bit** |
|---|---|---|
|**Linux (GCC)**         |[![Build status 32bit](https://ci.appveyor.com/api/projects/status/t9nhyqpo9eydrq36?svg=true)](https://ci.appveyor.com/project/Pitj3/sml) |[![Build status 64bit](https://ci.appveyor.com/api/projects/status/llf6vglm9lwxka6c?svg=true)](https://ci.appveyor.com/project/Pitj3/sml-mpl8y) |
|**Windows (MSVC)**         |[![Build status 32bit](https://ci.appveyor.com/api/projects/status/7yh9okxk0ed86a9v?svg=true)](https://ci.appveyor.com/project/Pitj3/sml-3lyt5) |[![Build status 64bit](https://ci.appveyor.com/api/projects/status/7gy2b6ueqhi2l35o?svg=true)](https://ci.appveyor.com/project/Pitj3/sml-ckq3k) |

# SML
#### Why SML?
SML(Simple Math Library) is a simple header only math library written in high performance C++.
SML aims to provide a easy to use open source implementation of all common math objects and functions.
Written in high performance C++ code with SIMD optimizations it offers high speed functionality for games and applications.

The library provides access to vec2, vec3, vec4, mat2, mat3, mat4 and quaternions (templated to allow for any variable type). SIMD optimalizations are implemented for all float and double types.

#### Requirements
- CPU with AVX support

#### Build Instructions
- Download repo
- Include header files in your project and make sure to enable AVX instructions


