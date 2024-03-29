/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-10-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/10/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_aht20_basic.h"
#include "driver_aht20_read_test.h"
#include <math.h>
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     aht20 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t aht20(void)
{
    uint8_t res;
    float temperature;
    uint8_t humidity;

    /* basic init */
    res = aht20_basic_init();
    if (res != 0)
    {
        return 1;
    }


        /* read data */
        res = aht20_basic_read((float *)&temperature, (uint8_t *)&humidity);
        if (res != 0)
        {
            (void)aht20_basic_deinit();

            return 1;
        }

        /* output */
        //aht20_interface_debug_print("aht20: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
        aht20_interface_debug_print("aht20: temperature is %0.2fF, ", temperature/5.0*9.0+32.0);
        aht20_interface_debug_print("aht20: humidity is %d%%.\n", humidity);

    /* deinit */
    (void)aht20_basic_deinit();

    return 0;
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = aht20();
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        aht20_interface_debug_print("aht20: run failed.\n");
    }
    else if (res == 5)
    {
        aht20_interface_debug_print("aht20: param is invalid.\n");
    }
    else
    {
        aht20_interface_debug_print("aht20: unknown status code.\n");
    }

    return 0;
}
