int func1(int a, int b) {
	
	return 0;
}

int func2(int b) {
	return 1;
}

void solve(int i) {
    int x = 8;
    int y = 8;
    int result = x + y;

    int z = (x * y) + (x / y);

    bool flag = x == y && x != z || !flag;

    result = func1(x, y) * func2(z);
}