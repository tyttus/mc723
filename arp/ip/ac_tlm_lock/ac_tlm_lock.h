
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate lock from ArchC
namespace user
{


class ac_tlm_lock :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;

  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;
    unsigned char tmp;

    // endereco do mutex
    union mutex_address {
        int i;
        unsigned char c[4];
    } mutex_address;

    mutex_address.i = 1;
    
    // trocando big endian - little endian
    tmp = mutex_address.c[0];
    mutex_address.c[0] = mutex_address.c[3];
    mutex_address.c[3] = tmp;
    tmp = mutex_address.c[1];
    mutex_address.c[1] = mutex_address.c[2];
    mutex_address.c[2] = mutex_address.c[1];

    switch( request.type ) {

    case READ: 
      response.status = SUCCESS;
      response.data = mutex;
      mutex = mutex_address.i;
      break;

    case WRITE:
      response.status = SUCCESS;
      mutex = request.data;
      break;

    default :
      response.status = ERROR;
      break;
    }

    return response;
  }


  
  // Default constructor.
  ac_tlm_lock( sc_module_name module_name );

  // Default destructor.
  ~ac_tlm_lock();

private:
  int mutex; 
};
};

