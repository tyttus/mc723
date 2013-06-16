
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

/// A TLM locker
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

    /* Handles mutex value using different types */
    union mutex_values {
        int i;
        unsigned char c[4];
    } mutex_value;

    mutex_value.i = 1;
    
    // trocando big endian - little endian
    tmp = mutex_value.c[0];
    mutex_value.c[0] = mutex_value.c[3];
    mutex_value.c[3] = tmp;
    tmp = mutex_value.c[1];
    mutex_value.c[1] = mutex_value.c[2];
    mutex_value.c[2] = mutex_value.c[1];

    switch( request.type ) {

      // Le o lock e se possivel, pega
    case READ: 
      response.status = SUCCESS;
      response.data = mutex;
      mutex = mutex_value.i;
      break;

      // escreve o lock ou tranca
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

