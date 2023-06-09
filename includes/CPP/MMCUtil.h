/*
 * MMCUtil.h
 *
 *  Created on: 21/07/2013
 *      Author: Haim Hillel
 */

#ifndef MMCUtil_H_
#define MMCUtil_H_

#include "MMC_definitions.h"
#include "MMCPPGlobal.h"


class DLLMMCPP_API CMMCUtil
{
public:
	 CMMCUtil();

	~CMMCUtil();

					/* Function steps: ensure server running, transfer file, shutdown server (conditional)	*/
						/* Download ("ImportFile") direction is "TO Gmas"	*/
						/* if FileName including path it ignore (removes)	*/
						/* DesHostFilePath keep on host (not send to client)*/
						/* if null keep previous path or use the default.	*/
int	UtilDownloadFile(IN MMC_CONNECT_HNDL ConnHndl, char* FileName, char* DesHostFilePath, char* RpcHostIp, MMC_DOWNLOAD_TYPE_ENUM FileDownloadType)	throw (CMMCException);
						/* Upload ("ExportFile") direction is "FROM Gmas"	*/
int UtilUploadFile  (IN MMC_CONNECT_HNDL ConnHndl, char* FileName, char* DesHostFilePath, char* RpcHostIp, MMC_DOWNLOAD_TYPE_ENUM FileDownloadType)	throw (CMMCException);
						/* If the server not running, run it and flag it	*/
						/* for stay running.								*/
						/* DesHostFilePath keep on host (not send to client)*/
						/* if null keep previous path or use the default.	*/
int	UtilStartTftpServer(char* DesHostFilePath);
						/* If Tftp server running stop it.					*/
void	UtilStopTftpServer(void);
						/* Set the TFTP low level services to new speak	(report level), return the	*/
						/* running speak level.														*/
						/* Range 0 (=HSTFTPAPP_SPEAK_LVL_ALL) to 5 (=HSTFTPAPP_SPEAK_LVL_NONE)		*/
						/* If value is out of range (Eg -1) set it same as DEF_SPEAK_LVL			*/
						/* (concider its the "default").											*/
						/* The newSpeakLvl effect Only during calling actions between 				*/
						/* UtilStartTftpServer to UtilStopTftpServer.								*/
						/* While calling UtilDownloadFile or UtilUploadFile which rerunning server,	*/
						/* (no preciding call to UtilStartTftpServer) the server rerunning with 	*/
						/* default speak level...													*/
int	UtilSetTftpSpeakLvl(int newSpeakLvl);



private:
	BOOL	bReqServerStayRunning;

						/* Activate TFTP Server.							*/
						/* For detaile about activation argument look in	*/
						/* HsTftpApp.cpp for entry name:					*/
						/*                UTILTFTP_MAIN_EP_NAME				*/
						/* DesHostFilePath is host file location,replace	*/
						/* location from client (if client send location	*/
						/* its location is ignore).							*/
						/* Look in the .cpp file for detailing,				*/
						/* if null keep previous path or use the default.	*/
int	UtilActivateTftpServer(char* DesHostFilePath);
};

#endif /* #ifndef MMCUtil_H_ */

