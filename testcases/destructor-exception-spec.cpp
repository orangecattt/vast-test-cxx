// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-use-cxa-atexit %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-rtti %s -std=c++11 %target -o %t%output-suffix && %filecheck

// PR13479: don't crash with -fno-exceptions.
namespace {
  struct SchedulePostRATDList {
    virtual ~SchedulePostRATDList();
  };

  SchedulePostRATDList::~SchedulePostRATDList() {}

  SchedulePostRATDList Scheduler;
}
