/**
 * Author: Andy Phan
 * Source: my brain
 * Description: decomposes (l, r) range into pair of (list of fully covered blocks, list of partially covered blocks)
 * Time: $O(B + (r - l)/B)$
 */
template<int B>
pair<vi, vector<array<int, 3>>> decomp(int l, int r) {
	if (l/B == (r-1)/B) return {{}, {{l/B, l, r}}};
    vi full;
	vector<array<int, 3>> subs;
	if (l%B != 0) {
		subs.push_back({l/B, l, (l/B+1)*B});
		l = subs.back()[2];
	}
	if (r%B != 0) {
		subs.push_back({r/B, r/B*B, r});
		r = subs.back()[1];
	}
	rep(i, l/B, r/B) full.push_back(i);
	return {full, subs};
}
