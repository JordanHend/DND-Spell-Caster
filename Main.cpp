#include <Windows.h>
#include <string>
#include <iostream>
#include <time.h>
#include <random>
#include <chrono>
#include <sstream>
#include "Spells.h"
bool keyDown = false;
bool close = false;
#define SHIFTED 0x8000 
int numTimesCast = 8;



void ShiftDwn()
{
	keybd_event(VK_LSHIFT, MapVirtualKey(VK_LSHIFT, 0), KEYEVENTF_EXTENDEDKEY, 0);
}

void ShiftUP()
{
	keybd_event(VK_LSHIFT, MapVirtualKey(VK_LSHIFT, 0),KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}


void OutputText(std::string text)
{
	

	
		for (unsigned int j = 0; j < text.size(); j++)
		{


			if (text[j] == '!' || text[j] == '+' || text[j] == '>' || text[j] == '(' || text[j] == ')' || text[j] == '#' || text[j] == ':')
				ShiftDwn();
			else
				ShiftUP();

 			if (text[j] == '\n')
			{
				

					ShiftDwn();
					keybd_event(VK_RETURN, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
					keybd_event(VK_RETURN, 0x45, KEYEVENTF_KEYUP, 0);
					ShiftUP();
				
				
			}
			else
			{


				keybd_event(VkKeyScan(text[j]), 0x45, KEYEVENTF_EXTENDEDKEY, 0);
				keybd_event(VkKeyScan(text[j]), 0x45, KEYEVENTF_KEYUP, 0);
			}
		}




	



}


bool tabDown = false;
int main()
{

	while (!close)
	{
		if (GetKeyState(VK_ESCAPE) & SHIFTED)
		{
			if (!close)
				close = true;
		}


		if ((GetKeyState(VK_TAB) & SHIFTED) && !tabDown)
		{
			tabDown = true;
			RollResponse r = rollDie(16, 6, 6, 2);
			std::cout << r.record;
			std::cout << "ROLLED 16d6: " << r.value << "\n";
		}
		else if(!(GetKeyState(VK_TAB) & SHIFTED) && tabDown)
			tabDown = false;




		if (GetKeyState(VK_BACK) & SHIFTED && !keyDown)
		{
			keyDown = true;
			RollResponse r = Spells::ScorchingRay(2);
			OutputText(r.record);
		}
		else if(!(GetKeyState(VK_BACK) & SHIFTED) && keyDown)
		{
			keyDown = false;
		}



	}

	return 0;
}