本测试集用于测试vast-front将C++翻译为IR的功能是否正确，由clang项目中的`test/CodeGenCXX`测试集移植而来

### 测试集结构

- `testcases/`
  - `*.cpp, *.cppm`：测试用例，每个测试用例都是一个单文件
  - `Inputs/, typeinfo`：测试用例的依赖
  - `ignore/`：忽略的测试用例
- `lit.cfg.py, lit.site.cfg.py.in`：lit的配置文件

### 测试方法

本测试集由cmake配置测试环境并启动测试：
```bash
mkdir build && cd build
cmake .. [-DTESTCASE=test1[;test2[;test3...]]]
ctest
```
测试结果可在`build/Testing/Temporary/LastTest.log`中查看

变量`TESTCASE`允许你指定`testcases/`下的一个测试用例子集运行测试，默认情况下测试所有测试用例。该变量为一个目录或文件的列表，每一项均为相对于`testcases/`的相对路径

### 测试集配置

本测试集使用llvm lit运行测试

#### 更改测试用例的目录结构

本测试集删减了clang的CodeGenCXX测试集，粗略去除了一些对vast不关心的内容的测试，比如目标平台相关的语法扩展和IR信息、IR中的调试信息等，目前共有721个测试用例。这些测试用例并未归类，你可以在实现vast对C++某个语法的翻译的同时筛选出相应测试用例并将其归入相应子目录（比如将有关构造函数的测试用例归入`testcases/constructor/`目录），这样也有助于划分我们各自负责的测试用例。同时这些测试用例中仍然包含一些我们不关心的测试用例，发现这些测试用例后你可以将其归入`testcases/ignore/`目录。如果想知道某个测试用例的原本目的，可以参考clang项目中的同名测试用例，查看其原本的编译和测试命令。**更改目录结构后请及时更新仓库。**

`lit.cfg.py`中可以在`config.excludes`中指定忽略的测试目录

#### 更改编译命令

lit按照测试用例中的注释`// RUN:`指定的命令运行测试，为了更灵活地配置测试命令，其中可以包括可被替换为相应文本的替换符。lit有一些内置替换符，可参考[llvm lit](https://llvm.org/docs/CommandGuide/lit.html#substitutions)，也可以通过`lit.cfg.py`中的`config.substitutions.append()`自定义替换规则。其中`%driver`指定编译工具、`%target`指定生成目标、`%output-suffix`指定生成文件的后缀，**你需要将这些替换符指定为vast相关的命令行参数**。

#### 更改测试命令

本测试集使用llvm FileCheck检查编译出的内容是否符合要求。FileCheck使用模板文件中的注释`// CHECK: <pattern>`、`// CHECK-NOT: <pattern>`等指定匹配模式用以匹配被检查的文件。通常将这些注释写在测试用例中，但为了使用替换符灵活指定匹配模式，本测试集使用一个临时文件指定测试注释（参考测试命令`%filecheck`的定义）。`%check`指定了匹配模式，目前对每个生成文件的检测都是相同的，仅保证其中不含`unsup.`和`unreach.`操作。如有补充，你可以修改`%filecheck`和`%check`。
