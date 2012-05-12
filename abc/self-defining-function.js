/*
    via http://habrahabr.ru/post/133074/
    Иногда бывает так, что при первом вызове функции нужно выполнить какие-нибудь дополнительные действия.
    Реализовать это можно следующим образом:
*/

var selfDefining = function()
{
    console.log("some really heavy initialization occured");
    console.log("f*ck yeah!");
    selfDefining = function(){
        console.log("job done!");
    }
}
selfDefining();
selfDefining();

