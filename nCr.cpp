ll fact[N], revfact[N];

void factorial()
{
  fact[0] = 1;

  ll i;

  for (i = 1; i < N; i++)
    fact[i] = i * fact[i - 1] % MOD;

  i--;

  revfact[i] = binpow(fact[i], MOD - 2, MOD);

  i--;

  for (; i >= 0; i--)
    revfact[i] = (i + 1) * revfact[i + 1] % MOD;

}

ll ncr(ll n, ll r)
{
  if (n < 0 || r < 0 || r > n)
    return 0;

  return fact[n] * revfact[r] % MOD * revfact[n - r] % MOD;
}
