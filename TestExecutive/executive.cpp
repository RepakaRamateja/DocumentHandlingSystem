#include "../Requirement1/FirstRequirement.h"
#include "../Requirement2/Requirement2.h" 
#include"../Requirement3Hashmap/invertedindex.h"
int main()
{
	//NOTE PLEASE CHECK ONE REQUIREMENT BY OTHER AS YOU CAN SEE THE OUTPUT VERY CLEARLY
	std::cout << "\n-------------demonstartion of first requirement-------------------\n";
	
	firstrequirement require;
	require.requirementone();

	std::cout << "\n--------------demonstration of second requirement-------------------\n";
	
	Secondrequirement require2;
	require2.secondrequirement();

	//3rd requirement demo

	invertedindex index;
	index.thirdrequirement();

	return 0;
}