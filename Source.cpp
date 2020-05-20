//#include <windows.h>
//#include <stdio.h>
//#include "dhnetsdk.h"
//using namespace std;
//
//#pragma comment(lib, "dhnetsdk.lib")
//
//static BOOL g_bNetSDKInitFlag = FALSE;
//
//void CALLBACK DisConnectFunc(LLONG ILoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser);
//
//void CALLBACK HaveReConnect(LLONG lloginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
//
//void InitTest() {
//	g_bNetSDKInitFlag = CLIENT_Init(DisConnectFunc, 0);
//	if (FALSE == g_bNetSDKInitFlag) {
//		printf("initialize client sdk fail; \n");
//		return;
//	}
//	else {
//		printf("initialize client sdk done; \n");
//	}
//
//	DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
//	printf("NETSDKVERSION[%d]", dwNetSdkVersion);
//
//	CLIENT_SetAutoReconnect(&HaveReConnect, 0);
//
//	int nWaitTime = 5000;
//	int nTryTimes = 3;
//	CLIENT_SetConnectTime(nWaitTime, nTryTimes);
//
//	NET_PARAM stuNetParm = { 0 };
//	stuNetParm.nConnectTime = 3000;
//	CLIENT_SetNetworkParam(&stuNetParm);
//
//	Sleep(1000);
//	printf("\n");
//}
//
//void RunTest() {
//	if (FALSE == g_bNetSDKInitFlag) {
//		return;
//	}
//}
//
//void EndTest() {
//	printf("input any key to quit!\n");
//	getchar();
//
//	if (TRUE == g_bNetSDKInitFlag) {
//		CLIENT_Cleanup();
//		g_bNetSDKInitFlag;
//	}
//	return;
//}
//
//int main() {
//	InitTest();
//	RunTest();
//	EndTest();
//	return 0;
//}
//
//void CALLBACK HaveReConnect(LLONG lloginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser) {
//	printf("Call DisConnectFunc\n");
//	printf("ILoginID[0x%x]", lloginID);
//	if (NULL != pchDVRIP) {
//		printf("pchDVRIP[%s]\n", pchDVRIP);
//	}
//	printf("nDVRPort[%d]\n", nDVRPort);
//	printf("dwUser[%p]\n", dwUser);
//	printf("\n");
//}
//
//void CALLBACK DisConnectFunc(LONG ILoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUser) {
//	printf("ILoginID[0x%x]", ILoginID);
//	printf("Call HaveReConnect\n");
//	if (NULL != pchDVRIP) {
//		printf("pchDVRIP[%s]\n", pchDVRIP);
//	}
//	printf("nDVRPort[%d]\n", nDVRPort);
//	printf("dwUser[%p]\n", dwUser);
//	printf("\n");
//}