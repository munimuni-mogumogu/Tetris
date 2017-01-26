#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>

using namespace std;

//分からないときはここを見てねhttp://www.geekpage.jp/programming/iphlpapi/arp-info.php

int main()
{
	DWORD i;
	PMIB_IPNETTABLE pIpNetTable = NULL;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	DWORD dwResult;

	dwResult = GetIpNetTable(NULL, &dwSize, 0);
	/* GetIpNetTable()で必要になるサイズを取得 */
	if (dwResult == ERROR_INSUFFICIENT_BUFFER) {
		pIpNetTable = (MIB_IPNETTABLE *)malloc(dwSize);
	}

	/* 実際にGetIpNetTable()を使う */
	if ((dwRetVal = GetIpNetTable(pIpNetTable, &dwSize, 0))
		== NO_ERROR) {
		if (pIpNetTable->dwNumEntries > 0) {
			for (i = 0; i<pIpNetTable->dwNumEntries; i++) {
				if (pIpNetTable->table[i].dwType == 3) {
					printf("Address: %s\n",
						inet_ntoa(*(struct in_addr *)&pIpNetTable->table[i].dwAddr));

					/* 注意：この例ではdwPhysAddrLenが6であると仮定しています */
					/* 本来はこのように6であると仮定すべきではありません      */
					//printf("Phys Addr Len: %d\n",
						//pIpNetTable->table[i].dwPhysAddrLen);
					//printf("Phys Address: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
						//pIpNetTable->table[i].bPhysAddr[0],
						//pIpNetTable->table[i].bPhysAddr[1],
						//pIpNetTable->table[i].bPhysAddr[2],
						//pIpNetTable->table[i].bPhysAddr[3],
						//pIpNetTable->table[i].bPhysAddr[4],
						//pIpNetTable->table[i].bPhysAddr[5]);

					//printf("Index:   %ld\n", pIpNetTable->table[i].dwIndex);
					//printf("Type:   %ld\n", pIpNetTable->table[i].dwType);
					printf("\n");
				}
			}
		}
	}
	else {
		printf("GetIpNetTable failed.\n");
		LPVOID lpMsgBuf;

		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwRetVal,
			MAKELANGID(LANG_NEUTRAL,
				SUBLANG_DEFAULT), //Default language
				(LPTSTR)&lpMsgBuf,
			0,
			NULL)) {
			printf("\tError: %s", lpMsgBuf);
		}

		LocalFree(lpMsgBuf);
	}
	cin.get();
	return 0;
}