// explicit Segtree

struct Segtree
{
	ll sum, max_seg, prefix, suffix;
};

Segtree t[4 * N];

Segtree combine(Segtree a, Segtree b)
{
	Segtree res;

	res.sum = a.sum + b.sum;

	res.max_seg = max({a.max_seg, b.max_seg, a.suffix + b.prefix});

	res.prefix = max(a.prefix, a.sum + b.prefix);

	res.suffix = max(b.suffix, b.sum + a.suffix);

	return res;
}

void build(ll node, ll leftmost, ll rightmost, ll a[])
{
	if (leftmost == rightmost)
	{
		t[node].sum = a[leftmost];
		t[node].prefix = a[leftmost];
		t[node].suffix = a[leftmost];
		t[node].max_seg = a[leftmost];

		return;
	}

	ll mid = (leftmost + rightmost) / 2;

	build(2 * node, leftmost, mid, a);

	build(2 * node + 1, mid + 1, rightmost, a);

	t[node] = combine(t[2 * node], t[2 * node + 1]);
}

void update(ll node, ll leftmost, ll rightmost, ll index, ll val)
{
	if (leftmost == index &&  rightmost == index)
	{
		t[node].sum = val;
		t[node].prefix = val;
		t[node].suffix = val;
		t[node].max_seg = val;

		return;
	}

	if (index > rightmost || index < leftmost)
		return;

	ll mid = (leftmost + rightmost) / 2;

	update(2 * node, leftmost, mid, index, val);

	update(2 * node + 1, mid + 1, rightmost, index, val);

	t[node] = combine(t[2 * node], t[2 * node + 1]);

}

Segtree Query(ll node, ll leftmost , ll rightmost, ll l , ll r)
{
	if (l > rightmost || r < leftmost)
	{
		Segtree res;

		res.sum = 0;

		res.prefix = -10007;
		res.suffix = -10007;
		res.max_seg = -10007;

		return res;
	}

	if (l <= leftmost && r >= rightmost)
	{
		return t[node];
	}

	ll mid = (leftmost + rightmost) / 2;

	return combine(Query(2 * node, leftmost, mid, l, r), Query(2 * node + 1, mid + 1, rightmost, l, r));
}
