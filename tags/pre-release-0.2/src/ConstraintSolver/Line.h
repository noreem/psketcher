#ifndef LineH
#define LineH

#include "PrimitiveBase.h"
#include "Point.h"

// line class
class Line : public PrimitiveBase
{
	public:
		Line (const PointPointer point1, const PointPointer point2);

		DOFPointer GetX1()const {return x1_;}
		DOFPointer GetY1()const {return y1_;}
		DOFPointer GetZ1()const {return z1_;}
		DOFPointer GetX2()const {return x2_;}
		DOFPointer GetY2()const {return y2_;}
		DOFPointer GetZ2()const {return z2_;}

		virtual void ApplySelectionMask(SelectionMask mask);

	private:
		DOFPointer x1_;
		DOFPointer y1_;
		DOFPointer z1_;
		DOFPointer x2_;
		DOFPointer y2_;
		DOFPointer z2_;
};
typedef boost::shared_ptr<Line> LinePointer;


#endif //LineH
