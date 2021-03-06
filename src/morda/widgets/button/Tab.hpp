#pragma once

#include "../label/NinePatch.hpp"
#include "ChoiceButton.hpp"
#include "NinePatchToggle.hpp"

namespace morda{
class Tab :
		public ChoiceButton,
		public NinePatchToggle
{
	bool maskOverlaps(Vec2r pos);
	
public:
	Tab(const stob::Node* chain);
	
	Tab(const Tab&) = delete;
	Tab& operator=(const Tab&) = delete;
	
protected:	
	bool onMouseButton(bool isDown, const morda::Vec2r& pos, MouseButton_e button, unsigned pointerId) override;

	void onHoverChanged(unsigned pointerID) override{}
	
	void onPressedChanged() override;
};
}
