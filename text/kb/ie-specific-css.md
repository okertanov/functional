CSS Specific for Internet Explorer
----------------------------------

### IE Conditional Comments
    <!--[if IE 8]> <![endif]--> = IE8
    <!--[if lt IE 8]> <![endif]--> = IE7 or below
    <!--[if gte IE 8]> <![endif]--> = greater than or equal to IE8

### CSS Rules Specific to Explorer (IE CSS hacks)
    .box
    {
        background: gray; /* standard */
        background: pink\9; /* IE 8 and below */
        *background: green; /* IE 7 and below */
        _background: blue; /* IE 6 */
    }

### Conditional HTML Class
    <!--[if lt IE 7 ]> <html class="ie6"> <![endif]-->
    <!--[if IE 7 ]> <html class="ie7"> <![endif]-->
    <!--[if IE 8 ]> <html class="ie8"> <![endif]-->
    <!--[if IE 9 ]> <html class="ie9"> <![endif]-->
    <!--[if (gt IE 9)|!(IE)]><!--> <html> <!--<![endif]-->


/via [http://www.webdesignerwall.com/tutorials/css-specific-for-internet-explorer/](http://www.webdesignerwall.com/tutorials/css-specific-for-internet-explorer/)

[See also html5boilerplate.com](http://html5boilerplate.com/)

