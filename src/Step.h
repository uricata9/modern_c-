#ifndef STEP_H_
#define STEP_H_

#include <cstdint>

namespace WMS
{
  class Step {
  public:
    enum Type { invalid, empty, fill, heat, wash, rinse, spin, dry, complete };

    Step();
    Step(Type step_type, uint32_t step_length);

    ~Step();

    void run();

  protected:
    void display();

  private:
    const char* as_string();

    Type           type{};
    uint32_t       duration{};
  };

} // namespace WMS

#endif // STEP_H_