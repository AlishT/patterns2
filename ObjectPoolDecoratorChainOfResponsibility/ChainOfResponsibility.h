#pragma once
#include <iostream>
#include <string>
#include <memory>

class Handler 
{
public:
	Handler() {}
	
	virtual void HandleRequest(int value) = 0;
};

class AtmHandler : Handler
{
	std::shared_ptr<AtmHandler> successor;

public:
	AtmHandler(std::shared_ptr<AtmHandler> _successor = nullptr) :
		successor(_successor)
	{}

	~AtmHandler()
	{}

	void HandleRequest(int value) override 
	{
		if (successor) 
		{
			successor->HandleRequest(value);
		}
	};
};

class Dollar100Handler : public AtmHandler 
{
	public:
		Dollar100Handler(std::shared_ptr<AtmHandler> _successor = nullptr) :
			AtmHandler(_successor)
		{}

		void HandleRequest(int value) override
		{
			if (value % 100 == 0)
			{
				std::cout << "Number of 100 Dollar:" << value / 100 << std::endl;
				std::cout << "Request is completed!" << std::endl;
			}
			else 
			{
				std::cout << "Number of 100 Dollar:" << value / 100 << std::endl;
				value = value - (value / 100) * 100;
				AtmHandler::HandleRequest(value);
			}
		}
};

class Dollar50Handler : public AtmHandler
{
public:
	Dollar50Handler(std::shared_ptr<AtmHandler> _successor = nullptr) :
		AtmHandler(_successor) 
	{}

	void HandleRequest(int value) override
	{
		if (value % 50 == 0)
		{
			std::cout << "Number of 50 Dollar:" << value / 50 << std::endl;
			std::cout << "Request is completed!" << std::endl;
		}
		else
		{
			std::cout << "Number of 50 Dollar:" << value / 50 << std::endl;
			value = value - (value / 50) * 50;
			AtmHandler::HandleRequest(value);
		}
	}
};

class Dollar20Handler : public AtmHandler
{
public:
	Dollar20Handler(std::shared_ptr<AtmHandler> _successor = nullptr) :
		AtmHandler(_successor)
	{}

	void HandleRequest(int value) override
	{
		if (value % 20 == 0)
		{
			std::cout << "Number of 20 Dollar:" << value / 20 << std::endl;
			std::cout << "Request is completed!" << std::endl;
		}
		else
		{
			std::cout << "Number of 20 Dollar:" << value / 20 << std::endl;
			value = value - (value / 20) * 20;
			AtmHandler::HandleRequest(value);
		}
	}
};


class Dollar10Handler : public AtmHandler
{
public:
	Dollar10Handler(std::shared_ptr<AtmHandler> _successor = nullptr) :
		AtmHandler(_successor)
	{}

	void HandleRequest(int value) override
	{
		if (value % 10 == 0)
		{
			std::cout << "Number of 10 Dollar:" << value / 10 << std::endl;
			std::cout << "Request is completed!" << std::endl;
		}
		else
		{
			std::cout << "Have not 10 Dollar!" << std::endl;
		}
	}
};