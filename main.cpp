#include <iostream>

#include <CrystalSpatial/spatial.h>

int main() {
  crystal::spatial::SubSpace root{};
  crystal::spatial::Position p1{root, {0, 0}};
  crystal::spatial::trans t{};
  t.Translate({1, 1});
  t.Rotate(3.14159 / 4);
  crystal::spatial::SubSpace ss1{&root, t};
  crystal::spatial::Position p2{ss1, {1, 1}};

  std::cout << "ROOT" << std::endl;
  std::cout << "\tTrans: " << root.Trans() << std::endl;
  std::cout << "\tOrigin: " << root.AbsoluteOrigin() << std::endl;

  std::cout << "SUBSPACE1" << std::endl;
  std::cout << "\tTrans: " << ss1.Trans() << std::endl;
  std::cout << "\tOrigin:" << ss1.AbsoluteOrigin() << std::endl;

  std::cout << "POSITION1" << std::endl;
  std::cout << "\t Relative Position: " << p1.Relative() << std::endl;
  std::cout << "\t Absolute Position: " << p1.Absolute() << std::endl;

  std::cout << "POSITION2" << std::endl;
  std::cout << "\t Relative Position: " << p2.Relative() << std::endl;
  std::cout << "\t Absolute Position: " << p2.Absolute() << std::endl;
  return 0;
}