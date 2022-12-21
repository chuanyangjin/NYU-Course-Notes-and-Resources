int fun2(int x, int y) {
  int c = 10;
  return x + y + c;
}

int fun1(int u, int v) {
  return fun2(u, v);
}

int main() {
  int a = 1, b = 2;
  fun1(a, b);
}
