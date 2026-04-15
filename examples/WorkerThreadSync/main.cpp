#include <stdio.h>
#include <Windows.h>

//work thread func
DWORD WINAPI ThreadFunc(LPVOID pParam) {
	puts(
		"Begin Thread"
	);
	
	for (int i = 0; i < 5; ++i) {
		printf("[Worker thread] %d \n", i);
		::Sleep(1);
}

//스레드 종료 전 이벤트 세트
	puts("before set event");
	// 이벤트 호출시 main wait 함수 호출
	::SetEvent((HANDLE)pParam);
	puts("after set event");
	puts("end thread");

return 0;
}

int main(int argc, CHAR* argv[]) {
	//이벤트 객체 생성
	HANDLE hEvent = ::CreateEvent(
		NULL,
		FALSE,
		FALSE,
		NULL
	);
	// 작업자 스레드 생성 및 시작
	DWORD dwThreadID = 0;
	HANDLE hThread = ::CreateThread(NULL,
		0, ThreadFunc, hEvent, 0, &dwThreadID);

	// 작업자 스레드와 동시에 실행되는 코드 영역의 시작
	for (int i = 0; i < 5; ++i) {
		printf("[Main thread %d\n", i);
		//i 값이 3이면 이벤트 세팅 대기
		if (i == 3 &&
			::WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0) {
			puts(" exit event detect");
			::CloseHandle(hEvent);
			hEvent = NULL;
		}
	}
	::CloseHandle(hThread);
	return 0;
}
