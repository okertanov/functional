/**
 * @category
 * @package
 * @copyright  2011-07-13 (c) 2011 Campaign and Digital Intelligence (http://canddi.com)
 * @license
 * @author     Oleg Kertanov <okertanov@gmail.com>
**/

/**
 * Jasmine test suite for CANDDi.Node.Socket.js
 *
 * To Use: open RunTests.html with any js capable browser
 *
 * describe/it
**/
describe("canddi.com::Socket.js", function() {

    var socket; // CANDDi.Node.Socket for every it()

    beforeEach(function() {
        console.log('canddi.com::Socket.js beforeEach.');

        // Fake Spy methods
        CANDDi.isDefined = jasmine.createSpy('CANDDi.isDefined').andCallFake(function(o){
            console.log('fake CANDDi.isDefined() for ' + new String(o).substring(0, 24));
            return true; // defined
        });
        CANDDi.isEmpty = jasmine.createSpy('CANDDi.isEmpty').andCallFake(function(o){
            console.log('fake CANDDi.isEmpty() for ' + new String(o).substring(0, 24));
            return false; // not empty
        });
        CANDDi.isInstance = jasmine.createSpy('CANDDi.isInstance').andCallFake(function(o){
            console.log('fake CANDDi.isInstance() for ' + new String(o).substring(0, 24));
            return true; // is instance
        });

        // IO mocks
        window.io = jasmine.createSpy('window.io');
        window.io.socket = jasmine.createSpy('window.io.socket').andCallFake(function(){
            console.log('fake window.io.socket()');
        });
        window.io.socket.on = jasmine.createSpy('window.io.socket.on').andCallFake(function(e, f){
            console.log('fake window.io.socket.on() for ' + new String(e).substring(0, 24) + " and " + new String(f).substring(0, 24));
        });
        window.io.connect = jasmine.createSpy('window.io.connect').andCallFake(function(uri, opt){
            console.log('fake window.io.connect() for ' + new String(uri).substring(0, 24) + " and " + new String(opt).substring(0, 24));
            return window.io.socket;
        });

        // Create CANDDi.Node.Socket instance for every suite scope
        socket = new CANDDi.Node.Socket();
        spyOn(socket, 'init').andCallThrough();
        spyOn(socket, 'connectContacts').andCallThrough();
        spyOn(socket, 'connectUser').andCallThrough();

        // Test data
        CANDDi.NodeData.Host = 'not.empty.tld';
        CANDDi.NodeData.Port = 8080;
    });

    afterEach(function() {
        console.log('canddi.com::Socket.js afterEach.');

        delete socket;
    });

    /* Suite 1. */
    describe("Suite 1: Initialization.", function() {

        /* Spec 1. */
        it("Spec 1: Module visibility and sanity check", function() {
            expect(CANDDi).not.toBeUndefined();
            expect(CANDDi.Node).toBeDefined();
            expect(CANDDi.Node.Socket).toBeDefined();
        });

        /* Spec 2. */
        it("Spec 2: Construct Socket object", function() {
            expect(socket).toBeDefined();
        });

        /* Spec 3. */
        it("Spec 3: Specification accordance", function() {
            // Socket should have constructor
            expect(typeof socket).toBe('object');
            // Public API
            expect(typeof socket.init).toBe('function');
            expect(typeof socket.connectContacts).toBe('function');
            expect(typeof socket.connectUser).toBe('function');
            // Private API
            expect(socket.getSocket).not.toBeDefined();
            expect(socket.setSocket).not.toBeDefined();
        });

    });

    /* Suite 2. */
    describe("Suite 2: Functionality.", function() {

        beforeEach(function() {
            console.log('Suite 2 beforeEach.');

            // Create CANDDi.Collection.Contacts for this suite scope
            contact = new CANDDi.Collection.Contacts();
            contact.callbackSocket = jasmine.createSpy('CANDDi.Collection.Contacts.callbackSocket').andCallFake(function(o){
                console.log('fake CANDDi.Collection.Contacts.callbackSocket() for ' + new String(o).substring(0, 24));
            });
            contact.setSocket = jasmine.createSpy('CANDDi.Collection.Contacts.setSocket').andCallFake(function(s){
                console.log('fake CANDDi.Collection.Contacts.setSocket() for ' + new String(s).substring(0, 24));
            });

            // Create CANDDi.Model.User for this suite scope
            user = new CANDDi.Model.User();
            user.callbackSocket = jasmine.createSpy('CANDDi.Model.User.setSocket.callbackSocket').andCallFake(function(o){
                console.log('fake CANDDi.Model.User.callbackSocket() for ' + new String(o).substring(0, 24));
            });
            user.setSocket = jasmine.createSpy('CANDDi.Model.User.setSocket.setSocket').andCallFake(function(s){
                console.log('fake CANDDi.Model.User.setSocket() for ' + new String(s).substring(0, 24));
            });
            user.get  = jasmine.createSpy('CANDDi.Model.User.get').andCallFake(function(i){
                console.log('fake CANDDi.Model.User.get() for ' + new String(i).substring(0, 24) + ' and returns ' + this[i]);
                return this[i];
            });

            // Test data
            user.id = 'UID-123';
            user['UserTypeId'] = 'UTID-123';
        });

        afterEach(function() {
            console.log('Suite 2 afterEach.');

            delete contact;
            delete user;
        });

        /* Spec 1. */
        it("Spec 1: socket.init", function() {
            expect(socket).toBeDefined();
            {
                // Default init
                socket.init();
                // Parametrized init
                socket.init('http://account.url.tld/acc');
            }
            expect(socket.init).toHaveBeenCalled();
            expect(socket.init.callCount).toEqual(2); // x*2
            expect(CANDDi.isDefined.callCount).toEqual(4);
            expect(CANDDi.isEmpty.callCount).toEqual(2);
            expect(CANDDi.isInstance.callCount).toEqual(0);
        });

        /* Spec 2. */
        it("Spec 2: socket.connectContacts", function() {
            expect(socket).toBeDefined();
            expect(contact).toBeDefined();
            {
                socket.init('http://api.tld/endpoint/contact');
                socket.connectContacts(contact);
            }
            expect(socket.init).toHaveBeenCalled();
            expect(socket.connectContacts).toHaveBeenCalled();
            expect(socket.connectUser).not.toHaveBeenCalled();
            expect(socket.init.callCount).toEqual(1);
            expect(CANDDi.isDefined.callCount).toEqual(2);
            expect(CANDDi.isEmpty.callCount).toEqual(1);
            expect(CANDDi.isInstance.callCount).toEqual(1);
            expect(window.io.connect.callCount).toEqual(1);
            expect(window.io.socket.on.callCount).toEqual(4);
            expect(contact.setSocket.callCount).toEqual(1);
            expect(contact.callbackSocket.callCount).toEqual(0);
        });

        /* Spec 3. */
        it("Spec 3: socket.connectUser", function() {
            expect(socket).toBeDefined();
            expect(user).toBeDefined();
            {
                socket.init('http://api.tld/endpoint/user');
                socket.connectUser(user);
            }
            expect(socket.init).toHaveBeenCalled();
            expect(socket.connectContacts).not.toHaveBeenCalled();
            expect(socket.connectUser).toHaveBeenCalled();
            expect(socket.init.callCount).toEqual(1);
            expect(CANDDi.isDefined.callCount).toEqual(2);
            expect(CANDDi.isEmpty.callCount).toEqual(1);
            expect(CANDDi.isInstance.callCount).toEqual(1);
            expect(window.io.connect.callCount).toEqual(1);
            expect(window.io.socket.on.callCount).toEqual(4);
            expect(user.setSocket.callCount).toEqual(1);
            expect(user.callbackSocket.callCount).toEqual(0);
            expect(user.get).toHaveBeenCalledWith('UserTypeId');
        });

    });

});

