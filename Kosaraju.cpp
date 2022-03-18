#define N 100001

vector<int>adj[N];
vector<int>tra[N];
vector<int>order;
int scc = 0;
int vis[N];

void dfs(int node)
{
  vis[node] = 1;

  for (auto child : adj[node])
  {
    if (!vis[child])
      dfs(child);
  }

  order.push_back(node);
}

void dfs1(int node)
{
  vis[node] = 1;

  scc++;

  for (auto child : tra[node])    // kosaraju algorithm for strongly connected component
  {
    if (!vis[child])
      dfs1(child);
  }
}

void kosaraju()
{
  int n;

  cin >> n;

  int a[n];

  for (int i = 0; i < n; i++)
    adj[i].clear(), tra[i].clear(), vis[i] = 0;

  order.clear();

  for (int i = 0; i < n; i++)
  {
    cin >> a[i];

    int b = (a[i] + 1 + i) % n;

    adj[i].push_back(b);
    tra[b].push_back(i);
  }

  for (int i = 0; i < n; i++)
  {
    if (!vis[i])
      dfs(i);
  }

  memset(vis, 0, sizeof(vis));

  int ans = 0;

  for (int i = n - 1; i >= 0; i--)
  {
    if (!vis[order[i]])
    {
      dfs1(order[i]);

      ans += 1;
    }
  }

  cout << ans << endl;
}