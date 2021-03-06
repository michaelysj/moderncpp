#include "tester.h"

static int autoplus = 1;
class AutoPlus {
public:
    AutoPlus() {
        cout << "constructor:" << autoplus++ << std::endl;
    }
    AutoPlus(const AutoPlus&)
    {
        cout << "copy constructor:" << autoplus++ << endl;
    }
};

void test_reference_wrapper()
{
    std::list<int> l(10);
    for (auto a : l) std::cout << a << ' '; std::cout << std::endl;
    std::iota(l.begin(), l.end(), -4);
    for (auto a : l) std::cout << a << ' '; std::cout << std::endl;

    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
    for (auto a : v) std::cout << a << ' '; std::cout << std::endl;

    std::shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });
    std::cout << "after shuffle:" << std::endl;
    for (auto a : l) std::cout << a << ' '; std::cout << std::endl;
    for (auto a : v) std::cout << a << ' '; std::cout << std::endl;

    for (auto& a : l) a *= 20;

    std::cout << "after multi by 20:" << std::endl;
    for (auto a : l) std::cout << a << ' '; std::cout << std::endl;
    for (auto a : v) std::cout << a << ' '; std::cout << std::endl;

    std::cout << "after minus by 10:" << std::endl;
    for (auto& a : v) a -= 10;
    for (auto a : l) std::cout << a << ' '; std::cout << std::endl;
    for (auto a : v) std::cout << a << ' '; std::cout << std::endl;

    cout << "test class obj:" << endl;
    std::list<AutoPlus> apl(10);
    cout << "autoplus after init:" << endl;
    std::cout << autoplus << endl;

    cout << "reference_wrapper by vector:" << endl;
    vector<reference_wrapper<AutoPlus>> apv(apl.begin(), apl.end());
    cout << autoplus << endl;

    cout << "no ref by vector:" << endl;
    vector<AutoPlus> apv_noref(apl.begin(), apl.end());
    cout << autoplus << endl;
}