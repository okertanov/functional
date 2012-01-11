Getting /etc under the revision control with git
================================================

Prepare and import
------------------
    sudo tar czvf /var/backups/etc-backup-pre-git-`uname -n`-`date +%d-%m-%Y`.tgz /etc

    cd /etc
    git config --list

    sudo git status
    sudo git init


    sudo find /etc -type f -print0 | sudo xargs -0 dpkg -S 2>&1 | vim -
    sudo vim .gitignore
    sudo git add .gitignore
    sudo git commit -a -m "git init and a basic .gitignore"

    sudo git add .
    sudo git commit -a -m "initial /etc structure added"
    sudo git status
    sudo git log

    sudo git tag initial
    sudo git tag

Commit changes
--------------
    sudo git add -A .
    sudo git commit -a -m "autocommit on xyz..."

Automation
----------
     man apt.conf
     DPkg::Post-Invoke
     /etc/apt/apt.conf.d

Backups
-------

Rollback
--------

