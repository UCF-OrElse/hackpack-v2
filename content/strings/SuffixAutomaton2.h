/**
 * Author: Sachin Sivakumar
 * Date: 2025-01-24
 * Description: Adds endpos (number of occurrences of substring),
 * to and from (number of paths to and from node), topsort of nodes
 * Status: works but not stress tested
 */
#pragma once

int endpos; ll to, from = 1; // add to end of st
a[last].endpos++; // add to end of char loop
// add to Suffix Automaton
vi topsort;
// add to end of constructor
vvi buckets(sz(a));
rep(u, 0, sz(a)) buckets[a[u].len].push_back(u);
rep(i, 0, sz(buckets))
	for(int u : buckets[i]) topsort.push_back(u);
for(int i = sz(a)-1; i >= 0; i--) {
	int u = topsort[i];
	for(auto [c, v] : a[u].next)
		a[u].from += a[v].from;
	if(u) a[a[u].link].endpos += a[u].endpos;
}
a[0].to = 1;
for(int u : topsort)
	for(auto [c, v] : a[u].next)
		a[v].to += a[u].to;
