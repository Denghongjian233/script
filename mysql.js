// 导入 mysql 模块
const mysql = require('mysql');

// 创建数据库连接配置
const connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '123456',
    port: 3306,
    authSwitchHandler: (data, callback) => {
      if (data.pluginName === 'caching_sha2_password') {
        const password = '123456'; // your MySQL user password
        const scrambleBuff = Buffer.from(data.authPluginData, 'hex');
        const token = Buffer.from(
          require('mysql').sha256(Buffer.concat([
            Buffer.from(password),
            require('crypto').createHash('sha256').update(scrambleBuff).digest()
          ])).toString('hex'), 'hex'
        );
        const packet = Buffer.allocUnsafe(1 + token.length);
  
        packet[0] = 0x01;
        token.copy(packet, 1);
  
        callback(packet);
      } else {
        callback(null);
      }
    }
  });

// 连接到 MySQL 数据库
connection.connect((err) => {
  if (err) {
    console.error('Error connecting to MySQL database: ' + err.stack);
    return;
  }
  console.log('Connected to MySQL database as id ' + connection.threadId);
});

// 当连接结束时关闭连接
connection.end((err) => {
  if (err) {
    console.error('Error closing MySQL connection: ' + err.stack);
    return;
  }
  console.log('MySQL connection closed');
});
