My github Howtos
================

Initialize global user info
---------------------------
    git config --global user.name "okertanov"
    git config --global user.email "okertanov@gmail.com"

    git config --global github.user okertanov
    git config --global github.token <api-token>

    git config --list

Tuning git
----------
    git var -l
    git config --global core.autocrlf input
    git config --global color.ui auto
    git config --global color.interactive auto
    git config --global color.diff auto
    git config --global color.status auto
    git config --global color.branch auto
    git config --global core.pager 'vim -R -'

    git config --global push.default tracking
    git config --global branch.autosetuprebase always

    git config --global core.excludesfile '~/.gitignore'

    When branching off a remote branch, automatically let the local branch track the remote branch:
    git config --global branch.autosetupmerge true

    When pushing without giving a refspec, push the current branch to its upstream branch:
    git config --global push.default tracking

    Enable the recording of resolved conflicts, so that identical hunks can be resolved automatically later on:
    git config --global rerere.enabled true

    Always show a diffstat at the end of a merge:
    git config --global merge.stat true

Global Config files
-------------------
    /usr/local/share/git-core/templates
    ~/.gitconfig
    ~/.gitattributes
    ~/.gitignore
    .git/hooks/

Create new github repo online & push
------------------------------------
    mkdir okertanov.github.com
    cd okertanov.github.com
    git init
    touch README
    git add README
    git commit -m 'first commit'
    git remote add origin git@github.com:okertanov/okertanov.github.com.git
    git push -u origin master

Create new github repo with the commandline & push
--------------------------------------------------
    sudo aptitude install curl
    mkdir -p projects/chicken-scheme
    cd projects/chicken-scheme
    git init
    ls -la
    touch cc-gen-a.ss
    git add cc-gen-a.ss
    git commit -a -m "initial import"
    curl -X POST https://okertanov:password@github.com/api/v2/json/repos/create -F 'name=chicken-scheme'
    git remote add origin git@github.com:okertanov/chicken-scheme
    git push -u origin master
    git status
    git pull

Help, everybody, help
---------------------
``git help command``  
``git command -h``  

Clone, rename
-------------
``git clone git://server.tld/path-to-repo.git`` - create a fork  
``git clone local-1 local-2`` - clone local copy to another  

Init repo
---------
``git init example.com``  
``cd example.com``  
``git commit --allow-empty -m "Initial Commit"``  
``git remote add origin ssh://git@github.com/okertanov/repositoryname.git``  
``git push origin master``  

Normal Git cycle
----------------
    git pull
    git status
    git diff --cached
    git add .
    git commit -a -m "a changeset message"
    git push

Normal Github cycle
-------------------
    git clone git@github.com:okertanov/some-project.git
    cd some-project
    git remote add upstream git://github.com/mainteiner/some-project.git
    git fetch upstream
    git push origin master
    git fetch upstream
    git merge upstream/master
    git remote rm upstream

Fetch then merge instead of pull
--------------------------------
``git fetch``  
``git merge origin/master``  

Normal Sync cycle
----------------
### Actualize master
    git fetch
    git co master
    git merge origin/master

### Rebase feature branch to master
    git checkout my-branch
    git rebase master

### Push to remote branch
    git push origin my-branch

Tags
----
``git tag -l`` - list all tags for the branch  
``git tag "v1.00"`` - create lightweight tag  
``git tag -a -s "v1.00-verified"`` -m "Tag reason message" - create signed and annotated tag  
``git checkout tag-name`` - check out y tag  
``git push --tags`` - push created tags  
``git fetch --tags`` - to pull all tags in  

Branches
--------
``git branch`` - list of the current branch  
``git branch future`` - create a WIP branch  
``git branch --track future origin/future`` - create a tracking branch  
``git branch --track feature origin/feature`` - create another tracking branch  
``git checkout origin/gh-pages -b gh-pages`` - create local tracking branch on with remote one  
``git checkout -b future`` - create and switch to a branch at the same time  
``git checkout -b future origin/future`` - clone branch from the repository  
``git checkout future`` - switch to the future branch  
``git push -u origin origin:refs/heads/future`` - push current branch to the server  
``git branch --set-upstream future origin/future`` - set remote tracking  
``git fetch origin future:future`` - update the branch  
``git pull origin future`` - pull the branch  
``git branch -a`` - list all of the branches  
``git fetch --all`` - get all branches from the server  
``git checkout --track -b future origin/future`` - get the branch  
``git rebase master`` - rebase master changes to the branch  
``git rebase --continue`` - continue to rebase after the conflict  
``git checkout master`` - switch back to the master branch  
``git diff master..future`` - diff master vs branch  
``git merge future`` - merge branch to the master  
``git merge --squash future`` - merge & squash future's commits  
``git mergetool`` - resolve conflicts with the merge tool  
``git branch -d future`` - delete obsolete  
``git branch -D future`` - force delete unmerged obsolete  
``git push origin :future`` - delete remote branch after the above commands  
``git branch -m new-branch-name`` - rename branch  

* [WIP]: Work In Progress

More on rebase
--------------
``git checkout local-branch``  
``git fetch``  
``git rebase remotes/origin/remote-branch>`` or ``git pull --rebase``  
``vim conflicting-file``  
``git update-index``  
``git rebase --continue`` or  
``git rebase --skip`` or  
``git rebase --abort``  
``git rebase -i`` - to squash into one commit  

Rebase actions
--------------
 * Reword - change the commit message to something else (e.g. to add a bug reference)
 * Edit - to make changes to the commit itself (e.g. fix a typo in the code)
 * Pick - to include that commit in the history
 * Squash - to condense that commit with the previous and make them one (and concatenate log entry)
 * Fixup - to condense that commit with the previous and make them one (and discard log entry)

Patchsets
---------
``git format-patch -n1`` - create patchset within n revisions back  
``curl https://github.com/user/project/pull/123.patch | git am`` - manually apply the pool request  
``git apply --check patchset.patch`` - check it before applying  
``git apply --stat patchset.patch`` - applying the patch  

Revert or Undo
--------------
``git reset --hard`` - abandon everything since your last commit.  
``git reset --soft HEAD^`` - Undo last commit, but keep the changes in the staging area.  
``git reset HEAD`` - unstage everything  
``git reflog`` - shows all actions that have been done in your repository.  
``rm file.c && git checkout -- .`` - reconstruct the working copy.  

Log, Diff
---------
    git log --oneline
    git log --pretty=oneline --abbrev-commit
    git log --pretty=oneline --graph
    git log --pretty=oneline --graph --decorate
    git log --author=okertanov --since="14 days ago" --pretty=oneline
    git log --format='%aN' | sort -u
    git diff HEAD^ HEAD
    git diff origin/master..HEAD
    git diff master origin/master
    git annotate file

Grep
----
``git grep word`` - search for word in the repo  
``git grep -c goto`` - calculate goto occurrence in a project  
``git grep word v1`` - search for word in the branch/tag  
``git grep -e 'first' --and -e 'another'`` - logically combined search (and)  
``git grep --all-match -e 'first' -e 'second'`` - logically combined search (or)  

Statuses or where am i
----------------------
``git status``  
``git log``  
``git show``  
``git diff``  
``git diff HEAD~~~~``  
``git diff master..HEAD``  
``git diff --cached``  
``git diff master..experimental``  
``git log origin/master..HEAD`` - see what you're about to push to a remote  
``git show _tag_``  

``git log --stat origin..@{0}`` - super command: What commits to Push.  
``git config --global alias.wu "log --stat origin..@{0}"`` - create alias from above one.  

``git log -p origin..@{0}`` - super command: What diff of commits to Push.  
``git config --global alias.wup "log -p origin..@{0}"`` - create alias from above one.  

``git diff origin..@{0}`` - like above but combined in the one patch.  

`git whatchanged --since="1 day ago" -p` - see what's up  

Revert changes
--------------
    git reset --hard HEAD
        or
    git checkout -f
        or
    git checkout filename
        or
    git diff path-to-the-file | patch -p1 -R

Fix last commit
---------------
``vim file`` - edit again  
``git commit --amend file`` - recommit with the previous comment message  
``git commit --amend`` - just edit the commit message  

Collapse last commit
--------------------
    git reset --soft HEAD^
    git commit -a --amend

svn ls for github
-----------------
    curl http://github.com/api/v2/json/repos/show/okertanov
    curl http://github.com/api/v1/json/okertanov
    curl http://github.com/api/v1/json/search/"search term"

Repo info
---------
    git remote -v
    git remote show origin

rev-parse
---------
Pick out and massage parameters  
    git rev-parse --show-toplevel
    git rev-parse --is-inside-work-tree
    git rev-parse --local-env-vars

List the remote branches
------------------------
    git branch -a
    git show-ref
    git show-branch
    git rev-parse HEAD

Stash
-----
    git stash list
    git stash save
    git stash apply
    git stash pop
    git stash clear

Notes
-----
    git notes - Add or inspect object notes

Submodules
----------
    git submodule add git://github.com/user/module.git module
    git submodule status
    git commit -m "Module added"
    git clone main-module
    git submodule init
    git submodule update
    git submodule update --init
    git submodule foreach --recursive git submodule update --init
    git submodule foreach 'git checkout master && git pull origin master'

Gnome's Git guidelines
----------------------
> It can be convenient to set up a clone alias:
> git config --global url.ssh://[login@]git.gnome.org/git/.insteadof gnome:
> Then the clone line becomes much shorter:
> git clone gnome:[project]
>
> You can check out an existing local branch using the following command:
> git checkout -b [branch name] origin/[branch name]
> like
> git checkout -b my-branch origin/my-branch
> you can also use:
> git checkout --track origin/my-branch
>
> You can create a local branch tracking a remote branch by using:
> git branch my-branch origin/my-branch
>
> The following command syncs up your code with what is stored in the Git repository:
> git pull --rebase
>
> Git has this great feature which makes resolving merge conflicts easy:
> git-mergetool
>
> If you want to edit / reorder / squash-into-one the last five commits, do:
> git rebase -i HEAD~5

msysgit & github's ssh
----------------------
    cd C:\tools\msysgit\
    msys.bat
    vim /bin/my-plink

    #!/bin/sh
    #plink -batch -v -i "c:\okertanov\.ssh\id_dsa-private.ppk" $1 $2
    ssh -i "/c/okertanov/.ssh/id_dsa-private" "$@"

    export GIT_SSH=my-plink

Server-side git
---------------
``mkdir module-shared.git && cd module-shared.git``  
``git --bare init --shared``  

Setting up a shared repository
------------------------------
``ssh git-server git init --shared --bare /srv/git/repo.git``  
``git clone ssh://git-server/srv/git/repo.git``  

    sudo groupadd developers
    sudo chgrp -R developers /srv/git/repo.git
    sudo chmod -R g+wX,o= /srv/git/repo.git
    sudo find /srv/git/repo.git -type d -exec chmod g+s '{}' ';'


Manage a site with git
----------------------
``mkdir website.git && cd website.git``  
``git init --bare``  
``mkdir /var/www/www.example.org``  
``vim hooks/post-receive``  

> \#!/bin/sh  
> GIT\_WORK\_TREE=/var/www/www.example.org git checkout -f  

``chmod +x hooks/post-receive``  

``git remote add web ssh://server.example.org/home/ams/website.git``  
``git push web +master:refs/heads/master``  

> [remote "web"]  
>     url = ssh://server.example.org/home/ams/website.git  
>     url = ssh://other.example.org/home/foo/website.git  


Uncategorized topics
--------------------
``git add -p`` - interactive add with review  
``git clean -fd`` - clean unversioned files  
``git clean -fdx`` - clean gitignored files  
``git gc`` - repo optimization & repackage  
``git filter-branch --tag-name-filter cat --env-filter "export GIT_AUTHOR_NAME='New name';export GIT_AUTHOR_EMAIL='New email'" -- --all``  
``git log --no-merges --pretty=format:%aN --since=7months | sort | uniq -c | sort -nr``  
``git repack -a -d -f --depth=512 --window=512``  


Git Applications
----------------
### Linux
* gitg
* giggle
* git gui

### Mac OS X Git Applications
* Tower
* Gitbox
* GitX

### Windows
* msysgit

Useful links
------------
1.  [git-scm.com][1]
2.  [gitref.org][2]
3.  [progit.org/book][3]
4.  [progit.org/book/ru][4]
5.  [help.github.com][5]
6.  [pages.github.com][6]
7.  [daringfireball.net/projects/markdown][7]
8.  [Everyday GIT With 20 Commands Or So][8]
9.  [Introduction To Git][9]
10. [Git - SVN Crash Course][10]
11. [Git cheat sheets][11]
12. [A successful git branching model][12]
13. [A successful git branching model RU Habr][13]
14. [Git Magic][14]
15. [Using Git to manage a web site][15]
16. [Fork a repo via Github][16]
17. [Working with remotes][17]
18. [Git cheat sheet][18]
19. [Git tricks, tips and workflows][19]
20. [Sourcemage Git Guide][20]
21. [Videolan's Git Guide][21]
22. [Gnome Git][22]
23. [GitReady][23]
24. [Git cheat sheets][24]
25. [Maxim Oleinik's cheat sheet][25]
26. [The Git Community Book][26]
27. [Brilliant Git Cheatsheet][27]
28. [GitFaq][28]
29. [Git bare vs. non-bare repositories][29]
30. [I have a pull request on github now what?][30]
31. [Git Immersion: a guided tour][31]
32. [A successful Git branching model][32]
33. [alblue.bandlem on git][33]
34. [Удачная модель ветвления для Git][34]
35. [Git Is Simpler Than You Think][35]

[1]:  http://git-scm.com/
[2]:  http://gitref.org/
[3]:  http://progit.org/book/
[4]:  http://progit.org/book/ru/
[5]:  http://help.github.com/
[6]:  http://pages.github.com/
[7]:  http://daringfireball.net/projects/markdown/
[8]:  http://www.kernel.org/pub/software/scm/git/docs/everyday.html
[9]:  http://learn.github.com/p/intro.html
[10]: http://git.or.cz/course/svn.html
[11]: http://help.github.com/git-cheat-sheets/
[12]: http://nvie.com/posts/a-successful-git-branching-model/
[13]: http://habrahabr.ru/blogs/Git/106912/
[14]: http://www-cs-students.stanford.edu/~blynn/gitmagic/
[15]: http://toroid.org/ams/git-website-howto
[16]: http://help.github.com/fork-a-repo/
[17]: http://help.github.com/remotes/
[18]: http://cheat.errtheblog.com/s/git/
[19]: http://nuclearsquid.com/writings/git-tricks-tips-workflows.html
[20]: http://www.sourcemage.org/Git_Guide
[21]: http://wiki.videolan.org/Git
[22]: http://live.gnome.org/Git
[23]: http://gitready.com/
[24]: http://help.github.com/git-cheat-sheets/
[25]: https://github.com/maxim-oleinik/symfony-dev-rules/blob/master/git-cheat-sheet.txt
[26]: http://book.git-scm.com/
[27]: http://www.ndpsoftware.com/git-cheatsheet.html
[28]: https://git.wiki.kernel.org/index.php/GitFaq
[29]: http://www.bitflop.com/document/111
[30]: http://www.viget.com/extend/i-have-a-pull-request-on-github-now-what/
[31]: http://gitimmersion.com/index.html
[32]: http://nvie.com/posts/a-successful-git-branching-model/
[33]: http://alblue.bandlem.com/search/label/git
[34]: http://habrahabr.ru/blogs/Git/106912/
[35]: http://nfarina.com/post/9868516270/git-is-simpler

My github links
---------------
* [github.com/okertanov][55]
* [okertanov.github.com][56]
* [gist.github.com/mine][57]

[55]: https://github.com/okertanov
[56]: http://okertanov.github.com/
[57]: https://gist.github.com/mine
