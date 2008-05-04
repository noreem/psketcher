#include "DistancePoint2D.h"

#include "IndependentDOF.h"

using namespace std;
using namespace GiNaC;

// Create a constraint that defines the distance between two points confined to a sketch plane
DistancePoint2D::DistancePoint2D(const Point2DPointer point1, const Point2DPointer point2, double distance):
point1_(point1),
point2_(point2)
{
	// Create a DOF for the distance parameter
	DOFPointer new_dof(new IndependentDOF(distance,false));
	distance_ = new_dof;

	dof_list_.push_back(distance_);

	// create the expression that defines the constraint and add it the the constraint list
	boost::shared_ptr<ex> new_constraint(new ex);
	
	*new_constraint = sqrt( pow(point1->GetSDOF()->GetVariable() - point2->GetSDOF()->GetVariable(),2) +
													pow(point1->GetTDOF()->GetVariable() - point2->GetTDOF()->GetVariable(),2))
										- distance_->GetVariable();

	cout << *new_constraint << endl;

	constraints_.push_back(new_constraint);
	weight_list_.push_back(1.0);
}

// Calculate the current actual distance between the two points
// This method is used to set the distance when graphically generating a distance constraint
double DistancePoint2D::GetActualDistance()
{
		// calculate the distance between point1_ and point2_
		double term1 = (point1_->GetSDOF()->GetValue() - point2_->GetSDOF()->GetValue());
		term1 = term1*term1;
		double term2 = (point1_->GetTDOF()->GetValue() - point2_->GetTDOF()->GetValue());
		term2 = term2*term2;

		return sqrt(term1+term2);
}
