#include "tester.h"

string show_value = "mav";

auto create_ref()
{
    static string value = "boolan";
    //return std::optional<std::string>{value};
    return optional<reference_wrapper<string>>{value};
}

auto show_ref()
{
    return ref(show_value);
}


void test_optional()
{
    if (auto str = create_ref())
    {
       cout << str->get() << endl;
    }

    //cout << show_ref()->get() << endl;
    cout << show_ref().get() << endl;
}