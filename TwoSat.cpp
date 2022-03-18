struct TwoSat
{
  int n;

  static const int V = 1e5 + 5;

  vector<int>adj[V], rev_adj[V];

  vector<int>order;

  int id[V];

  bool vis[V];

  TwoSat(int _n)
  {
    n = _n;

    order.clear();

    for (int i = 1; i <= 2 * n; i++)
    {
      adj[i].clear();
      rev_adj[i].clear();
    }
  }

  void add(int a, int b)
  {
    adj[a].push_back(b);

    rev_adj[b].push_back(a);
  }

  void add_or(int a1, bool flag1, int b1, bool flag2)
  {
    add(a1 + (flag1 ? n : 0), b1 + (flag2 ? 0 : n));
    add(b1 + (flag2 ? n : 0), a1 + (flag1 ? 0 : n));
  }

  void add_xor(int a1, bool flag1, int b1, bool flag2)
  {
    add_or(a1, flag1, b1, flag2);
    add_or(a1, !flag1, b1, !flag2);
  }

  void add_bi(int a1, bool flag1, int b1, bool flag2)
  {
    add_xor(a1, !flag1, b1, flag2);
  }

  void dfs1(int node)
  {
    vis[node] = true;

    for (auto it : adj[node])
    {
      if (!vis[it])
        dfs1(it);
    }

    order.push_back(node);
  }

  void dfs2(int node, int k)
  {
    vis[node] = true;

    id[node] = k;

    for (auto it : rev_adj[node])
    {
      if (!vis[it])
        dfs2(it, k);
    }
  }

  bool solve(vector<int>&ans)
  {
    memset(vis, false, sizeof(vis));

    for (int i = 1; i <= 2 * n; i++)
    {
      if (!vis[i])
        dfs1(i);
    }

    memset(vis, false, sizeof(vis));

    reverse(order.begin(), order.end());

    int k = 0;

    for (auto it : order)
    {
      if (!vis[it])
        dfs2(it, ++k);
    }

    for (int i = 1; i <= n; i++)
    {
      if (id[i] == id[n + i])
        return false;

      if (id[i] < id[n + i])
        ans.push_back(0);

      if (id[i] > id[n + i])
        ans.push_back(1);
    }

    return true;
  }
};
