
#ifndef SQUARE_HH
#define SQUARE_HH

// inlcude the base class definition
#include "VShape2D.hh"

/**
 * @file   Square.hh
 * @class  Square
 * @author M. Novak
 * @date   May 2022
 *
 * @brief Derived class that implements the VShape2D interface for Square-s.
 */

// square is a derived from the 2D shape base class
class Square : public VShape2D {

public:

  // constructor: requires the length of the side
  // - it calls the base class constructor by passing the required name
  Square(double lside) : VShape2D("mySquare"), fSideLength(lside) { }

  // no dynamic memeory allocation so nothing to do at destruction
  ~Square() { }


  /**
   * Actual implementation of the area computation interface method of the
   * base class.
   *
   * Square **must implement** the VShape2D::Area base class method since that's
   * a **pure virtual method**.
   *
   * @note The `override` keyword is very useful: indicates that this method
   *  implements a virtual method of the base class so the compiler is
   *  aware of that intention.
   */
  double Area() override { return fSideLength*fSideLength; }

  /** The **optional** `Perimeter` interface method implementation. */
  double Perimeter() override { return 4.0*fSideLength; }


private:

  // the only data member is the length of the edge
  double  fSideLength;

};

#endif  // SQUARE_HH
