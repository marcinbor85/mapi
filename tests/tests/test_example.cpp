/*
MIT License

Copyright (c) 2024 Marcin Borowicz <marcinbor85@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "api_calc.h"
#include "api_utils.h"

#include "mock_impl_calc.hpp"
#include "mock_impl_utils.hpp"

using ::testing::_;
using ::testing::Test;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

class ExampleTest : public Test
{
protected:
    virtual void SetUp()
    {
        gMock_ImplCalcInterfaceMock = new StrictMock<ImplCalcInterfaceMock>;
        gMock_ImplUtilsInterfaceMock = new StrictMock<ImplUtilsInterfaceMock>;
    }

    virtual void TearDown()
    {
        delete gMock_ImplCalcInterfaceMock;
        delete gMock_ImplUtilsInterfaceMock;
    }
};

TEST_F(ExampleTest, api_calc_sum)
{
    EXPECT_CALL(*gMock_ImplCalcInterfaceMock, calc_sum(g_mapi_api_calc, &g_mapi_api_calc->func_desc[0], nullptr, _, _))
        .WillOnce(Invoke([](struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) -> mapi_status_t {
            EXPECT_EQ(va_arg(argp, int), 5);
            EXPECT_EQ(va_arg(argp, int), 10);
            EXPECT_NE(ret, nullptr);
            *((int*)ret) = 15;
            return MAPI_STATUS_SUCCESS;
        }));
    EXPECT_EQ(calc_sum(5, 10), 15);
}

TEST_F(ExampleTest, api_calc_neg)
{
    EXPECT_CALL(*gMock_ImplCalcInterfaceMock, calc_neg(g_mapi_api_calc, &g_mapi_api_calc->func_desc[1], nullptr, nullptr, _))
        .WillOnce(Invoke([](struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) -> mapi_status_t {
            EXPECT_EQ(va_arg(argp, int*), (int*)123);
            return MAPI_STATUS_SUCCESS;
        }));
    calc_neg((int*)123);
}

TEST_F(ExampleTest, api_calc_print_pi)
{
    EXPECT_CALL(*gMock_ImplCalcInterfaceMock, calc_print_pi(g_mapi_api_calc, &g_mapi_api_calc->func_desc[2], nullptr, nullptr, _));
    calc_print_pi();
}

TEST_F(ExampleTest, api_utils_reverse)
{
    EXPECT_CALL(*gMock_ImplUtilsInterfaceMock, utils_reverse(g_mapi_api_utils, &g_mapi_api_utils->func_desc[0], nullptr, nullptr, _))
        .WillOnce(Invoke([](struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) -> mapi_status_t {
            EXPECT_EQ(va_arg(argp, char*), (char*)0x1234);
            return MAPI_STATUS_SUCCESS;
        }));
    utils_reverse((char*)0x1234);
}
