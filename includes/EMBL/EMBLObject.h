/*
 * EMBLObject.h
 *
 *  Created on: Jan 27, 2015
 *      Author: yuvall
 */

#ifndef EMBLObject_H_
#define EMBLObject_H_


#ifdef __cplusplus
/*
 *
 */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

//typedef struct
//{
//	unsigned int   uiHndl;		///< Returned function block handle.
//	unsigned short usStatus;	///< Returned command status.
//	short usErrorID;	///< Returned command error ID.
//}EMBL_FB_OBJECT_OUT;


#define TRUE 1
#define FALSE 0
class EMBLObject {
public:
	virtual ~EMBLObject();

public:
	virtual int Init(void * pData) = 0;
	virtual int Perform(void * pData) = 0;
	virtual int PostPerform(void * pData) = 0;

	inline unsigned short GetStatus() {return _usStatus;}
	inline unsigned short GetAxisRef() {return m_usAxisRef;}
	inline void SetStatus(unsigned short usStatus) {_usStatus = usStatus;}
	inline void SetErrorID(short ErrorID) {_sErrorID = ErrorID;}
	inline  short GetErrorID() {return _sErrorID;}
protected:
	/**
	 * protected constructor
	 * makes sure user program cannot declare this base class as stand alone object
	 */
	EMBLObject();

	int 			m_iState;
	unsigned int 	m_uiHandle;
	unsigned short	m_usAxisRef;
	unsigned int	m_uiConn;

private:
	unsigned short _usStatus;
	short _sErrorID;
};
#endif


#endif /* EMBLObject_H_ */
