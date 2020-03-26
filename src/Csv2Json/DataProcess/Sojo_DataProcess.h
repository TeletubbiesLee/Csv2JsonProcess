/**
 * @file Sojo_DataProcess.h
 * @brief 双杰测温接收板数据处理程序文件
 * @copyright Copyright (c) 2020 Beijing SOJO Electric CO., LTD.
 * @company  SOJO
 * @date 2020.03.26
 *
 * @author Lei.L
 * @version ver 1.0
 */

#ifndef _SOJO_DATA_PROCESS_H_
#define _SOJO_DATA_PROCESS_H_

enum {
	SOJO_TEMPERATURE = 0,
	SOJO_VOLTAGE,
};

int SOJO_Csv2Json(char *csvFilename);

#endif
