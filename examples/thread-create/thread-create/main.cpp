#include <Windows.h>
#include <stdio.h>

//스레드 함수
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	puts("Begin Thread");

	for (int i = 0; i < 5; i++)
	{
		printf("[Worker thread] %d\n", i);
		Sleep(500);
	}

	puts("End Thread");
	return 0;
}

int main() {
	DWORD threadId;

	//스레드 생성
	HANDLE hThread = CreateThread(
		NULL,
		0,
		ThreadFunc,
		NULL,
		0,
		&threadId
	);

	//메인 스레드 실행
	for (int i = 0; i < 10; ++i) {
		printf("[Main Thread] %d \n", i);
		Sleep(300);
	}

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);

	return 0;
}