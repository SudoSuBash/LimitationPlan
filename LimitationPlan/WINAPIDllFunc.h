#pragma once

#include <Windows.h>
typedef NTSTATUS (*fnRtlSetProcessIsCritical)(
	BOOL newValue,
	BOOL* oldValue,
	BOOL checkFlag
	);

fnRtlSetProcessIsCritical getRtlProcCritical();