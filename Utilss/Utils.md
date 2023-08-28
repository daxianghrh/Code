# 常用工具的面试

## Git

### 1、如何撤销已提交到远程仓库的上一次操作？

当你需要撤销已经推送到远程仓库的提交时，可以使用 `git revert` 创建一个撤销提交，并将其推送到远程仓库，以撤销之前的提交。以下是一个具体示例：

假设你有一个远程仓库和一个名为 `main` 的主分支，其中已经有一些提交。现在你想撤销某个之前的提交，具体步骤如下：

1. 首先，使用 `git log` 或其他方式查找你想要撤销的提交的哈希值（commit hash）。
```bash
commit aab2a1fa6afb691d8232f1c01c6406239b73a03a (commit hash)
Date:   Mon Aug 21 21:18:51 2023 +0800

    update net
```
2. 创建一个新分支，用于进行撤销操作：
   ```
   git checkout -b revert-branch
   ```

3. 使用 `git revert` 撤销指定的提交。假设你想要撤销的提交哈希是 `<commit-hash>`：
   ```
   git revert <commit-hash>
   ```

   这会打开一个编辑器，让你添加一条撤销提交的消息。保存并关闭编辑器。

4. 提交撤销的更改：
   ```
   git commit -m "Revert commit <commit-hash>"
   ```

5. 将撤销分支推送到远程仓库：
   ```
   git push origin revert-branch
   ```

6. 接下来，你可以在远程仓库中创建一个 Pull Request（或合并请求），将撤销分支合并到主分支。这将把撤销的更改应用于主分支，从而撤销之前的提交。
