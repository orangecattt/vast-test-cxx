// RUN: %driver -cc1 %isys -std=c++2b %s %target -o %t%output-suffix && %filecheck

struct TrivialStruct {
    void explicit_object_function(this TrivialStruct) {}
};
void test() {
    TrivialStruct s;
    s.explicit_object_function();
}



void test_lambda() {
    [](this auto This) -> int {
        return This();
    }();
}



void test_lambda_ref() {
    auto l = [i = 42](this auto & This, int j) -> int {
        return This(j);
    };
    l(0);
}




struct TestPointer {
    void f(this TestPointer &);
};

void test_pointer() {
    TestPointer t;
    using Fn = void(TestPointer&);
    Fn* fn = &TestPointer::f;
    fn(t);
}


struct MaterializedTemporary {
  void foo(this MaterializedTemporary&&);
  MaterializedTemporary();
  ~MaterializedTemporary();
};

void test_temporary() {
  MaterializedTemporary{}.foo();
}

