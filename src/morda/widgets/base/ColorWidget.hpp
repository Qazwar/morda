#pragma once

#include "../Widget.hpp"


namespace morda{


/**
 * @brief Basic widget which has a color setting.
 * 
 * @param color - color value.
 */
class ColorWidget : public virtual Widget{
	std::uint32_t color_v;
	
protected:
	ColorWidget(const stob::Node* chain);
	
public:
	ColorWidget(const ColorWidget&) = delete;
	ColorWidget& operator=(const ColorWidget&) = delete;
	
	
	void setColor(std::uint32_t color){
		if(this->color_v == color){
			return;
		}
		
		this->color_v = color;
		this->clearCache();
	}
	
	std::uint32_t color()const noexcept{
		return this->color_v;
	}
};


}
