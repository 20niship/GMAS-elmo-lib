/*
 * MMCMessage.h
 *
 *  Created on: 7/8/2011
 *      Author: dmitryb
 */

#ifndef CMMCMESSAGE_H_
#define CMMCMESSAGE_H_
//
#include <stdio.h>
#include <string.h>
#include <string>
#include "mmc_definitions.h"
//
#ifndef DLLMMCPP_API
#ifdef WIN32
#include "windows.h"
#ifdef LIBMMCPPLIB_EXPORTS
#define DLLMMCPP_API __declspec(dllexport)
#else
#define DLLMMCPP_API __declspec(dllimport)
#endif
#else
#define DLLMMCPP_API
#endif
#endif
//
//
//
#define MAX_CHARACTERS_IN_LINE		400
#define DEFAULT_MESSAGE_FILE_NAME	"/var/MMC/config/resources/Personality.xml\0"
#ifdef WIN32
#pragma warning (disable : 4251)
#endif
using namespace std;
//
typedef enum
{
	MT_UNKNOWN_ERROR,
	MT_GMAS_ERROR,
	MT_LIB_ERROR,
	MT_PROFILER_ERROR,
	MT_PROFILER_WARNING,
	MT_GMAS_WARNING,
} MMCPP_MESSAGE_TYPE;
//
typedef enum
{
	HT_UNKNOWN_HEADER,
	HT_ERROR_STRING_HEADER,
	HT_ID_HEADER,
	HT_TEXT_HEADER,
	HT_RESOLUTION_HEADER,
	HT_FINISH_HEADER,
	HT_ERROR_IN_XML
} MMCPP_HEADER_TYPE;
//
typedef enum
{
	CT_UNKNOWN,
	CT_IPC,
	CT_RPC
} MMCPP_CONN_TYPE;
//
//
class DLLMMCPP_API CMMCMessage {
	//
public:
	//
	CMMCMessage()
	{
		bFOUND = false;
		iErrorID = 0;
		iRetval = 0;
		eConnectionType = CT_UNKNOWN;
		eCurrentHeaderType = HT_UNKNOWN_HEADER;
		eCurrentMessageType = MT_UNKNOWN_ERROR;
	}
	~CMMCMessage()
	{
	}
	//
	string	GetMessage(){return sMessageFileName;}
	string	GetMessageFileName(){return sMessageFileName;}
	void	SetMessageFileName(string sMessageFileName_IN){sMessageFileName = sMessageFileName_IN;}
	void	SetMessageFileName(char* cMessageFileName_IN){sMessageFileName.insert(0,cMessageFileName_IN,strlen(cMessageFileName_IN));}	
	//
	void	MessageHandler(int iRetval,int iErrorID);
	//

private:
	// Internal variables for message throw mechanism
	string				sMessageFileName;
	string				sMessage;
	bool				bFOUND;
	int					iErrorID;
	int					iRetval;
	MMCPP_CONN_TYPE 	eConnectionType;
	MMCPP_HEADER_TYPE	eCurrentHeaderType;
	MMCPP_MESSAGE_TYPE  eCurrentMessageType;
	//
	//
	void	GetAndPrintMessage(fstream &pFile);
	void	ParseMessage(fstream &pFile);
	void	UpdateMessageType();
	void	OpenMessageFile(fstream &pFile,char* cFileName = DEFAULT_MESSAGE_FILE_NAME);
	void	CloseMessageFile(fstream &pFile);
	//
};
//
#endif /* CMMCMESSAGE_H_ */

