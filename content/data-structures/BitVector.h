/**
 * Author: Luke Videckis
 * Date: 2025-01-27
 * Source: https://github.com/programming-team-code/programming_team_code/blob/main/data_structures/seg_tree_uncommon/wavelet_bit_vec.hpp
 * Description: Given vector of bits, counts number of 0's in [0, r). Use with WaveletTree.h by 
 * using modifications in comments in that file and replacing bv[h][x] with bv[h].cnt0(x)
 * Time: $O(1)$ time
 * Status: tested on Range Kth Smallest on Yosupo
 */
#pragma once

struct BitVector {
	vector<pair<ll, int>> b;
	BitVector(vector<bool> a): b(sz(a) / 64 + 1) {
		rep(i, 0, sz(a))
			b[i >> 6].first |= ll(a[i]) << (i & 63);
		rep(i, 0, sz(b)-1)
			b[i + 1].second = __builtin_popcountll(b[i].first) 
				+ b[i].second;
	}
	int cnt0(int r) {
		auto [x, y] = b[r >> 6];
		return r - y 
			- __builtin_popcountll(x & ((1ULL << (r & 63)) - 1));
	}
};
