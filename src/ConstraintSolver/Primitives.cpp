#include "Primitives.h"

using namespace std;
using namespace GiNaC;

IndependentDOF ::IndependentDOF ( double value, bool free):
DOF(free,false /*dependent*/)
{
	value_=value;
}

IndependentDOF :: IndependentDOF ( const char *name, double value, bool free):
DOF(name,free,false /*dependent*/)
{
	value_ = value;
}

DependentDOF :: DependentDOF (ex expression, std::vector<DOFPointer> source_dof_list):
DOF(false /*free*/,true /*dependent*/)
{
	// @fixme Need to make sure that all DOF's in expression are included in the DOF list
	expression_ = expression;
	source_dof_list_ = source_dof_list;
}

DependentDOF :: DependentDOF ( const char *name, ex expression, std::vector<DOFPointer> source_dof_list):
DOF(name,false /*free*/,true /*dependent*/)
{
	// @fixme Need to make sure that all DOF's in expression are included in the DOF list
	expression_ = expression;
	source_dof_list_ = source_dof_list;
}

double DependentDOF::GetValue()const
{
	// For each independent DOF in the list, substitute its value into the expression that defines this dependent DOF
	GiNaC::ex current_expression = GetExpression();
	double result;

	for(unsigned int current_dof = 0; current_dof < source_dof_list_.size(); current_dof++)
	{
		if(!source_dof_list_[current_dof]->IsDependent())
		{
			current_expression = current_expression.subs(source_dof_list_[current_dof]->GetVariable() ==
														 source_dof_list_[current_dof]->GetValue(),subs_options::no_pattern);
		}
	}

	// Now evaluate the expression to a numeric value
	// check to make sure the expression evaluates to a numeric value
	if (is_a<numeric>(current_expression)) {
		result = ex_to<numeric>(current_expression).to_double();
	} else {
		throw PrimitiveException();
  	}

	return result;
}

GiNaC::ex DependentDOF::GetExpression()const
{
	// For each dependent DOF in the list, substitute its expression into the overall expression that defines this dependent DOF
	GiNaC::ex result = expression_;

	for(unsigned int current_dof = 0; current_dof < source_dof_list_.size(); current_dof++)
	{
		if(source_dof_list_[current_dof]->IsDependent())
		{
			result = result.subs(source_dof_list_[current_dof]->GetVariable() == source_dof_list_[current_dof]->GetExpression(),subs_options::no_pattern);
		}
	}

	return result;
}

Point :: Point ( double x, double y, double z, bool x_free, bool y_free, bool z_free):
x_(new IndependentDOF(x,x_free)),
y_(new IndependentDOF(y,y_free)),
z_(new IndependentDOF(z,z_free))
{
	dof_list_.push_back(x_);
	dof_list_.push_back(y_);
	dof_list_.push_back(z_);
}

Point2D :: Point2D ( double s, double t, SketchPlanePointer sketch_plane, bool s_free, bool t_free):
s_(new IndependentDOF(s,s_free)),
t_(new IndependentDOF(t,t_free)),
Primitive2DBase(sketch_plane)
{
	dof_list_.push_back(s_);
	dof_list_.push_back(t_);
}

Point2D :: Point2D ( DOFPointer s, DOFPointer t, SketchPlanePointer sketch_plane):
s_(s),
t_(t),
Primitive2DBase(sketch_plane)
{
	dof_list_.push_back(s_);
	dof_list_.push_back(t_);
}

Line :: Line(const PointPointer point1, const PointPointer point2)
{
	x1_ = point1->GetXDOF();
	y1_ = point1->GetYDOF();
	z1_ = point1->GetZDOF();

	x2_ = point2->GetXDOF();
	y2_ = point2->GetYDOF();
	z2_ = point2->GetZDOF();

	dof_list_.push_back(x1_);
	dof_list_.push_back(y1_);
	dof_list_.push_back(z1_);

	dof_list_.push_back(x2_);
	dof_list_.push_back(y2_);
	dof_list_.push_back(z2_);
}

Line2D :: Line2D(const Point2DPointer point1, const Point2DPointer point2, SketchPlanePointer sketch_plane):
Primitive2DBase(sketch_plane)
{
	s1_ = point1->GetSDOF();
	t1_ = point1->GetTDOF();

	s2_ = point2->GetSDOF();
	t2_ = point2->GetTDOF();

	dof_list_.push_back(s1_);
	dof_list_.push_back(t1_);

	dof_list_.push_back(s2_);
	dof_list_.push_back(t2_);
}

// returns global coordinates of line end points
void Line2D :: Get3DLocations(double & x1, double & y1, double & z1,
															double & x2, double & y2, double & z2)
{
	sketch_plane_->Get3DLocation(s1_->GetValue(), t1_->GetValue(), x1, y1, z1);
	sketch_plane_->Get3DLocation(s2_->GetValue(), t2_->GetValue(), x2, y2, z2);
}


// Create a constraint that defines the distance between two points
DistancePoint::DistancePoint(const PointPointer point1, const PointPointer point2, double distance)
{
	// Create a DOF for the distance parameter
	DOFPointer new_dof(new IndependentDOF(distance,false));
	
	dof_list_.push_back(new_dof);

	// create the expression that defines the constraint and add it the the constraint list
	boost::shared_ptr<ex> new_constraint(new ex);
	
	*new_constraint = sqrt( pow(point1->GetXDOF()->GetVariable() - point2->GetXDOF()->GetVariable(),2) +
													pow(point1->GetYDOF()->GetVariable() - point2->GetYDOF()->GetVariable(),2) +
													pow(point1->GetZDOF()->GetVariable() - point2->GetZDOF()->GetVariable(),2))
										- new_dof->GetVariable();

	constraints_.push_back(new_constraint);
	weight_list_.push_back(1.0);
}

// Create a constraint that defines the distance between two points confined to a sketch plane
DistancePoint2D::DistancePoint2D(const Point2DPointer point1, const Point2DPointer point2, double distance):
point1_(point1),
point2_(point2),
distance_(distance)
{
	// Create a DOF for the distance parameter
	DOFPointer new_dof(new IndependentDOF(distance,false));
	
	dof_list_.push_back(new_dof);

	// create the expression that defines the constraint and add it the the constraint list
	boost::shared_ptr<ex> new_constraint(new ex);
	
	*new_constraint = sqrt( pow(point1->GetSDOF()->GetVariable() - point2->GetSDOF()->GetVariable(),2) +
													pow(point1->GetTDOF()->GetVariable() - point2->GetTDOF()->GetVariable(),2))
										- new_dof->GetVariable();

	constraints_.push_back(new_constraint);
	weight_list_.push_back(1.0);
}

// Create a parallelism constrain between two lines
ParallelLine::ParallelLine(const LinePointer line1, const LinePointer line2)
{
	// create the expression that defines the parallel constraint and add it the the constraint list
	boost::shared_ptr<ex> new_constraint(new ex);
	
	ex line1_dx = line1->GetX1()->GetVariable() - line1->GetX2()->GetVariable();
	ex line1_dy = line1->GetY1()->GetVariable() - line1->GetY2()->GetVariable();
	ex line1_dz = line1->GetZ1()->GetVariable() - line1->GetZ2()->GetVariable();
	ex line1_length = sqrt(pow(line1_dx,2)+pow(line1_dy,2)+pow(line1_dz,2));

	ex line2_dx = line2->GetX1()->GetVariable() - line2->GetX2()->GetVariable();
	ex line2_dy = line2->GetY1()->GetVariable() - line2->GetY2()->GetVariable();
	ex line2_dz = line2->GetZ1()->GetVariable() - line2->GetZ2()->GetVariable();
	ex line2_length = sqrt(pow(line2_dx,2)+pow(line2_dy,2)+pow(line2_dz,2));

	// Calculate the dot product normalized by the vector lengths and subtract one
	// this expression will be zero when the lines are parallel
	// Ideally, I would use abs() instead of pow() but abs is not differentiable. 
	// @todo find a better function besides pow to use for the parallel constraint
	*new_constraint = pow((1/(line1_length*line2_length))*(line1_dx*line2_dx + line1_dy*line2_dy + line1_dz*line2_dz),2)-1;

	constraints_.push_back(new_constraint);
	weight_list_.push_back(1.0);
}


// Create a parallelism constrain between two lines
ParallelLine2D::ParallelLine2D(const Line2DPointer line1, const Line2DPointer line2):
line1_(line1),
line2_(line2)
{
	// create the expression that defines the parallel constraint and add it the the constraint list
	boost::shared_ptr<ex> new_constraint(new ex);
	
	ex line1_ds = line1->GetS1()->GetVariable() - line1->GetS2()->GetVariable();
	ex line1_dt = line1->GetT1()->GetVariable() - line1->GetT2()->GetVariable();
	ex line1_length = sqrt(pow(line1_ds,2)+pow(line1_dt,2));

	ex line2_ds = line2->GetS1()->GetVariable() - line2->GetS2()->GetVariable();
	ex line2_dt = line2->GetT1()->GetVariable() - line2->GetT2()->GetVariable();
	ex line2_length = sqrt(pow(line2_ds,2)+pow(line2_dt,2));

	// Calculate the dot product normalized by the vector lengths and subtract one
	// this expression will be zero when the lines are parallel
	// Ideally, I would use abs() instead of pow() but abs is not differentiable. 
	*new_constraint = pow((1/(line1_length*line2_length))*(line1_ds*line2_ds + line1_dt*line2_dt),2)-1;

	constraints_.push_back(new_constraint);
	weight_list_.push_back(1.0);
}


// Constructor for SketchPlane class
SketchPlane::SketchPlane ( VectorPointer normal, VectorPointer up, PointPointer base):
normal_(normal),
up_(up),
base_(base)
{
	// @TODO need to check to insure that the normal vector and the up vector are normalized, calculations later on will assume this

	// @TODO need to make sure that up vector lies in plane defined by normal vector (up vector must be orthogonal to normal vector)

	// Populate the primitve base classes DOF list for each of the primitives referenced by this SketchPlane
	std::vector<DOFPointer> current_dof_list = normal_->GetDOFList();
	for(unsigned int current_dof = 0; current_dof < current_dof_list.size(); current_dof++)
	{
		dof_list_.push_back(current_dof_list[current_dof]);
	}

	current_dof_list = up_->GetDOFList();
	for(unsigned int current_dof = 0; current_dof < current_dof_list.size(); current_dof++)
	{
		dof_list_.push_back(current_dof_list[current_dof]);
	}

	current_dof_list = base_->GetDOFList();
	for(unsigned int current_dof = 0; current_dof < current_dof_list.size(); current_dof++)
	{
		dof_list_.push_back(current_dof_list[current_dof]);
	}
}

void SketchPlane::GetABCD ( double & coef_a, double & coef_b, double & coef_c, double & coef_d)
{
	mmcMatrix normal_vector = normal_->GetmmcMatrix();
	mmcMatrix base_vector = base_->GetmmcMatrix();

	coef_a = normal_vector(0,0);
	coef_b = normal_vector(1,0);
	coef_c = normal_vector(2,0);
	coef_d = normal_vector.DotProduct(base_vector);
}

// Return the global coordinates of a point on the sketch plane
void SketchPlane::Get3DLocation ( double s, double t, double & x, double & y, double & z)
{
	mmcMatrix j_vector = up_->GetmmcMatrix();  // t axis direction vector in sketch plane
	mmcMatrix i_vector = j_vector.CrossProduct(normal_->GetmmcMatrix()); // s axis direction vector in sketch plane

	mmcMatrix global_position = base_->GetmmcMatrix() + s*i_vector + t*j_vector;

	x = global_position(0,0);
	y = global_position(1,0);
	z = global_position(2,0);
}

// Return the global coordinates for a Point2D object
void Point2D::Get3DLocation(double & x_location,double & y_location, double & z_location)const
{
	sketch_plane_->Get3DLocation(s_->GetValue(), t_->GetValue(), x_location, y_location, z_location);
}

// Return mmaMatrix vector of current x,y,z values
// used for numerical calculations only, loses associativity with DOF's
mmcMatrix Vector::GetmmcMatrix()
{
	mmcMatrix result(3,1);

	result(0,0) = x_->GetValue();
	result(1,0) = y_->GetValue();
	result(2,0) = z_->GetValue();

	return result;
}

// Return mmaMatrix vector of current x,y,z values
// used for numerical calculations only, loses associativity with DOF's
mmcMatrix Point::GetmmcMatrix()
{
	mmcMatrix result(3,1);

	result(0,0) = x_->GetValue();
	result(1,0) = y_->GetValue();
	result(2,0) = z_->GetValue();

	return result;
}

Vector :: Vector ( double x, double y, double z, bool x_free, bool y_free, bool z_free):
x_(new IndependentDOF(x,x_free)),
y_(new IndependentDOF(y,y_free)),
z_(new IndependentDOF(z,z_free))
{
	dof_list_.push_back(x_);
	dof_list_.push_back(y_);
	dof_list_.push_back(z_);
}



// Create an angle constraint between two lines
AngleLine2D::AngleLine2D(const Line2DPointer line1, const Line2DPointer line2, double angle /* radians */):
line1_(line1),
line2_(line2),
angle_(angle)
{
	// Create a DOF for the angle parameter
	DOFPointer new_dof(new IndependentDOF(angle_,false));
	
	dof_list_.push_back(new_dof);

	// create the expression that defines the parallel constraint and add it the the constraint list
	boost::shared_ptr<ex> new_constraint(new ex);
	
	ex line1_ds = line1->GetS1()->GetVariable() - line1->GetS2()->GetVariable();
	ex line1_dt = line1->GetT1()->GetVariable() - line1->GetT2()->GetVariable();
	ex line1_length = sqrt(pow(line1_ds,2)+pow(line1_dt,2));

	ex line2_ds = line2->GetS1()->GetVariable() - line2->GetS2()->GetVariable();
	ex line2_dt = line2->GetT1()->GetVariable() - line2->GetT2()->GetVariable();
	ex line2_length = sqrt(pow(line2_ds,2)+pow(line2_dt,2));

	ex desired_angle = new_dof->GetVariable();

	// Calculate the dot product normalized by the vector lengths and subtract the cos of the desired angle
	// this expression will be zero when the lines are at the desired angle
	*new_constraint = (1/(line1_length*line2_length))*(line1_ds*line2_ds + line1_dt*line2_dt)-cos(mmcPI-desired_angle);

	constraints_.push_back(new_constraint);
	weight_list_.push_back(1.0);
}


// create an arc
Arc2D::Arc2D (double s_center, double t_center, double theta_1, double theta_2, double radius, SketchPlanePointer sketch_plane,
			  bool s_center_free, bool t_center_free, bool theta_1_free, bool theta_2_free, bool radius_free):
s_center_(new IndependentDOF(s_center,s_center_free)),
t_center_(new IndependentDOF(t_center,t_center_free)),
theta_1_(new IndependentDOF(theta_1,theta_1_free)),
theta_2_(new IndependentDOF(theta_2,theta_2_free)),
radius_(new IndependentDOF(radius,radius_free)),
Primitive2DBase(sketch_plane)
{
	dof_list_.push_back(s_center_);
	dof_list_.push_back(t_center_);
	dof_list_.push_back(theta_1_);
	dof_list_.push_back(theta_2_);
	dof_list_.push_back(radius_);
}

void Arc2D::Get3DLocations(double & x_center, double & y_center, double & z_center)
{
	sketch_plane_->Get3DLocation(s_center_->GetValue(), t_center_->GetValue(), x_center, y_center, z_center);
}

// Return a point that will follow the first endpoint of the arc
// This point will use dependent DOF's to define its location
Point2DPointer Arc2D::GetPoint1()
{
	// Create expressions defining s and t coordinates of the first endpoint of the arc
	ex s_1 = s_center_->GetVariable() + radius_->GetVariable()*cos(theta_1_->GetVariable());
	ex t_1 = t_center_->GetVariable() + radius_->GetVariable()*sin(theta_1_->GetVariable());

	// create DOF lists for each DOF
	std::vector <DOFPointer> s_1_dof_list;
	s_1_dof_list.push_back(s_center_);
	s_1_dof_list.push_back(radius_);
	s_1_dof_list.push_back(theta_1_);

	std::vector <DOFPointer> t_1_dof_list;
	t_1_dof_list.push_back(t_center_);
	t_1_dof_list.push_back(radius_);
	t_1_dof_list.push_back(theta_1_);

	// create dependent DOF's based on the above expressions
	DOFPointer s_dof(new DependentDOF(s_1, s_1_dof_list));
	DOFPointer t_dof(new DependentDOF(t_1, t_1_dof_list));

	// create the actual point object
	Point2DPointer result(new Point2D(s_dof, t_dof, sketch_plane_));
	return result;
}

// Return a point that will follow the second endpoint of the arc
// This point will use dependent DOF's to define its location
Point2DPointer Arc2D::GetPoint2()
{
	// Create expressions defining s and t coordinates of the second endpoint of the arc
	ex s_2 = s_center_->GetVariable() + radius_->GetVariable()*cos(theta_2_->GetVariable());
	ex t_2 = t_center_->GetVariable() + radius_->GetVariable()*sin(theta_2_->GetVariable());

	// create DOF lists for each DOF
	std::vector <DOFPointer> s_2_dof_list;
	s_2_dof_list.push_back(s_center_);
	s_2_dof_list.push_back(radius_);
	s_2_dof_list.push_back(theta_2_);

	std::vector <DOFPointer> t_2_dof_list;
	t_2_dof_list.push_back(t_center_);
	t_2_dof_list.push_back(radius_);
	t_2_dof_list.push_back(theta_2_);

	// create dependent DOF's based on the above expressions
	DOFPointer s_dof(new DependentDOF(s_2, s_2_dof_list));
	DOFPointer t_dof(new DependentDOF(t_2, t_2_dof_list));

	// create the actual point object
	Point2DPointer result(new Point2D(s_dof, t_dof, sketch_plane_));
	return result;
}