// Copyright 2020 Novo Yakov xaxaxaxa232@mail.ru

#include <Broker.hpp>

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << Broker::Inspect(".", cout);
  } else if (argc == 2) {

    cout << Broker::Inspect(argv[1], cout);
  } else {
    cout << "Too many arguments!";
  }
}