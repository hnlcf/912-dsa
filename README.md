<div align="center">
    <h1> 912 DSA </h1>
    <i> A C++ implementation of 912 DSA. </i>
    <p></p>
    <a href="https://github.com/hnlcf/912-dsa/actions/workflows/build.yml">
        <img src="https://img.shields.io/github/workflow/status/hnlcf/912-dsa/CI?label=CI" alt="CI">
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
- [Features](#features)
- [Download](#download)
- [Dependency](#dependency)
    - [Tools](#tools)
    - [Library](#library)
- [QuickStart](#quickstart)
    - [Using script](#using-script)
    - [Manual](#manual)
- [License](#license)

## Introduction

This is a code implementation of **912 DSA**, which is a data structure course offered by **Tsinghua
University**.

- video: [DSA](https://www.xuetangx.com/course/THU08091000384/10322765?channel=i.area.learn_title)
- book: [Data Structures in C++](http://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/index.htm)

## Features

|  ID  |       Chapter       |                      Implementation                       |
|:----:|:-------------------:|:---------------------------------------------------------:|
|  1   |    Introduction     |                        `Fibonacci`                        |
|  2   |       Vector        |           `Vector`, `Bitmap`, `BitmapQuickInit`           |
|  3   |        List         |                    `ListNode`, `List`                     |
|  4   |   Stack and Queue   | `IStack`, `Stack`, `LinkedStack`,`StackExample`, `Queue`  |
|  5   |     Binary Tree     |                 `BinTreeNode`, `BinTree`                  |
|  6   | Binary Search Tree  |                `BST.hpp`, `AVL.hpp`                       |
|  7   |  BST Applications   |                             /                             |
|  8   |    Advanced BST     |                             /                             |
|  9   |     Dictionary      |                             /                             |
|  10  |        Graph        |             `Graph`,`GraphMatrix`,`GraphList`             |
|  11  | Graph Applications  |                             /                             |
|  12  |   Priority Queue    |                             /                             |
|  13  |       String        |                             /                             |
|  14  |       Sorting       |                             /                             |
| NaN  |        Other        |                        `Iterator`                         |

## Download

```shell
$ git clone --recurse-submodules https://github.com/hnlcf/912-dsa.git

$ cd 912-dsa
```

## Dependency

### Tools

- cmake
- python3

### Library

Using `catch2` for testing which managed by git submodules.

- catch2

## QuickStart

### Using script

```shell
python3 tools.py --all
```

### Manual

1. Generate config

```shell
$ mkdir -p build && cd build

$ cmake -DCMAKE_BUILD_TYPE=Release ..
```

2. Build

```shell
$ cmake --build . --config Release --parallel 12
```

3. Run test

```shell
$ ctest -C Release --verbose
```

4. Install

```shell
$ # undo
```

## License

[MIT](./LICENSE)
