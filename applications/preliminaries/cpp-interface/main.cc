
/**
 * M. Novak: the main program that actually shows that independently from the
 *           actual type of the 2D shape, they all implement the same `VShape2D`
 *           interface with its pure virtual `Area` interface method.
 *
 * compile: g++ -Iinclude -std=c++11 -o run main.cc
 * execute: ./run
 */


// include the definitions of the `Square` and `Circle` 2D shapes
#include "Square.hh"
#include "Circle.hh"
// include the definition of the 2D shape base class (actually already in with `Square.hh`)
#include "VShape2D.hh"

// standard includes
#include <iostream>
#include <vector>


// define a simple auxiliary function for printing information (implemented below)
void Print(VShape2D* sh);

// the main funtion
int main() {

  // ========================================================================
  // 1. Construct a `Squre` and a `Circle` and print their properties:
  //    - NOTE: we will use now directly the derived object pointers
  Square* sq1 = new Square(2.0);
  Circle* cr1 = new Circle(3.0);
  // then print their properties
  std::cout << "\n  === Using directly the DERIVED object pointers === \n" << std::endl;
  std::cout << " Area of sq1   = "   << sq1->Area()
            << " Perim. of sq1 = "   << sq1->Perimeter()
            << " name = "            << sq1->GetName()
            << std::endl;
  std::cout << " Area of cr1   = "   << cr1->Area()
            << " Perim. of cr1 = "   << cr1->Perimeter()
            << " name = "            << cr1->GetName()
            << std::endl;

  // ========================================================================
  // 2. Actually both different objects are 2D shapes as well:
  //    - we can store their pointers in a `VShape2D` pointer`
  //    - the proper interface implementation is invoked at run-time depending
  //      on if the 2D shape is actually a `Square` or a `Circle`
  std::cout << "\n  === Using the BASE and the common Print function now === \n" << std::endl;
  VShape2D* shape;
  shape = sq1;
  Print(shape);
  shape = cr1;
  Print(shape);
  // NOTE: we could simple write here the 2 lines below but it's mpre verbose above
  // Print(sq1);
  // Print(cr1);

  // ========================================================================
  // 3. This (abstraction) actually makes possible:
  //    - to implement the rest of the code without even knowing what 2D shapes
  //      will be eventually used since we can be sure, that independently from
  //      their actual type, all will (must) give back their area when the `Area`
  //      interface method is invokded
  //    - moreover, since all of them are actually 2D shapes (i.e. derived from the
  //      `VShape2D` base class), we can store all different 2D shapes in a single
  //      container, iterate over them, calling their `Area` interface methods will
  //      always invoke the apropriate implementation.
  std::cout << "\n  === Using the BASE in a (vector)container now  and the common Print function === \n" << std::endl;
  std::vector<VShape2D*> vect;
  vect.push_back(sq1);
  vect.push_back(cr1);
  // NOTE: we could use a nicer way of iterating over the vector but keep it simple
  for (std::size_t i=0; i<vect.size(); ++i) {
    Print(vect[i]);
  }

  std::cout << std::endl;
  return 0;
}


// implementation of the auxiliary print method
void Print(VShape2D* sh) {
  std::cout << " Area   = "   << sh->Area()
            << " Perim. = "   << sh->Perimeter()
            << " name   = "   << sh->GetName()
            << std::endl;
}
