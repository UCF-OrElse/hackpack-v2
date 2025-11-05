/**
 * Author: Nic Washbourne
 * Date: 2025-09-26
 * Source: Sachin Sivakumar
 * Description: Generic reroot DP with decombine. The provided operations solve sum of distances to all nodes.
 * Time: O(N)
 * Status: Tested on CSES: Tree Distances II
 */
#pragma once

using T = pair<ll, ll>;
T init() { return {1, 0}; }
T combine(T a, T b) { return {a.first + b.first, a.second + b.second + b.first}; }
T decombine(T a, T b) { return {a.first - b.first, a.second - b.second - b.first}; }

vector<vi> adj;
vector<T> dp, dpr;

T dfs(int u, int p) {
	dp[u] = init();
	for (int v : adj[u]) {
		if (v == p) continue;
		dp[u] = combine(dp[u], dfs(v, u));
	}
	return dp[u];
}

T dfsr(int u, int p, T dpr_p = init()) {
	dpr[u] = dp[u];
	if (p != u) dpr[u] = combine(dpr[u], dpr_p);
	for (int v : adj[u]) {
		if (v == p) continue;
		T dec = decombine(dpr[u], dp[v]);
		dfsr(v, u, dec);
	}
	return dpr[u];
}
