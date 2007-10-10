// This file has been generated by Py++.

#include "boost/python.hpp"

#include "boost/python/suite/indexing/vector_indexing_suite.hpp"

#include "../ConstraintSolver/Ark3DModel.h"

namespace bp = boost::python;

struct Arc2D_wrapper : Arc2D, bp::wrapper< Arc2D > {

    Arc2D_wrapper(Arc2D const & arg )
    : Arc2D( arg )
      , bp::wrapper< Arc2D >(){
        // copy constructor
        
    }

    Arc2D_wrapper(double s_center, double t_center, double theta_1, double theta_2, double radius, ::SketchPlanePointer sketch_plane, bool s_center_free=false, bool t_center_free=false, bool theta_1_free=false, bool theta_2_free=false, bool radius_free=false )
    : Arc2D( s_center, t_center, theta_1, theta_2, radius, sketch_plane, s_center_free, t_center_free, theta_1_free, theta_2_free, radius_free )
      , bp::wrapper< Arc2D >(){
        // constructor
    
    }

    virtual ::Point2DPointer GetPoint1(  ) {
        if( bp::override func_GetPoint1 = this->get_override( "GetPoint1" ) )
            return func_GetPoint1(  );
        else
            return this->Arc2D::GetPoint1(  );
    }
    
    
    ::Point2DPointer default_GetPoint1(  ) {
        return Arc2D::GetPoint1( );
    }

    virtual ::Point2DPointer GetPoint2(  ) {
        if( bp::override func_GetPoint2 = this->get_override( "GetPoint2" ) )
            return func_GetPoint2(  );
        else
            return this->Arc2D::GetPoint2(  );
    }
    
    
    ::Point2DPointer default_GetPoint2(  ) {
        return Arc2D::GetPoint2( );
    }

};

struct DOF_wrapper : DOF, bp::wrapper< DOF > {

    DOF_wrapper(bool free, bool dependent )
    : DOF( free, dependent )
      , bp::wrapper< DOF >(){
        // constructor
    
    }

    DOF_wrapper(char const * name, bool free, bool dependent )
    : DOF( name, free, dependent )
      , bp::wrapper< DOF >(){
        // constructor
    
    }

    virtual double GetValue(  ) const {
        bp::override func_GetValue = this->get_override( "GetValue" );
        return func_GetValue(  );
    }

    virtual void SetValue( double value ){
        bp::override func_SetValue = this->get_override( "SetValue" );
        func_SetValue( value );
    }

};

struct Line2D_wrapper : Line2D, bp::wrapper< Line2D > {

    Line2D_wrapper(Line2D const & arg )
    : Line2D( arg )
      , bp::wrapper< Line2D >(){
        // copy constructor
        
    }

    Line2D_wrapper(::Point2DPointer const point1, ::Point2DPointer const point2, ::SketchPlanePointer sketch_plane )
    : Line2D( point1, point2, sketch_plane )
      , bp::wrapper< Line2D >(){
        // constructor
    
    }

    virtual ::Point2DPointer GetPoint1(  ) {
        if( bp::override func_GetPoint1 = this->get_override( "GetPoint1" ) )
            return func_GetPoint1(  );
        else
            return this->Line2D::GetPoint1(  );
    }
    
    
    ::Point2DPointer default_GetPoint1(  ) {
        return Line2D::GetPoint1( );
    }

    virtual ::Point2DPointer GetPoint2(  ) {
        if( bp::override func_GetPoint2 = this->get_override( "GetPoint2" ) )
            return func_GetPoint2(  );
        else
            return this->Line2D::GetPoint2(  );
    }
    
    
    ::Point2DPointer default_GetPoint2(  ) {
        return Line2D::GetPoint2( );
    }

};

BOOST_PYTHON_MODULE(ark3d_module){
    { //::std::vector<boost::shared_ptr<PrimitiveBase>, std::allocator<boost::shared_ptr<PrimitiveBase> > >
        typedef bp::class_< std::vector<boost::shared_ptr<PrimitiveBase>, std::allocator<boost::shared_ptr<PrimitiveBase> > > > vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate__exposer_t;
        vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate__exposer_t vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate__exposer = vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate__exposer_t( "vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate_" );
        bp::scope vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate__scope( vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate__exposer );
        //WARNING: the next line of code will not compile, because "::boost::shared_ptr<PrimitiveBase>" does not have operator== !
        vector_less_boost_scope_shared_ptr_less_PrimitiveBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_PrimitiveBase_grate___grate___grate__exposer.def( bp::vector_indexing_suite< ::std::vector<boost::shared_ptr<PrimitiveBase>, std::allocator<boost::shared_ptr<PrimitiveBase> > >, true >() );
    }

    { //::std::vector<boost::shared_ptr<Edge2DBase>, std::allocator<boost::shared_ptr<Edge2DBase> > >
        typedef bp::class_< std::vector<boost::shared_ptr<Edge2DBase>, std::allocator<boost::shared_ptr<Edge2DBase> > > > vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate__exposer_t;
        vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate__exposer_t vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate__exposer = vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate__exposer_t( "vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate_" );
        bp::scope vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate__scope( vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate__exposer );
        //WARNING: the next line of code will not compile, because "::boost::shared_ptr<Edge2DBase>" does not have operator== !
        vector_less_boost_scope_shared_ptr_less_Edge2DBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_Edge2DBase_grate___grate___grate__exposer.def( bp::vector_indexing_suite< ::std::vector<boost::shared_ptr<Edge2DBase>, std::allocator<boost::shared_ptr<Edge2DBase> > >, true >() );
    }

    { //::std::vector<boost::shared_ptr<ConstraintEquationBase>, std::allocator<boost::shared_ptr<ConstraintEquationBase> > >
        typedef bp::class_< std::vector<boost::shared_ptr<ConstraintEquationBase>, std::allocator<boost::shared_ptr<ConstraintEquationBase> > > > vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate__exposer_t;
        vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate__exposer_t vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate__exposer = vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate__exposer_t( "vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate_" );
        bp::scope vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate__scope( vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate__exposer );
        //WARNING: the next line of code will not compile, because "::boost::shared_ptr<ConstraintEquationBase>" does not have operator== !
        vector_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate__comma__std_scope_allocator_less_boost_scope_shared_ptr_less_ConstraintEquationBase_grate___grate___grate__exposer.def( bp::vector_indexing_suite< ::std::vector<boost::shared_ptr<ConstraintEquationBase>, std::allocator<boost::shared_ptr<ConstraintEquationBase> > >, true >() );
    }

    bp::enum_< EdgePointNumber>("EdgePointNumber")
        .value("Point1", Point1)
        .value("Point2", Point2)
        .export_values()
        ;

    { //::AngleLine2D
        typedef bp::class_< AngleLine2D > AngleLine2D_exposer_t;
        AngleLine2D_exposer_t AngleLine2D_exposer = AngleLine2D_exposer_t( "AngleLine2D", bp::init< boost::shared_ptr<Line2D>, boost::shared_ptr<Line2D>, double >(( bp::arg("line1"), bp::arg("line2"), bp::arg("angle") )) );
        bp::scope AngleLine2D_scope( AngleLine2D_exposer );
        bp::register_ptr_to_python< boost::shared_ptr< AngleLine2D > >();
        bp::implicitly_convertible< boost::shared_ptr< AngleLine2D >, boost::shared_ptr< ConstraintEquationBase > >();
    }

    { //::Arc2D
        typedef bp::class_< Arc2D_wrapper > Arc2D_exposer_t;
        Arc2D_exposer_t Arc2D_exposer = Arc2D_exposer_t( "Arc2D", bp::init< double, double, double, double, double, SketchPlanePointer, bp::optional< bool, bool, bool, bool, bool > >(( bp::arg("s_center"), bp::arg("t_center"), bp::arg("theta_1"), bp::arg("theta_2"), bp::arg("radius"), bp::arg("sketch_plane"), bp::arg("s_center_free")=(bool)(false), bp::arg("t_center_free")=(bool)(false), bp::arg("theta_1_free")=(bool)(false), bp::arg("theta_2_free")=(bool)(false), bp::arg("radius_free")=(bool)(false) )) );
        bp::scope Arc2D_scope( Arc2D_exposer );
        { //::Arc2D::GeneratePoint1
        
            typedef ::Point2DPointer ( ::Arc2D::*GeneratePoint1_function_type )(  ) ;
            
            Arc2D_exposer.def( 
                "GeneratePoint1"
                , GeneratePoint1_function_type( &::Arc2D::GeneratePoint1 ) );
        
        }
        { //::Arc2D::GeneratePoint2
        
            typedef ::Point2DPointer ( ::Arc2D::*GeneratePoint2_function_type )(  ) ;
            
            Arc2D_exposer.def( 
                "GeneratePoint2"
                , GeneratePoint2_function_type( &::Arc2D::GeneratePoint2 ) );
        
        }
        { //::Arc2D::Get3DLocations
        
            typedef void ( ::Arc2D::*Get3DLocations_function_type )( double &,double &,double & ) ;
            
            Arc2D_exposer.def( 
                "Get3DLocations"
                , Get3DLocations_function_type( &::Arc2D::Get3DLocations )
                , ( bp::arg("x_center"), bp::arg("y_center"), bp::arg("z_center") ) );
        
        }
        { //::Arc2D::GetPoint1
        
            typedef ::Point2DPointer ( ::Arc2D::*GetPoint1_function_type )(  ) ;
            typedef ::Point2DPointer ( Arc2D_wrapper::*default_GetPoint1_function_type )(  ) ;
            
            Arc2D_exposer.def( 
                "GetPoint1"
                , GetPoint1_function_type(&::Arc2D::GetPoint1)
                , default_GetPoint1_function_type(&Arc2D_wrapper::default_GetPoint1) );
        
        }
        { //::Arc2D::GetPoint2
        
            typedef ::Point2DPointer ( ::Arc2D::*GetPoint2_function_type )(  ) ;
            typedef ::Point2DPointer ( Arc2D_wrapper::*default_GetPoint2_function_type )(  ) ;
            
            Arc2D_exposer.def( 
                "GetPoint2"
                , GetPoint2_function_type(&::Arc2D::GetPoint2)
                , default_GetPoint2_function_type(&Arc2D_wrapper::default_GetPoint2) );
        
        }
        { //::Arc2D::GetRadius
        
            typedef ::DOFPointer ( ::Arc2D::*GetRadius_function_type )(  ) const;
            
            Arc2D_exposer.def( 
                "GetRadius"
                , GetRadius_function_type( &::Arc2D::GetRadius ) );
        
        }
        { //::Arc2D::GetSCenter
        
            typedef ::DOFPointer ( ::Arc2D::*GetSCenter_function_type )(  ) const;
            
            Arc2D_exposer.def( 
                "GetSCenter"
                , GetSCenter_function_type( &::Arc2D::GetSCenter ) );
        
        }
        { //::Arc2D::GetTCenter
        
            typedef ::DOFPointer ( ::Arc2D::*GetTCenter_function_type )(  ) const;
            
            Arc2D_exposer.def( 
                "GetTCenter"
                , GetTCenter_function_type( &::Arc2D::GetTCenter ) );
        
        }
        { //::Arc2D::GetTheta1
        
            typedef ::DOFPointer ( ::Arc2D::*GetTheta1_function_type )(  ) const;
            
            Arc2D_exposer.def( 
                "GetTheta1"
                , GetTheta1_function_type( &::Arc2D::GetTheta1 ) );
        
        }
        { //::Arc2D::GetTheta2
        
            typedef ::DOFPointer ( ::Arc2D::*GetTheta2_function_type )(  ) const;
            
            Arc2D_exposer.def( 
                "GetTheta2"
                , GetTheta2_function_type( &::Arc2D::GetTheta2 ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< Arc2D > >();
        bp::implicitly_convertible< boost::shared_ptr< Arc2D >, boost::shared_ptr< Edge2DBase > >();
        bp::implicitly_convertible< boost::shared_ptr< Arc2D >, boost::shared_ptr< Primitive2DBase > >();
        bp::implicitly_convertible< boost::shared_ptr< Arc2D >, boost::shared_ptr< PrimitiveBase > >();
    }

    bp::class_< Ark3DModel >( "Ark3DModel" )    
        .def( 
            "AddConstraintEquation"
            , &::Ark3DModel::AddConstraintEquation
            , ( bp::arg("new_constraint_equation") ) )    
        .def( 
            "AddConstraintEquations"
            , &::Ark3DModel::AddConstraintEquations
            , ( bp::arg("new_constraint_equations") ) )    
        .def( 
            "AddPrimitive"
            , &::Ark3DModel::AddPrimitive
            , ( bp::arg("new_primitive") ) )    
        .def( 
            "AddPrimitives"
            , &::Ark3DModel::AddPrimitives
            , ( bp::arg("new_primitives") ) )    
        .def( 
            "SolveConstraints"
            , &::Ark3DModel::SolveConstraints )    
        .def( 
            "UpdateDisplay"
            , &::Ark3DModel::UpdateDisplay );

    { //::DOF
        typedef bp::class_< DOF_wrapper, boost::noncopyable > DOF_exposer_t;
        DOF_exposer_t DOF_exposer = DOF_exposer_t( "DOF", bp::init< bool, bool >(( bp::arg("free"), bp::arg("dependent") )) );
        bp::scope DOF_scope( DOF_exposer );
        DOF_exposer.def( bp::init< char const *, bool, bool >(( bp::arg("name"), bp::arg("free"), bp::arg("dependent") )) );
        { //::DOF::GetValue
        
            typedef double ( ::DOF::*GetValue_function_type )(  ) const;
            
            DOF_exposer.def( 
                "GetValue"
                , bp::pure_virtual( GetValue_function_type(&::DOF::GetValue) ) );
        
        }
        { //::DOF::GetVariable
        
            typedef ::GiNaC::symbol const & ( ::DOF::*GetVariable_function_type )(  ) const;
            
            DOF_exposer.def( 
                "GetVariable"
                , GetVariable_function_type( &::DOF::GetVariable )
                , bp::return_value_policy< bp::copy_const_reference >() );
        
        }
        { //::DOF::IsDependent
        
            typedef bool ( ::DOF::*IsDependent_function_type )(  ) const;
            
            DOF_exposer.def( 
                "IsDependent"
                , IsDependent_function_type( &::DOF::IsDependent ) );
        
        }
        { //::DOF::IsFree
        
            typedef bool ( ::DOF::*IsFree_function_type )(  ) const;
            
            DOF_exposer.def( 
                "IsFree"
                , IsFree_function_type( &::DOF::IsFree ) );
        
        }
        { //::DOF::SetValue
        
            typedef void ( ::DOF::*SetValue_function_type )( double ) ;
            
            DOF_exposer.def( 
                "SetValue"
                , bp::pure_virtual( SetValue_function_type(&::DOF::SetValue) )
                , ( bp::arg("value") ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< DOF > >();
    }

    bp::class_< DistancePoint >( "DistancePoint", bp::init< boost::shared_ptr<Point>, boost::shared_ptr<Point>, double >(( bp::arg("point1"), bp::arg("point2"), bp::arg("distance") )) );

    { //::DistancePoint2D
        typedef bp::class_< DistancePoint2D > DistancePoint2D_exposer_t;
        DistancePoint2D_exposer_t DistancePoint2D_exposer = DistancePoint2D_exposer_t( "DistancePoint2D", bp::init< boost::shared_ptr<Point2D>, boost::shared_ptr<Point2D>, double >(( bp::arg("point1"), bp::arg("point2"), bp::arg("distance") )) );
        bp::scope DistancePoint2D_scope( DistancePoint2D_exposer );
        bp::register_ptr_to_python< boost::shared_ptr< DistancePoint2D > >();
        bp::implicitly_convertible< boost::shared_ptr< DistancePoint2D >, boost::shared_ptr< ConstraintEquationBase > >();
    }

    bp::class_< EdgeLoop2D >( "EdgeLoop2D" )    
        .def( bp::init< >() )    
        .def( bp::init< std::vector<boost::shared_ptr<Edge2DBase>, std::allocator<boost::shared_ptr<Edge2DBase> > > >(( bp::arg("edge_list") )) )    
        .def( 
            "AddEdge"
            , &::EdgeLoop2D::AddEdge
            , ( bp::arg("new_edge") ) )    
        .def( 
            "IsLoopValid"
            , &::EdgeLoop2D::IsLoopValid );

    bp::implicitly_convertible< std::vector<boost::shared_ptr<Edge2DBase>, std::allocator<boost::shared_ptr<Edge2DBase> > >, EdgeLoop2D >();

    { //::Line
        typedef bp::class_< Line > Line_exposer_t;
        Line_exposer_t Line_exposer = Line_exposer_t( "Line", bp::init< boost::shared_ptr<Point>, boost::shared_ptr<Point> >(( bp::arg("point1"), bp::arg("point2") )) );
        bp::scope Line_scope( Line_exposer );
        { //::Line::GetX1
        
            typedef ::DOFPointer ( ::Line::*GetX1_function_type )(  ) const;
            
            Line_exposer.def( 
                "GetX1"
                , GetX1_function_type( &::Line::GetX1 ) );
        
        }
        { //::Line::GetX2
        
            typedef ::DOFPointer ( ::Line::*GetX2_function_type )(  ) const;
            
            Line_exposer.def( 
                "GetX2"
                , GetX2_function_type( &::Line::GetX2 ) );
        
        }
        { //::Line::GetY1
        
            typedef ::DOFPointer ( ::Line::*GetY1_function_type )(  ) const;
            
            Line_exposer.def( 
                "GetY1"
                , GetY1_function_type( &::Line::GetY1 ) );
        
        }
        { //::Line::GetY2
        
            typedef ::DOFPointer ( ::Line::*GetY2_function_type )(  ) const;
            
            Line_exposer.def( 
                "GetY2"
                , GetY2_function_type( &::Line::GetY2 ) );
        
        }
        { //::Line::GetZ1
        
            typedef ::DOFPointer ( ::Line::*GetZ1_function_type )(  ) const;
            
            Line_exposer.def( 
                "GetZ1"
                , GetZ1_function_type( &::Line::GetZ1 ) );
        
        }
        { //::Line::GetZ2
        
            typedef ::DOFPointer ( ::Line::*GetZ2_function_type )(  ) const;
            
            Line_exposer.def( 
                "GetZ2"
                , GetZ2_function_type( &::Line::GetZ2 ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< Line > >();
        bp::implicitly_convertible< boost::shared_ptr< Line >, boost::shared_ptr< PrimitiveBase > >();
    }

    { //::Line2D
        typedef bp::class_< Line2D_wrapper > Line2D_exposer_t;
        Line2D_exposer_t Line2D_exposer = Line2D_exposer_t( "Line2D", bp::init< boost::shared_ptr<Point2D>, boost::shared_ptr<Point2D>, SketchPlanePointer >(( bp::arg("point1"), bp::arg("point2"), bp::arg("sketch_plane") )) );
        bp::scope Line2D_scope( Line2D_exposer );
        { //::Line2D::Get3DLocations
        
            typedef void ( ::Line2D::*Get3DLocations_function_type )( double &,double &,double &,double &,double &,double & ) ;
            
            Line2D_exposer.def( 
                "Get3DLocations"
                , Get3DLocations_function_type( &::Line2D::Get3DLocations )
                , ( bp::arg("x1"), bp::arg("y1"), bp::arg("z1"), bp::arg("x2"), bp::arg("y2"), bp::arg("z2") ) );
        
        }
        { //::Line2D::GetPoint1
        
            typedef ::Point2DPointer ( ::Line2D::*GetPoint1_function_type )(  ) ;
            typedef ::Point2DPointer ( Line2D_wrapper::*default_GetPoint1_function_type )(  ) ;
            
            Line2D_exposer.def( 
                "GetPoint1"
                , GetPoint1_function_type(&::Line2D::GetPoint1)
                , default_GetPoint1_function_type(&Line2D_wrapper::default_GetPoint1) );
        
        }
        { //::Line2D::GetPoint2
        
            typedef ::Point2DPointer ( ::Line2D::*GetPoint2_function_type )(  ) ;
            typedef ::Point2DPointer ( Line2D_wrapper::*default_GetPoint2_function_type )(  ) ;
            
            Line2D_exposer.def( 
                "GetPoint2"
                , GetPoint2_function_type(&::Line2D::GetPoint2)
                , default_GetPoint2_function_type(&Line2D_wrapper::default_GetPoint2) );
        
        }
        { //::Line2D::GetS1
        
            typedef ::DOFPointer ( ::Line2D::*GetS1_function_type )(  ) const;
            
            Line2D_exposer.def( 
                "GetS1"
                , GetS1_function_type( &::Line2D::GetS1 ) );
        
        }
        { //::Line2D::GetS2
        
            typedef ::DOFPointer ( ::Line2D::*GetS2_function_type )(  ) const;
            
            Line2D_exposer.def( 
                "GetS2"
                , GetS2_function_type( &::Line2D::GetS2 ) );
        
        }
        { //::Line2D::GetT1
        
            typedef ::DOFPointer ( ::Line2D::*GetT1_function_type )(  ) const;
            
            Line2D_exposer.def( 
                "GetT1"
                , GetT1_function_type( &::Line2D::GetT1 ) );
        
        }
        { //::Line2D::GetT2
        
            typedef ::DOFPointer ( ::Line2D::*GetT2_function_type )(  ) const;
            
            Line2D_exposer.def( 
                "GetT2"
                , GetT2_function_type( &::Line2D::GetT2 ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< Line2D > >();
        bp::implicitly_convertible< boost::shared_ptr< Line2D >, boost::shared_ptr< Edge2DBase > >();
        bp::implicitly_convertible< boost::shared_ptr< Line2D >, boost::shared_ptr< Primitive2DBase > >();
        bp::implicitly_convertible< boost::shared_ptr< Line2D >, boost::shared_ptr< PrimitiveBase > >();
    }

    bp::class_< ParallelLine >( "ParallelLine", bp::init< boost::shared_ptr<Line>, boost::shared_ptr<Line> >(( bp::arg("line1"), bp::arg("line2") )) );

    { //::ParallelLine2D
        typedef bp::class_< ParallelLine2D > ParallelLine2D_exposer_t;
        ParallelLine2D_exposer_t ParallelLine2D_exposer = ParallelLine2D_exposer_t( "ParallelLine2D", bp::init< boost::shared_ptr<Line2D>, boost::shared_ptr<Line2D> >(( bp::arg("line1"), bp::arg("line2") )) );
        bp::scope ParallelLine2D_scope( ParallelLine2D_exposer );
        bp::register_ptr_to_python< boost::shared_ptr< ParallelLine2D > >();
        bp::implicitly_convertible< boost::shared_ptr< ParallelLine2D >, boost::shared_ptr< ConstraintEquationBase > >();
    }

    { //::Point
        typedef bp::class_< Point > Point_exposer_t;
        Point_exposer_t Point_exposer = Point_exposer_t( "Point", bp::init< double, double, double, bp::optional< bool, bool, bool > >(( bp::arg("x"), bp::arg("y"), bp::arg("z"), bp::arg("x_free")=(bool)(false), bp::arg("y_free")=(bool)(false), bp::arg("z_free")=(bool)(false) )) );
        bp::scope Point_scope( Point_exposer );
        { //::Point::GetXDOF
        
            typedef ::DOFPointer ( ::Point::*GetXDOF_function_type )(  ) const;
            
            Point_exposer.def( 
                "GetXDOF"
                , GetXDOF_function_type( &::Point::GetXDOF ) );
        
        }
        { //::Point::GetYDOF
        
            typedef ::DOFPointer ( ::Point::*GetYDOF_function_type )(  ) const;
            
            Point_exposer.def( 
                "GetYDOF"
                , GetYDOF_function_type( &::Point::GetYDOF ) );
        
        }
        { //::Point::GetZDOF
        
            typedef ::DOFPointer ( ::Point::*GetZDOF_function_type )(  ) const;
            
            Point_exposer.def( 
                "GetZDOF"
                , GetZDOF_function_type( &::Point::GetZDOF ) );
        
        }
        { //::Point::GetmmcMatrix
        
            typedef ::mmcMatrix ( ::Point::*GetmmcMatrix_function_type )(  ) ;
            
            Point_exposer.def( 
                "GetmmcMatrix"
                , GetmmcMatrix_function_type( &::Point::GetmmcMatrix ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< Point > >();
        bp::implicitly_convertible< boost::shared_ptr< Point >, boost::shared_ptr< PrimitiveBase > >();
    }

    { //::Point2D
        typedef bp::class_< Point2D > Point2D_exposer_t;
        Point2D_exposer_t Point2D_exposer = Point2D_exposer_t( "Point2D", bp::init< double, double, SketchPlanePointer, bp::optional< bool, bool > >(( bp::arg("s"), bp::arg("t"), bp::arg("sketch_plane"), bp::arg("s_free")=(bool)(false), bp::arg("t_free")=(bool)(false) )) );
        bp::scope Point2D_scope( Point2D_exposer );
        Point2D_exposer.def( bp::init< DOFPointer, DOFPointer, SketchPlanePointer >(( bp::arg("s"), bp::arg("t"), bp::arg("sketch_plane") )) );
        { //::Point2D::Get3DLocation
        
            typedef void ( ::Point2D::*Get3DLocation_function_type )( double &,double &,double & ) const;
            
            Point2D_exposer.def( 
                "Get3DLocation"
                , Get3DLocation_function_type( &::Point2D::Get3DLocation )
                , ( bp::arg("x_location"), bp::arg("y_location"), bp::arg("z_location") ) );
        
        }
        { //::Point2D::GetSDOF
        
            typedef ::DOFPointer ( ::Point2D::*GetSDOF_function_type )(  ) const;
            
            Point2D_exposer.def( 
                "GetSDOF"
                , GetSDOF_function_type( &::Point2D::GetSDOF ) );
        
        }
        { //::Point2D::GetTDOF
        
            typedef ::DOFPointer ( ::Point2D::*GetTDOF_function_type )(  ) const;
            
            Point2D_exposer.def( 
                "GetTDOF"
                , GetTDOF_function_type( &::Point2D::GetTDOF ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< Point2D > >();
        bp::implicitly_convertible< boost::shared_ptr< Point2D >, boost::shared_ptr< Primitive2DBase > >();
        bp::implicitly_convertible< boost::shared_ptr< Point2D >, boost::shared_ptr< PrimitiveBase > >();
    }

    bp::class_< PrimitiveException >( "PrimitiveException" );

    { //::SketchPlane
        typedef bp::class_< SketchPlane > SketchPlane_exposer_t;
        SketchPlane_exposer_t SketchPlane_exposer = SketchPlane_exposer_t( "SketchPlane", bp::init< VectorPointer, VectorPointer, PointPointer >(( bp::arg("normal"), bp::arg("up"), bp::arg("base") )) );
        bp::scope SketchPlane_scope( SketchPlane_exposer );
        { //::SketchPlane::Get3DLocation
        
            typedef void ( ::SketchPlane::*Get3DLocation_function_type )( double,double,double &,double &,double & ) ;
            
            SketchPlane_exposer.def( 
                "Get3DLocation"
                , Get3DLocation_function_type( &::SketchPlane::Get3DLocation )
                , ( bp::arg("s"), bp::arg("t"), bp::arg("x"), bp::arg("y"), bp::arg("z") ) );
        
        }
        { //::SketchPlane::GetABCD
        
            typedef void ( ::SketchPlane::*GetABCD_function_type )( double &,double &,double &,double & ) ;
            
            SketchPlane_exposer.def( 
                "GetABCD"
                , GetABCD_function_type( &::SketchPlane::GetABCD )
                , ( bp::arg("coef_a"), bp::arg("coef_b"), bp::arg("coef_c"), bp::arg("coef_d") ) );
        
        }
        { //::SketchPlane::GetBase
        
            typedef ::PointPointer ( ::SketchPlane::*GetBase_function_type )(  ) ;
            
            SketchPlane_exposer.def( 
                "GetBase"
                , GetBase_function_type( &::SketchPlane::GetBase ) );
        
        }
        { //::SketchPlane::GetNormal
        
            typedef ::VectorPointer ( ::SketchPlane::*GetNormal_function_type )(  ) ;
            
            SketchPlane_exposer.def( 
                "GetNormal"
                , GetNormal_function_type( &::SketchPlane::GetNormal ) );
        
        }
        { //::SketchPlane::GetUp
        
            typedef ::VectorPointer ( ::SketchPlane::*GetUp_function_type )(  ) ;
            
            SketchPlane_exposer.def( 
                "GetUp"
                , GetUp_function_type( &::SketchPlane::GetUp ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< SketchPlane > >();
        bp::implicitly_convertible< boost::shared_ptr< SketchPlane >, boost::shared_ptr< PrimitiveBase > >();
    }

    { //::TangentEdge2D
        typedef bp::class_< TangentEdge2D > TangentEdge2D_exposer_t;
        TangentEdge2D_exposer_t TangentEdge2D_exposer = TangentEdge2D_exposer_t( "TangentEdge2D", bp::init< Edge2DBasePointer, EdgePointNumber, Edge2DBasePointer, EdgePointNumber >(( bp::arg("edge1"), bp::arg("point_num_1"), bp::arg("edge2"), bp::arg("point_num_2") )) );
        bp::scope TangentEdge2D_scope( TangentEdge2D_exposer );
        bp::register_ptr_to_python< boost::shared_ptr< TangentEdge2D > >();
        bp::implicitly_convertible< boost::shared_ptr< TangentEdge2D >, boost::shared_ptr< ConstraintEquationBase > >();
    }

    { //::Vector
        typedef bp::class_< Vector > Vector_exposer_t;
        Vector_exposer_t Vector_exposer = Vector_exposer_t( "Vector", bp::init< double, double, double, bp::optional< bool, bool, bool > >(( bp::arg("x"), bp::arg("y"), bp::arg("z"), bp::arg("x_free")=(bool)(false), bp::arg("y_free")=(bool)(false), bp::arg("z_free")=(bool)(false) )) );
        bp::scope Vector_scope( Vector_exposer );
        { //::Vector::GetmmcMatrix
        
            typedef ::mmcMatrix ( ::Vector::*GetmmcMatrix_function_type )(  ) ;
            
            Vector_exposer.def( 
                "GetmmcMatrix"
                , GetmmcMatrix_function_type( &::Vector::GetmmcMatrix ) );
        
        }
        bp::register_ptr_to_python< boost::shared_ptr< Vector > >();
        bp::implicitly_convertible< boost::shared_ptr< Vector >, boost::shared_ptr< PrimitiveBase > >();
    }

    { //::CreateAngleLine2D
    
        typedef ::AngleLine2DPointer ( *CreateAngleLine2D_function_type )( ::Line2DPointer const,::Line2DPointer const,double );
        
        bp::def( 
            "CreateAngleLine2D"
            , CreateAngleLine2D_function_type( &::CreateAngleLine2D )
            , ( bp::arg("line1"), bp::arg("line2"), bp::arg("angle") ) );
    
    }

    { //::CreateArc2D
    
        typedef ::Arc2DPointer ( *CreateArc2D_function_type )( double,double,double,double,double,::SketchPlanePointer,bool,bool,bool,bool,bool );
        
        bp::def( 
            "CreateArc2D"
            , CreateArc2D_function_type( &::CreateArc2D )
            , ( bp::arg("s_center"), bp::arg("t_center"), bp::arg("theta_1"), bp::arg("theta_2"), bp::arg("radius"), bp::arg("sketch_plane"), bp::arg("s_center_free"), bp::arg("t_center_free"), bp::arg("theta_1_free"), bp::arg("theta_2_free"), bp::arg("radius_free") ) );
    
    }

    { //::CreateDistancePoint2D
    
        typedef ::DistancePoint2DPointer ( *CreateDistancePoint2D_function_type )( ::Point2DPointer const,::Point2DPointer const,double );
        
        bp::def( 
            "CreateDistancePoint2D"
            , CreateDistancePoint2D_function_type( &::CreateDistancePoint2D )
            , ( bp::arg("point1"), bp::arg("point2"), bp::arg("distance") ) );
    
    }

    { //::CreateLine2D
    
        typedef ::Line2DPointer ( *CreateLine2D_function_type )( ::Point2DPointer const,::Point2DPointer const,::SketchPlanePointer );
        
        bp::def( 
            "CreateLine2D"
            , CreateLine2D_function_type( &::CreateLine2D )
            , ( bp::arg("point1"), bp::arg("point2"), bp::arg("sketch_plane") ) );
    
    }

    { //::CreateParallelLine2D
    
        typedef ::ParallelLine2DPointer ( *CreateParallelLine2D_function_type )( ::Line2DPointer const,::Line2DPointer const );
        
        bp::def( 
            "CreateParallelLine2D"
            , CreateParallelLine2D_function_type( &::CreateParallelLine2D )
            , ( bp::arg("line1"), bp::arg("line2") ) );
    
    }

    { //::CreatePoint
    
        typedef ::PointPointer ( *CreatePoint_function_type )( double,double,double,bool,bool,bool );
        
        bp::def( 
            "CreatePoint"
            , CreatePoint_function_type( &::CreatePoint )
            , ( bp::arg("x"), bp::arg("y"), bp::arg("z"), bp::arg("x_free")=(bool)(false), bp::arg("y_free")=(bool)(false), bp::arg("z_free")=(bool)(false) ) );
    
    }

    { //::CreatePoint2D
    
        typedef ::Point2DPointer ( *CreatePoint2D_function_type )( double,double,::SketchPlanePointer,bool,bool );
        
        bp::def( 
            "CreatePoint2D"
            , CreatePoint2D_function_type( &::CreatePoint2D )
            , ( bp::arg("s"), bp::arg("t"), bp::arg("sketch_plane"), bp::arg("s_free"), bp::arg("t_free") ) );
    
    }

    { //::CreateSketchPlane
    
        typedef ::SketchPlanePointer ( *CreateSketchPlane_function_type )( ::VectorPointer,::VectorPointer,::PointPointer );
        
        bp::def( 
            "CreateSketchPlane"
            , CreateSketchPlane_function_type( &::CreateSketchPlane )
            , ( bp::arg("normal"), bp::arg("up"), bp::arg("base") ) );
    
    }

    { //::CreateTangentEdge2D
    
        typedef ::TangentEdge2DPointer ( *CreateTangentEdge2D_function_type )( ::Edge2DBasePointer,::EdgePointNumber,::Edge2DBasePointer,::EdgePointNumber );
        
        bp::def( 
            "CreateTangentEdge2D"
            , CreateTangentEdge2D_function_type( &::CreateTangentEdge2D )
            , ( bp::arg("edge1"), bp::arg("point_num_1"), bp::arg("edge2"), bp::arg("point_num_2") ) );
    
    }

    { //::CreateVector
    
        typedef ::VectorPointer ( *CreateVector_function_type )( double,double,double,bool,bool,bool );
        
        bp::def( 
            "CreateVector"
            , CreateVector_function_type( &::CreateVector )
            , ( bp::arg("x"), bp::arg("y"), bp::arg("z"), bp::arg("x_free")=(bool)(false), bp::arg("y_free")=(bool)(false), bp::arg("z_free")=(bool)(false) ) );
    
    }
}
