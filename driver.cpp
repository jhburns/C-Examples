#include <iostream>

#include "def.hpp"

using namespace std;

int main()
{
  try {
    //For testing
    cout << "Hello!" << endl;

  } catch(NotFoundException& e) {
    cout << e.what() << endl;
    return 1;
  } catch(EmptyException& e) {
    cout << e.what() << endl;
    return 1;
  } catch(exception& e) {
    cout << e.what() << endl;
    return 1;
  }

  return 0;
}
