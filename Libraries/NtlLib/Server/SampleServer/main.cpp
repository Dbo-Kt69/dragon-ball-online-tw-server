// SampleServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "main.h"

#define SAMPLESERVER
//#define DBSAMPLESERVER


//-----------------------------------------------------------------------------------
//		���� ���� ����
//-----------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
#if defined( SAMPLESERVER )
	SampleServerMain(argc, argv);
#elif defined( DBSAMPLESERVER )
	DBSampleServerMain(argc, argv);
#endif

	return 0;
}
