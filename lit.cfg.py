import subprocess
import re
import os

import lit.formats

from lit.llvm import llvm_config

config.name = "vast-test-cxx"
config.test_format = lit.formats.ShTest(True)

config.test_source_root = os.path.join(os.path.dirname(__file__), "testcases")
config.test_exec_root = config.my_obj_root

config.suffixes = ['.cpp', '.cppm']
config.excludes = ['Inputs', 'ignore']

# FileCheck command and pattern, %check and %output-suffix used in %FILECHECK so they should defined after %FILECHECK
config.substitutions.append((r'%filecheck', 'echo \'%check\' > %t.check && FileCheck %t.check --input-file=%t%output-suffix && rm %t.check'))
config.substitutions.append((r'%check', '// CHECK-NOT: {{unsup\.|unreach\.}}'))

config.substitutions.append((r'%driver', 'clang'))
config.substitutions.append((r'%target', '-emit-llvm'))
config.substitutions.append((r'%output-suffix', '.ll'))

# config.substitutions.append((r'%driver', 'vast-front'))
# config.substitutions.append((r'%target', '-vast-emit-mlir=hl'))
# config.substitutions.append((r'%output-suffix', '.hl'))

# clang -cc1 is the frontend, clang is the driver. The driver invokes the frontend with options appropriate for your system
# find clang SYSTEM include search path
clang_env = subprocess.run('clang -E -x c++ -v -', stdin=subprocess.DEVNULL, capture_output=True, text=True, shell=True)
pat_internal_isystem = r'\(in-process\)\s*\n\s*(?:(?!-internal-isystem)\S+\s+)*((?:-internal-isystem\s+\S+\s+)*(?:-internal-isystem\s+\S+))'
pat_internal_externc_isystem = r'\(in-process\)\s*\n\s*(?:(?!-internal-externc-isystem)\S+\s+)*((?:-internal-externc-isystem\s+\S+\s+)*(?:-internal-externc-isystem\s+\S+))'
match_internal_isystem = re.search(pat_internal_isystem, clang_env.stderr)
match_internal_externc_isystem = re.search(pat_internal_externc_isystem, clang_env.stderr)
isys = ""
if match_internal_isystem:
    isys += match_internal_isystem.group(1)
if match_internal_externc_isystem:
    isys += ' '
    isys += match_internal_externc_isystem.group(1)
config.substitutions.append((r'%isys', isys))

# %std_cxx<group> subst, defination in llvm_config.use_clang()
# Many tests work across many language standards. Before
# https://discourse.llvm.org/t/lit-run-a-run-line-multiple-times-with-different-replacements/64932
# has a solution, provide substitutions to conveniently try every standard with LIT_CLANG_STD_GROUP.
clang_std_group = int(os.environ.get("LIT_CLANG_STD_GROUP", "0"))
clang_std_values = ("98", "11", "14", "17", "20", "2b")
def add_std_cxx(s):
    t = s[8:]
    if t.endswith("-"):
        t += clang_std_values[-1]
    l = clang_std_values.index(t[0:2] if t[0:2] != "23" else "2b")
    h = clang_std_values.index(t[3:5])
    # Let LIT_CLANG_STD_GROUP=0 pick the highest value (likely the most relevant
    # standard).
    l = h - clang_std_group % (h - l + 1)
    config.substitutions.append((s, "-std=c++" + clang_std_values[l]))
add_std_cxx("%std_cxx98-14")
add_std_cxx("%std_cxx98-")
add_std_cxx("%std_cxx11-14")
add_std_cxx("%std_cxx11-")
add_std_cxx("%std_cxx14-")
add_std_cxx("%std_cxx17-20")
add_std_cxx("%std_cxx17-")
add_std_cxx("%std_cxx20-")
add_std_cxx("%std_cxx23-")

config.available_features.add('asserts')
config.available_features.add('thread_support')
