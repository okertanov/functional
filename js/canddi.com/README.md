CANDDi Task
===========

Letter
------
    from        *@canddi.com
    to          Oleg Kertanov <okertanov@gmail.com>
    date        Mon, Sep *, 201* at 9:** PM
    subject     Re: *************** apply for Hardcore Javascript Hacker
    signed-by   canddi.com

    >> The doc blocks should be self explanatory (but please ask questions if not)
    >> We use jasmine (http://pivotal.github.com/jasmine/) for unit testing
    >>
    >> Would you like to cover this in tests and five me a shout
    >> We can talk about this code and your background experience


Usage
-----

1. git submodule init && git submodule update # to clone jasmine into ./canddi.com/jasmine  
2. open RunTests.html  

Manifest
--------
* jasmine - JavaScript testing framework git submodule  
   jasmine/lib  
   jasmine/spec  
   jasmine/src  
   jasmine/images  
   jasmine/etc...  
* CANDDi.Node.Mock.js - Fake namespace to simulate whole system environment  
* CANDDi.Node.Socket.js - Original attachment with the code  
* CANDDi.Node.SocketSpec.js - Test specification for Jasmine BDD  
* RunTests.html - The test runner  
* README.md - This document  

