#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
 #define MAX_FIELDS 100
char *fields[MAX_FIELDS];
int fildscount;
int obter_numero_antigo(char *line) {
    int i=0;
    i = 0;
        fields[i] = strtok(line, ":");
        while (fields[i] != NULL && i < MAX_FIELDS) {
            i++;
            fields[i] = strtok(NULL, ":");
        }
        fildscount=i;
        if(i>0){
            return atoi( fields[0]);
        }
        return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
     WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    // Definir as propriedades da janela
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1); // definir pincel para azul
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "MinhaJanela";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    // Registrar a classe da janela
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Falha no registro da classe da janela!", "Erro", MB_ICONERROR | MB_OK);
        return 0;
    }

    // Criar a janela
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "MinhaJanela", "time difference",
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                          400, 300, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hStartEdit, hEndEdit, hButton;
    static char startStr[30], endStr[30];
     static WCHAR wstartStr[30], wendStr[30];
    switch (message)
    {
    case WM_CREATE:
        hStartEdit =CreateWindow(TEXT("EDIT"), NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        100, 50, 100, 30, hWnd, (HMENU)1, GetModuleHandle(NULL), NULL);
        hEndEdit = CreateWindow(TEXT("EDIT"), NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        100, 100, 100, 30, hWnd, (HMENU)2, GetModuleHandle(NULL), NULL);
        hButton = CreateWindow("BUTTON", "resolt", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            100, 150, 100, 30, hWnd, (HMENU)3, GetModuleHandle(NULL), NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 3: // Botão "Calcular"
            GetWindowText(hStartEdit, startStr, 9);
            GetWindowText(hEndEdit, endStr, 9);
            
            double d1=(double)obter_numero_antigo(startStr)*100;
            double d2=0;
            if(fildscount>1) d2=(double)atoi(fields[1]);
            d2=d2*1.666666;
            double d3=(double)obter_numero_antigo(endStr)*100;
            double d4=0;
            if(fildscount>1) d4=(double)atoi(fields[1]);
            d4=d4*1.666666;
            d1=d1+d2;
            d3=d3+d4;
  // Calcula a diferença entre as horas
            int dddd=(int)d4;
            double diffHour =(double) (d3-d1);
            diffHour =diffHour /100.00;
            char message[350];
            sprintf(message, "time diference %f hours.",diffHour);
            MessageBox(hWnd, message, "solved", MB_OK);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            // Define a cor de fundo da janela para azul
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            // Define a cor das linhas para branco
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);
            
            // Desenha as linhas com base nas coordenadas fornecidas
            
            
            // Libera os recursos utilizados
            DeleteObject(hPen);
            EndPaint(hWnd, &ps);
            break;
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
