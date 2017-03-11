#ifndef ITBMAP_H
#define ITBMAP_H

#include "shape.h"
#include "color.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

class ITBMap {
public:
  ITBMap(std::string, std::string, std::string);
  virtual ~ITBMap();

  void setArg(bool p, bool b, bool j);

  std::vector<Shape*> get_all_bangunan() const;
  std::vector<Shape*> get_all_jalan() const;
  std::vector<Shape*> get_all_pohon() const;
  std::vector<Shape*> get_all_drawn_shapes() const;

  /* Getter */
  Shape* get_bangunan(int) const;
  Shape* get_jalan(int) const;
  Shape* get_pohon(int) const;

  int get_bangunan_size() const;
  int get_jalan_size() const;
  int get_pohon_size() const;

  int get_bangunan_besar_size() const;
  int get_jalan_besar_size() const;
  int get_pohon_besar_size() const;

private:

  std::vector<Shape*> bangunan;
  std::vector<Shape*> jalan;
  std::vector<Shape*> pohon;
  std::vector<Shape*> bangunan_besar;
  std::vector<Shape*> jalan_besar;
  std::vector<Shape*> pohon_besar;
  bool p;
  bool b;
  bool j;
  int size_bangunan;
  int size_jalan;
  int size_pohon;
  int size_bangunan_besar;
  int size_jalan_besar;
  int size_pohon_besar;
};

#endif
