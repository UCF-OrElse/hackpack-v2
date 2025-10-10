/**
 * Author: Luke Videckis
 * Date: 2024-02-20
 * Source: https://github.com/programming-team-code/programming_team_code/blob/main/convolution/gcd_convolution.hpp
 * Description: Returns $\displaystyle c[k] = \sum_{gcd(i,j)=k} a[i] \cdot b[j]$.
 * Time: O(n \log n)
 * Status: unknown
 */
#pragma once

const int mod = 998'244'353;
vector<int> gcd_convolution(const vector<int>& a,
  const vector<int>& b) {
  int n = ssize(a);
  vector<int> c(n);
  for (int g = n - 1; g >= 1; g--) {
    int64_t sum_a = 0, sum_b = 0;
    for (int i = g; i < n; i += g) {
      sum_a += a[i], sum_b += b[i];
      if ((c[g] -= c[i]) < 0) c[g] += mod;
    }
    sum_a %= mod, sum_b %= mod;
    c[g] = (c[g] + sum_a * sum_b) % mod;
  }
  return c;
}
