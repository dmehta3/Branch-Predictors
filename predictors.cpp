#include <bits/stdc++.h>
using namespace std;

void readtaken(string input, ofstream& outfile) {
  ifstream infile(input);
  unsigned long addr;
  string behavior;
  unsigned long target;
  int total = 0;
  int taken = 0;
  
  while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    if (behavior == "T") {
      taken++;
    }
    total++;
  }

  outfile << taken << "," << total << ";" << endl;
  infile.close();
}

void readnottaken(string input, ofstream& outfile) {
  ifstream infile(input);
  unsigned long addr;
  string behavior;
  unsigned long target;
  int total = 0;
  int notTaken = 0;

  while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    if (behavior == "NT") {
      notTaken++;
    }
    total++;
  }
  outfile << notTaken << "," << total << ";" << endl;
  infile.close();
}

void bimodal(string input, ofstream& outfile) {
  ifstream infile(input);
  unsigned long addr;
  string behavior;
  unsigned long target;
  vector<unsigned long> addresses;
  vector<bool> behaviors;

  while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    addresses.push_back(addr);
    if (behavior == "T") {
      behaviors.push_back(true);
    } else {
      behaviors.push_back(false);
    }
  }

  vector<int> sizes{16, 32, 128, 256, 512, 1024, 2048};

  for (int i = 0; i < sizes.size(); i++) {
    int predictions = 0;
    vector<bool> table;
    for (int j = 0; j < sizes[i]; j++) {
      table.push_back(true);
    }

    int sBit;
    for (int k = 0; k < addresses.size(); k++) {
      sBit = addresses[k] % sizes[i];
      if (table[sBit] == behaviors[k]) {
        predictions++;
      } else if (behaviors[k] == true) {
        table[sBit] = true;
      } else if (behaviors[k] == false) {
        table[sBit] = false;
      }
    }
    
    if ((i+1) == sizes.size()) 
      outfile << predictions << "," << addresses.size() << ";";
    else
      outfile << predictions << "," << addresses.size() << "; ";
  }
  outfile << endl;
  infile.close();
}

void twobit(string input, ofstream& outfile) {
  ifstream infile(input);
  unsigned long addr;
  string behavior;
  unsigned long target;
  vector<unsigned long> addresses;
  vector<bool> behaviors;

  while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    addresses.push_back(addr);
    if (behavior == "T") {
      behaviors.push_back(true);
    } else {
      behaviors.push_back(false);
    }
  }

  vector<int> sizes{16, 32, 128, 256, 512, 1024, 2048};
  for (int i = 0; i < sizes.size(); i++) {
    unsigned long counter = 0;
    vector<int> v;
    for (int z = 0; z < sizes[i]; z++) {
      v.push_back(3);
    }
    for (int j = 0; j < addresses.size(); j++) {
      unsigned long val = addresses[j] % sizes[i];
      if (behaviors[j]) {
        if (v[val] == 2 || v[val] == 3) {
          counter++;
        }
        if (v[val] < 3) {
          v[val]++;
        }
      } else {
        if (v[val] == 0 || v[val] == 1) {
          counter++;
        }
        if (v[val] > 0) {
          v[val]--;
        }
      }
    }
    if ((i+1) == sizes.size()) 
      outfile << counter << "," << addresses.size() << ";";
    else
      outfile << counter << "," << addresses.size() << "; ";
  }
  outfile << endl;
  infile.close();
}

void gshare(string input, ofstream& outfile) {
  ifstream infile(input);
  unsigned long addr;
  string behavior;
  unsigned long target;
  unsigned long ghr = 0;
  vector<unsigned long> addresses;
  vector<bool> behaviors;

  while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    addresses.push_back(addr);
    if (behavior == "T") {
      behaviors.push_back(true);
    } else {
      behaviors.push_back(false);
    }
  }

  for (int i = 3; i < 12; i++) {
    vector<int> v;
    for (int k = 0; k < 2048; k++) {
      v.push_back(3);
    }
    unsigned long counter = 0;
    unsigned long ghr = 0;
    unsigned long size = pow(2, i) - 1;
    for (int j = 0; j < addresses.size(); j++) {
      unsigned long val = (addresses[j] ^ (ghr & size)) % 2048;
      ghr <<= 1;
      if (behaviors[j]) {
        if (v[val] == 2 || v[val] == 3) {
          counter++;
        }
        if (v[val] < 3) {
          v[val]++;
        }
        ghr |= 1;
      } else {
        if (v[val] == 0 || v[val] == 1) {
          counter++;
        }
        if (v[val] > 0) {
          v[val]--;
        }
        ghr |= 0;
      }
    }
    if ((i+1) == 12) 
      outfile << counter << "," << addresses.size() << ";";
    else
      outfile << counter << "," << addresses.size() << "; ";
  }
  outfile << endl;
  infile.close();
}

void tournament(string input, ofstream& outfile) {
  ifstream infile(input);
  unsigned long addr;
  string behavior;
  unsigned long target;
  unsigned long ghr = 0;
  unsigned long size = pow(2, 11) - 1;
  unsigned long counter = 0;
  vector<unsigned long> addresses;
  vector<bool> behaviors;

  while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    addresses.push_back(addr);
    if (behavior == "T") {
      behaviors.push_back(true);
    } else {
      behaviors.push_back(false);
    }
  }

  vector<int> bimodal;
  vector<int> gshare;
  vector<int> select;
  for (int k = 0; k < 2048; k++) {
    bimodal.push_back(3);
    gshare.push_back(3);
    select.push_back(0);
  }

  for (int i = 0; i < addresses.size(); i++) {
    bool bimodalStatus = false;
    bool gshareStatus = false;
    bool selectStatus;

    unsigned long val = addresses[i] % 2048;

    if (behaviors[i]) {
      if (bimodal[val] == 2 || bimodal[val] == 3) {
        bimodalStatus = true;
      } 
      if (bimodal[val] < 3) {
        bimodal[val]++;
      }
    } else {
      if (bimodal[val] == 0 || bimodal[val] == 1) {
        bimodalStatus = true;
      } 
      if (bimodal[val] > 0) {
        bimodal[val]--;
      }
    }

    unsigned long val1 = (addresses[i] ^ (ghr & size)) % 2048;
    ghr <<= 1;
    if (behaviors[i]) {
      if (gshare[val1] == 2 || gshare[val1] == 3) {
        gshareStatus = true;
      } 
      if (gshare[val1] < 3) {
        gshare[val1]++;
      }
      ghr |= 1;
    } else {
      if (gshare[val1] == 0 || gshare[val1] == 1) {
        gshareStatus = true;
      } 
      if (gshare[val1] > 0) {
        gshare[val1]--;
      }
      ghr |= 0;
    }

    if (gshareStatus == bimodalStatus) {
      if (gshareStatus) {
        counter++;
      }
    } else {
      if (select[val] == 2 || select[val] == 3) {
        if (bimodalStatus) {
          counter++;
          if (select[val] == 2) {
            select[val]++;
          }
        } else {
          if (select[val] > 0) {
            select[val]--;
          }
        }
      } else {
        if (gshareStatus) {
          counter++;
          if (select[val] == 1) {
            select[val]--;
          }
        } else {
          if (select[val] < 3) {
            select[val]++;
          }
        }
      }
    }
  }
  outfile << counter << "," << addresses.size() << ";" << endl;
  infile.close();
}

void btb(string input, ofstream& outfile) {
  ifstream infile(input);
  unsigned long addr;
  string behavior;
  unsigned long target;
  unsigned long counter = 0;
  unsigned long tCounter = 0;
  vector<unsigned long> addresses;
  vector<bool> behaviorVect;
  vector<bool> status;
  vector<unsigned long> targets;
  vector<unsigned long> points;
  unsigned long val = 0;

  while (infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    addresses.push_back(addr);
    targets.push_back(target);
    if (behavior == "T") {
      status.push_back(true);
    } else {
      status.push_back(false);
    }
  }

  for (int i = 0; i < 512; i++) {
    behaviorVect.push_back(true);
    points.push_back(0);
  }

  for (int j = 0; j < addresses.size(); j++) {
    val = addresses[j] % 512;

    if (behaviorVect[val]) {
      tCounter++;
      if (points[val] == targets[j]) {
        counter++;
      } 
    }   
    if (status[j]) {
      points[val] = targets[j];
    } 
    if (status[j] != behaviorVect[val]) {
      behaviorVect[val] = status[j];
    }
  }
  outfile << counter << "," << tCounter << ";" << endl;
  infile.close();
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Too few arguments" << endl;
    return 0;
  }

  ofstream outfile(argv[2]);
  readtaken(argv[1], outfile);
  readnottaken(argv[1], outfile);
  bimodal(argv[1], outfile);
  twobit(argv[1], outfile);
  gshare(argv[1], outfile);
  tournament(argv[1], outfile);
  btb(argv[1], outfile);
  outfile.close();
  return 0;
}