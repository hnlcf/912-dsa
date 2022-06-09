<div align="center">
    <h1> 912 DSA </h1>
    <i> A C++ implementation of 912 DSA. </i>
    <p></p>
    <img src="https://img.shields.io/github/workflow/status/hnlcf/912-dsa/Catch2%20Test?label=Catch2%20Test" alt="Catch2 Test">
    <img src="https://img.shields.io/github/issues/hnlcf/912-dsa" alt="Open issues">
    <img src="https://img.shields.io/github/license/hnlcf/912-dsa?color=blue" alt="License">
</div>

## Contents

- [Introduction](#introduction)
- [Feature](#feature)
    - [Classify](#classify)
    - [Todo](#todo)
- [Dependency](#dependency)
    - [Tools](#tools)
    - [Library](#library)
- [Install](#install)
- [QuickStart](#quickstart)
    - [Use scripts](#use-scripts)
    - [Manual](#manual)
- [License](#license)

## Introduction

- video: [DSA](https://www.xuetangx.com/course/THU08091000384/10322765?channel=i.area.learn_title)
- book: [Data Structures in C++](http://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/index.htm)

## Feature

### Classify

|  ID  |     Chapter      |                      Implementation                       |
|:----:|:----------------:|:---------------------------------------------------------:|
|  1   |   Introduction   |                        `Fibonacci`                        |
|  2   |      Vector      |           `Vector`, `Bitmap`, `BitmapQuickInit`           |
|  3   |       List       |                    `ListNode`, `List`                     |
|  4   | Stack and Queue  | `IStack`, `Stack`, `LinkedStack`,`StackExample`, `Queue`  |
|  5   |   Binary Tree    |                 `BinTreeNode`, `BinTree`                  |
| NaN  |      Other       |                        `Iterator`                         |

### Todo

- Data Structure
    - [x] `Vector`
    - [x] `Fibonacci`
    - [x] `Bitmap`
    - [x] `List`
    - [x] `Stack`(with `Vector`)
    - [x] `LinkedStack`(with `List`)
    - [x] `Queue`(with `List`)
    - [x] `Binary Tree`
    - [ ] `Graph`
    - [ ] `GraphMatrix`

## Dependency

### Tools

- conan
- cmake
- ninja
- python3

### Library

Using `catch2` which is managed by `conan` to test project.

- catch2

## Install

```shell
$ git clone https://github.com/hnlcf/912-dsa.git

$ cd 912-dsa
```

## QuickStart

### Use scripts

```shell
$ python3 tools.py --test
```

### Manual

1. Install dependency

```shell
$ mkdir build

$ conan install . -if=./build
```

2. Build project

```shell
$ cmake -G Ninja -S . -DCMAKE_BUILD_TYPE=Debug -B ./build

$ cmake --build ./build --config Debug --parallel 12 --target all
```

3. Run test

```shell
$ ./build/test/test -d yes --order lex
```

## License

[MIT](./LICENSE)
