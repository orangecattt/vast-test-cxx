// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

template<typename T>
struct S {
  static int n;
};
template<typename T> int S<T>::n = 5;

int f() {
  // Make sure that the reference here is enough to trigger the instantiation of
  // the static data member.
  // CHECK: @_ZN1SIiE1nE = linkonce_odr{{.*}} global i32 5
  int a[S<int>::n];
  return sizeof a;
}

void test0(void *array, int n) {
  // CHECK-LABEL: define{{.*}} void @_Z5test0Pvi(
  // AMDGCN:        [[ARRAY0:%.*]] = alloca ptr, align 8, addrspace(5)
  // AMDGCN-NEXT:   [[N0:%.*]] = alloca i32, align 4, addrspace(5)
  // AMDGCN-NEXT:   [[REF0:%.*]] = alloca ptr, align 8, addrspace(5)
  // AMDGCN-NEXT:   [[S0:%.*]] = alloca i16, align 2, addrspace(5)
  // AMDGCN-NEXT:   [[ARRAY:%.*]] = addrspacecast ptr addrspace(5) [[ARRAY0]] to ptr
  // AMDGCN-NEXT:   [[N:%.*]] = addrspacecast ptr addrspace(5) [[N0]] to ptr
  // AMDGCN-NEXT:   [[REF:%.*]] = addrspacecast ptr addrspace(5) [[REF0]] to ptr
  // AMDGCN-NEXT:   [[S:%.*]] = addrspacecast ptr addrspace(5) [[S0]] to ptr
  // X64:        [[ARRAY:%.*]] = alloca ptr, align 8
  // X64-NEXT:   [[N:%.*]] = alloca i32, align 4
  // X64-NEXT:   [[REF:%.*]] = alloca ptr, align 8
  // X64-NEXT:   [[S:%.*]] = alloca i16, align 2
  // CHECK-NEXT: store ptr
  // CHECK-NEXT: store i32

  // Capture the bounds.
  // CHECK-NEXT: [[T0:%.*]] = load i32, ptr [[N]], align 4
  // CHECK-NEXT: [[DIM0:%.*]] = zext i32 [[T0]] to i64
  // CHECK-NEXT: [[T0:%.*]] = load i32, ptr [[N]], align 4
  // CHECK-NEXT: [[T1:%.*]] = add nsw i32 [[T0]], 1
  // CHECK-NEXT: [[DIM1:%.*]] = zext i32 [[T1]] to i64
  typedef short array_t[n][n+1];

  // CHECK-NEXT: [[T0:%.*]] = load ptr, ptr [[ARRAY]], align 8
  // CHECK-NEXT: store ptr [[T0]], ptr [[REF]], align 8
  array_t &ref = *(array_t*) array;

  // CHECK-NEXT: [[T0:%.*]] = load ptr, ptr [[REF]]
  // CHECK-NEXT: [[T1:%.*]] = mul nsw i64 1, [[DIM1]]
  // CHECK-NEXT: [[T2:%.*]] = getelementptr inbounds i16, ptr [[T0]], i64 [[T1]]
  // CHECK-NEXT: [[T3:%.*]] = getelementptr inbounds i16, ptr [[T2]], i64 2
  // CHECK-NEXT: store i16 3, ptr [[T3]]
  ref[1][2] = 3;

  // CHECK-NEXT: [[T0:%.*]] = load ptr, ptr [[REF]]
  // CHECK-NEXT: [[T1:%.*]] = mul nsw i64 4, [[DIM1]]
  // CHECK-NEXT: [[T2:%.*]] = getelementptr inbounds i16, ptr [[T0]], i64 [[T1]]
  // CHECK-NEXT: [[T3:%.*]] = getelementptr inbounds i16, ptr [[T2]], i64 5
  // CHECK-NEXT: [[T4:%.*]] = load i16, ptr [[T3]]
  // CHECK-NEXT: store i16 [[T4]], ptr [[S]], align 2
  short s = ref[4][5];

  // CHECK-NEXT: ret void
}


void test2(int b) {
  // CHECK-LABEL: define{{.*}} void {{.*}}test2{{.*}}(i32 noundef %b)
  int varr[b];
  // AMDGCN: %__end1 = alloca ptr, align 8, addrspace(5)
  // AMDGCN: [[END:%.*]] = addrspacecast ptr addrspace(5) %__end1 to ptr
  // get the address of %b by checking the first store that stores it 
  //CHECK: store i32 %b, ptr [[PTR_B:%.*]]

  // get the size of the VLA by getting the first load of the PTR_B
  //CHECK: [[VLA_NUM_ELEMENTS_PREZEXT:%.*]] = load i32, ptr [[PTR_B]]
  //CHECK-NEXT: [[VLA_NUM_ELEMENTS_PRE:%.*]] = zext i32 [[VLA_NUM_ELEMENTS_PREZEXT]]
  
  b = 15;
  //CHECK: store i32 15, ptr [[PTR_B]]
  
  // Now get the sizeof, and then divide by the element size
  
  
  //CHECK: [[VLA_SIZEOF:%.*]] = mul nuw i64 4, [[VLA_NUM_ELEMENTS_PRE]]
  //CHECK-NEXT: [[VLA_NUM_ELEMENTS_POST:%.*]] = udiv i64 [[VLA_SIZEOF]], 4
  //CHECK-NEXT: [[VLA_END_PTR:%.*]] = getelementptr inbounds i32, ptr {{%.*}}, i64 [[VLA_NUM_ELEMENTS_POST]]
  //X64-NEXT: store ptr [[VLA_END_PTR]], ptr %__end1
  //AMDGCN-NEXT: store ptr [[VLA_END_PTR]], ptr [[END]]
  for (int d : varr) 0;
}

void test3(int b, int c) {
  // CHECK-LABEL: define{{.*}} void {{.*}}test3{{.*}}(i32 noundef %b, i32 noundef %c)
  int varr[b][c];
  // AMDGCN: %__end1 = alloca ptr, align 8, addrspace(5)
  // AMDGCN: [[END:%.*]] = addrspacecast ptr addrspace(5) %__end1 to ptr
  // get the address of %b by checking the first store that stores it 
  //CHECK: store i32 %b, ptr [[PTR_B:%.*]]
  //CHECK-NEXT: store i32 %c, ptr [[PTR_C:%.*]]
  
  // get the size of the VLA by getting the first load of the PTR_B
  //CHECK: [[VLA_DIM1_PREZEXT:%.*]] = load i32, ptr [[PTR_B]]
  //CHECK-NEXT: [[VLA_DIM1_PRE:%.*]] = zext i32 [[VLA_DIM1_PREZEXT]]
  //CHECK: [[VLA_DIM2_PREZEXT:%.*]] = load i32, ptr [[PTR_C]]
  //CHECK-NEXT: [[VLA_DIM2_PRE:%.*]] = zext i32 [[VLA_DIM2_PREZEXT]]
  
  b = 15;
  c = 15;
  //CHECK: store i32 15, ptr [[PTR_B]]
  //CHECK: store i32 15, ptr [[PTR_C]]
  // Now get the sizeof, and then divide by the element size
  
  // multiply the two dimensions, then by the element type and then divide by the sizeof dim2
  //CHECK: [[VLA_DIM1_X_DIM2:%.*]] = mul nuw i64 [[VLA_DIM1_PRE]], [[VLA_DIM2_PRE]]
  //CHECK-NEXT: [[VLA_SIZEOF:%.*]] = mul nuw i64 4, [[VLA_DIM1_X_DIM2]]
  //CHECK-NEXT: [[VLA_SIZEOF_DIM2:%.*]] = mul nuw i64 4, [[VLA_DIM2_PRE]]
  //CHECK-NEXT: [[VLA_NUM_ELEMENTS:%.*]] = udiv i64 [[VLA_SIZEOF]], [[VLA_SIZEOF_DIM2]]
  //CHECK-NEXT: [[VLA_END_INDEX:%.*]] = mul nsw i64 [[VLA_NUM_ELEMENTS]], [[VLA_DIM2_PRE]]
  //CHECK-NEXT: [[VLA_END_PTR:%.*]] = getelementptr inbounds i32, ptr {{%.*}}, i64 [[VLA_END_INDEX]]
  //X64-NEXT: store ptr [[VLA_END_PTR]], ptr %__end
  //AMDGCN-NEXT: store ptr [[VLA_END_PTR]], ptr [[END]]
 
  for (auto &d : varr) 0;
}


