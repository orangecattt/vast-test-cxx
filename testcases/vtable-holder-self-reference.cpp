// RUN: %driver -cc1 %isys -dwarf-version=2 -x c++ %s %target -o %t%output-suffix && %filecheck
//
// PR21941: crasher for self-referencing DW_TAG_structure_type node.  If we get
// rid of self-referenceing structure_types (PR21902), then it should be safe
// to just kill this test.
//
// CHECK: ![[SELF:[0-9]+]] = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "B",
// CHECK-SAME:                                         vtableHolder: ![[SELF]]

void foo() {
  struct V {
    int vi;
  };
  struct B : virtual V {};
  B b;
}
