#include <iostream>
#include "BigInt.h"

using namespace std;
#define uint unsigned int


int main() {
   string n;
   cin >> n;
   BigInt sq(n);
  cout << BigInt::Square_root(sq) << endl;
    return 0;
}