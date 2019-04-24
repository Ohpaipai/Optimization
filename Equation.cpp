#include "Equation.h"



void Linklist::PrintList()
{
	try {
		if (Lfirst == NULL)
		{
			throw("Empty");
		}

		ListNode *Lcurrent = Lfirst;
		while (1)
		{
			ListVariables *Vcurrent = Vfirst->Vnext;
			std::cout << Lcurrent->coefficient;
			while (Vcurrent!=NULL)
			{
				if (Vcurrent->name != "c")
					std::cout << Vcurrent->name << "^" << Vcurrent->exponential;
				
				Vcurrent = Vcurrent->Vnext;
			}
			Lcurrent = Lcurrent->Lnext;
			if (Lcurrent == NULL) break;
			else std::cout << " + ";
		}

		std::cout << std::endl;
	}
	catch (std::string gra)
	{
		std::cout << gra << std::endl;
	}

}

void Linklist::Push_front(double _coe)
{
	ListNode *newLNode = new ListNode(_coe);

}
