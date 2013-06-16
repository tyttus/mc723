
#include "ac_tlm_router.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate router from ArchC
using user::ac_tlm_router;

/// Constructor
ac_tlm_router::ac_tlm_router( sc_module_name module_name , unsigned int k ) :
  sc_module( module_name ),
  target_export("iport"),
  mem_port("mem", k),
  lock_port("lock", 1)
  //perif_port("perif", 8)
{
    /// Binds target_export to the router
    target_export( *this );
}

/// Destructor
ac_tlm_router::~ac_tlm_router() {
}
