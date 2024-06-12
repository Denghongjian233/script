// 判断是不是数组



// function isArray(obj: any): boolean {
//     return Array.isArray(obj);
// }

// // 实现LRU缓存置换算法

// class LRUCache {
//     private cache: Map<number, number>;
//     private capacity: number;

//     constructor(capacity: number) {
//         this.cache = new Map();
//         this.capacity = capacity;
//     }

//     get(key: number): number {
        
//         if (this.cache.has(key)) {
            

//             const value = this.cache.get(key);
//             this.cache.delete(key);
//             this.cache.set(key, value);
//             return value;
//         }
//     }

//     put(key: number, value: number): void {
        
//         if (this.cache.has(key)) {
//             this.cache.delete(key);
//         } else if (this.cache.size >= this.capacity) {
//             this.cache.delete(this.cache.keys().next().value);
//         }
//         this.cache.set(key, value);

//     }

// }

// 背包问题

function knapsack(weights: number[], values: number[], capacity: number): number {
    const n = weights.length;
    let result = new Array(capacity).fill(0);
    
    for (let i = 0; i < capacity; i++) {
        if(weights[i] <= i){
            result[i] = values[0]
            console.log(result)
        }else{
            result[i] = 0
        }
    }
    console.log(result)

    for (let i = 1; i < n; i++) {
        let next = new Array(capacity).fill(0);
        for(let j = 1;j<capacity;j++){
            if(weights[j] <= capacity){
                next[j] = Math.max(result[j],result[j-weights[i]]+values[i])
            }else{
                next[j] = result[j]
            }
        }
        result = next
    }
    return result[capacity-1]
}
const weights = [2, 3, 4, 5];
const values = [3, 4, 5, 6];
const capacity = 5;

console.log(knapsack(weights, values, capacity));  // 输出：7

function pick<T, K extends keyof T>(obj: T, keys: K[]): Pick<T, K> {
    let result = {} as Pick<T, K>;
    keys.forEach(key => {
        if (key in obj) {
            result[key] = obj[key];
        }
    });
    return result;
}

const person = { name: "Alice", age: 25, city: "New York" };
const picked = pick(person, ["name", "city"]);
// picked is { name: "Alice", city: "New York" }

function isString(value: any): value is string {
    return typeof value === "string";
}

function example(value: string | number) {
    if (isString(value)) {
        // value 在这里是 string 类型
        console.log(value.toUpperCase());
    } else {
        // value 在这里是 number 类型
        console.log(value.toFixed(2));
    }
}

function log(target: any, key: string) {
    let value = target[key];

    const getter = () => {
        console.log(`Get: ${key} => ${value}`);
        return value;
    };

    const setter = (newVal) => {
        console.log(`Set: ${key} => ${newVal}`);
        value = newVal;
    };

    Object.defineProperty(target, key, {
        get: getter,
        set: setter,
        enumerable: true,
        configurable: true
    });
}

class Person {
    @log
    name: string;

    constructor(name: string) {
        this.name = name;
    }
}

let p = new Person("John");
p.name = "Doe";

