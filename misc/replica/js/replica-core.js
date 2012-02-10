
    var g_uploading = false;

    var userAgent = navigator.userAgent.toLowerCase();
    var browser =
    {
        version: (userAgent.match( /.+(?:rv|it|ra|ie)[\/: ]([\d.]+)/ ) || [0,'0'])[1],
        safari: /webkit/.test( userAgent ),
        opera: /opera/.test( userAgent ) && !/(mini|midp)/.test( userAgent ),
        msie: /msie/.test( userAgent ) && !/opera/.test( userAgent ),
        mozilla: /mozilla/.test( userAgent ) && !/(compatible|webkit)/.test( userAgent ),
        touch: /webkit/.test( userAgent ) && /mobile/.test( userAgent ),
        mobile: /windows\sce/.test( userAgent ) || /iemobile/.test( userAgent ) || /windows\sphone/.test( userAgent ) || /avantgo/.test( userAgent ),
        simple: /midp/.test( userAgent ) || /cldc/.test( userAgent ),

        getUA: function(){ return userAgent; },
        getVersion: function(){ return this.version; },
        isIE:   function(){ return this.msie; },
        isSafari: function(){ return this.safari; },
        isMozilla: function(){ return this.mozilla; },
        isTouch: function(){ return this.touch; },
        isMobile: function(){ return this.mobile; },
        isSimple:  function(){ return this.simple; },
        isDesktop:  function(){ return (this.safari || this.opera || this.msie || this.mozilla) && !(this.touch || this.mobile || this.simple); }
    };

    $(document).ready(function() {
        $('#upload').bind('dragenter', function() {
            $('#droptext').addClass('dragging');
        }).bind('dragleave', function() {
            $('#droptext').removeClass('dragging');
        }).bind('change drop', function() {
            $('#droptext').removeClass('dragging');

            //if ( browser.isSafari() ) //ok, chrome == safari
            {
                if ( false == g_uploading )
                {
                    var drop_files = this.files;
                    do_upload(drop_files);
                    this.value = "";
                }
            }

        });

        if (
             ( browser.isSafari() )  ||
             ( browser.isMozilla() && /\/3\.6/.test( browser.getUA()) )
           )
        {
            $('#drop-caption').text('Drop Image file Here');

            if ( browser.isMozilla() && /\/3\.6/.test( browser.getUA()) )
            {
                ff36_set_handlers('droptext');
            }
        }
        else
        {
            $('#drop-caption').text('Click Here to upload Image');
        }
    });

    function stop_action(evt)
    {
        if ( evt.target.id != "upload" && false == g_uploading )
        {
            evt.preventDefault();
            evt.stopPropagation();
        }
    }

    /*async upload code*/
    function do_upload(drfiles)
    {
        $('#drop-form').submit();
    }

    function upload_done(res, url)
    {
        g_uploading = false;
        $('#container').fadeTo('slow', 1);

        if (res)
        {
            prompt("Copy the URL", url);
        }
        else
        {
            alert("There was an error uploading your file \n\n" + url);
        }
    }

    function on_upload()
    {
        g_uploading = true;
        $('#container').fadeTo('slow', 0.1);
    }
    /**/

    /*ff code*/
    function ff36_do_upload(drfiles)
    {
        on_upload();

        /**/
        http_request = new XMLHttpRequest();
        var boundaryString = 'the_boundary--';
        var boundary = '--' + boundaryString;
        var requestbody = boundary + '\n'

        + 'Content-Disposition: form-data; name="drop-form"' + '\n'
        + '\n'
        + drfiles[0].fileName + '\n'
        + '\n'
        + boundary + '\n'
        + 'Content-Disposition: form-data; name="files"; filename="'
            + drfiles[0].fileName + '"' + '\n'
        + 'Content-Type: application/octet-stream' + '\n'
        + '\n'
        + drfiles[0].getAsBinary()
        + '\n'
        + boundary;

        http_request.onreadystatechange = ff36_handle_ready;
        http_request.open('POST', 'upload.php', true);
        http_request.setRequestHeader("Content-type", "multipart/form-data; \
            boundary=\"" + boundaryString + "\"");
        http_request.setRequestHeader("Connection", "close");
        http_request.setRequestHeader("Content-length", requestbody.length);
        http_request.sendAsBinary(requestbody);
        /**/
    }

    function ff36_handle_ready()
    {
        if (this.readyState == 4)
        {
            if(this.status == 200)
            {
                var pathStored = this.responseText;
                $('#upload-target').html( pathStored );
            }
        }
    }

    function ff36_stop_action(event)
    {
        event.preventDefault();
        event.stopPropagation();
    }

    function ff36_handle_drop(event)
    {
        ff36_stop_action(event);

        var drop_files = event.dataTransfer.files;

        ff36_do_upload(drop_files);
    }

    function ff36_set_handlers(dropId)
    {

        var dropTarget = document.getElementById(dropId);
        ff36_add_event(dropTarget,'dragover', ff36_stop_action, true);
        ff36_add_event(dropTarget,'dragenter', ff36_stop_action, true);
        ff36_add_event(dropTarget,'drop', ff36_handle_drop, true);
    }

    function ff36_add_event(obj, evType, fn, useCapture)
    {
        if (obj.addEventListener)
        {
            obj.addEventListener(evType, fn, useCapture);
            return true;
        }
        else if (obj.attachEvent)
        {
            var r = obj.attachEvent("on"+evType, fn);
            return r;
        }
    }
    /*ff code*/

