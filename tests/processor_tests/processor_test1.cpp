#include <string>
#include <vector>
using namespace std;
#include <iostream>
typedef long long ll;
typedef vector<int> vi;
bool multiTest = 0;
ll d, l, r, k, n, m, p, q, u, v, w, x, y, z;
int solve(int a){
int n = 10;
int result = 0;
for(int i = a;(i < n);i++){
result = (result + 1);
}
std::cout << result << '\n';
return result;
}

int main() {
int t = 1;
if (multiTest) cin >> t;
for (int ii = 0; ii < t; ii++) {solve(ii);} 
 return 0;
}