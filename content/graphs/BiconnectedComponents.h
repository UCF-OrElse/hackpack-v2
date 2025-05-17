/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

vi tin, st;
vector<vector<pii>> ed;
int Time;
template<class F>
int dfs(int cur, int par, F& f) {
	int me = tin[cur] = ++Time, low = me;
	for (auto [nxt, e] : ed[cur]) if (e != par) {
		if (tin[nxt]) {
			low = min(low, tin[nxt]);
			if (tin[nxt] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(nxt, e, f);
			low = min(low, up);
			if (up >= me) { // e is a bridge if up > me
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else st.push_back(e);
		}
	}
	return low;
}

template<class F>
void bicomps(F f) {
	tin.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!tin[i]) dfs(i, -1, f);
}
