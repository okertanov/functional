/**
 * @category
 * @package
 * @copyright  2011-07-13 (c) 2011 Campaign and Digital Intelligence (http://canddi.com)
 * @license
 * @author     Oleg Kertanov <okertanov@gmail.com>
**/

/**
 * Fake NS (namespace) to simulate whole system environment
 * for the testing purposes only.
 *
 * Used to resolve circular references between CANDDi.Node, CANDDi.Node.Socket.js and
 * CANDDi.Node.SocketSpec.js
 *
 * To Use: refer this module before Socket.js and SocketSpec.js
 *
 * CANDDi
**/
(function(){
    CANDDi = {
                NodeData : {                // XXX: mock object
                    Host : undefined,       // XXX: stub
                    Port : undefined        // XXX: stub
                },
                Node : {                    // XXX: mock object
                    Socket : undefined      // XXX: stub
                },
                Collection : {              // XXX: mock object
                    Contacts : function(){  // XXX: mock object
                    }
                },
                Model : {                   // XXX: mock object
                    User : function(){      // XXX: mock object
                    }
                }
    };
})();

