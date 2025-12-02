Rebasing is an important aspect of any open-source project that receives lots of contributions. We should aim to rebase our main feature branches regularly, as to not introduce too much of a departure from the source branch. When we fail to keep our feature branch up to date, we allow the possibility of merge conflicts that will prevent our contributions from making their way into the open-source repository.

## What is rebasing?

Rebasing can simply be put as taking a set of commits, and moving them onto another set of commits (i.e., changing the relative "base"). This is different from merging, which takes a set of commits and adds them to our current history. There are benefits and dangers to both actions, however, the primary purpose for rebasing is to bring the new commits from a source branch into our current branch while maintaining a clean history.

For example, if we have an existing feature branch `Kusto-phase3` that was previously rebased onto ClickHouse's tagged release of `v23.10.5.20-stable` then our commit graph might look like the following

```
    (v23.10.5.20-stable)
    |       (v23.12.2.59-stable)
    ⌄       ⌄
o---o---o---o---o  ClickHouse/master
     \
      o---o---o---o---o  ClibMouse/Kusto-phase3
```

In this example, ClickHouse's main branch has continued development, and may even have a new tagged release which we'd like to target for a rebase, such as `v23.12.2.59-stable`.  To rebase onto this new target, is effectively moving all of our commits from `Kusto-phase3` on top of a new target

```
    (tags/v23.10.5.20-stable)
    |       (tags/v23.12.2.59-stable)
    ⌄       ⌄
o---o---o---o---o  ClickHouse/master
             \
              o---o---o---o---o  ClibMouse/Kusto-phase3
```

When we do this, we will attempt to add one-by-one, each commit from `Kusto-phase3` onto our new base. If a commit cannot be applied, because the file has changed in someway from what the commit has written, then we will be required to resolve the resulting conflict. Whenever we are rebasing, we are effectively **rewriting history**, which means that any commit SHAs will be regenerated and resigned through the operation.

For a complete overview, please read the `git` related documentation [here](https://git-scm.com/docs/git-rebase).

## Setup

The following instructions assume that `origin` points to the IBM fork of ClickHouse and `upstream` points to the original ClickHouse repository.

``` bash
$ git remote --verbose
origin  git@github.com:ClibMouse/ClickHouse.git (fetch)
origin  git@github.com:ClibMouse/ClickHouse.git (push)
upstream        git@github.com:ClickHouse/ClickHouse.git (fetch)
upstream        git@github.com:ClickHouse/ClickHouse.git (push) 
```

## Conducting a rebase

First, we will want to fetch all refs from our two remote repositories, checkout the latest version of the branch that we want to rebase, and create a draft branch that we can work off of

``` bash
$ git fetch --all
$ git checkout origin/Kusto-phase3
$ git pull
$ git checkout -b Kusto-phase3-24.01.15 # Example uses the date we started the rebase
$ git push --set-upstream origin Kusto-phase3-24.01.15
```

To start the rebase, we can do one of the following

``` bash
# Rebase the branch onto ClickHouse master (auto detect base)
$ git rebase -i upstream/master

# Rebase the branch onto ClickHouse version tag (auto detect base)
$ git rebase -i --onto tags/v23.12.2.59-stable

# Rebase the branch from one ClickHouse version tag onto another (specify base)
$ git rebase -i --onto tags/v23.12.2.59-stable tags/v23.10.5.20-stable
```

The interactive mode will look something like 

```
pick ddb1b744602 Backport #52680 to 23.7: Fix bugs and better test for SYSTEM STOP LISTEN
pick 8b364127ede added single unit test case for summarize bin()
...
pick 2726f800abb Revert "Kusto-phase3: Optimizing the 'summarize' operator" (#402)
pick 1e1f94f75c7 Kusto-phase3: rebase v23.10.5.20-stable

# Rebase e84001e5c61..1e1f94f75c7 onto 17ab210e761 (365 commands)
#
...
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
```

From this view we have the ability to squash commits, drop anything that is a duplicate, etc. (see the full commands list for more information). When this buffer is closed, the commands will be executed one-by-one from the top of the list down, adding the commits onto the new base. 

Periodically, a command may fail to automatically apply, causing the rebase to be halted. One reason for this could be that some patches contained in the current commit can not be automatically merged. This is typically the result of changes being made to the effected file upstream. Whatever the reason, we need to resolve a merge conflict.

Another possibility, is that the patch that the commit represents is rendered "empty" do to upstream changes already having equivalent changes. This can include a cherry-picked commit being in both the target and source branches, or some KQL features being merged from an OSS PR that has a commit different from the current commit. We may get a notice similar to the following

```
The previous cherry-pick is now empty, possibly due to conflict resolution.
If you wish to commit it anyway, use:

    git commit --allow-empty

Otherwise, please use 'git rebase --skip'
```

In these situations, we can simply use `--skip` to drop the commit.

At any time, we can `--abort` to return to the state prior to the rebase. This command will, however, cause any work or changes to commits to be lost. For this reason, while going through a large rebase such as with KQL, it can be good to make notes of what work was done on which commits. For example, taking notes that look something like this

```
# Note: Mostly accept incoming for toStartOfInterval.cpp
pick 7b108495eeb Rework timespan-handling

# NOTE: Accept current, but remove the three lines for the exception.
pick a6339d3b343 Fix errors by Clang 15 and clean up includes

# NOTE: Accept incoming with some tweaks.
pick db54031e3ce Enable PR Sanity Checks (#197)

# NOTE: Accept both, move the set for max bytes bellow the subtable insert.
pick 79290b895be Kusto-phase3: fix make-series bug

# NOTE: Some accepting of both, but making them work together.
pick 1e1f94f75c7 Kusto-phase3: rebase v23.10.5.20-stable
```

may help for in the event that we need to either, go back to the beginning, or look back to see what modifications were made.

**⚠️ Warning ⚠️** If the rebase was made to `Kusto-phase3` directly and not on a draft branch (such as `Kusto-phase3-24.01.15` used in the example above), we will want to take extra care to ensure that no commits were added to `Kusto-phase3` in the remote repository that we don't have on our local branch. Once we force push our changes to GitHub, the remote repository's copy of the branch will be overwritten and anything not on the local branch will be lost on the remote branch. It is good to always check and verify that what we see with

``` bash
$ git log # Note, commit SHAs will be different after a rebase from what is on GitHub
```

and finally when we have verified that it is safe to do so we can 

```
$ git push -f
```

to rewrite the history for the branch.

If we have been working off of a draft branch, we can "copy" our changes over to the original source branch with something like the following

```
$ git checkout Kusto-phase3
$ git reset --hard Kusto-phase3-24.01.15
$ git push -f
# Kusto-phase3 is now overwritten by contents from Kusto-phase3-24.01.15
```

