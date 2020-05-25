// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generators/include/python_CEGUI.h"
#include "FrameComponentIterator.pypp.hpp"

namespace bp = boost::python;

struct ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_FrameComponent__greater___greater__wrapper : CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > >, bp::wrapper< CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > > > {

    ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_FrameComponent__greater___greater__wrapper(CEGUI::ConstVectorIterator<std::vector<CEGUI::FrameComponent, std::allocator<CEGUI::FrameComponent> > > const & arg )
    : CEGUI::ConstVectorIterator<std::vector<CEGUI::FrameComponent, std::allocator<CEGUI::FrameComponent> > >( arg )
      , bp::wrapper< CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > > >(){
        // copy constructor
        
    }

    ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_FrameComponent__greater___greater__wrapper( )
    : CEGUI::ConstVectorIterator<std::vector<CEGUI::FrameComponent, std::allocator<CEGUI::FrameComponent> > >( )
      , bp::wrapper< CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > > >(){
        // null constructor
    
    }

    virtual ::CEGUI::FrameComponent getCurrentValue(  ) const  {
        if( bp::override func_getCurrentValue = this->get_override( "getCurrentValue" ) )
            return func_getCurrentValue(  );
        else{
            return this->CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > >::getCurrentValue(  );
        }
    }
    
    ::CEGUI::FrameComponent default_getCurrentValue(  ) const  {
        return CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > >::getCurrentValue( );
    }

};

void Iterator_next(::CEGUI::ConstVectorIterator<std::vector<CEGUI::FrameComponent, std::allocator<CEGUI::FrameComponent> > >& t)
{
    t++;
}

void Iterator_previous(::CEGUI::ConstVectorIterator<std::vector<CEGUI::FrameComponent, std::allocator<CEGUI::FrameComponent> > >& t)
{
    t--;
}

void register_FrameComponentIterator_class(){

    { //::CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > >
        typedef bp::class_< ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_FrameComponent__greater___greater__wrapper, bp::bases< CEGUI::ConstBaseIterator< std::vector< CEGUI::FrameComponent >, CEGUI::FrameComponent > > > FrameComponentIterator_exposer_t;
        FrameComponentIterator_exposer_t FrameComponentIterator_exposer = FrameComponentIterator_exposer_t( "FrameComponentIterator", bp::no_init );
        bp::scope FrameComponentIterator_scope( FrameComponentIterator_exposer );
        FrameComponentIterator_exposer.def( bp::init< >("*************************************************************************\n\
           No default construction available\n\
        *************************************************************************\n") );
        { //::CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > >::getCurrentValue
        
            typedef CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > > exported_class_t;
            typedef ::CEGUI::FrameComponent ( exported_class_t::*getCurrentValue_function_type )(  ) const;
            typedef ::CEGUI::FrameComponent ( ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_FrameComponent__greater___greater__wrapper::*default_getCurrentValue_function_type )(  ) const;
            
            FrameComponentIterator_exposer.def( 
                "getCurrentValue"
                , getCurrentValue_function_type(&::CEGUI::ConstVectorIterator< std::vector< CEGUI::FrameComponent > >::getCurrentValue)
                , default_getCurrentValue_function_type(&ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_FrameComponent__greater___greater__wrapper::default_getCurrentValue) );
        
        }
        FrameComponentIterator_exposer.def("next", &::Iterator_next);
        FrameComponentIterator_exposer.def("previous", &::Iterator_previous);
    }

}