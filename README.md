# CrystalSpatial

Coordinate system for the crystal project.
This library implements a 2d spatial system with subspace trees and positions within those subspaces.

## QuickStart

```c++
#include <CrystalSpatial/spatial.h>

constexpr float kPi = 3.1415926535;

using namespace crystal::spatial;

int main() {
  /* Subspaces */
  SubSpace root{};
  /* A subspace with a parent. */
  SubSpace subspace1{&root};
  /* A subspace with a rotational transformation. */
  SubSpace subspace2{&root, trans.Rotate(kPi / 4)};

  /* Positions */
  /* A position that belongs to the `root` subspace. */
  Position pos1{root};
  /* A position that belongs to the `subspace1`. */
  Position pos2{root, 1.0f, 2.0f};

  /* Functionalities */
  subspace1.RelativeTrans();
  subspace1.AbsoluteTrans();
  pos1.Relative();
  pos1.Absolute();

  return 0;
}
```