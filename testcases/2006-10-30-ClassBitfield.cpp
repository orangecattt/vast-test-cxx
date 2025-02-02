// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct _Refcount_Base   {
  unsigned long _M_ref_count;
  int _M_ref_count_lock;
  _Refcount_Base() : _M_ref_count(0) {}
};

struct _Rope_RopeRep : public _Refcount_Base
{
public:
  int _M_tag:8;
};

int foo(_Rope_RopeRep* r) { return r->_M_tag; }
