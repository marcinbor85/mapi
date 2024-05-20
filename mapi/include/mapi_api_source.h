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

#ifndef MAPI_NAME
#error MAPI_NAME not defined
#endif /* MAPI_NAME */

#ifndef MAPI_FUNCTIONS_LIST
#error MAPI_FUNCTIONS_LIST not defined
#endif /* MAPI_FUNCTIONS_LIST */

#define DISPATCHER_NAME _g_dispatcher
#define FUNCTIONS_NAME _g_functions

#define _FUNC_ITEM(api_name, func_name)\
{\
    .id=MAPI_FUNC_ID(api_name, func_name),\
    .name=#func_name,\
    .callback=MAPI_IMPL_FUNC_NAME(func_name)\
},

#define _FUNC_RET_P0(func_name, ret_type) _FUNC_ITEM(MAPI_NAME, func_name)
#define _FUNC_RET_P1(func_name, ret_type, arg1_type) _FUNC_ITEM(MAPI_NAME, func_name)
#define _FUNC_RET_P2(func_name, ret_type, arg1_type, arg2_type) _FUNC_ITEM(MAPI_NAME, func_name)
#define _FUNC_RET_P3(func_name, ret_type, arg1_type, arg2_type, arg3_type) _FUNC_ITEM(MAPI_NAME, func_name)
#define _FUNC_NORET_P0(func_name) _FUNC_ITEM(MAPI_NAME, func_name)
#define _FUNC_NORET_P1(func_name, arg1_type) _FUNC_ITEM(MAPI_NAME, func_name)
#define _FUNC_NORET_P2(func_name, arg1_type, arg2_type) _FUNC_ITEM(MAPI_NAME, func_name)
#define _FUNC_NORET_P3(func_name, arg1_type, arg2_type, arg3_type) _FUNC_ITEM(MAPI_NAME, func_name)

static const struct mapi_func_desc FUNCTIONS_NAME[] = {
    MAPI_FUNCTIONS_LIST
    {
    }
};

static struct mapi_dispatcher DISPATCHER_NAME = {
    .name=MAPI_STR(MAPI_NAME),
    .func_desc=FUNCTIONS_NAME
};

MAPI_DECL_DISPATCHER(MAPI_NAME) = &DISPATCHER_NAME;

#undef _FUNC_RET_P0
#undef _FUNC_RET_P1
#undef _FUNC_RET_P2
#undef _FUNC_RET_P3
#undef _FUNC_NORET_P0
#undef _FUNC_NORET_P1
#undef _FUNC_NORET_P2
#undef _FUNC_NORET_P3

#define _FUNC_RET_P0(func_name, ret_type) \
MAPI_DECL_API_FUNC_RET_P0(func_name, ret_type) \
{\
    ret_type ret;\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, &ret);\
    return ret;\
}

#define _FUNC_RET_P1(func_name, ret_type, arg1_type) \
MAPI_DECL_API_FUNC_RET_P1(func_name, ret_type, arg1_type) \
{\
    ret_type ret;\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, &ret, arg1);\
    return ret;\
}

#define _FUNC_RET_P2(func_name, ret_type, arg1_type, arg2_type) \
MAPI_DECL_API_FUNC_RET_P2(func_name, ret_type, arg1_type, arg2_type) \
{\
    ret_type ret;\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, &ret, arg1, arg2);\
    return ret;\
}

#define _FUNC_RET_P3(func_name, ret_type, arg1_type, arg2_type, arg3_type) \
MAPI_DECL_API_FUNC_RET_P3(func_name, ret_type, arg1_type, arg2_type, arg3_type) \
{\
    ret_type ret;\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, &ret, arg1, arg2, arg3);\
    return ret;\
}

#define _FUNC_NORET_P0(func_name) \
MAPI_DECL_API_FUNC_NORET_P0(func_name) \
{\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, NULL);\
}

#define _FUNC_NORET_P1(func_name, arg1_type) \
MAPI_DECL_API_FUNC_NORET_P1(func_name, arg1_type) \
{\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, NULL, arg1);\
}

#define _FUNC_NORET_P2(func_name, arg1_type, arg2_type) \
MAPI_DECL_API_FUNC_NORET_P2(func_name, arg1_type, arg2_type) \
{\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, NULL, arg1, arg2);\
}

#define _FUNC_NORET_P3(func_name, arg1_type, arg2_type, arg3_type) \
MAPI_DECL_API_FUNC_NORET_P3(func_name, arg1_type, arg2_type, arg3_type) \
{\
    mapi_call(MAPI_DISPATCHER_NAME(MAPI_NAME), MAPI_FUNC_ID(MAPI_NAME, func_name), NULL, NULL, arg1, arg2, arg3);\
}

MAPI_FUNCTIONS_LIST

#undef _FUNC_RET_P0
#undef _FUNC_RET_P1
#undef _FUNC_RET_P2
#undef _FUNC_RET_P3
#undef _FUNC_NORET_P0
#undef _FUNC_NORET_P1
#undef _FUNC_NORET_P2
#undef _FUNC_NORET_P3
