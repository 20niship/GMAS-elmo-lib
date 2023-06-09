/*
 * CMMCErrorCore.h
 *
 *  Created on: 05/07/2011
 *      Author: yuvall
 */

#ifndef CMMCERRORCORE_H_
#define CMMCERRORCORE_H_

#include "MMCPPGlobal.h"
/*
 *
 */
class DLLMMCPP_API CMMCErrorCorr {
public:
	CMMCErrorCorr():m_uiConnHndl(0) {}
	CMMCErrorCorr(MMC_CONNECT_HNDL uiConnHndl):m_uiConnHndl(uiConnHndl) {}
	virtual ~CMMCErrorCorr();

	void SetConnectionHndl(MMC_CONNECT_HNDL uiConnHndl){m_uiConnHndl = uiConnHndl;}
	MMC_CONNECT_HNDL GetConnectionHndl(){return m_uiConnHndl;}

	/**
	 * \fn	LoadErrorCorrTable(MMC_LOADERRORTABLE_IN& stInParams, int* iErrLineNum)
	 * \brief	this method loads an error correction table.
	 * \param	stInParams	table parameters
	 * \param	iErrLineNum out address to retrieve line number in case of loading error (failure).
	 * 			default is NULL for backward compatibility.
	 * \return	0 on success, otherwise error or exception thrown.
	 */
	int LoadErrorCorrTable(MMC_LOADERRORTABLE_IN& stInParams, int* iErrLineNum=NULL) throw (CMMCException);

	/**
	 * \fn	LoadErrorCorrTable(char pPathToETFile[NC_MAX_ET_FILE_PATH_LENGTH], NC_ERROR_TABLE_NUMBER eETNumber, double dMaxCorrectionDelta = 0, int* iErrLineNum=NULL)
	 * \brief	this method loads an error correction table.
	 * \param	pPathToETFile path to table file on target controller.
	 * \param	eETNumber table  index in journal.
	 * \param	dMaxCorrectionDelta maximum allowed aberration(error delta).  default is 0 as for no aberration allowed.
	 * \param	iErrLineNum out address to retrieve line number in case of loading error (failure).
	 * 			default is NULL for backward compatibility.
	 * \return	0 on success, otherwise error or exception thrown.
	 */
	void LoadErrorCorrTable(char pPathToETFile[NC_MAX_ET_FILE_PATH_LENGTH], NC_ERROR_TABLE_NUMBER eETNumber, double dMaxCorrectionDelta = 0, int* iErrLineNum=NULL) throw (CMMCException);

	/**
	 * \fn	LoadErrorCorrTable(NC_ERROR_TABLE_NUMBER eETNumber, double dMaxCorrectionDelta = 0, int* iErrLineNum=NULL)
	 * \brief	this method loads an error correction table.
	 * \param	eETNumber table  index in journal.
	 * \param	dMaxCorrectionDelta maximum allowed aberration(error delta). default is 0 as for no aberration allowed.
	 * \param	iErrLineNum out address to retrieve line number in case of loading error (failure).
	 * 			default is NULL for backward compatibility.
	 * \return	0 on success, otherwise error or exception thrown.
	 */
	void LoadErrorCorrTable(NC_ERROR_TABLE_NUMBER eETNumber, double dMaxCorrectionDelta = 0, int* iErrLineNum=NULL) throw (CMMCException);

	int UnloadErrorCorrTable(NC_ERROR_TABLE_NUMBER eTableNumber) throw (CMMCException);
	int EnableErrorCorrTable(NC_ERROR_TABLE_NUMBER eTableNumber) throw (CMMCException);
	int DisableErrorCorrTable(NC_ERROR_TABLE_NUMBER eTableNumber) throw (CMMCException);

	void GetErrorTableStatus(NC_ERROR_TABLE_NUMBER eTableNumber, MMC_GETERRORTABLESTATUS_OUT &stOutParams);
	bool IsTableEnabled(NC_ERROR_TABLE_NUMBER eETNumber) throw (CMMCException);
	bool IsTableLoaded(NC_ERROR_TABLE_NUMBER eETNumber) throw (CMMCException);		

private:
	MMC_CONNECT_HNDL m_uiConnHndl;
};

#endif /* CMMCERRORCORE_H_ */
