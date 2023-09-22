from pathlib import Path
from subprocess import run
from os import remove
from time import sleep
from sys import platform

def remove_if_exists(file):
    if Path(file).exists():
        remove(file)

if platform == 'win32':
    cli_args = ['clang-cl', '/std:c++20']
    pe = '.exe'
    rpe = '.\\'
else:
    cli_args = ['c++', '-std=c++20']
    pe = ''
    rpe = './'


for file in Path('idk').rglob('*.cpp'):
    print(f'current test file: {file}')
    run(cli_args + [file, '-o', f'{file}.{pe}'])
    
    if Path(f'{file}.{pe}').exists():
#        if len(pe) == 0 and Path('/bin/valgrind').exists():
#            run(['valgrind', f'{rpe}{file}.{pe}'])
#        else:
#            run([f'{rpe}{file}.{pe}'])
        run([f'{rpe}{file}.{pe}'])

        remove(f'{file}.{pe}')
        remove_if_exists(f'{file}.exp')
        remove_if_exists(f'{file}.lib')
        remove_if_exists(f'{file}.pdb')

    sleep(0.1)