void main()
{
  int sum;
  sum = 35 + 400;
  cout << sum;

  int diff;
  diff = 100 - 50;
  cout << diff;

  int mul;
  mul = 5 * 5;
  cout << mul;

  int div;
  div = 10 / 2;
  cout << div;

  int small;
  small = 4;
  int big;
  big = 5;

  // cout << 100;
  // cout << big;

  /*
  cout << 500;
  */

  // should be 1
  int l;
  l = small < big;
  cout << l;

// should be 0
  int g;
  g = small > big;
  cout << g;

  int le;
  le = small <= big;
  cout << le;

  int ge;
  ge = small >= big;
  cout << ge;

  int e;
  e = small == big;
  cout << e;

  int ne;
  ne = small != big;
  cout << ne;

  int a;
  a = small && big;
  cout << a;

  int o;
  o = small || big;
  cout << o;

  int inc;
  inc = 5;

  if (inc < 7) {
    cout << inc;
    inc = inc + 1;
  }

  if (inc == 1000) {
    cout << 1000;
  }

  if (inc < 4) {
    cout << inc;
    inc = inc - 1;
  } else {
    cout << 420;
  }

    int i;
    i = 0;
  while (i < 10) {
    cout << i;
    i = i + 1;
  }

}