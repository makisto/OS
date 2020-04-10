#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	long long a, b, a1, b1, q;
	cin >> q;
	while(q--)
	{
		cin >> a >> b;
		if((a == 0 && b != 0) || (a != 0 && b == 0) || (a == b))
		{
			cout << "NO" << endl;
			continue;	
		}
		if(a == 0 && b == 0)
		{
			cout << "YES" << endl;
			continue;
		}
		while(1)
		{
			a1 = max(a, b);
			b1 = min(a, b);
			if(a1 == 2 && b1 == 1)
			{
				cout << "YES" << endl;
				break;
			}
			if(a1 == 3 && b1 == 2)
			{
				cout << "NO" << endl;
				break;
			}
			a1 -= 1;
			b1 -= 2;
			a -= 1;
			b -= 2;
			if(b1 * 2 < a1)
			{				
				cout << "NO" << endl;
				break;				
			}
			if(b1 * 2 == a1)
			{
				cout << "YES" << endl;
				break;
			}	
		}
	}
}
