#pragma once

#include "../Widget.hpp"

namespace morda{
class FractionWidget : public virtual Widget{
	float fraction_v = 0; //Current position from 0 to 1
protected:
	FractionWidget(const stob::Node* chain) :
			Widget(chain)
	{}
	
	virtual void onFractionChange();
public:
	std::function<void(FractionWidget&)> fractionChange;
	
	real fraction()const noexcept{
		return this->fraction_v;
	}
	
	void setFraction(float newFraction);
};
}