#ifndef QtParallelLine2DH
#define QtParallelLine2DH

#include "QtPrimitiveBase.h"

class QtParallelLine2D : public QtPrimitiveBase, public ParallelLine2D
{
	public:
		QtParallelLine2D (QGraphicsItem * parent,
																			 const Line2DPointer line1, const Line2DPointer line2);

		void Display() {return QtPrimitiveBase::Display();}
		bool IsSelected() {return QtPrimitiveBase::IsSelected();}
		void SetSelectable(bool input_selectable) {PrimitiveBase::SetSelectable(input_selectable); QtPrimitiveBase::SetSelectable(selectable_);}

		void UpdateDisplay();

		virtual QRectF boundingRect() const;
		virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

	private:

};
typedef boost::shared_ptr<QtParallelLine2D> QtParallelLine2DPointer;


#endif //QtParallelLine2DH
