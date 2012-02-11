#include <iostream>
using namespace std;

void print(int n) {
  for (int i = 7; i >= 0; i--) cout << ((n & (1 << i)) ? '1' : '0');
  cout << endl;
}

int main() {
  int sup = 0x6D; // 01101101
  
  /*
  int sub = sup;
  do {
    print(sub);
    sub = (sub - 1) & sup;
  } while (sub != sup);
  */

  int k = 4;
  int comb = (1 << k) - 1;
  while (comb < 1 << 8) {
    print(comb);
    int x = comb & -comb;
    int y = comb + x;
    comb = ((comb & ~y) / x >> 1) | y;
  }
}
