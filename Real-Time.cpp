#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <memory>
#include <vector>
#include "dhnetsdk.h"
#include "dhconfigsdk.h"
#include "avglobal.h"
using namespace std;

#pragma comment(lib, "dhnetsdk.lib")
#pragma comment(lib, "dhconfigsdk.lib")

typedef HWND(WINAPI *PROCGETCONSOLEWINDOW)();
PROCGETCONSOLEWINDOW _GetConsoleWindow;

static LLONG g_ILoginHandle = 0L;
static LLONG g_IRealHandle = 0L;
static BOOL save_handle = FALSE;
static char g_szDevlp[32] = "192.168.1.108";
static WORD g_nPort = 37777;
static char g_szUserName[64] = "admin";
static char g_szPasswd[64] = "admin123";
static BOOL g_bSDKInitFlag = FALSE;
static LLONG m_FindHandle = NULL;
static int nToken = 0;


static bool addGroup();
static bool addPerson();
static bool downloadPersonPic();
static int StartFindPerson();
static CANDIDATE_INFO doFindPerson();

int GetIntInput(char *szPromt, int &nError);

void GetStringInput(const char *szPromt, char *szBuffer);

void CALLBACK DownLoadPosCallBack(LLONG IPlayHandle, DWORD dwTotalSize, DWORD dwDownloadSize, LDWORD dwUser);

int CALLBACK DataCallBack(LLONG IRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);

void CALLBACK DisConnectFunc(LONG ILoginID, char *pchDVRIP, LONG nDVRPort, DWORD dwUSER) {
	printf("Call DisConnectFunc\n");
	printf("ILoginID[0x%x]", ILoginID);
	if (NULL != pchDVRIP) {
		printf("pchDVRIP[%s]\n", pchDVRIP);
	}
	printf("nDVRPort[%d]\n", nDVRPort);
	printf("dwUser[%p]\n", dwUSER);
	printf("\n");
}

void CALLBACK HaveReConnect(LLONG ILoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

void InitTest() {
	g_bSDKInitFlag = CLIENT_Init(DisConnectFunc, 0);
	if (FALSE == g_bSDKInitFlag) {
		printf("Initialize client SDK fail; \n");
		return;
	}
	else {
		printf("Initialize SDK done; \n");
	}

	DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
	printf("NetSDK version is [%d]\n", dwNetSdkVersion);

	CLIENT_SetAutoReconnect(&HaveReConnect, 0);

	int nWaitTime = 5000;
	int nTryTimes = 3;
	CLIENT_SetConnectTime(nWaitTime, nTryTimes);

	NET_PARAM stuNetParam = { 0 };
	stuNetParam.nConnectTime = 3000;
	// For Snapshot
	stuNetParam.nPicBufSize = 4 * 1024 * 1024;
	CLIENT_SetNetworkParam(&stuNetParam);

	CLIENT_SetNetworkParam(&stuNetParam);

	NET_DEVICEINFO_Ex stDevInfoEx = { 0 };
	int nError = 0;
	while (0 == g_ILoginHandle) {
		g_ILoginHandle = CLIENT_LoginEx2(g_szDevlp, g_nPort, g_szUserName, g_szPasswd, EM_LOGIN_SPEC_CAP_TCP, NULL, &stDevInfoEx, &nError);

		if (0 == g_ILoginHandle) {
			printf("CLIENT_LoginEX2 %s[%d] Failed! Last Error[%x]\n", g_szDevlp, g_nPort, CLIENT_GetLastError());
		}
		else {
			printf("CLIENT_LoginEx2 %s[Port Number : %d] Success\n", g_szDevlp, g_nPort);
		}

		Sleep(1000);
		printf("\n");
	}
}

void RunTest() {
	if (FALSE == g_bSDKInitFlag) {
		return;
	}
	if (0 == g_ILoginHandle) {
		return;
	}

	HMODULE hKernel32 = GetModuleHandle("kernel32");
	_GetConsoleWindow = (PROCGETCONSOLEWINDOW)GetProcAddress(hKernel32, "GetConsoleWindow");
	HWND hWnd = GetConsoleWindow();

	printf("user can input any key to quit during real play!\n");
	Sleep(1000);

	int nChannelID = 0;
	DH_RealPlayType emRealPlayType = DH_RType_Multiplay_1;
	g_IRealHandle = CLIENT_RealPlayEx(g_ILoginHandle, nChannelID, hWnd, emRealPlayType);
	if (0 == g_IRealHandle) {
		printf("CLIENT_RealPlayEx : failed! Error code : %x\n", CLIENT_GetLastError());
	}
	//addGroup();
	//addPerson();
	//downloadPersonPic();
	//StartFindPerson();
	doFindPerson();

	// Face Recognition
	//NET_IN_OPERATE_FACERECONGNITIONDB netInOperate = { sizeof(netInOperate) };
	//NET_OUT_OPERATE_FACERECONGNITIONDB netOutOperate = { sizeof(netOutOperate) };
	//FACERECOGNITION_PERSON_INFO personInfo = { 0 };

	//int bufferLength = 2048;
	//char *pBuffer = new char[bufferLength];
	//memset(pBuffer, 0, bufferLength);

	////****************** Personal Information ******************//
	//personInfo.szPersonName[DH_MAX_PERSON_NAME_LEN] = { 0 };
	//personInfo.wYear = 0;
	//personInfo.byMonth = 0;
	//personInfo.byDay = 0;
	//personInfo.szID[DH_MAX_PERSON_ID_LEN] = '007';
	//personInfo.bImportantRank = 5;
	//personInfo.bySex = 1;
	//personInfo.wFacePicNum = '1';
	//personInfo.bReserved1[2];
	//personInfo.bReserved[60];
	////**********************************************************

	//netInOperate.dwSize = sizeof(NET_IN_OPERATE_FACERECONGNITIONDB);
	//netInOperate.emOperateType = NET_FACERECONGNITIONDB_ADD;
	//netInOperate.stPersonInfo = personInfo;
	//netInOperate.pBuffer = &(*pBuffer);
	//netInOperate.nBufferLen = bufferLength;

	//netOutOperate.dwSize = sizeof(NET_OUT_OPERATE_FACERECONGNITIONDB);
	//operation : BOOL operation = CLIENT_OperateFaceRecognitionDB(g_ILoginHandle, &netInOperate, &netOutOperate, 5000);
	//cout << operation << endl;

	//if (FALSE == operation) {
	//	cout << "Error : " << CLIENT_GetLastError() << endl;
	//}
	// End Face Recognition

	//FACERECOGNITION_PERSON_INFO personInfo = { 0 };
	/*personInfo.wYear = 1999;
	personInfo.byMonth = 12;
	personInfo.byDay = 15;*/
	/*personInfo.szID[DH_MAX_PERSON_ID_LEN] = '007';
	personInfo.bImportantRank = 5;*/
	//personInfo.bySex = 1;
	//personInfo.wFacePicNum = '1';
	/*personInfo.bReserved1[2];
	personInfo.bReserved[60];*/

	/*NET_IN_STARTFIND_FACERECONGNITION pstInParam;
	NET_OUT_STARTFIND_FACERECONGNITION pstOutParam;
	pstOutParam.dwSize = sizeof(NET_OUT_STARTFIND_FACERECONGNITION);
	pstOutParam.nTotalCount = 2;
	pstInParam.dwSize = sizeof(NET_IN_STARTFIND_FACERECONGNITION);
	pstInParam.bPersonEnable = true;
	pstInParam.stPerson = personInfo;
	BOOL findFace = CLIENT_StartFindFaceRecognition(g_ILoginHandle, &pstInParam, &pstOutParam, 2000);
	cout << findFace << endl;*/

	// Video Snapshot
	/*NET_IN_SNAP_PIC_TO_FILE_PARAM stuInParam = { sizeof(stuInParam) };
	NET_OUT_SNAP_PIC_TO_FILE_PARAM stuOutParam = { sizeof(stuOutParam) };
	SNAP_PARAMS stuSnapParams = { 0 };
	stuSnapParams.Channel = 0;
	int nBufferLen = 2 * 1024 * 1024;
	char *pBuffer = new char[nBufferLen];
	memset(pBuffer, 0, nBufferLen);
	stuOutParam.szPicBuf = pBuffer;
	stuOutParam.dwPicBufLen = nBufferLen;
	if (FALSE == CLIENT_SnapPictureToFile(g_ILoginHandle, &stuInParam, &stuOutParam, 5000)) {
	cout << "CLIENT_SnapPictureEx Failed! Last Error : " << CLIENT_GetLastError() << endl;
	}
	delete[] pBuffer;

	if (FALSE == CLIENT_CapturePictureEx(g_IRealHandle, "test1.jpg", NET_CAPTURE_JPEG)) {
	cout << "CLIENT_CapturePictureEx Failed! Last Error : " << CLIENT_GetLastError() << endl;
	}*/

	//data-saving
	save_handle = CLIENT_SaveRealData(g_IRealHandle, "videofile.mpeg");
}



void EndTest() {
	printf("input any key to quit!\n");
	getchar();

	if (0 == g_IRealHandle) {
		if (FALSE == CLIENT_StopRealPlayEx(g_IRealHandle)) {
			printf("CLIENT_StopRealPlayEx Failed! Last Error[%x]\n", CLIENT_GetLastError());
		}
		else {
			g_IRealHandle = 0;
		}
	}
	if (0 == g_ILoginHandle) {
		if (FALSE == CLIENT_Logout(g_ILoginHandle)) {
			printf("CLIENT_Logout Failed! Last Error[%x]\n", CLIENT_GetLastError());
		}
		else {
			printf("CLIENT_Logout Success");
			g_ILoginHandle = 0;
		}
	}

	if (TRUE == g_bSDKInitFlag) {
		CLIENT_Cleanup();
		g_bSDKInitFlag = FALSE;
	}
	return;
}

int main(int argc, char *argv[]) {
	/*int choice = 0;
	cout << "1.Enter Login" << endl;
	do {
	switch (choice) {
	case 1 :
	InitTest();
	break;
	case 2:

	}
	} while (choice != 0);
	cout << "WELCOME TO DAHUA SERVICE : " << endl;
	cout << "1.Log In." << endl;
	cout << "2.Add Face Library." << endl;
	cout << "3.Add Person To Face Library" << endl;*/
	InitTest();
	RunTest();
	EndTest();
	_getch();
	return 0;
}

void CALLBACK HaveReConnect(LLONG ILoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser) {
	//printf("ILoginID[0x%x]", ILoginID);
	cout << "ILoginID : " << ILoginID << endl;
	printf("Call HaveReConnect\n");
	if (NULL != pchDVRIP) {
		printf("pchDVRIP[%s]\n", pchDVRIP);
	}
	printf("nDVRPort[%d]\n", nDVRPort);
	printf("dwUser[%p]\n", dwUser);
	printf("\n");
}

static bool addPerson() {
	char *groupId = "2";
	char personName[] = "JOHN";
	short idType = 1512;
	char *memory = new char[100];

	NET_IN_OPERATE_FACERECONGNITIONDB stuIn = NET_IN_OPERATE_FACERECONGNITIONDB();
	stuIn.dwSize = sizeof(NET_IN_OPERATE_FACERECONGNITIONDB);
	stuIn.emOperateType = EM_OPERATE_FACERECONGNITIONDB_TYPE::NET_FACERECONGNITIONDB_ADD;
	stuIn.stPersonInfo.bImportantRank = 1;
	stuIn.stPersonInfo.pszGroupID = groupId;

	stuIn.stPersonInfo.wYear = 1999;
	stuIn.stPersonInfo.byMonth = 12;
	stuIn.stPersonInfo.byDay = 15;

	stuIn.stPersonInfo.bySex = 1;

	memcpy(stuIn.stPersonInfo.szPersonName, personName, sizeof(personName));

	stuIn.stPersonInfo.byIDType = byte(idType);
	DH_PIC_INFO pic;

	if (memory != NULL) {
		stuIn.stPersonInfo.wFacePicNum = 1;
		stuIn.stPersonInfo.szFacePicInfo[0].dwFileLenth = (int)sizeof(memory);
		stuIn.stPersonInfo.szFacePicInfo[0].dwOffSet = 0;

		stuIn.nBufferLen = (int)sizeof(memory);
		stuIn.pBuffer = memory;
	}

	NET_OUT_OPERATE_FACERECONGNITIONDB stuOut = NET_OUT_OPERATE_FACERECONGNITIONDB();
	stuOut.dwSize = sizeof(NET_OUT_OPERATE_FACERECONGNITIONDB);

	bool bRet = CLIENT_OperateFaceRecognitionDB(g_ILoginHandle, &stuIn, &stuOut, 3000);

	if (bRet) {
		cout << "szUID : " << (char)stuIn.stuUIDs << endl;
	}
	else {
		cout << CLIENT_GetLastError() << endl;
	}

	return bRet;
}
static bool addGroup() {
	static char groupName[] = "TEST1";

	NET_ADD_FACERECONGNITION_GROUP_INFO addGroupInfo = NET_ADD_FACERECONGNITION_GROUP_INFO();
	memcpy(addGroupInfo.stuGroupInfo.szGroupName, groupName, sizeof(groupName)+10);

	NET_IN_OPERATE_FACERECONGNITION_GROUP stuIn = NET_IN_OPERATE_FACERECONGNITION_GROUP();
	stuIn.dwSize = sizeof(NET_IN_OPERATE_FACERECONGNITION_GROUP);
	stuIn.emOperateType = EM_OPERATE_FACERECONGNITION_GROUP_TYPE::NET_FACERECONGNITION_GROUP_ADD;
	stuIn.pOPerateInfo = &addGroupInfo;

	NET_OUT_OPERATE_FACERECONGNITION_GROUP stuOut = NET_OUT_OPERATE_FACERECONGNITION_GROUP();
	stuOut.dwSize = sizeof(NET_OUT_OPERATE_FACERECONGNITION_GROUP);
	stuOut.szGroupId;

	bool bRet = CLIENT_OperateFaceRecognitionGroup(g_ILoginHandle, &stuIn, &stuOut, 4000);

	cout << "Face Library : " << addGroupInfo.stuGroupInfo.szGroupName << "ID : " << stuOut.szGroupId << endl;

	if (bRet) {
		cout << "ID : " << stuOut.szGroupId << endl;
	}

	return bRet;
}

//static bool downloadPersonPic() {
//	string szFileName = "787294.png";
//	/*string pszFileDst = "/";*/
//	fstream in("Images/1.jpg");
//	/*if (in) {
//		in.seekg(0, ios::end);
//		size_t len = in.tellg();
//		in.seekg(0);
//		string contents(len + 1, '\0');
//		in.read(&contents[0], len);
//		}*/
//
//	tagDH_IN_DOWNLOAD_REMOTE_FILE stuIn = tagDH_IN_DOWNLOAD_REMOTE_FILE();
//	stuIn.dwSize = sizeof(tagDH_IN_DOWNLOAD_REMOTE_FILE);
//	stuIn.pszFileName = szFileName.data();
//	//stuIn.pszFileDst = pszFileDst.data();
//
//	tagDH_OUT_DOWNLOAD_REMOTE_FILE stuOut = tagDH_OUT_DOWNLOAD_REMOTE_FILE();
//	stuOut.dwSize = sizeof(tagDH_OUT_DOWNLOAD_REMOTE_FILE);
//	if (CLIENT_DownloadRemoteFile(g_ILoginHandle, &stuIn, &stuOut, 5000)) {
//		cout << "Successfully added!!!";
//		return true;
//	}
//	else {
//		cout << "Error : " << CLIENT_GetLastError() << endl;
//		return false;
//	}
//}

static int StartFindPerson() {
	char *groupId = "TEST";
	//char *personName = "akmal";
	m_FindHandle = NULL;
	nToken = 0;

	int nTotalCount = 0;
	NET_IN_STARTFIND_FACERECONGNITION stuIn = NET_IN_STARTFIND_FACERECONGNITION();
	stuIn.dwSize = sizeof(NET_IN_STARTFIND_FACERECONGNITION);
	stuIn.bPersonEnable = 1;
	stuIn.stPerson.pszGroupID = groupId;
	//memcpy(stuIn.stPerson.szPersonName, personName, sizeof(personName));
	stuIn.stPerson.bySex = 0;
	stuIn.stFilterInfo.nGroupIdNum = 1;
	stuIn.stFilterInfo.emFaceType = EM_FACERECOGNITION_FACE_TYPE::EM_FACERECOGNITION_FACE_TYPE_ALL;

	//stuIn.stFilterInfo.stBirthdayRangeStart.dwYear = 1999;
	stuIn.stFilterInfo.nRangeNum = 1;
	stuIn.stFilterInfo.szRange[0] = EM_FACE_DB_TYPE::NET_FACE_DB_TYPE_BLACKLIST;

	NET_OUT_STARTFIND_FACERECONGNITION stuOut = NET_OUT_STARTFIND_FACERECONGNITION();
	stuOut.dwSize = sizeof(NET_OUT_STARTFIND_FACERECONGNITION);
	if (CLIENT_StartFindFaceRecognition(g_ILoginHandle, &stuIn, &stuOut, 4000)) {
		m_FindHandle = stuOut.lFindHandle;
		nTotalCount = stuOut.nTotalCount;
		cout << nTotalCount << endl;
		nToken = stuOut.nToken;
	}
	else {
		cout << "CLIENT_StartFindFaceRecognition Failed, Error : " << CLIENT_GetLastError() << endl;
	}
	return nTotalCount;
}

static tagCANDIDATE_INFO doFindPerson() {
	int nBeginNum = 1;
	int nCount = 1;
	int candidateNumber;
	NET_IN_DOFIND_FACERECONGNITION stuIn = NET_IN_DOFIND_FACERECONGNITION();
	stuIn.dwSize = sizeof(NET_IN_DOFIND_FACERECONGNITION);
	stuIn.lFindHandle = m_FindHandle;
	stuIn.nCount = nCount;
	stuIn.nBeginNum = nBeginNum;
	stuIn.emDataType = EM_NEEDED_PIC_RETURN_TYPE::EM_NEEDED_PIC_TYPE_HTTP_AND_BINARY;

	/*CANDIDATE_INFO candidate = CANDIDATE_INFO();
	candidate.nChannelID = 0;
	candidate.stPersonInfo.pszGroupName = "test1";
	candidate.stPersonInfo.pszGroupID = "2";
	candidate.stPersonInfo.szPersonName[0] = { 'a' };
	candidate.stPersonInfo.bySex = 0;*/
	NET_OUT_DOFIND_FACERECONGNITION stuOut = NET_OUT_DOFIND_FACERECONGNITION();
	stuOut.dwSize = sizeof(NET_OUT_DOFIND_FACERECONGNITION);
	stuOut.nCadidateNum = 1;
	candidateNumber = stuOut.nCadidateNum;
	stuOut.stCadidateInfo[0].stPersonInfo.pszGroupID = "2";
	stuOut.stCadidateInfo[0].stPersonInfo.bySex = 0;
	stuOut.stCadidateInfo[0].stPersonInfo.pszGroupName = "test1";
	//stuOut.stCadidateInfo[0].stPersonInfo.wYear = '1992';
	stuOut.stCadidateInfo[0].stPersonInfo.byIDType = EM_CERTIFICATE_TYPE::CERTIFICATE_TYPE_IC;

	for (int i = 0; i < nCount; i++) {
		stuOut.stCadidateInfo[i].stPersonInfo.szFacePicInfo[0].dwFileLenth = 256;
		stuOut.stCadidateInfo[i].stPersonInfo.szFacePicInfo[0].pszFilePath = new char(256);
	}

	if (CLIENT_DoFindFaceRecognition(&stuIn, &stuOut, 4000)) {
		if (stuOut.stCadidateInfo == 0) {
			cout << 0 << endl;
		}
		tagCANDIDATE_INFO stuCandidatesEx[] = { 0 };
		for (int i = 0; i < candidateNumber; i++) {
			stuCandidatesEx[i] = tagCANDIDATE_INFO();
			stuCandidatesEx[i] = stuOut.stCadidateInfo[i];
		}
		for (int i = 0; i < candidateNumber; i++) {
			cout << stuCandidatesEx[i].stPersonInfo.szPersonName << endl;
		}

		return *stuCandidatesEx;
	}
	else {
		cout << "CLIENT_DoFindFaceRecognition Failed, Error : " << CLIENT_GetLastError() << endl;
	}
}

//static bool doFindPerson() {
//
//}
// Find Face Library
//static NET_FACERECONGNITION_GROUP_INFO findGroupInfo(char groupId[]) {
//	NET_FACERECONGNITION_GROUP_INFO groupInfoRet[] = { NULL };
//
//	NET_IN_FIND_GROUP_INFO stuIn = NET_IN_FIND_GROUP_INFO();
//	memcpy(stuIn.szGroupId, groupId, sizeof(groupId));
//
//	int max = 20;
//	NET_FACERECONGNITION_GROUP_INFO *groupInfo = new NET_FACERECONGNITION_GROUP_INFO[max];
//	for (int i = 0; i < max; i++) {
//		*(groupInfo + i) = NET_FACERECONGNITION_GROUP_INFO();
//	}
//
//	NET_OUT_FIND_GROUP_INFO stuOut = NET_OUT_FIND_GROUP_INFO();
//	stuOut.pGroupInfos = sizeof(NET_OUT_FIND_GROUP_INFO) * stuOut.nMaxGroupNum;
//	stuOut.nMaxGroupNum = sizeof(groupInfo);
//
//	if (CLIENT_FindGroupInfo(g_ILoginHandle, &stuIn, &stuOut));
//}