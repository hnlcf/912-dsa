#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import sys

project_path = os.getcwd()
binary_path = project_path + '/build'
test_path = binary_path + '/test'

conan_p = 'conan'
cmake_p = 'cmake'
ninja_p = 'ninja'
format_p = 'clang-format'

conan_install_cmd = f'{conan_p} install {project_path} -if={binary_path}'

cmake_build_type = 'Debug'  # Or Release
cmake_generator_type = '-G Ninja'
cmake_config_cmd = f'{cmake_p}  {cmake_generator_type} -S {project_path} -DCMAKE_BUILD_TYPE={cmake_build_type} -B {binary_path}'
cmake_build_cmd = f'{cmake_p} --build {binary_path} --config {cmake_build_type} --parallel 12 --target '

catch2_test_cmd = f'{test_path}/test -d yes --order lex '

file_type_list = [
    'c',
    'cc',
    'cpp',
    'h',
    'hpp'
]

ignore_path_list = [
    'build',
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


def find_source_files():
    ignore_path_opt = ''
    for sub_path in ignore_path_list:
        ignore_path_opt += f' -path "{project_path}/{sub_path}" -o'
    ignore_path_opt = ignore_path_opt[:-3]

    file_type_opt = ''
    for type in file_type_list:
        file_type_opt += f' -name "*.{type}" -or'
    file_type_opt = file_type_opt[:-4]

    find_cmd = f'find . "(" {ignore_path_opt} ")" -prune -o -type f "(" {file_type_opt} ")" -print '

    return find_cmd


def list_files():
    find_file_cmd = find_source_files()
    os.system(find_file_cmd)


def count_lines():
    find_file_cmd = find_source_files()
    count_line_cmd = f'{find_file_cmd} | xargs grep -v "^$" | wc -l'
    os.system(count_line_cmd)


def format_file(file_path):
    print(file_path)
    os.system(f"{format_p} -i {file_path} -style=File")


def format_all():
    for root, _, files in os.walk(project_path):
        for file in files:
            if file.endswith('.hpp') or file.endswith('.cpp') or file.endswith('.h'):
                file_path = f'{root}/{file}'
                format_file(file_path)


def print_help_msg(option, explanation):
    print(' ' * 4, f'{option}'.ljust(12), f'{explanation}')


def help_cmd():
    for msg in help_msg_list:
        print_help_msg(msg[0], msg[1])


def build_target(target='all'):
    if not os.path.exists(binary_path):
        cmake_refresh_project()
    os.system(cmake_build_cmd + target)


def clean_build():
    if os.path.exists(binary_path):
        build_target('clean')
    else:
        os.mkdir(binary_path)


def cmake_refresh_project():
    clean_build()
    os.system(conan_install_cmd)
    os.system(cmake_config_cmd)
    build_target()


def run_test(test_name=''):
    if not os.path.exists(binary_path):
        cmake_refresh_project()
    build_target()
    os.system(catch2_test_cmd + f'{test_name}')


def all_actions():
    format_all()
    cmake_refresh_project()
    run_test()


def main():
    if len(sys.argv) < 2 or sys.argv[1] == '-h' or sys.argv[1] == '--help':
        help_cmd()
    elif sys.argv[1] == '--all':
        all_actions()
    elif sys.argv[1] == '--count':
        count_lines()
    elif sys.argv[1] == '--list':
        list_files()
    elif sys.argv[1] == '--cmake':
        cmake_refresh_project()
    elif sys.argv[1] == '--clean':
        clean_build()
    elif sys.argv[1] == '--format':
        format_all()
    elif sys.argv[1] == '--build':
        if len(sys.argv) == 3:
            build_target(sys.argv[2])
        else:
            build_target()
    elif sys.argv[1] == '--test':
        if len(sys.argv) == 3:
            run_test(sys.argv[2])
        else:
            run_test()


if __name__ == '__main__':
    main()
