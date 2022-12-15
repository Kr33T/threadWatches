#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>


VOID ManageTime();
DWORD WINAPI Timer(BOOL[2]);
VOID ChangeTime(VOID);
SYSTEMTIME t; // struct

int main()
{
	system("chcp 1251");
	system("cls");
	ManageTime();
	return 0;
}
VOID ChangeTime(VOID)
{
	system("cls");
	DWORD d = 0;
	printf_s("������� ����:");
	scanf_s("%d", &d);
	t.wHour = d;
	printf_s("������� ������:");
	scanf_s("%d", &d);
	t.wMinute = d;
	printf_s("������� �������:");
	scanf_s("%d", &d);
	t.wSecond = d;
	system("cls");
}
VOID ManageTime()
{
	BOOL F[2];
	F[0] = TRUE;
	F[1] = FALSE;
	DWORD cmd = 0;
	GetLocalTime(&t);
	HANDLE Potok = CreateThread(NULL, 0, Timer, F, 0, 0);
	while (1)
	{
		scanf_s("%d", &cmd);
		if (cmd == 6) {
			SuspendThread(Potok);
			printf("����� ��������!\n");
		}
		else if (cmd == 7) {
			printf("����� ���������!\n");
			ResumeThread(Potok);
		}
		if (cmd == 0)
		{
			SuspendThread(Potok);
			system("cls");
			printf_s("0-���������\n1-������\n2-������� �����\n3-��������� ���������\n4-���/���� ����������\n5-���/���� ������");
		}
		if (cmd == 1)
		{
			ResumeThread(Potok);
			system("cls");
		}
		if (cmd == 2)
		{
			SuspendThread(Potok);
			ChangeTime();
			ResumeThread(Potok);
		}
		if (cmd == 3)
		{
			GetLocalTime(&t);
			system("cls");
			ResumeThread(Potok);
		}
		if (cmd == 4)
		{
			F[1] = !F[1];
			if (F[1])
			{
				t.wHour = 0;
				t.wMinute = 0;
				t.wSecond = 0;
				t.wMilliseconds = 0;
			}
			else
			{
				GetLocalTime(&t);
			}
			system("cls");
		}
		if (cmd == 5)
		{
			F[0] = !F[0];
			if (!F[0])
			{
				SuspendThread(Potok);
				ChangeTime();
				ResumeThread(Potok);


			}
			else
			{
				GetLocalTime(&t);
			}
		}
	}
}
DWORD WINAPI Timer(BOOL F[2])
{
	SYSTEMTIME staroe, novoe; // ��� ������� ��� ��������� ����� ������ ������ ������� ��� ���
	GetLocalTime(&staroe);
	GetLocalTime(&novoe);
	while (1)
	{
		GetLocalTime(&staroe);
		if (F[1]) // ���� �������� ����� ������ �����������
		{
			if ((staroe.wMilliseconds / 100) != (novoe.wMilliseconds / 100) || novoe.wHour != staroe.wHour || novoe.wMinute != staroe.wMinute || novoe.wSecond != staroe.wSecond)
			{
				// ��������� ���������� �� ��������� ����� �� ������
				system("cls");
				novoe = staroe;
				printf_s("%d:%d:%d:%d\n", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds); // ����������
				t.wMilliseconds++;
				if (t.wMilliseconds == 10)
				{
					t.wMilliseconds = 0;
					t.wSecond++;
				}
				if (t.wSecond == 60)
				{
					t.wSecond = 0;
					t.wMinute++;
				}
				if (t.wMinute == 60)
				{
					t.wMinute = 0;
					t.wHour++;
				}
				if (t.wHour == 24)
				{
					t.wHour = 0;
				}

			}
		}
		else { // ���� �������� ����� ������ �������
			if (novoe.wHour != staroe.wHour || novoe.wMinute != staroe.wMinute || novoe.wSecond != staroe.wSecond)
			{
				system("cls");
				novoe = staroe;
				printf_s("%d:%d:%d", t.wHour, t.wMinute, t.wSecond);
				if (F[0]) // f = true - ����
				{
					t.wSecond++;
					if (t.wSecond == 60)
					{
						t.wSecond = 0;
						t.wMinute++;
					}
					if (t.wMinute == 60)
					{
						t.wMinute = 0;
						t.wHour++;
					}
					if (t.wHour == 24)
					{
						t.wHour = 0;
					}
				}
				else // ������
				{
					if (t.wHour == 0 && t.wMinute == 0 && t.wSecond == 0)
					{
						system("cls");
						printf_s("0:0:0 ����� �������");
					}
					else
					{
						if (t.wHour != 0 && t.wMinute == 0 && t.wSecond == 0)
						{
							t.wMinute = 59;
							t.wSecond = 60;
							t.wHour--;
						}
						if (t.wMinute != 0 && t.wSecond == 0)
						{
							t.wSecond = 60;
							t.wMinute--;
						}
						if (t.wSecond != 0)
						{
							t.wSecond--;
						}
					}
				}
			}
		}
	}
	ExitThread(0);
}
