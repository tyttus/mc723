// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"

#include "ac_tlm_lock.h"
//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate router from ArchC
namespace user
{

// A TLM router
  class ac_tlm_router :
  public sc_module,
  public ac_tlm_transport_if
{
public:
  
  // Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;
  ac_tlm_port mem_port;
  ac_tlm_port lock_port;
  //ac_tlm_port perif_port;
  
  // Constructor
  ac_tlm_router ( sc_module_name module_name , unsigned int k = 5242880U ); // 5M
  
  // Destructor
  ~ac_tlm_router();
  
  ac_tlm_rsp transport( const ac_tlm_req &request ) {
    // To memory
    if(request.addr < (5*1024*1024+4)) //5242884
      return mem_port->transport(request);

    // To lock
    if (request.addr == (6*1024*1024))
      return lock_port->transport(request);

    // To function unit
    //return perif_port->transport(request);
  } 
};
  
};

