<div align="center">
    <h1> 912 DSA </h1>
    <i> A C++ implementation of 912 DSA. </i>
    <p></p>
    <a href="https://github.com/hnlcf/912-dsa/actions/workflows/unit-test.yml">
        <img src="https://img.shields.io/github/workflow/status/hnlcf/912-dsa/Catch2%20Test?label=Catch2%20Test" alt="Catch2 Test">
    </a>
    <a href="https://github.com/hnlcf/912-dsa/issues">
        <img src="https://img.shields.io/github/issues/hnlcf/912-dsa" alt="Open issues">
    </a>
    <a href="https://github.com/hnlcf/912-dsa/blob/master/LICENSE">
        <img src="https://img.shields.io/github/license/hnlcf/912-dsa?color=blue" alt="License">
    </a>
</div>

## Contents

- [Introduction](#introduction)
- [Feature](#feature)
    - [Chapter Code](#chapter-code)
    - [Done](#done)
- [Dependency](#dependency)
    - [Tools](#tools)
    - [Library](#library)
- [QuickStart](#quickstart)
    - [Download](#download)
    - [Build](#build)
    - [Test](#test)
- [License](#license)

## Introduction

- video: [DSA](https://www.xuetangx.com/course/THU08091000384/10322765?channel=i.area.learn_title)
- book: [Data Structures in C++](http://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/index.htm)

## Feature

### Chapter Code

|  ID  |     Chapter      |                      Implementation                       |
|:----:|:----------------:|:---------------------------------------------------------:|
|  1   |   Introduction   |                        `Fibonacci`                        |
|  2   |      Vector      |           `Vector`, `Bitmap`, `BitmapQuickInit`           |
|  3   |       List       |                    `ListNode`, `List`                     |
|  4   | Stack and Queue  | `IStack`, `Stack`, `LinkedStack`,`StackExample`, `Queue`  |
|  5   |   Binary Tree    |                 `BinTreeNode`, `BinTree`                  |
| NaN  |      Other       |                        `Iterator`                         |

### Done

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

- cmake
- python3

### Library

Using `catch2` for testing.

- catch2

## QuickStart

### Download

```shell
$ git clone --recurse-submodules https://github.com/hnlcf/912-dsa.git

$ cd 912-dsa
```

### Build

```shell
$ mkdir -p build && cd build

$ cmake -DCMAKE_BUILD_TYPE=Release ..

$ cmake --build .
```

### Test

```shell
$ ctest -C Release --verbose
```

## License

[MIT](./LICENSE)
