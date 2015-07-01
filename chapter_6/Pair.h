/*
* Author : StrayWarrior
* Solution to 6.5-9
*
*/
#include <utility>

template <typename TFirst, typename TSecond>
class PairKey{
public:
	TFirst & operator()(const std::pair<TFirst, TSecond> & obj){
		return (TFirst &)obj.first;
	}
};