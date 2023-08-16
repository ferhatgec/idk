from pathlib import Path
from subprocess import run
from os import remove
from time import sleep

def remove_if_exists(file):
    if Path(file).exists():
        remove(file)

for file in Path('idk').rglob('*.cpp'):
    print(f'current test file: {file}')
    run(['clang-cl', '/fsanitize=address', '/std:c++20', file, '-o', f'{file}.exe'])

    if Path(f'{file}.exe').exists():
        run([f'.\{file}.exe'])
        remove(f'{file}.exe')
        remove_if_exists(f'{file}.exp')
        remove_if_exists(f'{file}.lib')
        remove_if_exists(f'{file}.pdb')

    sleep(0.1)