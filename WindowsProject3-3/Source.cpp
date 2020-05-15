#define LOWORD(l)   ((WORD) (l))
#ifdef UNICODE
typedef wchar_t WCHAR;
typedef WCHAR TCHAR;
#endif
#include <Windows.h>
#include <Windowsx.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <iomanip>
#include <iostream>
#include <string>

#pragma comment(lib, "ComCtl32.lib")
LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int z = 0;

TCHAR czClassName[] = L"MaimWin";
TCHAR czFormName[] = L"Мирсонов Лаб.3";
TCHAR childClassName[] = L"AboutName";
TCHAR child_app_name[] = L"О функциях";
HWND hwndA;
DWORD buff, temp, rez;

HINSTANCE hInst;
TCHAR szFile[] = L"Y:\\12346.bmp";       // buffer for file name
HANDLE hf;

OPENFILENAME OpenFileName = { 0 };
//TCHAR FilePath[MAX_PATH] = _T("1");

void OpenFileDialog(HWND hwnd)
{
    OPENFILENAME OpenFileName;
    ZeroMemory(&OpenFileName, sizeof(OpenFileName));
    OpenFileName.hwndOwner = hwnd;
    OpenFileName.lpstrFile = szFile;
    TCHAR FilePath[MAX_PATH] = _T("\0");
    OpenFileName.lpstrFile[0] = *FilePath;
    OpenFileName.lStructSize = sizeof(OpenFileName);
    OpenFileName.lpstrFilter = _T("Bitmap Files\0*.bmp\0Ico files\0*.ico");
    OpenFileName.nFilterIndex = 2;
    OpenFileName.nMaxFile = MAX_PATH;
    OpenFileName.Flags = OFN_EXPLORER | OFN_FORCESHOWHIDDEN;
    if (GetOpenFileName(&OpenFileName)) {
        hf = CreateFile(OpenFileName.lpstrFile, GENERIC_READ,
            0, (LPSECURITY_ATTRIBUTES)NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
            (HANDLE)NULL);
        MessageBox(hwnd, szFile, TEXT("Путь к файлу"), NULL);//при нажатии на кнпоку что то будет происходить здесь
        z = 1;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND HHw, hW, hWndChild;
    RECT Rect;
    PAINTSTRUCT PaintStruct;
    HDC hDC, hCompatibleDC;
    HANDLE hOldBitmap;
    static int caption, menu, border;
 HDC memBit;
 HBITMAP hBitmap;
 BITMAP bm;
    switch (message)
    {
        //case WM_CREATE:
        //{
        //    caption = GetSystemMetrics(SM_CYCAPTION);
        //    menu = GetSystemMetrics(SM_CYMENU);
        //   // border = GetSystemMetrics(SM_CXFIXEDFRAME);
        //   
        //    break;
        //}
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 502://выход из программы
            ExitProcess(0);
            break;
        case 1001://окно о создателе
            MessageBox(hwnd, TEXT("Данное приложение создал студент Мирсонов В.А.\nГруппа РТ5-41Б"), TEXT("О создателе"), MB_ICONINFORMATION);//при нажатии на кнпоку что то будет происходить здесь
            break;
        case 1002://окно о функциях программы
        //MessageBox(hwnd, TEXT("Нажата кнопка о функциях"), TEXT("О функциях"), NULL);//при нажатии на кнпоку что то будет происходить здесь
            CreateWindow(childClassName, _T("О работе приложения"), /*WS_CHILDWINDOW |*/ WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE | WS_POPUPWINDOW /*| WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS*/, 100, 100, 500, 400, hwnd, 0, hInst, 0);
            break;
        case 501:
            hW = GetForegroundWindow();
            //MessageBox(hwnd, TEXT("Нажата кнопка открыть"), NULL, NULL);//при нажатии на кнпоку что то будет происходить здесь
            OpenFileDialog(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_PAINT:
    {
        hDC = BeginPaint(hwnd, &PaintStruct);
        GetClientRect(hwnd, &Rect);
        hBitmap = (HBITMAP)LoadImage(NULL, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
       // if (z == 1)
       // {
       //     LPCWSTR adr = LPCWSTR(szFile);
       //     hBitmap = (HBITMAP)LoadImage(NULL,szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
      //  }
            if (hBitmap == NULL)
            {
                MessageBox(hwnd, _T("Файл не найден"), _T("Загрузка изображения"),
                    MB_OK | MB_ICONHAND);
               // DestroyWindow(hwnd);
                return 1;
            }
            GetObject(hBitmap, sizeof(BITMAP), &bm);
            hCompatibleDC = CreateCompatibleDC(hDC);
            hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
            StretchBlt(hDC, Rect.left + 20, Rect.top + 20, Rect.right - 40, Rect.bottom - 40, hCompatibleDC, 0, 0, bm.bmWidth,
                bm.bmHeight, SRCCOPY);
            SelectObject(hCompatibleDC, hOldBitmap);
            DeleteObject(hBitmap);
            DeleteDC(hDC);
            EndPaint(hwnd, &PaintStruct);
            return 0;
            /* hDC = BeginPaint(hwnd, &PaintStruct);
             GetClientRect(hwnd, &Rect);
             hBitmap = (HBITMAP)LoadImage(hInst, szFile, IMAGE_BITMAP,
                 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
             if (hBitmap == NULL)
             {
                 MessageBox(hwnd, _T("Файл не найден"), _T("Загрузка изображения"),
                     MB_OK | MB_ICONHAND);
                 DestroyWindow(hwnd);
                 return 1;
             }
             GetObject(hBitmap, sizeof(bm), &bm);
             hDC = GetDC(hwnd);
             memBit = CreateCompatibleDC(hDC);
             SelectObject(memBit, hBitmap);
             ReleaseDC(hwnd, hDC);
             BitBlt(hDC, 30, 30, bm.bmWidth - 30, bm.bmHeight - 30, memBit, 0, 0, SRCCOPY);
             EndPaint(hwnd, &PaintStruct);*/
            return 0;
        }
    case WM_DESTROY: PostQuitMessage(0); break;
    default: return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}


//case WM_COMMAND:
//    switch (wParam)
//    {
//    case 502://выход из программы
//    {
//        ExitProcess(0);
//        break;
//    }
//    case 1001://окно о создателе
//    {
//        MessageBox(hwnd, TEXT("Данное приложение создал студент Мирсонов В.А.\nГруппа РТ5-41Б"), TEXT("О создателе"),MB_ICONINFORMATION);//при нажатии на кнпоку что то будет происходить здесь
//        break;
//    }
//    case 1002://окно о функциях программы
//    {
//        //MessageBox(hwnd, TEXT("Нажата кнопка о функциях"), TEXT("О функциях"), NULL);//при нажатии на кнпоку что то будет происходить здесь
//        CreateWindow(childClassName, _T("О работе приложения"),/* WS_CHILDWINDOW |*/ WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE | WS_S_END/*| WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS*/ , 100, 100, 500, 400, hwnd, 0, hInst, 0);
//        break;
//    }
//    case 501:
//    {
//        hW = GetForegroundWindow();
//        MessageBox(hwnd,TEXT("Нажата кнопка открыть"),NULL,NULL);//при нажатии на кнпоку что то будет происходить здесь
//        OpenFileDialog(hwnd);
//        InvalidateRect(hwnd, NULL, TRUE);
//        break;
//    }
//    }
//    case WM_PAINT:
//    {
//         hDC = BeginPaint(hwnd, &PaintStruct);
//         GetClientRect(hwnd, &Rect);
//         hBitmap = LoadImage(NULL, TEXT("C:\\Users\\Вячеслав\\Desktop\\1.bmp" /*+ imAdr*/), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//         GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
//         hCompatibleDC = CreateCompatibleDC(hDC);
//         hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
//         GetClientRect(hwnd, &Rect);
//         StretchBlt(hDC,   Rect.left +20, Rect.top +20, Rect.right -40, Rect.bottom-40, hCompatibleDC, 0, 0, Bitmap.bmWidth,
//             Bitmap.bmHeight, SRCCOPY);
//         SelectObject(hCompatibleDC, hOldBitmap);
//         DeleteObject(hBitmap);
//         DeleteDC(hCompatibleDC);
//         EndPaint(hwnd, &PaintStruct);
//         return 0;
//         //здесь начинаются строки, связанные с рисованием картинки
//         //hmdc = CreateCompatibleDC(hDC); //Создаёт совместимый с оконным контекст памяти
//         //SelectObject(hmdc, hBitmap); //Выбирает объект картинку
//         //GetObject(hBitmap, sizeof(bm), (LPSTR)&bm); //получаем высоту и ширину картинки
//         //BitBlt(hDC, 10, 10, bm.Width, bm.bmHeight, hmdc, 0, 0, SRCCOPY); //Помещает картинку на экран в точку 10, 10
//         //из памяти (hmdc)

//         //DeleteDC(hmdc); //удаляем из памяти контекст
//         //Конец рисования картинки
//        // HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
//        // FillRect(hDC, &Rect, hBrush);
//         //SetBkColor(hDC, RGB(205, 133, 63));
//         //EndPaint(hwnd, &PaintStruct);
//         break;
//    }
//case WM_DESTROY: PostQuitMessage(0); break;

//default: return DefWindowProc(hwnd, message, wParam, lParam); break;
//}

ATOM myRegistryClass(HINSTANCE hI, int cmdMode)
{
    WNDCLASS cw;

    cw.style = CS_HREDRAW | CS_VREDRAW;
    cw.cbClsExtra = 0;
    cw.cbWndExtra = 0;
    cw.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(205, 133, 100));
    cw.hCursor = LoadCursor(NULL, IDC_ARROW);
    cw.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    cw.hInstance = hInst;
    cw.lpfnWndProc = WndProc;
    cw.lpszClassName = czClassName;
    cw.lpszMenuName = NULL;

    RegisterClass(&cw);

    WNDCLASS wch;
    // Определение класса окна
    wch.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(25, 120, 255));
    wch.hCursor = LoadCursor(NULL, IDC_ARROW);
    wch.hInstance = hInst;
    wch.lpszClassName = childClassName;
    wch.lpfnWndProc = ChildProc;
    wch.style = CS_VREDRAW | CS_HREDRAW;
    wch.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wch.lpszMenuName = NULL;
    wch.cbClsExtra = 0;
    wch.cbWndExtra = 0;
    if (!RegisterClass(&wch)) return 0;

    return 0;
}


BOOL InitInstance(HINSTANCE hI, int Mode)
{
    hwndA = CreateWindow(czClassName, czFormName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1350, 750, NULL, NULL, hInst, NULL);

    ShowWindow(hwndA, Mode);
    UpdateWindow(hwndA);

    return TRUE;
}


/*Главная функция*/
int WINAPI WinMain(HINSTANCE hIn, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int cmdShow)
{
    MSG msg;
    myRegistryClass(hIn, cmdShow);
    InitInstance(hIn, cmdShow);

    InitCommonControls();

    /*Создание строки состояния*/
    HWND hStatusWindow = CreateStatusWindow(WS_CHILD | WS_VISIBLE, L"", hwndA, 5000);

    HMENU hMainMenu = CreateMenu();
    HMENU hPopMenuFile = CreatePopupMenu();
    HMENU hPopMenuFile1 = CreatePopupMenu();

    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile, L"Файл");
    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT)hPopMenuFile1, L"Справка");

    AppendMenu(hPopMenuFile, MF_STRING, 501, L"Открыть...\t");
    AppendMenu(hPopMenuFile, MF_STRING, 502, L"Выход из программы\t");
    AppendMenu(hPopMenuFile1, MF_STRING, 1001, L"О создателе\t");
    AppendMenu(hPopMenuFile1, MF_STRING, 1002, L"Что программа делает?\t");

    SetMenu(hwndA, hMainMenu);
    SetMenu(hwndA, hPopMenuFile);
    SetMenu(hwndA, hPopMenuFile1);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   // Обработчик сообщений
    HDC hDC;
    TCHAR szText[] = _T("Данное приложение предназначено для открытия и \nпросмотра картинок, выбранных пользователем.\nПри выборе в меню Файл->Открыть... \nоткрывается диалоговое окно выбора файла");
    PAINTSTRUCT PaintStruct;
    RECT Rect;
    switch (message)
    {
    case WM_PAINT:
    {
        hDC = BeginPaint(hWnd, &PaintStruct);
        GetClientRect(hWnd, &Rect);
        SetBkColor(hDC, RGB(25, 120, 255));
        SetTextColor(hDC, RGB(255, 255, 255));
        DrawText(hDC, szText, -1, &Rect, DT_INTERNAL | DT_CENTER | DT_VCENTER);
        EndPaint(hWnd, &PaintStruct);
        return 0;
    }
    case WM_CLOSE:
        ShowWindow(hWnd, SW_HIDE); // <----
        break;
        // Обработка сообщения по умолчанию
    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}