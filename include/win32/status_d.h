
#define STATUS_D	1
#define ID_TEXT1        200
#define ID_TEXT2        201
#define ID_CANCEL       203
/* Prototype of status_d.c */
BOOL CALLBACK status_dDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void Handle_WM_PAINT(HWND hDlg);
void Handle_WM_INITDIALOG(HWND hDlg);
void Handle_WM_COMMAND(HWND hDlg, WPARAM wParam, LPARAM lParam);

BOOL bCreate_status_d_text(char *text1,char *text2);
BOOL bUpdate_status_d_text(char *text1,char *text2);
BOOL bIs_status_d_Cancel_checked();
void close_status_d();

