
// RUN: %driver -cc1 %isys -std=c++14 %s -faligned-allocation %target -o %t%output-suffix && %filecheck

typedef __typeof__(sizeof(0)) size_t;

namespace std {
struct nothrow_t {};
enum class align_val_t : size_t;
} // namespace std
std::nothrow_t nothrow;

typedef unsigned char uint8_t;

enum class __hot_cold_t : uint8_t;

namespace malloc_namespace {
using hot_cold_t = __hot_cold_t;
}

void *operator new(size_t size,
                   malloc_namespace::hot_cold_t hot_cold) noexcept(false);
void *operator new[](size_t size,
                     malloc_namespace::hot_cold_t hot_cold) noexcept(false);
void *operator new(size_t size, const std::nothrow_t &,
                   malloc_namespace::hot_cold_t hot_cold) noexcept;
void *operator new[](size_t size, const std::nothrow_t &,
                     malloc_namespace::hot_cold_t hot_cold) noexcept;
void *operator new(size_t size, std::align_val_t alignment,
                   malloc_namespace::hot_cold_t hot_cold) noexcept(false);
void *operator new[](size_t size, std::align_val_t alignment,
                     malloc_namespace::hot_cold_t hot_cold) noexcept(false);
void *operator new(size_t size, std::align_val_t alignment,
                   const std::nothrow_t &,
                   malloc_namespace::hot_cold_t hot_cold) noexcept;
void *operator new[](size_t size, std::align_val_t alignment,
                     const std::nothrow_t &,
                     malloc_namespace::hot_cold_t hot_cold) noexcept;


void hot_cold_new() {
  operator new(1, (__hot_cold_t)0);
  new ((__hot_cold_t)0) int;
}


void hot_cold_new_array() {
  operator new[](1, (__hot_cold_t)0);
  new ((__hot_cold_t)0) int[1];
}


void hot_cold_new_nothrow() {
  operator new(1, nothrow, (__hot_cold_t)0);
  new (nothrow, (__hot_cold_t)0) int;
}


void hot_cold_new_nothrow_array() {
  operator new[](1, nothrow, (__hot_cold_t)0);
  new (nothrow, (__hot_cold_t)0) int[1];
}


class alignas(32) alignedstruct {
  int x;
};

void hot_cold_new_align() {
  operator new(1, (std::align_val_t)32, (__hot_cold_t)0);
  new ((__hot_cold_t)0) alignedstruct;
}


void hot_cold_new_align_array() {
  operator new[](1, (std::align_val_t)32, (__hot_cold_t)0);
  new ((__hot_cold_t)0) alignedstruct[1];
}


void hot_cold_new_align_nothrow() {
  operator new(1, (std::align_val_t)32, nothrow, (__hot_cold_t)0);
  new (nothrow, (__hot_cold_t)0) alignedstruct;
}


void hot_cold_new_align_nothrow_array() {
  operator new[](1, (std::align_val_t)32, nothrow, (__hot_cold_t)0);
  new (nothrow, (__hot_cold_t)0) alignedstruct[1];
}


