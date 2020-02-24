#include <iostream>

#include "list.hpp"
#include "exceptions.hpp"
#include "tree.hpp"

using namespace std;

int main()
{
  try {
    //Test anything here
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
