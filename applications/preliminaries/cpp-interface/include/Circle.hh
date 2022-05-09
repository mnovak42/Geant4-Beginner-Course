

#ifndef CIRCLE_HH
#define CIRCLE_HH

// inlcude the base class definition
#include "VShape2D.hh"


/**
 * @file   Circle.hh
 * @class  Circle
 * @author M. Novak
 * @date   May 2022
 *
 * @brief Derived class that implements the VShape2D interface for Circle-s.
 */

// square is a 2D shape
class Circle : public VShape2D {

public:

  // constructor: requires the length of the radius
  // - it calls the base class constructor by passing the required name
  Circle(double lradius) : VShape2D("myCircle"), fRadius(lradius) { }

  // no dynamic memeory allocation so nothing to do at destruction
  ~Circle() { }


  // MUST implement the `Shape2D::Area` base class method since that's a pure
  // virtual/abstract method. The `override` keyword is very useful: indicates
  // that this method implements a virtual method of the base class so the
  // compiler is aware of that

  /**
   * Actual implementation of the area computation interface method of the
   * base class.
   *
   * Circle **must implement** the VShape2D::Area base class method since that's
   * a **pure virtual method**.
   */
  double Area() override {
    const double kPi = 3.14159265359;
    return kPi*fRadius*fRadius;
  }

  // note: we decided not to implement the optional `Perimeter` interface method
  //       so its default base class implementation will be used for `Circle`-s!


private:

  // the only data member is the radius of the circle
  double  fRadius;

};

#endif  // CIRCLE_HH
