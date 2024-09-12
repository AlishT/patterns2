#pragma once
#include<iostream>
#include<vector>
#include<memory>

class Bullet 
{
private:
	int value;

public:
	Bullet() 
	{
		value = 0;
	}

	void reset()
	{
		value = 0;
	}

	void setValue(const int number)  
	{
		value = number;
	}

	int getValue() const 
	{
		return value;
	}
};

class RoundMag
{
private:
	const unsigned int capacity;
	unsigned int currentlySpawned;
	unsigned int objectsToSpawn;
	std::vector<Bullet*> bullets;
	std::vector<bool> freeBulletsFlags;
public:
	enum class Result
	{
		Ok,
		NoBullesInMag
	};

public:
	RoundMag() = delete;
	RoundMag(const RoundMag&) = delete;
	RoundMag(RoundMag&&) = delete;

	RoundMag(unsigned int value) : 
		capacity(value),
		bullets(value, nullptr),
		freeBulletsFlags(value, true)
	{
		Reload();
	}

	~RoundMag() 
	{
		for (unsigned int i = 0; i < capacity; i++) 
		{
			delete bullets.at(i);
		}
	}

	std::pair<RoundMag::Result, std::vector<Bullet*>> GetFreeBullets(unsigned int value) 
	{
		std::vector<Bullet*> _bullets;
		
		while (!HasEnoughFreeBullets(value) && Reload()) // Перевіряємо на достаність куль - поки не достаньо куль доспавнюємо.
		{}
		
		if (!HasEnoughFreeBullets(value))// якщо не достатньо, або релауд не вдався, чи нема вже куди, видає помилку та виходимо з функції.
		{
			return
			{
				 Result::NoBullesInMag, _bullets
			};
		}
		
		_bullets.reserve(value);

		for (unsigned int i = 0; i < currentlySpawned; i++) // якщо пройшли всі перевірки, то видаємо кулі та відмічаємо влажок, що пусто. 
		{
			if (freeBulletsFlags[i])
			{
				_bullets.push_back(bullets[i]);
				freeBulletsFlags[i] = false;

				if (_bullets.size() == value)
				{
					break;
				}
			}
		}
		
		return
		{
			 Result::Ok, _bullets
		};
	}

	void ReleaseBullet(Bullet* bullet)
	{
		if (!bullets.empty())
		{
			for (unsigned int i = 0; i < currentlySpawned; i++)
			{
				if (bullets[i] == bullet)
				{
					freeBulletsFlags[i] = false;
					break;
				}
			}
		}
	}

private:
	bool Reload()
	{
		if (capacity == currentlySpawned)
		{
			return false;
		}
		
		const unsigned int stillCanSpawn = capacity - currentlySpawned;
		objectsToSpawn = capacity / 3;

		if((stillCanSpawn - objectsToSpawn) < objectsToSpawn)
		{
			objectsToSpawn = stillCanSpawn;
		}
		
		for (unsigned int i = 0; i < objectsToSpawn; i++)	
		{
			bullets[i] = new Bullet();
			currentlySpawned++;
		}
		std::cout << "Spawned "<< currentlySpawned << std::endl;
		return true;
	}

	bool HasEnoughFreeBullets(int num) const
	{
		int numFreeBullets = 0;
		for (unsigned int i = 0; i < currentlySpawned; i++)
		{
			if (freeBulletsFlags[i])
			{
				numFreeBullets++;
			}
		}

		return numFreeBullets >= num;
	}
};



