# SuperSoft Soft Clipper

Initial JUCE VST3/AU plugin scaffold for the **SoftClipper** project.

## What's included

- JUCE CMake project setup
- Basic plugin processor/editor classes
- Simple soft-clipping DSP module (`tanh`-based)
- Drive and output gain parameters

## Setup JUCE (submodule)

From repository root:

```bash
git submodule add https://github.com/juce-framework/JUCE.git JUCE
git submodule update --init --recursive
```

If the submodule already exists, you only need:

```bash
git submodule update --init --recursive
```

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```
