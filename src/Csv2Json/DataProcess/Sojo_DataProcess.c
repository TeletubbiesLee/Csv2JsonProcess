/**
 * @file Sojo_DataProcess.c
 * @brief 双杰测温接收板数据处理程序文件
 * @copyright Copyright (c) 2020 Beijing SOJO Electric CO., LTD.
 * @company  SOJO
 * @date 2020.03.26
 *
 * @author Lei.L
 * @version ver 1.0
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../ParserCSV/ParseDataFile.h"
#include "Sojo_DataProcess.h"
#include "../../Config.h"


static float Temperature[64] = {0};			//存放温度数值

static int GetTimeStr(char *timeStr);
static void SOJO_TemperatureDataProcess(int registerData[], int arrayNumber);
static int SOJO_SaveJsonFile(char *fileName, int modeSelection, int arrayNumber);


/**
 * @fn SOJO_Csv2Json
 * @brief 解析数据文件。将CSV数据文件解析为字符串
 * @param fileName 文件名
 * @param registerData 用于存放解析完成后的数据
 * @param arrayNumber 数据数组大小
 * @return 成功:解析到的数据个数 错误:-1
 */
int SOJO_Csv2Json(char *csvFilename)
{
	int dataArray[512] = {0};
	int dataNumber = 0;
	char fileName[FILENAME_STRING_MAX] = {0};    //文件名
	char temp[20] = {0};

	dataNumber = ParseCSVDataFile(csvFilename, dataArray, 512);
	SOJO_TemperatureDataProcess(dataArray, dataNumber);

	GetTimeStr(temp);
	strncat(fileName, JSON_DIR_NAME, strlen(JSON_DIR_NAME));
	strncat(fileName, temp, strlen(temp));
	strncat(fileName, ".json", strlen(".json"));
	SOJO_SaveJsonFile(fileName, SOJO_TEMPERATURE, dataNumber);

	return NO_ERROR;
}


/**
 * @fn GetTimeStr
 * @brief 获取当前时间字符串
 * @param timeStr 保存时间字符串
 * @return 成功:0 错误:-1
 */
static int GetTimeStr(char *timeStr)
{
    time_t rawTime;
    struct tm *info;

    time(&rawTime);     //获取当前时间
    info = localtime(&rawTime);

    strftime(timeStr, 20, "%Y%m%d%H%M%S", info);    //时间字符串格式化

    return NO_ERROR;
}


/**
 * @fn SOJO_TemperatureDataProcess
 * @brief 双杰温度数据处理
 * @param registerData 用于存放数据
 * @param arrayNumber 数据个数
 * @return void
 * @updata: [2020-01-07][Gang][creat]
 */
static void SOJO_TemperatureDataProcess(int registerData[], int arrayNumber)
{
	int i = 0;
	int tempValue = 0;				//存放临时值

	for(i = 0; i < arrayNumber; i++)
	{
		if(registerData[i] & (1 << 15))
		{
			tempValue = ~registerData[i] + 1;
			tempValue &= (1 << 15);
		}
		else
		{
			tempValue = registerData[i];
		}
		Temperature[i] = tempValue / 10.0;
	}
}


/**
  * @brief : 将数据保存到json文件中
  * @param : fileName json文件的文件名
  * @return: 返回值
  * @updata: [2020-01-08][Gang][creat]
  */
static int SOJO_SaveJsonFile(char *fileName, int modeSelection, int arrayNumber)
{
    int fileNameFd;         //读取文件的文件描述符
    char str[128] = {0};     //存放需要保存到文件中的字符
    int i = 0;

    fileNameFd = open(fileName, O_RDWR | O_CREAT | O_TRUNC);

    /* 根据全局变量中读取到的数据，写json文件 */
    write(fileNameFd, "{\r\n", strlen("{\r\n"));

    switch(modeSelection)
    {
        case SOJO_TEMPERATURE:
            for(i = 0; i < arrayNumber; i++)
            {
				sprintf(str, "\t\"Temperature %d\":%.1f,\r\n", i, Temperature[i]);
				write(fileNameFd, str, strlen(str));
            }
            break;
        case SOJO_VOLTAGE:
            for(i = 0; i < arrayNumber; i++)
            {
				sprintf(str, "\t\"Voltage %d\":%f,\r\n", i, Temperature[i]);
				write(fileNameFd, str, strlen(str));
            }
            break;
    }


	lseek(fileNameFd, -3, SEEK_END);
    write(fileNameFd, "\r\n}\r\n", strlen("\r\n}\r\n"));

    close(fileNameFd);

    return 0;
}

