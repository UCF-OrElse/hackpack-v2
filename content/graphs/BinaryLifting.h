
/**
 * Author: Luke Videckis
 * Source: https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/graphs/TreeLifting.h
 * Description: lca and kth\_parent queries
 * Time: construction $O(N)$, queries $O(\log N)$
 */
#pragma once

struct tree_lift {
	struct node {
		int d, p = -1, j = -1;
	};
	vector<node> t;
	tree_lift(const auto& adj): t(ssize(adj)) {
		auto dfs = [&](auto&& self, int v) -> void {
		int jump =
			(t[v].d + t[t[t[v].j].j].d == 2 * t[t[v].j].d)
			? t[t[v].j].j
			: v;
		for (int u : adj[v])
			if (u != t[v].p)
				t[u].d = t[t[u].p = v].d + 1, t[u].j = jump,
				self(self, u);
		};
		for (int i = 0; i < ssize(t); i++)
		if (t[i].j == -1) t[i].j = i, dfs(dfs, i);
	}
	int kth_par(int v, int k) {
		int anc_d = t[v].d - k;
		while (t[v].d > anc_d)
			v = t[t[v].j].d >= anc_d ? t[v].j : t[v].p;
		return v;
	}
	int lca(int u, int v) {
		if (t[u].d < t[v].d) swap(u, v);
		u = kth_par(u, t[u].d - t[v].d);
		while (u != v)
			if (t[u].j != t[v].j) u = t[u].j, v = t[v].j;
			else u = t[u].p, v = t[v].p;
		return u;
	}
	int dist_edges(int u, int v) {
		return t[u].d + t[v].d - 2 * t[lca(u, v)].d;
	}
};
