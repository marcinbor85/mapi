
# MAPI
MAPI is an abbreviation of Magic Application Protocol Interface. It's a macro-based wrapper for C API.
With this library You can easily wrap and unify any raw C API and call it with unified dispatcher.
All functions calls are passed through internal MAPI dispatcher.
Each function has its own "api" namespace with its own list of identifiers.
Library uses variadic arguments internally.

## Features
- can wrap any C api with dispatcher pattern
- supports up-to 3 function arguments (can be easily extended)
- all library features are covered by unit tests
- allow to call public functions by name string
- c-like namespaces

## Usage

Declare API in header file (e.g. api_calc.h)

```c
// include mapi header
#include "mapi.h"

// define api name
#define MAPI_NAME api_calc

// define list of public functions with their types and arguments
#define MAPI_FUNCTIONS_LIST\
    _FUNC_RET_P2(calc_sum, int, int, int)\
    _FUNC_NORET_P1(calc_neg, int*)\
    _FUNC_NORET_P0(calc_print_pi)\

// write optional explicit declarations with codedocs
// they are optional, because declarations are generated by library
int calc_sum(int a, int b);
void calc_neg(int *val);
void calc_print_pi(void);

// include mapi header generator
#include "mapi_api_header.h"
```

Define API source code (e.g. api_calc.c)

```c
// include header file created above
#include "api_calc.h"

// include mapi source generator
#include "mapi_api_source.h"

// no need to define anything here, wrappers will be generated automatically
```

Define real API source code with unified API (e.g. impl_calc.c)

```c
// include app specific headers
#include <stdarg.h>
#include <stdio.h>

// include "our" public header
#include "api_calc.h"

// define api function (input arguments are available at "argp", output are at "ret")
MAPI_DECL_IMPL_FUNC(calc_sum)
{
    int a = va_arg(argp, int);
    int b = va_arg(argp, int);
    *((int*)ret) = a + b;
    return MAPI_STATUS_SUCCESS;
}
```

Usage:

```c
// include "our" public header
#include "api_calc.h"

// main application
void main() {
    int sum;
    
    // can be called with standard regular function (its not macro, its real function)
    sum = calc_sum(5, 10);
    // can be called through MACRO
    MAPI_CALL(api_calc, calc_sum, NULL, &sum, 5, 10);
    // can be called through MACRO by name
    MAPI_CALL_BY_NAME(api_calc, "calc_sum", NULL, &sum, 5, 10);
}
```
