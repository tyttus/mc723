// Standard includes
#include <math.h>
// SystemC includes
// ArchC includes

#include "ac_tlm_perif.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate perif from ArchC
using user::ac_tlm_perif;

/// Constructor
ac_tlm_perif::ac_tlm_perif( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

}

/// Destructor
ac_tlm_perif::~ac_tlm_perif() {
}

/// raiz quadrada
void ac_tlm_perif::squareRoot(float &d) {
    result = (float) sqrt (d);
}

void ac_tlm_perif::write( const float &d ) {
    argument_address.i = d;
    
    unsigned char tmp = argument_address.c[0];
    argument_address.c[0] = argument_address.c[3];
    argument_address.c[3] = tmp;
    tmp = argument_address.c[1];
    argument_address.c[1] = argument_address.c[2];
    argument_address.c[2] = argument_address.c[1];

    squareRoot(argument_address.i);
}

void ac_tlm_perif::read( float &d ) {
    argument_address.i = result;

    unsigned char tmp = argument_address.c[0];
    argument_address.c[0] = argument_address.c[3];
    argument_address.c[3] = tmp;
    tmp = argument_address.c[1];
    argument_address.c[1] = argument_address.c[2];
    argument_address.c[2] = argument_address.c[1];

    d = argument_address.i;
}
