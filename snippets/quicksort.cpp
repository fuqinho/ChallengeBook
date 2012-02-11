#include <iostream>
#include <vector>
using namespace std;

void quicksort(const vector<int>::iterator begin, const vector<int>::iterator end) {
  if (end - begin <= 1) return;
  // pivotには単純に先頭要素を使う
  int pivot = *begin;

  // 両サイドから走査して、pivot未満の要素とpivot以上の要素の
  // 組が見つかったらswap
  vector<int>::iterator left = begin, right = end - 1;
  do {
    while (*left < pivot && left < right) left++;
    while (*right >= pivot && left < right) right--; 
    if (left < right) {
      swap(*left, *right);
    }
  } while (left != right);

  // [begin, left)がpivot未満、[left, end)がpivot以上なので、
  // leftを境に分割する。ただしleft==beginの時は全要素pivot以上なので
  // pivotになった左端の要素は左側の区間に振り分けて区間を小さくする
  vector<int>::iterator mid = left;
  if (mid == begin) mid++;

  // 分割した区間に対して再帰的にsort
  quicksort(begin, mid);
  quicksort(mid, end);
}

// Randam test by comparing with std::sort
int test(int n) {
  int error_num = 0;
  for (int i = 0; i < n; i++) {
    int n = rand() % 1000;
    vector<int> v_orig(n);
    for (int j = 0; j < n; j++) v_orig[j] = rand() % 1000 - 500;

    vector<int> v1 = v_orig;
    vector<int> v2 = v_orig;
    sort(v1.begin(), v1.end());
    quicksort(v2.begin(), v2.end());
    //cerr << (v1 == v2 ? "OK" : "xxxx NG xxxx") << endl;
    if (v1 != v2) error_num++;
  }
  return error_num;
}

int main() {
  static const int a[] = {3, 2, 1, 2, 6, 5, 9, 1, 8};
  vector<int> v(sizeof(a) / sizeof(a[0]));
  v.assign(a, a + v.size());

  quicksort(v.begin(), v.end());

  for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
  cout << endl;

  int errors = test(1000);
  cerr << "errors: " << errors << endl;
}
