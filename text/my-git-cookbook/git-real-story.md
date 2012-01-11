The real-world story of github
==============================

0. Intro
--------


1. Fork
-------
``github://clone repo-url.git``  
``cd projects/3rdparty``  
``git clone repo-url.git repo-url-orig``  
``git clone my.repo.url.git repo-url-fork``  

    $ ls -l 
    drwxr-xr-x 6 okertanov okertanov 4096 2011-03-29 17:05 node-compress-buffer-orig
    drwxr-xr-x 6 okertanov okertanov 4096 2011-03-29 17:49 node-compress-buffer-fork

``cd node-compress-buffer-fork``  
``git remote add upstream https://github.com/egorFiNE/node-compress-buffer.git``  

    $ git remote -v
    origin  git@github.com:okertanov/node-compress-buffer.git (fetch)
    origin  git@github.com:okertanov/node-compress-buffer.git (push)
    upstream    https://github.com/egorFiNE/node-compress-buffer.git (fetch)
    upstream    https://github.com/egorFiNE/node-compress-buffer.git (push)

``git fetch origin``  
``git fetch upstream``  

    $ git branch -a
    * master
      remotes/origin/HEAD -> origin/master
      remotes/origin/master
      remotes/upstream/master

``git pull upstream master``  


2. Feature branch
-----------------
``git tag -a "t_via_egorFiNE"``  
``git tag``  
``git branch -a``  
``git branch out-of-c``  
``git push origin origin:refs/heads/out-of-c``  
``git pull origin out-of-c``  


3. Patch & code
---------------
``$vim src/*``  
``$npm install node-compress-buffer-fork``  
``$npm install nodeunit``  


4. Periodical sync with the upstream
------------------------------------
``git branch``  
``git branch -a``  
``git checkout master``  
``git pull upstream master``  
``git checkout out-of-c``  
``git branch``  
``git pull origin out-of-c``  


5. Commit
---------
``git commit -a -m "static z_stream"``  
``git diff HEAD^``  
``git commit -a -m "strdup for *string; length() method instead of strlen(); throwexception(); z_stream wrapper;"``  
``git pull origin out-of-c``  
``git diff master out-of-c | gvim -``  
``git push``  
``git status``  


6. Testing, testing, testing
----------------------------
``npm install node-compress-buffer-orig``  
``npm install node-compress-buffer-fork``  
``./node_modules/nodeunit/bin/nodeunit ./node-compress-buffer-fork/test/node-compress-buffer-test.js``  


7. Pull request
---------------
``git push && git status``  
``run unittests!``  
``github://pull request``  


8. Create feature branch on the upstream and merge local fork into it
---------------------------------------------------------------------
> When you are becoming collaboration member so do this:  
> git remote prune upstream  
> git remote update
> vim .git/config  
> git remote add upstream git@github.com:egorFiNE/node-compress-buffer.git  
> git diff out-of-c remotes/upstream/master  
> git pull upstream master  
> git checkout -b upstream upstream/master  
> git megre out-of-c  
> git status  
> git push upstream out-of-c  


9. Finalize: Closing merged branch
----------------------------------
``git branch -a`` - list all branches  
``git branch -d out-of-c`` - remove local branch  
``git push git@github.com:egorFiNE/node-compress-buffer.git :out-of-c`` - remove remote branch  
``git remote prune origin`` - cleanup deleted remote branches  


10. Done!
--------


11. Beside all things
--------------------
11.1. Communicate with the author:  
- Clearly know what you should change & push it to the upstream  
- Define the name of the changeset  
- Know author's mail/twitter  
- Read author's lists/groups  
- Read author's bugtracking url  
11.2. Write down your log  
11.3. Learn your tools  
11.4. GPG your tags  
11.5. Unittest before commits  
11.6. NLS this writing and create the course  


