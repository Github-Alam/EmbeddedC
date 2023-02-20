/* Yousuf ALam
 * 18.02.23
 * int2char_conv version-2

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define int16_arrSize 20000
#define ch_arrSize    120000

uint16_t creatRandoms(uint8_t lower, uint32_t upper, uint8_t count);

void app_main(void)
{
	printf("***welcome to i2c_hello***\n");

	uint64_t t1,t2,t3,t4;
	static uint32_t j=0;
	static char ch_arr[ch_arrSize]={};
	static uint16_t int16_arr[int16_arrSize] ={0};

	t1 = esp_timer_get_time();
	//store random number
	for (uint32_t i=0; i<ch_arrSize; i++)
	{
		ch_arr[i]=48;
	}
	t2 = esp_timer_get_time();
	printf("Total time for storing 16bits 20K random integer number = %lld us\r\n",(t2-t1));


	t1 = esp_timer_get_time();
	//store random number
	for (uint16_t i=0; i<int16_arrSize; i++)
	{
		srand(i);
		int16_arr[i] =creatRandoms (1, 65535, 1);
	}
	t2 = esp_timer_get_time();
	printf("Total time for storing 16bits 20K random integer number = %lld us\r\n",(t2-t1));

	//print the integer value and  i numbers in range lower= 0, upper=20000
		for(uint16_t i=0; i<10; i++)
		{
			printf(" %dth position integer value = %d \r\n",i,int16_arr[i]);
		}

	t3 = esp_timer_get_time();
	for(uint16_t i=0; i<int16_arrSize; i++)
	{
		uint8_t len=0; //int8_arr[5]={0,0,0,0,0},len=5;
		j+=4;
		while(int16_arr[i])
			{
			   // j=len;
				ch_arr[j] = 48+ int16_arr[i]%10;
				int16_arr[i] = int16_arr[i]/10;
				j--;
				len++;
				//printf("%d----%c-----\n",len,ch_arr[len]);
			}
	/*	for(uint8_t k=0; k<5; k++)
		{
			ch_arr[j] = 48+int8_arr[k];
			j++;
		}*/
		//j++;
		j+=len+1;
		ch_arr[j] =',';
		j++;
	}
	t4 = esp_timer_get_time();
	printf("Total time for converting 20k integer number into character of array size 120k = %lld us\r\n",(t4-t3));
	//printf("%s\n", ch_arr);

	//print the character value and i numbers in range lower= 0*6, upper = 20000*6
	uint8_t new=0;
	for(uint32_t i=0*6; i<10*6; ++i)
	{
		new++;
		printf("%c",ch_arr[i]);
		if(new==6)
		{
			printf("<=%dth position character value \r\n",i/6);
			new=0;
		}
	}
}

// Generates int random number
// numbers in range lower, upper.
uint16_t creatRandoms(uint8_t lower, uint32_t upper, uint8_t count)
{
	uint16_t num=0;
	for( uint8_t i=0; i<count; i++)
	{
		num = ((rand()%(upper - lower + 1))+lower);
	}
	return num;
}

