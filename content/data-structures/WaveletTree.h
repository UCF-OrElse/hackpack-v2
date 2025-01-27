/**
 * Author: Luke Videckis
 * Date: 2025-01-27
 * Source: https://github.com/programming-team-code/programming_team_code/blob/main/data_structures/seg_tree_uncommon/wavelet_matrix.hpp
 * Description: kth: finds k+1th smallest number in [l,r), count: rank of k (how many < k) in [l,r).
 * Doesn't support negative numbers, and requires a[i] <= maxval. Use BitVector to make 1.6x faster
 * and 4x less memory.
 * Time: O(\log MAX)
 * Status: tested on Range Kth Smallest on Yosupo
 */
#pragma once

struct WaveletTree {
	int n; vvi bv; // vector<BitVector> bv;
	WaveletTree(vl a, ll max_val):
		n(sz(a)), bv(1+__lg(max_val), {{}}) {
		vl nxt(n);
		for (int h = sz(bv); h--;) {
			vector<bool> b(n);
			rep(i, 0, n) b[i] = ((a[i] >> h) & 1);
			bv[h] = vi(n+1); // bv[h] = b;
			rep(i, 0, n) bv[h][i+1] = bv[h][i] + !b[i]; // delete
			array it{begin(nxt), begin(nxt) + bv[h][n]};
			rep(i, 0, n) *it[b[i]]++ = a[i];
			swap(a, nxt);
		}
	}
	ll kth(int l, int r, int k) {
		ll res = 0;
		for (int h = sz(bv); h--;) {
			int l0 = bv[h][l], r0 = bv[h][r];
			if (k < r0 - l0) l = l0, r = r0;
			else
				k -= r0 - l0, res |= 1ULL << h,
					l += bv[h][n] - l0, r += bv[h][n] - r0;
		}
		return res;
	}
	int count(int l, int r, ll ub) {
		int res = 0;
		for (int h = sz(bv); h--;) {
			int l0 = bv[h][l], r0 = bv[h][r];
			if ((~ub >> h) & 1) l = l0, r = r0;
			else
				res += r0 - l0, l += bv[h][n] - l0,
					r += bv[h][n] - r0;
		}
		return res;
	}
};
