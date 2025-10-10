/**
 * Author: Luke Videckis
 * Date: 2024-02-20
 * Source: https://github.com/programming-team-code/programming_team_code/blob/main/convolution/lcm_convolution.hpp
 * Description: Returns $\displaystyle c[k] = \sum_{lcm(i,j)=k} a[i] \cdot b[j]$.
 * Time: O(n \log n)
 * Status: unknown
 */
#pragma once

const int mod = 998'244'353;
vector<int> lcm_convolution(const vector<int>& a,
  const vector<int>& b) {
  int n = ssize(a);
  vector<int64_t> sum_a(n), sum_b(n);
  vector<int> c(n);
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j += i)
      sum_a[j] += a[i], sum_b[j] += b[i];
    sum_a[i] %= mod, sum_b[i] %= mod;
    c[i] = (c[i] + sum_a[i] * sum_b[i]) % mod;
    for (int j = i + i; j < n; j += i)
      if ((c[j] -= c[i]) < 0) c[j] += mod;
  }
  return c;
}
