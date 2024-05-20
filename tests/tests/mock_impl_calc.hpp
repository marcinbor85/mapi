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

#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mapi.h"

using ::testing::StrictMock;

struct ImplCalcInterface
{
    virtual ~ImplCalcInterface() {};

    virtual mapi_status_t calc_sum(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) = 0;
    virtual mapi_status_t calc_neg(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) = 0;
    virtual mapi_status_t calc_print_pi(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) = 0;
};

struct ImplCalcInterfaceMock : public ImplCalcInterface
{
    MOCK_METHOD(mapi_status_t, calc_sum, (struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp), (override));
    MOCK_METHOD(mapi_status_t, calc_neg, (struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp), (override));
    MOCK_METHOD(mapi_status_t, calc_print_pi, (struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp), (override));
};

StrictMock<ImplCalcInterfaceMock> *gMock_ImplCalcInterfaceMock;

extern "C" {

mapi_status_t _impl_calc_sum(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp)
{
    return gMock_ImplCalcInterfaceMock->calc_sum(self, func_desc, user_data, ret, argp);
}

mapi_status_t _impl_calc_neg(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp)
{
    return gMock_ImplCalcInterfaceMock->calc_neg(self, func_desc, user_data, ret, argp);
}

mapi_status_t _impl_calc_print_pi(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp)
{
    return gMock_ImplCalcInterfaceMock->calc_print_pi(self, func_desc, user_data, ret, argp);
}

}
