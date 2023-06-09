/*
 * EMBLSendCommandBySDO.h
 *
 *  Created on: 12/05/2015
 *      Author: ilia
 */

#ifndef EMBLSENDCOMMANDBYSDO_H_
#define EMBLSENDCOMMANDBYSDO_H_

#include <mmc_definitions.h>
#include "MMC_drive_comm_API.h"
#include "EMBLDefinitions.h"
/*
typedef enum
{
	eDOWNLOAD = 1,
	eUPLOAD = 2
}EMBL_SDO_SERVICE_ENUM;
*/
typedef enum
{
	eFINISHED 	= 0,
	eIN_PROCESS = 1,
	eERROR		= 2
}EMBL_SDO_PROCESS_STATUS_ENUM;

typedef struct
{
	unsigned short usIndex;
	unsigned char ucSubIndex;
	long lData;
	unsigned long ulDataLength;
}EMBL_WRITE_DATA_SDO_IN;

#define MAX_COMMANDS_ARRAY_SIZE 20
#ifdef __cplusplus

class CEMBLWriteSdoData
{
public:
	CEMBLWriteSdoData(char* pCmd, unsigned char ucSubIndex, long lData, unsigned long ulDataLength);

	virtual ~CEMBLWriteSdoData() {}

	virtual MMC_SENDSDO_IN GetSdoDataStruct(unsigned short usAxisRef);

	static unsigned short ConvertCmdToIndex(char* pCmd)
	{
		char cTmpCmd[3];
		cTmpCmd[2]='\0';
		if(!pCmd)return 0;
		for(int i = 0; i<2; i++)
		{
			cTmpCmd[i] = toupper(pCmd[i]);
		}
		return (unsigned short)(12288 + 26 * (cTmpCmd[0] - 'A') + (cTmpCmd[1] - 'A'));
	}

private:
	unsigned short m_usIndex;
	unsigned char m_ucSubIndex;
	long m_lData;
	unsigned long m_ulDataLength;
};

class CEMBLSendCommandBySDO {
public:
	CEMBLSendCommandBySDO(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEMBLSendCommandBySDO();
	int WriteCommandViaSdo(char* pCmd, unsigned char ucSubIndex, long lData, unsigned long ulDataLength);
	int ReadCommandViaSdo (char *pCmd, unsigned char ucSubIndex, long &lOut, unsigned long ulDataLength);
	unsigned short ConvertCmdToIndex(char *pCmd);
	inline void SetStatus(EMBL_SDO_PROCESS_STATUS_ENUM Status){_eStatus = Status ;}
	inline EMBL_SDO_PROCESS_STATUS_ENUM GetStatus(){return _eStatus;}
	int WriteArrCommandViaSdo(EMBL_WRITE_DATA_SDO_IN* pInParamArray,MMC_SENDSDO_OUT* pOutParam,unsigned long ulArrayLength);
	int WriteArrayCommandViaSdo(CEMBLWriteSdoData* pWriteSdoDataArray[],MMC_SENDSDO_OUT* pOutParam);


protected:
	unsigned short	m_usAxisRef;
	unsigned int	m_uiConn;

private:
	EMBL_SDO_PROCESS_STATUS_ENUM _eStatus;
	short _sErrorID;
	unsigned short	m_usSentDataCounter;

};
#endif
#endif /* EMBLSENDCOMMANDBYSDO_H_ */



