Gerrit on Tallinn.local
=======================

    ssh -v -L 10.0.35.156:8080:10.211.55.4:8080 kertanov@tallinn
    sudo java -jar gerrit-2.8.3.war init --batch -d /srv/gerrit/data

    vim data/etc/gerrit.config
    sudo data/bin/gerrit.sh restart

    mkdir -p /srv/git/repo
    git svn clone ...
    git remote add gerrit ssh://kertanov@tallinn:29418/Mobile
    git remote show gerrit

    git svn rebase
    git push -u gerrit HEAD:refs/for/master
