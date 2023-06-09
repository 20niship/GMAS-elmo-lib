/*
 * MMCNetwork.h
 *
 *  Created on: 27/03/2011
 *      Author: yuvall
 */

#ifndef MMCNETWORK_H_
#define MMCNETWORK_H_

#include "MMCPPGlobal.h"

class DLLMMCPP_API CMMCNetwork {
public:
	CMMCNetwork();
	~CMMCNetwork();

	void SetConnHndl(MMC_CONNECT_HNDL uiConnHndl) {m_uiConnHndl = uiConnHndl;}

	void ResetCommStatistics(MMC_RESETCOMMSTATISTICS_OUT& stOutParams) throw (CMMCException);
	void ResetCommDiagnostics(MMC_RESETCOMMDIAGNOSTICS_OUT& stOutParams) throw (CMMCException);
	void GetCommDiagnostics(MMC_GETCOMMDIAGNOSTICS_OUT& stOutParams) throw (CMMCException);
	int GetCommStatistic(MMC_GETCOMMSTATISTICS_OUT& stOutParams) throw (CMMCException);
	int GetNetworkInfo(MMC_NETWORKINFO_OUT& stOutParams) throw (CMMCException);
	//
private:
	MMC_CONNECT_HNDL m_uiConnHndl;					/*!< communication session handler;					*/
};

#endif /* MMCNETWORK_H_ */
