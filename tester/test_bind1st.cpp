#include "tester.h"

/*
* lessÔ´Âë
struct less<void>
{
	template <typename _Tp, typename _Up>
		operator()(_Tp&& __t, _Up&& __u) const
}
*/

void test_bind1st()
{
	vector<int> coll;
	for (int i = 1; i <= 10; ++i)
	{
		coll.push_back(i);
	}
	int res = count_if(coll.begin(), coll.end(), bind1st(less<int>(), 10));
	cout << res << endl;

	res = count_if(coll.begin(), coll.end(), bind2nd(less<int>(), 10));
	cout << res << endl;

	// using std::bind
	res = count_if(coll.begin(), coll.end(), bind(less<int>(), 8, placeholders::_1));
	cout << res << endl;

}