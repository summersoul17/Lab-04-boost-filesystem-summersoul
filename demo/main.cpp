// Copyright 2021 Summersoul17 17summersoul17@gmail.com

#include <Boost-FileSystem.hpp>

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << Broker::Analyz(".", cout);
  } else if (argc == 2) {

    cout << Broker::Analyz(argv[1], cout);
  } else {
    cout << "Too many arguments!";
  }
}