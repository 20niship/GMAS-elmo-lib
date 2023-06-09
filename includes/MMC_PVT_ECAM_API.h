////////////////////////////////////////////////////////////////////////////////
/// \file MMC_PVT_API.h
/// Name        : MMC_PVT_API.h
/// Author      : Alex
/// Created on	: April 07, 2012
/// Version     : 0.0.1
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_PVT_API_H_
#define MMC_PVT_API_H_

#ifdef __cplusplus
 extern "C" {
#endif

#define NC_PVT_ECAM_MAX_ARRAY_SIZE               170

typedef enum
 {
 	eNC_TABLE_NONE,
 	eNC_TABLE_SPLINE,
	eNC_TABLE_PVT_FILE,								//old method eCUBIC_POLYNOM
	eNC_TABLE_PVT_ARRAY,							//old method eCUBIC_POLYNOM
	eNC_TABLE_PVT_FILE_QUINTIC_CUB,	//new method eQUINTIC_ON_CUBIC
	eNC_TABLE_PVT_ARRAY_QUINTIC_CUB,//new method eQUINTIC_ON_CUBIC
 	eNC_TABLE_ECAM_FILE,
 	eNC_TABLE_ECAM_ARRAY,
	eNC_TABLE_OLSPLN_FILE,
	eNC_TABLE_OLSPLN_ARRAY,
 	eNC_TABLE_MAX
} NC_MOTION_TABLE_TYPE_ENUM;

typedef enum
{
	MC_NONE_ONLINE_SPLINE_MODE = 0,
	MC_QUINTIC_ON_PARAB_FT_DWELL,	//fixed time
	MC_QUINTIC_ON_PARAB_VT_DWELL,	//variable time
    MC_QUINTIC_ON_PARAB_CV_DWELL,	//constant velocity
} NC_ONLINE_SPLINE_MODE_ENUM;


typedef struct mmc_inittable_in
{
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	NC_MOTION_TABLE_TYPE_ENUM eTableType;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	unsigned long ulMaxNumberOfPoints;
	unsigned long ulUnderflowThreshold;
	unsigned short usAxisRef;
	unsigned short usDimension;
	unsigned char ucIsDynamicMode;
	unsigned char ucIsPosAbsolute;
	unsigned char ucIsCyclic;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
} MMC_INITTABLE_IN;

typedef struct mmc_inittable_out
{
	MC_PATH_REF hMemHandle;
	unsigned short usStatus;
	short usErrorID;
} MMC_INITTABLE_OUT;

typedef struct mmc_inittableex_in
{
	double dbConstVelocity;
	double dbConstTime;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	NC_MOTION_TABLE_TYPE_ENUM eTableType;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_ONLINE_SPLINE_MODE_ENUM eSplineMode;
	unsigned long ulMaxNumberOfPoints;
	unsigned long ulUnderflowThreshold;
	unsigned short usAxisRef;
	unsigned short usDimension;
	unsigned char ucIsDynamicMode;
	unsigned char ucIsPosAbsolute;
	unsigned char ucIsCyclic;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
	unsigned char ucSpare[35];
} MMC_INITTABLEEX_IN;

typedef struct mmc_inittableex_out
{
	MC_PATH_REF hMemHandle;
	unsigned short usStatus;
	short usErrorID;
} MMC_INITTABLEEX_OUT;



typedef struct mmc_loadtablefromfile_in
{
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	NC_MOTION_TABLE_TYPE_ENUM eTableType;
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	unsigned short usAxisRef;
	MC_PATH_DATA_REF pPathToTableFile;
} MMC_LOADTABLEFROMFILE_IN;

/*
 * eUserDefInterp means one of the types in this list (besides eUserDefInterp)
 * from CAM table. default is eQuintic.
 */
//typedef enum {eUserDefInterp=0, eQuinticInterp, eLinearInterp, eCycloidVelocityInterp, eCycloidPositionInterp, eSepticInterp, eSinusoidalTrapezAC} CURVE_TYPE_ENUM;
typedef enum {
  eTableDefInterp = 0, 
  eLinearInterp = 1, 
  ePolynom5Interp = 2, 
  ePolynom7Interp = 3, 
  eCycloidPositionInterp = 4, 
  eCycloidVelocityModified1Interp = 5, 
  eCycloidVelocityModified2Interp = 6, 
} CURVE_TYPE_ENUM;
typedef enum {eCAMT_RWMode=0, eCAMT_ROMode} CAM_TABLE_MODE_ENUM; //if eCAMT_ROMode, 'on the fly' changes are forbidden.

typedef struct _mmc_camtable_ref
{
	double dbGap;					//relevant only if gap is fixed
	double dbMasterStartPosition;	//master position in CAM table first entry.
									//must be specified in case of fixed gap (no master column) and master position is absolute.
	MC_COORD_SYSTEM_ENUM eCoordSystem;	//currently irrelevant because group is not supported.
	int iCamTableID;				//<0 means load new table from file. otherwise it is an handle of existing table,
									//which was either retrieved by mmc_camtableinitcmd or previous call to mmc_camtableselect.
	CAM_TABLE_MODE_ENUM eTableMode;	//modifiable table or not.
	MC_PATH_DATA_REF pPathToTableFile;
	unsigned char ucSpare[32];		//spare for future use
} MC_CamRef;

typedef struct _mmc_camtableselect_in
{
	MC_CamRef CamTable;
	unsigned int uiStartMode;			//reserved for future use of Ramp-In and other options.
	unsigned char ucIsMasterPosAbsolute;//master position relative(0) or absolute(1)
	unsigned char ucIsSlavePosAbsolute; //slave position relative(0) or absolute(1)
	unsigned char ucSpare[32];			//8 longs spare
} MMC_CAMTABLESELECT_IN;

typedef struct _mmc_camtableselect_out
{
	MC_PATH_REF hMemHandle;
	unsigned short usStatus;
	unsigned short usErrorID;
} MMC_CAMTABLESELECT_OUT;

#ifdef WIN32
#define NC_ALIGNMENT __declspec(align(8)) //double alignmment
#else
#define NC_ALIGNMENT __attribute__((aligned(8)))
#endif
#define NC_ECAM_MAX_ARRAY_SIZE 164
/*
typedef NC_ALIGNMENT struct _mc_motion_func {
	unsigned short _usCurveType; //!< interpolation type. only Quintic at this phase. 
	unsigned char ucSpare[32];
} MMC_CAM_MOTION_FUNC;
*/
#ifdef WIN32
typedef NC_ALIGNMENT struct _mmc_camtableset_in
{
	double dbTable[NC_ECAM_MAX_ARRAY_SIZE]; //164 + 6 = 170 doubles max size
	unsigned long ulStartIndex;
	unsigned long ulNumberOfPoints;
	MC_PATH_REF hMemHandle;
	unsigned char ucSpare[32];			//8 longs spare
} MMC_CAMTABLESET_IN;
#else
typedef  struct _mmc_camtableset_in
{
	double dbTable[NC_ECAM_MAX_ARRAY_SIZE]; //164 + 6 = 170 doubles max size
	unsigned long ulStartIndex;
	unsigned long ulNumberOfPoints;
	MC_PATH_REF hMemHandle;
	unsigned char ucSpare[32];			//8 longs spare
} NC_ALIGNMENT MMC_CAMTABLESET_IN;
#endif


typedef struct _mmc_camtableset_out
{
	unsigned short usStatus;
	unsigned short usErrorID;
} MMC_CAMTABLESET_OUT;

typedef enum {
	eECAM_SET_VALUE = 0,
	eECAM_ACTUAL_VALUE,
	eECAM_AUX_VALUE,
} ECAM_VALUE_SRC_ENUM;
typedef enum {eCAM_NON_PERIODIC, eCAM_PERIODIC,  eCAM_LINEAR} ECAM_PERIODIC_ENUM;

typedef struct _mmc_camtableinit_in
{
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned long ulMaxNumberOfPoints;
	unsigned long ulUnderflowThreshold;
	CURVE_TYPE_ENUM eCurveType;			//interpolation type. currently only Quitic (Poly-5) is supported
	unsigned short usDimension;
	unsigned char ucSuperimposed;
	unsigned char ucIsFixedGap;			//mandatory factor here for memory allocation
	unsigned char ucExecute;
	unsigned char ucSpare[32];			//spare for future use
} MMC_CAMTABLEINIT_IN;

typedef struct _mmc_camin_in
{
	double dbMasterOffset;
	double dbSlaveOffset;
	double dbMasterScaling;
	double dbSlaveScaling;
	double dbMasterStartDistance;
	double dbMasterSyncPosition;
	ECAM_VALUE_SRC_ENUM eMasterValueSource;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned int uiStartMode;	/**< reserved for future use of Ramp-In and other options			*/
	CURVE_TYPE_ENUM eCurveType;	/**< Interpolation type. currently only Quitic (Poly-5) is supported*/
	ECAM_PERIODIC_ENUM ePeriodicMode;
	unsigned int uiCamTableID;
	unsigned short usMaster;
	unsigned char ucAutoOffset;	/**< false for user defined offsets, true for Auto offset.			*/
	 	 	 	 	 	 	 	/**< Auto mode makes sure the CAM process avoid any jump			*/
	unsigned char ucExecute	;
	unsigned char ucSpare[32]; //spare for future use
} MMC_CAMIN_IN;

typedef struct _mmc_camin_out
{
	unsigned int   uiHandle;
	unsigned int   uiEndOfProfile;//count variable increases each time the master meets the end of the table
	unsigned short usStatus;
	short sErrorID;
} MMC_CAMIN_OUT;

typedef struct _mmc_camout_in
{
	unsigned char ucExecute	;
} MMC_CAMOUT_IN;

typedef struct _mmc_camout_out
{
	unsigned int   uiHandle;
	unsigned short usStatus;
	short sErrorID;
} MMC_CAMOUT_OUT;

typedef struct _mmc_camstatus_in
{
	unsigned char ucDummy;
} MMC_CAMSTATUS_IN;

typedef struct _mmc_camstatus_out
{
	unsigned long ulEndOfProfile;	//counts number of exists from cam table
	unsigned long ulCurrentIndex;
	unsigned long ulCycle;
	unsigned short usStatus;
	short sErrorID;
	unsigned int uiCamTableID;
	//unsigned char ucSpare[32]; //spare for future use
	unsigned char ucSpare[28]; //spare for future use
} MMC_CAMSTATUS_OUT;


#define ECAM_STARTMODE_BASE			0x00000000
#define ECAM_STARTMODE_RISING_EDGE	0x00000001

typedef enum _ecam_properties {eCAM_PeriodicMode} ECAM_PROPERTIES_ENUM;

typedef union {
	double dbVal;
	ECAM_PERIODIC_ENUM ePeriodicMode;
	CURVE_TYPE_ENUM	eCurveType;
	int iVal;
	float fVal;
	short sVal;
	char cVal;
} ECAM_PROPERTY_VALUE;

typedef struct _mmc_camsetprop_in
{
	ECAM_PROPERTIES_ENUM eProperty;
	ECAM_PROPERTY_VALUE value;
	unsigned char ucExecute	;
	unsigned char ucSpare[32]; /**< spare for future use											*/
} MMC_CAMSETPROP_IN;

typedef struct _mmc_camsetprop_out
{
	unsigned short usStatus;
	short sErrorID;
} MMC_CAMSETPROP_OUT;

typedef enum {
	eCATCH_UP = 0,
	eSLOW_DOWN = 1,
} GEAR_IN_SYNC_MODE_ENUM;


typedef struct _mmc_gearin_in
{
	unsigned short usMaster;					//axis reference of master
	int iRatioNumerator;						//gear ratio Numerator
	int iRatioDenominator;						//gear ratio Denominator
	ECAM_VALUE_SRC_ENUM eMasterValueSource;		//defines the source for synchronization:
												//mcSetValue - Synchronization on master set value
												//mcActualValue - Synchronization on master actual value
	GEAR_IN_SYNC_MODE_ENUM eSyncMode;			//eCATCH_UP(0), eSLOW_DOWN(1)
	double dbAcceleration;						//acceleration for gearing in
	double dbDeceleration;						//deceleration for gearing in
	double dbJerk;								//jerk of Gearing
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute	;					//start the gearing process at the rising edge.
	unsigned char ucSpare[32];					//spare for future use.
} MMC_GEARIN_IN;

typedef struct _mmc_gearinpos_in
{
	unsigned short usMaster;					//axis reference of master
	double dbMasterStartDistance;				//master distance for gear in procedure (distance for ramp-in)
												//(when the slave axis is started to get into synchronization)
	double dbMasterSyncPosition;				//position of the master in which the slave is in-sync with the master.
	double dbSlaveSyncPosition;					//slave position at which the axes are running in sync
	int iRatioNumerator;						//gear ratio Numerator
	int iRatioDenominator;						//gear ratio Denominator
	ECAM_VALUE_SRC_ENUM eMasterValueSource;		//defines the source for synchronization:
												//mcSetValue - Synchronization on master set value
												//mcActualValue - Synchronization on master actual value
	GEAR_IN_SYNC_MODE_ENUM eSyncMode;			//eCATCH_UP(0), eSLOW_DOWN(1)
	double dbVelocity;
	double dbAcceleration;						//acceleration for gearing in
	double dbDeceleration;						//deceleration for gearing in
	double dbJerk;								//jerk of Gearing
	
	MC_BUFFERED_MODE_ENUM eBufferMode;
	unsigned char ucExecute	;					//start the gearing process at the rising edge
	unsigned char ucSpare[32]; 					//spare for future use
} MMC_GEARINPOS_IN;

typedef struct _mmc_gearin_out
{
	unsigned int   uiHandle;
	unsigned short usStatus;
	short sErrorID;
} MMC_GEARIN_OUT;

typedef struct _mmc_gearinpos_out
{
	unsigned int   uiHandle;
	unsigned short usStatus;
	short sErrorID;
} MMC_GEARINPOS_OUT;


typedef struct _mmc_gearout_in
{
	unsigned char ucExecute	;					//start the disengaging process at the rising edge
} MMC_GEAROUT_IN;

typedef struct _mmc_gearout_out
{
	unsigned int   uiHandle;
	unsigned short usStatus;
	short sErrorID;
} MMC_GEAROUT_OUT;


typedef MMC_PATHSELECT_OUT MMC_LOADTABLE_OUT;

typedef struct mmc_appendpointstotable_in
{
	double dTable[NC_PVT_ECAM_MAX_ARRAY_SIZE];
	NC_MOTION_TABLE_TYPE_ENUM eTableType;
	MC_PATH_REF hMemHandle;
	unsigned long ulStartIndex;
	unsigned long ulNumberOfPoints;
	unsigned short usAxisRef;
	unsigned char ucIsTimeAbsolute;
	unsigned char ucIsAutoAppend;
} MMC_APPENDPOINTSTOTABLE_IN;

typedef struct mmc_appendpointstotable_out
{
	unsigned short usStatus;
	short usErrorID;
} MMC_APPENDPOINTSTOTABLE_OUT;

typedef struct mmc_gettableindex_in
{
	MC_PATH_REF hMemHandle;
} MMC_GETTABLEINDEX_IN;

typedef struct mmc_gettableindex_out
{
	unsigned long ulCurrentIndex;
	unsigned short usStatus;
	short usErrorID;
} MMC_GETTABLEINDEX_OUT;

typedef MMC_MOVEPATH_IN MMC_MOVETABLE_IN;
typedef MMC_MOVEPATH_OUT MMC_MOVETABLE_OUT;
typedef MMC_PATHUNSELECT_IN MMC_UNLOADTABLE_IN;
typedef MMC_PATHUNSELECT_OUT MMC_UNLOADTABLE_OUT;

MMC_LIB_API int MMC_InitTableCmd(MMC_CONNECT_HNDL hConn,
				  	  	  	  	 MMC_INITTABLE_IN* pInParam,
				  	  	  	  	 MMC_INITTABLE_OUT* pOutParam);

MMC_LIB_API int MMC_InitTableExCmd(MMC_CONNECT_HNDL hConn,
								 MMC_INITTABLEEX_IN* pInParam,
				  	  	  	  	 MMC_INITTABLEEX_OUT* pOutParam);

MMC_LIB_API int MMC_LoadTableFromFileCmd(MMC_CONNECT_HNDL hConn,
								   	   	 MMC_LOADTABLEFROMFILE_IN* pInParam,
								   	   	 MMC_LOADTABLE_OUT* pOutParam);

MMC_LIB_API int MMC_CamTableInitCmd(MMC_CONNECT_HNDL hConn,
				  	  	  	  	 MMC_CAMTABLEINIT_IN* pInParam,
				  	  	  	  	 MMC_INITTABLE_OUT* pOutParam);
MMC_LIB_API int MMC_CamTableSelectCmd(IN MMC_CONNECT_HNDL hConn,
								IN MMC_CAMTABLESELECT_IN* pInParam,
								OUT MMC_CAMTABLESELECT_OUT* pOutParam);
MMC_LIB_API int MMC_CamTableAddCmd(MMC_CONNECT_HNDL hConn,
			     	 	 	 	   MMC_CAMTABLESET_IN* pInParam,
			     	 	 	 	   MMC_CAMTABLESET_OUT* pOutParam);
MMC_LIB_API int MMC_CamTableSetCmd(MMC_CONNECT_HNDL hConn,
			     	 	 	 	   MMC_CAMTABLESET_IN* pInParam,
			     	 	 	 	   MMC_CAMTABLESET_OUT* pOutParam);
MMC_LIB_API int MMC_CamInCmd(IN MMC_CONNECT_HNDL hConn,
								 IN MMC_AXIS_REF_HNDL hAxisRef,
								 IN MMC_CAMIN_IN* pInParam,
								 OUT MMC_CAMIN_OUT* pOutParam);
MMC_LIB_API int MMC_CamOutCmd(IN MMC_CONNECT_HNDL hConn,
								 IN MMC_AXIS_REF_HNDL hAxisRef,
								 IN MMC_CAMOUT_IN* pInParam,
								 OUT MMC_CAMOUT_OUT* pOutParam);
MMC_LIB_API int MMC_CamStatusCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CAMSTATUS_IN* pInParam,
		OUT MMC_CAMSTATUS_OUT* pOutParam);

MMC_LIB_API int MMC_CamSetPropertyCmd(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_CAMSETPROP_IN* pInParam,
		OUT MMC_CAMSETPROP_OUT* pOutParam);
MMC_LIB_API int MMC_AppendPointsToTableCmd(MMC_CONNECT_HNDL hConn,
			     	 	 	 	 	       MMC_APPENDPOINTSTOTABLE_IN* pInParam,
			     	 	 	 	 	       MMC_APPENDPOINTSTOTABLE_OUT* pOutParam);

MMC_LIB_API int MMC_GetTableIndexCmd(MMC_CONNECT_HNDL hConn,
				 	 	 	 	   	 MMC_GETTABLEINDEX_IN* pInParam,
				 	 	 	 	   	 MMC_GETTABLEINDEX_OUT* pOutParam);

MMC_LIB_API int MMC_MoveTableCmd(MMC_CONNECT_HNDL hConn,
				   		   	     MMC_AXIS_REF_HNDL hAxisRef,
				   		   	     MMC_MOVETABLE_IN* pInParam,
				   		   	     MMC_MOVETABLE_OUT* pOutParam);

MMC_LIB_API int MMC_UnloadTableCmd(MMC_CONNECT_HNDL hConn,
								   MMC_UNLOADTABLE_IN* pInParam,
								   MMC_UNLOADTABLE_OUT* pOutParam);

/**
 * \fn	void mmc_gearin(void *arg)
 * \brief commands a ratio between the VELOCITY of the slave and master axis.
 * \param hConn		connection handler by which the mmc library communicate with MultiAxisControl.
 * \param hAxisRef	axis reference.
 * \param pInParam	buffer to store input arguments.
 * \param pOutParam buffer to store output arguments.
 * \return none. results returned within arg buffer.
 */
MMC_LIB_API int MMC_GearInCmd(IN MMC_CONNECT_HNDL hConn,
								 IN MMC_AXIS_REF_HNDL hAxisRef,
								 IN MMC_GEARIN_IN* pInParam,
								 OUT MMC_GEARIN_OUT* pOutParam);
/**
 * \fn	void mmc_gearinpos(void *arg)
 * \brief commands a gear ratio between the position of the slave and master axes from the synchronization point onwards
 * \param hConn		connection handler by which the mmc library communicate with MultiAxisControl.
 * \param hAxisRef	axis reference.
 * \param pInParam	buffer to store input arguments.
 * \param pOutParam buffer to store output arguments.
 * \return none. results returned within arg buffer.
 */
MMC_LIB_API int MMC_GearInPosCmd(IN MMC_CONNECT_HNDL hConn,
								 IN MMC_AXIS_REF_HNDL hAxisRef,
								 IN MMC_GEARINPOS_IN* pInParam,
								 OUT MMC_GEARINPOS_OUT* pOutParam);
/**
 * \fn	void MMC_GearOutCmd(void *arg)
 * \brief disengage a gear between slave and master axes. actually MC_Stop at this stage. 
 * \param hConn		connection handler by which the mmc library communicate with MultiAxisControl.
 * \param hAxisRef	axis reference.
 * \param pInParam	buffer to store input arguments.
 * \param pOutParam buffer to store output arguments.
 * \return none. results returned within arg buffer.
 */
MMC_LIB_API int MMC_GearOutCmd(IN MMC_CONNECT_HNDL hConn,
								 IN MMC_AXIS_REF_HNDL hAxisRef,
								 IN MMC_GEAROUT_IN* pInParam,
								 OUT MMC_GEAROUT_OUT* pOutParam);		 


/*--------------------------------------
*	table info API
*/
#define MMC_MAX_JOURNAL_ENTRIES	20
#define MMC_TABLE_FILE_LENGTH	20	//max length for table file name (exluded from path)


typedef struct o_table_list {
	unsigned int _uiHandlers[MMC_MAX_JOURNAL_ENTRIES];	//list of table handlers
	int _iNumber;										//number of found tables
	unsigned short usStatus;
	short	sErrorID;
} MMC_TABLE_LIST_OUT;
typedef struct i_table_list {
	NC_MOTION_TABLE_TYPE_ENUM eTableType;
} MMC_TABLE_LIST_IN;

typedef struct o_table_data {
	char _name[MMC_TABLE_FILE_LENGTH+1];
	unsigned short usStatus;
	short	sErrorID;
} MMC_TABLE_DATA_OUT;

typedef struct i_table_list_data {
	unsigned int uiHandler;
} MMC_TABLE_DATA_IN;

/**
* \fn int MMC_GetTableList(
*				IN MMC_CONNECT_HNDL hConn,
*				IN MMC_TABLE_LIST_IN* pInParam,
*				OUT MMC_TABLE_LIST_OUT* pOutParam)
* \brief this function get a list of table for given table type.
* \param  hConn - 	 [IN] connection handle
* \param  hAxisRef - [IN] axis reference handle
* \param  pInParam - [IN] input parameters.
* \param  pOutParam - [OUT] output parameters.
* \return	return - 0 if success otherwise error.
*/
MMC_LIB_API int MMC_GetTableList(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_TABLE_LIST_IN* pInParam,
		OUT MMC_TABLE_LIST_OUT* pOutParam);

/**
* \fn int MMC_GetTableInfo(
*				IN MMC_CONNECT_HNDL hConn,
*				IN MMC_AXIS_REF_HNDL hAxisRef,
*				IN MMC_TABLE_DATA_IN* pInParam,
*				OUT MMC_TABLE_DATA_OUT* pOutParam)
* \brief this function get table info (currently name only) for given table handler.
* \param  hConn - 	 [IN] connection handle
* \param  pInParam - [IN] input parameters.
* \param  pOutParam - [OUT] output parameters.
* \return	return - 0 if success otherwise error.
*/
MMC_LIB_API int MMC_GetTableInfo(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_TABLE_DATA_IN* pInParam,
		OUT MMC_TABLE_DATA_OUT* pOutParam);

#ifdef __cplusplus
}
#endif

#endif /* MMC_PVT_API_H_ */
