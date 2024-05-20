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

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "api_calc.h"
#include "api_utils.h"

void test_api_calc()
{
    int sum = 0;
    
    // can be called with standard regular function (its not macro, its real function)
    sum = calc_sum(5, 10);
    printf("sum = %d\n", sum);
    assert(sum == 15);
    // or by dispatcher with macro
    MAPI_CALL(api_calc, calc_sum, NULL, &sum, 5, 10);
    printf("sum = %d\n", sum);
    assert(sum == 15);
    // or by dispatcher with macro with name
    MAPI_CALL_BY_NAME(api_calc, "calc_sum", NULL, &sum, 5, 10);
    printf("sum = %d\n", sum);
    assert(sum == 15);

    int neg = 0;

    // can be called with standard regular function (its not macro, its real function)
    neg = 9;
    calc_neg(&neg);
    printf("neg = %d\n", neg);
    assert(neg == -9);
    // or by dispatcher with macro
    neg = 9;
    MAPI_CALL(api_calc, calc_neg, NULL, NULL, &neg);
    printf("neg = %d\n", neg);
    assert(neg == -9);
    // or by dispatcher with macro with name
    neg = 9;
    MAPI_CALL_BY_NAME(api_calc, "calc_neg", NULL, NULL, &neg);
    printf("neg = %d\n", neg);
    assert(neg == -9);

    // can be called with standard regular function (its not macro, its real function)
    calc_print_pi();
    // or by dispatcher with macro
    MAPI_CALL(api_calc, calc_print_pi, NULL, NULL);
    // or by dispatcher with macro with name
    MAPI_CALL_BY_NAME(api_calc, "calc_print_pi", NULL, NULL);
}

void test_api_utils()
{
    // can be called with standard regular function (its not macro, its real function)
    char text1[] = "magic api";
    utils_reverse(text1);
    printf("reverse = %s\n", text1);
    assert(strcmp(text1, "ipa cigam") == 0);

    // or by dispatcher with macro
    char text2[] = "magic api";
    MAPI_CALL(api_utils, utils_reverse, NULL, NULL, text2);
    printf("reverse = %s\n", text2);
    assert(strcmp(text1, "ipa cigam") == 0);

    // or by dispatcher with macro with name
    char text3[] = "magic api";
    MAPI_CALL_BY_NAME(api_utils, "utils_reverse", NULL, NULL, text3);
    printf("reverse = %s\n", text3);
    assert(strcmp(text1, "ipa cigam") == 0);
}

int main(int argc, char *argv[])
{
    test_api_calc();
    test_api_utils();

    return 0;
}