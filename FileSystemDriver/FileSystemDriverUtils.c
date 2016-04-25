#include "FileSystemDriver.h"


BOOLEAN CheckExtension(_In_ PFILE_OBJECT fileObject) {
	WCHAR txtExtBuf[] = L".txt";
	UNICODE_STRING txtExt, fileExt;
	txtExt.Buffer = txtExtBuf;
	fileExt.Length = txtExt.Length = sizeof(txtExtBuf) - sizeof(WCHAR);
	fileExt.MaximumLength = txtExt.MaximumLength = sizeof(txtExtBuf);

	if (NULL != fileObject) {
		PT_DBG_PRINT(PTDBG_INFORMATION,
			("Read file: %wZ\n", &fileObject->FileName));
		if (NULL != fileObject->FileName.Buffer && fileObject->FileName.Length >= txtExt.Length) {
			fileExt.Buffer = &fileObject->FileName.Buffer[(fileObject->FileName.Length - txtExt.Length) / sizeof(WCHAR)];
			PT_DBG_PRINT(PTDBG_INFORMATION,
				("Extension: %wZ\n", &fileExt));
			if (RtlEqualUnicodeString(&txtExt, &fileExt, TRUE)) {
				PT_DBG_PRINT(PTDBG_INFORMATION,
					("Text file detected\n"));
				return TRUE;
			}
		}
	}
	return FALSE;
}
