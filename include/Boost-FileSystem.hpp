// Copyright 2021 Summersoul17 17summersoul17@gmail.com

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <boost/filesystem.hpp>
#include <utility>
#include <map>
#include <sstream>

using std::cout;
using std::string;
using std::vector;
using std::stringstream;
using std::ostream;
using std::find_if;
using std::make_pair;
using std::runtime_error;
using std::move;
using std::map;

class Broker {
 private:
  class BrokerAccount {
   private:
    string last_date;
    size_t count_of_files{};
   public:
    inline static void SetDate(BrokerAccount& account, const string& date) {
      account.count_of_files++;
      if (atoi(date.c_str()) > atoi(account.last_date.c_str())) {
        account.last_date = date;
      }
    }
    BrokerAccount() = default;
    explicit BrokerAccount(string date)
        : last_date(move(date)), count_of_files(0){};
    [[nodiscard]] size_t FileCount() const { return count_of_files; }
    [[nodiscard]] string LastDate() const { return last_date; }
  };
  map<string, BrokerAccount> accounts;
  string name;

 public:
  static Broker AnalyzerSingleBroker(const boost::filesystem::path& p);
  explicit Broker(string n) : name(move(n)) {}
  friend ostream& operator<<(ostream& os, const vector<Broker>& brokers);
  static vector<Broker> Analyz(const boost::filesystem::path& p, ostream& os);
  inline static bool CorrectFileName(const boost::filesystem::path& fileName);
};

inline bool separator(char c) { return c == '_'; }
inline bool not_separator(char c) { return !separator(c); }

#endif // INCLUDE_HEADER_HPP_
