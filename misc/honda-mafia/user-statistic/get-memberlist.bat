@FOR /L %%U IN (0,40,6000) DO @wget -a "session.log" -O "memberlist-%%U.html" --html-extension --keep-session-cookies --relative --load-cookies="Mozilla\Firefox\Profile\cookies.txt"  "http://honda.org.ua/forum/memberlist.php?mode=joined&order=ASC&start=%%U"