/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vi tin, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int u, G& g, F& f) {
	int low = tin[u] = ++Time, x; z.push_back(u);
	for (auto v : g[u]) if (comp[v] < 0)
		low = min(low, tin[v] ?: dfs(v,g,f));

	if (low == tin[u]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != u);
		f(cont); cont.clear();
		ncomps++;
	}
	return tin[u] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	tin.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}
