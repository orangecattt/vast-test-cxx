// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct box {
  virtual ~box();
};

struct pile_box : public box {
  pile_box(box *);
};

pile_box::pile_box(box *pp)
{
}


