/**
 * @file Config.h
 * @brief 配置相关的头文件
 * @copyright Copyright (c) 2020 Beijing SOJO Electric CO., LTD.
 * @company  SOJO
 * @date 2020.03.24
 *
 * @author Lei.L
 * @version ver 1.0
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define DEBUG_PRINTF
#ifdef DEBUG_PRINTF
#define printf_debug(fmt,...) do{printf("%s: %s[line %d]: "fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);}while(0)
#endif

#define CSV_LINE_MAX			1024			//csv数据文件一行的最大字符数
#define DATA_STRING_MAX			8				//一个数据字符串的最大字符串
#define DATA_STRING_BUF_NUM		40				//存放数据字符串的缓存区大小
#define DATA_NUMBER				12				//数据个数

#define JSON_FILENAME			"MqttConfigFile.json"
#define NAME_STRING_MAX			30				//配置结构体的名称字符串最大长度
#define VALUE_STRING_MAX		40				//配置结构体的配置值字符串最大长度

#define MOSQUITTO_PATHNAME		"~/mosquitto_pub"

/* 程序错误码 */
typedef enum {
	FUNCTION_FAIL = -1,		//函数执行错误
	NO_ERROR = 0,			//没有错误
	POINT_NULL,				//指针为空
	OPEN_FILE_FAIL,			//打开文件失败
	MALLOC_FAIL,			//分配堆内存失败
	FEW_ARGUMENTS,			//参数太少
	ERROR_ARGUMENTS,		//参数错误


}ErrorCode;

#endif
