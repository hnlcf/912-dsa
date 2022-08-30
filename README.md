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
- [Todo](#todo)
- [Installation](#installation)
- [Build](#build)
  - [Dependency](#dependency)
  - [Using script](#using-script)
  - [Manual](#manual)
- [License](#license)

## Introduction

This is a code implementation of **912 DSA**, which is a data structure course offered by **Tsinghua
University**.

- video: [DSA](https://www.xuetangx.com/course/THU08091000384/10322765?channel=i.area.learn_title)
- book: [Data Structures in C++](http://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/index.htm)

## Todo

- [ ] Tree
  - [ ] B Tree
  - [ ] Red-Black Tree
  - [ ] Kd Tree
- [ ] Dict
  - [ ] Hash Table
  - [ ] Skip List
    - [ ] Quadlist

|  ID  |       Chapter       |                               Implementation                                |
|:----:|:-------------------:|:---------------------------------------------------------------------------:|
|  1   |    Introduction     |                                 `Fibonacci`                                 |
|  2   |       Vector        |                    `Vector`, `Bitmap`, `BitmapQuickInit`                    |
|  3   |        List         |                             `ListNode`, `List`                              |
|  4   |   Stack and Queue   |      `StackInterface`, `Stack`, `LinkedStack`,`StackExample`, `Queue`       |
|  5   |     Binary Tree     |                          `BinTreeNode`, `BinTree`                           |
|  6   | Binary Search Tree  |                                `BST`, `AVL`                                 |
|  7   |  BST Applications   |                                      /                                      |
|  8   |    Advanced BST     |                       `SplayTree`, `BTree`, `RBTree`                        |
|  9   |     Dictionary      |                                      /                                      |
|  10  |        Graph        |                      `Graph`,`GraphMatrix`,`GraphList`                      |
|  11  | Graph Applications  |                                      /                                      |
|  12  |   Priority Queue    |                                      /                                      |
|  13  |       String        |                                      /                                      |
|  14  |       Sorting       |                                      /                                      |
| NaN  |        Other        |                                 `Iterator`                                  |

## Installation

```shell
git clone --recurse-submodules https://github.com/hnlcf/912-dsa.git

cd 912-dsa
```

## Build

### Dependency

#### Tools

- cmake
- python

#### Library

Using `catch2` for testing which managed by git submodules.

- catch2

### Using script

#### 1. CMake build and ctest

```shell
python tools.py --all
```

#### 2. Catch2 test

```shell
python tools.py --catch2
```

### Manual

#### 1. CMake config

```shell
mkdir -p build && cd build

cmake -DCMAKE_BUILD_TYPE=Release ..
```

#### 2. Build

```shell
cmake --build . --config Release --parallel 12
```

#### 3. Run ctest

```shell
ctest -C Release --verbose
```

## License

[MIT](./LICENSE)
