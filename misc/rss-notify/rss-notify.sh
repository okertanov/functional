#!/bin/bash

user=`whoami`
/home/$user/bin/rsstail -i 180 -N -H -n 3 -p -P -z -l -m -v \
-u http://habrahabr.ru/rss/ \
-u http://k.img.com.ua/rss/ru/news.xml \
-u http://honda.org.ua/forum/rss.php  \
-u http://www.linux.org.ru/section-rss.jsp?section=1 \
    | while read line ; do
        echo "$line"
        header=`echo "$line" | sed -e 's/^.*\s\*\(.*\)\*\s.*$/\1/'`
        body=`echo "$line" | sed -e 's/\s\*\(.*\)\*\s//'`
        notify-send --urgency normal --expire-time=900000 -i tomboy "$header" "$body" ;
done

