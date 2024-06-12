let a = () => {
  console.log("fdfs");
};
function currying() {
  return () => {
    a();
  };
}
currying()(3);
// 节流 定时器写法

function throttle(fn, delay) {
  let timer = null;
  return function () {
    if (!timer) {
      timer = setTimeout(() => {
        fn.apply(this, arguments);
        timer = null;
      }, delay);
    }
  };
}

// 防抖 定时器写法
function debounce(fn, delay) {
  let timer = null;
  return function () {
    if (timer) {
      clearTimeout(timer);
    }
    timer = setTimeout(() => {
      fn.apply(this, arguments);
    }, delay);
  };
}

// 柯里化
// function currying(fn) {
//   return function curriedFn(...args) {
//     if (args.length >= fn.length) {
//       return fn.apply(this, args);
//     } else {
//       return function (...args2) {
//         return curriedFn.apply(this, args.concat(args2));
//       };
//     }
//   };
// }
function MyComponent({ items }) {
  for (let i = 0; i < items.length; i++) {
    const [value, setValue] = useState(0); // 错误：在循环中调用 useState
    // ...
  }
}

function customPromiseAll(promises) {
  return new Promise((resolve, reject) => {
    if (!Array.isArray(promises)) {
      return reject(new TypeError("Argument must be an array"));
    }

    let resolvedCount = 0;
    const results = new Array(promises.length);

    promises.forEach((promise, index) => {
      Promise.resolve(promise)
        .then((value) => {
          results[index] = value;
          resolvedCount++;

          if (resolvedCount === promises.length) {
            resolve(results);
          }
        })
        .catch((error) => {
          reject(error);
        });
    });
  });
}
function PromiseAll(promises) {
  return new Promise((resolve, reject) => {
    let count = 0;
    const results = [];
    promises.forEach((promise, index) => {
      Promise.resolve(promise)
        .then((value) => {
          results[index] = value;
          count++;
          if (count === promises.length) {
            resolve(results);
          }
        })
        .catch((error) => {
          reject(error);
        });
    });
  });
}
