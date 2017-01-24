/** Test TinyUnitTest with TinyUnitTest
 */

#include "tiny_unit.h"


int main() {
    std::ostringstream buf;
    TinyUnit::Test t;

    {
        TinyUnit::Test x(buf);
        x.case_("").assert(true);
        t.case_("assert(true)").assert(x.getSuccessCount() == 1 &&  x.getCount() == 1);
    }
    {
        TinyUnit::Test x(buf);
        x.case_("").assert(false);
        t.case_("assert(false)").assert(x.getSuccessCount() == 0 && x.getCount() == 1);
    }

    {
        TinyUnit::Test x(buf);
        x.case_("").equals(1, 1);
        t.case_("equals(1, 1)").assert(x.getSuccessCount() == 1 &&  x.getCount() == 1);
    }
    {
        TinyUnit::Test x(buf);
        x.case_("").equals(1, 0);
        t.case_("equals(1, 0)").assert(x.getSuccessCount() == 0 &&  x.getCount() == 1);
    }

    {
        TinyUnit::Test x(buf);
        x.case_("").not_equals(1, 0);
        t.case_("equals(1, 0)").assert(x.getSuccessCount() == 1 &&  x.getCount() == 1);
    }
    {
        TinyUnit::Test x(buf);
        x.case_("").not_equals(1, 1);
        t.case_("equals(1, 1)").assert(x.getSuccessCount() == 0 &&  x.getCount() == 1);
    }

    {
        TinyUnit::Test x(buf);
        x.case_("").less(10, 11);
        t.case_("less(10, 11)").assert(x.getSuccessCount() == 1 &&  x.getCount() == 1);
    }
    {
        TinyUnit::Test x(buf);
        x.case_("").less(11, 10);
        t.case_("less(11, 10)").assert(x.getSuccessCount() == 0 &&  x.getCount() == 1);
    }

    {
        TinyUnit::Test x(buf);
        x.case_("").less(10, 11, 20);
        t.case_("less(10, 11, 20)").assert(x.getSuccessCount() == 1 &&  x.getCount() == 1);
    }
    {
        TinyUnit::Test x(buf);
        x.case_("").less(11, 10, 20);
        t.case_("less(11, 10, 20)").assert(x.getSuccessCount() == 0 &&  x.getCount() == 1);
    }
    {
        TinyUnit::Test x(buf);
        x.case_("").less(10, 12, 11);
        t.case_("less(10, 12, 11)").assert(x.getSuccessCount() == 0 &&  x.getCount() == 1);
    }

    t.show_report();

    return t.getSuccessCount() != t.getCount();
}
