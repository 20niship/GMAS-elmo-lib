/*
 * CMMCMotionAxis.h
 *
 *  Created on: 20/05/2012
 *      Author: Alex
 */

#ifndef CMMCMOTIONAXIS_H_
#define CMMCMOTIONAXIS_H_

#include "MMC_definitions.h"
#include "MMCNode.h"
#include "MMCPPGlobal.h"

class DLLMMCPP_API CMMCMotionAxis : public CMMCNode
{
public:
	/*! \fn default constructor
	 */
	CMMCMotionAxis();

	CMMCMotionAxis(MMC_CONNECT_HNDL uiConnHndl);
	/*! \fn copy constructor
	 */
	CMMCMotionAxis(CMMCMotionAxis& axis):CMMCNode(axis){}

	/*! \fn destructor
 	 */
	virtual ~CMMCMotionAxis();

public:


	/*! \fn unsigned int GetFbDepth(const unsigned int uiHndl)
	* \brief This function sends a command for receive number of function blocks in Node Queue .
	* \param  uiHndl handler of which to Get F.B. Depth output parameters
	* \return	return - number of function blocks on success, otherwise throws CMMCException.
	*/
	unsigned int GetFbDepth() throw (CMMCException);


	/*! \fn unsigned int EnableMotionEndedEvent()
	* \brief This function Enable the event of ended motion
	* \param
	* \return
	*/
	void EnableMotionEndedEvent() throw (CMMCException);


	/*! \fn unsigned int DisableMotionEndedEvent()
	* \brief This function Disable the event of ended motion
	* \param
	* \return
	*/
	void DisableMotionEndedEvent() throw (CMMCException);


	/*! \fn unsigned int GetStatusRegister()
	* \brief This function Insert a dwell fb to the FB queue of the axis
	* \return	return - 0 on success, otherwise throws CMMCException.
	*/
	void Dwell(unsigned long ulDwellTimeMs) throw (CMMCException);

	/*! \fn unsigned int InsertNotificationFb()
	* \brief This function Insert a notification FB that will generate event when called
	* \return	return - 0 on success, otherwise throws CMMCException.
	*/
	void InsertNotificationFb(int iEventCode) throw (CMMCException);
	void InsertNotificationFb(MMC_INSNOTIFICATIONFB_IN stInParams) throw (CMMCException);

	/*! \fn void WaitUntilConditionFB()
	* \brief This function Insert a condition fb to the queue of the node
	* \return	in case of error throws CMMCException.
	*/
	void WaitUntilConditionFB(MMC_WAITUNTILCONDITIONFB_IN stInput) throw (CMMCException);

	void WaitUntilConditionFBEX(MMC_WAITUNTILCONDITIONFBEX_IN stInput) throw (CMMCException);

	/*! \fn void KillRepetitive()
	* \brief This function stop the repetitive motion after current FB
	* \return	in case of error throws CMMCException.
	*/
	void KillRepetitive() throw (CMMCException);

	/*! \fn MC_PATH_REF InitPVTTable()
	 * \brief This function loads PVT table from file
	 * \param ulMaxPoints - Maximum points for one table
	 * \param ulUnderflowThreshold - Upon reaching this threshold, an event will be generated
	 * \param ucIsCyclic - Is the table cyclic
	 * \param ucIsDynamic - Is dynamic append allowed
	 * \param ucIsPosAbsolute - Are the position units absolute
	 * \return void
	*/
	virtual MC_PATH_REF InitPVTTable(unsigned long ulMaxPoints,
						   unsigned long ulUnderflowThreshold,
						   unsigned char ucIsCyclic,
						   unsigned char ucIsPosAbsolute,
						   unsigned short usDimension,
						   MC_COORD_SYSTEM_ENUM eCoordSystem,
						   NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_ARRAY) throw (CMMCException);

	/*! \fn MC_PATH_REF InitPTTable()
	 * \brief This function allocates and init PT (online spline) table on GMAS
	 * \param ulMaxPoints - Maximum points for one table
	 * \param ulUnderflowThreshold - Upon reaching this threshold, an event will be generated
	 * \param ucIsCyclic - Is the table cyclic
	 * \param ucIsDynamic - Is dynamic append allowed
	 * \param ucIsPosAbsolute - Are the position units absolute
	 * \param eSplineMode	- defines the way spline if calculated (FT/VT/CV_DWELL)
	 * \parma ConstVelocity	- constant velocity is forced on all segments
	 * \parma FixedType	- constant time (ms) is forced on all segments
	 * \return void
	*/
	virtual MC_PATH_REF InitPTTable(unsigned long ulMaxPoints,
						   unsigned long ulUnderflowThreshold,
						   unsigned char ucIsCyclic,
						   unsigned char ucIsDynamic,
						   unsigned char ucIsPosAbsolute,
						   unsigned short usDimension,
						   MC_COORD_SYSTEM_ENUM eCoordSystem,
						   NC_ONLINE_SPLINE_MODE_ENUM eSplineMode = MC_QUINTIC_ON_PARAB_VT_DWELL,
						   double ConstVelocity = 1000.0,
						   double FixedTime = 2.0) throw (CMMCException);



	/*! \fn void LoadPVTTable()
	 * \brief This function loads PVT table from file
	 * \param char* pFileName - File Name
	 * \return void
	 */
	virtual MC_PATH_REF LoadPVTTableFromFile(char* pFileName,
			MC_COORD_SYSTEM_ENUM eCoordSystem,
			NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_FILE) throw (CMMCException);

	/*! \fn void LoadPTTable()
	* \brief This function loads PT (online spline) table from file
	* \param char* pFileName - File Name
	* \param eCoordSystem coordinate system (ACS/MCS/PCS or NONE)
	* \return	- handler (>=0) of loaded table if loaded successfully otherwise 
				throws an exception or returns an error (<0).
	*/
	virtual MC_PATH_REF LoadPTTableFromFile(char* pFileName,
			MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);

	MC_PATH_REF CamTableInit(unsigned long ulMaxPoints,
									unsigned short usDimension,
									unsigned char ucIsFixedGap=0,
									CURVE_TYPE_ENUM eCurveType=ePolynom5Interp) throw (CMMCException);
	MC_PATH_REF CamTableSelect(const MC_CamRef& CamTableDescr,
					unsigned char ucIsMasterPosAbsolute,
					unsigned char ucIsSlavePosAbsolute,
					unsigned int uiStartMode = 0) throw (CMMCException);
	int CamTableAdd(MC_PATH_REF hMemHandle, double *dbTable, unsigned short usColumns, unsigned long ulNumberOfPoints) throw (CMMCException);

	int CamTableAddEx(MC_PATH_REF hMemHandle, double *dbTable, unsigned short usColumns, unsigned long ulNumberOfPoints);

	int CamTableSet(MC_PATH_REF hMemHandle, double *dbTable, unsigned short usColumns, unsigned long ulStartIndex, unsigned long ulNumberOfPoints) throw (CMMCException);
//#ifdef _DEBUG
//	int CamTablePrint(MC_PATH_REF hMemHandle, unsigned long ulStartIndex, unsigned long ulNumberOfPoints) throw (CMMCException);
//#endif	
	/**
	* \fn	int CamGetStatus(unsigned long ulEndOfProfile,
					unsigned long ulCurrentIndex,
					unsigned long ulCycle,
					unsigned short usStatus,
					short sErrorID) throw (CMMCException)
	* \brief	retrieve status of MC_CamIn FB on this axis and other parameters as given on this list
	* \param	ulEndOfProfile counts number of exists from cam table.
	* \param	ulCurrentIndex returned segment (index) in CAM table, wich is currently proccessed.
	* \param	ulCycle		returned process cycle  of CamIn on this axis
	* \param	usStatus	returned FB status
	* \param	sErrorID	returned with error number if error
	* \return	0 if completed successfully, otherwise error or thrown exception.
	*/
	int CamGetStatus(unsigned long& ulEndOfProfile,	//counts number of exists from cam table
					unsigned long& ulCurrentIndex,
					unsigned long& ulCycle,
					unsigned short& usStatus,
					short& sErrorID)  throw (CMMCException);

	/**
	* \fn	int CamGetStatus(unsigned long ulEndOfProfile,
					unsigned long ulCurrentIndex,
					unsigned long ulCycle,
					unsigned short usStatus,
					short sErrorID) throw (CMMCException)
	* \brief	retrieve status of MC_CamIn FB on this axis and other parameters as given on this list
	* \param	ulEndOfProfile counts number of exists from cam table.
	* \param	ulCurrentIndex returned segment (index) in CAM table, wich is currently proccessed.
	* \param	ulCycle		returned process cycle  of CamIn on this axis
	* \param	usStatus	returned FB status
	* \param	sErrorID	returned with error number if error
	* \param	uiCamTableID return table handler if FB is active.
	* \return	0 if completed successfully, otherwise error or thrown exception.
	*/
	int CamGetStatus(unsigned long& ulEndOfProfile,
					unsigned long& ulCurrentIndex,
					unsigned long& ulCycle,
					unsigned short& usStatus,
					short& sErrorID, unsigned int& uiCamTableID) throw (CMMCException);

	int CamSetProperty(ECAM_PROPERTIES_ENUM eProperty, ECAM_PERIODIC_ENUM ePeriodicMode) throw (CMMCException);

	int CamIn(
		unsigned short usMaster,
		MC_BUFFERED_MODE_ENUM eBufferMode,
		unsigned int uiCamTableID,
		CURVE_TYPE_ENUM eCurveType,
		unsigned int ucAutoOffset = 0,
		ECAM_PERIODIC_ENUM ePeriodic=eCAM_NON_PERIODIC,
		double dbMasterSyncPosition=0.0,	//relative to first row in CAM table
		double dbMasterStartDistance = 0,	//for now, until we have Ram-In implemented.
		unsigned int uiStartMode = 0,
		double dbMasterOffset = 0,
		double dbSlaveOffset = 0,
		double dbMasterScaling = 1,
		double dbSlaveScaling = 1,
		ECAM_VALUE_SRC_ENUM eMasterValueSource = eECAM_SET_VALUE) throw (CMMCException);
	
	int CamOut() throw (CMMCException);
	/*! \fn void MovePVT()
	 * \brief This function moves along the PVT table
	 * \param eCoordSystem - Coordinate system - not relevant in case of single axis
	 * \return void
	 */
	virtual void MovePVT(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);

	/*! \fn void MovePT()
	 * \brief This function moves along the PT table (online spline)
	 * \param hMemHandle - table access handler (index to journal on GMAS)
	 * \param eCoordSystem - Coordinate system - not relevant in case of single axis
	 * \return 0 if completed successfully, otherwise error
	 */
	virtual int MovePT(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);


	/*! \fn void UnloadPVTTable()
	 * \brief This function unloads PVT table
	 * \return void
	 */
	void UnloadPVTTable(MC_PATH_REF hMemHandle) throw (CMMCException);
	void CamTableUnload(MC_PATH_REF hMemHandle) throw (CMMCException) { UnloadPVTTable(hMemHandle);} 
	void UnloadCamTable(MC_PATH_REF hMemHandle) throw (CMMCException) { UnloadPVTTable(hMemHandle);}  //same as CamTableUnload but compatible to PT/PVT naming convension.
	void UnloadPTTable(MC_PATH_REF hMemHandle) throw (CMMCException) {UnloadPVTTable(hMemHandle);}


	/*! \fn void AppendPointsToTableCmn
	 * \brief This function appends points to an existing table
	 * \param CMMCAxis* - Pointer to axis
	 * \param cName - Axis name
	 * \param hConn - Connection handle
	 * \return void
	 */
	void AppendPVTPoints(MC_PATH_REF hMemHandle,
							    double (&dTable)[NC_PVT_ECAM_MAX_ARRAY_SIZE],
							    unsigned long ulNumberOfPoints,
								unsigned char ucIsTimeAbsolute = 0,
								NC_MOTION_TABLE_TYPE_ENUM eTableType = eNC_TABLE_PVT_ARRAY) throw (CMMCException);

	/*! \fn void AppendPTPoints()
	 * \brief This function appends points to an existing table
	 * \param hMemHandle - table handler
	 * \param dTable - and array contains ulNumberOfPoints points (rows)
	 * \param ulNumberOfPoints - numbe of points to append (set) to (in) table on GMAS.
	 * \param ucAutoAppend - flag for automatic append. if true, GMAS ignores ulStartIndex
							 and appends all points to the end of existing table.
	 * \param ulStartIndex - table segment on GMAS from which to start the append process.
	 * \param ucIsTimeAbsolute - tells GMAS whether the time column is absolute or relative (absolute or relative to previous row).
	 *							 if absolute the its relative to FB activation time.
	 * \return void
	 */
	void AppendPTPoints(MC_PATH_REF hMemHandle,
						double dTable[NC_PVT_ECAM_MAX_ARRAY_SIZE],
						unsigned long ulNumberOfPoints,
						unsigned char ucAutoAppend,
						unsigned long ulStartIndex,
						unsigned char ucIsTimeAbsolute = 0) throw (CMMCException);


		/*! \fn void AppendPointsToTableCmn
	 * \brief This function appends points to an existing table
	 * \param CMMCAxis* - Pointer to axis
	 * \param cName - Axis name
	 * \param hConn - Connection handle
	 * \return void
	 */
	void AppendPVTPoints(MC_PATH_REF hMemHandle,
							    double (&dTable)[NC_PVT_ECAM_MAX_ARRAY_SIZE],
							    unsigned long ulNumberOfPoints,
							    unsigned long ulStartIndex,
							    unsigned char ucIsTimeAbsolute = 0,
								NC_MOTION_TABLE_TYPE_ENUM eTableType = eNC_TABLE_PVT_ARRAY) throw (CMMCException);


	unsigned int GetPVTTableIndex(MC_PATH_REF hMemHandle)  throw (CMMCException);
	unsigned int GetPTTableIndex(MC_PATH_REF hMemHandle)  throw (CMMCException)
	{
		return GetPVTTableIndex(hMemHandle);
	}

	/**
	* \fn int int GetTableList(NC_MOTION_TABLE_TYPE_ENUM eTableType, unsigned int (&uiHandlers)[MMC_MAX_JOURNAL_ENTRIES]);
	* \brief this function get a list of table for given table type.
	* \param  eTableType - type of tables to retrieve.
	* \param  uiHandlers - buffer of table handlers to retriev by eTableType.
	* \param  iNum - stores number of loaded tables of eTableType on successfull return.
	* \return	return - 0 if success otherwise error or thrown CMMCException.
	*/
	int GetTableList(NC_MOTION_TABLE_TYPE_ENUM eTableType, unsigned int (&uiHandlers)[MMC_MAX_JOURNAL_ENTRIES], int& iNum) throw (CMMCException);

	/**
	* \fn int GetTableInfo(unsigned int uiHandler, char (&name)[MMC_TABLE_FILE_LENGTH+1]) throw (CMMCException);
	* \brief this method gets the table name (by table handler).
	* \param  uiHandler - table's uiHandler to retrieve its name.
	* \param  name - name of given table by uiHandler.
	* \return	return - 0 if success otherwise error or thrown CMMCException.
	*/
	int GetTableInfo(unsigned int uiHandler, char (&name)[MMC_TABLE_FILE_LENGTH+1]) throw (CMMCException);

	void ReadGroupOfParameters(MMC_READGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],unsigned char ucNumberOfParameters, double* dbOutVal);
	void WriteGroupOfParametersImmediate(MMC_WRITEGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],unsigned char ucNumberOfParameters);
	void WriteGroupOfParametersQueued(MMC_WRITEGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],unsigned char ucNumberOfParameters);

	void WriteGroupOfParametersImmediateEX(MMC_WRITEGROUPOFPARAMETERSMEMBEREX sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],unsigned char ucNumberOfParameters);
	void WriteGroupOfParametersQueuedEX(MMC_WRITEGROUPOFPARAMETERSMEMBEREX sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],unsigned char ucNumberOfParameters);


private:

		/*! \fn void AppendPointsToTableCmn
	 * \brief This function appends points to an existing table
	 * \param CMMCAxis* - Pointer to axis
	 * \param cName - Axis name
	 * \param hConn - Connection handle
	 * \return void
	 */
	void AppendPVTPoints(MC_PATH_REF hMemHandle,
							    double (&dTable)[NC_PVT_ECAM_MAX_ARRAY_SIZE],
							    unsigned long ulNumberOfPoints,
							    unsigned long ulStartIndex,
							    unsigned char ucIsAutoAppend,
							    unsigned char ucIsTimeAbsolute,
								NC_MOTION_TABLE_TYPE_ENUM eTableType = eNC_TABLE_PVT_ARRAY) throw (CMMCException);

	void WriteGroupOfParameters(MC_EXECUTION_MODE eExecutionMode,MMC_WRITEGROUPOFPARAMETERSMEMBER sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],unsigned char ucNumberOfParameters);
	void WriteGroupOfParametersEX(MC_EXECUTION_MODE eExecutionMode,MMC_WRITEGROUPOFPARAMETERSMEMBEREX sParameters[GROUP_OF_PARAMETERS_MAXIMUM_SIZE],unsigned char ucNumberOfParameters);
};

#endif /// CMMCMOTIONAXIS_H_
