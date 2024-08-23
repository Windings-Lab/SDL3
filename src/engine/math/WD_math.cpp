#include "engine/math/WD_math.h"

#include "engine/math/WD_point.h"

namespace WD::Math
{
    int Test(Point2D point)
    {
	    return 0;
    }
    int TestRef(const Point2D& point)
    {
	    return 0;
    }

    void DoSomething()
    {
        Point2D point = {1, 2};

        int dst = Test(point);
    }

    void DoSomethingRef()
    {
        Point2D point = {1, 2};

        int dst = TestRef(point);
    }
}
