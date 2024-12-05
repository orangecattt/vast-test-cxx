// RUN: %driver -cc1 %isys -fnew-infallible %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-new-infallible -fnew-infallible %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-new-infallible %s %target -o %t%output-suffix && %filecheck





int *new_infallible = new int;
