// RUN: %driver -cc1 %isys -std=c++14 %s -fblocks %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -x c++ -std=c++14 -fblocks -emit-pch %s -o %t
// RUN: %driver -cc1 %isys -x c++ -std=c++14 -fblocks -include-pch %t %s %target -o %t%output-suffix && %filecheck

#ifndef HEADER
#define HEADER







int printf(const char * _Format, ...);

class ClassInTopLevelNamespace {
public:
  auto *topLevelNamespaceFunction() {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    return static_cast<int *>(nullptr);
  }

  decltype(auto) variadicFunction(int *a, ...) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    return a;
  }

  template<typename T>
  auto &functionTemplate(T &t) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    return t;
  }
};

template<typename T>
class ClassTemplate {
public:
  const auto &classTemplateFunction(T &t) {
    printf("__func__ %s\n", __func__);
    printf("__FUNCTION__ %s\n", __FUNCTION__);
    printf("__PRETTY_FUNCTION__ %s\n\n", __PRETTY_FUNCTION__);
    return t;
  }
};

struct ClassBlockConstr {
  const char *s;
  ClassBlockConstr() {
    const char * (^b)() = ^() {
    return __func__;
    };
    s = b();
  }
  ~ClassBlockConstr() {
    const char * (^b)() = ^() {
    return __func__;
    };
    s = b();
  }
};

template <class T>
class FuncTemplate {
  const char *Func;

public:
  FuncTemplate() : Func(__func__) {}
  const char *getFunc() const { return Func; }
};

constexpr const char* ConstexprPrettyFn() {
  return __PRETTY_FUNCTION__;
}
const char* ConstexprPrettyVar = ConstexprPrettyFn();

int
main() {
  int a;
  ClassInTopLevelNamespace topLevelNamespace;
  ClassBlockConstr classBlockConstr;
  topLevelNamespace.topLevelNamespaceFunction();
  topLevelNamespace.variadicFunction(&a);
  topLevelNamespace.functionTemplate(a);

  ClassTemplate<int> t;
  t.classTemplateFunction(a);
  return 0;
}
#else
void Foo() {
  FuncTemplate<int> FTi;
  (void)FTi.getFunc();
}
#endif

