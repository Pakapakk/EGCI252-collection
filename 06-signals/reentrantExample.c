#include <stdio.h>

int f(int i)
{ 
  int priv = i; 
  priv = priv + 2;
  printf("f = %d\n", priv);
  return priv; 
}

int g(int i)
{ 
  int priv = i; 
  printf("g = %d\n", f(priv) + 2);
  return f(priv) + 2; 
}

int main() { 
  g(1); 
  return 0; 
}