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

#include <array>

#include "mapi.h"

#include "mock_func_desc_callback.hpp"

using ::testing::_;
using ::testing::Test;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrictMock;

class MapiTest : public Test
{
    std::string mNames[10] = {"f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10"};

protected:
    struct mapi_dispatcher *mMapi;
    std::array<struct mapi_func_desc, 10> *mFuncDesc;

    virtual void SetUp()
    {
        gMock_FuncDescCallbackInterfaceMock = new StrictMock<FuncDescCallbackInterfaceMock>;

        mFuncDesc = new std::array<struct mapi_func_desc, 10>;
        for (size_t i = 0; i < mFuncDesc->size() - 1; i++) {
            int id = i + 1;
            mFuncDesc->at(i).id = id;
            mFuncDesc->at(i).name = mNames[i].c_str();
            mFuncDesc->at(i).callback = nullptr;
        }

        mMapi = new struct mapi_dispatcher;
        mMapi->name = "test";
        mMapi->func_desc = mFuncDesc->data();
        mMapi->context = nullptr;
    }

    virtual void TearDown()
    {
        delete gMock_FuncDescCallbackInterfaceMock;
        delete mMapi;
        delete mFuncDesc;
    }
};

TEST_F(MapiTest, mapi_call__found)
{
    EXPECT_CALL(*gMock_FuncDescCallbackInterfaceMock, callback(mMapi, &mFuncDesc->at(0), (void*)112233, _, _))
        .WillOnce(Invoke([](struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) -> mapi_status_t {
            EXPECT_EQ(va_arg(argp, int), 1);
            EXPECT_EQ(va_arg(argp, int), 2);
            EXPECT_EQ(va_arg(argp, int), 3);
            EXPECT_EQ(ret, (void*)123);
            return MAPI_STATUS_SUCCESS;
        }));
    mFuncDesc->at(0).callback = func_desc_callback;
    EXPECT_EQ(mapi_call(mMapi, 1, (void*)112233, (void*)123, 1, 2, 3), MAPI_STATUS_SUCCESS);
}

TEST_F(MapiTest, mapi_call__found_status)
{
    EXPECT_CALL(*gMock_FuncDescCallbackInterfaceMock, callback(mMapi, &mFuncDesc->at(3), (void*)112233, _, _))
        .WillOnce(Invoke([](struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) -> mapi_status_t {
            EXPECT_EQ(va_arg(argp, int), 1);
            EXPECT_EQ(va_arg(argp, int), 2);
            EXPECT_EQ(va_arg(argp, int), 3);
            EXPECT_EQ(ret, (void*)123);
            return (mapi_status_t)111;
        }));
    mFuncDesc->at(3).callback = func_desc_callback;
    EXPECT_EQ(mapi_call(mMapi, 4, (void*)112233, (void*)123, 1, 2, 3), (mapi_status_t)111);
}

TEST_F(MapiTest, mapi_call__not_found)
{
    EXPECT_EQ(mapi_call(mMapi, 11, (void*)112233, (void*)123, 1, 2, 3), MAPI_STATUS_ERROR_FUNC_NOT_FOUND);
}

TEST_F(MapiTest, mapi_call__no_callback)
{
    EXPECT_EQ(mapi_call(mMapi, 4, (void*)112233, (void*)123, 1, 2, 3), MAPI_STATUS_ERROR_FUNC_NO_CALLBACK);
}

TEST_F(MapiTest, mapi_call_by_name__found)
{
    EXPECT_CALL(*gMock_FuncDescCallbackInterfaceMock, callback(mMapi, &mFuncDesc->at(0), (void*)112233, _, _))
        .WillOnce(Invoke([](struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) -> mapi_status_t {
            EXPECT_EQ(va_arg(argp, int), 1);
            EXPECT_EQ(va_arg(argp, int), 2);
            EXPECT_EQ(va_arg(argp, int), 3);
            EXPECT_EQ(ret, (void*)123);
            return MAPI_STATUS_SUCCESS;
        }));
    mFuncDesc->at(0).callback = func_desc_callback;
    EXPECT_EQ(mapi_call_by_name(mMapi, "f1", (void*)112233, (void*)123, 1, 2, 3), MAPI_STATUS_SUCCESS);
}

TEST_F(MapiTest, mapi_call_by_name__found_status)
{
    EXPECT_CALL(*gMock_FuncDescCallbackInterfaceMock, callback(mMapi, &mFuncDesc->at(6), (void*)112233, _, _))
        .WillOnce(Invoke([](struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp) -> mapi_status_t {
            EXPECT_EQ(va_arg(argp, int), 1);
            EXPECT_EQ(va_arg(argp, int), 2);
            EXPECT_EQ(va_arg(argp, int), 3);
            EXPECT_EQ(ret, (void*)123);
            return (mapi_status_t)111;
        }));
    mFuncDesc->at(6).callback = func_desc_callback;
    EXPECT_EQ(mapi_call_by_name(mMapi, "f7", (void*)112233, (void*)123, 1, 2, 3), (mapi_status_t)111);
}

TEST_F(MapiTest, mapi_set_context)
{
    mapi_set_context(mMapi, (void*)112233);
    EXPECT_EQ(mMapi->context, (void*)112233);
}

TEST_F(MapiTest, mapi_get_context)
{
    mMapi->context = (void*)112233;
    EXPECT_EQ(mapi_get_context(mMapi), (void*)112233);
}
