const fs = require('fs');
const path = require('path');
const simpleGit = require('simple-git');

const LOCAL_REPO_PATH = '/Users/hjiandeng/code/study';  // 替换为本地仓库路径
const FILE_PATH = 'ts.md';  // 替换为你要修改的文件相对于仓库根目录的路径
const BRANCH_NAME = 'main';  // 替换为你的分支名称

// 常用提交信息前缀
const COMMIT_PREFIXES = ['feat:', 'fix:', 'chore:', 'refactor:', 'docs:', 'style:', 'test:', 'perf:'];

// 随机生成提交信息
function getRandomCommitMessage() {
    const prefix = COMMIT_PREFIXES[Math.floor(Math.random() * COMMIT_PREFIXES.length)];
    const details = [
        'automatically update file',
        'improve performance',
        'fix a bug',
        'update documentation',
        'refactor codebase',
        'style code improvements',
        'add unit tests',
        'optimize build process'
    ];
    const detail = details[Math.floor(Math.random() * details.length)];
    return `${prefix} ${detail}`;
}

// 修改文件内容
function modifyFile(filePath) {
    fs.appendFileSync(filePath, '\nNew line added automatically.\n', 'utf8');
}

// 提交并推送更改
async function commitAndPush(repoPath, filePath, commitMessage, branchName) {
    const git = simpleGit(repoPath);
    await git.add(filePath);
    await git.commit(commitMessage);
    await git.push('origin', branchName);
}

async function main() {
    try {
        const fullFilePath = path.join(LOCAL_REPO_PATH, FILE_PATH);
        
        // 修改文件内容
        modifyFile(fullFilePath);
        
        // 生成随机提交信息
        const commitMessage = getRandomCommitMessage();
        
        // 提交并推送更改
        await commitAndPush(LOCAL_REPO_PATH, FILE_PATH, commitMessage, BRANCH_NAME);

        console.log('File modified, committed, and pushed successfully.');
        console.log(`Commit message: ${commitMessage}`);
    } catch (err) {
        console.error('Error:', err);
    }
}

main().catch(err => {
    console.error('Error:', err);
});
