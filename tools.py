#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import sys
import shutil

project_path = os.getcwd()
binary_path = project_path + '/build'
test_path = binary_path + '/test'

cmake_p = 'cmake'
format_p = 'clang-format'

cmake_build_mode = 'RelWithDebInfo'  # 'Debug'
cmake_config_cmd = f'{cmake_p} -S {project_path} -B {binary_path} -DCMAKE_BUILD_TYPE={cmake_build_mode} '
cmake_build_cmd = f'{cmake_p} --build {binary_path} --config {cmake_build_mode} --parallel 12'
cmake_test_cmd = f'ctest -C {cmake_build_mode} --verbose'

catch2_test_cmd = f'{binary_path}/test/dsa_test -d yes --order lex '

file_type_list = [
    'cc',
    'h',
]

include_path_list = [
    'exercise',
    'src',
    'test'
]

help_msg_list = [
    ['--all', 'format --> build --> test'],
    ['--list', 'list source files'],
    ['--count', 'count code lines'],
    ['--format', 'format all files'],
    ['--build', 'build the project'],
    ['--test', 'run test case'],
    ['--cmake', 'cmake refresh project'],
    ['--clean', 'clear the project'],
    ['--help/-h', 'help'],
]


def source_file_list() -> list[str]:
    file_list = []
    for include_path in include_path_list:
        for root, _, files in os.walk(include_path):
            for file in files:
                for file_type in file_type_list:
                    if file.endswith(file_type):
                        file_path = f'{root}/{file}'
                        file_list.append(file_path)
    return file_list


def list_files():
    file_list = source_file_list()
    for file in file_list:
        print(file)


def count_file_line(file_path: str) -> int:
    count = 0
    with open(file_path, 'rb') as f:
        for line in f:
            # remove blank
            line = line.strip()
            if not line:
                continue
            # remove comments
            if line.startswith(b'//') or line.startswith(b'/*') or line.startswith(b'*'):
                continue
            count += 1
    return count


def count_lines():
    total_count = 0
    file_list = source_file_list()
    for file in file_list:
        count = count_file_line(file)
        print('-' * 2, f'{file}'.ljust(50), f'{count}')
        total_count += count
    print('-' * 2, f'[Total lines]: '.ljust(50), f'{total_count}')


def format_file(file_path):
    print(file_path)
    os.system(f"{format_p} -i {file_path} -style=file")


def format_all():
    file_list = source_file_list()
    for file in file_list:
        format_file(file)


def print_help_msg(option, explanation):
    print(' ' * 4, f'{option}'.ljust(12), f'{explanation}')


def help_cmd():
    for msg in help_msg_list:
        print_help_msg(msg[0], msg[1])


def clean_build():
    if os.path.exists(binary_path):
        shutil.rmtree(binary_path)
    os.mkdir(binary_path)


def cmake_refresh_project():
    clean_build()
    os.system(cmake_config_cmd)


def build_target():
    if not os.path.exists(binary_path):
        cmake_refresh_project()
    os.system(cmake_build_cmd)


def run_test():
    build_target()
    os.system(f'cd build && {cmake_test_cmd}')


def catch2_test(tag=''):
    build_target()
    os.system(f'cd build && make && {catch2_test_cmd} {tag}')


def all_actions():
    format_all()
    cmake_refresh_project()
    build_target()
    run_test()


def main():
    arg_len = len(sys.argv)
    arg_list = list(sys.argv)
    if arg_len < 2 or arg_list[1] == '-h' or arg_list[1] == '--help':
        help_cmd()
    elif arg_list[1] == '--count':
        count_lines()
    elif arg_list[1] == '--list':
        list_files()
    elif arg_list[1] == '--format':
        format_all()
    elif arg_list[1] == '--clean':
        clean_build()
    elif arg_list[1] == '--cmake':
        cmake_refresh_project()
    elif arg_list[1] == '--build':
        build_target()
    elif arg_list[1] == '--test':
        run_test()
    elif arg_list[1] == '--catch2':
        if arg_len > 2:
            catch2_test(arg_list[2])
        else:
            catch2_test()
    elif arg_list[1] == '--all':
        all_actions()


if __name__ == '__main__':
    main()
