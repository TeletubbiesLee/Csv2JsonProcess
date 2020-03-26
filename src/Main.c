/**
 * @file main.c
 * @brief CSV数据文件转换为JSON文件的程序main函数文件
 * @copyright Copyright (c) 2020 Beijing SOJO Electric CO., LTD.
 * @company  SOJO
 * @date 2020.03.26
 *
 * @author Lei.L
 * @version ver 1.0
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Config.h"
#include "Csv2Json/DataProcess/Sojo_DataProcess.h"


int main(int argc, char *arhv[])
{
	int i = 0, j = 0, ret = NO_ERROR;
	char newPathname[60] = {0};					//存放新文件夹路径
	DIR *csvDataDirentPoint = NULL;			//存放csv数据文件的文件夹指针
	char *csvDataDirentName = "CSV_Data";		//存放csv数据文件的文件夹名字
	char *backupDirentName = "/home/root/backup/";			//数据备份文件夹路径
	struct dirent *csvFile = NULL;				//csv数据文件结构体指针
	struct stat fileStat;						//文件状态
	char historyFile[20][60];

	for(i = 0; i < 20; i++)
	{
		memset(historyFile[i], 0, sizeof(historyFile[i]));
	}

	/* 建立数据备份文件夹 */
	mkdir(backupDirentName, S_IRWXU);

	//while(1)
	{
		j = 0;
		if((csvDataDirentPoint = opendir(csvDataDirentName)) == NULL)
		{
			printf_debug("Cannot open directory: %s\n", csvDataDirentName);
		}
		chdir(csvDataDirentName);

		/* 依次读取该文件夹下的文件 */
		while((csvFile = readdir(csvDataDirentPoint)) != NULL && j < 20)
		{
			lstat(csvFile->d_name, &fileStat);
			if(S_ISREG(fileStat.st_mode))			//判断是否为文件
			{
				printf("open file %s\n", csvFile->d_name);
				SOJO_Csv2Json(csvFile->d_name);

				strncpy(historyFile[j++], csvFile->d_name, strlen(csvFile->d_name));
			}
			sleep(1);
		}

		/* 将传输完毕的数据文件进行备份 */
		for(i = 0; i < j; i++)
		{
			memset(newPathname, 0, sizeof(newPathname));
			strncat(newPathname, backupDirentName, strlen(backupDirentName));
			strncat(newPathname, historyFile[i], strlen(historyFile[i]));
			printf("%s -> %s\n", historyFile[i], newPathname);
			rename(historyFile[i], newPathname);
			memset(historyFile[i], 0, strlen(historyFile[i]));
		}

		chdir("../");
		closedir(csvDataDirentPoint);

		//sleep(10);
	}

	return ret;
}







































/**
 *               ii.                                         ;9ABH,
 *              SA391,                                    .r9GG35&G
 *              &#ii13Gh;                               i3X31i;:,rB1
 *              iMs,:,i5895,                         .5G91:,:;:s1:8A
 *               33::::,,;5G5,                     ,58Si,,:::,sHX;iH1
 *                Sr.,:;rs13BBX35hh11511h5Shhh5S3GAXS:.,,::,,1AG3i,GG
 *                .G51S511sr;;iiiishS8G89Shsrrsh59S;.,,,,,..5A85Si,h8
 *               :SB9s:,............................,,,.,,,SASh53h,1G.
 *            .r18S;..,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....,,.1H315199,rX,
 *          ;S89s,..,,,,,,,,,,,,,,,,,,,,,,,....,,.......,,,;r1ShS8,;Xi
 *        i55s:.........,,,,,,,,,,,,,,,,.,,,......,.....,,....r9&5.:X1
 *       59;.....,.     .,,,,,,,,,,,...        .............,..:1;.:&s
 *      s8,..;53S5S3s.   .,,,,,,,.,..      i15S5h1:.........,,,..,,:99
 *      93.:39s:rSGB@A;  ..,,,,.....    .SG3hhh9G&BGi..,,,,,,,,,,,,.,83
 *      G5.G8  9#@@@@@X. .,,,,,,.....  iA9,.S&B###@@Mr...,,,,,,,,..,.;Xh
 *      Gs.X8 S@@@@@@@B:..,,,,,,,,,,. rA1 ,A@@@@@@@@@H:........,,,,,,.iX:
 *     ;9. ,8A#@@@@@@#5,.,,,,,,,,,... 9A. 8@@@@@@@@@@M;    ....,,,,,,,,S8
 *     X3    iS8XAHH8s.,,,,,,,,,,...,..58hH@@@@@@@@@Hs       ...,,,,,,,:Gs
 *    r8,        ,,,...,,,,,,,,,,.....  ,h8XABMMHX3r.          .,,,,,,,.rX:
 *   :9, .    .:,..,:;;;::,.,,,,,..          .,,.               ..,,,,,,.59
 *  .Si      ,:.i8HBMMMMMB&5,....                    .            .,,,,,.sMr
 *  SS       :: h@@@@@@@@@@#; .                     ...  .         ..,,,,iM5
 *  91  .    ;:.,1&@@@@@@MXs.                            .          .,,:,:&S
 *  hS ....  .:;,,,i3MMS1;..,..... .  .     ...                     ..,:,.99
 *  ,8; ..... .,:,..,8Ms:;,,,...                                     .,::.83
 *   s&: ....  .sS553B@@HX3s;,.    .,;13h.                            .:::&1
 *    SXr  .  ...;s3G99XA&X88Shss11155hi.                             ,;:h&,
 *     iH8:  . ..   ,;iiii;,::,,,,,.                                 .;irHA
 *      ,8X5;   .     .......                                       ,;iihS8Gi
 *         1831,                                                 .,;irrrrrs&@
 *           ;5A8r.                                            .:;iiiiirrss1H
 *             :X@H3s.......                                .,:;iii;iiiiirsrh
 *              r#h:;,...,,.. .,,:;;;;;:::,...              .:;;;;;;iiiirrss1
 *             ,M8 ..,....,.....,,::::::,,...         .     .,;;;iiiiiirss11h
 *             8B;.,,,,,,,.,.....          .           ..   .:;;;;iirrsss111h
 *            i@5,:::,,,,,,,,.... .                   . .:::;;;;;irrrss111111
 *            9Bi,:,,,,......                        ..r91;;;;;iirrsss1ss1111
 *
 *								狗头保佑，永无BUG！
 */





