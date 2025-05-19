
/**
 * Author: Luke Videckis
 * Source: https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/graphs/TreeLifting.h
 * Description: kth on path, goes in tree\_lift
 * Time: $O(\log N)$
 */
int kth_path(int u, int v, int k) {
    int lca_d = t[lca(u, v)].d;
    int u_lca = t[u].d - lca_d;
    int v_lca = t[v].d - lca_d;
    if (k <= u_lca) return kth_par(u, k);
    if (k <= u_lca + v_lca)
        return kth_par(v, u_lca + v_lca - k);
    return -1;
}