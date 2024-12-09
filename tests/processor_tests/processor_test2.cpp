#include <string>
#include <vector>
using namespace std;
#include <iostream>
typedef long long ll;
typedef vector<int> vi;
bool multiTest = 0;
ll d, l, r, k, n, m, p, q, u, v, w, x, y, z;
int func1(int a,int b){
return 0;
}

int func2(int b){
return 1;
}

void solve(int i){
int x = 8;
int y = 8;
int result = (x + y);
int z = ((x * y) + (x / y));
bool flag = ((((x == y) && x) != z) || !flag);
result = (func1(x,y) * func2(z));
print(result);
}

int main() {
int t = 1;
if (multiTest) cin >> t;
for (int ii = 0; ii < t; ii++) {solve(ii);}
}