#include <systemc>
#include "ac_tlm_protocol.H"

// using statements
using tlm::tlm_transport_if;

/// Namespace to isolate perif from ArchC
namespace user
{

class ac_tlm_perif :
  public sc_module,
  public ac_tlm_transport_if
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

    switch( request.type ) {

      //le a resposta
    case READ: 
      response.status = SUCCESS;
      if (request.addr == 5242896) {
          read ((float &) response.data);
      }
      
      break;
      
      //escreve argumento
    case WRITE:
      response.status = SUCCESS;
      if (request.addr == 5242888) {
          write ((float &) request.data);
      } 
      break;

    default :
      response.status = ERROR;
      break;
    }

    return response;
  }


  
  // Default constructor.
  ac_tlm_perif( sc_module_name module_name );

  // Default destructor.
  ~ac_tlm_perif();

private:
  /* Handles argument value using different types */
    union argument_address {
        float i;
        unsigned char c[4];
    } argument_address;

    
  float result;

  void squareRoot (float &d);

  void write (const float &d);

  void read (float &d);
};
};

