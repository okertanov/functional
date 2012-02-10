/**
 * @category   
 * @package    
 * @copyright  2011-07-13 (c) 2011 Campaign and Digital Intelligence (http://canddi.com)
 * @license    
 * @author     Tim Langley
**/

/**
 * Handles all connections between the browser and Node
 * To Use:
 * CANDDi.Node.Socket = CANDDi.Node.Socket()
 * CANDDi.Node.Socket.init(accountURL)
 * Then connect to a Contact or a User
**/
CANDDi.Node.Socket = function(){
  var _nodeHost = null,
      _nodePort = null,
      _accountURL = null,
      _bIsLoaded = false,
      _arrDelivered = [];
  /**
   * Configures and returns a socket instance
  **/
  var getSocket = function(socketId, postData, callBack) {
    var  uri = document.location.protocol+'//'+_nodeHost+":"+_nodePort+"/"+socketId
        ,options = {}
        ,socket = io.connect(uri, options)
  
    socket.on('connect', function() {
      socket.send(JSON.stringify(postData));
    });
    socket.on('message', function(jsonMessage){
      if ("undefined" == typeof jsonMessage)
        return;
      
      //This means that we only deliver each message once
      strDelivered = jsonMessage["class"]+":"+jsonMessage["_deliveryTag"]
      if (true == _arrDelivered[strDelivered])
        return;
      _arrDelivered[strDelivered] = true;

      callBack(jsonMessage);
    });
    socket.on('error', function(error) {
      alert("Socket Error" + error);
    })
    socket.on('disconnect', function() { 
      _arrDelivered = [];
    });
    return socket; 
  };
  
  return { 
    /**
     * init must be called first
     * @param accountURL - the account to connect to http://canddi-motors.canddi.com (use canddi-motors)
     * @return void 
    **/
    init: function(accountURL) {
      if (!CANDDi.isDefined(CANDDi.NodeData)) {
        console.log("CANDDi.Node.Socket::init NodeData not loaded");
        return;
      }
      if ("" == CANDDi.NodeData.Host) {
        console.log("CANDDi.Node.Socket::init hostEmpty not loaded");
        return;
      }
      if (CANDDi.isEmpty(window.io)) {
        console.log("CANDDi.Node.Socket::init io not loaded");
        return;
      }
      if (!CANDDi.isDefined(JSON.stringify)) {
        throw new Error("CANDDi.Node.Socket::init JSON.stringify isn't defined");
      }
      _bIsLoaded = true;
    
      _nodeHost = CANDDi.NodeData.Host;
      _nodePort = CANDDi.NodeData.Port || 80;
      _accountURL = accountURL;
    }
    /**
     * This allows us to connect to a specific CANDDi.Collection.Contacts
     * 
     * @param colContact - instance of CANDDi.Collection.Contacts
     * @author Tim Langley
    **/
    ,connectContacts : function(colContact) {
      if (false == _bIsLoaded) {
        console.log("CANDDi.Node.Socket::connectContact Node not loaded");
        return;
      }
      if (!CANDDi.isInstance(colContact, CANDDi.Collection.Contacts)) {
        throw new Error("CANDDi.Node.Socket::connectContact is not a CANDDi.Collection.Contacts");
      }
      var postData = {AccountUrl : _accountURL
                     }
          ,socketId = "Contacts";
      colContact.setSocket(getSocket(socketId, postData, colContact.callbackSocket));
    }
    /**
     * This allows us to connect to a specific CANDDi.Model.User
     * 
     * @param modelUser - instance of CANDDi.Model.User
     * @author Tim Langley
    **/
    ,connectUser : function(modelUser) {
      if (false == _bIsLoaded) {
        console.log("CANDDi.Node.Socket::connectUser Node not loaded");
        return;
      }
      if (!CANDDi.isInstance(modelUser, CANDDi.Model.User)) {
        throw new Error("CANDDi.Node.Socket::connectUser is not a CANDDi.Model.User");
      }
      var postData = {AccountUrl : _accountURL
                     ,UserId : modelUser.id
                     ,UserTypeId : modelUser.get('UserTypeId')
                     }
          ,socketId = "User"
      
      modelUser.setSocket(getSocket(socketId, postData, modelUser.callbackSocket));
    }
  }
}
