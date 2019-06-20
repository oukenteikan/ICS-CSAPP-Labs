#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
	int n;
	char c;
	while (scanf("%x", &n))
	{
		c = char(n);
		cout << n << " " << c << endl;
		if (n == 0)
			break;
	}
	return 0;
}
