#include <cstdint>
#include <minunit/minunit.h>
#include <vcvm/lib.h>

TEST_SUITE(fx);

TEST(basic_fx)
{
    const uint8_t program[] = {
        // 0xDECAF
        0x0, 0x0, 0x0, 0x0, 0x0, 0xD, 0xEC, 0xAF,
    };

    TEST_SUCCESS()
}