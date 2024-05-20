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
    printf("call <%s> function <%s> id <%d>\n", self->name, func->name, func->id);
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
