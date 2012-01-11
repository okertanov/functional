Shairtunes story on github
==========================

    git checkout --track -b infra-003 origin/infra-003
      or
    git checkout -b infra-003
    git branch
    git push -u origin origin:refs/heads/infra-003
    git branch -a
    git branch --set-upstream infra-003 origin/infra-003
    git branch

    git checkout -b jhl-004
    git push -u origin origin:refs/heads/jhl-004
    git branch --set-upstream jhl-004 origin/jhl-004

    git remote add albertz https://github.com/albertz/shairport.git
    git branch -a
    git fetch albertz
    git checkout master
    git branch -a
    git fetch albertz master
    git rebase albertz/master
    git diff --cached
    git diff HEAD^
    git diff --cached
    git commit -a --amend
    git push

