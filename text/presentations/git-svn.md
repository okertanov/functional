Git or SVN? - Both!
===================

Intro
-----

On SVN
------
  
On Git
------

Blob storage by hash SHA1

    git init
    git init --bare
    git clone transport://remote.endpoint/repository.git

    git fetch
    git pull    (git fetch && git merge origin/master --ff)
    git push
    git push -u origin master

    git remote -v
    git remote add origin

    git status
    git diff master..HEAD~

    git log
    git log --one-line
    git log -p
    git log -10
    git log --since="date"
    git log --author

    git add -p
    git commit
    git commit -a -m "a changeset message"
    git commit --amend

    git checkout
    git checkout -b
    git branch
    git tag

    git merge
    git merge --squash
    git rebase
    git rebase --interactive

    git checkout filename
    git reset --soft HEAD^
    git commit -a --amend
    git reset --hard HEAD

    git stash 
    git cherry-pick
    git format-patch 
    git apply patch-file
    git gc
    git clean
    git grep
    git submodule add git://github.com/user/module.git module

    hooks/post-receive

    .gitconfig
    .gitignore
  

On git-svn
----------

    git svn clone
    git svn rebase
    git svn dcommit  
