/**
 * Author: Luke Videckis
 * Date: 2024-05-21
 * Source: https://github.com/programming-team-code/programming_team_code/
 * Description: Recursively splits a tree into two edge sets that share a centroid.
 * Consider all paths that pass through the centroid and use at least one edge from
 * each set. A node can be a centroid multiple times. Consider all length 1 paths separately.
 * Callback takes the graph, centroid, and split, where edges $[0, split)$ from $adj[centroid]$
 * are in the first set and the rest are in the second set.
 * Usage: edge_cd(adj, [\&](const vector<vector<int>>\& adj, int cent, int split) { \ldots\ });
 * Time: $O(n \log n)$
 * Status: Untested
 */
#pragma once

template <class F> struct edge_cd {
	vvi adj;
	F f;
	vi sub_sz;
	edge_cd(const vvi& adj, F f) : adj(adj), f(f), 
		sub_sz(sz(adj)) {
		dfs(0, sz(adj) - 1);
	}
	int find_cent(int u, int p, int siz) {
		sub_sz[u] = 1;
		for (int v : adj[u]) if (v != p) {
			int cent = find_cent(v, u, siz);
			if (cent != -1) return cent;
			sub_sz[u] += sub_sz[v];
		}
		return 2 * sub_sz[u] > siz ? 
			p >= 0 && (sub_sz[p] = siz + 1 - sub_sz[u]), u : -1;
	}
	void dfs(int u, int siz) {
		if (siz < 2) return;
		u = find_cent(u, -1, siz);
		int sum = 0;
		auto it = partition(all(adj[u]), [&](int v) {
			ll x = sum + sub_sz[v];
			return x * x < siz * (siz - x) ? sum += sub_sz[v], 1 : 0;
		});
		f(adj, u, it - begin(adj[u]));
		vi oth(it, end(adj[u]));
		adj[u].erase(it, end(adj[u]));
		dfs(u, sum);
		swap(adj[u], oth);
		dfs(u, siz - sum);
	}
};
