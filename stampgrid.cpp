#include <iostream>
#include <vector>
using namespace std;
bool check (int i, int j, vector<vector<int>>& stamp, vector<vector<int>>& desired, vector<vector<int>>& copy) {
  bool c = true;
  for (int p = i; p < stamp.size() + i; ++p) {
    for (int l = j; l < stamp.size() + j; ++l) {
      if (stamp[p-i][l-j]) {
        if (!desired[p][l]) {
          c = false;
        }
      }
    }
  }
  if (!c) {
    return false;
  }
  for (int p = i; p < stamp.size() + i; ++p) {
    for (int l = j; l < stamp.size() + j; ++l) {
      if (stamp[p-i][l-j]) {
        copy[p][l] = 1;
      }
    }
  }
  return true;
}
vector<vector<int>> rotate(vector<vector<int>>& stamp) {
  int n = stamp.size();
  vector<vector<int>> trans(n);
  for (int j = 0; j < n; ++j) {
    for (int i = n - 1; i >= 0; i--) {
      trans[j].push_back(stamp[i][j]);
    }
  }
  return trans;
}
void solve () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n;
  vector<string> grid1;
  vector<vector<int>> desired(n, vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    grid1.push_back(s);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) { 
      if (grid1[i][j] == '*') {
        desired[i][j] = 1;
      }
    }
  }
  cin >> k;
  vector<string> grid2;
  vector<vector<int>> stamp(k, vector<int>(k, 0));
  vector<vector<int>> copy(n, vector<int>(n, 0));
  for (int i = 0; i < k; ++i) {
    string s;
    cin >> s;
    grid2.push_back(s);
  }
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (grid2[i][j] == '*') {
        stamp[i][j] = 1;
      }
    }
  }
  for (int p = 0; p < 4; ++p) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i < n-k + 1 && j < n-k+1) {
          check(i, j, stamp, desired, copy);
        }
      }
    }
    stamp = rotate(stamp);
  }
  bool y = true;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (desired[i][j] && !copy[i][j]) {
        y = false;
      }
      else if (copy[i][j] && !desired[i][j]) {
        y = false;
      }
    }
  }
  if (y) {
    cout << "YES" << '\n';
  }
  else {
    cout << "NO" << '\n';
  }
}
int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}