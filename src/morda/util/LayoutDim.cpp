#include "LayoutDim.hpp"
#include "../widgets/PaddedWidget.hpp"
#include "../widgets/Container.hpp"



using namespace morda;



namespace{

const char* D_Min = "min";
const char* D_Layout = "layout";

inline bool NodeHoldsFractionValue(const stob::Node& node)throw(){
	size_t len = node.ValueLength();
	return len != 0 && node.Value()[len - 1] == '%';
}

}//~namespace


//static
LayoutDim LayoutDim::FromSTOB(const stob::Node& node)throw(){
	LayoutDim ret;
	
	const stob::Node* n = node.Child();
	
	for(unsigned i = 0; i != 2; ++i){
		if(!n){
			ret[i].unit = MIN;
			continue;
		}
		
		if(*n == D_Min){
			ret[i].unit = MIN;
		}else if(NodeHoldsFractionValue(*n)){
			ret[i].unit = FRACTION;
			ret[i].value = n->AsFloat() / 100;
		}else{
			ret[i].unit = PIXEL;
			ret[i].value = n->AsFloat();
		}
		
		n = n->Next();
	}
	
	return ret;
}



//static
LayoutDim LayoutDim::FromLayout(const stob::Node& layout)throw(){
	const stob::Node* dim = layout.Child(LayoutDim::D_Dim()).node();
	if(!dim){
		return LayoutDim::Default();
	}
	return LayoutDim::FromSTOB(*dim);
}



//static
LayoutDim LayoutDim::FromPropLayout(const stob::Node& prop)throw(){
	const stob::Node* layout = prop.Child(D_Layout).node();
	if(!layout){
		return LayoutDim::Default();
	}
	return LayoutDim::FromLayout(*layout);
}



Vec2f LayoutDim::ForWidget(const Widget& w)const throw(){
	Vec2f ret;
	
	for(unsigned i = 0; i != 2; ++i){
		const Value& v = this->operator[](i);
		
		switch(v.unit){
			case PIXEL:
				ret[i] = v.value;
				break;
			case FRACTION:
				if(ting::Ref<const Container> p = w.Parent()){
					float padding;
					if(ting::Ref<const PaddedWidget> pw = p.DynamicCast<const PaddedWidget>()){
						padding = pw->Padding()[i] + pw->Padding()[i + 2];
					}else{
						padding = 0;
					}
					ret[i] = v.value * (p->Rect().d[i] - padding);
					ting::util::ClampBottom(ret[i], 0.0f);
				}else{
					ret[i] = 0;
				}
				break;
			default:
			case MIN:
				ret[i] = w.GetMinDim()[i];
				break;
		}
	}
	
	return ret;
}