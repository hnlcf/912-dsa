#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import sys
import shutil

project_path = os.getcwd()
binary_path = project_path + '/build'
test_path = binary_path + '/test'

conan_p = 'conan'
cmake_p = 'cmake'
ninja_p = 'ninja'
format_p = 'clang-format'

conan_install_cmd = f'{conan_p} install {project_path} -if={binary_path}'

cmake_build_mode = 'release'  # Or debug
cmake_generator_type = '-G Ninja'
cmake_config_cmd = f'{cmake_p} {cmake_generator_type} -S {project_path} -DCMAKE_BUILD_TYPE={cmake_build_mode} -B {binary_path}'
cmake_build_cmd = f'{cmake_p} --build {binary_path} --parallel 12 --target '

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
    os.system(f"{format_p} -i {file_path} -style=file")


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


def build_target(mode='release', target='all'):
    if not os.path.exists(binary_path) or len(os.listdir(binary_path)) == 0:
        cmake_refresh_project(mode=mode)
    os.system(cmake_build_cmd + target)


def clean_build():
    if os.path.exists(binary_path):
        shutil.rmtree(binary_path)
    os.mkdir(binary_path)


def cmake_refresh_project(mode: str):
    global cmake_config_cmd
    clean_build()
    os.system(conan_install_cmd)
    if mode != cmake_build_mode:
        os.system(cmake_config_cmd.replace('release', mode))
    os.system(cmake_config_cmd)


def run_test(test_name=''):
    if not os.path.exists(binary_path):
        build_target(mode='release', target='all')
    os.system(catch2_test_cmd + f'{test_name}')


def all_actions():
    format_all()
    cmake_refresh_project(mode='release')
    build_target(mode='release', target='all')
    run_test()


def main():
    arg_len = len(sys.argv)
    arg_list = list(sys.argv)
    if arg_len < 2 or arg_list[1] == '-h' or arg_list[1] == '--help':
        help_cmd()
    elif arg_list[1] == '--cmake':
        mode = 'release'
        if arg_len > 2 and arg_list[2] == '--mode':
            mode = arg_list[3]
        cmake_refresh_project(mode)
    elif arg_list[1] == '--build':
        mode = 'Release'
        target = 'all'
        if arg_len > 2 and arg_list[2] == '--mode':
            mode = arg_list[3]
            if arg_len > 4 and arg_list[4] == '--target':
                target = arg_list[5]
        elif arg_len > 2 and arg_list[2] == '--target':
            target = arg_list[3]
        build_target(mode, target)
    elif arg_list[1] == '--all':
        all_actions()
    elif arg_list[1] == '--count':
        count_lines()
    elif arg_list[1] == '--list':
        list_files()
    elif arg_list[1] == '--clean':
        clean_build()
    elif arg_list[1] == '--rebuild':
        clean_build()
        build_target()
    elif arg_list[1] == '--format':
        format_all()
    elif arg_list[1] == '--test':
        if arg_len > 2:
            run_test(arg_list[2])
        else:
            run_test()


if __name__ == '__main__':
    main()
