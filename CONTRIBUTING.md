# CONTRIBUTING

OpenPool project welcomes new contributors.  This document will guide you
through the process.

### FORK

Fork the project [on GitHub](https://github.com/openpool/openpool-core-unity)
and check out your copy.  For keeping code quarities of our project, we separate
devel(opment) branch from master branch, so you HAVE TO checkout local branch
from "devel" and send pull request into it.  Also we recommend you to make
your own topic branch (like FEATUREBRANCH) for managing your commit.
```
# Clone your fork of the repo into the current directory
$ git clone git@github.com:YOURNAME/openpool-core-unity.git
# Navigate to the newly cloned directory
$ cd openpool-core-unity
# Assign the original repo to a remote called "openpool"
$ git remote add openpool git@github.com:openpool/openpool-core.git
$ git checkout devel
$ git checkout -b FEATUREBRANCH
```

### REBASE

Use `git rebase` (not `git merge`) to sync your work from time to time.

```
$ git checkout devel
$ git pull openpool devel
$ git rebase devel FEATUREBRANCH
```

### COMMIT

Writing good commit logs is important.  Our recommendation is to make commits
as meaningful small change, and gather it before pushing.
```
$ git commit -m "short comment"
```

### PUSH
```
$ git push origin FEATUREBRANCH
```

Go to https://github.com/YOURNAME/openpool-core-unity and select your topic branch.
Click the 'Pull Request' button, select "devel" as a base branch and fill out the form.

