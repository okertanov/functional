Git as SVN client
=================

Git or SVN? – Both!
-------------------

Intro
-----
Git is revision control system like Perforce or SVN, but in some distributed flavour.
Distributed means that Git is capable to manage your repository in-place, without having central repo.
Also distributed means that everyone who cares (and have permissions to) may access your repo to read and write code changes.

![screenshot](https://raw.github.com/okertanov/functional/master/text/my-git-cookbook/git-svn-repos.png "svn vs git")

### Comparing to other RCS/SCM it's:
 * Fast
 * Free
 * Stable
 * Powerful
 * Well documented
 * Easy to start using it
 * Flexible workflow
 * Works locally on your computer
 * Supports lightweight branches with COW
 * Works on the top of secure and reliable networking protocols
 * Have biggest user base
 * Have best hosting service: github
 * Activelly developed
 * Have built-in perforce, svn and cvs support
 * IBM, Google, Apple, Microsoft, Apache, Eclipse, Linux, Facebook, Twitter, Intel, Mozilla, Amazon, Samsung...


Installation
------------
### In Windows
1. Install latest official distribution of Git for Windows ([link](http://msysgit.github.io/))
2. Install TortoiseGit ([link](https://code.google.com/p/tortoisegit/))

### With OS X
#### Install using Homebrew:
1. Install Homebrew ([link](http://brew.sh/))
2. Install git with the command:
```
    brew install git
```

#### Install using XCode:
1. Launch XCode
2. Go to Preferences->Downloads and select "Install command line tools"

### For Linux (Debian/Ubuntu)
1. In the command prompt run the following:
```
    sudo aptitude install git-core
```

### Other GUI clients
If you personally prefers rich user interface over the command line you may install one of the following:
 * XCode4 and 5 has built-in Git support
 * Eclipse has Git support
 * Netbeans has Git support via plugin
 * Git Extensions for Windows
 * GitHub for Windows
 * GitHub for Mac
 * GitX (Mac)
 * Tower (Mac)
 * Gitbox (Mac)
 * SourceTree (Win/Mac)
 * GitEye (Mac)
 * tig (Unix)


Configure your Git
------------------
### Introduce yourself

    git config --global user.name "Name Surname" # Insert your real name here
    git config --global user.email "recipient@example.com" # Insert your valid email address


Start using Git like SVN client
-------------------------------
### First rule - Is it works for you

    git --version

### Second rule - Know your repo

    svn info # Inside your project

### Third rule - Stay in your working directory

    cd ~/projects

### Initial checkout or Cloning

    git svn clone https://svn.example.com/svn/projects/trunk LocalProjectName


Daily workflow
--------------
### Update your local snapshot from SVN repo

    git svn rebase

### Modify code to complete the task, bug fix, or other coding activity
Use your IDE or the editors as usual, like
```
   vim file1.cpp file2.cpp
   ...
```

### Stage your local changes

    git add ModifiedFile.txt OtherModifiedCode.cpp AndMore.cs AndEvenMore.m
    git add Other/Path/And.a.File.txt
    git add .

### Commit your changes to your local repo

    git commit

### Push your changes to the central SVN repo

    git svn rebase
    git svn dcommit


Git only goodies (uncategorized)
--------------------------------

    git help
    git clone
    git init
    git add
    git commit
    git status
    git log
    git diff
    git grep
    git blame
    git fetch
    git pull
    git push
    git branch
    git merge
    git rebase
    git reset
    git show
    git stash
    git remote
    git cherry-pick
    git submodule
    git clean


Other useful tasks
------------------
### Test drive your commit without actually commiting
```
    git svn dcommit --dry-run
```

### Generate .gitignore from SVN
```
    git svn create-ignore
```

### Generate and use SSH key

    ssh-keygen -t rsa -b 1024 -C "recipient@example.com"
    cat ~/.ssh/id_rsa.pub | pbcopy


Resources
---------
[Git Home page](http://git-scm.com/)  
[Try Git](http://try.github.io/)  
[Pro Git book](http://git-scm.com/book)  
[Git via Git :)](https://github.com/git/git)  
[Git Wiki: Main page](https://git.wiki.kernel.org/index.php/Main_Page)  
[Git Wiki: Git interfaces, frontends, and tools](https://git.wiki.kernel.org/index.php/InterfacesFrontendsAndTools)  
