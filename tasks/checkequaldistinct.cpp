#include <iostream>
#include "plan.h"
#include "checkequaldistinct.h"

using namespace std;

CheckEqualDistinct::CheckEqualDistinct(const DPPlan &plan)
    : DPTask(), _plan(plan)
{

}

void CheckEqualDistinct::routine()
{
    cout << "CheckEqualDistinct routine" << endl;
}

