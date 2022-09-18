void initGlew();
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void setupPixelFormat(HDC hDC);
void setupPixelFormatARB();
void initWinClass(PWNDCLASS WndCls, HINSTANCE hInstance);
void setupDummyContext(HINSTANCE hInstance);
void initGL(HINSTANCE hInstance);