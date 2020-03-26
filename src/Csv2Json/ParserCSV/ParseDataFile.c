/**
 * @file ParseDataFile.c
 * @brief 解析数据文件的程序相关文件
 * @copyright Copyright (c) 2020 Beijing SOJO Electric CO., LTD.
 * @company  SOJO
 * @date 2020.03.24
 *
 * @author Lei.L
 * @version ver 1.0
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "csv.h"
#include "ParseDataFile.h"
#include "../../Config.h"

static int String2Int(char *string, int stringLenth);

/**
 * @fn ParseCSVDataFile
 * @brief 解析数据文件。将CSV数据文件解析为字符串
 * @param fileName 文件名
 * @param registerData 用于存放解析完成后的数据
 * @param arrayNumber 数据数组大小
 * @return 成功:解析到的数据个数 错误:-1
 */
int ParseCSVDataFile(char *fileName, int registerData[], int arrayNumber)
{
    FILE *fp = NULL;
    int err, done = 0;
    char *csvLineString = NULL;     //一行csv文件字符串
    char **parsed = NULL;           //一个csv文件中一个字符串元素
    int i = 0, num = 0;
    int fileDataNum = 0, dataNum = 0;;

	if(NULL == registerData)
	{
		printf_debug("error:dataString[%d] is NULL!\n", arrayNumber);
		return FUNCTION_FAIL;
	}

    if((fp = fopen(fileName, "r")) == NULL)
    {
    	printf_debug("error:%s open fail!\n", fileName);
    	return FUNCTION_FAIL;
    }

    /* 保存信息的格式：Data Name,数据名称,Start Address,起始地址,Number,数量, */
    csvLineString = fread_csv_line(fp, CSV_LINE_MAX, &done, &err);
    parsed = parse_csv(csvLineString);
    fileDataNum = String2Int(parsed[5], strlen(parsed[5]));
    dataNum = (fileDataNum < arrayNumber ? fileDataNum : arrayNumber);

    while(num < dataNum)
    {
        csvLineString = fread_csv_line(fp, CSV_LINE_MAX, &done, &err);
        parsed = parse_csv(csvLineString);

        for(i = 0; i < 10 && num < dataNum; i++)
        {
        	registerData[num] = String2Int(parsed[i], strlen(parsed[i]));
            num++;
        }
    }

    fclose(fp);
    fp = NULL;
    free(csvLineString);
    csvLineString = NULL;
    free_csv_line(parsed);
    parsed = NULL;

    return num;
}


/**
 * @fn String2Int
 * @brief 字符串转整型
 * @param string 需要转换的字符串
 * @param stringLenth 字符串长度
 * @return 转换后的整数
 */
static int String2Int(char *string, int stringLenth)
{
    int number = 0;         //保存转换后的数
    bool isPositive = true;     //正数标志位
    int i = 0;

    for(i = 0; i < stringLenth && string[i] != '\0'; i++)
    {
        if(i == 0 && string[i] == '-')
        {
            isPositive = false;
            continue;
        }
        if('0' <= string[i] && string[i] <= '9')
        {
			number *= 10;
			number += string[i] - '0';
        }
        else
        {
        	printf_debug("\'String2Int(%s, %d)\' error!\n", string, stringLenth);
        	return 0xFFFFFFFF;
        }
    }
    if(isPositive == false)
    {
        number = -number;
    }

    return number;
}



