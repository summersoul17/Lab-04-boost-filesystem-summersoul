// Copyright 2021 Summersoul17 17summersoul17@gmail.com

#include <Boost-FileSystem.hpp>

bool Broker::isRightFile(const boost::filesystem::path &fileName) {
  return (fileName.stem().extension().string() != ".old" &&
          fileName.filename().string().find("balance") != string::npos);
}

void splitString(const string &text, string& ID, string& date) {
  vector<string> bid;
  for (auto i = text.cbegin(); i != text.cend();) {
    i = find_if(i, text.end(), not_separator);
    auto j = find_if(i, text.end(), separator);
    bid.emplace_back(i, j);
    i = j;
  }
  if (bid.size() == 3) {
    ID = bid[1];
    date = bid[2];
  }
}

Broker Broker::InspectSingleBroker(const boost::filesystem::path &p) {
  Broker broker(p.filename().string());
  for (const auto& x : boost::filesystem::directory_iterator{p})
  {
    if(!is_directory(x)) {
      if (isRightFile(x.path())) {
        string accountID;
        string accountDate;

        splitString(x.path().stem().string(), accountID, accountDate);

        if(broker.accounts.find(accountID) != broker.accounts.end()) {
          BrokerAccount::SetDate(broker.accounts[accountID], accountDate);
        } else {
          broker.accounts.insert(make_pair<string, BrokerAccount>(accountID.c_str(), BrokerAccount(accountDate)));
        }
      }
    }
  }
  return broker;
}

vector<Broker> Broker::Inspect(const boost::filesystem::path& p, ostream& os) {
  vector<Broker> back;
  if (!boost::filesystem::is_directory(p))
    throw runtime_error("argument must be path to Broker directory, not file");
  for (const auto& x : boost::filesystem::directory_iterator{p})
  {
    if(!is_directory(x)) {
      if (isRightFile(x.path())) {
        os << x.path().filename().string() << "\n";
      }
    } else if (is_directory(x)) {
      stringstream out;
      out << x.path().filename().string() << "\n";
      Inspect(x.path(), out);
      if(out.str() != x.path().filename().string() + "\n"){
        os << out.str();
        back.emplace_back(Broker::InspectSingleBroker(x.path()));
      }
    } else {
      os << "This is not a regular file or dir!\n";
    }
  }
  return back;
}

ostream &operator<<(ostream &os, const vector<Broker>& brokers) {
  if (brokers.empty()) {
    os << "Brokers array is empty!\n";
  } else {
    os << std::endl;
    for (const auto& broker : brokers) {
      for (const auto& account : broker.accounts) {
        os << "broker:" << broker.name + " "
           << "account:" << account.first
           << " files:" << account.second.getFileNum()
           << " lastdate:" << account.second.getLastDate() << std::endl;
      }
    }
  }
  return os;
}
