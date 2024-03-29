///////////////////////////////////////////////////////////////////////////////
// ActionFactory.h
// The ActionFactory class is used to instantiate objects of the Action class.
// It takes as input a char which represents the specific concrete movie class
// desired.  It uses a hash function to determine which object to create based
// on that char, then returns a pointer to that new movie object.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_ACTIONFACTORY_H
#define CSS343_LAB4_ACTIONFACTORY_H

#include <tr1/unordered_map>

class Action;
class Store;

class ActionFactory
{
public:
  ActionFactory();
  ~ActionFactory();

  // Returns an instantiated Action object of the correct type
  // @param actionType - character representing the action to return
  //        'B' -> Borrow
  //        'S' -> ShowMovie
  // @param store - the store whose data will be used by the action
  Action* Create(const char, Store&) const;

private:
  // Returns the concrete objects
  static Action* MakeBorrow(Store&);
  static Action* MakeReturn(Store&);
  static Action* MakeDisplayCustomerHistory(Store&);
  static Action* MakeShowMovies(Store&);

  struct CharHash { // creates hash value for characters
    std::size_t operator() (const char) const;
  };

  // fcn pointer: Action* ActionBuilder(Store&)
  typedef Action* (*ActionBuilder)(Store&);
  typedef std::tr1::unordered_map<char, ActionBuilder, CharHash> BuilderHash;

  BuilderHash action_builder_; // hash of functions to create new movies
};

#endif
