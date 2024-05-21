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

#include "mapi.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

static const struct mapi_func_desc* find_func_by_id(struct mapi_dispatcher *self, int func_id)
{
    const struct mapi_func_desc *func = self->func_desc;

    while (func->id != 0) {
        if (func->id == func_id) {
            return func;
        }
        func++;
    }

    return NULL;
}

static const struct mapi_func_desc* find_func_by_name(struct mapi_dispatcher *self, const char *func_name)
{
    const struct mapi_func_desc *func = self->func_desc;

    while (func->id != 0) {
        if (strcmp(func->name, func_name) == 0) {
            return func;
        }
        func++;
    }

    return NULL;
}

static mapi_status_t call_func(struct mapi_dispatcher *self, const struct mapi_func_desc *func, void *user_data, void* ret, va_list argp)
{
    MAPI_LOG("call <%s> function <%s> id <%d>\n", self->name, func->name, func->id);
    mapi_status_t status = MAPI_STATUS_ERROR_FUNC_NO_CALLBACK;
    if (func->callback != NULL) {
        status = func->callback(self, func, user_data, ret, argp);
    }
    return status;
}

mapi_status_t mapi_call(struct mapi_dispatcher *self, int func_id, void *user_data, void* ret, ...)
{
    va_list argp;

    const struct mapi_func_desc *func = find_func_by_id(self, func_id);
    if (func == NULL) {
        return MAPI_STATUS_ERROR_FUNC_NOT_FOUND;
    }

    va_start(argp, ret);
    mapi_status_t status = call_func(self, func, user_data, ret, argp);
    va_end(argp);
    return status;
}

mapi_status_t mapi_call_by_name(struct mapi_dispatcher *self, const char* func_name, void *user_data, void* ret, ...)
{
    va_list argp;

    const struct mapi_func_desc *func = find_func_by_name(self, func_name);
    if (func == NULL)
        return MAPI_STATUS_ERROR_FUNC_NOT_FOUND;

    va_start(argp, ret);
    mapi_status_t status = call_func(self, func, user_data, ret, argp);
    va_end(argp);
    return status;
}

void mapi_set_context(struct mapi_dispatcher *self, void *context)
{
    self->context = context;
}

void* mapi_get_context(struct mapi_dispatcher *self)
{
    return self->context;
}
