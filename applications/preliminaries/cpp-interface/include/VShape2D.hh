

// This is called "include guard": used to avoid double inclusion that would
// lead to double definition. Very good practice, check it and use.
#ifndef VSHAPE2D_HH
#define VSHAPE2D_HH

#include <string>

/**
 * @file   VShape2D.hh
 * @class  VShape2D
 * @author M. Novak
 * @date   May 2022
 *
 * **Interface**, i.e. base class with a **pure virtual** method, for 2D shape area computations.
 *
 * This base class is an **interface** for 2D shape area computations. It has its
 * **pure virtual** Area() method. Therefore, this method **must be implemented
 * by each derived** classes. This ensures, that whatever type of an actuall 2D
 * shape is (derived from this base class) the Area() interface method will be
 * available. Therefore, the rest of the code can be developed without knowing
 * what 2D shapes will be eventually there: they will be all `VShape2D` types
 * providing their own implementation of the Area() interface method defined
 * in this base class.
 *
 * Note, that the **pure virtual** method makes this base class **abstract**,
 * i.e. objects cannot be instantiated directly form this base class.
 */

// The `VShape2D` base class definition.
class VShape2D {

public:

  // constructor: requires the name of the shape
  VShape2D(const std::string& name) : fName(name) { }
  // destructor: no dynamic memory allocation so nothing to do
  virtual ~VShape2D() { }

  // public method to get the name: short so we implement here
  const std::string& GetName() const { return fName; }

  /**
   * The area computation *interface* method.
   *
   * Example of a **pure virtual** method that makes this base class **abstract**.
   *
   * Each 2D shape has an area but all computed differently depending on the
   * actual type of the shape. This is why it's a **pure virtual method**, i.e.
   * **each derived class must implement**.
   */
  virtual double Area() = 0;

  /**
   * *Optional* perimeter computation method.
   *
   * Example of a **virtual** method with defult implementation in the base class.
   *
   * Each 2D shape has its own way of computing the perimeter just like the area.
   * However, we decided that actually the perimeter is not important for our
   * algorithm in most cases of shapes. Therefore, this default implementation
   * is available for each derived class and will be invoked unless the concrete
   * derived class provides its own implementation. The derived `Square` class
   * implements this method while `Circle` relyes on this defult base class
   * implementation.
   */
  virtual double Perimeter() { return 0.0; }


private:

 // name of the shape
 std::string  fName;

};

#endif // VSHAPE2D_HH
