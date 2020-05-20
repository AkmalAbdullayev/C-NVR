//#include <Windows.h>
//#include <conio.h>
//#include <stdio.h>
//#include "dhnetsdk.h"
//
//#pragma comment(lib, "dhnetsdk.lib")
//
//static LLONG g_ILoginHandle = 0L;
//static char g_szDevlp[32] = "192.168.1.108";
//static WORD g_nPort = 37777;
//static char g_szUserName[64] = "admin";
//static char g_szPasswd[64] = "admin123";
//static BOOL g_bSDKInitFlag = FALSE;
//
//void CALLBACK DisConnectFunc(LONG ILoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUSER) {
//	printf("Call DisConnectFunc\n");
//	printf("ILoginID[0x%x]", ILoginID);
//	if (NULL != pchDVRIP) {
//		printf("pchDVRIP[%s]\n", pchDVRIP);
//	}
//	printf("nDVRPort[%d]\n", nDVRPort);
//	printf("dwUser[%p]\n", dwUSER);
//	printf("\n");
//}
//
//void CALLBACK HaveReConnect(LLONG ILoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
//
//void InitTest() {
//	g_bSDKInitFlag = CLIENT_Init(DisConnectFunc, 0);
//	if (FALSE == g_bSDKInitFlag) {
//		printf("Initialize client SDK fail; \n");
//		return;
//	}
//	else {
//		printf("Initialize SDK done; \n");
//	}
//
//	DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
//	printf("NetSDK version is [%d]\n", dwNetSdkVersion);
//
//	CLIENT_SetAutoReconnect(&HaveReConnect, 0);
//
//	int nWaitTime = 5000;
//	int nTryTimes = 3;
//	CLIENT_SetConnectTime(nWaitTime, nTryTimes);
//
//	NET_PARAM stuNetParam = { 0 };
//	stuNetParam.nConnectTime = 3000;
//	CLIENT_SetNetworkParam(&stuNetParam);
//
//	CLIENT_SetNetworkParam(&stuNetParam);
//	NET_DEVICEINFO_Ex stDevInfoEx = { 0 };
//	int nError = 0;
//	while (0 == g_ILoginHandle) {
//		g_ILoginHandle = CLIENT_LoginEx2(g_szDevlp, g_nPort, g_szUserName, g_szPasswd, EM_LOGIN_SPEC_CAP_TCP, NULL, &stDevInfoEx, &nError);
//
//		if (0 == g_ILoginHandle) {
//			printf("CLIENT_LoginEX2 %s[%d] Failed! Last Error[%x]\n", g_szDevlp, g_nPort, CLIENT_GetLastError());
//		}
//		else {
//			printf("CLIENT_LoginEx2 %s[Port Number : %d] Success\n", g_szDevlp, g_nPort);
//		}
//
//		Sleep(1000);
//		printf("\n");
//	}
//}
//
//void EndTest() {
//	if (0 == g_ILoginHandle) {
//		if (FALSE == CLIENT_Logout(g_ILoginHandle)) {
//			printf("CLIENT_Logout Failed! Last Error[%x]\n", CLIENT_GetLastError());
//		}
//		else {
//			printf("CLIENT_Logout Success");
//			g_ILoginHandle = 0;
//		}
//	}
//
//	if (TRUE == g_bSDKInitFlag) {
//		CLIENT_Cleanup();
//		g_bSDKInitFlag = FALSE;
//	}
//
//	printf("input any key to quit!\n");
//	getchar();
//	return;
//}
//
//int main() {
//	InitTest();
//	EndTest();
//}
//
//void CALLBACK HaveReConnect(LLONG ILoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser) {
//	printf("ILoginID[0x%x]", ILoginID);
//	printf("Call HaveReConnect\n");
//	if (NULL != pchDVRIP) {
//		printf("pchDVRIP[%s]\n", pchDVRIP);
//	}
//	printf("nDVRPort[%d]\n", nDVRPort);
//	printf("dwUser[%p]\n", dwUser);
//	printf("\n");
//}