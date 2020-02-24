#ifndef EXC_HPP
#define EXC_HPP

using namespace std;

class EmptyException {
  public:
    EmptyException();
    string what() const;
  protected:
    string msg;
};

class NotFoundException {
  public:
    NotFoundException();
    string what() const;
  protected:
    string msg;
};

#endif