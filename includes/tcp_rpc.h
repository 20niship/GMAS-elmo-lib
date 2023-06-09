
#ifndef	_TCPRPC_FUNCS_
#define _TCPRPC_FUNCS_

#include "datastructs.h"
#include "MMC_definitions.h"

//

int MMC_CreateRpcConnect(
				IN MMC_IF_STRUCT* pMmcIf,IN char* pSockPath, unsigned short usPort,char* cpHostIPAddr);
//
int MMC_CloseRpcConnect(
				IN MMC_IF_STRUCT* pMmcIf);

int MMC_RpcSndMsg(
				IN MMC_IF_STRUCT* pMmcIf,
				IN MMC_AXIS_REF_HNDL hAxisRef,
				IN int iFuncId,
				IN void* pInParam,
				IN short iInSize,
				IN short iOutSize,
				OUT void* pOutParam);

#endif	// _TCPRPC_FUNCS_
