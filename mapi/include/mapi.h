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

#ifdef MAPI_NAME
#undef MAPI_NAME
#endif

#ifdef MAPI_FUNCTIONS_LIST
#undef MAPI_FUNCTIONS_LIST
#endif

#ifndef MAPI_H
#define MAPI_H

#include <stdarg.h>
#include <stddef.h>

#define MAPI_XSTR(x) #x
#define MAPI_STR(x) MAPI_XSTR(x)

#define MAPI_IMPL_FUNC_NAME(func_name) _impl_##func_name
#define MAPI_DECL_IMPL_FUNC(func_name) mapi_status_t MAPI_IMPL_FUNC_NAME(func_name)(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp)
#define _MAPI_DISPATCHER_NAME(api_name) g_mapi_##api_name
#define MAPI_DISPATCHER_NAME(api_name) _MAPI_DISPATCHER_NAME(api_name)
#define MAPI_DECL_DISPATCHER(api_name) struct mapi_dispatcher* MAPI_DISPATCHER_NAME(api_name)

#define _MAPI_FUNC_ID(api_name, func_name) api_name##_##func_name##_id
#define MAPI_FUNC_ID(api_name, func_name) _MAPI_FUNC_ID(api_name, func_name)
#define _MAPI_FUNC_ID_NONE(api_name) _##api_name##_none_id
#define MAPI_FUNC_ID_NONE(api_name) _MAPI_FUNC_ID_NONE(api_name)
#define _MAPI_FUNC_ID_ENUM_NAME(api_name) mapi_##api_name##_func_id
#define MAPI_FUNC_ID_ENUM_NAME(api_name) _MAPI_FUNC_ID_ENUM_NAME(api_name)

#define MAPI_DECL_API_FUNC_RET_P0(func_name, ret_type) ret_type func_name(void)
#define MAPI_DECL_API_FUNC_RET_P1(func_name, ret_type, arg1_type) ret_type func_name(arg1_type arg1)
#define MAPI_DECL_API_FUNC_RET_P2(func_name, ret_type, arg1_type, arg2_type) ret_type func_name(arg1_type arg1, arg2_type arg2)
#define MAPI_DECL_API_FUNC_RET_P3(func_name, ret_type, arg1_type, arg2_type, arg3_type) ret_type func_name(arg1_type arg1, arg2_type arg2, arg3_type arg3)
#define MAPI_DECL_API_FUNC_NORET_P0(func_name) void func_name(void)
#define MAPI_DECL_API_FUNC_NORET_P1(func_name, arg1_type) void func_name(arg1_type arg1)
#define MAPI_DECL_API_FUNC_NORET_P2(func_name, arg1_type, arg2_type) void func_name(arg1_type arg1, arg2_type arg2)
#define MAPI_DECL_API_FUNC_NORET_P3(func_name, arg1_type, arg2_type, arg3_type) void func_name(arg1_type arg1, arg2_type arg2, arg3_type arg3)

#define MAPI_CALL(api_name, func_name, user_data, ...) mapi_call(MAPI_DISPATCHER_NAME(api_name), MAPI_FUNC_ID(api_name, func_name), user_data, __VA_ARGS__);
#define MAPI_CALL_BY_NAME(api_name, func_name, user_data, ...) mapi_call_by_name(MAPI_DISPATCHER_NAME(api_name), func_name, user_data, __VA_ARGS__);

typedef enum {
    MAPI_STATUS_ERROR_FUNC_NO_CALLBACK = -2,
    MAPI_STATUS_ERROR_FUNC_NOT_FOUND = -1,
    MAPI_STATUS_SUCCESS = 0
} mapi_status_t;

#ifdef __cplusplus
extern "C" {
#endif

struct mapi_dispatcher;
struct mapi_func_desc;

typedef mapi_status_t (*mapi_func_t)(struct mapi_dispatcher *self, const struct mapi_func_desc *func_desc, void *user_data, void *ret, va_list argp);

struct mapi_func_desc {
    int id;
    const char *name;
    mapi_func_t callback;
};

struct mapi_dispatcher {
    const char *name;
    const struct mapi_func_desc *func_desc;
    void *context;
};

mapi_status_t mapi_call(struct mapi_dispatcher *self, int func_id, void *user_data, void *ret, ...);
mapi_status_t mapi_call_by_name(struct mapi_dispatcher *self, const char* func_name, void *user_data, void* ret, ...);

void mapi_set_context(struct mapi_dispatcher *self, void *context);
void* mapi_get_context(struct mapi_dispatcher *self);

#ifdef __cplusplus
}
#endif

#endif /* MAPI_H */
