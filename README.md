# rubypoint-task

The Rubypoint task.

## Documentation

The documentation for the Rubypoint task. This project was developed on Windows 11.

### CMake

Make sure to get CMake for your OS.

[CMake download](https://cmake.org/download/).

Used CMake version for this project: `3.24`. _(Was already available on my system.)_

### Visual Studio

**_Note: Tested and implemented with Visual Studio Community 2026._**

How to open the project using visual studio.

#### `File` -> `Open` -> `Folder`

The Visual Studio natively supports CMake.

[CMake support in Visual Studio](https://devblogs.microsoft.com/cppblog/cmake-support-in-visual-studio/).

This method should work with a Visual Studio 2017 and onwards. Otherwise, read on.

#### Cmake generators

Cmake may generate project which Visual Studio may understand. For the list of supported generators, open the link below.

[cmake-generators(7)](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)

Make sure to have the Visual Studio which matches the CMake generator which you want to use.

On my Windows 11 OS, running `cmake --help`, listed the following generators:

```powershell

  Visual Studio 17 2022        = Generates Visual Studio 2022 project files.
                                 Use -A option to specify architecture.
  Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 11 2012 [arch] = Generates Visual Studio 2012 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 10 2010 [arch] = Deprecated.  Generates Visual Studio 2010
                                 project files.  Optional [arch] can be
                                 "Win64" or "IA64".
  Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files.
                                 Optional [arch] can be "Win64" or "IA64".
```
