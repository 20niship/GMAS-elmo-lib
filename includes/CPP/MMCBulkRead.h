/*
 * MMCBulkRead.h
 *
 *  Created on: 19/01/2012
 *      Author: alexanderk
 */

#ifndef MMCBULKREAD_H_
#define MMCBULKREAD_H_

#include "MMC_definitions.h"
#include "MMCPPGlobal.h"

#define BULKREAD_DEFAULT_NUMBER_OF_AXES		2
#define BULKREAD_DEFAULT_FIRST_AXIS_REF		0
#define BULKREAD_DEFAULT_SECOND_AXIS_REF	1
#define BULKREAD_DEFAULT_IS_PRESET			1
#define BULKREAD_DEFAULT_PRESET				eNC_BULKREAD_PRESET_1
#define BULKREAD_DEFAULT_CONFIG				eBULKREAD_CONFIG_2


class DLLMMCPP_API CMMCBulkRead
{
public:

	CMMCBulkRead();
	CMMCBulkRead(MMC_CONNECT_HNDL hConnectHandle);
	CMMCBulkRead(MMC_CONNECT_HNDL hConnectHandle,
				 NC_BULKREAD_CONFIG_ENUM eConfig,
				 NC_BULKREAD_PRESET_ENUM ePreset);

	virtual ~CMMCBulkRead();

	void SetDefaultParameters();
	void SetDefaultParameters(MMC_CONFIGBULKREAD_IN stConfigBulkReadParams);

	void Config() throw (CMMCException);
	void Config(MMC_CONFIGBULKREAD_IN stCfgBulkReadIn) throw (CMMCException);

	void BulkRead() throw (CMMCException);
	void SetConnectionHandle(MMC_CONNECT_HNDL hConnectHandle) {m_hConnectHandle = hConnectHandle;}

	float m_fFactorsArray[NC_MAX_BULK_READ_READABLE_PACKET_SIZE];

	NC_BULKREAD_PRESET_1 m_pPreset1Data[NC_MAX_AXES_PER_BULK_READ];
	NC_BULKREAD_PRESET_2 m_pPreset2Data;
	NC_BULKREAD_PRESET_3 m_pPreset3Data[NC_MAX_AXES_PER_BULK_READ];
	NC_BULKREAD_PRESET_4 m_pPreset4Data[NC_MAX_AXES_PER_BULK_READ];
	NC_BULKREAD_PRESET_5 m_pPreset5Data[NC_MAX_AXES_PER_BULK_READ];

private:

	int GetAxesNum() throw (CMMCException);
	MMC_CONNECT_HNDL m_hConnectHandle;
	NC_BULKREAD_CONFIG_ENUM m_eConfiguration;
	NC_BULKREAD_PRESET_ENUM m_ePreset;

	unsigned long m_ulRvArray[NC_MAX_REC_SIGNALS_NUM];
	unsigned short m_usAxisRefArray[NC_MAX_AXES_PER_BULK_READ];
	unsigned short m_usNumberOfAxes;
	unsigned char m_ucIsPreset;

};

#endif /* MMCBULKREAD_H_ */
