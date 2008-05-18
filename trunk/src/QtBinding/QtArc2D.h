#ifndef QtArc2DH
#define QtArc2DH

#include "QtPrimitiveBase.h"

// line class
class QtArc2D : public QtPrimitiveBase, public Arc2D
{
	public:
		QtArc2D (QGraphicsItem * parent, double s_center, double t_center, double theta_1, double theta_2, double radius, 
			      SketchPlanePointer sketch_plane, bool s_center_free = false, bool t_center_free = false, bool theta_1_free = false, bool theta_2_free = false, 
			      bool radius_free = false);
		QtArc2D (QGraphicsItem * parent,DOFPointer s_center, DOFPointer t_center, DOFPointer theta_1, DOFPointer theta_2, DOFPointer radius, SketchPlanePointer sketch_plane);

		void Display() {return QtPrimitiveBase::Display();}
		bool IsSelected() {return QtPrimitiveBase::IsSelected();}
		void SetSelectable(bool input_selectable) {PrimitiveBase::SetSelectable(input_selectable); QtPrimitiveBase::SetSelectable(selectable_);}

		void UpdateDisplay();

		virtual QRectF boundingRect() const;
		virtual void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

	private:

};
typedef boost::shared_ptr<QtArc2D> QtArc2DPointer;



#endif //QtArc2DH
