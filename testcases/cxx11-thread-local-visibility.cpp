// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

// Regression test for PR40327

// LINUX_AIX: @default_tls ={{.*}} thread_local global i32
// LINUX_AIX: @hidden_tls ={{( hidden)?}} thread_local global i32
// LINUX_AIX: define weak_odr hidden noundef ptr @_ZTW11default_tls()
// LINUX_AIX: define weak_odr hidden noundef ptr @_ZTW10hidden_tls()
//
// DARWIN: @default_tls = internal thread_local global i32
// DARWIN: @hidden_tls = internal thread_local global i32
// DARWIN: define cxx_fast_tlscc noundef ptr @_ZTW11default_tls()
// DARWIN: define hidden cxx_fast_tlscc noundef ptr @_ZTW10hidden_tls()

__attribute__((visibility("default"))) thread_local int default_tls;
__attribute__((visibility("hidden"))) thread_local int hidden_tls;
