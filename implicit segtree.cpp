struct Segtree
{
  ll leftmost, rightmost;
  ll sum;
  Segtree *lchild, *rchild;
  bool lazy = false;
  ll upd = 0;

  Segtree(ll leftmost, ll rightmost)
  {
    this->leftmost = leftmost;
    this->rightmost = rightmost;

    if (leftmost == rightmost)
    {
      sum = 0;
      return;
    }

    ll mid = (leftmost + rightmost) / 2;

    lchild = new Segtree(leftmost, mid);

    rchild = new Segtree(mid + 1, rightmost);

    calc();

  }

  void calc()
  {
    if (leftmost == rightmost)
    {
      return;
    }

    sum = lchild->sum + rchild->sum;
  }

  void update(ll index, ll val)   // updates in O(logn)
  {
    if (leftmost == rightmost)
    {
      sum = val;
      return;
    }

    if (index <= lchild->rightmost)
    {
      lchild->update(index, val);
    }
    else
    {
      rchild->update(index, val);
    }

    calc();
  }

  void apply(ll val)
  {
    sum += (rightmost - leftmost + 1) * val;

    if (leftmost != rightmost)
    {
      lazy = 1;
      upd += val;
    }
  }

  void propagate()
  {
    if (lazy)
    {
      lchild->apply(upd);
      rchild->apply(upd);
      lazy = 0;
      upd = 0;
    }
  }

  void rangeupdate(ll l, ll r, ll val)
  {
    if (l > rightmost || r < leftmost)
      return;

    if (l <= leftmost && r >= rightmost)
    {
      apply(val);
      return;
    }

    propagate();

    lchild->rangeupdate(l, r, val);

    rchild->rangeupdate(l, r, val);

    calc();

  }

  ll Query(ll l, ll r)            // Query in O(logn)
  {
    if (l > rightmost || r < leftmost)
      return 0;

    if (l <= leftmost && r >= rightmost)
      return sum;

    propagate();

    return lchild->Query(l, r) + rchild->Query(l, r);
  }
};
