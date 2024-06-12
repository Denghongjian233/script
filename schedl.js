const { exec } = require('child_process');

// 定义一个函数来执行 index.js
function runScript() {
    console.log('Running index.js at', new Date());

    exec('node index.js', (error, stdout, stderr) => {
        if (error) {
            console.error(`Execution error: ${error.message}`);
            return;
        }

        if (stderr) {
            console.error(`stderr: ${stderr}`);
            return;
        }

        console.log(`stdout: ${stdout}`);
    });
}

// 立即执行一次
runScript();

// 设置定时器，每小时执行一次
setInterval(runScript, 1000); // 每小时（3600000 毫秒）执行一次
     