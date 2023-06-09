/*
 * MMCEoE.h
 *
 *  Created on: 06/01/2013
 *      Author: yuvall
 */

#ifndef MMCEOE_H_
#define MMCEOE_H_

#ifndef WIN32

#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#else

#include <winsock2.h>
#include <iostream>
#include <fstream>

#endif //WIN32


#include "MMCSocket.h"
#include "MMCUDP.h"

#define EoE_BUFFER_SIZE 128

/*
 *
 */
class DLLMMCPP_API CMMCEoE : public CMMCUDP {
public:
	/**
	* default constructor
	*/
	CMMCEoE();

	/**
	* default destructor
	*/
    virtual ~CMMCEoE()
	{
		this->DestroySemSyncDrvIo();
	}

	/**! \fn SetTimeout(long lTimeOut)
	* \brief set default time out for UDP socket.
	* \param lTimeOut default to set.
	* \return none
	*/
	void SetTimeout(long lTimeOut) {this->_lTimeOut = lTimeOut;}

	/**! \fn ElmoSetAsyncArray(char szCmd[3], short iIndex, const int iVal)
	 * \brief send EoE array command asynchronously.
	 * \param szCmd the command
	 * \param iIndex EoE array index
	 * \param iValue integer value to set.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoSetAsyncArray(char cCmd[3], short iIndex, const int iVal)throw (CMMCException);

	/**! \fn ElmoSetAsyncArray(char szCmd[3], short iIndex, const float fVal)
	 * \brief send EoE array command asynchronously.
	 * \param szCmd the command
	 * \param iIndex EoE array index
	 * \param fVal real value to set.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoSetAsyncArray(char cCmd[3], short iIndex, const float fVal)throw (CMMCException);

	/**! \fn ElmoSetAsyncParameter(char szCmd[3], const int iVal)
	 * \brief send EoE command asynchronously.
	 * \param szCmd the command
	 * \param iVal value to set.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoSetAsyncParameter(char cCmd[3], const int iVal)throw (CMMCException);

	/**! \fn ElmoSetAsyncParameter(char szCmd[3], const int fVal)
	 * \brief sends EoE command asynchronously.
	 * \param szCmd the command
	 * \param fValue value to set.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoSetAsyncParameter(char cCmd[3], const float fVal)throw (CMMCException);

	/**! \fn ElmoSetArray(char szCmd[3], short iIndex, const int iVal)
	 * \brief send EoE array command.
	 * \param szCmd the command
	 * \param iIndex EoE array index
	 *  \param iVal integer value to set.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoSetArray(char cCmd[3], short iIndex, const int iVal)throw (CMMCException);

	/**! \fn ElmoSetArray(char szCmd[3], short iIndex, const int fVal)
	 * \brief send EoE array command.
	 * \param szCmd the command
	 * \param iIndex EoE array index
	 *  \param fVal real value to set.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoSetArray(char cCmd[3], short iIndex, const float fVal)throw (CMMCException);

	/*! \fn ElmoSetParameter(char szCmd[3], const int iVal)
	* \brief sets parameter of type int.
	* \param szCmd string command.
	* \param iVal integer value to set.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoSetParameter(char cCmd[3], const int iVal)throw (CMMCException);

	/*! \fn ElmoSetParameter(char szCmd[3], const int fVal)
	* \brief sets parameter of type float.
	* \param szCmd string command.
	* \param fVal float value to set.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoSetParameter(char cCmd[3], const float fVal)throw (CMMCException);

	/*! \fn ElmoGetAsyncArray(char szCmd[3], short iIndex, int& fVal)
	* \brief sends asynchronous array command to get EoE parameter.
	* 		one may get the result asynchronously as follows:
	* 		call IsReady, then ElmoReadData API.
	* \param szCmd string command.
	* \param iIndex index to array cell.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoGetAsyncArray(char cCmd[3], short iIndex)throw (CMMCException);

	/*! \fn ElmoGetAsyncParameter(char szCmd[3])
	* \brief sends asynchronous command to get EoE parameter.
	* 		one may get the result asynchronously as follows:
	* 		call IsReady, then ElmoReadData API.
	* \param szCmd string command.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoGetAsyncParameter(char cCmd[3])throw (CMMCException);

	/*! \fn ElmoGetArray(char szCmd[3], short iIndex, int& iVal)
	* \brief sends command to get EoE parameter of type integer.
	* \param szCmd string command.
	* \param iIndex	index to EoE array.
	* \param iVal reference for returned value.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoGetArray(char cCmd[3], short iIndex, int& iVal)throw (CMMCException);

	/*! \fn ElmoGetArray(char szCmd[3], short iIndex, int& iVal)
	* \brief sends command to get EoE parameter of type float.
	* \param szCmd string command.
	* \param iIndex	index to EoE array.
	* \param fVal reference for returned value.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoGetArray(char cCmd[3], short iIndex, float& fVal)throw (CMMCException);

	/*! \fn ElmoGetParameter(char szCmd[3], int& iVal)
	* \brief gets EoE parameter of type integer.
	* \param szCmd string command.
	* \param iVal reference for returned value.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoGetParameter(char cCmd[3], int& iVal)throw (CMMCException);

	/*! \fn ElmoGetParameter(char szCmd[3], float& fVal)
	* \brief gets EoE parameter of type float.
	* \param szCmd string command.
	* \param fVal reference for returned value.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoGetParameter(char cCmd[3], float& fVal)throw (CMMCException);

	/*! \fn ElmoGetParameter(char szCmd[3], char szVal[], int iSize)
	* \brief gets EoE parameter of type string.
	* \param szCmd string command.
	* \param szVal	storage for returned value.
	* \param iSize size of szVal.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoGetParameter(char szCmd[3], char szVal[], int iSize)throw (CMMCException);

	/*! \fn ElmoReadData(char* cBuffer, int iSize)
	* \brief read EoE response from driver and search for ';' suffix
	* 		 as for asynchronous response.
	* \param cBuffer address of buffer to store response.
	* \param iSize expected response message length.
	* \return	return number of read characters - 0 if none.
	*/
	int ElmoReadData(char* cBuffer, int iSize)throw (CMMCException);

	/**! \fn ElmoReadData(int& iValue)
	 * \brief read EoE data and set iValue accordingly.
	 * \param iValue set with returned value if completed successfully.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoReadData(int& iValue);

	/**! \fn ElmoReadData(float& fValue)
	 * \brief read EoE data and set fValue accordingly.
	 * \param fValue set with returned value if completed successfully.
	 * \return 0 on success otherwise error (<0).
	 */
	int ElmoReadData(float& fValue);

	/*! \fn ElmoCall(const char szCmd[3])
	* \brief sends EoE command for execution.
	* \param szCmd string command.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoCall(const char szCmd[3])throw (CMMCException);

	/*! \fn ElmoCallAsync(const char szCmd[3])
	* \brief sends EoE command for execution.
	* \param szCmd string command.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoCallAsync(const char szCmd[3])throw (CMMCException);

	/*! \fn ElmoAck(char* szBuffer, int iSize)
	* \brief checks wether or not a previous EoE command is acknowlaged.
	* \param szBuffer string buffer to store the acknowledgement.
	* \param iSize buffer size - number of bytes to store on success.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoAck(char* szBuffer, int iSize)throw (CMMCException);

	/*! \fn ElmoExecuteLabel(const char *szCmd)
	* \brief sends EoE command for user program execution.
	* \param szCmd string command.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoExecuteLabelAsync(const char *szCmd)throw (CMMCException);

	/*! \fn ElmoExecuteLabelAsync(const char *szCmd)
	* \brief sends EoE command for user program execution.
	* \param szCmd string command.
	* \return 0 on success otherwise error (<0).
	*/
	int ElmoExecuteLabel(const char *szCmd)throw (CMMCException);

protected:
	/*! \fn GetAck(char* cBuffer, int iSize)
	* \brief read EoE response from and search for ';' suffix as for acknowledge.
	* \param cBuffer address of buffer to store response.
	* \param iSize expected response message length.
	* \return	return number of read characters - 0 if none.
	*/
	int GetAck(char* cBuffer, int iSize)throw (CMMCException);

	/**! \fn ParseResult(char *szResult, int& iVal)
	 * \brief parses read string and set fVal with accordance.
	 * \param szResult read data from UDP socket (EoE)
	 * \param iVal set with real value if completed successfully.
	 * \return 1 if completed successfully, 0 otherwise.
	 */
	int ParseResult(char *szResult, int& iVal);

	/**! \fn ParseResult(char *szResult, float& fVal)
	 * \brief parses read string and set fVal with accordance.
	 * \param szResult read data from UDP socket (EoE)
	 * \param fVal set with real value if completed successfully.
	 * \return 1 if completed successfully, 0 otherwise.
	 */
	int ParseResult(char *szResult, float& fVal);

	/**! \fn ParseResult(char *szResult, char szRetVal[], int iSize)
	 * \brief parses read string and set szRetVal with accordance.
	 * \param szResult read data from UDP socket (EoE)
	 * \param szRetVal set with string value if completed successfully.
	 * \param iSize maximum length allowed for szRetVal.
	 * \return 1 if completed successfully, 0 otherwise.
	 */
	int ParseResult(char *szResult, char szRetVal[], int iSize);

private:
	int InitSemSyncDrvIo	(void) throw (CMMCException);
	int DestroySemSyncDrvIo	(void) throw (CMMCException);
	int TakeSemSyncDrvIo	(void) throw (CMMCException);
	int ReleaseSemSyncDrvIo	(void) throw (CMMCException);

private:
    long _lTimeOut;
    char _szBuffer[EoE_BUFFER_SIZE];

#ifdef WIN32
#else
			/* Sync thread aginst driver for complet set of send /recev. pakget */
pthread_mutex_t gSemSyncDrvIo;
#endif
};
#endif /* MMCEOE_H_ */
