
#include "ac_tlm_lock.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate lock from ArchC
using user::ac_tlm_lock;

/// Constructor
ac_tlm_lock::ac_tlm_lock( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    /// Initialize mutex
    mutex = 0;
}

/// Destructor
ac_tlm_lock::~ac_tlm_lock() {
}
