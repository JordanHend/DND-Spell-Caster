#ifndef DNDSPELLS_H
#define DNDSPELLS_H
#include <Windows.h>
#include <string>
#include <iostream>
#include <time.h>
#include <random>
#include <chrono>
#include <sstream>


struct RollResponse
{
	int value;
	std::string record;

};

RollResponse rollDie(int numDie, int size, int max = 0, int min = 1, int modifier = 0)
{
	if (max == 0)
		max = size;

	RollResponse roll;
	std::stringstream rec;
	rec.str("");

	int num = modifier;


	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, max); 



	rec << numDie << "d" << size << " (";
	for (unsigned int i = 0; i < numDie; i++)
	{

		int value = dist(rng);


		if (value < min)
		{
			rec << value << " -> " << min;
			value = min;
		}
		else
			rec << value;

		//Not last in sequence.
		if (i + 1 < numDie)
		{
			rec << ", ";
		}
		else if (modifier != 0)
		{
			rec << ") + " << modifier << "\n";

		}
		else
		{
			rec << ")\n";
		}
		num += value;


	}

	rec << "= " << num << "\n";
	roll.record = rec.str();
	roll.value = num;
	return roll;
}



class Spells
{

public:
	static RollResponse ScorchingRay(int level)
	{
		if (level >= 2)
		{
			int numRays = 3 + (level - 2);

			//These are what we pass at the end.
				std::string record = "";
				int damage = 0;


			for (unsigned int i = 0; i < numRays; i++)
			{
				//The response text
				std::string t = "Ray " + std::to_string(i+1) + ": " "\n";
				//Roll

				
				RollResponse hitroll = rollDie(1, 20, 20, 1, 7); //Each dice roll has a string component for output- giving details about the roll.
				record = record + t + hitroll.record + "\n"; //So here, I'm just adding the hit roll details to the end of the base string, and linebreaking.

				
				RollResponse damageRoll = rollDie(2, 6, 6, 2, 5); //Same as before, just with the damage roll instead.
				record = record + damageRoll.record;

				damage += damageRoll.value;

				//Line break at the end.
				record = record + "\n";
		
			}

			//Putting it all in one wrapper to return
			RollResponse total;
			record = record + "\n TOTAL: " + std::to_string(damage) + "\n";
			total.record = record;
			total.value = damage;


			return total;




		}
	
	};

	
};

#endif