from pathlib import Path
from subprocess import run
from os import remove
from time import sleep
from sys import platform
from shutil import which
from sys import exit

def remove_if_exists(file):
    if Path(file).exists():
        remove(file)

    if '.obj' in file:
      obj_file = Path(file).name.replace('.cpp', '')
      if Path(obj_file).exists():
        remove(obj_file)

if platform == 'win32':
    pe = 'exe'
    rpe = '.\\'

    def compile(file_src):
      if which("clang-cl.exe") is not None:
        return ['clang-cl.exe', '/std:c++20', '-Z7', f'{file_src}', f'-o', f'{file}.{pe}']

      if which("cl.exe") is not None:
        return ['cl.exe', '/EHsc', '/std:c++20', '/Z7', '/nologo', f'/Tp{file_src}', f'/Fe{file}.{pe}', '/link', '/NOLOGO', '/INCREMENTAL:NO']

      raise Exception("clang-cl.exe or cl.exe not found")
else:
    def compile(file_src):
      return ['c++', '-std:c++20', '-g', file_src, '-o', f'{file}']

    pe = ''
    rpe = './'


for file in Path('idk').rglob('*.cpp'):
    print(f'current test file: {file}')
    print('--------')
    run(compile(file))
    
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
        remove_if_exists(f'{file}..pdb')
        remove_if_exists(f'{file}.ilk')
        remove_if_exists(f'{file}..ilk')
        remove_if_exists(f'{file}.obj')
        print('--------')
    else:
      print(f"compile error might be occurred for {file}.{pe}!")
      exit(1)

    sleep(0.1)