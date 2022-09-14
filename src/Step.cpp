#include "Step.h"
#include "Timer.h"
#include "Trace.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace
{
  const char* const strings[9] = { "invalid", "empty", "fill",
                                   "heat",    "wash",  "rinse",
                                   "spin",    "dry",   "complete" };
}

namespace WMS
{
  Step::Step() { TRACE_MSG("Step::Step()"); }

  Step::Step(Type step_type, uint32_t step_length) :
    type{ step_type }, duration{ step_length }
  {
    TRACE_MSG("Step::Step(Type, uint32_t)");
  }

  Step::~Step() { TRACE_MSG("Step:~Step()"); }

  void Step::run()
  {
    display();
    sleep(duration);
  }

  const char* Step::as_string() { return strings[type]; }

  void Step::display()
  {
    cout << fixed;
    cout << setprecision(2);
    cout << "Step '" << as_string() << "' ";
    cout << "running for " << duration/1000.0 << " seconds";
    cout << endl;
  }

} // namespace WMS