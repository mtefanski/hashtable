#include <string>
#include <iostream>

class tablica
{
private:

	long key;
	std::string value;
	char flag;

public:

	tablica()
		:
		key(0),
		value(" "),
		flag('E')
	{
	}

	void setKey(long key_)
	{
		key = key_;
	}

	void setValue(std::string value_)
	{
		value = value_;
	}

	void setFlag(char flag_)
	{
		flag = flag_;
	}

	long getKey()
	{
		return key;
	}

	std::string getValue()
	{
		return value;
	}

	char getFlag()
	{
		return flag;
	}

	tablica getTablica()
	{
		std::cout << key << " " << value << std::endl;
		return *this;
	}

};

class HT
{
private:
	tablica * tab;
	int size;
public:
	HT()
		:
		size(0)
	{
	}

	~HT()
	{
		if(tab)
			delete[] tab;
	}

	void Size(int size_)
	{
		if (size != size_)
		{

			size = size_;
			tab = new tablica[size];
			for (int i = 0; i < size; i++)
			{
				tab[i].setKey(0);
				tab[i].setValue(" ");
				tab[i].setFlag('E');
			};
		}
	}

	void Add(long key_, std::string value_)
	{
		int index = hash(key_);
		bool flag = false;

		do {

			if (tab[index].getValue() == " ")
			{
				tab[index].setKey(key_);
				tab[index].setValue(value_);
				tab[index].setFlag('F');
				flag = true;
			}
			else
			{
				tab[index].setFlag('C');

				index++;

				if (index == size)
					index = 0;
			}

		} while (flag != true);
	}

	void Print()
	{

		for (int i = 0; i < size; i++)
		{
			if (tab[i].getValue() != " ")
			{
				std::cout << i << " ";
				tab[i].getTablica();
			}
		}
		std::cout << std::endl;
	}

	void Delete(long key_)
	{
		int index = hash(key_);
		int deleted = 0;

		//usuwanie elementu o podanym kluczu
		while (tab[index].getFlag() != 'E')
		{
			if (tab[index].getKey() == key_ && tab[index].getValue() != " ")
			{
				tab[index].setKey(0);
				tab[index].setValue(" ");
				deleted = index;
				break;
			}
			else
			{
				index++;
				if (index == size)
					index = 0;
			}
		}
		//___

		//ile elementow o zadanym hashu jest w lancuchu?
		int elementow = 0;
		int ostatni = 0;

		while (tab[index].getFlag() != 'E')
		{
			if (hash(tab[index].getKey()) == hash(key_) && tab[index].getValue() != " ")
			{
				elementow++;
				ostatni = index;
			}

			if (tab[index].getFlag() == 'F')
				break;

			index++;
			if (index == size)
				index = 0;
		}
		//_

		//relokacja elemetow
		if (elementow == 1)
		{
			Add(tab[ostatni].getKey(), tab[ostatni].getValue());
			tab[ostatni].setKey(0);
			tab[ostatni].setValue(" ");
		}
		else if (elementow > 1)
		{
			Add(tab[ostatni].getKey(), tab[ostatni].getValue());
			tab[deleted].setFlag('C');
			tab[ostatni].setKey(0);
			tab[ostatni].setValue(" ");
		}
		//___
		ustawFlagi(ostatni);
	}

	void ustawFlagi(int index_)
	{
		if (tab[index_].getFlag() == 'F')
		{
			tab[index_].setFlag('E');
			tab[index_ - 1].setFlag('F');
		}
		else if (tab[index_].getFlag() == 'C')
		{

			index_++;
			while (tab[index_].getFlag() != 'E')
			{
				if (hash(tab[index_].getKey()) != index_)
				{
					Add(tab[index_].getKey(), tab[index_].getValue());
					tab[index_].setKey(0);
					tab[index_].setValue(" ");
					ustawFlagi(index_);
				}

				if (tab[index_].getFlag() == 'F')
					break;

				index_++;
				if (index_ == size)
					index_ = 0;
			}
		}
	}

	int hash(long key_)
	{
		return key_ % size;
	}
};

int main()
{
	int licznik = 0;
	int liczba_przypadkow;
	
	std::cin >> liczba_przypadkow;
	
	while (licznik < liczba_przypadkow)
	{
		HT ht_;
		std::string komenda;
		while (komenda != "stop")
		{
			std::getline(std::cin, komenda);
			if (komenda[0] == 's' && komenda[1] == 'i' && komenda[2] == 'z' && komenda[3] == 'e')
			{
				std::string st_liczba;

				for (int i = 5; i < komenda.length(); i++)
				{
					st_liczba += komenda[i];
				}
				int size = std::stoi(st_liczba);
				ht_.Size(size);
			}
			else if (komenda[0] == 'a' && komenda[1] == 'd' && komenda[2] == 'd')
			{
				std::string st_key;
				std::string value;
				int i = 4;
				while (komenda[i] != ' ')
				{
					st_key += komenda[i];
					i++;
				}
				long key = std::stol(st_key);
				
				for (i++; i < komenda.length(); i++)
				{
					value += komenda[i];
				}
				ht_.Add(key, value);
			}
			else if (komenda == "print")
			{
				ht_.Print();
			}
			else if (komenda[0] == 'd' && komenda[1] == 'e' && komenda[2] == 'l' && komenda[3] == 'e' && komenda[4] == 't' && komenda[5] == 'e')
			{
				std::string st_key;
				for (int i = 7; i < komenda.length(); i++)
				{
					st_key += komenda[i];
				}
				long key = std::stol(st_key);
				ht_.Delete(key);
			}
		}
		licznik++;
	}

	system("pause");
	return 0;
}