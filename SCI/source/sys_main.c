/** @file sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */

#include "sci.h"
#include "system.h"
#include "stdlib.h"
#include "stdio.h"

// alias for a byte of data that is transferred from matlab
typedef uint8_t byte;

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

static byte var[33]; // Buffer used to store the bytes that are being received
uint64_t values = 0; // holds a 64 bit double in binary representation using 1 signed bit 11 bias bits and the 52 bits as the mantissa
double result[10][5];  // dummy variable that holds the incoming vectors
int i = 0; // i and j are used for running through the vector elements
int j = 0;

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    /* Enable IRQ */
    _enable_IRQ();

    /* Initialize the SCI module */
    sciInit();

    /* Send connection status if observing through terminal: teraterm or putty */
    sciSend(scilinREG, 11, (unsigned char*) "Connected\r\n");

    /*Awaits for data to be sent, NOTE: length expected is irrelevant in this transfer. Default is 1 */
    sciReceive(scilinREG,1, var);

    /*Infinite loop to run program: */
    while(1)
    {

    }

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* Serial communication interrupt callback whenever data is received*/
void sciNotification(sciBASE_t *sci, unsigned flags)
{
    /* Awaits for further data */
    sciReceive(sci, 1, var);
     /* Collect the first double representation in bytes and convert them into double representation in binary and store them as double in the holder variable*/
     values =  ((uint64_t)var[0] << 56| (uint64_t)var[1] << 48 | (uint64_t)var[2] << 40| (uint64_t)var[3] << 32 | (uint64_t)var[4] << 24| (uint64_t)var[5] << 16| (uint64_t)var[6] << 8 |(uint64_t)var[7] );
     result[i][j] = *(double*)&values;

     /* Collect the second double representation from bytes into binary and store as double */
     values =  ((uint64_t)var[8] << 56| (uint64_t)var[9] << 48 | (uint64_t)var[10] << 40| (uint64_t)var[11] << 32 | (uint64_t)var[12] << 24| (uint64_t)var[13] << 16| (uint64_t)var[14] << 8 |(uint64_t)var[15] );
     j++; // Increment the elements of each vector
     result[i][j] = *(double*)&values;

     /* Collect the third double representation from bytes into binary and store as double */
     values =  ((uint64_t)var[16] << 56| (uint64_t)var[17] << 48 | (uint64_t)var[18] << 40| (uint64_t)var[19] << 32 | (uint64_t)var[20] << 24| (uint64_t)var[21] << 16| (uint64_t)var[22] << 8 |(uint64_t)var[23] );
     j++;
     result[i][j] = *(double*)&values;

     /* Collect the fourth double representation from bytes into binary and store as double */
     values =  ((uint64_t)var[24] << 56| (uint64_t)var[25] << 48 | (uint64_t)var[26] << 40| (uint64_t)var[27] << 32 | (uint64_t)var[28] << 24| (uint64_t)var[29] << 16| (uint64_t)var[30] << 8 |(uint64_t)var[31] );

     j++;
     result[i][j] = *(double*)&values;
     j = 0;

     i++; // Increment the which vector is being populated

}

/* ESM interrupt notification is needed */
void esmGroup1Notification(int bit)
{
    return;
}

void esmGroup2Notification(int bit)
{
    return;
}

/* USER CODE END */
